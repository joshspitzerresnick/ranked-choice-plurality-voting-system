#! /bin/bash

# This file is a system test for the VotingSystem.

echo "----------------------------------------------------" >> system_test_report.txt
echo "Starting system tests" >> system_test_report.txt
echo "----------------------------------------------------" >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Execute help display in VotingSystem..." >> system_test_report.txt
printf "2\n0\n1\ny\n1\n../testing/plurality_ballots.csv\nq" | ../src/./VotingSystem -m >> system_test_report.txt
echo "Test Completed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Execute Plurality election in VotingSystem..." >> system_test_report.txt
echo "Use plurality_ballots.csv with 1 seat" >> system_test_report.txt
printf "0\n1\ny\n1\n../testing/plurality_ballots.csv\nq" | ../src/./VotingSystem -m >> system_test_report.txt
echo "Test Completed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Execute STV election in VotingSystem..." >> system_test_report.txt
echo "Use stv_ballots.csv with 1 seat" >> system_test_report.txt
printf "1\n1\ny\n1\n../testing/stv_ballots.csv\nq" | ../src/./VotingSystem -m >> system_test_report.txt
echo "Test Completed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Try Invalid entries..." >> system_test_report.txt
printf "3\n-1\na\n+\n0\n1\ny\n1\n../testing/plurality_ballots.csv\nq" | ../src/./VotingSystem -m 
echo "Test Passed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Try Invalid number of seats..." >> system_test_report.txt
printf "0\n-1\na\n1000000\n1\ny\n1\n../testing/plurality_ballots.csv\nq" | ../src/./VotingSystem -m
echo "Test Passed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Try Invalid answer for is this correct..." >> system_test_report.txt
printf "0\n1\n2\na\n+\ny\n1\n../testing/plurality_ballots.csv\nq" | ../src/./VotingSystem -m
echo "Test Passed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Try no for is this correct..." >> system_test_report.txt
printf "0\n1\nn\n1\ny\n1\n../testing/plurality_ballots.csv\nq" | ../src/./VotingSystem -m
echo "Test Passed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Try invalid ballot file name..." >> system_test_report.txt
printf "0\n1\ny\n1\n../testing/this_doesnt_exists.csv\nq" | ../src/./VotingSystem -m >> system_test_report.txt
echo "Test Completed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Execute Plurality election in VotingSystem..." >> system_test_report.txt
echo "Use plurality_ballots.csv with seats greater than candidate count" >> system_test_report.txt
printf "0\n10\ny\n1\n../testing/plurality_ballots.csv\nq" | ../src/./VotingSystem -m >> system_test_report.txt
echo "Test Completed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Execute STV election in VotingSystem..." >> system_test_report.txt
echo "Use stv_ballots.csv with seats greater than candidate count" >> system_test_report.txt
printf "1\n10\ny\n1\n../testing/stv_ballots.csv\nq" | ../src/./VotingSystem -m >> system_test_report.txt
echo "Test Completed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Execute STV election in VotingSystem..." >> system_test_report.txt
echo "Use invalid_ballots.csv with 2 seats" >> system_test_report.txt
printf "1\n2\ny\n1\n../testing/invalid_ballots.csv\nq" | ../src/./VotingSystem -m >> system_test_report.txt
echo "Test Completed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Execute plurality election in VotingSystem..." >> system_test_report.txt
echo "Use many ballots, basic names with 1 seat" >> system_test_report.txt
printf "0\n1\ny\n1\n../testing/plurality_10000ballots_10candidates.csv\nq" | ../src/./VotingSystem -m >> system_test_report.txt
echo "Test Completed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Execute plurality election in VotingSystem..." >> system_test_report.txt
echo "Use many ballots, named candidates with 1 seat" >> system_test_report.txt
printf "0\n1\ny\n1\n../testing/pluralityLCandidateNames_10000ballots_10candidates.csv\nq" | ../src/./VotingSystem -m >> system_test_report.txt
echo "Test Completed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Execute stv election in Voting System..." >> system_test_report.txt
echo "Use many ballots, basic names, no invalid ballots with nominal number of seats" >> system_test_report.txt
printf "1\n3\ny\n1\n../testing/stv_10000ballots_10candidates_0pctBadBallots.csv\nq" | ../src/./VotingSystem -m >> system_test_report.txt
echo "Test Completed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Execute stv election in Voting System..." >> system_test_report.txt
echo "Use many ballots, basic names, with invalid ballots and nominal number of seats" >> system_test_report.txt
printf "1\n3\ny\n1\n../testing/stv_10000ballots_10candidates_20pctBadBallots.csv\nq" | ../src/./VotingSystem -m >> system_test_report.txt
echo "Test Completed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Execute stv election in Voting System..." >> system_test_report.txt
echo "Use many ballots, named candidates, no invalid ballots and nominal number of seats" >> system_test_report.txt
printf "1\n3\ny\n1\n../testing/stvLCanNames_10000ballots_10candidates_0pctBadBallots.csv\nq" | ../src/./VotingSystem -m >> system_test_report.txt
echo "Test Completed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Execute stv election in Voting System..." >> system_test_report.txt
echo "Use many ballots, named candidates, with invalid ballots and nominal number of seats" >> system_test_report.txt
printf "1\n3\ny\n1\n../testing/stvLCanNames_10000ballots_10candidates_20pctBadBallots.csv\nq" | ../src/./VotingSystem -m >> system_test_report.txt
echo "Test Completed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Execute plurality election in Voting System..." >> system_test_report.txt
echo "Multi-file election" >> system_test_report.txt
printf "0\n1\ny\n1\n../testing/plurality_110ballots_5candidates.csv\n../testing/plurality_500ballots_5candidates.csv\nq" | ../src/./VotingSystem -m >> system_test_report.txt
echo "Test Completed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Execute stv election in Voting System..." >> system_test_report.txt
echo "Multi-file election" >> system_test_report.txt
printf "1\n3\ny\n1\n../testing/stv_100ballots_5candidates_0pctBadBallots.csv\n../testing/stv_500ballots_5candidates_10pctBadBallots.csv\nq" | ../src/./VotingSystem -m >> system_test_report.txt
echo "Test Completed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Execute plurality election in Voting System..." >> system_test_report.txt
echo "Multi-file election - differing number of candidates" >> system_test_report.txt
printf "0\n1\ny\n1\n../testing/plurality_110ballots_5candidates.csv\n../testing/plurality_120ballots_8candidates.csv\nq" | ../src/./VotingSystem -m >> system_test_report.txt
echo "Test Completed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Execute stv election in Voting System..." >> system_test_report.txt
echo "Multi-file election - differing number of candidates" >> system_test_report.txt
printf "1\n3\ny\n1\n../testing/stv_100ballots_5candidates_0pctBadBallots.csv\n../testing/stv_120ballots_8candidates_20pctBadBallots.csv\nq" | ../src/./VotingSystem -m >> system_test_report.txt
echo "Test Completed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Execute STV election in VotingSystem..." >> system_test_report.txt
echo "Use stv_1000ballots_10candidates_10pctBadBallots.csv with nominal number of seats and turnoff ballot shuffle" >> system_test_report.txt
printf "1\n3\ny\n1\n../testing/stv_1000ballots_10candidates_10pctBadBallots.csv\nq" | ../src/./VotingSystem -t -m >> system_test_report.txt
echo " "
echo "The above election output should match the following output:" >> system_test_report.txt
echo " "
printf "1\n3\ny\n1\n../testing/stv_1000ballots_10candidates_10pctBadBallots.csv\nq" | ../src/./VotingSystem -t -m >> system_test_report.txt
echo " "
echo "The following election output should be different than above:" >> system_test_report.txt
printf "1\n3\ny\n1\n../testing/stv_1000ballots_10candidates_10pctBadBallots.csv\nq" | ../src/./VotingSystem -m >> system_test_report.txt
echo "Test Completed." >> system_test_report.txt
echo " " >> system_test_report.txt
