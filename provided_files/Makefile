# COMP20007 Design of Algorithms
# 2019 Semester 1
#
# Assignment 2 Makefile
# Template by Tobias Edwards <tobias.edwards@unimelb.edu.au>

CC     = gcc
CFLAGS = -Wall
ALL    = p1 p2 p3

all: $(ALL)

P1_FILES = p1.c
p1: $(P1_FILES)
	$(CC) $(CFLAGS) -o p1 $(P1_FILES)

P2_FILES = p2.c
p2: $(P2_FILES)
	$(CC) $(CFLAGS) -o p2 $(P2_FILES)

P3_FILES = p3.c
p3: $(P3_FILES)
	$(CC) $(CFLAGS) -o p3 $(P3_FILES)

.PHONY: clean

clean:
	rm -f $(ALL)
