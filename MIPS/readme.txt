This code uses assembly code to perform basic commands

To run this program:
Compile and run it with an input text file at the command line.

============================================================================
||  Input files should be in the format of "W X Y Z" for each operation.  ||
============================================================================
Example of correct file input structure with 3 operations:
5 0 0 5 6 0 0 9 3 0 0 0

=================================================================
||  Example run at command line for a text file named "input"  ||
=================================================================
gcc mips.c
./a.out input.txt

This will take your input instructions and the program will execute
what you have instructed it to do via the input text file.

============================================
||  How to properly run multiply program  ||
============================================
For proper use of the multiply instruction
file, when prompted for user input you should
enter your first digit followed by the enter
key. You will then be prompted to input your
second digit, again followed by the enter key.
*********************************************
****** THE THIRD INPUT DIGIT MUST BE 1 ******
*********************************************
The third input digit for the program to work
properly must be 1. This allows us to decrement
the value 1 from one of the numbers to simulate
the act of multiplication in the program.

The resulting value from the multiplication will
both be printed onto the screen and stored in
DM[3].

The DM register view will give you a good look at
what the program is doing.

Example:
If we multiplied 5x6 the DM register by
the end of the program will look like:
DM = [5, 6, 1, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]

The first value being your first input number

The second value being your second input number

The third value being 1 (This should always be 1 for
the program to work properly)

The fourth value being your result from the multiplication

=================================================================
||  Example input for multiplying 5x6 in the multiply program  ||
=================================================================
gcc mips.c
./a.out multiply.txt
5
6
1

============================================
||   Summary of instructions for input    ||
============================================
Opcode		 Instruction		      Description
    1   	 lw   Rx  0  addr		  Rx <- DM[addr]
    2		   add  Rx  Ry Rz		    Rx <- Ry + Rz
    3		   sw   Rx  0  addr		  DM[addr] <-  Rx
    4		   sub  Rx  Ry Rz		    Rx < -Ry - Rz
    5  		 sio1 Rx  0  5	      Rx <- Keyboard
    6 		 sio2 Rx  0  9	      screen <- Rx
    7 		 sio3  0  0  0		    halt <- 0
    8 		 jmp   0  0  addr	    PC <- addr
    9 		 beqz Rx  0   0		    if Rx = 0 {PC <- PC + 4}
