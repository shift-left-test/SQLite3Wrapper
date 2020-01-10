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

#ifndef INCLUDE_SQLITE3_DATABASE_HPP_
#define INCLUDE_SQLITE3_DATABASE_HPP_

#include <sqlite3.h>
#include <memory>
#include <string>
#include "SQLite3/Statement.hpp"

namespace SQLite3 {

class Database {
 public:
  enum OPEN {
    READWRITE = SQLITE_OPEN_READWRITE,
    READONLY = SQLITE_OPEN_READONLY,
    CREATE = SQLITE_OPEN_CREATE,
  };

  explicit Database(const std::string& path);
  Database(const std::string& path, int flags);

  int execute(const std::string& sql);
  Statement prepare(const std::string& sql);

 private:
  sqlite3* getDB();
  void check(int status);

  std::unique_ptr<sqlite3, int(*)(sqlite3*)> mDB;
};

}  // namespace SQLite3

#endif  // INCLUDE_SQLITE3_DATABASE_HPP_
