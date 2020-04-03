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
#include "SQLite3Wrapper/Database.hpp"

class StatementTest : public ::testing::Test {
 protected:
  void SetUp() override {
    db = std::make_shared<SQLite3Wrapper::Database>(Constants::DB_FILE);
    db->execute(Constants::CREATE_TABLE);
  }
  std::shared_ptr<SQLite3Wrapper::Database> db;
};

TEST_F(StatementTest, testExecuteOKWhenValidQueryGiven) {
  auto stmt = db->prepare(Constants::INSERT_RECORD);
  EXPECT_EQ(1, stmt.execute());
}

TEST_F(StatementTest, testExecuteFailsWhenInvalidQueryGiven) {
  EXPECT_THROW(db->prepare(Constants::INVALID_QUERY), std::runtime_error);
}

TEST_F(StatementTest, testExecuteFailsWhenConstraintsNotHold) {
  auto stmt = db->prepare(Constants::INSERT_RECORD);
  EXPECT_NO_THROW(stmt.execute());
  EXPECT_THROW(stmt.execute(), std::runtime_error);
}

TEST_F(StatementTest, testBindOKWhenValidIndicesGiven) {
  auto stmt = db->prepare(Constants::INSERT_FORMAT);
  stmt.bind(1, 1).bind(2, 2.0).bind(3, "three").bind(4);
  EXPECT_NO_THROW(stmt.execute());
}

TEST_F(StatementTest, testBindFailsWhenInvalidIndicesGiven) {
  auto stmt = db->prepare(Constants::INSERT_FORMAT);
  EXPECT_THROW(stmt.bind(0, 1), std::runtime_error);
  EXPECT_THROW(stmt.bind(0, 2.0), std::runtime_error);
  EXPECT_THROW(stmt.bind(10, "three"), std::runtime_error);
  EXPECT_THROW(stmt.bind(10), std::runtime_error);
}

TEST_F(StatementTest, testBindOKWhenValidNamesGiven) {
  auto stmt = db->prepare(Constants::INSERT_FORMAT);
  stmt.bind(":first", 1)
      .bind(":second", 2.0)
      .bind(":third", "three")
      .bind(":fourth");
  EXPECT_NO_THROW(stmt.execute());
}

TEST_F(StatementTest, testBindFailsWhenInvalidNamesGiven) {
  auto stmt = db->prepare(Constants::INSERT_FORMAT);
  EXPECT_THROW(stmt.bind(":unknown", 1), std::runtime_error);
}

TEST_F(StatementTest, testInsertMultipleRecords) {
  auto stmt = db->prepare(Constants::INSERT_FORMAT);
  stmt.bind(":first", 1)
      .bind(":second", 2.0)
      .bind(":third", "three")
      .bind(":fourth");
  EXPECT_NO_THROW(stmt.execute());
  stmt.reset();
  stmt.bind(":first", 2)
      .bind(":second", 2.0)
      .bind(":third", "three")
      .bind(":fourth");
  EXPECT_NO_THROW(stmt.execute());
}

TEST_F(StatementTest, testFetchReturnFalseWhenNoRecordExist) {
  auto stmt = db->prepare(Constants::SELECT_RECORDS);
  EXPECT_FALSE(stmt.fetch());
}

TEST_F(StatementTest, testFetchReturnTrueWhenRecordExist) {
  db->execute(Constants::INSERT_RECORD);
  auto stmt = db->prepare(Constants::SELECT_RECORDS);
  EXPECT_TRUE(stmt.fetch());
}
