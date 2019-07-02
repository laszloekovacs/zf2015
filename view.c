//
//  debug.c
//  zf2015
//
//  Created by Laszlo Kovacs on 29/10/2015.
//  Copyright (c) 2015 Swipe_06. All rights reserved.
//

#include "game.h"


extern globalSegment_t gs;








void makeIdentityMatrix(matrix_t m) {
	
	
	memset(m, 0, 16 * sizeof(float));
	
	m[0] = m[5] = m[10] = m[15] = 1.0f;
}









float VectorLenSq(vec3_t v) {
	
	float accum = 0.0f;
	
	accum += v[0] * v[0];
	accum += v[1] * v[1];
	accum += v[2] * v[2];
	
	return accum;
}


float VectorLen(vec3_t v) {
	
	
	return sqrtf(VectorLenSq(v));
}


void VectorNormalise(vec3_t v) {
	
	float len;
	
	len = VectorLen(v);
	
	v[0] /= len;
	v[1] /= len;
	v[2] /= len;
	
}


// A x B = (a2b3 - a3b2, a3b1 - a1b3, a1b2 - a2b1);
void VectorCrossProduct(vec3_t A, vec3_t B, vec3_t C) {
	
	C[0] = A[1] * B[2] - A[2] * B[1];
	C[1] = A[2] * B[0] - A[0] * B[2];
	C[2] = A[0] * B[1] - A[1] * B[0];
	
}


float VectorDot(vec3_t a, vec3_t b) {
	
	return (a[0] * b[0] + a[1] * b[1] + a[2] + b[2]);
}




void MakeVector(vec3_t v, float x, float y, float z) {
	v[0] = x;
	v[1] = y;
	v[2] = z;
}


void AxisToAngles(float yaw, float pitch, float roll, vec3_t left, vec3_t up, vec3_t forward) {
	
	
	float sx, sy, sz;
	float cx, cy, cz;
	float theta;
	
	theta = DEG2RAD(yaw);
	sx = sinf(theta);
	cx = cosf(theta);
	
	theta = DEG2RAD(pitch);
	sy = sinf(theta);
	cy = cosf(theta);
	
	theta = DEG2RAD(roll);
	sz = sinf(theta);
	cz = cosf(theta);
	
	left[0] = cy*cz;
	left[1] = sx*sy*cz + cx*sz;
	left[2] = -cx*sy*cz + sx*sz;
	
	up[0] = -cy*sz;
	up[1] = -sz*sy*sz + cx*cz;
	up[2] = cx*sy*sz + sx*cz;
	
	forward[0] = sy;
	forward[1] = -sx*cy;
	forward[2] = cx*cy;
}



void SpectatorController(void) {
	

	if (0.16 < fabsf(I_GetAxis(JOYAXIS_SPECTATOR_VIEW_HORIZONTAL))) {
		gs.viewaxis[YAW] += 5.0f * I_GetAxis(JOYAXIS_SPECTATOR_VIEW_HORIZONTAL);
		
		// clamp to a reasonable value
		while (gs.viewaxis[YAW] > 360.0f) {
			gs.viewaxis[YAW] -= 360.0f;
		}
		
		while (gs.viewaxis[YAW] < 0.0f) {
			gs.viewaxis[YAW] += 360.0f;
		}
	}

#if 1
	if (0.16 < fabsf(I_GetAxis(JOYAXIS_SPECTATOR_VIEW_VERTICAL))) {
		gs.viewaxis[PITCH] += 5.0f * I_GetAxis(JOYAXIS_SPECTATOR_VIEW_VERTICAL);
		
		
		if (gs.viewaxis[PITCH] > 45.0f) {
			gs.viewaxis[PITCH] = 45.0f;
		}
		
		if (gs.viewaxis[PITCH] < -45.0f) {
			gs.viewaxis[PITCH] = -45.0f;
		}
	}
#endif
	
	AxisToAngles(gs.viewaxis[YAW], gs.viewaxis[PITCH], 0.0f, gs.viewLeft, gs.viewUp, gs.viewForward);
	
}


void CalcView(void) {
	
	
	
	gs.viewMatrix[0] = gs.viewLeft[0];
	gs.viewMatrix[1] = gs.viewLeft[1];
	gs.viewMatrix[2] = gs.viewLeft[2];
	gs.viewMatrix[3] = 0.0f;

	
	gs.viewMatrix[4] = gs.viewUp[0];
	gs.viewMatrix[5] = gs.viewUp[1];
	gs.viewMatrix[6] = gs.viewUp[2];
	gs.viewMatrix[7] = 0.0f;
	
	gs.viewMatrix[8] = gs.viewForward[0];
	gs.viewMatrix[9] = gs.viewForward[1];
	gs.viewMatrix[10] = gs.viewForward[2];
	gs.viewMatrix[11] = 0.0f;
	
	
	gs.viewMatrix[12] = 0.0f;
	gs.viewMatrix[13] = 0.0f;
	gs.viewMatrix[14] = 0.0f;
	gs.viewMatrix[15] = 1.0f;
	
	
	return;
}








