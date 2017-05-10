#!/usr/bin/env bash

sed -i 's/std::forward_list/forward_list/g' *.cpp
sed -i 's/<forward_list>/"forward_list.h"/g' *.cpp

