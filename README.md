# EIPScanner

[![Build Status](https://travis-ci.com/nimbuscontrols/EIPScanner.svg?branch=master)](https://travis-ci.com/nimbuscontrols/EIPScanner)
![GitHub release (latest by date)](https://img.shields.io/github/v/release/nimbuscontrols/EIPScanner)


Free implementation of Ethernet/IP scanner in C++.


## Features

* Explicit messaging
* Implicit messaging (only point-to-point)
* Discovery

CIP Standard objects:

* File Object (upload only)
* Parameter Object (read only)
* Identity Object

Vendor specific objects:

* RA DPI Fault Object 

## Requirements

* CMake 3.5 and higher
* C++20 compiler (tested with GCC and MinGW)
* Linux, MacOS, and Windows

## Installing

```shell
$ mkdir build && cd build
$ cmake ..
$ cmake --build . --target install
```

## Usage

To see how to work with the library, look into `examples` directory 

## Contribution

We welcome outside contributions for any improvements, features, or new devices (see below) to the library. Please create a pull request with unit/mock tests

## Vendor specific objects & devices

Our goal is to maintain an active device catalog of all EtherNet/IP devices and their objects that we encounter. We encourage others to contribute to this communal device catalog in /src/vendor/.

All vendor source files are automatically enabled. If you'd like to disable vendor files, you can disable with any of the below options.
1) set this option in CMakeLists.txt
```cmake
option(ENABLE_VENDOR_SRC "Enable vendor source" OFF)
```
2) set the cmake build flag 
```shell
-DENABLE_VENDOR_SRC=OFF
```
3) manually comment needed files in src/vendor/CMakeLists.txt

## Testing

To build the tests:

1) set this option in CmakeLists.txt
```cmake
option(TEST_ENABLED "Enable unit test" ON)
```

2) set the cmake build flag
```shell
# in EIPScanner root directory
mkdir build && cd build
cmake -DTEST_ENABLED=ON ..
cmake --build .
```

## IntelliSense

In order to allow the `clangd` server to properly find all of the files being updated, the `compile_commands.json` file needs to be updated.

* I the CMakeLists.txt files have all been updated correctly, the `compile_commands.json` file can be auto-generated

1) generate the file in the `build` directory
```shell
cd build
cmake -DTEST_ENABLED=ON -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
```

2) replace the `compile_commands.json` file with the `build/compile_commands.json` file

## Authors

Aleksey Timin

Adam Roth

Jan Ritzenhoff