#!/usr/bin/env bash

trap 'exit' ERR

apt-get update

apt-get -y install premake4

apt-get -y install g++ libboost-system-dev libboost-program-options-dev

echo "Provision (root) completed."
