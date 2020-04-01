
#include "voting_system.h"
#include "stv_election.h"
#include "plurality_election.h"
#include "ballot_file_processor.h:
#include <cstring>

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
	}
	
	UserInterface(&numSeats, &choice);
	votingInfo = new VotingInfo(choice, numSeats);

	ballotFileProcessor = new BallotFileProcessor;
	ballotFileProcessor.ProcessFiles(votingInfo);

	switch (choice){
	case 1 :
		stvElection = new STVElection(votingInfo);
		STVElection.RunElection();
		break;
	case 2:
		pluralityElection = new PluralityElection(votingInfo);
		STVElection.RunElection();
		break;
	default:
		//error
	}	
}

void UserInterface(int *numSeats, int *choice)
{
	while (choice != 1 || choice != 2)
	{
		cout << "Select election type, choose 3. Help if instruction is needed: " << endl;
		cout << "1: STV" << endl;
		cout << "2: Plurality" << endl;
		cout << "3: Help" << endl;
		cout << "Selection: ";
		cin >> choice;
		cout << endl;
		
		if (choice == 3)
		{
			DisplayHelp();
		}
	}
	cout << "Enter number of seats: "
	cin >> numSeats; // need to add some error check here
}

void DisplayHelp()
{
	// need code here
}
	