
#include "voting_system.h"
#include "stv_election.h"
#include "plurality_election.h"
#include "ballot_file_processor.h
#include "logger.h"
#include <cstring>
#include <iostream>

bool BallotShuffleOff=false;

int main(int argc, char* argv){	
	
	int choice = 0;
	int numSeats;
	STVElection* stvElection;
	PluralityElection* pluralityElection;
	BallotFileProcessor* ballotFileProcessor;
	VotingInfo* votingInfo;
   
	if (argc >= 2 && strcmp (argv[1], "-t") == 0){
		BallotShuffleOff = true;
        Logger::GetLogger()->LogToFile("Command line argument received: turn off ballot shuffle.")
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
	while (choice != 1 || choice != 2)
	{
		std::cout << "-----------------Voting System Main Menu-----------------------" << endl;
        std::cout << "Select election type, choose 3. Help if instruction is needed: " << endl;
		std::cout << "1: STV" << endl;
		std::cout << "2: Plurality" << endl;
		std::cout << "3: Help" << endl;
		std::cout << "Selection: ";
		std::cin >> choice;
		std::cout << endl;
		
		if (choice == 3)
		{
			DisplayHelp();
		}
	}
	std::cout << "Enter number of seats: "
	std::cin >> numSeats; // need to add some error check here
}

void DisplayHelp()
{
	std::cout << "---------------Voting System Help Menu------------------" << endl;
    std::cout << "* Voting System is ..."
    // need more printing codes
}
	