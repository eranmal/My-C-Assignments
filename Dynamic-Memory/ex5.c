#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DESCENDING 0
#define ASCENDING 1
#define BY_YEAR 0
#define BY_STREAMS 1

// struct of the songs
typedef struct Song {
    char* title;
    char* artist;
    int year;
    char* lyrics;
    int streams;
} Song;
// struct of a playlist that contain songs
typedef struct Playlist {
    char* name;
    Song** songs;
    int songsNum;
} Playlist;
// struct of spotify that contain playlists
typedef struct Spotify {
    Playlist** playlist;
    int numOfPlaylists;
}Spotify;

// explanation for each function is after the main
void freePlaylist(Playlist* playlists);
void printPlaylistsMenu();
void sortPlaylist(Playlist* playlists,int* sortArray ,int currentPlace,int size, int direction);
void addSong(Playlist* playlists, int songPlace);
void showPlaylist(Playlist* playlists);
char* insertUnlimited();
void cleanBuffer();
int* arrayForSort(Playlist* playlists, int task);
void showPlaylistSongs(Playlist* playlists);

int main() {
    int playlistNum = 0;
    // creating a new pointer to a spotify
    Spotify* spotify = NULL;
    int task = -1;
    do
    {
        printPlaylistsMenu();
        scanf("%d", &task);
        //cleaning the \n after the chosen number,(in this program after every number receiving their will be cleaning)
        cleanBuffer();
        // if the user chose to leave, freeing the spotify if it's not empty
        if (task == 4) {
            if(playlistNum != 0 || spotify != NULL) {
                // freeing with a function every playlist in spotify
                for (int i = 0; i < playlistNum; i++) {
                    freePlaylist(spotify->playlist[i]);
                }
                // free the playlist himself
                free(spotify->playlist);
            }
            // free spotify and exit
            free(spotify);
            printf("Goodbye!\n");
            break;
        }
        {
            switch (task) {
                // view playlists
                case 1: {
                    int numOfPlaylist=-1;
                    // keep showing the playlist until the user chose to exit, choose the number of playlists +1
                    while(playlistNum+1 != numOfPlaylist) {
                        printf("Choose a playlist: \n");
                        // printing every playlist name
                        for (int i = 0; i < playlistNum; i++) {
                            printf("\t%d. ", i + 1);
                            printf("%s\n", spotify->playlist[i]->name);
                        }
                        printf("\t %d. Back to main menu\n", playlistNum +1);
                        scanf("%d", &numOfPlaylist);
                        cleanBuffer();
                        // keep asking for valid input from the user(between 0 to the number of playlists +1)
                        while (playlistNum+1 < numOfPlaylist || numOfPlaylist<=0) {
                            printf("Invalid option\n");
                            scanf("%d", &numOfPlaylist);
                            cleanBuffer();
                        }
                        // if the user chose to exit
                        if (playlistNum+1 == numOfPlaylist) {
                            break;
                        }else {
                            // show the playlist the user chose
                            showPlaylist(spotify->playlist[numOfPlaylist-1]);
                        }
                    }
                    break;
                }
                // adding new playlist
                case 2: {
                    char* namePlaylist = NULL;

                    // initialize Spotify if it's the first playlist inserted
                    if (spotify == NULL) {
                        // allocate a memory in the size of Spotify
                        spotify = (Spotify*)malloc(sizeof(Spotify));
                        if (spotify == NULL) {
                            printf("Memory allocation failed!\n");
                            exit(1);
                        }
                        // initialize the spotify values
                        spotify->playlist = NULL;
                        spotify->numOfPlaylists = 0;
                    }
                    // rising the number of playlists value
                    spotify->numOfPlaylists += 1;
                    // create a temporary spotify for the memory allocation
                    Spotify* newSpotify = spotify;
                    // resize the spotify memory allocation by the size of Playlist
                    newSpotify->playlist = realloc(spotify->playlist, spotify->numOfPlaylists * sizeof(Playlist*));
                    if (newSpotify->playlist == NULL) {
                        printf("Memory allocation failed!\n");
                        exit(1);
                    }
                    // after the memory allocated safely point our spotify to the temporary one
                    spotify->playlist = newSpotify->playlist;
                    // allocate a memory for the new playlist himself
                    spotify->playlist[spotify->numOfPlaylists - 1] = (Playlist*)malloc(sizeof(Playlist));
                    if (spotify->playlist[spotify->numOfPlaylists - 1] == NULL) {
                        printf("Memory allocation failed!\n");
                        exit(1);
                    }
                    // initialize the new playlist values
                    spotify->playlist[spotify->numOfPlaylists - 1]->name = NULL;
                    spotify->playlist[spotify->numOfPlaylists - 1]->songs = NULL;
                    spotify->playlist[spotify->numOfPlaylists - 1]->songsNum = 0;

                    printf("Enter playlist's name:\n");
                    // entering unlimited name for the new playlist by a function
                    namePlaylist = insertUnlimited();
                    spotify->playlist[spotify->numOfPlaylists - 1]->name = namePlaylist;
                    // rising the number of playlist by one
                    playlistNum ++;
                    break;
                }
                // deleting a whole playlist
                case 3:{
                    int deletedPlayList;
                    printf("Choose a playlist: \n");
                    // printing the names of the playlists
                    for (int i = 0; i < playlistNum; i++) {
                        printf("\t%d. ", i + 1);
                        printf("%s\n", spotify->playlist[i]->name);
                    }
                    printf("\t%d. Back to main menu\n", playlistNum +1);
                    scanf("%d", &deletedPlayList);
                    cleanBuffer();
                    while (playlistNum+1 < deletedPlayList || deletedPlayList<=0) {
                        printf("Invalid option\n");
                        scanf("%d", &deletedPlayList);
                        cleanBuffer();
                    }
                    if (playlistNum + 1 == deletedPlayList) {
                        break;
                    }
                    // using a function to free the chosen playlist
                    freePlaylist(spotify->playlist[deletedPlayList-1]);
                    // each pointer, from the deleted one, will point to the playlist before him
                    for (int i = deletedPlayList-1; i < spotify->numOfPlaylists; i++) {
                        spotify->playlist[i] = spotify->playlist[i+1];
                    }
                    // change the number of playlists
                    spotify->numOfPlaylists--;
                    playlistNum--;

                    // if this was the last playlist
                    if (spotify->numOfPlaylists == 0) {
                        free(spotify->playlist);
                        spotify->playlist = NULL;
                    } else {
                        // reallocate memory for the remaining playlists
                        Playlist** tempPlaylist=realloc(spotify->playlist, spotify->numOfPlaylists * sizeof(Playlist*));
                        if (tempPlaylist == NULL && spotify->numOfPlaylists > 0) {
                            printf("Memory allocation failed!\n");
                            exit(1);
                        }
                        spotify->playlist = tempPlaylist;
                    }

                    printf("Playlist deleted.\n");
                    break;
                }

                default:
                    printf("Please choose a task number from the list.\n");
                break;
            }
        }
    } while (task != 4);
    return 0;
}

