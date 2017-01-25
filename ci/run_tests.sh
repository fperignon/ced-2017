#!/bin/bash
mkdir build
cd build
export CXX=g++ FC=gfortran
cmake -D CMAKE_BUILD_TYPE=Debug -DWITH_BOOST=ON -DWITH_FFTW=ON ../solutions
make
make test
