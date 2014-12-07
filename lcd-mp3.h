/*
 * header file for lcd-mp3.c
 *
 * John Wiggins
 */

// for thread
#include <pthread.h>
// for mp3 playing
#include <ao/ao.h>
#include <mpg123.h>
// for id3
#include <sys/types.h>

#include <ncurses.h>

// # defines:
#ifndef	TRUE
#  define	TRUE	(1==1)
#  define	FALSE	(1==2)
#endif

#define MAXDATALEN 256

// Mount enum
typedef enum {
	UNMOUNTED,
	MOUNTED,
	MOUNT_ERROR
} mount_enum;


typedef enum {
	TITLE,
	ARTIST,
	GENRE,
	ALBUM,
	BASE_FILENAME,
	FILENAME
} song_enum; 

typedef enum {
	PLAY,
	PREV,
	NEXT,
	PAUSE,
	INFO,
	STOP,
	QUIT
} status_enum;

// playlist
typedef struct playlist_node {
  int index;
  void *songptr;
  struct playlist_node *nextptr;
} playlist_node_t;

typedef playlist_node_t *playlist_t;

struct song_info {
	char title[MAXDATALEN];
	char artist[MAXDATALEN];
	char genre[MAXDATALEN];
	char album[MAXDATALEN];
	char second_row_text[MAXDATALEN];
	char base_filename[MAXDATALEN];
	char filename[MAXDATALEN];
	char scroll_firstRow[32];
	char scroll_secondRow[32];
	int song_number;
	int song_over;
	int play_status;
	pthread_mutex_t pauseMutex;
	pthread_mutex_t writeMutex;
	pthread_cond_t m_resumeCond;
}; struct song_info cur_song;

// TODO use this somewhere... because right now it's not being used.
struct play_status {
	int is_playing;
	int is_paused;
	int is_stopped;
	int song_over;
}; struct play_status cur_status;

// Musical note
static unsigned char musicNote[8] = {
	0b01111,
	0b01001,
	0b01001,
	0b11001,
	0b11011,
	0b00011,
	0b00000,
	0b00000,
};

static const char *spaces = "                    ";

// Variables for the LCD display
const int BS = 4;	// Bits (4 or 8)
const int CO = 16;	// Number of columns
const int RO = 2;	// Number of rows
const int RS = 3;	// 
const int EN = 14;	// 
const int D0 = 4;	// 
const int D1 = 12;	// 
const int D2 = 13;	// 
const int D3 = 6;	// 

// Global lcd handle:
static int lcdHandle;

// Global vars
int num_songs; // current number of songs.

/*
// pthread
void nextSong();
void prevSong();
void quitMe();
void pauseMe();
void playMe();
void checkPause();

// ID3 stuff
void make_id(mpg123_string *inlines, int type);
int id3_tagger();

int usage(const char *progName);

// LCD scrolling
void scrollMessage_firstRow(void);
void scrollMessage_secondRow(void);

// threaded function that plays the music
void *play_song(void *arguments);

// Playlist
int playlist_init(playlist_t *playlistptr);
int playlist_add_song(int index, void *songptr, playlist_t *playlistptr);
int playlist_get_song(int index, void **songptr, playlist_t *playlistptr);
*/