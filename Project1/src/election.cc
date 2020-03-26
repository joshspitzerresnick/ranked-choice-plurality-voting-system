/**
 * @file election.cc
 *
 * @copyright 2020 5801 Team3, All rights reserved.
 */

#include "election.h"
#include "voting_info.h"

AbstractElection::AbstractElection() {
    // Add code here
}

void AbstractElection::RunElection(VotingInfo*) {
    // Add code here
}

PluralityElection::PluralityElection() {
    // Add code here
}

void PluralityElection::RunElection(VotingInfo*) {
    // Add code here
}

STVElection::STVElection() {
    // Add code here
}

void STVElection::RunElection(VotingInfo*) {
    // Add code here
}
