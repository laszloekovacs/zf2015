//
//  world.c
//  zf2015
//
//  Created by Laszlo Kovacs on 10/11/2015.
//  Copyright (c) 2015 Swipe_06. All rights reserved.
//

#include "game.h"

uint8_t* mapfiledata;
uint8_t* cp;


void ParseSpawnInfo(uint8_t* s) {
	
	float x, y, z;
	float a, b, c;
	char	name[16];
	
	sscanf((char*)s, "s %f %f %f %f %f %f %s", &x, &y, &z, &a, &b, &c, name);
	
}


void LoadTextScene(char* path) {
	
	mapfiledata = FS_CacheFile(path);
	
	cp = mapfiledata;
	
	switch (*cp) {
		case 's':
			ParseSpawnInfo(cp);
			break;
			
		default:
			GLOBAL_ASSERT(0);
			break;
	}
}