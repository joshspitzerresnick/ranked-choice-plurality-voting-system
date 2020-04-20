# CSci 5801 S20 Project 2 Makefile - Team 3
# Originally compiled by Colin Kluegel, features added by Josh Spitzer-Resnick
# (C) 2020 Colin Kluegel (klue0037), Josh Spitzer-Resnick (spitz123)

VotingSystem: voting_system.o ballot.o candidate.o voting_info.o ballot_file_processor.o plurality_election_record.o logger.o plurality_election.o stv_election.o stv_election_record.o
	g++ -g voting_system.o ballot.o candidate.o voting_info.o ballot_file_processor.o plurality_election_record.o logger.o plurality_election.o stv_election.o stv_election_record.o -o VotingSystem

voting_system.o: voting_system.cc
	g++ -c -g voting_system.cc

ballot.o: ballot.cc ballot.h
	g++ -c -g ballot.cc

candidate.o: candidate.cc candidate.h
	g++ -c -g candidate.cc

voting_info.o: voting_info.cc voting_info.h
	g++ -c -g voting_info.cc

ballot_file_processor.o: ballot_file_processor.cc ballot_file_processor.h
	g++ -c -g ballot_file_processor.cc

plurality_election_record.o: plurality_election_record.cc plurality_election_record.h
	g++ -c -g plurality_election_record.cc

logger.o: logger.cc logger.h
	g++ -c -g logger.cc

plurality_election.o: plurality_election.cc plurality_election.h
	g++ -c -g plurality_election.cc

stv_election.o: stv_election.cc stv_election.h
	g++ -c -g stv_election.cc

stv_election_record.o: stv_election_record.cc stv_election_record.h
	g++ -c -g stv_election_record.cc



all: VotingSystem docs

docs:
	cd ../documentation; doxygen Doxyfile

clean:
	rm *.o VotingSystem
