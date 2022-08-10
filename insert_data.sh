#!/bin/bash

python2 insert_data.py gcc-x64/running_insertion.cpp.csv "Running insertion"             "gcc-x64/Running insertion.xlsx"             "plot"
python2 insert_data.py gcc-x64/running_erasure.cpp.csv   "Running erasure"               "gcc-x64/Running erasure.xlsx"               "plot"
python2 insert_data.py gcc-x64/scattered_lookup.cpp.csv  "Scattered successful lookup"   "gcc-x64/Scattered successful looukp.xlsx"   "plot"
python2 insert_data.py gcc-x64/scattered_lookup.cpp.csv  "Scattered unsuccessful lookup" "gcc-x64/Scattered unsuccessful looukp.xlsx" "plot"

python2 insert_data.py clang-x64/running_insertion.cpp.csv "Running insertion"             "clang-x64/Running insertion.xlsx"             "plot"
python2 insert_data.py clang-x64/running_erasure.cpp.csv   "Running erasure"               "clang-x64/Running erasure.xlsx"               "plot"
python2 insert_data.py clang-x64/scattered_lookup.cpp.csv  "Scattered successful lookup"   "clang-x64/Scattered successful looukp.xlsx"   "plot"
python2 insert_data.py clang-x64/scattered_lookup.cpp.csv  "Scattered unsuccessful lookup" "clang-x64/Scattered unsuccessful looukp.xlsx" "plot"

python2 insert_data.py -e utf-16 vs-x64/running_insertion.cpp.csv "Running insertion"             "vs-x64/Running insertion.xlsx"             "plot"
python2 insert_data.py -e utf-16 vs-x64/running_erasure.cpp.csv   "Running erasure"               "vs-x64/Running erasure.xlsx"               "plot"
python2 insert_data.py -e utf-16 vs-x64/scattered_lookup.cpp.csv  "Scattered successful lookup"   "vs-x64/Scattered successful looukp.xlsx"   "plot"
python2 insert_data.py -e utf-16 vs-x64/scattered_lookup.cpp.csv  "Scattered unsuccessful lookup" "vs-x64/Scattered unsuccessful looukp.xlsx" "plot"