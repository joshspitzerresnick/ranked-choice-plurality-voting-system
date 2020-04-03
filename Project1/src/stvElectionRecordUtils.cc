/**
 * @file ListShuffle.cc
 *
 * Helper function for shuffling ballots
 */

#include <list>
#include <vector>
#include <algorithm> //std::shuffle
#include <random>  // std::default_random_engine
#include <chrono>  // std::chrono::system_clock
#include "candidate.h"

// utility function for shuffling ballots
template <typename T > void STVElectionRecord::listShuffle( std::list<T> &L )
{
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::vector<T> V( L.begin(), L.end() );
  std::shuffle( V.begin(), V.end(), std::default_random_engine(seed) );
  L.assign( V.begin(), V.end() );
}

// utility function for comparing candidates' votes
bool STVElectionRecord::STVCandidateComparator(STVCandidate* candidate1, STVCandidate* candidate2) {
  if (candidate1->GetNumBallots() == candidate2->GetNumBallots()){
    return candidate1->GetFirstBallotNum()>candidate2->GetFirstBallotNum();
  }
  else {
  return candidate1->GetNumBallots() > candidate2->GetNumBallots();
  }
}

struct STVCandidateComparator
{
  // Compare 2 STVCandidate objects using number of ballots and order received
  bool operator ()(STVCandidate* candidate1, STVCandidate* candidate2)
  {
    if (candidate1->GetNumBallots() == candidate2->GetNumBallots())
      {return candidate1->GetFirstBallotNum()>candidate2->GetFirstBallotNum(); }
      return candidate1->GetNumBallots() > candidate2->GetNumBallots(); 
  }
}