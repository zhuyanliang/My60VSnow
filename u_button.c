#include "u_include.h"

bool Get_Button_State(void)
{
	if(BUTTON)
		return true;
	else
		return false;
}

void Task_Btn_Scan(void)
{
	static uint8_t cnt = 0;
	if(SW_ON)
	{	
		if(cnt++ > 2)
		{
			cnt = 2;
			g_btnPress = true;
		}
	}
	else
	{
		cnt = 0;
		g_btnPress = false;
	}
}



