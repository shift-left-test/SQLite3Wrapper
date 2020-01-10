# SQLite3

This is SQLite3


### Requirements

* C++ compiler (c++11 supported)
* CMake 3.5.1 or above
* Google Test Framework
* gcovr, python
* doxygen, graphviz
* (OPTIONAL) clang-tidy, cppcheck, cpplint


### How to install the required software packages

    $ sudo apt-get install build-essential cmake git python clang-tidy cppcheck libgtest-dev doxygen graphviz
    & sudo pip install cpplint gcovr
    $ cmake -H/usr/src/gtest -Bbuild
    $ make -C build
    $ sudo cp build/libgtest*.a /usr/lib


### How to build from source

    $ ./build.sh


### Licenses

The project source code is available under MIT license. See [LICENSE](LICENSE).
