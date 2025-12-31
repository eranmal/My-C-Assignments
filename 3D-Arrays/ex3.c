/******************
Name: eran malachi
*******************/

#include <stdio.h>

#define NUM_OF_BRANDS 5
#define BRANDS_NAMES 10
#define NUM_OF_TYPES 4
#define TYPES_NAMES 5
#define DAYS_IN_YEAR 365
#define ADD_ONE 1
#define ADD_ALL 2
#define STATS 3
#define PRINT 4
#define INSIGHT 5
#define DELATS 6
#define DONE 7

char brands[NUM_OF_BRANDS][BRANDS_NAMES] = {"Toyoga    ", "HyunNight ", "Mazduh    ", "FolksVegan", "Key-Yuh   "};
char types[NUM_OF_TYPES][TYPES_NAMES] = {"SUV  ", "Sedan", "Coupe", "GT   "};

// the explanations for each function are at the end of the code
void resetCube(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]);
void printMenu();
void getBrandName(int brandNum);
void brandDData(int lay,int row, int cou,int cube[lay][row][cou],int cBrand, int s1, int s2, int s3,int s4, int days[]);
int dayCount(int day, int iBrand, int days[]);
int biggestDay(int days[], int day);
int biggestBrand(int brand[]);
int biggestType(int type[]);
void getTypeName(int typeNum);
void totalDaySum(int lay, int row, int cou,int cube[lay][row][cou],int day);
void totalSalesDay(int lay, int row, int cou,int cube[lay][row][cou], int days[]);
void bestOverall(int lay, int row, int cou,int cube[lay][row][cou],int day);
void avaregeCalculate(int daySum[], int day, int days[]);
void deltaMetrics(int lay, int row, int cou,int cube[lay][row][cou], int day, int days[]);


