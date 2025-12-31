#include <stdio.h>

int main() {

  // What bit
  // declaration of variable.
  int number, position;
  printf("What bit:\n");
  printf("Please enter a number:\n");
  //receiving a number from the user.
  scanf("%d", &number);
  printf("Please enter a position:\n");
  //receiving a position number from the user.
  scanf("%d", &position);
  /*
    using shifting to create a new number that the lsb of this number
    is the wanted position of the user number
  */
  int shiftNum= number >> position;

  /*
    using & 1 to find out what is the number in the wanted position.
    if T, the result will be 1, and the wanted position also will be 1
    and if F the result will be 0, and the wanted position will be 0.
  */
  int bitInPosition = shiftNum & 1;

  printf("The bit in position %d of number %d is: %d\n", position, number, bitInPosition);
  /*Scan two integers
  Print the bit in this position. */
  
  // Set bit
  // declaration of variable.
  int newNumber1, newPosition1;
  printf("\nSet bit:");
  printf("\nPlease enter a number:\n");
  //receiving a number from the user.
  scanf("%d", &newNumber1);
  printf("Please enter a position:\n");
  //receiving a position number from the user.
  scanf("%d", &newPosition1);
  /*
   create a mask that the only bit who is turned on in her
   is the bit in the position the user chose.
  */
  int setMask = 1 << newPosition1;
  /*
   by using bitwise we create two new numbers:
   BitOn- is the number with the bit in the chosen position turn on,
   by using bitwise or, the bit in the chosen position turn on
  */
  int bitOn = newNumber1 | setMask;
  /*
    BitOff- is the number with the bit in the chosen position turn off,
    by using bitwise not on the mask the only bit who turn off is the bit in the user position number,
    and use bitwise and to connect them and turn off the bit in the user chosen position in the original number
  */
  int bitOff = ~setMask & newNumber1;
  // printing the result.
  printf("Number with bit %d set to 1: %d", newPosition1, bitOn);
  printf("\nNumber with bit %d set to 0: %d\n", newPosition1, bitOff);
  /*Scan two integers
  Make sure the bit in this position is "on"
  Print the output
  Now make sure it's "off"
  */

  // Toggle bit
  // declaration of variable.
  int newNumber2, newPosition2;
  printf("\nToggle bit:");
  printf("\nPlease enter a number:\n");
  //receiving a number from the user.
  scanf("%d", &newNumber2);
  printf("Please enter a position:\n");
  //receiving a position number from the user.
  scanf("%d", &newPosition2);
  // creating a mask with only one bit on in the user chosen position
  int newMask = 1 << newPosition2;
  /*
    using bitwise xor on the number and the mask to create a new number,
    in this number the bit on the chosen position will toggle.
    because if both of them are 1 it will turn to 0
    and if in the original number is 0 it will turn to 1.
  */
  int toggleNumber = newNumber2 ^ newMask;
  //printing the result.
  printf("Number with bit %d toggled: %d\n", newPosition2, toggleNumber);
  /*Scan two integers
  Toggle the bit in this position and print
   */
  
  // Even - Odd
  // declaration of variable.
  int newNumber3;
  printf("\nEven - Odd:");
  printf("\nPlease enter a number:\n");
  //receiving a number from the user.
  scanf("%d", &newNumber3);
  /*
   if the number is odd the lsb=1 and the result will be 1
   and if even the lsb=0 and the result will be 0
  */
  int lsbNum = 1 & newNumber3;
  // find out the opposite of the lsb by using xor
  int oddOrEven = 1 ^ lsbNum;
  // printing the result
  printf("%d\n", oddOrEven);
  /* Scan an integer
  If the number is even - print 1, else - print 0. */
  
  // 3, 5, 7, 11
  printf("\n3, 5, 7, 11:");
  int number1, number2;
  printf("\nPlease enter the first number (octal):\n");
  //receiving a number from the user.
  scanf("%o", &number1);
  printf("Please enter the second number (octal):\n");
  //receiving a number from the user.
  scanf("%o", &number2);
  // new variable who sum the two numbers
  int sumNumbers = number1 + number2;
  //printing in hexa
  printf("The sum in hexadecimal: %X", sumNumbers);
  /*
   creating four variables to find the binary number in the wanted position
   by shifting the wanted bit to the lsb and find out if he is 1/0 by using &1
  */
  int position3 = (sumNumbers >> 3)&1;
  int position5 = (sumNumbers >> 5)&1;
  int position7 = (sumNumbers >> 7)&1;
  int position11 = (sumNumbers >> 11)&1;
  // printing the numbers in the position
  printf("\nThe 3,5,7,11 bits are: %d%d%d%d\n", position3, position5, position7, position11);
  /* Scan two integers in octal
  sum them  print in hexa
  Print bits in positions: 3,5,7,11  */

  printf("Bye!\n");
  
  return 0;
}
