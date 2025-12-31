/******************
Name:eran malachi
*******************/
#include <stdio.h>
#include <string.h>

#define COLS 6
#define CHARS 256
#define GRID_SIZE 30
#define WORD_LEN 16
#define MAX_SLOTS 100
#define MAX_WORDS 100
#define MAX_GROUP 20
#define REMOVE 2
#define PLACE 1
#define CHECK 0
#define ROW_COL 2


//explanation for every function is after the main above every function
int task1RobotPaths(int row, int col);
float task2HumanPyramid(float gymTable[][COLS], int currentRow, int currentCol);
int gym_insert(float gymTabel[][COLS], int rowNum);
int task3ParenthesisValidator(char wantedClosing, int checkStart, int firstRound);
int task4QueensBattle(int row, int col, int size, int board[][MAX_GROUP], char groups[][MAX_GROUP],
    int groupUsed[CHARS]);
int checkColAndDiagonal(int row, int col, int size, int board[][MAX_GROUP], int currentRow);
int wordLength(char dictionary[][WORD_LEN], int word, int count);
int task5CrosswordGenerator(char grid[][GRID_SIZE], int startPositions[][MAX_SLOTS],
    int slLength[MAX_SLOTS], char slDirection[MAX_SLOTS], char dictionary[][WORD_LEN], int usedWords[MAX_WORDS],
    int numSlots, int numWords, int currentSlot, int currentWord);
int checkPlaceOrRemove(char grid[][GRID_SIZE], int startPositions[][MAX_SLOTS], int slLength[MAX_SLOTS],
    char slDirection[MAX_SLOTS], int currentSlot, char word[], int index, int task);
int isPlaceOk(char grid[][GRID_SIZE], int startPositions[][MAX_SLOTS], int slLength[MAX_SLOTS],
    char slDirection[MAX_SLOTS], int currentSlot, char word[], int index);
void placeOrRemoveWord(char grid[][GRID_SIZE], int startPositions[][MAX_SLOTS], int slLength[MAX_SLOTS],
    char slDirection[MAX_SLOTS], int currentSlot, char word[], int index, int removeOrAdd);
void initializeGrid(char grid[][GRID_SIZE], int size, int row, int col);

