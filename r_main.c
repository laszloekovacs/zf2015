//
//  not_imp.c
//  zf2015
//
//  Created by Laszlo Kovacs on 03/11/2015.
//  Copyright (c) 2015 Swipe_06. All rights reserved.
//

#include "game.h"

extern globalSegment_t gs;




void DrawPointSpace(void) {
	
	glBegin(GL_LINES);
	
	for (int i = -4; i < 4; i++) {
		for (int j = -4; j < 4; j++) {
			for (int k = -4; k < 4; k++) {
				glColor3f(0.25f*i, 0.25*j, 0.25*k);
				glVertex3f(i, j, k);
			}
		}
	}
	
	
	glEnd();
}


void R_Refresh(void) {
	
	
	
	glClearColor(0.5, 0.5, 0.5, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(3);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0f, 1.0f, -0.5f, 0.5f, 1.0f, 1000.0f);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(gs.viewMatrix);
	glPushMatrix();
	

	// load whatever matrix you need for the current obj.
	
	DrawPointSpace();
	
	DrawOverlay();
	
	glPopMatrix();
	
	glFinish();

	
	
	
	
}