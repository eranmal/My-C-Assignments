/******************
Name: Eran malachi
*******************/

#include <stdio.h>

int main() {

	int numChosen;
	// creating variables tha present the dividers we will use late in the code
	int diTwo = 2, diTen = 10, eqZero = 0, eqOne = 1;
	int choseExit= 1;
	// the program keep running until the user choose 7
	while (choseExit == eqOne) {
		printf("Choose an option: "
		"\n\t1. Happy Face"
		"\n\t2. Balanced Number"
		"\n\t3. Generous Number"
		"\n\t4. Circle Of Joy"
		"\n\t5. Happy Numbers"
		"\n\t6. Festival Of Laughter"
		"\n\t7. Exit\n"
		);
		scanf(" %d", &numChosen);
		switch (numChosen) {
			// Case 1: Draw Happy Face with given symbols for eyes, nose and mouse
			case 1:
				char eyes,noes,mouth;
				int faceSize;
				printf("Enter symbols for the eyes, nose, and mouth:");
				scanf(" %c %c %c", &eyes, &noes, &mouth);
			    printf("\nEnter face size:\n");
				scanf( "%d", &faceSize);
				// keep running until positive number
				while (faceSize%diTwo == eqZero || faceSize < eqZero) {
					printf("The face's size must be an odd and positive number, please try again:\n");
					scanf("%d", &faceSize);
				}
				// printing the "eyes" in the first and last position
				for (int i = 0; i < faceSize; i++) {
					// print the eyes in the end and start of the row
					if (i==eqZero || i==faceSize-1) {
						printf("%c", eyes);
					}else {
						printf(" ");
					}
				}
				printf("\n");
				//printing the nose in the middle
				for (int i = 0; i < faceSize; i++) {
					// print the nose in the middle
					if (i==faceSize/diTwo) {
						printf("%c", noes);
					}else {
						printf(" ");
					}
				}
				// printing the mouth
				printf("\n\\");
				for (int i = 0; i < faceSize; i++) {
					printf("%c", mouth);
				}
				printf("/\n");
				continue;
			/*
			Case 2: determine whether the sum of all digits to the left of the middle digit(s)
			and the sum of all digits to the right of the middle digit(s) are equal
			*/

			case 2:
				int harmonNumber, harmonCut, skipping;
				int leftSum = 0, rightSum = 0, numberLength=0, fullLength;
				printf("Enter a number:\n");
				scanf(" %d", &harmonNumber);
				// keep running until the number is positive
				while (harmonNumber < eqZero || harmonNumber == eqZero) {
					printf("Only positive number is allowed, please try again:\n");
					scanf(" %d", &harmonNumber);
				}
				// finding the length of the chosen number
				harmonCut = harmonNumber;
				while (harmonCut != eqZero) {
					harmonCut = harmonCut/diTen;
					numberLength++;
					if (harmonCut == eqZero) {
						break;
					}
				}
				fullLength = numberLength;;
				skipping = 0;
				// if the length is odd, it will find the middle number
				if (numberLength%diTwo == eqOne) {
					skipping = numberLength/diTwo;
				}
				/*
				 running on the number from right to left by finding the right number by %10 and than
				 dividing by 10.
				 if i is lower than the middle number position the right number will added to the right sum
				 if i is higher than the middle number position the right number will added to the left sum
				 and if the number is odd and the middle number position = i it will skip on the right number
				 */
				for (int i = 0; i <numberLength ; i++) {
					if (i < (numberLength/diTwo) ){
						rightSum += harmonNumber%diTen;
						harmonNumber = harmonNumber/diTen;
					}else if (i >= (numberLength/diTwo) ) {
						if (i == skipping && fullLength%diTwo == eqOne ) {
							harmonNumber = harmonNumber/diTen;
						}
						leftSum += harmonNumber%diTen;
						harmonNumber = harmonNumber/diTen;
					}
				}
				// checking if the right sum equal to the left sum
				if (leftSum == rightSum) {
					printf("This number is balanced and brings harmony!\n");
				}else {
					printf("This number isn't balanced and destroys harmony.\n");
				}
				continue;
			// Case 3: determine whether the sum of the proper divisors (od an integer) is greater than the number itself
			case 3:
				int genereusNum, diveders=0;
				printf("Enter a number:\n");
			    scanf(" %d", &genereusNum);
				// keep running until positive number entered
				while (genereusNum < eqZero || genereusNum == eqZero) {
					printf("Only positive number is allowed, please try again:\n");
					scanf("%d", &genereusNum);
				}
				// x presenting the number that the chosen number is divided by
				int x = 1;
				// finding the dividers of the chosen number, and adding the good ones to one sum
				for(int i = 0; i < genereusNum-eqOne; i++) {
					if ((genereusNum%x)==eqZero) {
						diveders += x;
						x++;
					}else {
						x++;
					}
				}
				// checking if the sum of the dividers is greater the chosen number
				if (diveders > genereusNum) {
					printf("This number is generous!\n");
				}else {
					printf("This number does not share.\n");
				}
				continue;

			// Case 4: determine if a number is a prime.
			case 4:
				int primeNum, oppositeNum=0 , sizeMeasure,  size = 1 ;
				int prime=0;
				printf("Enter a number:\n");
				scanf(" %d", &primeNum);
				// keep running until positive number entered
				while (primeNum < eqZero || primeNum == eqZero) {
					printf("Only positive number is allowed, please try again:\n");
					scanf("%d", &primeNum);
				}
				// y representing the dividers
				int  y = 1;
				// going through all the numbers from 0 to the chosen number
				for(int i = 0; i < primeNum-eqOne; i++) {
					// checking if the number is divided by any numbers except himself and one
					if ((primeNum%y)==eqZero) {
						if (y==eqOne || y==primeNum) {
							y++;
						//if the number is divided by another number the prime variable increase and the num is no prime
						}else {
							prime++;
							y++;
						}
					}else {
						y++;
					}
				}
				sizeMeasure = primeNum;
				// checking the length of the number for the flipping later
				while (sizeMeasure != eqZero) {
					if (sizeMeasure/diTen == eqZero) {
						break;
					}
					// the size multiply by 10 because this is his size eventually
					size = size * diTen;
					sizeMeasure = primeNum/diTen;
				}
				// back flipping the number by using the size and adding everything to one number
				while (primeNum != eqZero) {
					oppositeNum += (primeNum % diTen)*size;
					primeNum = primeNum/diTen;
					size = size/diTen;
				}
				// y representing the divider
				y=1;
				// doing the same checking as we did to the chosen number
				for(int i = 0; i < oppositeNum-eqOne; i++) {
					if ((oppositeNum%y)==eqZero) {
						if (y==eqOne || y==oppositeNum) {
							y++;
						}else {
							y++;
							prime++;
						}
					}else {
						y++;
					}
				}
				// if prime in any level of the checking equal more than 0 than the the circle is incomplete
				if (prime > eqZero) {
					printf("The circle remains incomplete.\n");
				}else {
					printf("This number completes the circle of joy!\n");
				}
				continue;

			// Happy numbers: Print all the happy numbers between 1 to the given number.
			// Happy number is a number which eventually reaches 1 when replaced by the sum of the square of each digit
			case 5:
				int happyNum,sliptNum1,  happySum, recilcled = 0;
				int currentNum , rounds, rutinNum = 4;
				printf("Enter a number:\n");
				scanf("%d", &happyNum);
				// keep running until positive number entered
				while (happyNum < eqZero || happyNum == eqZero) {
					printf("Only positive number is allowed, please try again:\n");
					scanf("%d", &happyNum);
				}
				if (happyNum==eqOne) {
					printf("Between 1 and 1 only these numbers bring happiness: 1");
				}else {
					printf("Between 1 and %d only these numbers bring happiness: 1 ", happyNum);
					for(int i = 2; i <= happyNum;i++) {
						rounds = eqOne;
						happySum = eqZero;
						while (happySum != eqOne) {
							if (rounds == eqOne) {
								currentNum = i;
								/*
								  checking if the number bring happiness on the first time by using %10 and /10
								  to sum all his numbers
								*/
								while (currentNum != eqZero) {
									sliptNum1 = currentNum%diTen;
									happySum += sliptNum1*sliptNum1;
									if (currentNum/diTen == eqZero) {
										rounds++;
									}
									currentNum = currentNum/diTen;
								}
								// choosing the first sum as a way to find if the loop is recicling
								recilcled = happySum;
								// if i is a happy sum it printed and going to the next one
								if (happySum == eqOne) {
									printf("%d ", i);
								}
							// if the number is not a happy sum on the first round it comes to here
							}else {
								currentNum = happySum;
								happySum = eqZero;
								// calculating the new sum
								while (currentNum != eqZero) {
									sliptNum1 = currentNum%diTen;
									happySum += sliptNum1*sliptNum1;
									if (currentNum/diTen == eqZero) {
										break;
									}
									currentNum = currentNum/diTen;
								}
								// checking if he is happy sum
								if (happySum == eqOne) {
									printf("%d ", i);
								/*
									if the sum equal to the recycled one or 4(appear in any unhappy number}
									the loop end and a moving to the next i
								*/
								}else if(rounds>eqOne && (recilcled == happySum|| happySum==rutinNum)) {
									happySum = eqOne;
								}
								rounds++;
							}
							// if after ten rounds their still isn't an answer, the recycled number changing
							if (rounds == diTen) {
								recilcled = happySum;
							}

						}
					}
				}
				printf("\n");
				continue;
			// Festival of Laughter: Prints all the numbers between 1 the given number according to the statments
			case 6:
				int smileNum, cheerNum, maxNum;
				int isOk =1;
				printf("Enter a smile and cheer number:\n");
				// keep running on the program until the right values entered
				while (isOk) {
					/*
					  if the input is equal to the input inside the "if", and there is two numbers in the input
					  the program moving on. and if the input isn't like it should be it will keep running
					  until it will be okay
					 */
					if (scanf(" smile : %d , cheer : %d",&smileNum, &cheerNum) == diTwo ){
						// checking that the numbers greater than 0 and unequal.
						if(smileNum>eqZero && cheerNum>eqZero && smileNum != cheerNum) {
							printf("\nEnter maximum number for the festival:\n");
							scanf(" %d", &maxNum);
							// checking if the input is greater than 0
							while (maxNum < eqZero || maxNum == eqZero) {
								printf("Only positive maximum number is allowed, please try again:\n");
								scanf(" %d", &maxNum);

							}
							// closing the loop after the printing next.
							isOk = 0;
							/*
							 going through all the numbers between 0 to the chosen one and printing according to the
							 statement.
							*/
							for (int i = 1; i <= maxNum; i++) {
								if (i%smileNum == eqZero && i%cheerNum==eqZero) {
									printf("Festival!\n");
								}else if (i%cheerNum == eqZero) {
									printf("Cheer!\n");
								}else if(i%smileNum == eqZero) {
									printf("Smile!\n");
								}else if (i%smileNum != eqZero && i%cheerNum!=eqZero) {
									printf("%d\n", i);
								}
							}

						} else {
							printf("Only 2 different positive numbers in the given format"
								 " are allowed for the festival, please try again:\n");
						}
					// cleaning the buffet if the input isn't right
					}else {
						printf("Only 2 different positive numbers in the given format"
							 " are allowed for the festival, please try again:\n");
						scanf("%*[^\n]");
						scanf("%*c");
					}
				}
				continue;
			// exiting the code by collapsing the loop.
			case 7:
				printf("Thank you for your journey through Numeria!\n");
				choseExit = 0;
				continue;
			// any other input than the cases
			default:
				// clearing the buffet and returning to the beginning of the loop
				printf("This option is not available, please try again.\n");
				scanf("%*[^\n]");
				scanf("%*c");
				break;

		}
	}

	return 0;
}
