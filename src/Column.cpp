/*
  MIT License

  Copyright (c) 2020 LG Electronics, Inc.

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

#include "SQLite3Wrapper/Column.hpp"

namespace SQLite3Wrapper {

Column::Column(sqlite3_stmt* stmt, int index) :
    mStmt(stmt), mIndex(index) {
}

const char* Column::getName() const noexcept {
  return sqlite3_column_name(mStmt, mIndex);
}

int Column::getInt() const noexcept {
  return sqlite3_column_int(mStmt, mIndex);
}

double Column::getDouble() const noexcept {
  return sqlite3_column_double(mStmt, mIndex);
}

const char* Column::getText() const noexcept {
  return reinterpret_cast<const char*>(sqlite3_column_text(mStmt, mIndex));
}

const void* Column::getBlob() const noexcept {
  return sqlite3_column_blob(mStmt, mIndex);
}

int Column::size() const noexcept {
  return sqlite3_column_bytes(mStmt, mIndex);
}

}  // namespace SQLite3Wrapper
