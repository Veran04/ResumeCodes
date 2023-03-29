// Jesse Jericho
// Brian Simpson
// CDA 3103C
/*.....|.....*/

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
  int opcode, rx, ry, rz;
} Instruction;

void printInstruction(int *im, int count)
{
  int i = 0, j = 0, temp = count;

  for(i = 0; i < count; i++)
  {
    printf("%d ", im[i]);
    j++;
    if (j == 4)
    {
      j = 0;
      printf("\n");
    }
  }

  printf("\n");

  for (i = 0; i < count; i += 4)
  {
    switch(im[i])
    {
      case 1 :
        printf("lw   %d %d %d", im[i + 1], im[i + 2], im[i + 3]);
        break;
      case 2 :
        printf("add  %d %d %d", im[i + 1], im[i + 2], im[i + 3]);
        break;
      case 3 :
        printf("sw   %d %d %d", im[i + 1], im[i + 2], im[i + 3]);
        break;
      case 4 :
        printf("sub  %d %d %d", im[i + 1], im[i + 2], im[i + 3]);
        break;
      case 5 :
        printf("sio1 %d %d %d", im[i + 1], im[i + 2], im[i + 3]);
        break;
      case 6 :
        printf("sio2 %d %d %d", im[i + 1], im[i + 2], im[i + 3]);
        break;
      case 7 :
        printf("sio3 %d %d %d", im[i + 1], im[i + 2], im[i + 3]);
        break;
      case 8 :
        printf("jmp  %d %d %d", im[i + 1], im[i + 2], im[i + 3]);
        break;
      case 9 :
        printf("beqz %d %d %d", im[i + 1],im[i + 2], im[i + 3]);
        break;
    }
    printf("\n");
  }
  printf("\n");
}

void printStatus(Instruction *b1, Instruction *b2, Instruction *b3, Instruction *b4, int *pc, int *rf, int *dm)
{
  int i = 0;

  printf("PC = %d | RF = [", *pc);
  for (i = 0; i < 8; i++)
  {
    if (i == 7)
      printf("%d] | DM = [", rf[i]);
    else
      printf("%d, ", rf[i]);
  }

  for (i = 0; i < 16; i++)
  {
    if (i == 15)
      printf("%d]\n", dm[i]);
    else
      printf("%d, ", dm[i]);
  }

  printf("IFID = [%d, %d, %d, %d] | ", b1->opcode, b1->rx, b1->ry, b1->rz);
  printf("IDEX = [%d, %d, %d, %d] | ", b2->opcode, b2->rx, b2->ry, b2->rz);
  printf("EXDM = [%d, %d, %d, %d] | ", b3->opcode, b3->rx, b3->ry, b3->rz);
  printf("DMWB = [%d, %d, %d, %d]\n\n", b4->opcode, b4->rx, b4->ry, b4->rz);
}

int setZero(Instruction *b1, Instruction *b2, Instruction *b3, Instruction *b4)
{
    b1->opcode = 0;
    b1->rx = 0;
    b1->ry = 0;
    b1->rz = 0;

    b2->opcode = 0;
    b2->rx = 0;
    b2->ry = 0;
    b2->rz = 0;

    b3->opcode = 0;
    b3->rx = 0;
    b3->ry = 0;
    b3->rz = 0;

    b4->opcode = 0;
    b4->rx = 0;
    b4->ry = 0;
    b4->rz = 0;
}

int opfetch(Instruction *b1, Instruction *b2, int *rf)
{
  b2->opcode = b1->opcode;
  b2->rx = b1->rx;
  b2->ry = b1->ry;
  b2->rz = b1->rz;

  // Load
  if (b1->opcode == 1){} // Doesn't need to do anything

  // Add
  if (b1->opcode == 2)
  {
    b2->ry = rf[b1->ry];
    b2->rz = rf[b1->rz];

    b2->opcode = b1->opcode;
    b2->rx = b1->rx;
  }

  // Store
  if (b1->opcode == 3){} // Doesn't need to do anything

  // Subtract
  if (b1->opcode == 4)
  {
    b2->ry = rf[b1->ry];
    b2->rz = rf[b1->rz];

    b2->opcode = b1->opcode;
    b2->rx = b1->rx;
  }

  // Input
  if (b1->opcode == 5)
  {
    b2->rx = 0;
    b2->ry = 0;
    b2->rz = 0;
  }

  // Output
  if (b1->opcode == 6)
  {
    b2->rx = 0;
    b2->ry = 0;
    b2->rz = 0;
  }

  // Halt
  if (b1->opcode == 7)
  {
    b2->rx = 0;
    b2->ry = 0;
    b2->rz = 0;
  }
  // Jump
  if (b1->opcode == 8){} // Doesn't need to do anything

  // BeqZ
  if (b1->opcode == 9){} // Doesn't need to do anything
}

