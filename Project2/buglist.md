# CSci 5801 Project2 - Team3 - VotingSystem - Bug List

Num | Description of bug | Location of bug | Steps to recreate bug/test case | Root cause analysis
--- | --- | --- | --- | ---
1 | In manual file input mode, the same ballot file can get processed more than once if a user inputs the file more than once | ballot_file_processor.cc | Start VotingSystem with command line input '-m', choose input file, enter the same file twice | No checking for duplicate files, deemed low risk since we are implementing GUI file selector
2 | If an STV election ballot file is selected for plurality election, ballot file processor does not raise flag. However, election result would be correct based on which candidate is ranked 1. | ballot_file_processor.cc | Run VotingSystem, select plurality election, select stv ballot files | No file election type checking, deemed low risk, since plurality files will be put on invalid ballot list, while stv files run correctly for plurality election