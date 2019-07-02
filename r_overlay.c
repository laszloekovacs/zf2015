//
//  r_overlay.c
//  zf2015
//
//  Created by Laszlo Kovacs on 06/11/2015.
//  Copyright (c) 2015 Swipe_06. All rights reserved.
//

#include "game.h"


extern globalSegment_t gs;

int8_t* asciibits;


// pixel to uv ratios
float sd;
float td;



int8_t* loadRaw(char* path) {
	
	int8_t*	glymph;
	FILE*	fp = NULL;
	long	filesize;
	
	
	fp = fopen(path, "r");
	
	if (fp == NULL) {
		printf("debug font load failed\n");
		fclose(fp);
		return NULL;
	}
	
	
	fseek(fp, 0, SEEK_END);
	filesize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	
	glymph = malloc(filesize);
	
	fread(glymph, 1, filesize, fp);
	
	fclose(fp);
	
	return glymph;
}


void OverlayInit(void) {
	

	asciibits = loadRaw("font_bits.raw");

	// calculate pixel ratios
	sd = 1.0f / 400.0f;
	td = 1.0f / 150.0f;
}







/*
 * Print one character at a location
 * Returns the width of the glyph drawn (raster advancement)
 */
int PlotGlyph(unsigned int x, unsigned int y, char c) {
	
	
	//	GLubyte red, green, blue, alpha;
	float s0, t0;
	int row, col;
	
	
	// adjust character. we need to consider '!' as the 2nd char.
	c -= 32;
	
	// ugly hack. annoying space
	if (c == 0) {
		return 25;
	}
	
	// calculate the location of the character
	row = c / 16;
	col = c % 16;
	
	
	
	glBegin(GL_TRIANGLE_FAN);
	
	// bottom left
	s0 = sd * (col * 25);
	t0 = td * ((row * 25) + 24);
	
	glTexCoord2f(s0, t0);
	glVertex2f(x, y);
	
	// bottom right
	s0 = sd * ((col * 25) + 24);
	t0 = td * ((row * 25) + 24);
	
	glTexCoord2f(s0, t0);
	glVertex2f(x + 25, y);
	
	
	// top right
	t0 = td * (row * 25);
	
	glTexCoord2f(s0, t0);
	glVertex2f(x + 25, y + 25);
	
	// top left
	s0 = sd * (col * 25);
	glTexCoord2f(s0, t0);
	glVertex2f(x, y + 25);
	
	glEnd();
	
	
	return 25;
}



/*
 * Print string to screen
 */
void OverlayPrintf(unsigned int x, unsigned int y, char* format, ...) {
	
	
	char message[1024];
	va_list ap;
	int rasterpos;
	
	
	/* first of all, build the string we want to display */
	va_start(ap, format);
	vsnprintf(message, sizeof message, format, ap);
	va_end(ap);
	
	
	rasterpos = x;
	
	/* go trough every character and draw it */
	for(int i=0; i < strlen(message); i++) {
		
		/* filter out non printable characters */
		if(iscntrl(message[i]))
			continue;
		
		
		rasterpos += PlotGlyph(rasterpos, y, message[i]);
	}
}


void DrawOverlay(void) {
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, 1024.0f, 0.0f, 768.0f, 1.0f, 100.0f);
	
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// move camera back so 0 gets on screen just fine
	glTranslatef(0.0f, 0.0f, -2.0f);
	glPushMatrix();
	
	glEnable(GL_TEXTURE_2D);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 400, 150, 0, GL_RGB, GL_UNSIGNED_BYTE, asciibits);
	
	
	OverlayPrintf(10, 50, "Joy H: %.3f", I_GetAxis(JOYAXIS_SPECTATOR_VIEW_HORIZONTAL));
	OverlayPrintf(10, 100, "Joy V: %.3f", I_GetAxis(JOYAXIS_SPECTATOR_VIEW_VERTICAL));

	OverlayPrintf(10, 150, "View Rot: %.3f, %.3f", gs.viewaxis[0], gs.viewaxis[1]);
	
	OverlayPrintf(10, 200, "View Vect: [%.3f %.3f %.3f]", gs.viewForward[0], gs.viewForward[1], gs.viewForward[2]);
	
	
	OverlayPrintf(10, 500, "[%.2f %.2f %.2f %.2f]", gs.viewMatrix[0], gs.viewMatrix[1], gs.viewMatrix[2], gs.viewMatrix[3]);
	OverlayPrintf(10, 450, "[%.2f %.2f %.2f %.2f]", gs.viewMatrix[4], gs.viewMatrix[5], gs.viewMatrix[6], gs.viewMatrix[7]);
	OverlayPrintf(10, 400, "[%.2f %.2f %.2f %.2f]", gs.viewMatrix[8], gs.viewMatrix[9], gs.viewMatrix[10], gs.viewMatrix[11]);
	OverlayPrintf(10, 350, "[%.2f %.2f %.2f %.2f]", gs.viewMatrix[12], gs.viewMatrix[13], gs.viewMatrix[14], gs.viewMatrix[15]);

	M_Draw();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	
}

