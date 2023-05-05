#!/bin/bash

if ! [ -x "$(command -v wget)" ]; then
  echo -e "\033[31mError: wget is not installed."
  exit 1
fi

if ! [ -x "$(command -v tar)" ]; then
  echo -e "\033[31mError: tar is not installed."
  exit 1
fi

echo "Downloading dependencies ..."

wget https://boostorg.jfrog.io/artifactory/main/release/1.82.0/source/boost_1_82_0.tar.gz -O /tmp/boost_1_82_0.tar.gz > /dev/null 2>&1 &

if [ ! -d "lib" ]; then
  mkdir lib
fi
cd lib

tar -xf /tmp/boost_1_82_0.tar.gz > /dev/null 2>&1 &

wait
echo -e "\033[32mTerminado con éxito\033[0m"
