/* Measuring running erasure times of unordered associative containers
 * without duplicate elements.
 *
 * Copyright 2013-2022 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#include <algorithm>
#include <array>
#include <chrono>
#include <numeric>

std::chrono::high_resolution_clock::time_point measure_start,measure_pause;

template<typename F>
double measure(F f)
{
  using namespace std::chrono;

  static const int              num_trials=10;
  static const milliseconds     min_time_per_trial(200);
  std::array<double,num_trials> trials;

  for(int i=0;i<num_trials;++i){
    int                               runs=0;
    high_resolution_clock::time_point t2;
    volatile decltype(f())            res; /* to avoid optimizing f() away */

    measure_start=high_resolution_clock::now();
    do{
      res=f();
      ++runs;
      t2=high_resolution_clock::now();
    }while(t2-measure_start<min_time_per_trial);
    trials[i]=duration_cast<duration<double>>(t2-measure_start).count()/runs;
  }

  std::sort(trials.begin(),trials.end());
  return std::accumulate(
    trials.begin()+2,trials.end()-2,0.0)/(trials.size()-4);
}

void pause_timing()
{
  measure_pause=std::chrono::high_resolution_clock::now();
}

void resume_timing()
{
  measure_start+=std::chrono::high_resolution_clock::now()-measure_pause;
}

#include <boost/bind/bind.hpp>
#include <boost/cstdint.hpp>
#include <iostream>
#include <random>
#include <vector>

static std::vector<boost::uint64_t> data,unsuccessful_data;

static inline void initialize_data(unsigned int n)
{
  std::uniform_int_distribution<boost::uint64_t> dist;
  std::mt19937_64                                gen(34862);

  data.clear();
  for(unsigned int i=0;i<n;++i){
    data.push_back(dist(gen));
  }
}

template<typename Container>
Container create(unsigned int n)
{
  Container s;
  for(unsigned int i=0;i<n;++i)s.insert({data[i],i});
  return s;
}

template<typename Container>
struct running_erasure
{
  typedef unsigned int result_type;

  unsigned int operator()(const Container& s0)const
  {
    unsigned int res=0;
    {
      pause_timing();
      Container s=s0;
      resume_timing();
      for(auto first=s.begin(),last=s.end();first!=last;){
        if(first->second%2){
          s.erase(first++);
          ++res;
        }
        else{
          ++first;
        }
      }
      pause_timing();
    }
    resume_timing();
    return res;
  }
};

template<typename T>
boost::reference_wrapper<const T> temp_cref(T&& x)
{
  return boost::cref(static_cast<const T&>(x));
}

template<
  template<typename> class Tester,
  typename Container1,typename Container2,typename Container3>
void test(
  const char* title,
  const char* name1,const char* name2,const char* name3)
{
  unsigned int n0=10000,n1=10000000,dn=500;
  double       fdn=1.05;

  std::cout<<title<<":"<<std::endl;
  std::cout<<name1<<";"<<name2<<";"<<name3<<std::endl;

  initialize_data(n1);

  for(unsigned int n=n0;n<=n1;n+=dn,dn=(unsigned int)(dn*fdn)){
    double t;
    unsigned int m=Tester<Container1>()(create<Container1>(n));

    t=measure(boost::bind(
      Tester<Container1>(),
      temp_cref(create<Container1>(n))));
    std::cout<<n<<";"<<(t/m)*10E6;

    t=measure(boost::bind(
      Tester<Container2>(),
      temp_cref(create<Container2>(n))));
    std::cout<<";"<<(t/m)*10E6;
 
    t=measure(boost::bind(
      Tester<Container3>(),
      temp_cref(create<Container3>(n))));
    std::cout<<";"<<(t/m)*10E6<<std::endl;
  }
}

#include "container_defs.hpp"

int main()
{
  using container_t1=absl::flat_hash_map<boost::uint64_t,boost::uint64_t>;
  using container_t2=foa_unordered_rc_map<
    boost::uint64_t,boost::uint64_t,mulx_hash<boost::uint64_t>,
    std::equal_to<boost::uint64_t>,
    std::allocator<boost::uint64_t>,
    fxa_unordered::rc::group16>;
  using container_t3=foa_unordered_rc_map<
    boost::uint64_t,boost::uint64_t,mulx_hash<boost::uint64_t>,
    std::equal_to<boost::uint64_t>,
    std::allocator<boost::uint64_t>,
    fxa_unordered::rc::group15>;

  test<
    running_erasure,
    container_t1,
    container_t2,
    container_t3>
  (
    "Running erasure",
    "absl::flat_hash_map",
    "foa_unordered_rc16_map",
    "foa_unordered_rc15_map"
  );
}
