#include "u_include.h"

static uint32_t lastProtectDelay = (~0x00);

/*
 * execution cycle is 10Ms
 *
 * Check Battery Voltage
 *
 */
void Task_Voltage_Check(void)
{
	uint8_t i;
	static bool 	firstFlag = true;
	static uint16_t voltArray[4] = {0};
	static uint8_t  voltIndex = 0;

	uint16_t volatge;

	if(firstFlag)
	{
		firstFlag = false;
		for(i=0;i<4U;i++)
		{
			voltArray[voltIndex++ & 0x03] = ADC_Convert_Original(Adc_Channel_Voltage);
		}
		volatge = Calc_AverageCalculate(voltArray,4);
	}
	else
	{
		voltArray[voltIndex++ & 0x03] = ADC_Convert_Original(Adc_Channel_Voltage);
		volatge = Calc_AverageCalculate(voltArray,4);
	}

	if(volatge < g_voltLow)
	{
		g_sysProtect.lowVolt = 0b1;
		if(g_protectDelay > PROTECTDELAY_100Ms)
		{
			g_protectDelay = PROTECTDELAY_100Ms;
		}
	}
	else
	{
		g_sysProtect.lowVolt = 0b0;
		g_protectDelay = lastProtectDelay;
	}
	lastProtectDelay = g_protectDelay;
}


/*
 * execution cycle is 10Ms
 *
 * Check Pahse Current
 *
 */
void Task_Current_Check(void)
{
	uint8_t i;
	static bool firstFlag = true;
	static uint16_t currentArray[4] = {0};
	static uint8_t  currentIndex = 0;
	
	if(firstFlag)
	{
		firstFlag = false;
		for(i=0;i<4U;i++)
		{
			currentArray[currentIndex++ & 0x03] = ADC_Convert_Original(Adc_Channel_Current);
			if(g_motorCurrent > g_curShort)
			{
				g_sysProtect.curshort = 0b1;
			}
		}
		g_motorCurrent = Calc_AverageCalculate(currentArray,4);
	}
	else
	{
		currentArray[currentIndex++ & 0x03] = ADC_Convert_Original(Adc_Channel_Current);
		g_motorCurrent = Calc_AverageCalculate(currentArray,4);
	}

	/* Check if over current*/
	if(g_motorCurrent > g_curOvLeve1)
	{
		g_sysProtect.ovCurLe1 = 0b1;
		if(g_protectDelay > PROTECTDELAY_3S)
		{
			g_protectDelay = PROTECTDELAY_3S;
		}
	}
	else
	{
		g_sysProtect.ovCurLe1 = 0b0;
		g_protectDelay = lastProtectDelay;
	}

	if(g_motorCurrent > g_curOvLeve2)
	{
		g_sysProtect.ovCurLe2 = 0b1;
		if(g_protectDelay > PROTECTDELAY_600Ms)
		{
			g_protectDelay = PROTECTDELAY_600Ms;
		}
	}
	else
	{
		g_sysProtect.ovCurLe2 = 0b0;
		g_protectDelay = lastProtectDelay;
	}

	if(g_motorCurrent > g_curOvLeve3)
	{
		g_sysProtect.ovCurLe3 = 0b1;
		if(g_protectDelay > PROTECTDELAY_100Ms)
		{
			g_protectDelay = PROTECTDELAY_100Ms;
		}
	}
	else
	{
		g_sysProtect.ovCurLe3 = 0b0;
		g_protectDelay = lastProtectDelay;
	}

	if(g_motorCurrent > g_curOvLeve4)
	{
		g_sysProtect.ovCurLe4 = 0b1;
		if(g_protectDelay > PROTECTDELAY_20Ms)
		{
			g_protectDelay = PROTECTDELAY_20Ms;
		}
	}
	else
	{
		g_sysProtect.ovCurLe4 = 0b0;
		g_protectDelay = lastProtectDelay;
	}
	
	if(g_motorCurrent > g_curShort)
	{
		g_sysProtect.curshort = 0b1;
		if(g_protectDelay > PROTECTDELAY_10Ms)
		{
			g_protectDelay = PROTECTDELAY_10Ms;
		}
	}
	else
	{
		g_sysProtect.curshort = 0b0;
		g_protectDelay = lastProtectDelay;
	}

	lastProtectDelay = g_protectDelay;
}

