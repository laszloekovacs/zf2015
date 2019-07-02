//
//  fs.c
//  zf2015
//
//  Created by Laszlo Kovacs on 03/11/2015.
//  Copyright (c) 2015 Swipe_06. All rights reserved.
//

#include "game.h"

#define DEVELOPER_DIR	"/Users/m3lvin/Desktop/source"






void FS_Init(void) {
	
	uint32_t result;
	
	
	result = chdir(DEVELOPER_DIR);
	
	if (result) {
		printf("chdir failed: %d", result);
		OS_Exit();
	}
	
}





void* FS_CacheFile(char* path) {
	
	uint8_t*	data;
	FILE*		fp = NULL;
	uint64_t	filesize = 0;
	uint64_t	bytesread = 0;
	
	
	fp = fopen(path, "r");

	GLOBAL_ASSERT(fp);
	
	
	fseek(fp, 0, SEEK_END);
	filesize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	
	
	
	// alloc enough space for reading
	data = malloc(filesize);
	
	
	
	bytesread = fread(data, 1, filesize, fp);
	
	
	GLOBAL_ASSERT(!(bytesread - filesize));
	
	fclose(fp);
	
	return (void*)data;
}



