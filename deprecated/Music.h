#ifndef _MUSIC_H_
#define _MUSIC_H_

#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include "TimerDriver.h"

#include "DAC.h"

#define C_2 19111   // 65.406 Hz			
#define DF_1 18039   // 69.296 Hz			
#define D_1 17026   // 73.416 Hz			
#define EF_1 16071   // 77.782 Hz			
#define E_1 15169   // 82.407 Hz			
#define F_1 14317   // 87.307 Hz			
#define GF_1 13514   // 92.499 Hz			
#define G_1 12755   // 97.999 Hz			
#define AF_1 12039   // 103.826 Hz			
#define A_1 11364   // 110.000 Hz			
#define BF_1 10726   // 116.541 Hz			
#define B_1 10124   // 123.471 Hz			
#define C_1 9556   // 130.813 Hz			
#define DF0 9019   // 138.591 Hz			
#define D0 8513   // 146.832 Hz			
#define EF0 8035   // 155.563 Hz			
#define E0 7584   // 164.814 Hz			
#define F0 7159   // 174.614 Hz			
#define GF0 6757   // 184.997 Hz			
#define G0 6378   // 195.998 Hz			
#define AF0 6020   // 207.652 Hz			
#define A0 5682   // 220.000 Hz			
#define BF0 5363   // 233.082 Hz			
#define B0 5062   // 246.942 Hz			
#define C0 4778   // 261.626 Hz			
#define DF 4510   // 277.183 Hz			
#define D 4257   // 293.665 Hz			
#define EF 4018   // 311.127 Hz			
#define E 3792   // 329.628 Hz			
#define F 3579   // 349.228 Hz			
#define GF 3378   // 369.994 Hz			
#define G 3189   // 391.995 Hz			
#define AF 3010   // 415.305 Hz			
#define A 2841   // 440.000 Hz			
#define BF 2681   // 466.164 Hz			
#define B 2531   // 493.883 Hz			
#define C 2389   // 523.251 Hz			
#define DF1 2255   // 554.365 Hz			
#define D1 2128   // 587.330 Hz			
#define EF1 2009   // 622.254 Hz			
#define E1 1896   // 659.255 Hz			
#define F1 1790   // 698.456 Hz			
#define GF1 1689   // 739.989 Hz			
#define G1 1594   // 783.991 Hz			
#define AF1 1505   // 830.609 Hz			
#define A1 1420   // 880.000 Hz			
#define BF1 1341   // 932.328 Hz			
#define B1 1265   // 987.767 Hz			
#define C1 1194   // 1046.502 Hz			
#define DF2 1127   // 1108.731 Hz			
#define D2 1064   // 1174.659 Hz			
#define EF2 1004   // 1244.508 Hz			
#define E2 948   // 1318.510 Hz			
#define F2 895   // 1396.913 Hz			
#define GF2 845   // 1479.978 Hz			
#define G2 797   // 1567.982 Hz			
#define AF2 752   // 1661.219 Hz			
#define A2 710   // 1760.000 Hz			
#define BF2 670   // 1864.655 Hz			
#define B2 633   // 1975.533 Hz			
#define C2 597   // 2093.005 Hz			


#define bus 80000000
#define sxth 		bus / 16
#define eighth 	2  * sxth
#define quarter 4  * sxth
#define half 		8  * sxth
#define whole 	16 * sxth

typedef uint16_t Sound;

struct Note{
	Sound currSound;
	int length;
};

struct MySong {
	int bpm;
	struct Note* notes; //these are all my notes that I play (eg. A B C D E F G A)
	const unsigned short* instrument; //This is the "voice" I play the  note with
	int songLen; // length  of my song -- number of items in my notes array
	int notePointer;
	int instrumentPointer;
};


typedef struct {
	//TODO: Create song struct here
	//uint16_t songVals[155] = {};
	struct Note notes[150];	
} Song;

extern const Sound Wave[64];

void Music_Init(void);

//You will need public functions Rewind, Play and Stop, which perform operations like a cassette tape player
void Play(void);

void Rewind(void);

void Stop(void);


#endif
