#include "playlist.h"

/////////////////////////////////////////////////////////////////////////////////////////////
// add a new playlist to your list of playlists
Playlist* add(Playlist *theList, char *name) {
	/*
		1. Make sure a playlist by that name does not exist in your library
		2. Add a new playlist with that name (add-at-front)
	*/
				


		Playlist* ptr = (Playlist*)malloc(sizeof(Playlist));
		ptr = theList;
		
		int check = 0;

		while (ptr!=NULL) {
	
		if (strcmp(ptr->name, name) == 0) {
			check++;
			}
		ptr=ptr->next;
		}
		
		if (check == 0){
			Playlist* newplaylist = (Playlist*)malloc(sizeof(Playlist));
			newplaylist->name = (char*)malloc(strlen(name) + 1);
			strcpy(newplaylist->name, name);
			newplaylist->songlist = NULL;
			newplaylist->next = theList;
			return newplaylist;
		}


		else {
			printf("That is already a playlist!\n");
			return theList;
		}
	
		

}


/////////////////////////////////////////////////////////////////////////////////////////////
// adds a new song to the specified playlist
void addSong(Playlist *theList, char *name, char *title, char *artist, int minutes, int seconds) {
	/*
		1. Make sure a playlist by that name exists (so you can add a song to it)
		2. Make sure the song does not already exist in the playlist (title/artist)
		3. Add the new song to the end of the songlist in that playlist (add-at-end)
	*/

		
	Playlist* playptr = (Playlist*)malloc(sizeof(Playlist));
	playptr = theList;
	int checker = 0;
	while (playptr != NULL) {

		if (strcmp(playptr->name, name) == 0) {
		checker = 1;
		Song* search = (Song*)malloc(sizeof(Song));
		search = playptr->songlist;

		while (search != NULL) {
			if ((strcmp(search->title, title) == 0) && (strcmp(search->artist, artist) == 0)) {
				printf("That song already exists in this playlist!\n");
				return;
			}

		search = search->next;
		}	


		Song* ptr = (Song*)malloc(sizeof(Song));
		ptr = playptr->songlist;
		
	
	
		Song* newNode = (Song*)malloc(sizeof(Song));
		
		newNode->title = (char*)malloc(strlen(title)+1);
		newNode->artist = (char*)malloc(strlen(artist)+1);
		
		strcpy(newNode->title, title);
		strcpy(newNode->artist, artist);

		newNode->minutes = minutes;
		newNode->seconds = seconds;
		newNode->next = NULL;
	


		if (playptr->songlist == NULL) {

			playptr->songlist = newNode;
		
		}

		else {	

			while(ptr->next!=NULL) {
				

				ptr = ptr->next;
			}
		ptr->next = newNode;
		}


	}
playptr = playptr->next;
}
if (checker == 0) {
printf("That playlist does not exist.\n");
return;
}
}


/////////////////////////////////////////////////////////////////////////////////////////////
// prints all the songs in a given playlist
void printSongs(Playlist *theList, char *name) {
	/*
		1. Make sure a playlist by that name exists
		2. Print the name of hte playlist, then
		3. print each song on separate line (print song & title & time)
	*/
 
	Playlist *playlistPtr = theList;	
	Playlist *correctplayList = NULL;
	
	
	while (playlistPtr != NULL) {

		if (strcmp(playlistPtr->name, name) == 0) {
			correctplayList = playlistPtr;
			break;
		}
	playlistPtr = playlistPtr->next;
	}

if (correctplayList == NULL) {

	printf("That playlist does not exist.\n");
	return;
}

Song *song = correctplayList->songlist;


if (song == NULL) {
	printf("This playlist is empty.\n");
	return;
}


printf("Playlist: %s\n", correctplayList->name);

	while (song != NULL) {

	printf("Title: %s; Artist: %s; Time: %d:%02d", song->title, song->artist, song->minutes, song->seconds);
	printf("\n");

	song = song->next;
	}

}



/////////////////////////////////////////////////////////////////////////////////////////////
// prints the size of a given playlist
void printSize(Playlist *theList, char *name) {
	/*
		1. Make sure a playlist by that name exists
		2. Count the number of songs in the playlist and add up all their times
		3. Print the name of the playlist, the number of songs and the total time
	*/
	
	Playlist* ptr = theList;
	Playlist* correct = NULL;

	while (ptr!=NULL) {

		if (strcmp(ptr->name, name) == 0) {
			correct = ptr;
			break;
		}

	ptr = ptr->next;
	}
if (correct == NULL) {

	printf("That playlist does not exist.\n");
	return;
}

Song *songptr = correct->songlist;


if (songptr==NULL) {
	printf("This playlist (%s) is empty.\n", correct->name );
	return;
	}


	printf("Playlist: %s\n", correct->name);
int count = 0;
int totalmins = 0;
int totalsec = 0;
	while (songptr!=NULL) {
		count++;
		totalmins = totalmins + songptr->minutes;
		totalsec = totalsec + songptr->seconds;
		
			if (totalsec > 60) {
				totalmins = totalmins + 1;
				totalsec = totalsec - 60;
			}		


	songptr = songptr->next;	
	}
printf("Total songs: %d; total time: %d:%d", count, totalmins, totalsec);
printf("\n");

	return;
}


/////////////////////////////////////////////////////////////////////////////////////////////
// prints statistics on all your playlists
void printStats(Playlist *theList) {
	/*
		For each playlist in your library
		1. Count the number of songs that the playlist and add up all their times
		2. Print the name of the playlist, the number of songs and the total time
		Note: this code can call other functions (printSize) 
	*/
	
	Playlist* ptr = theList;

	while (ptr != NULL) {

	printSize(ptr, ptr->name);
	printf("\n");
ptr = ptr->next;
}

}


