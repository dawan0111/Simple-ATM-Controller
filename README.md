# Simple-ATM-Controller

# Introduction
The ATM-Controller accepts command line inputs. The `atm.cpp` file allows for testing of a temporary `bank_api` through the command line, and the `bank_api` is implemented in the `bank_api` file. The `bank_api` includes the following functionalities:

- Verification of the correct PIN Number
- Retrieval of account list
- Withdrawal
- Deposit

# Test code
The code includes the ability to test the `bank_api` using gTest. If gTest is not installed, it must be installed.
## GTest Download
```sh
$ git clone https://github.com/google/googletest
$ cd googletest/
$ mkdir build
$ cd build
$ cmake ..
$ make
$ sudo make install
```

# How to run proogram:
## Build
```sh
$ git clone https://github.com/dawan0111/Simple-ATM-Controller.git
cd Simple-ATM-Controller
mkdir build && cd build
cmake ..
make
```
## Console Application
```sh
./console_app
```
## GTest Code
```sh
./all_test
```