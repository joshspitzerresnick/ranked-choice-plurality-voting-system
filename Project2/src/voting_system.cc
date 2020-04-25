/**
 * @file voting_system.cc
 *
 * @copyright 2020 5801 Team3, All rights reserved.
 */
#include "stv_election.h"
#include "plurality_election.h"
#include "ballot_file_processor.h"
#include "logger.h"
#include <cstring>
#include <iostream>
#include <stdio.h>
#include <limits.h>  // INT_MAX for ignoring bad input
#include <assert.h>
#include <ctime>

bool BallotShuffleOff = false;
char InvalidBallotFileName[500];
char LogFileName[500];

void UserInterface(int *numSeats, int *choice);
void DisplayHelp();
std::string GetTimeStamp();

int main(int argc, char** argv) {
  int choice = 5;
  int numSeats, numBallots;
  std::string TimeStamp;
  STVElection* stvElection;
  PluralityElection* pluralityElection;
  BallotFileProcessor* ballotFileProcessor;
  VotingInfo* votingInfo;
  std::list<string> files;
  char msg[200];
  TimeStamp = GetTimeStamp();
  snprintf(InvalidBallotFileName, 500, "InvalidBallotFile_%s.txt",TimeStamp.c_str());
  snprintf(LogFileName, 500, "AuditFile_%s.txt",TimeStamp.c_str());
  std::cout << LogFileName << std::endl;
  Logger::GetLogger();  
  LOGGER->Log("---------------------------------------------------------Start A New Election---------------------------------------------------------");  
  // Check command line argument
  if (argc >= 2 && strcmp(argv[1], "-t") == 0) {
    BallotShuffleOff = true;  // Turn off ballot shuffle if '-t' is detected    
    LOGGER->Log("Command line argument received: turn off ballot shuffle.");
  }

  UserInterface(&numSeats, &choice);
  votingInfo = new VotingInfo(choice, numSeats);

  ballotFileProcessor = new BallotFileProcessor();
  files = ballotFileProcessor->GetFiles(ballotFileProcessor->GetUserInput());
  numBallots = ballotFileProcessor->ProcessFiles(files, votingInfo);
  // delete previous BallotFileProcessor object after use, not pointer
  delete ballotFileProcessor;
  if (numBallots<1) {
    throw "No ballots are processed";
  }

  switch (choice) {
    case 0:
      snprintf(msg, sizeof(msg), "Start running plurality election...");
      LOGGER->Log(msg);
      pluralityElection = new PluralityElection();
      pluralityElection->RunElection(votingInfo);
      break;
    case 1 :
      snprintf(msg, sizeof(msg), "Start running stv election...");
      LOGGER->Log(msg);
      stvElection = new STVElection(votingInfo);
      stvElection->RunElection(votingInfo);
      break;
    default:
      exit(1);  // error, this should never happen
  }
}

void UserInterface(int *numSeats, int *choice) {
  std::string errMsg = "Invalid choice. Please enter 0, 1 or 2.";
  char c = 0;  // char var to hold user input for y/n
  bool numSeatsValid = false;  // for input checking
  char msg[200];

  while (*choice != 0 && *choice != 1) {
    std::cout << "-----------------Voting System Main Menu-----------------------\n" << std::flush;
    std::cout << "Select election type, choose \"2: Help\" if instruction is needed: \n" << std::flush;
    std::cout << "0: Plurality\n" << std::flush;
    std::cout << "1: STV\n" << std::flush;
    std::cout << "2: Help\n" << std::flush;
    std::cout << "Selection: ";
    std::cin >> *choice;
    if (std::cin.fail()) {
    std::cout << errMsg << std::endl;
    std::cin.clear();
    cin.ignore(INT_MAX, '\n');
    *choice = 5;
    } else if (*choice < 0 || *choice > 2) {
      std::cout << errMsg << std::endl;
    } else if (*choice == 2) {
      DisplayHelp();
    }
  }

  snprintf(msg, sizeof(msg), "User choose election type option: %d", *choice);
  Logger::GetLogger()->Log(msg);
  while (!numSeatsValid) {
    std::cout << "Enter number of seats (1-99): ";
    std::cin >> *numSeats;
    // Input checking
    if (std::cin.fail() || *numSeats < 1 || *numSeats > 99) {
      std::cout << "Invalid input. Please enter a number between 1 and 99." << std::endl;
      std::cin.clear();
      cin.ignore(INT_MAX, '\n');
      *numSeats = -1;
    } else {
      while (true) {
        std::cout << "Number of seats entered is " << *numSeats << std::endl;
        std::cout << "Is this number correct? (y/n): ";
        std::cin >> c;
        if (std::cin.fail()) {
          std::cout << "Invalid input. Please enter y or n." << std::endl;
          std::cin.clear();
          cin.ignore(INT_MAX, '\n');
          c = 0;
        } else if (c == 'y') {
          numSeatsValid = true;
          snprintf(msg, sizeof(msg), "User enter number of seats: %d", *numSeats);
          LOGGER->Log(msg);
          break;
        } else if (c == 'n') {
          break;
        } else {
          std::cout << "Invalid input. Please enter y or n." << std::endl;
          std::cin.clear();
          cin.ignore(10000, '\n');
          c = 0;
        }
      }
    }
  }
}

void DisplayHelp() {
	std::cout << "--------------------Voting System Help Menu-------------------------------------\n" << std::flush;
  // std::cout << "* Voting System is ...\n" << std::flush;
  std::cout << "(C) 2020 Archer, Baker, Kluegel, Spitzer-Resnick\n\n" << std::flush;
  std::cout << "How to get started:\n" << std::flush;
  std::cout << "1. Open your command line terminal on your Linux system\n" << std::flush;
  std::cout << "2. Type ./VotingSystem and press enter\n\n" << std::flush;
  std::cout << "To calibrate the voting system:\n" << std::flush;
  std::cout << "1. Contact your IT department to enter the appropriate commands\n\n" << std::flush;
  std::cout << "How to run an election:\n" << std::flush;
  std::cout << "1. In the input screen:\n" << std::flush;
  std::cout << "   a. enter election type: 0 = plurality, 1 = STV\n" << std::flush;
  std::cout << "   b. enter number of seats\n" << std::flush;
  std::cout << "   c. enter name(s) of ballot file(s), one at a time\n" << std::flush;
  std::cout << "   d. press enter to run election\n" << std::flush;
  std::cout << "2. Wait momentarily for all computations to finish\n" << std::flush;
  std::cout << "3. When all computations have finished, a summary of the results with appropriate\n" << std::flush;
  std::cout << "   statistics for the type of election you have chosen will appear on the screen\n" << std::flush;
  std::cout << "4. Close the program\n" << std::flush;
  std::cout << "5. To run a new election, start the system again and repeat the above steps\n" << std::flush;
}

std::string GetTimeStamp(){
  char timeStamp[200];
  time_t now = time(0);
  std::tm *ltm = localtime(&now);
  snprintf(timeStamp, sizeof(timeStamp), "%d.%02d.%02d.%02d%02d%02d"
          , 1900 + ltm->tm_year, ltm->tm_mon, ltm->tm_mday, ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
  return timeStamp;
}
