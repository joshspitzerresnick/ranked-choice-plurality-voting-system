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

int main(int argc, char** argv){

  int choice = 0;
  int numSeats;
  STVElection* stvElection;
  PluralityElection* pluralityElection;
  BallotFileProcessor* ballotFileProcessor;
  VotingInfo* votingInfo;
  // Check command line argument
  if (argc >= 2 && strcmp (argv[1], "-t") == 0){
    BallotShuffleOff = true; // Turn off ballot shuffle if '-t' is detected
    logger->LogToFile("Command line argument received: turn off ballot shuffle.");
  }

  UserInterface(&numSeats, &choice);
  votingInfo = new VotingInfo(choice, numSeats);

  ballotFileProcessor = new BallotFileProcessor;
  ballotFileProcessor->ProcessFiles(votingInfo);

  switch (choice){
    case 1 :
      stvElection = new STVElection(votingInfo);
      stvElection->RunElection();
      break;
    case 2:
      pluralityElection = new PluralityElection(/*votingInfo*/); // TODO once Colin implements - Josh
      pluralityElection->RunElection(votingInfo); // TODO
      break;
    default:
      exit(1); //error, this should never happen
  }
}

void UserInterface(int *numSeats, int *choice)
{
  std::string errMsg = "Invalid choice. Please enter 1, 2 or 3.";
  char c = 0; // char var to hold user input for y/n
  bool numSeatsValid = false; // for input checking
  while (*choice != 1 && *choice != 2)
  {
    std::cout << "-----------------Voting System Main Menu-----------------------" << std::endl;
    std::cout << "Select election type, choose 3. Help if instruction is needed: " << std::endl;
    std::cout << "1: STV\n" << std::endl;
    std::cout << "2: Plurality\n" << std::endl;
    std::cout << "3: Help\n" << std::endl;
    std::cout << "Selection: ";
    std::cin >> *choice;
    while(std::cin.fail()) {
      std::cout << errMsg << std::endl;
      choice = 0;
    }
    std::cout << " "<< std::endl;

    if (*choice < 1 || *choice > 3)
    {
      std::cout << errMsg << std::endl;
    }
    else if (*choice == 3)
    {
      DisplayHelp();
    }
  }
  while (!numSeatsValid) {
    std::cout << "Enter number of seats: ";
    std::cin >> *numSeats;
    // Input checking
    while(std::cin.fail()) {
      std::cout << "Invalid input. Please enter a number between 1 and 99." << std::endl;
      std::cin.clear();
      numSeats = 0;
    }
    // Input range checking
    if (*numSeats > 1 && *numSeats < 99){
      numSeatsValid = true;
    }
  }
}

void DisplayHelp()
{
	std::cout << "---------------Voting System Help Menu------------------" << std::endl;
    std::cout << "* Voting System is ..." << std::endl;
    // need more printing codes
}
