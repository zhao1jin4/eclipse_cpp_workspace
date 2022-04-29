#!/usr/bin/bash

#rm -rf ./build/
#mkdir ./build
cd ./build
rm -rf *

#cmake ..后不能有空格
cmake -DCMAKE_INSTALL_PREFIX=/tmp/main01 .. #如程序中已经指定DESTINATION这个就没用了

make
./main
make install

cd ..

