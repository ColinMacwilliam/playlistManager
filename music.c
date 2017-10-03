#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "playlist.h"

typedef enum { ADD_LIST, ADD_SONG, PRINT_LIST, LIST_SIZE, STATS, ADD_LIST_ORDERED,
		ADD_SONG_ORDERED, REMOVE_SONG, REMOVE_LIST, HELP, QUIT, INVALID } Option;

Option getAction(void);
void printOptions(void);
void optionDetails(void);
char *getString(char *);
void getTime(int *, int *);


int main( int argc, char* argv[ ] ) {
	Playlist *myList = NULL;
	int minutes, seconds;
	char *name, *title, *artist;
	Option opt;

	printf("\n\nWelcome to project 5 - music playlists\n\n");
	opt = getAction();
	while (opt != QUIT) {
		switch (opt) {
			case ADD_LIST:
				printf("Adding a new playlist to start of library\n");
				name = getString("Enter the name of the new playlist");
				printf("\nAdding the playlist '%s' to your library (at front of library) \n", name);
				myList = add(myList, name);
				break;
			case ADD_SONG:
				printf("Add a song to an existing playlist\n");
				name = getString("Enter the name of the playlist");
				title = getString("Enter the title of the song to add");
				artist = getString("Enter the name of the artist");
				getTime(&minutes, &seconds);
				printf("\nAdding the song below to the playlist '%s' (at end of playlist)\n", name);
				printf("\tTitle : %s\n", title);
				printf("\tArtist: %s\n", artist);
				printf("\tLength: %d:%d\n", minutes, seconds);
				addSong(myList, name, title, artist, minutes, seconds);
				break;
			case PRINT_LIST:
				printf("Print the songs in a playlist\n");
				name = getString("Enter the name of the playlist");
				printf("\nPrinting the names of all songs in the playlist '%s'\n", name);
				printSongs(myList, name);
				break;
			case LIST_SIZE:
				printf("Print the size of a playlist\n");
				name = getString("Enter the name of the playlist");
				printf("\nThe playlist '%s' contains N songs and has NN:NN minutes of music\n", name);
				printSize(myList, name);
				break;
			case STATS:
				printf("Print statistics on all your playslists\n");
				printStats(myList);
				break;
			case ADD_LIST_ORDERED:
				printf("Adding a new playlist to library (ordered)\n");
				name = getString("Enter the name of the new playlist");
				printf("\nAdding the playlist '%s' to your library (in alphabetical order)\n", name);
				myList = addOrdered(myList, name);
				break;
			case ADD_SONG_ORDERED:
				printf("Add a song to an existing playlist (ordered)\n");
				name = getString("Enter the name of the playlist");
				title = getString("Enter the title of the song to add");
				artist = getString("Enter the name of the artist");
				getTime(&minutes, &seconds);
				printf("\nAdding the song below to the playlist '%s' (in alphabetical order)\n", name);
				printf("\tTitle : %s\n", title);
				printf("\tArtist: %s\n", artist);
				printf("\tLength: %d:%d\n", minutes, seconds);
				addSongOrdered(myList, name, title, artist, minutes, seconds);
				break;
			case REMOVE_SONG:
				printf("Removing a song from an existing playlist\n");
				name = getString("Enter the name of the playlist");
				title = getString("Enter the title of the song to remove");
				artist = getString("Enter the artist of the song to remove");
				printf("\nRemoving the song '%s' by '%s' from the playlist %s\n", title, artist, name);
				removeSong(myList, name, title, artist);
				break;
			case REMOVE_LIST:
				printf("Removing a playlist\n");
				name = getString("Enter the name of the playlist to remove");
				printf("\nRemoving the the playlist %s from your library\n", name);
				myList = removeList(myList, name);
				break;
			case HELP:
				optionDetails();
				break;
			default: break;
		}
		opt = getAction();
	}
	return 0;
}

Option getAction(void) {
	// print the list of options
	printOptions();
	Option answer = INVALID;

	while (answer == INVALID) {
		// read the user command
		char input[32];
		fgets(input, 31, stdin);
		input[strlen(input)-1] = '\0';

		// update answer
		if (strcmp(input, "quit") == 0)			answer = QUIT;
		else if (strcmp(input, "addlist") == 0)		answer = ADD_LIST;
		else if (strcmp(input, "addsong") == 0)		answer = ADD_SONG;
		else if (strcmp(input, "show") == 0)		answer = PRINT_LIST;
		else if (strcmp(input, "size") == 0)		answer = LIST_SIZE;
		else if (strcmp(input, "stats") == 0)		answer = STATS;
		else if (strcmp(input, "addorder") == 0)	answer = ADD_LIST_ORDERED;
		else if (strcmp(input, "songorder") == 0)	answer = ADD_SONG_ORDERED;
		else if (strcmp(input, "dumplist") == 0)	answer = REMOVE_LIST;
		else if (strcmp(input, "dumpsong") == 0)	answer = REMOVE_SONG;
		else if (strcmp(input, "help") == 0)		answer = HELP;
		else {
			if (strlen(input)>0) {
				printf("\nINVALID OPTION\n");
				printOptions();
			}
		}
	}
	return answer;
}

void printOptions(void) {
	printf("\nOptions: addlist addsong show size stats addorder songorder dumplist dumpsong help quit\n");
	printf("Select an option: ");
}

void optionDetails(void) {
	printf("\nThe Options are:\n");
	printf("\taddlist    Create a new playlist (at start of library)\n");
	printf("\taddsong    Add a song to an existing playlist (at start of playlist)\n");
	printf("\tshow       Print the songs in a playlist\n");
	printf("\tsize       Print the size of a playlist (songs and time)\n");
	printf("\tstats      Print statistics on all your playlists\n");
	printf("\taddorder   Create a new playlist (in alphabetical order)\n");
	printf("\tsongorder  Add a song to an existing playlist (in alphabetical order)\n");
	printf("\tdumplist   Remove a song from your playlist\n");
	printf("\tdumpsong   Remove a playlist\n");
	printf("\thelp       Display this detailed menu\n");
	printf("\tquit       Exit the program\n");
}

char *getString(char *str) {
	char input[1024];
	printf("%s : ", str);
	fgets(input, 1023, stdin);
	input[strlen(input)-1] = '\0';	// get rid of \n character
	char *answer = (char *) malloc (strlen(input) + 1);
	strcpy(answer, input);
	return answer;
}

void getTime(int *min, int *sec) {
	char input[1024];
	printf("Enter the song time (in the format MM:SS) : ");
	fgets(input, 1023, stdin);
	input[strlen(input)-1] = '\0';	// get rid of \n character
	sscanf(input, "%d:%d", min, sec);
	return;
}