int main()
{
    int task = -1;
    do
    {
        printf("Choose an option:\n"
               "1. Robot Paths\n"
               "2. The Human Pyramid\n"
               "3. Parenthesis Validation\n"
               "4. Queens Battle\n"
               "5. Crossword Generator\n"
               "6. Exit\n");
        if (scanf("%d", &task))
        {

            switch (task)
            {
            // choose exit
            case 6:
                printf("Goodbye!\n");
                break;
            // robot path
            case 1:
                int row = 0 , col = 0, total = 0;
                printf("Please enter the coordinates of the robot (column, row):\n");
                scanf("%d %d",&row,&col);
                // total equal to function that calculate how many different ways the robot have to his destination
                total = task1RobotPaths(row, col);
                printf("The total number of paths the robot can take to reach home is: %d\n", total);
                break;
            // the human pyramid
            case 2:
                float gymTable[COLS][COLS] = {0};
                int isValid = 1;
                printf("Please enter the weights of the cheerleaders:\n");
                /*
                 inserting the weight of each cheerleader by using a function, every call to the function present
                 the number of line and cheerleader, first call- one cheerleader, second- two....
                 if the user input negative num the case will break
                */
                for (int i = 0; i < COLS; i++) {
                    isValid = gym_insert(gymTable, i);
                    if (isValid == 0) {
                        break;
                    }
                }
                if (isValid == 0) {
                    break;
                }
                printf("The total weight on each cheerleader is:");
                /*
                 printing the weight after calculate in the pyramid, each cheerleader weight is calculated with a
                 function that calculate recursive her weight with the other on top her
                */
                for (int i = 0; i < COLS; i++) {
                    for (int j = 0; j < COLS; j++) {
                        float weightResult = task2HumanPyramid(gymTable, i, j);
                        if (weightResult != 0) {
                            printf("%.2f ", weightResult);
                        }
                    }
                    printf("\n");
                }
                break;
            //Parenthesis Validation
            case 3: {
                int checkStart= 0;
                int firstRound = 0;
                /*
                cleaning the buffer from the enter the user press after he chose 3, because right after the entering
                the function base condition in to return after getting '\n'
                */
                printf("Please enter a term for validation:\n");
                /*
                 checking if the user input in the buffer is parenthesis Validate, the \0 is for the moment the
                 expected closer but it will change if the user entered opening parenthesis
                 (explained more in the function itself)
                 */
                if (task3ParenthesisValidator('\0', checkStart, firstRound)) {
                    // if the check was positive
                    printf("The parentheses are balanced correctly.\n");
                } else {
                    //if the check was negative
                    printf("The parentheses are not balanced correctly.\n");
                }
                break;
            }
            //Queens Battle
            case 4: {
                // array for the results
                int board[MAX_GROUP][MAX_GROUP] = {0};
                // array for the groups
                char groups[MAX_GROUP][MAX_GROUP];
                // an array to store all the groups
                int groupUsed[CHARS] = {0};
                int size;
                // user choose the board size
                printf("Please enter the board dimensions:\n");
                scanf("%d", &size);
                // inserting the groups the user chose
                printf("Please enter a %d*%d puzzle board:\n", size, size);
                for (int i = 0; i < size; i++) {
                    for (int j = 0; j < size; j++) {
                        // keep receiving groups without insert any enter/spaces and limited to the size*size
                        scanf("%*[ \n]");
                        scanf("%c", &groups[i][j]);
                    }
                }
                // sending the boards and size to the recursive func that try to figure if the board can be solve or not
                if (task4QueensBattle(0,0, size, board, groups, groupUsed)) {
                    /*
                     if the board can be solved the program will print it
                     the function marked in the board where is the place of the queens by 1 and the printing
                     will be according to this
                    */
                    printf("Solution:\n");
                    for (int i = 0; i < size; i++) {
                        for (int j = 0; j < size; j++) {
                            if (board[i][j] == 1) {
                                printf("X ");
                            } else {
                                printf("* ");
                            }
                        }
                        printf("\n");
                    }
                } else {
                    printf("This puzzle cannot be solved.\n");
                }
                break;
            }
            case 5:
                int gridSize;
                int numSlots;
                int numWords;
                char grid[GRID_SIZE][GRID_SIZE];
                // array for the starting rows and col in the board(first row for row second for columns
                int startPosition[ROW_COL][MAX_SLOTS];
                //arrays for the length and directions of the slots
                int slotLength[MAX_SLOTS];
                char slotDirection[MAX_SLOTS];
                //array for the words and for the used words
                char dictionary[MAX_WORDS][WORD_LEN];
                int usedWords[MAX_WORDS] = {0};

                printf("Please enter the dimensions of the crossword grid:\n");
                scanf("%d", &gridSize);
                //initializing the grid to #
                initializeGrid(grid, gridSize, 0,0);
                printf("Please enter the number of slots in the crossword:\n");
                scanf("%d", &numSlots);
                // enter values to each slot, every detail is saved in a different array for the checking later
                printf("Please enter the details for each slot (Row, Column, Length, Direction):\n");
                for (int i = 0; i < numSlots; i++) {
                    scanf("%d %d %d %c", &startPosition[0][i], &startPosition[1][i], &slotLength[i], &slotDirection[i]);
                }
                printf("Please enter the number of words in the dictionary:\n");
                scanf("%d", &numWords);
                // check the dictionary have enough words
                while (numWords < numSlots) {
                    printf("The dictionary must contain at least %d words. Please enter a valid dictionary size:\n",
                        numSlots);
                    scanf("%d", &numWords);
                }
                printf("Please enter the words for the dictionary:\n");
                // every word will catch a row in the dictionary array
                for (int i = 0; i < numWords; i++) {
                    scanf("%s", dictionary[i]);
                }
                // if the board can be solved, then he will be printed in the for inside the statement
                if (task5CrosswordGenerator(grid, startPosition, slotLength, slotDirection, dictionary, usedWords,
                    numSlots, numWords, 0, 0)) {
                    for (int i = 0; i < gridSize; i++) {
                        for (int j = 0; j < gridSize; j++) {
                            printf("| %c ", grid[i][j]);
                        }
                        printf("|\n");
                    }
                } else {
                    printf("This crossword cannot be solved.\n");
                }
                break;
            default:
                printf("Please choose a task number from the list.\n");
                break;
            }
        }
        else
        {
            scanf("%*s");
        }

    } while (task != 6);
}
// inserting the cheerleaders weight into an array
int gym_insert(float gymTabel[][COLS], int rowNum) {
    float cheerWeight = 0;
    // in row 1 - 1 cheerleader, row 2- 2 cheerleaders...
    for (int i = 0; i < rowNum; i++) {
        scanf("%f", &cheerWeight);
        // if the user insert a negative weight the function will stop
        if (cheerWeight < 0) {
            printf("Negative weights are not supported.\n");
            // cleaning the buffer
            scanf("%*[^\n]");
            scanf("%*c");
            return 0;
        }
        gymTabel[rowNum][i] = cheerWeight;
        cheerWeight = 0;
    }
    return 1;
}
// function that calculate all the different ways the robot has to go to (0,0)
int task1RobotPaths(int row, int col){
    if(row < 0 || col < 0) {
        return 0;
    }
    // if the robot succeed to go "home" than it return 1 and add it to the overall calculate
    if(row == 0 && col == 0) {
        return 1;
    }
    // because the robot only can move left and down the function check both the options in recursive calls and
    // calculate it together for one sum
    return task1RobotPaths(row-1, col) + task1RobotPaths(row, col-1);
}
//function that calculate the weight of the cheerleader in the pyramid
float task2HumanPyramid(float gymTable[][COLS],  int currentRow, int currentCol){
    // variable for the multiplying later
    float midWeight = 0.5;
    if(currentRow < 0 || currentCol < 0) {
        return 0;
    }
    // the top cheerleader has the same weight
    if(currentCol == 0 && currentRow == 0) {
        return gymTable[currentRow][currentCol];
    }
    /*
     all the cheerleaders organized in the 2d array from left to right so each cheerleader weight is her weight
     and half of the cheerleader above her(her row -1) and half of the cheerleader weight
     in the place top-left( her row and column -1)
     and the recursive function doing this to every cheerleader one by one by reaching the top cheerleader
     and coming back to the bottom cheerleader
    */
    return gymTable[currentRow][currentCol] +
        midWeight*task2HumanPyramid(gymTable,currentRow-1, currentCol)+
        midWeight*task2HumanPyramid(gymTable,currentRow-1, currentCol-1);
}
// function that check if the parenthesis is validate
int task3ParenthesisValidator(char wantedClosing, int checkStart, int firstRound) {
    char c;
    // reading the next character from the buffer and checking if he is the last one
    if (scanf("%c", &c) != 1 || c == '\n') {
        // return just if the user input something else than just enters
        if(firstRound != 0) {
            //the last one change the expectedClosing permanently and the result will be according the open looses
            checkStart = 1;
            return (wantedClosing == '\0');
        }
    }
    // after the first character with different from enter, change the value of the firstRound and able the opportunity
    // to end the checking
    if(c != '\n' && c!= ' ' && firstRound == 0) {
        firstRound = 1;
    }
    /*
     in for 'if' ahead every time that appear open parenthesis the if inside him will try to find his closer if he find
     it(by the conditions later) than the function
     return to the point she stopped and move to the next character,
     if not than the function return false and the result is in valid
    */
    if (c == '{') {
        if (task3ParenthesisValidator('}', checkStart, firstRound)==0) {
            return 0;
        }
    } else if (c == '[') {
        if (task3ParenthesisValidator(']', checkStart, firstRound)==0) {
            return 0;
        }
    } else if (c == '<') {
        if (task3ParenthesisValidator('>', checkStart, firstRound)==0) {
            return 0;
        }
    } else if (c == '(') {
        if (task3ParenthesisValidator(')', checkStart, firstRound)==0) {
            return 0;
        }
    }
    /*
     every time that appear any closer this condition check if this is the closing we excepted, if not the program
     will end, if yes than return 1 and the condition
     in the top skip on the return and moving on to the next character
    */
    else if (c == '}' || c == ']' || c == '>' || c == ')') {
        // Check if it matches the expected closing character
        if (c != wantedClosing) {
            /*
            if it doesn't the closer we excepted than we check if it is the last character, if yes than the program
            just return 0.
            if not than we clean the buffer for not making problems later with values remain in the buffer
            */
            if(wantedClosing != '\0' || ( wantedClosing == '\0' && checkStart!=1 ) ) {
                scanf("%*[^\n]");
                scanf("%*c");
            }
            return 0;
        }
        // the closer matched to the expected closing so return one and moving to the next character
        return 1;
    }
    // skipping on non parenthesis characters
    return task3ParenthesisValidator(wantedClosing, checkStart, firstRound);
}

