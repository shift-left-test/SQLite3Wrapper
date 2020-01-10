/*
  MIT License

  Copyright (c) 2020 Sung Gon Kim

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#ifndef INCLUDE_SQLITE3_STATEMENT_HPP_
#define INCLUDE_SQLITE3_STATEMENT_HPP_

#include <sqlite3.h>
#include <memory>
#include "SQLite3/Column.hpp"

namespace SQLite3 {

class Statement {
 public:
  explicit Statement(sqlite3_stmt* stmt);
  int execute();
  bool fetch();
  void reset();

  Statement& bind(int index, int value);
  Statement& bind(int index, double value);
  Statement& bind(int index, const std::string& value);
  Statement& bind(int index);
  Statement& bind(const std::string& name, int value);
  Statement& bind(const std::string& name, double value);
  Statement& bind(const std::string& name, const std::string& value);
  Statement& bind(const std::string& name);
  Column getColumn(int index);
  Column getColumn(const std::string& name);

  Column operator[](int index);
  Column operator[](const std::string& name);

 private:
  sqlite3* getDB();
  sqlite3_stmt* getStmt();
  void check(int status);
  int toIndex(const std::string& name);

  std::unique_ptr<sqlite3_stmt, int(*)(sqlite3_stmt*)> mStmt;
};

}  // namespace SQLite3

#endif  // INCLUDE_SQLITE3_STATEMENT_HPP_
