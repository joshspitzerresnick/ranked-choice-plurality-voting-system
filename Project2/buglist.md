# CSci 5801 Project1 - Team3 - VotingSystem - Bug List

Num | Description of bug | Location of bug | Steps to recreate bug/test case | Root cause analysis
--- | --- | --- | --- | ---
1 | STV election hangs | stv_election.cc | Start VotingSystem, select STV election | Many dependencies
2 | Logger does not work | logger.cc | Run VotingSystem, audit_file.txt is created but doesn’t get printed to
3 | STV election assigning order of receiving the first ballot to candidate is not implemented | stv_election.cc, stv_election_record.cc | Developer realized it | Not enough time to debug
4 | UserInterface does not read in multiple files | voting_system.cc | Run VotingSystem, type two csv files when prompted, only first will be used | Lack of time to debug / implement loop
5 | Readme out of date for building with CMake when unit test files moved from testing to src | Readme.md | View Readme.md under building with CMake | Lack of time to update
