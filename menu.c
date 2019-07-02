//
//  menu.c
//  zf2015
//
//  Created by Laszlo Kovacs on 10/11/2015.
//  Copyright (c) 2015 Swipe_06. All rights reserved.
//

#include "game.h"


char selection;



void MenuResponder(void) {
	
	
	if (BUTTON_DOWN == I_GetInputState(ACTION_MENU_UP, NULL)) {
		
		if (selection) {
			selection--;
		}
	}
	
	if (BUTTON_DOWN == I_GetInputState(ACTION_MENU_DOWN, NULL)) {
		
		if (selection <= 4) {
			selection++;
		}
	}
	
	if (BUTTON_DOWN == I_GetInputState(ACTION_MENU_SELECT, NULL)) {
		switch (selection) {
			case 0:
				
				break;
				
			default:
				break;
		}
	}
}



void M_Draw(void) {
	
	OverlayPrintf(0, 300, "selection: %d", selection);
}