//function to check if the column is empty from queens
int checkColAndDiagonal(int row, int col, int size, int board[][MAX_GROUP], int currentRow) {
    // because our work is from top to bottom the function check the previous row and not the next rows
    if (currentRow < 0) {
        // if the program checked all the column to the top without breaking than the column safe
        return 1;
    }
    // at the first round in the function check the diagonal area around the wanted place
    if(currentRow == row) {
        //checking top-left&right
        if ((row - 1 >= 0 && col - 1 >= 0 && board[row - 1][col - 1] == 1) ||
            (row - 1 >= 0 && col + 1 < size && board[row - 1][col + 1] == 1) ||
            // checking bottom-left&right
            (row + 1 < size && col - 1 >= 0 && board[row + 1][col - 1] == 1) ||
            (row + 1 < size && col + 1 < size && board[row + 1][col + 1] == 1) ||
            //checking same row left&right columns
            (col - 1 >= 0 && board[row][col - 1] == 1) ||
            (col + 1 < size && board[row][col + 1] == 1)) {
            return 0;
            }
    }else {
        // if there is a queen in the column
        if (board[currentRow][col] == 1) {
            return 0;
        }
    }
    // moving to the previous row until reaching the top
    return checkColAndDiagonal(row, col, size, board, currentRow - 1);
}

