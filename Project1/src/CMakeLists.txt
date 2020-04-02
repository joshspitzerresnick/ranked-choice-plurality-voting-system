cmake_minimum_required(VERSION 2.6)

set(Sources
    plurality_election_record.cc
    logger.cc
    ballot_file_processor.cc
    ballot.cc
    candidate.cc
    voting_info.cc
    # ../src/election_record.cc
    # ../src/election.cc
    plurality_election_record.cc
    plurality_election.cc
    stv_election_record.cc
    stv_election.cc
)

add_executable(VotingSystem 
    ${Sources} 
    voting_system.cc) 
    
target_link_libraries(VotingSystem pthread)