int execute(Instruction *b2, Instruction *b3, int *rf, int *pc)
{
  b3->opcode = b2->opcode;
  b3->rx = b2->rx;
  b3->ry = b2->ry;
  b3->rz = b2->rz;

  // Load
  if (b2->opcode == 1){} // Doesn't need to do anything

  // Add
  if (b2->opcode == 2)
  {
    printf("/* Adding (%d) to (%d) & storing in RF[%d] */\n\n", b2->ry, b2->rz, b2->rx);
    b3->rz = b2->ry + b2->rz; // v3 = v1 + v2
  }

  // Store
  if (b2->opcode == 3)
  {
    b2->rx = rf[b3->rx];
    b3->rx = rf[b3->rx];
    printf("/* Storing R0 to DM[%d] */\nR0 = %d\n\n", b3->rz, b3->rx);
  }

  // Subtract
  if (b2->opcode == 4)
  {
    printf("/* Subtracting (%d) - (%d) & storing in RF[%d] */\n\n", b2->ry, b2->rz, b2->rz);
    b3->rz = b2->ry - b2->rz; // v3 = v1 - v2
  }

  // Input
  if (b3->opcode == 5) // Puts user input value into R0
  {
    printf("/* input value (sio1 0 0 5) */\n");
    scanf("%d", &rf[0]);
    printf("\n");
    b3->rz = rf[0];
  }

  // Output
  if (b2->opcode == 6) // Displays value of R0 to the screen
  {
    printf("/* Outputting R0 to screen (sio1 0 0 9) */\n%d\n\n", rf[0]);
    b2->rx = rf[0];
    b3->rx = rf[0];
  }

  // Halt
  if (b2->opcode == 7) // Exit program
    return 0;

  // Jump
  if (b2->opcode == 8)
  {
    printf("/* Comparison failed - jumping back to PC = %d */\n\n", b2->rz);
    *pc = b2->rz; // Going back to PC value that we set to jump
  }

  // BeqZ
  if (b2->opcode == 9)
  {
    printf("/* Checking %d against 0 */\n\n", rf[1]);
    if (rf[1] == 0 || rf[1] == -1) // If the value is equal to 0, we skip over the jump
    {
      printf("/* Comparison success - skipping jump statement */\n\n");
      *pc = *pc + 4;
    }
  }
}

int dm(Instruction *b3, Instruction *b4, int *rf, int *dm, int mar2)
{
  b4->opcode = b3->opcode;
  b4->rx = b3->rx;
  b4->ry = b3->ry;
  b4->rz = b3->rz;

  mar2 = b4->rz;

  // Load
  if (b3->opcode == 1)
  {
    b4->ry = dm[mar2]; // Loading the value from DM into buffer
  }
  // Add
  if (b3->opcode == 2){} // Doesn't need to do anything

  // Store
  if (b3->opcode == 3)
  {
    dm[mar2] = b3->rx; // Storing the value in the RF to DM
  }

  // Subtract
  if (b3->opcode == 4){} // Doesn't need to do anything

  // Input
  if (b3->opcode == 5){} // Doesn't need to do anything

  // Output
  if (b3->opcode == 6){} // Doesn't need to do anything

  // Jump
  if(b3->opcode == 8){} // Doesn't need to do anything

  // BeqZ
  if(b3->opcode == 9){} // Doesn't need to do anything
}

int wb(Instruction *b4, int *rf)
{
  // Load
  if (b4->opcode == 1)
  {
    printf("/* Loading DM[%d] to RF[%d] */\n\n", b4->rz, b4->rx);
    rf[b4->rx] = b4->ry; // Loading value from buffer into RF
  }

  // Add
  if (b4->opcode == 2)
  {
    rf[b4->rx] = b4->rz; // Writing result back to rf
  }

  // Store
  if (b4->opcode == 3){} // Doesn't need to do anything

  // Subtract
  if (b4->opcode == 4)
  {
    rf[b4->rx] = b4->rz; // Writing the result value to the register file
  }

  // Input
  if (b4->opcode == 5){} // Doesn't need to do anything

  // Output
  if (b4->opcode == 6){} // Doesn't need to do anything

  // Jump
  if(b4->opcode == 8){} // Doesn't need to do anything

  // BeqZ
  if(b4->opcode == 9){} // Doesn't need to do anything
}

int main(int argc, char **argv)
{
  Instruction r, b1, b2, b3, b4; // IR, Buffer1, Buffer2, Buffer3, Buffer4
  FILE *ifp = NULL;
  int IM[500], DM[16], RF[8];
  int mar1, mar2, pc = 0, halt = 1, i = 0, j = 0, count = 0;

  // Setting all buffer content and arrays to be filled with 0s
  setZero(&b1, &b2, &b3, &b4);
  for(i = 0; i < 16; i++)
  {
    if (i < 8)
      RF[i] = 0;
    DM[i] = 0;
  }

  // Reading instruction input from file and storing into IM
  ifp = fopen(argv[1], "r");
  while(!feof(ifp))
  {
    fscanf(ifp, "%d", &IM[count]);
    count++;
  }

  // Printing the instructions from the file
  printInstruction(IM, count);

  printf("Assembling Program...\n");
  printf("Program assembled.\n\n/* Run */\n\n");

  while(halt)
  {
    printStatus(&b1, &b2, &b3, &b4, &pc, RF, DM);

    // Instruction Fetch - Needed for every operation
    mar1 = pc;
    pc += 4;
    r.opcode = IM[mar1];

    r.rx = IM[mar1 + 1];
    r.ry = IM[mar1 + 2];
    r.rz = IM[mar1 + 3];

    // Loading first buffer with values
    b1.opcode = r.opcode;
    b1.rx = r.rx;
    b1.ry = r.ry;
    b1.rz = r.rz;

    opfetch(&b1, &b2, RF);
    halt = execute(&b2, &b3, RF, &pc);
    dm(&b3, &b4, RF, DM, mar2);
    if (!halt)
    {
      printf("/* Halt called -- ending program */\n\n");
      break;
    }
    wb(&b4, RF);
  }

  // Printing last output before we exit from halt
  printStatus(&b1, &b2, &b3, &b4, &pc, RF, DM);
  printf("Program complete.\n");
  exit(0);
}