int main(){
    int days[NUM_OF_BRANDS] = {0};
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
    // unchangeable values
    const int dayD = DAYS_IN_YEAR, brandD = NUM_OF_BRANDS, typeD = NUM_OF_TYPES;
    // resetting the cube values to -1
    resetCube(cube);
    int day = 0, choice;
    printMenu();
    scanf("%d", &choice);
    while(choice != DONE){
        switch(choice){
            // updating just one brand and his types
            case ADD_ONE:
                int carBrand, dOneSum1, dOneSum2, dOneSum3,dOneSum4, loopConti= 0;
                while(loopConti != 1) {
                    printf("What Brand: \n");
                    if(scanf(" %d %d %d %d %d", &carBrand, &dOneSum1, &dOneSum2, &dOneSum3, &dOneSum4)==5) {
                        // keep asking until a valid input insert
                        if(carBrand>=0 && carBrand<=4) {
                            // sending the inputs to a function that give every type his sum
                            brandDData(dayD,brandD,typeD,cube,carBrand,dOneSum1,dOneSum2,dOneSum3,dOneSum4,days);
                            // Sends the current day to a function that updates him
                            day = dayCount(day , carBrand, days);
                            // closing the loop
                            loopConti=1;
                        }else {
                            printf("\nThis brand is not valid\n");
                        }
                    } else {
                        printf("\nThis brand is not valid\n");
                        scanf("%*[^\n]");
                        scanf("%*c");
                    }
                }
            break;
            // updating all the brands
            case ADD_ALL:
                #define CHECKING 5
                int allCarBrand=0, allSum1=0, allSum2=0, allSum3=0,allSum4=0, check=0, place=0, breakLoop=0;
                int numExist =0 ;
                int checking[CHECKING];
                //Reset the checking array
                for (int i= 0; i < CHECKING; i++) {
                    checking[i]=CHECKING;
                }
                while(breakLoop != 1) {
                    printf("No data for brands ");
                    // printing just the un updated brands
                    for (int j = 0; j < NUM_OF_BRANDS; j++) {
                        /*
                         every brand presented by a number, later, after every insert, the brand number
                         will enter to the checking array and at the next time
                         the if statement will skip on him, and he will not be printed
                        */
                        if (checking[j] == CHECKING) {
                            //sending the number to a function that print the brand name by receive the wanted position
                            getBrandName(j);
                            printf(" ");
                        }
                    }
                    printf("\nPlease complete the data\n");
                    if(scanf(" %d", &allCarBrand)==1) {
                        scanf("%d %d %d %d",  &allSum1, &allSum2, &allSum3, &allSum4);
                        // statement that allow to receive just the brands number location
                        if(allCarBrand>=0 && allCarBrand<=4) {
                            // checkin if the user already input this brand
                            for(int i = 0; i < NUM_OF_BRANDS; i++) {
                                // going through the checking array and find if the chosen number already in there
                                if(checking[i] == allCarBrand) {
                                    printf("This brand is not valid\n");
                                    //check- check that all brands inserts, numExist- check if the brand already chosen
                                    check++;
                                    numExist++;
                                }
                            }
                            // if the brand num didnt chosen yet:
                            if(numExist==0) {
                                // insert the chosen num to the checking array
                                checking[allCarBrand] = allCarBrand;
                                // sending the inputs to a function that insert the sums to the brand types
                                brandDData(dayD,brandD,typeD,cube,allCarBrand, allSum1,allSum2,allSum3,allSum4,days);
                                place++;
                            }
                            // if place equal to 5 the means that all the brands number had been inserted
                            if (place == CHECKING) {
                                // breaking the loop
                                breakLoop = 1;
                                // adding a day by using the func
                                day = dayCount(day, NUM_OF_BRANDS, days);
                            }
                            // reset for the checking next round
                            numExist = 0;
                        }else {
                            printf("This brand is not valid\n");
                        }
                    }else {
                        printf("This brand is not valid\n");
                        scanf("%*[^\n]");
                        scanf("%*c");
                    }
                }
            break;
            // analyzing a specific day stats.
            case STATS:
                int selectedDay, keepRun=0;
                while(keepRun != 1) {
                    printf("What day would you like to analyze?\n");
                    scanf(" %d", &selectedDay);
                    // checking that the selected day is a valid day(day with stats in it)
                    if(selectedDay>day || selectedDay<0) {
                        printf("Please enter a valid day.\n");
                        scanf("%*[^\n]");
                        scanf("%*c");
                    }else if (selectedDay==0) {
                        printf("In day number 0: \nThe sales total was 0\nThe best sold brand with 0 sales was Toyoga"
                               "\nThe best sold type with 0 sales was SUV\n\n");
                                keepRun = 1;
                    }else {
                        // sending the selected day to a func that printing all the chosen day stats
                        totalDaySum(dayD,brandD,typeD,cube,selectedDay);
                        keepRun = 1;
                    }
                }
            break;
            // print the entire dataset
            case PRINT:
                // sending the current day to the func that printing all the data
                totalSalesDay(dayD,brandD,typeD,cube, days);
            break;
            // provide overall insight
            case INSIGHT:
                //ending the current day to the func that printing the insights
                bestOverall(dayD,brandD,typeD,cube,day);
            break;
            // provide average delta metrics
            case DELATS:
                //ending the current day to the func that printing the average delta metrics for each brand
                deltaMetrics(dayD,brandD,typeD,cube,day, days);
            break;

            default:
                printf("Invalid input\n");
        }
        printMenu();
        // clearing the buffet
        scanf("%*[^\n]");
        scanf("%*c");
        scanf(" %d", &choice);
        // if day reach the day limit the loop will break
        if (day == DAYS_IN_YEAR) {
            choice = DONE;
        }
    }
    printf("Goodbye!\n");
    return 0;
}
// resting the cube at the begging of the program
void resetCube(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]) {
    for (int i = 0; i < DAYS_IN_YEAR; i++) {
        for (int j = 0; j < NUM_OF_BRANDS; j++) {
            for (int k = 0; k < NUM_OF_TYPES; k++) {
                cube[i][j][k] = -1;
            }
        }
    }
}
// func that printing the menu
void printMenu(){
    printf("Welcome to the Cars Data Cube! What would you like to do?\n"
           "1.Enter Daily Data For A Brand\n"
           "2.Populate A Day Of Sales For All Brands\n"
           "3.Provide Daily Stats\n"
           "4.Print All Data\n"
           "5.Provide Overall (simple) Insights\n"
           "6.Provide Average Delta Metrics\n"
           "7.exit\n");
}
// func that printing the brand name by getting his location
void getBrandName(int brandNum) {
    // printing char by char the brand name until its end
    for (int i = 0; i < BRANDS_NAMES; i++) {
        if(brands[brandNum][i] != ' ') {
            printf("%c", brands[brandNum][i]);
        }
    }
}
// insert a values just for one brand
void brandDData(int lay,int row, int cou,int cube[lay][row][cou],int cBrand, int s1, int s2, int s3,int s4, int days[]){
    // going through all the types of the chosen brand and insert the chosen values to the current day
    int typePosition = 0;
    cube[days[cBrand]][cBrand][typePosition] += s1+1;
    cube[days[cBrand]][cBrand][++typePosition] += s2+1;
    cube[days[cBrand]][cBrand][++typePosition] += s3+1;
    cube[days[cBrand]][cBrand][++typePosition] += s4+1;
}
// func that counts the days
int dayCount(int day, int iBrand, int days[]) {
    // updating the day, insert him in the days array and return the updated day back
    day++;
    // updating just one day(if the user chose 1 on the menu)
    if (iBrand != NUM_OF_BRANDS) {
        days[iBrand] += 1;
    // updating the day for all the brands (if the user chose 2 on the menu)
    }else {
        for (int j = 0; j < NUM_OF_BRANDS; j++) {
            days[j] += 1;
        }
    }
    return day;
}
//function that receive an array of total profits in a day, every position represent the day number
int biggestDay(int daysRe[], int day) {
    int bestDay=0;
    int comperDay=0;
    int countDay = 0;
    // going through all the values
    for (int i = 0; i < day; i++) {
        bestDay = daysRe[i];
        // check if the current profit is bigger than the last bigger day profit
        if (bestDay > comperDay) {
            // if its bigger the compare value change his value to the current value
            comperDay = bestDay;
            // saving the biggest day profit in a variable
            countDay = i;
        }
    }
    // sending back the position of the biggest day profit
    return countDay;
}
//function that receive an array of total brand profits, every position represent another brand.
int biggestBrand(int brand[]) {
    int bestBrand=0, comperBrand=0, countBrand = 0;
    // going through all the values
    for (int i = 0; i < NUM_OF_BRANDS; i++) {
        bestBrand = brand[i];
        // check if the current brand is bigger than the last bigger brand
        if (bestBrand > comperBrand) {
            comperBrand = bestBrand;
            // saving the biggest brand profit in a variable
            countBrand = i;
        }
    }
    // sending back the position of the biggest brand profit
    return countBrand;
}
//function that receive an array of total type profits, every position represent another type.
int biggestType(int type[]){
    int bestType=0, comperType=0, countType = 0;
    // going through all the values
    for (int i = 0; i < NUM_OF_TYPES; i++) {
        bestType = type[i];
        // check if the current type is bigger than the last bigger type
        if (bestType > comperType) {
            comperType = bestType;
            // saving the biggest type profit in a variable
            countType = i;
        }
    }
    // sending back the position of the biggest type profit
    return countType;
}
// func that receive a type position and prints his name
void getTypeName(int typeNum) {
    // printing char by char the brand name until its end
    for (int i = 0; i < TYPES_NAMES; i++) {
        if(types[typeNum][i] != ' ') {
            printf("%c", types[typeNum][i]);
        }
    }
}
// function that analyze the chosen day stats printing them
void totalDaySum(int lay, int row, int cou,int cube[lay][row][cou], int day) {
    day = day-1;
    int totalSum = 0, brandSum2 = 0, biggerBrand =0,brandSum1 = 0;
    int typeSumPos = 0;
    int typeSum1[NUM_OF_TYPES]={0};
    // only analyze the chosen day
    for (int i = 0; i < row; i++) {
        brandSum1 = 0;
        for (int j = 0; j < cou; j++) {
            // entering the day,brand and types to different variables.
            if(cube[day][i][j] != -1) {
                totalSum += cube[day][i][j];
                brandSum1 += cube[day][i][j];
                // each daily profit of a type is entering to the same position as the type in a collector array
                typeSum1[j] += cube[day][i][j];
            }
        }
        // checking if the current brand profits is bigger than the last brand
        if(brandSum1 > brandSum2) {
            // if he is bigger than the compare variable is now equal to him, and saving his location
            brandSum2 = brandSum1;
            biggerBrand = i;
        }
    }
    // sending the type array to function that return the position of the most profitable type
    typeSumPos = biggestType(typeSum1);
    printf("In day number %d:\n", day+1);
    printf("The sales total was %d\n",totalSum);
    printf("The best sold brand with %d sales was ", brandSum2);
    // printing the name of the most profitable brand by sending his position
    getBrandName(biggerBrand);
    printf("\n");
    printf("The best sold type with %d sales was ", typeSum1[typeSumPos]);
    // printing the name of the most profitable type by sending his position
    getTypeName(typeSumPos);
    printf("\n\n");
}
// func that printing the types values for each brand day by day
void totalSalesDay(int lay, int row, int cou,int cube[lay][row][cou], int days[]) {
    printf("*****************************************\n\n");
    // brand by brand
    for (int i = 0; i < row; i++) {
        printf("Sales for ");
        // func that printing the brand name by receiving his position
        getBrandName(i);
        printf(":\n");
        // day by day
        //printf("%d", days[i]);
        for (int j = 0; j < days[i]; j++) {
            printf("Day %d- ", j+1);
            // type by type
            for (int k = 0; k < cou; k++) {
                // func that printing the type name by receiving his position
                getTypeName(k);
                printf(": ");
                // print the type value
                printf("%d ", cube[j][i][k]);
            }
            printf("\n");
        }
        printf("\n");
    }
    printf("*****************************************\n");
}
// function that print the bestseller day,brand and type of all time
void bestOverall(int lay, int row, int cou,int cube[lay][row][cou],int day) {
    int overallBrand = 0, overallDay = 0;
    int positionDay = 0, positionType = 0, positionBrand = 0;
    // creating an arrays for each category. later those arrays will help us check who is the biggest value in them.
    int biggerDay[DAYS_IN_YEAR]={0};
    int biggerBrand[NUM_OF_BRANDS]={0};
    int biggerType[NUM_OF_TYPES]={0};
    // going through every day->brand->types
    for (int i = 0; i < day; i++) {
        for (int j = 0; j < row; j++) {
            overallBrand=0;
            for (int k = 0; k < cou; k++) {
                if(cube[i][j][k] != -1) {
                    // summering the daily profits of a brand
                    overallBrand += cube[i][j][k];
                    /*
                     calculate the sum of a type and input him in an array.
                     every brand round k is reset and the type profit is added to the same type position
                     of the brand before him
                    */
                    biggerType[k] += cube[i][j][k];
                }
            }
            // inserting every brand total sum to an array, the position is the same position as the brand in brands
            biggerBrand[j] += overallBrand;
            // summering the total of all brands in a day
            overallDay += overallBrand;
        }
        // inserting every day total sum to an array, the position is the same position as the day in days
        biggerDay[i] = overallDay;
        overallDay=0;
    }
    // function that return the position of the most profitable day
    positionDay = biggestDay(biggerDay, day);
    // function that return the position of the most profitable brand
    positionBrand= biggestBrand(biggerBrand);
    // function that return the position of the most profitable type
    positionType= biggestType(biggerType);
    printf("The best-selling brand overall is ");
    // printing the most profitable brand name by sending him the returned position from earlier
    getBrandName(positionBrand);
    printf(": %d$\n", biggerBrand[positionBrand]);
    printf("The best-selling type of car is ");
    // printing the most profitable type name by sending him the returned position from earlier
    getTypeName(positionType);
    printf(": %d$\n", biggerType[positionType]);
    // printing the day number and his profits
    printf("The most profitable day was day number %d: %d$\n", positionDay+1, biggerDay[positionDay]);
}
//func that receive an array, each place in the array presented a profit of a specific brand(day 2 == position 2)
void avaregeCalculate(int daySum[], int day, int days[]) {
    float metAvr=0;
    int totalSum = 0;
    int x = 0;
    // going through the array from last to first and reduce the value of the day before him
    for (int i = days[x]-1; i > 0 ; i--) {
        if (daySum[i] > 0) {
            // calculate the sum of all the reducing
            totalSum += daySum[i] - daySum[i-1];
            x++;
        }
    }
    // divide the total sum with the number of days minus one. (explicit to float)
    metAvr = (float)totalSum / (float)(days[day]- 1);
    printf("%f\n", metAvr);
}
// function that arrange all days profits by brand, for calculate later what is the delta metrics of a brand
void deltaMetrics(int lay, int row, int cou,int cube[lay][row][cou],int day, int days[]) {
    int limDay = day+1;
    #define LIMIT_DAY limDay
    int dayBrandSum;
    // creating an array, in the array each position will present a daily profit of a brand.
    int metricSaver[LIMIT_DAY];
    for (int i = 0; i < row; i++) {
        for (int q = 0; q < LIMIT_DAY; q++) {
            // resetting the array before any new brand
            metricSaver[q] = 0;
        }
        printf("Brand: ");
        // printing the brand name
        getBrandName(i);
        printf(", Average Delta: ");
        for (int j = 0; j < days[j]; j++) {
            // resetting the day sum variable before calculating a new day
            dayBrandSum = 0;
            for (int k = 0; k < cou; k++) {
                if (cube[j][i][k] != -1) {
                    // calculate the total day profit of a brand
                    dayBrandSum += cube[j][i][k];
                }
            }
            // each day profit sum is inserted to a position in the array(day0-position0, day1-position1...)
            metricSaver[j] = dayBrandSum;
        }
        // sending the array and the brand position to a function that calculate the sum and eventually print it
        avaregeCalculate(metricSaver,i, days);
    }

}

