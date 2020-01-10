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

#include "SQLite3/Statement.hpp"

namespace SQLite3 {

Statement::Statement(sqlite3_stmt* stmt) : mStmt(stmt, sqlite3_finalize) {
}

sqlite3* Statement::getDB() {
  return sqlite3_db_handle(getStmt());
}

sqlite3_stmt* Statement::getStmt() {
  return mStmt.get();
}

void Statement::check(int status) {
  if (status != SQLITE_OK) {
    throw std::runtime_error(sqlite3_errmsg(getDB()));
  }
}

int Statement::execute() {
  if (sqlite3_step(getStmt()) != SQLITE_DONE) {
    throw std::runtime_error(sqlite3_errmsg(getDB()));
  }
  return sqlite3_changes(getDB());
}

bool Statement::fetch() {
  auto status = sqlite3_step(getStmt());
  if (status == SQLITE_ROW) {
    return true;
  }
  if (status == SQLITE_DONE) {
    return false;
  }
  throw std::runtime_error(sqlite3_errmsg(getDB()));
}

void Statement::reset() {
  sqlite3_reset(getStmt());
  sqlite3_clear_bindings(getStmt());
}

Statement& Statement::bind(int index, int value) {
  check(sqlite3_bind_int(getStmt(), index, value));
  return *this;
}

Statement& Statement::bind(int index, double value) {
  check(sqlite3_bind_double(getStmt(), index, value));
  return *this;
}

Statement& Statement::bind(int index, const std::string& value) {
  check(sqlite3_bind_text(getStmt(), index, value.c_str(), -1,
                          SQLITE_TRANSIENT));
  return *this;
}

Statement& Statement::bind(int index) {
  check(sqlite3_bind_null(getStmt(), index));
  return *this;
}

int Statement::toIndex(const std::string& name) {
  return sqlite3_bind_parameter_index(getStmt(), name.c_str());
}

Statement& Statement::bind(const std::string& name, int value) {
  return bind(toIndex(name), value);
}

Statement& Statement::bind(const std::string& name, double value) {
  return bind(toIndex(name), value);
}

Statement& Statement::bind(const std::string& name, const std::string& value) {
  return bind(toIndex(name), value);
}

Statement& Statement::bind(const std::string& name) {
  return bind(toIndex(name));
}

Column Statement::getColumn(int index) {
  if (index < 0 || sqlite3_column_count(getStmt()) <= index) {
    throw std::runtime_error(std::to_string(index) + ": out of bounds");
  }
  return Column(getStmt(), index);
}

Column Statement::getColumn(const std::string& name) {
  for (int index = 0; index < sqlite3_column_count(getStmt()); ++index) {
    if (name == sqlite3_column_name(getStmt(), index)) {
      return Column(getStmt(), index);
    }
  }
  throw std::runtime_error(name + ": column does not exist");
}

Column Statement::operator[](int index) {
  return getColumn(index);
}

Column Statement::operator[](const std::string& name) {
  return getColumn(name);
}

}  // namespace SQLite3
