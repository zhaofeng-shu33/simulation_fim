[![Build Status](https://api.travis-ci.com/zhaofeng-shu33/simulation_fim.svg?branch=master)](https://travis-ci.com/zhaofeng-shu33/simulation_fim/)

# simulation_lib

`cmake` build system

## General Consideration

On windows platform, you should use [vcpkg](https://github.com/Microsoft/vcpkg) to fix the dependencies. 

## Dependency
To successfully build simulation_lib, the following is required:


* Boost
* lapack Package

On different platforms, we use different wrapper. On Windows, `clapack` is used;
On linux, `lapacke` is used.

## Build Commands
```shell
cd simulation_lib
mkdir build
cd build
cmake ..
```

On Unix systems, you can install the build library by
```shell
sudo make install
```
