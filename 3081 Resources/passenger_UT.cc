/* STUDENTS: YOU MUST ADD YOUR PASSENGER UNIT TESTS TO THIS FILE. FORMAT YOUR
 * TESTS TO FIT THE SPECIFICATIONS GIVEN BY THE TESTS PROVIDED IN THIS FILE.
 *
 * Please note, the assessment tests for grading, will use the same include
 * files, class names, and function names for accessing students' code that you
 * find in this file.  So students, if you write your code so that it passes
 * these feedback tests, you can be assured that the auto-grader will at least
 * be able to properly link with your code.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <gtest/gtest.h>
#include "../src/passenger.h"

/******************************************************
* TEST FEATURE SetUp
*******************************************************/

class PassengerTests : public ::testing::Test {

	protected:

  	Passenger* passenger;

	virtual void SetUp() {
    	passenger = new Passenger();
  	}

  	virtual void TearDown() {
    	delete passenger;
  	}

};


/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(PassengerTests, Constructor) {
  	EXPECT_EQ(passenger->IsOnBus(), false);
  	passenger->GetOnBus();
  	EXPECT_EQ(passenger->IsOnBus(), true);
};

TEST_F(PassengerTests, UpdateOffBus) {
	EXPECT_EQ(passenger->IsOnBus(), false);
	passenger->Update();
	EXPECT_EQ(passenger->IsOnBus(), false);
}

TEST_F(PassengerTests, UpdateOnBus) {
	EXPECT_EQ(passenger->IsOnBus(), false);
	passenger->GetOnBus();
	EXPECT_EQ(passenger->IsOnBus(), true);
	passenger->Update();
	EXPECT_EQ(passenger->IsOnBus(), true);
}

TEST_F(PassengerTests, GetTotalWait) {
	EXPECT_EQ(passenger->GetTotalWait(), 0);
	passenger->Update();
	EXPECT_EQ(passenger->GetTotalWait(), 1);
	passenger->GetOnBus();
	EXPECT_EQ(passenger->GetTotalWait(), 2);
}

TEST_F(PassengerTests, GetOnBus) {
	EXPECT_EQ(passenger->GetTotalWait(), 0);
	passenger->GetOnBus();
	EXPECT_EQ(passenger->GetTotalWait(), 1);
	passenger->GetOnBus();
	EXPECT_EQ(passenger->GetTotalWait(), 1);
}
