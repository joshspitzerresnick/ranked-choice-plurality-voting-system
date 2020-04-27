/**
 * @file ballot_file_processor.cc
 *
 * @copyright 2020 5801 Team3, All rights reserved.
 */

#include "ballot_file_processor.h"

using std::vector;
using std::string;
using std::stringstream;
using std::ios;

BallotFileProcessor::BallotFileProcessor() {
}

std::list<std::string> BallotFileProcessor::GetFiles(int choice) {
  int idx;
  bool validDir = false;
  std::list<string> files;
  std::string curFile, path;
  std::string extension;
  struct dirent *entry;
  switch (choice) {
    case 1: // When user wants to input files by hand
      std::cout << "Enter file names, press enter after each file, enter 'q' to quit: " << std::endl;
      while (true) {        
        std::cin >> curFile;
        if (!curFile.compare("q")) {break;} 
        files.push_back(curFile);
      }
      break;
    case 2: // When user wants to input all csv files in a directory
      while (!validDir) {
        std::cout << "Enter directory name: " << std::endl;
        std::cin >> path;
        DIR *dir = opendir(path.c_str());
        if (!(dir == NULL)) {
          validDir = true;
          while ((entry = readdir(dir)) != NULL) {
            curFile = entry->d_name;
            idx = curFile.rfind('.');
            if (idx != std::string::npos) {
              extension = curFile.substr(idx+1);
              if (!extension.compare("csv")) {
                files.push_back(path+"/"+curFile);
              }
            } else {
              extension = "";
            }
          }
        } else {
          std::cout << "Invalid directory. Please re-enter." << std::endl;
        }
        closedir(dir);
      }
      break;
    default:
      exit(1);  // error, this should never happen
  }
  return files;
}

int BallotFileProcessor::GetUserInput() {  
  // Ask users whether to input files by hands or import from a directory
  int choice = -1;
  std::string errMsg = "Invalid choice. Please enter 1 or 2.";
  while (choice != 1 && choice != 2) {
    std::cout << "-----------------Voting System Get Ballot Files-----------------------\n" << std::flush;
    std::cout << "How would you like to input ballot files? \n" << std::flush;
    std::cout << "1: Input by typing in console\n" << std::flush;
    std::cout << "2: Load from a directory\n" << std::flush;
    std::cout << "Selection: ";
    std::cin >> choice;
    if (std::cin.fail()) {
      std::cout << errMsg << std::endl;
      std::cin.clear();
      cin.ignore(10000, '\n');
      choice = -1;
    } else if (choice < 1 || choice > 2) {
      std::cout << errMsg << std::endl;
    }
  }
  return choice;
}

bool BallotFileProcessor::IsInvalid(int algo, int cand_cnt, Ballot* ballot) {
  std::list<int> cand_lst = ballot->GetRankedCandidateIDList();
  if (algo != 0 && (cand_lst.size() < (cand_cnt / 2.0))) {
    return true;
  } else {
    return false;
  }
}

int BallotFileProcessor::ProcessFiles(std::list<std::string> files, VotingInfo* votinginfo) {
  int ballotNum = 0;
  int numBallotsRead; // Number of ballots processed
  char msg[1000];

  for (std::list<std::string>::iterator it=files.begin(); it != files.end(); ++it) {
    numBallotsRead = ReadFile(*it, votinginfo, &ballotNum);
    snprintf(msg,sizeof(msg),"numBallotsRead=%d", numBallotsRead);
    LOGGER->Log(msg);
    if (numBallotsRead == -1) {
      snprintf(msg, sizeof(msg), "Invalid candidates detected. Skip file %s", (*it).c_str());
      LOGGER->Log(msg);
      std::cout << msg << std::endl;
    } else if (numBallotsRead == -2) {
      snprintf(msg, sizeof(msg), "Cannot open ballot file: %s", (*it).c_str());
      LOGGER->Log(msg);
      std::cout << msg << std::endl;
    } else {
      snprintf(msg,sizeof(msg),"%d Ballots are read in file %s", numBallotsRead, (*it).c_str());
      LOGGER->Log(msg);
      std::cout << msg << std::endl;
    }
  }
  if (votinginfo->GetAlgorithm() == 1) {
    votinginfo->WriteInvalidBallotsToFile(InvalidBallotFileName);
  }  
  return ballotNum;
}