//function that try placing a queen in a if the conditions allow it
int task4QueensBattle(int row,int col,int size,int board[][MAX_GROUP],char groups[][MAX_GROUP],int groupUsed[CHARS]){
    //the only case row=size it's the case when the function succeed to insert queen in every row, so the func stop
    if(row == size) {
        return 1;
    }
    // if the function go through all column in the row without finding a place to insert the queen
    if (col == size) {
        return 0;
    }
    // save the group name of the current place
    char group = groups[row][col];
    /*
      if the group haven't been used yet(checked by the hascii value location in the used group array)
      and if the diagonal and column are empty from queen, then move on.
    */
    if (groupUsed[(int)group] == 0 && checkColAndDiagonal(row, col, size, board, row) == 1) {
        //place a queen and mark the group as used
        board[row][col] = 1;
        groupUsed[(int)group] = 1;
        //if this is the last row than the board solved
        if (row == size - 1) {
            return 1;
        }
        //sending the next row
        if (task4QueensBattle(row+1, 0, size, board, groups, groupUsed)) {
            return 1;
        }
        // remove the queen and mark the group as unused(happened after the function above get stack at some point)
        board[row][col] = 0;
        groupUsed[(int)group] = 0;
    }
    //sending the next column
    return task4QueensBattle(row, col + 1, size, board, groups, groupUsed);
}
// Initialize the grid with '#' characters recursively
void initializeGrid(char grid[][GRID_SIZE], int size, int row, int col) {
    if (row == size) {
        return;
    }
    if (col == size) {
        initializeGrid(grid, size, row + 1, 0);
        return;
    }
    grid[row][col] = '#';
    initializeGrid(grid, size, row, col + 1);
}
//function that count the length of a word
int wordLength(char dictionary[][WORD_LEN], int word, int count) {
    // if the word end send the count of characters in the word
    if(dictionary[word][count] == '\0') {
        return count;
    }
    // send the next character
    return wordLength(dictionary, word, count + 1);
}
// function that check if word can be placed and remove/place word.
int checkPlaceOrRemove(char grid[][GRID_SIZE], int startPositions[][MAX_SLOTS], int slLength[MAX_SLOTS],
    char slDirection[MAX_SLOTS], int currentSlot, char word[], int index, int task) {
    /*
      the function behave according to where she called, each value of task represent another task:
      0- Check, 1- Place, 2- Remove
     */
    // the whole word had been place/checked/removed
    if (index == slLength[currentSlot]) {
        return 1;
    }
    int checkRow = startPositions[0][currentSlot];
    int checkCo = startPositions[1][currentSlot];
    // if the direction is vertical, move to the next vertical cell, and if horizontal do the same for horizontal cell
    if (slDirection[currentSlot] == 'V') {
        checkRow += index;
    } else if (slDirection[currentSlot] == 'H') {
        checkCo += index;
    }
    // if the function at checking
    if (task == CHECK) {
        // if the cell isn't empty or doesn't matching to the character in the word, then return 0
        if (grid[checkRow][checkCo] != '#' && grid[checkRow][checkCo] != word[index]) {
            return 0;
        }
    // if the function at placing
    } else if (task == PLACE) {
        grid[checkRow][checkCo] = word[index];
    // if the function at removing
    } else if (task == REMOVE) {
        grid[checkRow][checkCo] = '#';
    }

    // Recursive call to process the next character
    return checkPlaceOrRemove(grid, startPositions, slLength, slDirection, currentSlot, word, index + 1, task);
}