// function for cleaning the buffer until new line or end of input
void cleanBuffer() {
    int cleanChar;
    while ((cleanChar = getchar()) != '\n' && cleanChar != EOF);
}
// function for free a whole playlist
void freePlaylist(Playlist* playlists) {
    // freeing every song in the playlist value by value
    for(int i=0; i<playlists->songsNum; i++) {
        free(playlists->songs[i]->artist);
        free(playlists->songs[i]->title);
        free(playlists->songs[i]->lyrics);
        free(playlists->songs[i]);
    }
    // freeing the songs, name and the playlist himself
    free(playlists->songs);
    free(playlists->name);
    free(playlists);
}
// function for printing the menu
void printPlaylistsMenu() {
    printf("Please Choose:\n");
    printf("\t1. Watch playlists\n\t2. Add playlist\n\t3. Remove playlist\n\t4. exit\n");
}
//function for sorting playlist songs. the function receive an array with the values and sorting according to the array
void sortPlaylist(Playlist* playlists,int* sortArray ,int currentPlace,int size, int direction) {
    if(sortArray == NULL) {return;}
    // this function sorting descending and ascending by the value of direction
    Song* tempSong = NULL;
    // keep sorting until the whole playlist sorted
    while(currentPlace != size) {
        //each value sorted by the values after him in the array, and that's how the all array sorted
        for (int i = currentPlace; i < size; i++) {
            // if the user chose descending(by year or streams)
            if(direction == DESCENDING) {
                // if a value is bigger from the current value they will change places
                if (sortArray[i] > sortArray[currentPlace]) {
                    //swap the songs by using a temporary pointer
                    tempSong = playlists->songs[currentPlace];
                    playlists->songs[currentPlace] = playlists->songs[i];
                    playlists->songs[i] = tempSong;
                    // and also swap the values in the arrays himself
                    int tempValue = sortArray[currentPlace];
                    sortArray[currentPlace] = sortArray[i];
                    sortArray[i] = tempValue;
                }
            // if the user chose sort by streams ascending, the same actions just for the new term
            }else if (direction == ASCENDING) {
                if (sortArray[i] < sortArray[currentPlace]) {
                    // swapping the pointers and then the values in the array himself
                    tempSong = playlists->songs[i];
                    playlists->songs[i] = playlists->songs[currentPlace];
                    playlists->songs[currentPlace] = tempSong;
                    int tempValue = sortArray[i];
                    sortArray[i] = sortArray[currentPlace];
                    sortArray[currentPlace] = tempValue;                }
            }
        }
        // moving to the next value in the array
        currentPlace++;
    }
}
// function for adding songs, the function receive the playlist himself and the location of the new song
void addSong(Playlist* playlists, int songPlace) {
    // initialize pointers for each value in Songs and year venerable
    char* songTitle = NULL;
    char* songArtist = NULL;
    char* songLyrics = NULL;
    int year;
    // for each value in the new song receiving unlimited characters from the user using a function
    printf("Enter song's details\n");
    printf("Title: \n");
    songTitle = insertUnlimited();
    printf("Artist: \n");
    songArtist = insertUnlimited();
    printf("Year of release: \n");
    scanf("%d", &year);
    cleanBuffer();
    printf("Lyrics: \n");
    songLyrics = insertUnlimited();
    // insert each value to his proper location in the new song
    playlists->songs[songPlace]->title = songTitle;
    playlists->songs[songPlace]->artist = songArtist;
    playlists->songs[songPlace]->year = year;
    playlists->songs[songPlace]->lyrics = songLyrics;
    playlists->songs[songPlace]->streams= 0;
}
// function for receiving unlimited characters from the user, the func return an array
char* insertUnlimited() {
    char* resizeArray = NULL;
    int place = 0, sizeOfArray = 1;
    char newChar;
    // allocate memory for the array
    resizeArray = (char*)malloc(sizeOfArray * sizeof(char));
    if (resizeArray == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    // skip all new lines before the input that different from \n
    while ((newChar = getchar()) == '\n' || newChar == EOF) {}
    // keep adding characters to the array until \n, and reallocate the size of the array if necessary
    do {
        //  check if the array need to reallocate
        if (place + 1 >= sizeOfArray) {
            sizeOfArray += 1;
            // increasing the size of the array
            char* temp = realloc(resizeArray, sizeOfArray * sizeof(char));
            if (temp == NULL) {
                printf("Memory reallocation failed!\n");
                exit(1);
            }
            resizeArray = temp;
        }
        // add the new character to the array
        resizeArray[place++] = newChar;
    } while ((newChar = getchar()) != '\n' && newChar != EOF && newChar != '\r');

    // adding one more place at the end of the array for '\0'
    if (place + 1 > sizeOfArray) {
        char* temp = realloc(resizeArray, (place + 1) * sizeof(char));
        if (temp == NULL) {
            printf("Memory reallocation failed!\n");
            exit(1);
        }
        resizeArray = temp;
    }
    // adding '\0' to the end of the array
    resizeArray[place] = '\0';
    return resizeArray;
}
// func to enter the values of streams/year in an array for the sorting later
int* arrayForSort(Playlist* playlists, int task) {
    int* sortArray = NULL;
    // allocate memory for array
    sortArray = (int*)malloc(playlists->songsNum*sizeof(int));
    if (sortArray == NULL) {
        printf("Memory reallocation failed!\n");
        exit(1);
    }
    // each year/streams of a song will be in the same place as the song himself in the playlist
    for (int i = 0; i < playlists->songsNum; i++) {
        // if the user chose to sort by year
        if(task == BY_YEAR ) {
            sortArray[i] = playlists->songs[i]->year;
        // if the user chose to sort by streams
        }else if(task == BY_STREAMS) {
            sortArray[i] = playlists->songs[i]->streams;
        }
    }
    return sortArray;
}
// function for printing the song details
void showPlaylistSongs(Playlist* playlists) {
    for (int i = 0; i < playlists->songsNum; i++) {
        printf("%d. Title: %s\n", i + 1, playlists->songs[i]->title);
        printf("   Artist: %s\n",playlists->songs[i]->artist);
        printf("   Released: %d\n",playlists->songs[i]->year);
        printf("   Streams: %d\n",playlists->songs[i]->streams);
    }
}
// function for showing and applying all the options the user can do inside a playlist
void showPlaylist(Playlist* playlists) {
    int task = -1;
    // print the chosen playlist name
    printf("playlist %s:\n", playlists->name);
    // keep running until the user choose to exit
    do {
        printf("\t1. Show Playlist\n\t2. Add Song\n\t3. Delete Song\n\t4. Sort\n"
               "\t5. Play\n \t6. exit\n");
        scanf("%d", &task);
        cleanBuffer();
        switch (task) {
            // showing all the songs in a playlist and playing a specific song
            case 1: {
                int songNumber=-1;
                // printing every song values
                showPlaylistSongs(playlists);
                // keep letting the user the option of playing a new playlist until he wants to exit
                while (songNumber != 0) {
                    printf("choose a song to play, or 0 to quit:\n");
                    scanf(" %d", &songNumber);
                    cleanBuffer();
                    // if there is no songs in the playlist or the user wanted to exit
                    if (playlists->songsNum == 0 || songNumber == 0) {
                        break;
                    }
                    while (songNumber<0 || songNumber > playlists->songsNum) {
                        printf("choose a song to play, or 0 to quit:\n");
                        scanf("%d", &songNumber);
                        cleanBuffer();
                    }
                    if(songNumber == 0) {
                        break;
                    }
                    // printing the title and lyrics of the wanted song, and rising the value of his streams
                    printf("Now playing %s:\n", playlists->songs[songNumber-1]->title);
                    printf("$ %s $\n", playlists->songs[songNumber-1]->lyrics);
                    playlists->songs[songNumber-1]->streams +=1;
                }
                break;
            }
            // add song
            case 2: {
                playlists->songsNum += 1;
                Song** tempSongs = realloc(playlists->songs, playlists->songsNum* sizeof(Song*));
                //rising the number of songs and allocating a bigger place for the new song
                if (tempSongs == NULL) {
                    printf("Memory allocation failed!\n");
                    exit(1);
                }
                playlists->songs = tempSongs;
                // allocate memory for the new song
                playlists->songs[playlists->songsNum - 1] = (Song*)malloc(sizeof(Song));
                if (playlists->songs[playlists->songsNum - 1] == NULL) {
                    printf("Memory allocation failed!\n");
                    exit(1);
                }
                // add the new song using a function
                addSong(playlists, playlists->songsNum - 1);
                break;
            }
            //delete a song
            case 3: {
                int deletedNum=0;
                // printing all the songs values
                showPlaylistSongs(playlists);
                printf("choose a song to delete, or 0 to quit:\n");
                scanf("%d", &deletedNum);
                cleanBuffer();
                deletedNum = deletedNum%10;
                // if the user chose to exit
                if (playlists->songsNum == 0 || deletedNum == 0) {
                    break;
                }
                while (deletedNum < 0 || deletedNum > playlists->songsNum) {
                    printf("choose a song to delete, or 0 to quit:\n");
                    scanf("%d", &deletedNum);
                    cleanBuffer();
                }
                if(deletedNum == 0) {break;}
                // if the user chose to delete the last song
                if (playlists->songsNum == 1 && deletedNum == playlists->songsNum) {
                    playlists->songsNum -= 1;
                    free(playlists->songs[0]->artist);
                    free(playlists->songs[0]->title);
                    free(playlists->songs[0]->lyrics);
                    free(playlists->songs[0]);
                    free(playlists->songs);
                    printf("Song deleted successfully.\n");
                    break;
                }
                // free the last song pointer values
                Song* songToDelete = playlists->songs[deletedNum-1];
                free(songToDelete->title);
                free(songToDelete->artist);
                free(songToDelete->lyrics);
                free(songToDelete);

                // every song after the deleted one his pointer will be the pointer of the song before him
                for (int i = deletedNum-1; i < playlists->songsNum-1; i++) {
                    playlists->songs[i] = playlists->songs[i+1];
                }

                // update the song number
                playlists->songsNum--;
                // reallocate the playlist for the new size after the delete, using temporary pointer
                Song** tempPlaylist = realloc(playlists->songs, playlists->songsNum * sizeof(Song*));
                if (tempPlaylist == NULL) {
                    printf("Memory reallocation failed.\n");
                    break;
                }
                playlists->songs = tempPlaylist;
                printf("Song deleted successfully.\n");
                break;
            }
            // sorting
            case 4: {
                int sortType =0;
                printf("choose:\n1. sort by year\n2. sort by streams - ascending order\n"
                       "3. sort by streams - descending order\n4. sort alphabetically\n");
                scanf("%d", &sortType);
                cleanBuffer();
                if (playlists->songsNum == 0) {
                    printf("sorted\n");
                    break;
                }
                if (sortType == 1) {
                    // if the user chose to sort by the year
                    int *yearArray= NULL;
                    // if the user chose to sort according to the years song
                    yearArray = arrayForSort(playlists, BY_YEAR);
                    // sort the playlist using the function of sorting
                    sortPlaylist(playlists, yearArray, 0, playlists->songsNum, ASCENDING);
                    free(yearArray);
                    printf("sorted\n");
                    break;
                }else if (sortType == 2 || sortType == 3) {
                    // if the user chose to sort according to the streams
                    int *streamArray= NULL;
                    streamArray = arrayForSort(playlists, BY_STREAMS);
                    // if the user chose to sort ascending
                    if (sortType == 2) {
                        sortPlaylist(playlists, streamArray, 0, playlists->songsNum, ASCENDING);
                    // if the user chose to sort descending
                    }else {
                        sortPlaylist(playlists, streamArray, 0, playlists->songsNum, DESCENDING);
                    }
                    free(streamArray);
                    printf("sorted\n");
                    break;
                }
                // the default is sorting alphabetic
                Song* tempSong = NULL;
                int currentPlace = 0;
                // while the function didn't relate to every song
                while (currentPlace != playlists->songsNum) {
                    /*
                    every song in the current place will be sorted according to all the song after him
                    because the first current place is 0, in every other current place all the song before him
                    already sorted properly
                    */
                    for (int i = 0; i < playlists->songsNum - currentPlace - 1; i++) {
                        // compare the songs name using strcmp
                        if (strcmp(playlists->songs[i]->title, playlists->songs[i + 1]->title) > 0) {
                            // if the word in the next place is bigger from the current, replace them
                            tempSong = playlists->songs[i];
                            playlists->songs[i] = playlists->songs[i + 1];
                            playlists->songs[i + 1] = tempSong;
                        }
                    }
                    // moving to the next word index
                    currentPlace++;
                }
                free(tempSong);
                printf("sorted\n");
                break;
            }
            // play
            case 5: {
                // play all the songs by their order in the playlist
                for (int i = 0; i < playlists->songsNum; i++) {
                    printf("Now playing %s:\n", playlists->songs[i]->title);
                    printf("$ %s $\n", playlists->songs[i]->lyrics);
                    // rising the streams value to each song
                    playlists->songs[i]->streams += 1;
                }
                break;
            }
            case 6: {
                break;
            }
            default:
                printf("Invalid value\n");
                break;
        }
    } while (task != 6);
}
