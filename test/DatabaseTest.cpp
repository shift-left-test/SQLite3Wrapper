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

#include <gtest/gtest.h>
#include <memory>
#include <stdexcept>
#include "Constants.hpp"
#include "SQLite3/Database.hpp"

class DatabaseTest : public ::testing::Test {
 protected:
  void SetUp() override {
    db = std::make_shared<SQLite3::Database>(Constants::DB_FILE);
  }
  std::shared_ptr<SQLite3::Database> db;
};

TEST_F(DatabaseTest, testInitOKWhenDefaultOptionGiven) {
  EXPECT_NO_THROW({ SQLite3::Database db(Constants::DB_FILE); });
}

TEST_F(DatabaseTest, testInitFailsWhenFileNotExist) {
  EXPECT_THROW({ SQLite3::Database db(Constants::DB_FILE, 0); },
               std::runtime_error);
}

TEST_F(DatabaseTest, testExecuteOKWhenValidQueryGiven) {
  EXPECT_NO_THROW(db->execute(Constants::CREATE_TABLE));
}

TEST_F(DatabaseTest, testExecuteFailsWhenConstraintsNotHold) {
  EXPECT_NO_THROW(db->execute(Constants::CREATE_TABLE));
  EXPECT_THROW(db->execute(Constants::CREATE_TABLE), std::runtime_error);
}

TEST_F(DatabaseTest, testExecuteFailsWhenInvalidQueryGiven) {
  EXPECT_THROW(db->execute(Constants::INVALID_QUERY), std::runtime_error);
}

TEST_F(DatabaseTest, testExecuteFailsWhenReadOnlyDBGiven) {
  SQLite3::Database db(Constants::DB_FILE, SQLite3::Database::OPEN::READONLY);
  EXPECT_THROW(db.execute(Constants::CREATE_TABLE), std::runtime_error);
}
