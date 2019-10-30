#!/usr/bin/env sh

if [ -z "$1" ]
    then
        echo "No argument supplied. Choose which problem to build:"
        ls | grep *.cpp
        return
fi

g++ "$1" -I../Catch2/ --std=c++17 -Wall -Wextra -Wpedantic -Werror -Wno-unused-variable
