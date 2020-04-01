
#include "voting_info.h"
#include "stv_election_record.h"
#include "candidate.h"
#include "ballot.h"


class STVElection{
    private:
    STVElectionRecord* stvElectionRecord_;
    STVResultDisplay* stvResultDisplay_;
    int numSeats_;
    public:
    STVElection(VotingInfo*);
    void RunElection();    
}