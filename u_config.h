
#ifndef CONFIG_H
#define CONFIG_H

// Only one can be true
#define CONST_SPEED		true
#define CONST_CURRENT	false
#define OPEN_LOOP		false


#define SPEED_MAX		(int16_t)4799
#define SPEED_MIN		(int16_t)400
#define SPEED_EXPECT	6000U

#define MAGNEDTIC_POLE_NUM 		4U
#define SPEEDAVGNUM				4U


#define VDD			5U
#define AVREF		VDD
#define ADC10BITS	1024U

/* protect parameter set*/
/*VBUS*/
#define	Rtop					200U
#define	Rbottom					47U		/* k */
#define Voltage_Normal			18U		/* k */
#define Voltage_Low_Value		14U     /* k */
#define Voltage_Low_Value_AD	(uint16_t)(Voltage_Low_Value*1.0F*Rbottom/(Rtop+Rbottom)/VDD*ADC10BITS)

/*current check parameters*/
#define R_curchk					0.001F
#define Amplifier					10U		/* 电流采样放大倍数*/
/* x -- 单位: A*/
#define Current(x)					(uint16_t)(x*R_curchk/VDD*ADC10BITS*Amplifier)

/*单位: A*/
#define Current_Short_AD			Current(110)
#define Current_OverLeve1_AD		Current(20)
#define Current_OverLeve2_AD		Current(40)
#define Current_OverLeve3_AD		Current(60)
#define Current_OverLeve4_AD		Current(80)


/*mosfet temperature parameters*/
#define R_div				10U
#define Temp_Over_R_Val		0.98F 
#define	Temp_Over_AD        (uint16_t)(Temp_Over_R_Val/(R_div+Temp_Over_R_Val)*ADC10BITS)

#define Adc_Channel_Current		1U
#define Adc_Channel_Voltage		0U
#define Adc_Channel_MOSTemp		18U


#define Enable		true
#define NeedBrake	Enable


#endif