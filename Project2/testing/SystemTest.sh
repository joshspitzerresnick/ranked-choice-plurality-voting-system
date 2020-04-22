#! /bin/bash

# This file is a system test for the VotingSystem.

echo "----------------------------------------------------" >> system_test_report.txt
echo "Starting system tests" >> system_test_report.txt
echo "----------------------------------------------------" >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Execute help display in VotingSystem..." >> system_test_report.txt
printf "2\n1\n1\ny\n../testing/plurality_ballots.csv\n0" | ../src/./VotingSystem >> system_test_report.txt
echo "Test Completed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Execute Plurality election in VotingSystem..." >> system_test_report.txt
echo "Use plurality_ballots.csv with 1 seat" >> system_test_report.txt
printf "0\n1\ny\n../testing/plurality_ballots.csv\n0" | ../src/./VotingSystem >> system_test_report.txt
echo "Test Completed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Execute STV election in VotingSystem..." >> system_test_report.txt
echo "Use stv_ballots.csv with 1 seat" >> system_test_report.txt
printf "1\n1\ny\n../testing/stv_ballots.csv\n0" | ../src/./VotingSystem >> system_test_report.txt
echo "Test Completed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Try Invalid entries..." >> system_test_report.txt
printf "3\n-1\na\n+\n1\n1\ny\n../testing/plurality_ballots.csv\n0" | ../src/./VotingSystem
echo "Test Passed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Try Invalid number of seats..." >> system_test_report.txt
printf "0\n-1\na\n1000000\n1\ny\n../testing/plurality_ballots.csv\n0" | ../src/./VotingSystem
echo "Test Passed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Try Invalid answer for is this correct..." >> system_test_report.txt
printf "0\n1\n2\na\n+\ny\n../testing/plurality_ballots.csv\n0" | ../src/./VotingSystem
echo "Test Passed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Try no for is this correct..." >> system_test_report.txt
printf "0\n1\nn\n1\ny\n../testing/plurality_ballots.csv\n0" | ../src/./VotingSystem
echo "Test Passed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Try invalid ballot file name..." >> system_test_report.txt
printf "0\n1\ny\n../testing/this_doesnt_exists.csv\n0" | ../src/./VotingSystem
echo "Test Completed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Execute Plurality election in VotingSystem..." >> system_test_report.txt
echo "Use plurality_ballots.csv with seats greater than candidate count" >> system_test_report.txt
printf "0\n10\ny\n../testing/plurality_ballots.csv\n0" | ../src/./VotingSystem >> system_test_report.txt
echo "Test Completed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Execute STV election in VotingSystem..." >> system_test_report.txt
echo "Use stv_ballots.csv with seats greater than candidate count" >> system_test_report.txt
printf "1\n10\ny\n../testing/stv_ballots.csv\n0" | ../src/./VotingSystem >> system_test_report.txt
echo "Test Completed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Execute STV election in VotingSystem..." >> system_test_report.txt
echo "Use invalid_ballots.csv with 2 seats" >> system_test_report.txt
printf "1\n2\ny\n../testing/invalid_ballots.csv\n0" | ../src/./VotingSystem >> system_test_report.txt
echo "Test Completed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Execute STV election in VotingSystem..." >> system_test_report.txt
echo "Use stv_ballots.csv with nominal number of seats" >> system_test_report.txt
printf "1\n3\ny\n../testing/stv_ballots.csv\n0" | ../src/./VotingSystem >> system_test_report.txt
echo "Test Completed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Execute STV election in VotingSystem..." >> system_test_report.txt
echo "Use stv_ballots.csv with nominal number of seats and turnoff ballot shuffle" >> system_test_report.txt
printf "1\n3\ny\n../testing/stv_ballots.csv\n0" | ../src/./VotingSystem -t >> system_test_report.txt
echo " "
echo "The above election output should match the following output:" >> system_test_report.txt
echo " "
printf "1\n3\ny\n../testing/stv_ballots.csv\n0" | ../src/./VotingSystem -t >> system_test_report.txt
echo " "
echo "The following election output should be different than above:" >> system_test_report.txt
printf "1\n3\ny\n../testing/stv_ballots.csv\n0" | ../src/./VotingSystem >> system_test_report.txt
echo "Test Completed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Execute Plurality election in VotingSystem..." >> system_test_report.txt
echo "Use plurality_20ballots_5candidates.csv with 1 seat" >> system_test_report.txt
printf "0\n1\ny\n../testing/plurality_20ballots_5candidates.csv\n0" | ../src/./VotingSystem >> system_test_report.txt
echo "Test Completed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Execute Plurality election in VotingSystem..." >> system_test_report.txt
echo "Use plurality_110ballots_5candidates.csv with 1 seat" >> system_test_report.txt
printf "0\n1\ny\n../testing/plurality_110ballots_5candidates.csv\n0" | ../src/./VotingSystem >> system_test_report.txt
echo "Test Completed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Execute Plurality election in VotingSystem..." >> system_test_report.txt
echo "Use plurality_120ballots_8candidates.csv with 1 seat" >> system_test_report.txt
printf "0\n1\ny\n../testing/plurality_120ballots_8candidates.csv\n0" | ../src/./VotingSystem >> system_test_report.txt
echo "Test Completed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Execute Plurality election in VotingSystem..." >> system_test_report.txt
echo "Use plurality_500ballots_5candidates.csv with 1 seat" >> system_test_report.txt
printf "0\n1\ny\n../testing/plurality_500ballots_5candidates.csv\n0" | ../src/./VotingSystem >> system_test_report.txt
echo "Test Completed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Execute Plurality election in VotingSystem..." >> system_test_report.txt
echo "Use plurality_1000ballots_10candidates.csv with 1 seat" >> system_test_report.txt
printf "0\n1\ny\n../testing/plurality_1000ballots_10candidates.csv\n0" | ../src/./VotingSystem >> system_test_report.txt
echo "Test Completed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Execute Plurality election in VotingSystem..." >> system_test_report.txt
echo "Use plurality_5000ballots_8candidates.csv with 1 seat" >> system_test_report.txt
printf "0\n1\ny\n../testing/plurality_5000ballots_8candidates.csv\n0" | ../src/./VotingSystem >> system_test_report.txt
echo "Test Completed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Execute Plurality election in VotingSystem..." >> system_test_report.txt
echo "Use plurality_10000ballots_10candidates.csv with 1 seat" >> system_test_report.txt
printf "0\n1\ny\n../testing/plurality_10000ballots_10candidates.csv\n0" | ../src/./VotingSystem >> system_test_report.txt
echo "Test Completed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Execute STV election in VotingSystem..." >> system_test_report.txt
echo "Use stv_20ballots_5candidates_0pctBadBallots.csv with nominal number of seats" >> system_test_report.txt
printf "1\n3\ny\n../testing/stv_20ballots_5candidates_0pctBadBallots.csv\n0" | ../src/./VotingSystem >> system_test_report.txt
echo "Test Completed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Execute STV election in VotingSystem..." >> system_test_report.txt
echo "Use stv_20ballots_5candidates_10pctBadBallots.csv with nominal number of seats" >> system_test_report.txt
printf "1\n3\ny\n../testing/stv_20ballots_5candidates_10pctBadBallots.csv\n0" | ../src/./VotingSystem >> system_test_report.txt
echo "Test Completed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Execute STV election in VotingSystem..." >> system_test_report.txt
echo "Use stv_100ballots_5candidates_0pctBadBallots.csv with nominal number of seats" >> system_test_report.txt
printf "1\n3\ny\n../testing/stv_100ballots_5candidates_0pctBadBallots.csv\n0" | ../src/./VotingSystem >> system_test_report.txt
echo "Test Completed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Execute STV election in VotingSystem..." >> system_test_report.txt
echo "Use stv_120ballots_8candidates_20pctBadBallots.csv with nominal number of seats" >> system_test_report.txt
printf "1\n3\ny\n../testing/stv_120ballots_8candidates_20pctBadBallots.csv\n0" | ../src/./VotingSystem >> system_test_report.txt
echo "Test Completed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Execute STV election in VotingSystem..." >> system_test_report.txt
echo "Use stv_500ballots_5candidates_0pctBadBallots.csv with nominal number of seats" >> system_test_report.txt
printf "1\n3\ny\n../testing/stv_500ballots_5candidates_0pctBadBallots.csv\n0" | ../src/./VotingSystem >> system_test_report.txt
echo "Test Completed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Execute STV election in VotingSystem..." >> system_test_report.txt
echo "Use stv_500ballots_5candidates_10pctBadBallots.csv with nominal number of seats" >> system_test_report.txt
printf "1\n3\ny\n../testing/stv_500ballots_5candidates_0pctBadBallots.csv\n0" | ../src/./VotingSystem >> system_test_report.txt
echo "Test Completed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Execute STV election in VotingSystem..." >> system_test_report.txt
echo "Use stv_1000ballots_10candidates_0pctBadBallots.csv with nominal number of seats" >> system_test_report.txt
printf "1\n3\ny\n../testing/stv_1000ballots_10candidates_0pctBadBallots.csv\n0" | ../src/./VotingSystem >> system_test_report.txt
echo "Test Completed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Execute STV election in VotingSystem..." >> system_test_report.txt
echo "Use stv_1000ballots_10candidates_10pctBadBallots.csv with nominal number of seats" >> system_test_report.txt
printf "1\n3\ny\n../testing/stv_1000ballots_10candidates_10pctBadBallots.csv\n0" | ../src/./VotingSystem >> system_test_report.txt
echo "Test Completed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Execute STV election in VotingSystem..." >> system_test_report.txt
echo "Use stv_5000ballots_8candidates_0pctBadBallots.csv with nominal number of seats" >> system_test_report.txt
printf "1\n3\ny\n../testing/stv_5000ballots_8candidates_0pctBadBallots.csv\n0" | ../src/./VotingSystem >> system_test_report.txt
echo "Test Completed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Execute STV election in VotingSystem..." >> system_test_report.txt
echo "Use stv_5000ballots_8candidates_20pctBadBallots.csv with nominal number of seats" >> system_test_report.txt
printf "1\n3\ny\n../testing/stv_5000ballots_8candidates_20pctBadBallots.csv\n0" | ../src/./VotingSystem >> system_test_report.txt
echo "Test Completed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Execute STV election in VotingSystem..." >> system_test_report.txt
echo "Use stv_10000ballots_10candidates_0pctBadBallots.csv with nominal number of seats" >> system_test_report.txt
printf "1\n3\ny\n../testing/stv_10000ballots_10candidates_0pctBadBallots.csv\n0" | ../src/./VotingSystem >> system_test_report.txt
echo "Test Completed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Execute STV election in VotingSystem..." >> system_test_report.txt
echo "Use stv_10000ballots_10candidates_20pctBadBallots.csv with nominal number of seats" >> system_test_report.txt
printf "1\n3\ny\n../testing/stv_10000ballots_10candidates_20pctBadBallots.csv\n0" | ../src/./VotingSystem >> system_test_report.txt
echo "Test Completed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Execute STV election in VotingSystem..." >> system_test_report.txt
echo "Use stv_1000ballots_10candidates_10pctBadBallots.csv with nominal number of seats and turnoff ballot shuffle" >> system_test_report.txt
printf "1\n3\ny\n../testing/stv_1000ballots_10candidates_10pctBadBallots.csv\n0" | ../src/./VotingSystem -t >> system_test_report.txt
echo " "
echo "The above election output should match the following output:" >> system_test_report.txt
echo " "
printf "1\n3\ny\n../testing/stv_1000ballots_10candidates_10pctBadBallots.csv\n0" | ../src/./VotingSystem -t >> system_test_report.txt
echo " "
echo "The following election output should be different than above:" >> system_test_report.txt
printf "1\n3\ny\n../testing/stv_1000ballots_10candidates_10pctBadBallots.csv\n0" | ../src/./VotingSystem >> system_test_report.txt
echo "Test Completed." >> system_test_report.txt
echo " " >> system_test_report.txt
