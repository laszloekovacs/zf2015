//
//  main.c
//  zf2015
//
//  Created by Laszlo Kovacs on 29/10/2015.
//  Copyright (c) 2015 Swipe_06. All rights reserved.
//


#include "game.h"


globalSegment_t gs;


void DispatchInput(void) {
	
	
	I_PollJoystick();
	
	
	if (BUTTON_DOWN == I_GetInputState(ACTION_MENU_TOGGLE, NULL)) {
		gs.inputfocus ^= 1;
	}
	
	switch (gs.inputfocus) {
		case 0:
			SpectatorController();
			break;
			
		case 1:
			MenuResponder();
		default:
			break;
	}
	

}



int main(int argc, const char * argv[]) {
	
	
	
	OS_Init();
	FS_Init();
	
	OverlayInit();
	
	LoadTextScene("textscene.txt");
	
	while (!OS_ShouldQuit()) {
		
		OS_BeginFrame();
		
		DispatchInput();
		
		CalcView();
		
		R_Refresh();
		
		OS_Wait(20);
		
		OS_FlipBuffers();
	}
	
	
	OS_Exit();
	
    return 0;
}
