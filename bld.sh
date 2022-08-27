#!/bin/bash

rm -rf bin/
mkdir bin


bld="$(tr [A-Z] [a-z] <<< "$1")"
echo "Building...$bld"
gcc -c       src/main.cpp -o bin/main.o
gcc -c       src/intelhexclass.cpp -o bin/intelhexclass.o

gcc -c       src/utils.cpp -o bin/utils.o
gcc -c       src/wiring.cpp -o bin/wiring.o

if [[ $bld == "rpi" ]]
then
  echo "Building Raspberry Pi CC interface"
  gcc -c  -DMACHINE_RPI src/cc_interface.cpp -o bin/cc_interface_rpi.o
  g++  -lwiringPi  bin/main.o bin/intelhexclass.o bin/cc_interface_rpi.o bin/utils.o -o bin/flasher
else
  echo "Building Dummy CC interface"
  gcc -c     src/cc_interface.cpp -o bin/cc_interface.o
  g++  bin/main.o bin/intelhexclass.o bin/cc_interface.o bin/utils.o bin/wiring.o -o bin/egflasher
fi

#
# Create the object files for the static library (without -fPIC)
#
#gcc -c       src/cc11xx/cc_interface.cpp    -o bin/static/cc_interface.o
#gcc   bin/main.o bin/utils.o bin/cc_interface.o -Lbin/static -ltq84 -o bin/statically-linked
#g++  -v bin/main.o bin/utils.o bin/cc_interface.o bin/wiring.o -o bin/egcc
