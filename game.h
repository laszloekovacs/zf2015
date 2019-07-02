//
//  game.h
//  zf2015
//
//  Created by Laszlo Kovacs on 29/10/2015.
//  Copyright (c) 2015 Swipe_06. All rights reserved.
//

#ifndef zf2015_game_h
#define zf2015_game_h


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <memory.h>
#include <math.h>
#include <unistd.h>
#include <stdarg.h>
#include <assert.h>
#include <ctype.h>



#include <GLFW/glfw3.h>



#define GLOBAL_ASSERT(x) assert(x)


// multiply degrees with this to get radians
#define DEG2RAD(x) (x) * M_PI / 180;


#define FRAMETIME_60HZ	(1000 / 60)
#define FRAMETIME_30HZ	(1000 / 30)


// internal resolution for 2D. 16:9 ratio.
#define SCREEN_WIDHT	640
#define SCREEN_HEIGHT	360


#define YAW	0
#define PITCH	1
#define ROLL	2


typedef enum {
	false,
	true
} boolean_t;

typedef struct {
	unsigned int x, y, w, h;
} glyph_t;


typedef float vec3_t[3];
typedef float matrix_t[16];


typedef struct {
	uint8_t		idlength;
	uint8_t		colormaptype;
	uint8_t		imgtype;
	uint8_t		pad[9];

	uint16_t	width;
	uint16_t	height;
	
	uint8_t		pixeldepth;
	uint8_t		imgdesc;
	
	uint8_t		data;
	
} targa_t;



typedef struct {
	uint32_t	state;
	uint64_t	presstime;
} button_t;



typedef struct {
	uint32_t frametime;
	uint32_t prevframetime;
	uint32_t dt;
	

	float moveaxis[2];
	float viewaxis[2];
	
	vec3_t viewForward;
	vec3_t viewUp;
	vec3_t viewLeft;
	matrix_t viewMatrix;
	
	char inputfocus;
} globalSegment_t;



typedef enum {
	ACTION_MENU_TOGGLE,
	ACTION_MENU_UP,
	ACTION_MENU_DOWN,
	ACTION_MENU_BACK,
	ACTION_MENU_SELECT,
	
	ACTION_SOLDIER_RELOAD,
	ACTION_SOLDIER_FIRE,
	
	ACTION_HELI_RELOAD,
	
	ACTION_VEHICLE_EXIT,
	
	ACTION_MAX
} actions_t;


typedef enum {
	
	JOYAXIS_SPECTATOR_VIEW_HORIZONTAL,
	JOYAXIS_SPECTATOR_VIEW_VERTICAL,
	
	JOYAXIS_SPECTATOR_MOVE_HORIZONTAL,
	JOYAXIS_SPECTATOR_MOVE_VERTICAL,
	
	JOYAXIS_MAX,
} joy_axis_t;





// the buttons can be up down or held down
enum {
	BUTTON_UP,
	BUTTON_DOWN,
	BUTTON_HELD_DOWN,
};

// PS4 buttons, don't change the order!
typedef enum {
	PS4_SQUARE = 0,
	PS4_CROSS,
	PS4_CIRCLE,
	PS4_TRIANGLE,
	
	PS4_L1,
	PS4_R1,
	PS4_L2,
	PS4_R2,
	
	PS4_SHARE,
	PS4_OPTIONS,
	
	PS4_L3,
	PS4_R3,
	
	PS4_PSBUTTON,
	PS4_TOUCHPAD,
	
	PS4_DPAD_UP,
	PS4_DPAD_RIGHT,
	PS4_DPAD_DOWN,
	PS4_DPAD_LEFT,
	PS4_NUM_BUTTONS
	
} ps4_buttons_t;

typedef enum {
	PS4_LEFT_HORIZONTAL,
	PS4_LEFT_VERTICAL,
	
	PS4_RIGHT_HORIZONTAL,
	PS4_RIGHT_VERTICAL,
	
	PS4_LEFT_TRIGGER,
	PS4_RIGHT_TRIGGER,
	
	PS4_NUM_TRIGGERS
	
} ps4_axis_t;



// sys.c
void		OS_Init(void);
void		OS_BeginFrame(void);
void		OS_FlipBuffers(void);

void		OS_Exit(void);
uint32_t	OS_ShouldQuit(void);



uint64_t	OS_Milliseconds(void);
void		OS_Wait(uint32_t msec);


uint8_t		OS_GetGamepadButton(uint32_t button);
float		OS_GetGamepadAxis(uint32_t axis);
boolean_t	OS_IsJoyConnected(void);

// input.c
int32_t		I_GetInputState(actions_t action, uint64_t* presstime);
float		I_GetAxis(joy_axis_t axis);
void		I_PollJoystick(void);

// debug.c
void		debugInit(void);
void		debugRender(void);
void		debugController(void);

void		R_Refresh(void);
//fs.c

void		FS_Init(void);
void*		FS_CacheFile(char* path);


void		SpectatorController(void);
void		CalcView(void);


void OverlayInit(void);
void OverlayPrintf(unsigned int x, unsigned int y, char* format, ...);
void DrawOverlay(void);
void LoadTextScene(char* path);

void MenuResponder();
#endif
