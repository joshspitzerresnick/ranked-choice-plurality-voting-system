/**
 * @file ballot_file_processor.cc
 *
 * @copyright 2020 5801 Team3, All rights reserved.
 */

#include <string>
#include <sstream>
#include <vector>
#include <list>
#include "candidate.h"
#include "ballot.h"
#include "voting_info.h"
#include "ballot_file_processor.h"

using std::vector;
using std::string;
using std::stringstream;
using std::ios;

BallotFileProcessor::BallotFileProcessor(std::string ballotfilename) {
  ballot_file_name_ = ballotfilename;
}

BallotFileProcessor::~BallotFileProcessor() {
  ballot_files_.close();
}

bool BallotFileProcessor::IsInvalid(int algo, int cand_cnt, Ballot* ballot) {
  std::list<int> cand_lst = ballot->GetRankedCandidateIDList();
  if (algo != 0 && (cand_lst.size() < (cand_cnt / 2.0))) {
    return true;
  } else {
    return false;
  }
}

void BallotFileProcessor::ProcessFiles(VotingInfo* votinginfo) {
  // Define required variables
  int linecnt = 0;
  int algo = votinginfo->GetAlgorithm();
  int i, j;
  int num;
  Candidate* candidate;
  STVCandidate* stv_candidate;
  Ballot* ballot;
  vector<string> row;
  vector<int> introw;
  std::list<int> cand_list;
  string line, word;
  bool candidates_already_loaded_ = false;

  ballot_files_.open(ballot_file_name_, ios::in);  // Open ballot file

  // Start processing ballot file
  while (getline(ballot_files_, line)) {
    row.clear();  // Clear the row variable prior to reading in new line.
    introw.clear();
    cand_list.clear();
    stringstream s(line);
    while (getline(s, word, ',')) {  // Break the row by , delimiter
      row.push_back(word);
    }
    if (linecnt == 0) {  // Run for first line - Candidates // only want FIRST ballot file, assume others are the same
      for (i = 0; i < row.size(); i++) {
        if (algo == 0) {  // plurality election
          // check if candidates already loaded - ASSUME candidates in same order across ballot files
          if (votinginfo->GetCandidateList().size() == row.size()) {  // candidates already added by previous ballot file
            candidates_already_loaded_ = true;
          }
          // add candidate if doesn't exist already
          if (candidates_already_loaded_ == false) {
            candidate = new Candidate(i, row[i], "Ind");
            votinginfo->AddCandidateToCandidateList(candidate);
          }
        } else {  // STV election, algo == 1
          // check if candidates already loaded - ASSUME candidates in same order across ballot files
          if (votinginfo->GetSTVCandidateList().size() == row.size()) {  // candidates already added by previous ballot file
            candidates_already_loaded_ = true;
          }
          // add STV candidate if doesn't exist already
          if (candidates_already_loaded_ == false) {
            stv_candidate = new STVCandidate(i, row[i], "Ind");
            votinginfo->AddCandidateToCandidateList(stv_candidate);
          }
        }
      }
    } else {  // Run for the rest of the file - ballot information
      for (i = 0; i < row.size(); i++) {
        num = atoi(row.at(i).c_str());
        introw.push_back(num);  // Convert strings to integers
      }
      i = 0;
      j = 0;
      for (i = 0; i < row.size(); i++) {
        for (j = 0; j < introw.size(); j++) {
          if (introw[j] != 0 & introw[j] == i+1) {
            cand_list.push_back(j);
          }
        }
      }
      ballot = new Ballot(linecnt, cand_list);
      if (IsInvalid(algo, votinginfo->GetNumCandidates(), ballot)) {
        votinginfo->AddBallotToInvalidList(ballot);
      } else {
        votinginfo->AddBallotToBallotList(ballot);
      }
    }
    linecnt++;  // Increment line counter
  }
  ballot_files_.close();
}
