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
        if (linecnt == 0) {  // Run for first line - Candidates
            for (i = 0; i < row.size(); i++) {
                if (algo == 0) {  // plurality election
                    candidate = new Candidate(i, row[i], "Ind");
                    votinginfo->AddCandidateToCandidateList(candidate);
                } else {  // stv election
                    stv_candidate = new STVCandidate(i, row[i], "Ind");
                    votinginfo->AddCandidateToCandidateList(stv_candidate);
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
            votinginfo->AddBallotToBallotList(ballot);
        }
        linecnt++;  // Increment line counter
    }
    ballot_files_.close();
}
