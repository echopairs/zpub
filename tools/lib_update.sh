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

## init zeromq
## TODO