/////////////////////////////////////////////////////////////////////////////////////////////
// add a new playlist to your list of playlists (in alphabetical order)
Playlist* addOrdered(Playlist *theList, char *name) {
	/*
		1. Make sure a playlist by that name does not exist in your library
		2. Add a new playlist with that name (add-in-order)
	*/


	Playlist* newPlay = (Playlist*)malloc(sizeof(Playlist));

		newPlay->name = (char*)malloc(strlen(name)+1);
		strcpy(newPlay->name, name);
		newPlay->songlist = NULL;
		newPlay->next = NULL;	

	if (theList == NULL) {
		return newPlay;
	
	}
	



	
int result = strcmp(name, theList->name);

if (result < 0) {

	newPlay->next = theList;
	return newPlay;
	}


Playlist* cur;

for (cur = theList; cur!=NULL; cur=cur->next) {


	if (strcmp(name, cur->name) == 0) {
		printf("This playlist already exists.\n");
		return theList;
	}

	if (cur->next==NULL) {

		cur->next = newPlay;
		return theList;
	}

	if (strcmp(name, cur->next->name) < 0) {

		newPlay->next = cur->next;
		cur->next = newPlay;
		return theList;
	}

}


return NULL;
}


/////////////////////////////////////////////////////////////////////////////////////////////
// adds a new song to the specified playlist (in alphabetical order)
void addSongOrdered(Playlist *theList, char *name, char *title, char *artist, int minutes, int seconds) {
	/*
		1. Make sure a playlist by that name exists (so you can add a song to it)
		2. Make sure the the song (title/artist) does not already exist in playlist
		3. Add the new song to the songlist in that playlist (add-in-order)
	*/
	
	Playlist* head = theList;
	Playlist* correct = NULL;
	
if (head == NULL) {
	printf("This playlist does not exist.\n");
	return;
}
while (head != NULL) {

	if (strcmp(head->name, name) == 0) {
		correct = head;
		break;
	}
head = head->next;
}

if (correct == NULL) {

	printf("This playlist does not exist.\n");
	return;
}


Song* search = correct->songlist;

while (search != NULL) {

	if ((strcmp(search->title, title) == 0) && (strcmp(search->artist, artist) == 0)) {

		printf("This song already exists in this playlist!\n");
		return;
	}

search = search->next;
}

Song* ptr = (Song*)malloc(sizeof(Song));
ptr->title = (char*)malloc(strlen(title) + 1);
strcpy(ptr->title, title);
ptr->artist = (char*)malloc(strlen(artist) + 1);
strcpy(ptr->artist, artist);
ptr->minutes = minutes;
ptr->seconds = seconds;
ptr->next = NULL;

Song* head2 = correct->songlist;

	if (head2==NULL) {
		correct->songlist = ptr;
		return;
	}

if (strcmp(title, head2->title) < 0) {

correct->songlist = ptr;
ptr->next = head2;
return;

}

Song* cur;

for (cur = head2; cur!=NULL; cur=cur->next) {

	if (cur->next == NULL) {
		cur->next = ptr;
		return;
	}


	
	if (strcmp(title, cur->next->title) < 0) {

	ptr->next = cur->next;
	cur->next = ptr;
	return;

	}
}

return;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// remove a song from a playlist
void removeSong(Playlist *theList, char *name, char *title, char *artist) {
	/*
		1. Make sure a playlist by that name exists
		2. Make sure the song exists in that playlist (title/artist match)
		3. Remove the song from the list of songs in that playlist
	*/
	
Playlist* correctplay = theList;
int check = 0;

while (correctplay != NULL) {


if (strcmp(correctplay->name, name) == 0) {
	check = 1;
	break;
}

correctplay = correctplay->next;
}

if (check == 0) {
	printf("This playlist does not exist.\n");
	return;
}


Song* head = correctplay->songlist;

if (head == NULL) {
	printf("This playlist is empty.\n");
	return;
}

if ((strcmp(head->title, title) == 0) && (strcmp(head->artist, artist) == 0)) {
	Song* ptr = head->next;
	free(head);
	correctplay->songlist = ptr;
	return;
}


Song* prev = head;
Song* curr=head->next;

while ((curr != NULL) && (strcmp(curr->title, title)) && (strcmp(curr->artist, artist) != 0)) {

	prev = curr;
	curr = curr->next;
}

if (curr == NULL) {

	printf("This song does not exist in this playlist.\n");
	return;
}

prev->next = curr->next;
free(curr);

return;
}


/////////////////////////////////////////////////////////////////////////////////////////////
// remove a playlist
Playlist *removeList(Playlist *theList, char *name) {
	/*
		1. Make sure a playlist by that name exists
		2. Remove that playlist from your library
	*/
	

	if (theList == NULL) {
		return theList;
	}

if (strcmp(theList->name, name) == 0) {

	Playlist* ptr = theList->next;
	free(theList);
	return ptr;
}

Playlist* prev = theList;
Playlist* curr = theList->next;

while ((curr != NULL) && (strcmp(curr->name, name) != 0)) {

	prev = curr;
	curr = curr->next;
}

if (curr == NULL) {
	printf("This playlist does not exist.\n");
	return theList;
}

else {
	prev->next = curr->next;
	free(curr);
	return theList;
}

return theList;
}

/////////////////////////////////////////////////////////////////////////////////////////////
