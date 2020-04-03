/**
 * @file voting_system.cc
 *
 * @copyright 2020 5801 Team3, All rights reserved.
 */

// #include "voting_system.h" // NO SUCH THING - Josh
#include "stv_election.h"
#include "plurality_election.h"
#include "ballot_file_processor.h"
#include "logger.h"
#include <cstring>
#include <iostream>

bool BallotShuffleOff = false;
Logger* logger = new Logger();

void UserInterface(int *numSeats, int *choice);
void DisplayHelp();

int main(int argc, char** argv) {
  int choice = 0;
  int numSeats =0;
  STVElection* stvElection;
  PluralityElection* pluralityElection;
  BallotFileProcessor* ballotFileProcessor;
  VotingInfo* votingInfo;
  // Check command line argument
  if (argc >= 2 && strcmp(argv[1], "-t") == 0) {
    BallotShuffleOff = true;  // Turn off ballot shuffle if '-t' is detected
    logger->LogToFile("Command line argument received: turn off ballot shuffle.");
  }

  UserInterface(&numSeats, &choice);
  std::cout << numSeats <<std::endl;
  votingInfo = new VotingInfo(choice, numSeats);

  ballotFileProcessor = new BallotFileProcessor;
  ballotFileProcessor->ProcessFiles(votingInfo);

  switch (choice) {
    case 1 :
      stvElection = new STVElection(votingInfo);
      stvElection->RunElection();
      break;
    case 2:
      pluralityElection = new PluralityElection(/*votingInfo*/);  // TODO once Colin implements - Josh
      pluralityElection->RunElection(votingInfo);  // TODO
      break;
    default:
      exit(1);  // error, this should never happen
  }
}

void UserInterface(int *numSeats, int *choice) {
  std::string errMsg = "Invalid choice. Please enter 1, 2 or 3.";
  bool numSeatsValid = false;  // for input checking
  int temp;
  while (temp != 1 && temp != 2) {
    std::cout << "-----------------Voting System Main Menu-----------------------"
              << std::endl;
    std::cout << "Select election type, choose 3. Help if instruction is needed: "
              << std::endl;
    std::cout << "1: STV" << std::endl;
    std::cout << "2: Plurality" << std::endl;
    std::cout << "3: Help" << std::endl;
    std::cout << "Selection: ";
    std::cin >> temp;    
    while (std::cin.fail()) {
      std::cout << errMsg << std::endl;
    }

    if (temp < 1 || temp > 3) {
      std::cout << errMsg << std::endl;
    } else if (temp == 3) {
      DisplayHelp();
    }
  }
  *choice = temp;
  temp = 0;
  while (!numSeatsValid) {
    std::cout << "Enter number of seats: ";
    std::cin >> temp;
    // Input range checking
    if (temp >= 1 && temp <= 99) {
      numSeatsValid = true;
      *numSeats = temp;
    }
  }
}

void DisplayHelp() {
	std::cout << "---------------Voting System Help Menu------------------"
            << std::endl;
    std::cout << "* Voting System is ..." << std::endl;
    // need more printing codes
}
