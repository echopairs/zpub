#!/usr/bin/env bash

#-------------------------------------
# Filename: lib_update.sh
# Revision: 1.0
# Data: 2017/01/05
# Des: build Dependent libraries
# Env: Ubuntu 16.04.1
#-------------------------------------

set -e
script=$(readlink -f "$0")
route=$(dirname "$script")


if [ -d "$route/install_zmq" ]; then
   sudo  rm -rf $route/install_zmq
fi
mkdir $route/install_zmq
cd $route/install_zmq
# build zmp
git clone https://github.com/zeromq/libzmq
cd libzmq && mkdir build
cd build
cmake ../ || exit 1
make -j 4 || exit 2
make test || exit 3

sudo make install
#sudo checkinstall -D --install=yes --fstrans=no --default --pkgname=zmq --pkgversion=4.2.2 --pakdir=$route || exit 4
# build zmqc++
cd $route/install_zmq
git clone https://github.com/zeromq/cppzmq.git
cd cppzmq && mkdir build
cd build
cmake ../ || exit 5
make -j 4 || exit 6
#sudo checkinstall -D --install=yes --fstrans=no --default --pkgname=zmq++ --pkgversion=4.2.2 --pakdir=$route

sudo make install

rm -rf install_zmq