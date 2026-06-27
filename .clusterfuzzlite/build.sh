#!/bin/bash -eu

$CXX $CXXFLAGS -std=c++11 -Iinclude \
  -c src/input_parser.cpp -o input_parser.o

$CXX $CXXFLAGS $LIB_FUZZING_ENGINE \
  -std=c++11 -Iinclude \
  fuzz/parser_fuzzer.cc input_parser.o \
  -o $OUT/parser_fuzzer

$CXX $CXXFLAGS $LIB_FUZZING_ENGINE \
  -std=c++11 -Iinclude \
  fuzz/graph_fuzzer.cc input_parser.o \
  -o $OUT/graph_fuzzer

$CXX $CXXFLAGS $LIB_FUZZING_ENGINE \
  -std=c++11 -Iinclude \
  fuzz/tree_fuzzer.cc input_parser.o \
  -o $OUT/tree_fuzzer
