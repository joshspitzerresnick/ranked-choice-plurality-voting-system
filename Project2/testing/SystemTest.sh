#! /bin/bash

# This file is a system test for the VotingSystem.

echo "----------------------------------------------------" >> system_test_report.txt
echo "Starting system tests" >> system_test_report.txt
echo "----------------------------------------------------" >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Execute help display in VotingSystem..." >> system_test_report.txt
printf "2\n1\n1\ny\n../testing/plurality_ballots.csv" | ../src/./VotingSystem >> system_test_report.txt
echo "Test Completed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Execute Plurality election in VotingSystem..." >> system_test_report.txt
echo "Use plurality_ballots.csv with 1 seat" >> system_test_report.txt
printf "0\n1\ny\n../testing/plurality_ballots.csv" | ../src/./VotingSystem >> system_test_report.txt
echo "Test Completed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Execute STV election in VotingSystem..." >> system_test_report.txt
echo "Use stv_ballots.csv with 1 seat" >> system_test_report.txt
printf "1\n1\ny\n../testing/stv_ballots.csv" | ../src/./VotingSystem >> system_test_report.txt
echo "Test Completed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Try Invalid entries..." >> system_test_report.txt
printf "3\n-1\na\n+\n1\n1\ny\n../testing/plurality_ballots.csv" | ../src/./VotingSystem
echo "Test Passed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Try Invalid number of seats..." >> system_test_report.txt
printf "0\n-1\na\n1000000\n1\ny\n../testing/plurality_ballots.csv" | ../src/./VotingSystem
echo "Test Passed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Try Invalid answer for is this correct..." >> system_test_report.txt
printf "0\n1\n2\na\n+\ny\n../testing/plurality_ballots.csv" | ../src/./VotingSystem
echo "Test Passed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Try no for is this correct..." >> system_test_report.txt
printf "0\n1\nn\n1\ny\n../testing/plurality_ballots.csv" | ../src/./VotingSystem
echo "Test Passed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Try invalid ballot file name..." >> system_test_report.txt
printf "0\n1\ny\n../testing/this_doesnt_exists.csv" | ../src/./VotingSystem
echo "Test Completed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Execute Plurality election in VotingSystem..." >> system_test_report.txt
echo "Use plurality_ballots.csv with seats greater than candidate count" >> system_test_report.txt
printf "0\n10\ny\n../testing/plurality_ballots.csv" | ../src/./VotingSystem >> system_test_report.txt
echo "Test Completed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Execute STV election in VotingSystem..." >> system_test_report.txt
echo "Use stv_ballots.csv with seats greater than candidate count" >> system_test_report.txt
printf "1\n10\ny\n../testing/stv_ballots.csv" | ../src/./VotingSystem >> system_test_report.txt
echo "Test Completed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Execute STV election in VotingSystem..." >> system_test_report.txt
echo "Use invalid_ballots.csv with 2 seats" >> system_test_report.txt
printf "1\n2\ny\n../testing/invalid_ballots.csv" | ../src/./VotingSystem >> system_test_report.txt
echo "Test Completed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Execute STV election in VotingSystem..." >> system_test_report.txt
echo "Use stv_ballots.csv with nominal number of seats" >> system_test_report.txt
printf "1\n3\ny\n../testing/stv_ballots.csv" | ../src/./VotingSystem >> system_test_report.txt
echo "Test Completed." >> system_test_report.txt
echo " " >> system_test_report.txt

echo "Execute STV election in VotingSystem..." >> system_test_report.txt
echo "Use stv_ballots.csv with nominal number of seats and turnoff ballot shuffle" >> system_test_report.txt
printf "1\n3\ny\n../testing/stv_ballots.csv" | ../src/./VotingSystem -t >> system_test_report.txt
echo " "
echo "The above election output should match the following output:" >> system_test_report.txt
echo " "
printf "1\n3\ny\n../testing/stv_ballots.csv" | ../src/./VotingSystem -t >> system_test_report.txt
echo " "
echo "The following election output should be different than above:" >> system_test_report.txt
printf "1\n3\ny\n../testing/stv_ballots.csv" | ../src/./VotingSystem >> system_test_report.txt
echo "Test Completed." >> system_test_report.txt
echo " " >> system_test_report.txt

# Add additional tests using larger ballot files....
