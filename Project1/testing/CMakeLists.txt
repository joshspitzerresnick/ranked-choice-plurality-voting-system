cmake_minimum_required(VERSION 2.6)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Link runTests with waht we want to test and the GTest and pthread libraries
add_executable(runTests testmain.cc ballot_UT.cc candidate_UT.cc voting_info_UT.cc STVElectionRecord_UT.cc) 
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)