// func that try to solve the board by sending word by word to checking/removing and inserting until the board solved
int task5CrosswordGenerator(char grid[][GRID_SIZE], int startPositions[][MAX_SLOTS], int slLength[MAX_SLOTS],
    char slDirection[MAX_SLOTS], char dictionary[][WORD_LEN], int usedWords[MAX_WORDS], int numSlots, int numWords,
    int currentSlot, int currentWord) {
    // if all board have been inserted successfully
    if (currentSlot == numSlots) {
        return 1;
    }
    // if all the word tried to be placed, and without success
    if (currentWord >= numWords) {
        return 0;
    }
    // check if the current word been used
    if (usedWords[currentWord] != 0) {
        return task5CrosswordGenerator(grid, startPositions, slLength, slDirection, dictionary, usedWords, numSlots,
            numWords, currentSlot, currentWord + 1);
    }
    // check if the current word length match the slot length and if it can be placed
    if (wordLength(dictionary,currentWord,0) == slLength[currentSlot] &&
        checkPlaceOrRemove(grid, startPositions, slLength,slDirection, currentSlot, dictionary[currentWord],0, CHECK)){
        // if yes, mark the word as used and place the word
        usedWords[currentWord] = 1;
        checkPlaceOrRemove(grid, startPositions, slLength, slDirection, currentSlot, dictionary[currentWord], 0, PLACE);
        // calling to the next slot index
        if (task5CrosswordGenerator(grid, startPositions, slLength, slDirection, dictionary, usedWords,
            numSlots, numWords, currentSlot + 1, 0)) {
            // if succeed to place all the words than return 1
            return 1;
        }
        // if there was a problem in the way, return and remove the words that need to be removed
        checkPlaceOrRemove(grid, startPositions, slLength, slDirection, currentSlot, dictionary[currentWord], 0,REMOVE);
        //mark the removed words as unused
        usedWords[currentWord] = 0;
    }
    //moving to the next word
    return task5CrosswordGenerator(grid, startPositions, slLength, slDirection, dictionary, usedWords, numSlots,
        numWords, currentSlot, currentWord + 1);
}
