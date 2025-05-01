# MIT License
#
# Copyright (c) 2020 LG Electronics, Inc.
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

if(WITH_TESTS)
  include(GoogleTest)

  add_executable(SQLite3WrapperTest DatabaseTest.cpp StatementTest.cpp ColumnTest.cpp)

  set_target_properties(SQLite3WrapperTest PROPERTIES SUFFIX .exe)

  target_include_directories(SQLite3WrapperTest PRIVATE ${CMAKE_SOURCE_DIR})

  target_link_libraries(SQLite3WrapperTest PRIVATE SQLite3Wrapper)
  target_link_libraries(SQLite3WrapperTest PRIVATE gmock gtest gtest_main)

  gtest_add_tests(SQLite3WrapperTest "" AUTO)
endif(WITH_TESTS)
