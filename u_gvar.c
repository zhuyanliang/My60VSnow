
/*
 * Global variables in this file
 *
 */

#include "u_include.h"

/* system tick*/
uint32_t 		g_sysTick;	

/* system 2ms flag*/
bool 	 		g_elapse2Ms;

/* protect case*/
S_SYS_PROTECT	g_sysProtect;

/*led's parameters*/
S_LED_SET		g_ledSet;


E_MOTOR_STATUS	g_motorState;
uint8_t			g_hallState;


uint16_t 		g_voltLow;
uint16_t		g_curShort;
uint16_t 		g_curOvLeve1;
uint16_t 		g_curOvLeve2;
uint16_t 		g_curOvLeve3;
uint16_t 		g_curOvLeve4;
uint16_t		g_ovTemp;


/*  button was pressed
 * false  -- button not pressed
 * true   -- button was pressed
 */
bool 			g_btnPress;	

/*motor's current*/
uint16_t 		g_motorCurrent;

/* motor rotation direction
 * false -- reverse
 * true  -- forward
 */
bool 					g_motorDirection;

bool 					g_motorStopFlag;
volatile uint32_t		g_dltSpeedTick[8];

volatile int16_t		g_speedPWM;
volatile uint16_t		g_realSpeed;
uint16_t				g_setSpeed;
uint8_t					g_elapse20MsCnt;
/* 设定恒流值 */
volatile int16_t 		g_constCurrent;

/* 保护时间 Ms*/
uint32_t	g_protectDelay; 


void Global_Var_Init(void)
{
	uint8_t i;
	g_voltLow 		= Voltage_Low_Value_AD;
	g_curShort 		= Current_Short_AD;
	g_curOvLeve1 	= Current_OverLeve1_AD;
	g_curOvLeve2 	= Current_OverLeve2_AD;
	g_curOvLeve3 	= Current_OverLeve3_AD;
	g_curOvLeve4 	= Current_OverLeve4_AD;
	g_ovTemp		= Temp_Over_AD;

	g_speedPWM = SPEED_MIN;
	g_motorStopFlag = true;
	g_realSpeed = 0;

	g_btnPress = false;
	g_motorDirection = true;
	g_elapse2Ms = true;

	for(i=0;i<DLTSPEEDTICKNUM;i++)
		g_dltSpeedTick[i] = (~0x00);
	
	g_setSpeed = SPEED_EXPECT;

	g_protectDelay = (~0x00);
	g_constCurrent = Current(10);
	
}

