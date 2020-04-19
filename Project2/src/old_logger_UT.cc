/**
 * @file logger_UT.cc
 *
 * @copyright 2020 5801 Team3, All rights reserved.
 */

#include <gtest/gtest.h>
#include <list>
#include "../src/logger.h"

/******************************************************
* TEST FEATURE SetUp
*******************************************************/
class LoggerTests : public ::testing::Test {
 protected:
  std::string audit_file_name;
  Logger* audit_log;
  virtual void SetUp() {
    audit_log = new Logger();
  }
  virtual void TearDown() {
    delete audit_log;
  }
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(LoggerTests, Constructor) {
    EXPECT_NO_THROW(audit_log = new Logger());
    audit_log->~Logger();
    EXPECT_ANY_THROW(audit_log = new Logger());
}

TEST_F(LoggerTests, GetLogFile) {
    EXPECT_EQ(audit_log->GetLogFile(), "audit_file.txt");
}

TEST_F(LoggerTests, LogToFile) {
    audit_log->LogToFile("This is a test");
}
