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
#include <QApplication>
#include <QString>
#include <QFileDialog>

bool BallotShuffleOff = false;

void UserInterface(int *numSeats, int *choice);
void get_ballots_manual(VotingInfo* voting_info);
void get_ballots_gui(VotingInfo* voting_info);
void DisplayHelp();

int main(int argc, char** argv) {

  //need to create a QApplication object to use a QWidget
  QApplication a(argc, argv);
  int choice = 5;
  int numSeats;
  bool ManuallyEnterBallots = false;
  STVElection* stvElection;
  PluralityElection* pluralityElection;
  VotingInfo* votingInfo;
  char msg[200];
  Logger::GetLogger();
  LOGGER->Log("---------------------------------------------------------Start A New Election---------------------------------------------------------");
  // Check command line argument
  if (argc >= 2 && strcmp(argv[1], "-t") == 0) {
    BallotShuffleOff = true;  // Turn off ballot shuffle if '-t' is detected    
    LOGGER->Log("Command line argument received: turn off ballot shuffle.");
  }

  if (argc >= 2 && ((strcmp(argv[1], "-m") == 0) || (strcmp(argv[2], "-m") == 0))) {
    ManuallyEnterBallots = true;  // Manually enter ballots rather than GUI select
    LOGGER->Log("Command line argument received: manually enter ballot file names.");
  }

  UserInterface(&numSeats, &choice);
  votingInfo = new VotingInfo(choice, numSeats);

  if(ManuallyEnterBallots)
  {
    get_ballots_manual(votingInfo);
  }
  else
  {
    get_ballots_gui(votingInfo);
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

void get_ballots_manual(VotingInfo* voting_info)
{
// loop to get number of ballot files & take in multiple ballot files
  int has_more_ballot_files_ = 1;  // true
  BallotFileProcessor* ballotFileProcessor;
  char msg[200];
  std::string ballot_files_;
  while(has_more_ballot_files_ != 0) {  // not false or error
    std::cout << "Enter name of ballot file:\n" << std::flush;
    std::cin >> ballot_files_;
    snprintf(msg, sizeof(msg), "User entered ballot file: %s", ballot_files_.c_str());
    Logger::GetLogger()->Log(msg);

    // input checking
    while (true) {
      std::cout << "Do you have more ballot files to input? 1: Yes, 0: No\n" << std::flush;
      std::cin >> has_more_ballot_files_;  // automatically cast to bool // letters to 0
      if (std::cin.fail() || (has_more_ballot_files_ != 1 && has_more_ballot_files_ != 0) ) {  // failed input, will continue to silently fail
        std::cout << "Invalid input. Please enter 1 for yes or 0 for no." << std::endl;
        std::cin.clear();  // return to normal operation
        cin.ignore(INT_MAX, '\n');  // remove bad input
       } else {  // 1 or 0 entered
         break;
      }
     }

    ballotFileProcessor = new BallotFileProcessor(ballot_files_);
    ballotFileProcessor->ProcessFiles(voting_info);

    // delete previous BallotFileProcessor object after use, not pointer
    delete ballotFileProcessor;
  }
}

void get_ballots_gui(VotingInfo* voting_info)
{
  char msg[200];
  BallotFileProcessor* ballotFileProcessor;
  QString filter = "csv(*.csv)";
  QStringList ballot_files = QFileDialog::getOpenFileNames(NULL, "Select ballot files","./", filter);
  QString b_file;
  std::list<std::string> ballot_files_list;
  while(!ballot_files.empty())
  {
      b_file = ballot_files.front();
      ballot_files_list.push_back(b_file.toStdString());
      ballot_files.pop_front();
      cout << "Selected Ballot File:" << b_file.toStdString() << "\n" << std::endl;
      snprintf(msg, sizeof(msg), "User entered ballot file: %s", b_file.toStdString().c_str());
      Logger::GetLogger()->Log(msg);
  }

  std::string ballot_files_;
  while(!ballot_files_list.empty()) {  // not false or error
    ballot_files_ = ballot_files_list.front();
    ballot_files_list.pop_front();
    ballotFileProcessor = new BallotFileProcessor(ballot_files_);
    ballotFileProcessor->ProcessFiles(voting_info);

    // delete previous BallotFileProcessor object after use, not pointer
    delete ballotFileProcessor;
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
