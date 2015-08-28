#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


/*
  The tower of hanoi is a mathematical puzzle.  It consists of three
  rods (or pegs or towers), and a number of disks of different
  sizes which can slide onto any rod.  The puzzle starts with the
  disks on one rod in ascending order of size, the smallest at the
  top, thus making a conical shape.  The objective of the puzzle is
  to move the entire stack to another rod, satisfying the following
  rules:

  - Only one disk may be moved at a time.
  - Each move consists of taking the upper disk from one of the rods
   and sliding it onto another rod.
  - No disk may be placed on top of a smaller disk.
  
  Algorithm:
  - Move the top n-1 disks from Source to Auxiliary tower
  - Move the nth disk from Source to Destination tower
  - Move the n-1 disks from Auxiliary tower to Destination tower
  - Transferring the top n-1 disks from Source to Auxiliary tower
    can be again thought as a fresh problem, and can be solved
    in the same manner. Once we solve Tower of Hanoi with three
    disks, we can solve it with any number of disks with the
    above algorithm.
  
*/

void towers_of_hanoi(int n, char from_peg, 
		     char to_peg, char aux_peg)
{
  /* if only 1 disk, move and return */
  if(n == 1)
    {
      printf("Move disk 1 from peg %c to peg %c\n", from_peg, to_peg);
      return;
    }

  /* move top n-1 disks from A to B, using C as auxiliary */
  towers_of_hanoi(n-1, from_peg, aux_peg, to_peg);

  /* move remaining disks from A to C */
  printf("Move disk %d from peg %c to peg %c\n", 
	 n, from_peg, to_peg);

  /* move n-1 disks from B to C using A as auxiliary */
  towers_of_hanoi(n-1, aux_peg, to_peg, from_peg);
}


int main(int argc, char* argv[])
{
  int num_disks = 0;

  /*printf("argv[0] is %s, argc is %d\n", argv[0], argc);*/

  num_disks = atoi(argv[1]);

  if(argc == 2)
    {
      printf("num disks is: %d\n", num_disks);
      towers_of_hanoi(num_disks, 'A', 'B', 'C');
    }
}
