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

bool BallotShuffleOff=false;

void UserInterface(int *numSeats, int *choice);
void DisplayHelp();

int main(int argc, char** argv){

  int choice = 0;
  int numSeats;
  STVElection* stvElection;
  PluralityElection* pluralityElection;
  BallotFileProcessor* ballotFileProcessor;
  VotingInfo* votingInfo;

  if (argc >= 2 && strcmp (argv[1], "-t") == 0){
    BallotShuffleOff = true;
    // Logger::GetLogger()->LogToFile("Command line argument received: turn off ballot shuffle.") // TODO - Josh
  }

  UserInterface(&numSeats, &choice);
  votingInfo = new VotingInfo(choice, numSeats);

  ballotFileProcessor = new BallotFileProcessor;
  ballotFileProcessor.ProcessFiles(votingInfo);

  switch (choice){
    case 1 :
      stvElection = new STVElection(votingInfo);
      stvElection->RunElection();
      break;
    case 2:
      pluralityElection = new PluralityElection(votingInfo);
      pluralityElection->RunElection();
      break;
    default:
    //error, this should never happen
  }
}

void UserInterface(int *numSeats, int *choice)
{
  std::string errMsg = "Invalid choice. Please enter 1, 2 or 3.";
  char c = 0; // char var to hold user input for y/n
  bool numSeatsValid = false; // for input checking
  while (choice != 1 || choice != 2)
  {
    std::cout << "-----------------Voting System Main Menu-----------------------\n" << std::flush;
    std::cout << "Select election type, choose 3. Help if instruction is needed: \n" << std::flush;
    std::cout << "1: STV\n" << std::flush;
    std::cout << "2: Plurality\n" << std::flush;
    std::cout << "3: Help\n" << std::flush;
    std::cout << "Selection: ";
    std::cin >> choice;
    while(std::cin.fail()) {
    std::cout << errMsg << "\n" << std::flush;
    choice = 0;
  }
    std::cout << "\n" << std::flush;

    if (choice < 1 || choice > 3)
    {
      std::cout << errMsg << "\n" << std::flush;
    }
    else if (choice == 3)
    {
      DisplayHelp();
    }
  }
  while (~numSeatsValid) {
    std::cout << "Enter number of seats: "
    std::cin >> numSeats;
    // Input checking
    while(std::cin.fail()) {
      std::cout << "Invalid input. Please enter a number between 1 and 99.\n" << std::flush;
      std::cin.clear();
      numSeats = 0;
    }
    // Input range checking
    if (numSeats > 1 && numSeats < 99)
    {
      // Confirm user input
      std::cout << "Number of seats entered is :" << numSeats << "\n" << std::flush;
      std::cout << "Is this number is correct? (y/n): ";
      std::cin >> c;
      while(std::cin.fail()) {
        std::cout << "Invalid input. Please enter y or n. \n" << std::flush;
        std::cin.clear();
        c = 0;
      }
      if (c == 'y')
      {
        numSeatsValid = true;
      }
    }
  }
}

void DisplayHelp()
{
	std::cout << "---------------Voting System Help Menu------------------\n" << std::flush;
    std::cout << "* Voting System is ...\n" << std::flush;
    // need more printing codes
}