void Task_Temperature_Check(void)
{
	uint8_t i;
	static bool firstFlag = true;
	static uint16_t tempArray[4] = {0};
	static uint8_t  tempIndex = 0;
	static uint8_t cnt = 0;
	uint16_t temperature;

	if(firstFlag)
	{
		firstFlag = false;
		for(i=0;i<4U;i++)
		{
			tempArray[tempIndex++ & 0x03] = ADC_Convert_Original(Adc_Channel_MOSTemp);
		}
		temperature = Calc_AverageCalculate(tempArray,4);
	}
	else
	{
		tempArray[tempIndex++ & 0x03] = ADC_Convert_Original(Adc_Channel_MOSTemp);
		temperature = Calc_AverageCalculate(tempArray,4);
	}
	
	if(temperature < g_ovTemp)
	{
		if(cnt++>3)
			g_sysProtect.mos_ovTemp = 0b1;
	}
	else
	{
		cnt = 0;
		g_sysProtect.mos_ovTemp = 0b0;
	}
}

void Task_Motor_Control(void)
{
	Manage_Motor_State();
	Manage_Motor_Phase();
}

void Task_Motor_SpeedControl(void)
{
	if(!g_btnPress)
	{
		g_speedPWM = SPEED_MIN;
		if(Check_Motor_Stop())
		{
			g_realSpeed = 0;
			g_dltSpeedTick = (~(uint32_t)0x00);
		}
		return;
	}
	if(CONST_SPEED)
	{
		g_speedPWM += PID_Control();
	}
	else if(CONST_CURRENT)
	{
		Const_Current();
	}
	else if(OPEN_LOOP)
	{
		Open_Loop_Run();
	}
	
	if(g_speedPWM >= SPEED_MAX)
	{
		g_speedPWM = SPEED_MAX - 1;
	}
	if(g_speedPWM <= SPEED_MIN)
	{
		g_speedPWM = SPEED_MIN;
	}
	
	PWM_Set_Duty(g_speedPWM);
}

/*
 * execution cycle is 10Ms
 *
 */
void Task_Delay(void)
{
	 
}

void Task_Manage_ProtectInfo(void)
{
	uint8_t protectInfo =  *(uint8_t*)&g_sysProtect;

	g_protectDelay -= 2;
	if(!g_protectDelay)
	{
		g_protectDelay = 2;
		Motor_Stop();
	}
	
	/* LED always on  */
	if(0 == protectInfo)
	{
		if(g_btnPress)
			Led_Set(0xFF,0xFF,0xFFFF);
		else
			Led_Set(0x00,0x00,0x00);
		return;
	}
	else
	{
		if(g_sysProtect.hallerr)
		{
			Led_Set(30,7,200);
		}
		if(g_sysProtect.ovCurLe1|| g_sysProtect.curshort)
		{
			Led_Set(30,6,200);
		}
		if(g_sysProtect.ovCurLe1)
		{
			Led_Set(30,5,200);
		}
		if(g_sysProtect.lowVolt)
		{
			Led_Set(30,4,200);
		}
		Motor_Stop();
	}
}

/*
 * execution cycle is 10Ms
 *
 */
void Task_Calc_Speed(void)
{
	static uint16_t speedSum = 0;
	static uint8_t cnt = 0;

	cnt++;
	if(MOTOR_STOP == g_motorState)
	{
		return;
	}
	if(cnt >= SPEEDAVGNUM)
	{
		cnt = 0;
		g_realSpeed = speedSum/SPEEDAVGNUM;
		speedSum = 0;
	}
	speedSum += (uint16_t)(60000000/g_dltSpeedTick/MAGNEDTIC_POLE_NUM);
	
}


