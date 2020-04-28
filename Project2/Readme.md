# CSci 5801 Project2 - Team3

Project2 - Agile Methodology - VotingSystem

- Bryan Baker - bake1358@umn.edu
- Hailin Archer - deak0007@umn.edu
- Josh Spitzer-Resnick - spitz123@umn.edu
- Colin Kluegel - klue0037@umn.edu

## How to compile the system

### Build the Voting System and test files

To build both the voting system and the unit test file, in the project directory, type
```
Project2 $ make
```
This will create an executable file called `VotingSystem` in the `src` directory.  Run the project by typing
```
Project2/src $ ./VotingSystem
```
The Voting System can be executed without the ballot file selection gui (all command prompt based) by typing
```
Project2/src $ ./VotingSystem -m
```
To run the Voting System with ballot shuffling turned off type
```
Project2/src $ ./VotingSystem -t
```
The above command line arguments can be combined with
```
Project2/src $ ./VotingSystem -t -m
```
An executable file called `runTests` will also be created in the `testing` directory.  Run these unit tests by typing
```
Project2/testing $ ./runTests
```
There is also a system test in a bash script called `SystemTest.sh`.  Run this test by typing
```
Project2/testing $ ./SystemTest.sh
```
This system test will output data for review in the file `system_test_report.txt`.

In order to clean the `src` and `testing` directory of object files and the executables, type
```
Project2 $ make clean
```
To clean up the file system and remove the log files Voting System creates along with the system test reports, type
```
Project2 $ make log-clean
```
