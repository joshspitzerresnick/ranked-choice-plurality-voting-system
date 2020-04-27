// Copyright 2020 CSCI5801-Team3
// tests.cpp
#include <gtest/gtest.h>

bool BallotShuffleOff = true;
char InvalidBallotFileName[500];
char LogFileName[500];

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
