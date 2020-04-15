/**
 * @file voting_info.cc
 *
 * @copyright 2020 Josh Spitzer-Resnick, spitz123
 */

#include <iostream>
#include <string>
#include <list>

#include "voting_info.h"

VotingInfo::VotingInfo(int algorithm, int seats) {
  algorithm_ = algorithm;
  num_seats_ = seats;
  num_candidates_ = 0;
  candidate_list_ = {};
  num_ballots_ = 0;
  ballot_list_ = {};
}

VotingInfo::~VotingInfo() {
  for (int i = 0; i < candidate_list_.size(); i++) {
    candidate_list_.pop_back();
  }
  for (int i = 0; i < ballot_list_.size(); i++) {
    ballot_list_.pop_back();
  }
  candidate_list_.clear();
  ballot_list_.clear();
}

int VotingInfo::GetAlgorithm() const {
  return algorithm_;
}

int VotingInfo::GetNumSeats() const {
  return num_seats_;
}

void VotingInfo::AddCandidateToCandidateList(Candidate* candidate) {
  candidate_list_.push_back(candidate);
  IncrementNumCandidates();
}

void VotingInfo::AddCandidateToCandidateList(STVCandidate* stv_candidate) {
  stv_candidate_list_.push_back(stv_candidate);
  IncrementNumCandidates();
}

void VotingInfo::AddBallotToBallotList(Ballot* ballot) {
  ballot_list_.push_back(ballot);
  IncrementNumBallots();
}

int VotingInfo::GetNumCandidates() const {
  return num_candidates_;
}

int VotingInfo::GetNumBallots() const {
  return num_ballots_;
}

std::list<Candidate*> VotingInfo::GetCandidateList() const {
  return candidate_list_;
}

std::list<STVCandidate*> VotingInfo::GetSTVCandidateList() const {
  return stv_candidate_list_;
}

std::list<Ballot*> VotingInfo::GetBallotList() const {
  return ballot_list_;
}

void VotingInfo::IncrementNumCandidates() {
  num_candidates_++;
}

void VotingInfo::IncrementNumBallots() {
  num_ballots_++;
}
