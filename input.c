//
//  input.c
//  zf2015
//
//  Created by Laszlo Kovacs on 29/10/2015.
//  Copyright (c) 2015 Swipe_06. All rights reserved.
//

#include "game.h"




extern globalSegment_t gs;

button_t button[ACTION_MAX];




void I_SetButton(actions_t action, uint32_t hwbutton) {
	
	
	button_t* b = &button[action];
	
	
	
	if (hwbutton == BUTTON_DOWN) {
		
		switch (b->state) {
			
			case BUTTON_UP:
				b->state = BUTTON_DOWN;
				b->presstime = OS_Milliseconds();
				break;
				
				
				
			case BUTTON_DOWN:
				b->state = BUTTON_HELD_DOWN;
				break;
			
				
				
			case BUTTON_HELD_DOWN:
				break;
				
				
		}
		
		
	} else {
		button[action].state = BUTTON_UP;
	}
}




int32_t I_GetInputState(actions_t action, uint64_t* presstime) {
	
	if (presstime != NULL) {
		memcpy(presstime, &button[action].presstime, sizeof(uint64_t));
	}
	
	return button[action].state;
}




float I_GetAxis(joy_axis_t axis) {
	
	
	float value;
	
	
	switch (axis) {
			
		case JOYAXIS_SPECTATOR_VIEW_HORIZONTAL:
			value = OS_GetGamepadAxis(PS4_RIGHT_HORIZONTAL);
			break;
	
			
		case JOYAXIS_SPECTATOR_VIEW_VERTICAL:
			value = OS_GetGamepadAxis(PS4_RIGHT_VERTICAL);
			break;
			
			
		case JOYAXIS_SPECTATOR_MOVE_HORIZONTAL:
			value = OS_GetGamepadAxis(PS4_LEFT_HORIZONTAL);
			break;
			
			
		case JOYAXIS_SPECTATOR_MOVE_VERTICAL:
			value = OS_GetGamepadAxis(PS4_LEFT_VERTICAL);
			break;
			
			
		default:
			printf("Invalid axis \n");
			value = 0;
			break;
	}
	

	return value;
}



void I_PollJoystick(void) {

	
	if (!OS_IsJoyConnected())
		return;
	
	
	I_SetButton(ACTION_MENU_UP,	OS_GetGamepadButton(PS4_DPAD_UP));
	I_SetButton(ACTION_MENU_DOWN,	OS_GetGamepadButton(PS4_DPAD_DOWN));
	I_SetButton(ACTION_MENU_BACK,	OS_GetGamepadButton(PS4_CIRCLE));
	I_SetButton(ACTION_MENU_SELECT,	OS_GetGamepadButton(PS4_CROSS));
	I_SetButton(ACTION_MENU_TOGGLE, OS_GetGamepadButton(PS4_OPTIONS));
}





