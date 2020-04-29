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
#include <QApplication>
#include <QString>
#include <QFileDialog>

bool BallotShuffleOff = false;
char InvalidBallotFileName[500];
char LogFileName[500];

/**
* @brief The command line user interface, allows the user to enter the number of seats and the
* election choice, either plurality of STV
*
* @param[out] int* numSeats used to specified the number of seats for the election
* @param[out] int* choice, either 0 for plurality 1 for stv
*/
void UserInterface(int *numSeats, int *choice);

/**
* @brief Prints some help information to the user through cout.
*
*/
void DisplayHelp();

/**
* @brief Launches a GUI so the user can select the ballot files and then processes
* the ballot files and saves them into voting_info
*
* @param[out] VotingInfo*, ballots passed into VotingInfo
*
* @return Returns int, the total number of ballots
*/
int get_ballots_gui(VotingInfo* voting_info);

/**
* @brief Utility function to get a timestamp to be used for the audit and invalid ballot files.
*
* @return Returns std::string, of timestamp in format year_month_day_hour_min_second
*/
std::string GetTimeStamp();

int main(int argc, char** argv) {

  //need to create a QApplication object to use a QWidget
  QApplication a(argc, argv);
  int choice = 5;
  int numSeats, numBallots;
  bool ManuallyEnterBallots = false;
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
  Logger::GetLogger();  
  LOGGER->Log("---------------------------------------------------------Start A New Election---------------------------------------------------------");  
  // Check command line argument
  if (argc > 3) {
	  std::cout << "Too many command line arguments. Abort." << std::endl;
	  return -1;
  }
  if (argc > 1) {
    for (int iCmd = 1; iCmd < argc; iCmd++) {
	  if (strcmp(argv[iCmd],"-t") == 0) {
         BallotShuffleOff = true;  // Turn off ballot shuffle if '-t' is detected    
         snprintf(msg, sizeof(msg), "Command line argument '%s' received: turn off ballot shuffle.", argv[iCmd]);
		 LOGGER->Log(msg);
		 std::cout << msg << std::endl;
      } else if (strcmp(argv[iCmd],"-m") == 0) {
         ManuallyEnterBallots = true;  // Manually enter ballots rather than GUI select
         snprintf(msg, sizeof(msg), "Command line argument '%s' received: manually enter ballot files.", argv[iCmd]);
		 LOGGER->Log(msg);
		 std::cout << msg << std::endl;;
      } else {
		 snprintf(msg, sizeof(msg), "Invalid command line argument '%s'. Ignored.", argv[iCmd]);
		 LOGGER->Log(msg);
		 std::cout << msg << std::endl;;
	  }
    }
  }
  
  UserInterface(&numSeats, &choice);
  votingInfo = new VotingInfo(choice, numSeats);
  if(ManuallyEnterBallots)
  {
    ballotFileProcessor = new BallotFileProcessor();
    files = ballotFileProcessor->GetFiles(ballotFileProcessor->GetUserInput());
    numBallots = ballotFileProcessor->ProcessFiles(files, votingInfo);
    // delete previous BallotFileProcessor object after use, not pointer
    delete ballotFileProcessor;
  }
  else
  {
    numBallots = get_ballots_gui(votingInfo);
  }
  if (votingInfo->GetNumBallots()<1) {
    std::cout << "There are no valid ballots. Abort." << std::endl;
    return -1;
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

int get_ballots_gui(VotingInfo* voting_info)
{
  char msg[200];
  int numBallots;
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

  ballotFileProcessor = new BallotFileProcessor();
  numBallots = ballotFileProcessor->ProcessFiles(ballot_files_list, voting_info);
  delete ballotFileProcessor;
  return numBallots;
}

void DisplayHelp() {
	std::cout << "--------------------Voting System Help Menu-------------------------------------\n" << std::flush;
  // std::cout << "* Voting System is ...\n" << std::flush;
  std::cout << "(C) 2020 Archer, Baker, Kluegel, Spitzer-Resnick\n\n" << std::flush;
  std::cout << "How to get started:\n" << std::flush;
  std::cout << "1. Open your command line terminal on your Linux system\n" << std::flush;
  std::cout << "2. Type ./VotingSystem and press enter\n\n" << std::flush;
  std::cout << "To calibrate the voting system:\n" << std::flush;
  std::cout << "3. Contact your IT department to enter the appropriate commands\n\n" << std::flush;
  std::cout << "How to run an election:\n" << std::flush;
  std::cout << "4. In the input screen:\n" << std::flush;
  std::cout << "   a. enter election type: 0 = plurality, 1 = STV\n" << std::flush;
  std::cout << "   b. enter number of seats\n" << std::flush;
  std::cout << "   c. Gui will launch for selecting ballot files, you may select multiple ballot files\n" << std::flush;
  std::cout << "   d. Election will run\n" << std::flush;
  std::cout << "5. Wait momentarily for all computations to finish\n" << std::flush;
  std::cout << "6. When all computations have finished, a summary of the results with appropriate\n" << std::flush;
  std::cout << "   statistics for the type of election you have chosen will appear on the screen\n" << std::flush;
  std::cout << "7. Close the program\n" << std::flush;
  std::cout << "8. To run a new election, start the system again and repeat the above steps\n\n" << std::flush;
  std::cout << "Alternative run method: enter files manually through command line\n\n" << std::flush;
  std::cout << "If you would prefer enter ballot files through the command line instead of the gui:\n" << std::flush;
  std::cout << "1. Type ./VotingSystem -m \n" << std::flush;
  std::cout << "2. Follow steps 4a-b above \n" << std::flush;
  std::cout << "3. At the input screen:\n" << std::flush;
  std::cout << "    a. enter 1 to specify ballot files, 2 to specify a directory \n" << std::flush;
  std::cout << "    b. If 1 is entered to specify ballot files enter each file one \n" << std::flush;
  std::cout << "       at a time, hit enter after each file, once all files have \n" << std::flush;
  std::cout << "       hit q to run the election with these files \n" << std::flush;
  std::cout << "       If 2 is entered to specify a directory, type the name of \n" << std::flush;
  std::cout << "       the directory and hit enter, all csv files in that will \n" << std::flush;
  std::cout << "       be used in the election \n" << std::flush;
  std::cout << "    c. Election will run \n" << std::flush;
}

std::string GetTimeStamp(){
  char timeStamp[200];
  time_t now = time(0);
  std::tm *ltm = localtime(&now);
  snprintf(timeStamp, sizeof(timeStamp), "%d.%02d.%02d.%02d%02d%02d"
          , 1900 + ltm->tm_year, ltm->tm_mon, ltm->tm_mday, ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
  return timeStamp;
}
