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

#include <gtest/gtest.h>
#include <memory>
#include <stdexcept>
#include "Constants.hpp"
#include "SQLite3Wrapper/Database.hpp"

class ColumnTest : public ::testing::Test {
 protected:
  void SetUp() override {
    db = std::make_shared<SQLite3Wrapper::Database>(Constants::DB_FILE);
    db->execute(Constants::CREATE_TABLE);
    db->execute(Constants::INSERT_RECORD);
  }
  std::shared_ptr<SQLite3Wrapper::Database> db;
};

TEST_F(ColumnTest, testGetColumnFailsWhenOOBIndexGiven) {
  auto stmt = db->prepare(Constants::SELECT_RECORDS);
  EXPECT_THROW(stmt.getColumn(-1), std::runtime_error);
  EXPECT_THROW(stmt.getColumn(4), std::runtime_error);
}

TEST_F(ColumnTest, testGetColumnOKWhenValidIndexGiven) {
  auto stmt = db->prepare(Constants::SELECT_RECORDS);
  EXPECT_NO_THROW(stmt.getColumn(0));
  EXPECT_NO_THROW(stmt.getColumn(3));
}

TEST_F(ColumnTest, testGetColumFailsWhenUnknownNameGiven) {
  auto stmt = db->prepare(Constants::SELECT_RECORDS);
  EXPECT_THROW(stmt.getColumn("unknown"), std::runtime_error);
}

TEST_F(ColumnTest, testGetColumnOKWhenValidNamesGiven) {
  auto stmt = db->prepare(Constants::SELECT_RECORDS);
  EXPECT_NO_THROW(stmt.getColumn("first"));
  EXPECT_NO_THROW(stmt.getColumn("second"));
  EXPECT_NO_THROW(stmt.getColumn("third"));
  EXPECT_NO_THROW(stmt.getColumn("fourth"));
}

TEST_F(ColumnTest, testGetColumnData) {
  auto stmt = db->prepare(Constants::SELECT_RECORDS);
  EXPECT_TRUE(stmt.fetch());
  EXPECT_STREQ("first", stmt.getColumn(0).getName());
  EXPECT_EQ(1, stmt.getColumn(0).getInt());
  EXPECT_EQ(2.0, stmt.getColumn(1).getDouble());
  EXPECT_STREQ("three", stmt.getColumn("third").getText());
  EXPECT_EQ(nullptr, stmt.getColumn("fourth").getBlob());
  EXPECT_EQ(0, stmt.getColumn("fourth").size());
}

TEST_F(ColumnTest, testGetColumnDataWithSubscriptOperator) {
  auto stmt = db->prepare(Constants::SELECT_RECORDS);
  EXPECT_TRUE(stmt.fetch());
  EXPECT_STREQ("first", stmt[0].getName());
  EXPECT_EQ(1, stmt[0].getInt());
  EXPECT_EQ(2.0, stmt[1].getDouble());
  EXPECT_STREQ("three", stmt["third"].getText());
  EXPECT_EQ(nullptr, stmt["fourth"].getBlob());
  EXPECT_EQ(0, stmt["fourth"].size());
}
