cmake_minimum_required(VERSION 2.6)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(Sources
    ../src/plurality_election_record.cc
    ../src/logger.cc
    ../src/ballot_file_processor.cc
    ../src/ballot.cc
    ../src/candidate.cc
    ../src/voting_info.cc
    # ../src/election_record.cc
    # ../src/election.cc
    ../src/plurality_election_record.cc
    ../src/plurality_election.cc
    # ../src/stv_election_record.cc
    # ../src/stv_election.cc
)

# Link runTests with waht we want to test and the GTest and pthread libraries
add_executable(runTests 
    ${Sources} 
    ../src/testmain.cc 
    ../src/ballot_UT.cc 
    ../src/candidate_UT.cc 
    ../src/voting_info_UT.cc 
    ../src/ballot_file_processor_UT.cc 
    ../src/plurality_election_record_UT.cc
    ../src/plurality_election_UT.cc
    # ../src/STVElectionRecord_UT.cc
    # ../src/STVElection_UT.cc
    ../src/logger_UT.cc) 
    
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)
