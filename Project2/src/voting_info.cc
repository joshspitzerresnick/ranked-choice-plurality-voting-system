/**
 * @file voting_info.cc
 *
 * @copyright 2020 5801 Team3, all rights reserved
 */

#include <iostream>
#include <string>
#include <list>
#include <fstream>  // ofstream for writing invalid ballots
#include <typeinfo>  // typeid( ).name() for debugging
#include <iomanip>
#include <math.h>
#include "logger.h"

#include "voting_info.h"

VotingInfo::VotingInfo(int algorithm, int seats) {
  algorithm_ = algorithm;
  num_seats_ = seats;
  num_candidates_ = 0;
  candidate_list_ = {};
  num_ballots_ = 0;
  ballot_list_ = {};
  num_invalid_ = 0;
  invalid_list_ = {};
}

VotingInfo::~VotingInfo() {
  for (int i = 0; i < candidate_list_.size(); i++) {
    candidate_list_.pop_back();
  }
  for (int i = 0; i < ballot_list_.size(); i++) {
    ballot_list_.pop_back();
  }
  for (int i = 0; i < invalid_list_.size(); i++) {
    invalid_list_.pop_back();
  }
  candidate_list_.clear();
  ballot_list_.clear();
  invalid_list_.clear();
}

int VotingInfo::GetAlgorithm() const {
  return algorithm_;
}

int VotingInfo::GetNumSeats() const {
  return num_seats_;
}

void VotingInfo::AddCandidateToCandidateList(Candidate* candidate) {
  std::list<Candidate*> temp_list = GetCandidateList();
  while (!temp_list.empty()) {
    if (temp_list.front()->GetID() == candidate->GetID()) {  // don't add twice
      std::string errmsg = "Candidate with ID #" + std::to_string(candidate->GetID()) + " already added to Candidate list";
      perror(errmsg.c_str());
      return;
    }
    temp_list.pop_front();
  }
  candidate_list_.push_back(candidate);  // else
  IncrementNumCandidates();
}

void VotingInfo::AddCandidateToCandidateList(STVCandidate* stv_candidate) {
  std::list<STVCandidate*> temp_list = GetSTVCandidateList();
  while (!temp_list.empty()) {
    if (temp_list.front()->GetID() == stv_candidate->GetID()) {  // don't add twice
      std::string errmsg = "STVCandidate with ID #" + std::to_string(stv_candidate->GetID()) + " already added to STVCandidate list";
      perror(errmsg.c_str());
      return;
    }
    temp_list.pop_front();
  }
  stv_candidate_list_.push_back(stv_candidate);  // else
  IncrementNumCandidates();
}

void VotingInfo::AddBallotToBallotList(Ballot* ballot) {
  std::list<Ballot*> temp_list = GetBallotList();
  while (!temp_list.empty()) {
    if (temp_list.front()->GetID() == ballot->GetID()) {  // don't add twice
      std::string errmsg = "Ballot with ID #" + std::to_string(ballot->GetID()) + " already added to Ballot list";
      perror(errmsg.c_str());
      return;
    }
    temp_list.pop_front();
  }
  ballot_list_.push_back(ballot);  // else
  IncrementNumBallots();
}

void VotingInfo::AddBallotToInvalidList(Ballot* ballot) {
  std::list<Ballot*> temp_list = GetInvalidList();
  while (!temp_list.empty()) {
    if (temp_list.front()->GetID() == ballot->GetID()) {  // don't add twice
      std::string errmsg = "Ballot with ID #" + std::to_string(ballot->GetID()) + " already added to Invalid list";
      perror(errmsg.c_str());
      return;
    }
    temp_list.pop_front();
  }
  invalid_list_.push_back(ballot);  // else

  IncrementNumInvalid();
}

int VotingInfo::GetNumCandidates() const {
  return num_candidates_;
}

int VotingInfo::GetNumBallots() const {
  return num_ballots_;
}

int VotingInfo::GetNumInvalid() const {
  return num_invalid_;
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

std::list<Ballot*> VotingInfo::GetInvalidList() const {
  return invalid_list_;
}

void VotingInfo::IncrementNumCandidates() {
  num_candidates_++;
}

void VotingInfo::IncrementNumBallots() {
  num_ballots_++;
}

void VotingInfo::IncrementNumInvalid() {
  num_invalid_++;
}

void VotingInfo::WriteInvalidBallotsToFile(std::string filename) {
  std::ofstream invalidated_file_;
  invalidated_file_.open(filename/*, std::ios_base::app*/);  // overwrite instead of append
  if (invalidated_file_.fail()) {  // better to use !invalidated_file_.good() ?
    invalidated_file_.close();
    std::string errmsg = "File \"" + filename + "\" failed to open, invalidated ballots report not written";
    perror (errmsg.c_str());
    return;
  }

  std::list<Ballot*> invalid_ballots_ = GetInvalidList();  // makes copy so original list safe
  std::list<int> ranked_candidate_ids_;

  invalidated_file_ << "--------------------Invalidated Ballot Report-----------------------------------" << std::endl;
  invalidated_file_ << "# invalidated ballots: " << GetNumInvalid() << std::endl;
  invalidated_file_ << "# candidates: " << GetNumCandidates() << std::endl;
  invalidated_file_ << "# candidates to be invalidated (< half): <" << GetNumCandidates()/2.0 << std::endl;
  invalidated_file_ << "--------------------------------------------------------------------------------" << std::endl;
  // invalidated_file_ << "Ballot ID:\t\t\t\tCandidate IDs in order of preference:" << std::endl;
  // invalidated_file_ << "[1, n] indexed\t\t[0, n-1] indexed" << std::endl;

  while(!invalid_ballots_.empty()) {  // iterate through ballots
    ranked_candidate_ids_ = invalid_ballots_.front()->GetRankedCandidateIDList();  // makes copy so original list safe
    invalidated_file_ << "Ballot #" << std::setw(floor(log10(GetNumBallots()) + 1)) << invalid_ballots_.front()->GetID() << ":  Ranked Candidate ID List: ";
    while (!ranked_candidate_ids_.empty()) {  // iterate through candidate rankings
      invalidated_file_ << ranked_candidate_ids_.front();  // don't leave trailing ", "

      ranked_candidate_ids_.pop_front();  // will not need anymore
      if (ranked_candidate_ids_.empty()) {
        invalidated_file_ << std::endl;  // end of 1 ballot
        break;
      }
      invalidated_file_ << ", ";  // only if has another candidate in ranking
    }
    invalid_ballots_.pop_front();  // will not need anymore
  }
  invalidated_file_ << "--------------------Invalidated Ballot Report Completed-------------------------";
  invalidated_file_.close();
}

void VotingInfo::LogToAuditFile() {
  char msg[1000];
  snprintf(msg, sizeof(msg), "Following ballots are put on invalid ballot list: ");
  LOGGER->Log(msg);
  LOGGER->Log(invalid_list_);
}
