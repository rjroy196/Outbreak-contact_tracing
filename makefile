CC=mpicxx
CC1=g++

all: seq par

seq:
	$(CC1) -std=c++11 outbreak_seq.cpp -o outbreak_seq.o
par:
	$(CC) -std=c++11 outbreak_mpi.cpp -o outbreak_mpi.o
clean:
	rm -f outbreak_mpi.o outbreak_seq.o