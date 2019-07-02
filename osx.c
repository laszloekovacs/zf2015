//
//  sys.c
//  zf2015
//
//  Created by Laszlo Kovacs on 29/10/2015.
//  Copyright (c) 2015 Swipe_06. All rights reserved.
//

#include "game.h"





GLFWwindow*		window;

int			numbuttons;
int			numaxis;
const unsigned char*	glfwbuttons;
const float*		glfwaxis;





// startup windowing system
void OS_Init(void) {

	int result = 0;

	
	result = glfwInit();
	
	GLOBAL_ASSERT(result);
	
	
	result = glfwJoystickPresent(GLFW_JOYSTICK_1);
	
	if (!result) {
		printf("No joystick present\n");
	}
	
	window = glfwCreateWindow(600, 300, "2015", NULL, NULL);
	
	GLOBAL_ASSERT(window);

	
	glfwMakeContextCurrent(window);
}



// Called at the start of every frame
void OS_BeginFrame(void) {
	
	
	glfwPollEvents();
	
	// glfw batch queries the buttons, so get the array here
	glfwbuttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &numbuttons);
	
	
	// get axis information
	glfwaxis = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &numaxis);
	
	return;
}


// call at the end of the fame. handles buffer swap
void OS_FlipBuffers(void) {
	
	
	glfwSwapBuffers(window);
}



// terminate system
void OS_Exit(void) {

	
	glfwTerminate();
	
	exit(EXIT_SUCCESS);
}




uint32_t OS_ShouldQuit(void) {

	
	if (window) {
		return glfwWindowShouldClose(window);
	}
	
	return 0;
}




uint64_t OS_Milliseconds(void) {

	
	struct timeval tv;
	uint64_t msec;
	
	
	gettimeofday(&tv, NULL);
	
	msec = tv.tv_sec * 1000;
	msec += tv.tv_usec / 1000;
	
	return msec;
}



void OS_Wait(uint32_t msec) {

	
	msec *= 1000;
	
	usleep(msec);
}




uint8_t OS_GetGamepadButton(uint32_t button) {
	

	if (button >= numbuttons) {
		return 0;
	}
	
	return glfwbuttons[button];
}





float OS_GetGamepadAxis(uint32_t axis) {
	
	if (axis >= numaxis) {
		return 0.0f;
	}
	
	return glfwaxis[axis];
}





boolean_t OS_IsJoyConnected(void) {
	return glfwJoystickPresent(GLFW_JOYSTICK_1);
}