int BallotFileProcessor::ReadFile(std::string fileName, VotingInfo* votinginfo, int* ballotNum) {
      // Define required variables
    int linecnt = 0;
    int algo = votinginfo->GetAlgorithm();
    int i, j;
    int num;
    std::ifstream ballot_file;
    Candidate* candidate;
    STVCandidate* stv_candidate;
    std::list<Candidate*> candidateList;
    std::list<STVCandidate*> stvCandidateList;
    Ballot* ballot;
    vector<string> row;
    vector<string> candidateNameVector;
    vector<int> introw;
    std::list<int> cand_list;
    string line, word;
    char msg[1000];

    ballot_file.open(fileName, ios::in);  // Open ballot file
    if (!ballot_file) {
      return -2;
    }
    
    // Start processing ballot file
    while (getline(ballot_file, line)) {
        row.clear();  // Clear the row variable prior to reading in new line.
        introw.clear();
        cand_list.clear();
        stringstream s(line);
        while (getline(s, word, ',')) {  // Break the row by , delimiter
        // snprintf(msg,sizeof(msg),"word=%s,word.length()=%d,isalpha(word[0])=%d,isspace(word[0])=%d",word.c_str(),(int)word.length(),isalpha(word[0]),isspace(word[0]));
        // LOGGER->Log(msg);
          if (!isspace(word[0])) { // ignore \n at the end of the line
            if (isspace(word[(int)word.length()-1])) {word.resize((int)word.length()-1);} // Get rid of \n at the end
            row.push_back(word);
            // snprintf(msg, sizeof(msg), "word= %s", word.c_str());
            // LOGGER->Log(msg);
          }
        }
        if (linecnt == 0) {  // Run for first line - Candidates
          // snprintf(msg, sizeof(msg), "ballotNum=%d", *ballotNum);
          // LOGGER->Log(msg);
          if (*ballotNum == 0) {
            for (i = 0; i < row.size(); i++) {
              if (algo == 0) {  // plurality election
                candidate = new Candidate(i, row[i], "Ind");
                votinginfo->AddCandidateToCandidateList(candidate);
              } else {  // stv election
                stv_candidate = new STVCandidate(i, row[i], "Ind");
                votinginfo->AddCandidateToCandidateList(stv_candidate);
              }
            }
          } else {  // check if candidate matches
            if (algo ==0) {
              candidateList = votinginfo->GetCandidateList();
              for (std::list<Candidate*>::iterator it=candidateList.begin(); it != candidateList.end(); ++it) {
                candidateNameVector.push_back((*it)->GetName().c_str());
            //     snprintf(msg, sizeof(msg), "canName= %s", (*it)->GetName().c_str());
            // LOGGER->Log(msg);
              }
            } else {
              stvCandidateList = votinginfo->GetSTVCandidateList();
              for (std::list<STVCandidate*>::iterator it=stvCandidateList.begin(); it != stvCandidateList.end(); ++it) {
                candidateNameVector.push_back((*it)->GetName().c_str());
              }
            }
            if (!(candidateNameVector == row)) {return -1;}
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
            ballot = new Ballot((*ballotNum)++, cand_list);
            if (IsInvalid(algo, votinginfo->GetNumCandidates(), ballot)) {
                votinginfo->AddBallotToInvalidList(ballot);
            } else {
                votinginfo->AddBallotToBallotList(ballot);
            }
        }
        linecnt++;  // Increment line counter
    }
    ballot_file.close();
    votinginfo->LogToAuditFile();
    return linecnt-1;  // Return number of ballots processed
}
