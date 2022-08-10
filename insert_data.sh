#!/bin/bash

python2 insert_data.py gcc-x64/running_insertion.cpp.csv "Runnning insertion"            "gcc-x64/Runnning insertion.xlsx"            "plot"
python2 insert_data.py gcc-x64/scattered_lookup.cpp.csv  "Scattered successful lookup"   "gcc-x64/Scattered successful looukp.xlsx"   "plot"
python2 insert_data.py gcc-x64/scattered_lookup.cpp.csv  "Scattered unsuccessful lookup" "gcc-x64/Scattered unsuccessful looukp.xlsx" "plot"

python2 insert_data.py clang-x64/running_insertion.cpp.csv "Runnning insertion"            "clang-x64/Runnning insertion.xlsx"            "plot"
python2 insert_data.py clang-x64/scattered_lookup.cpp.csv  "Scattered successful lookup"   "clang-x64/Scattered successful looukp.xlsx"   "plot"
python2 insert_data.py clang-x64/scattered_lookup.cpp.csv  "Scattered unsuccessful lookup" "clang-x64/Scattered unsuccessful looukp.xlsx" "plot"

python2 insert_data.py -e utf-16 vs-x64/running_insertion.cpp.csv "Runnning insertion"            "vs-x64/Runnning insertion.xlsx"            "plot"
python2 insert_data.py -e utf-16 vs-x64/scattered_lookup.cpp.csv  "Scattered successful lookup"   "vs-x64/Scattered successful looukp.xlsx"   "plot"
python2 insert_data.py -e utf-16 vs-x64/scattered_lookup.cpp.csv  "Scattered unsuccessful lookup" "vs-x64/Scattered unsuccessful looukp.xlsx" "plot"