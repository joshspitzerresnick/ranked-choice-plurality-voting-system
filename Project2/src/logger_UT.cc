/**
 * @file logger_UT.cc
 *
 * @copyright 2020 5801 Team3, All rights reserved.
 */

#include <gtest/gtest.h>
#include <list>
#include "logger.cc"

/******************************************************
* TEST FEATURE SetUp
*******************************************************/
class LoggerTests : public ::testing::Test {
 protected:
  std::string testMsg = "Test Message";
  virtual void SetUp() {
  }
  virtual void TearDown() {
  }
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(LoggerTests, LogToFile) {
    Logger::GetLogger()->Log(testMsg);
    Logger::GetLogger()->Log("This is a test... 2nd message");
    LOGGER->Log("This is a test... 3rd message");
}
