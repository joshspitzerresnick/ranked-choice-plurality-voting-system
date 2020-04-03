# csci5801_Project1 - Team3

Project1 - Waterfall Methodology - VotingSystem

- Bryan Baker - bake1358@umn.edu
- Hailin Archer - deak0007@umn.edu
- Josh Spitzer-Resnick - spitz123@umn.edu
- Colin Kluegel - klue0037@umn.edu

## How to compile the system

### Voting System build / clean using included makefile

To build the voting system, first ensure you are using the correct stable
makefile. In the project directory, navigate to the `src` directory and type
```
Project1/src $ cp Makefile.colin_stable Makefile
```
Then, compile the project by typing `make`
```
Project1/src $ make
```
This will create an executable file called `VotingSystem` in the `src`
directory. Run the project by typing
```
Project1/src $ ./VotingSystem
```
In order to clean the `src` directory of object files and the executable, type
```
Project1/src $ make clean
```

### Voting System build using CMake

To build the voting system, ensure you are in the `src` directory and type:
```
Project1/src $ cmake CMakeLists.txt
```
Then type:
```
Project1/src $ make
```
This will build the voting system. You can execute the system with the following
command:
```
Project1/src $ ./VotingSystem
```
- **NOTE** Running cmake will overwrite your current Makefile, and will be
customized to work only on your machine's file system. Do not push this version
of the Makefile to GitHub, as no one else will be able to use it.

### Unit Test files build using CMake

To build unit test files, ensure you are in the `testing` directory and type:
```
Project1/testing $ cmake CMakeLists.txt
```
Then type:
```
Project1/testing $ make
```
This will build the test system. You can execute the test system with the
following command:
```
Project1/testing $ ./runTests
```
- **NOTE** Running cmake will overwrite your current Makefile, and will be
customized to work only on your machine's file system. Do not push this version
of the Makefile to GitHub, as no one else will be able to use it.
