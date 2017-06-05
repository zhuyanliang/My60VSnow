#include "u_include.h"

static S_PID	s_pid;

void PID_Init(void)
{
	s_pid.setSpeed= g_setSpeed;
    s_pid.realSpeed= 0;
    s_pid.errPre = 0;
    s_pid.errLast = 0;
    s_pid.integral = 0;
	s_pid.Kp = 0.002;
    s_pid.Ki = 0.0005;
    s_pid.Kd = 0;
}


int16_t PID_Control(void)
{
	int32_t iError = 0;
	float inncPid = 0.0;
	s_pid.setSpeed = g_setSpeed;
	s_pid.realSpeed = g_realSpeed;
	
	iError = s_pid.setSpeed - s_pid.realSpeed;
	iError *= 10;

	inncPid = (float)(s_pid.Kp*(iError - s_pid.errLast));
	inncPid += (float)(s_pid.Ki*iError);
	inncPid += (float)(s_pid.Kd*(iError - 2*s_pid.errLast + s_pid.errPre));
	
	s_pid.errPre = s_pid.errLast;
	s_pid.errLast = iError;

	return (uint16_t)inncPid;
}
