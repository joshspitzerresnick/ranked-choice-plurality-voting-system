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

bool BallotShuffleOff = false;

void UserInterface(int *numSeats, int *choice);
void DisplayHelp();

int main(int argc, char** argv) {
  int choice = 5;
  int numSeats;
  STVElection* stvElection;
  PluralityElection* pluralityElection;
  BallotFileProcessor* ballotFileProcessor;
  VotingInfo* votingInfo;
  char msg[200];
  Logger::GetLogger();
  LOGGER->Log("----------------------------------Start A New Election----------------------------------------------------");
  // Check command line argument
  if (argc >= 2 && strcmp(argv[1], "-t") == 0) {
    BallotShuffleOff = true;  // Turn off ballot shuffle if '-t' is detected    
    LOGGER->Log("Command line argument received: turn off ballot shuffle.");
  }

  UserInterface(&numSeats, &choice);
  std::string ballot_files;
  std::cout << "enter the name of the ballot file:" << std::flush;
  std::cin >> ballot_files;
  snprintf(msg, sizeof(msg), "User entered ballot file: %s", ballot_files.c_str());
  LOGGER->Log(msg);

  votingInfo = new VotingInfo(choice, numSeats);

  ballotFileProcessor = new BallotFileProcessor(ballot_files);
  ballotFileProcessor->ProcessFiles(votingInfo);

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
      stvElection->RunElection();
      break;
    default:
      exit(1);  // error, this should never happen
  }
}

void UserInterface(int *numSeats, int *choice)
{
  std::string errMsg = "Invalid choice. Please enter 0, 1 or 2.";
  char c = 0;  // char var to hold user input for y/n
  bool numSeatsValid = false;  // for input checking
  int msgSize = 200, n;
  char msg[msgSize];

  while (*choice != 0 && *choice != 1) {
    std::cout << "-----------------Voting System Main Menu-----------------------\n" << std::flush;
    std::cout << "Select election type, choose 2. Help if instruction is needed: \n" << std::flush;
    std::cout << "0: Plurality\n" << std::flush;
    std::cout << "1: STV\n" << std::flush;
    std::cout << "2: Help\n" << std::flush;
    std::cout << "Selection: ";
    std::cin >> *choice;
    if (std::cin.fail()) {
    std::cout << errMsg << std::endl;
    std::cin.clear();
    cin.ignore(10000, '\n');
    *choice = 5;
    } else if (*choice < 0 || *choice > 2) {
      std::cout << errMsg << std::endl;
    } else if (*choice == 2) {
      DisplayHelp();
    }
  }
  n = snprintf(msg, msgSize, "User choose election type option: %d", *choice);
  Logger::GetLogger()->Log(msg);
  while (!numSeatsValid) {
    std::cout << "Enter number of seats: ";
    std::cin >> *numSeats;
    // Input checking
    if (std::cin.fail() || *numSeats < 1 || *numSeats > 99) {
      std::cout << "Invalid input. Please enter a number between 1 and 99." << std::endl;
      std::cin.clear();
      cin.ignore(10000, '\n');
      *numSeats = -1;
    } else {
      while (true) {
        std::cout << "Number of seats entered is " << *numSeats << std::endl;
        std::cout << "Is this number is correct? (y/n): ";
        std::cin >> c;
        if (std::cin.fail()) {
          std::cout << "Invalid input. Please enter y or n." << std::endl;
          std::cin.clear();
          cin.ignore(1, '\n');
          c = 0;
        } else if (c == 'y') {
          numSeatsValid = true;
          n = snprintf(msg, msgSize, "User enter number of seats: %d", *numSeats);
          LOGGER->Log(msg);
          break;
        } else if (c == 'n') {
          break;
        } else {
          std::cout << "Invalid input. Please enter y or n." << std::endl;
        }
      }
    }
  }
}

void DisplayHelp() {
	std::cout << "---------------Voting System Help Menu------------------\n"         << std::flush;
    std::cout << "* Voting System is ...\n"                                         << std::flush;
    std::cout << "(C) 2020 Archer, Baker, Kluegel, Spitzer-Resnick \n\n"            << std::flush;
    std::cout <<  "How to get started: \n"                                          << std::flush;
    std::cout <<  "1. Open your command line terminal on your Linux system \n"      << std::flush;
    std::cout <<  "2. Type  ./VotingSystem  and press enter \n\n"                   << std::flush;
    std::cout <<  "To calibrate the voting system:\n"                               << std::flush;
    std::cout <<   "1. Contact your IT department to enter the appropriate commands\n\n"  << std::flush;
    std::cout <<   "How to run an election:\n"                                      << std::flush;
    std::cout <<   "1. In the input screen:\n"                                      << std::flush;
    std::cout <<   "     a. enter election type, 0 = plurality 1 = stv \n"    << std::flush;
    std::cout <<   "     b. enter number of seats \n"                         << std::flush;
    std::cout <<   "     c. enter name of ballot file \n"                         << std::flush;
    std::cout <<   "     d. press enter to run election \n"                         << std::flush;
    std::cout <<   "2. Wait momentarily for all computations to have finished \n"                    << std::flush;
    std::cout <<   "3. When all computations have finished, a summary of the results with appropriate\n"    << std::flush;
    std::cout <<   "statistics for the type of election you have chose will appear on the screen \n"                   << std::flush;
    std::cout <<   "4. Close the program \n"                   << std::flush;
    std::cout <<   "5. To run a new election, start the system again and repeat the above steps\n"  << std::flush;

}
