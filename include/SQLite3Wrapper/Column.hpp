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

#ifndef INCLUDE_SQLITE3WRAPPER_COLUMN_HPP_
#define INCLUDE_SQLITE3WRAPPER_COLUMN_HPP_

#include <sqlite3.h>
#include <string>

namespace SQLite3Wrapper {

class Column {
 public:
  Column(sqlite3_stmt* stmt, int index);

  const char* getName() const noexcept;
  int getInt() const noexcept;
  double getDouble() const noexcept;
  const char* getText() const noexcept;
  const void* getBlob() const noexcept;
  int size() const noexcept;

 private:
  sqlite3_stmt* mStmt;
  int mIndex;
};

}  // namespace SQLite3Wrapper

#endif  // INCLUDE_SQLITE3WRAPPER_COLUMN_HPP_
