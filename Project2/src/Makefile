VotingSystem: voting_system.o ballot.o candidate.o voting_info.o ballot_file_processor.o plurality_election_record.o logger.o plurality_election.o stv_election.o stv_election_record.o
	g++ voting_system.o ballot.o candidate.o voting_info.o ballot_file_processor.o plurality_election_record.o logger.o plurality_election.o stv_election.o stv_election_record.o -o VotingSystem

voting_system.o: voting_system.cc
	g++ -c voting_system.cc

ballot.o: ballot.cc ballot.h
	g++ -c ballot.cc

candidate.o: candidate.cc candidate.h
	g++ -c candidate.cc

voting_info.o: voting_info.cc voting_info.h
	g++ -c voting_info.cc

ballot_file_processor.o: ballot_file_processor.cc ballot_file_processor.h
	g++ -c ballot_file_processor.cc

plurality_election_record.o: plurality_election_record.cc plurality_election_record.h
	g++ -c plurality_election_record.cc

logger.o: logger.cc logger.h
	g++ -c logger.cc

plurality_election.o: plurality_election.cc plurality_election.h
	g++ -c plurality_election.cc

stv_election.o: stv_election.cc stv_election.h
	g++ -c stv_election.cc

stv_election_record.o: stv_election_record.cc stv_election_record.h
	g++ -c stv_election_record.cc




clean:
	rm *.o VotingSystem
