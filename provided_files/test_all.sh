#! /bin/bash

# Written for Assignment 2 Design of Algorithms Semester 1 2019
# by Tobias Edwards <tobias.edwards@unimelb.edu.au>

# This bash script tests the programs p1, p2 and p3 against the appropriate
# test files in the tests/ directory. It creates output in the format
#   tests/pXx-my-out-X.txt, e.g., tests/p2b-my-out-3.txt

makefile="Makefile"

if [ ! -f verifier.py ]
then
  echo "verifier.py not found."
  exit
fi

if [ -f Makefile ]
then

  # Make p1
  echo "Compiling p1"
  make clean
  make p1

  # Test p1
  if [ -x p1 ]
  then
    for part in a b ; do
      for i in {0..9} ; do
        in_file="tests/p1$part-in-$i.txt"
        expected_file="tests/p1$part-out-$i.txt"
        out_file="tests/p1$part-my-out-$i.txt"
        ./p1 $part < $in_file > $out_file
        python verifier.py p1$part $in_file $expected_file $out_file
      done
    done
  else
    echo "Failed to compile p1."
  fi

  # Make p2
  echo "Compiling p2"
  make clean
  make p2

  # Test p2
  if [ -x p2 ]
  then
    for part in a b ; do
      for i in {0..9} ; do
        in_file="tests/p2$part-in-$i.txt"
        expected_file="tests/p2$part-out-$i.txt"
        out_file="tests/p2$part-my-out-$i.txt"
        ./p2 $part < $in_file > $out_file
        python verifier.py p2$part $in_file $expected_file $out_file
      done
    done
  else
    echo "Failed to compile p2."
  fi

  # Make p3
  echo "Compiling p3"
  make clean
  make p3

  # Test p3
  if [ -x p3 ]
  then
    for i in {0..9} ; do
      in_file="tests/p3-in-$i.txt"
      expected_file="tests/p3-out-$i.txt"
      out_file="tests/p3-my-out-$i.txt"
      ./p3 < $in_file > $out_file
      python verifier.py p3 $in_file $expected_file $out_file
    done
  else
    echo "Failed to compile p3."
  fi

  # Clean up after ourselves
  make clean

else
  echo "Makefile not found."
fi
