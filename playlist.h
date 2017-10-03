#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct song {
	char *title;
	char *artist;
	int minutes;
	int seconds;
	struct song *next;
} Song;

////////////////////////////////////////////////////////////////////////////////////////

typedef struct playlist {
	char *name;
	Song *songlist;
	struct playlist *next;
} Playlist;

////////////////////////////////////////////////////////////////////////////////////////

Playlist* add(Playlist *, char *);
void addSong(Playlist *, char *, char *, char *, int, int );
void printSongs(Playlist *, char *);
void printSize(Playlist *, char *);
void printStats(Playlist *);
Playlist* addOrdered(Playlist *, char *);
void addSongOrdered(Playlist *, char *, char *, char *, int, int);
void removeSong(Playlist *, char *, char *, char *);
Playlist *removeList(Playlist *, char *);

////////////////////////////////////////////////////////////////////////////////////////
