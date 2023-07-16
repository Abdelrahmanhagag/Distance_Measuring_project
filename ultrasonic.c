#include "timer1.h"
#include "ultrasonic.h"
#include "gpio.h"
#include "common_macros.h"
#include "avr/io.h"
#include <util/delay.h>
#include "lcd.h"
static volatile uint16 T1,T2;
static volatile uint8 g = 0 ,c = 0;

void ICUISR_FUNCTION (void)
{
	g++;
	if (g == 1)
	{
		c = 0;
		TIMER1_setIcrEdge(FALLING_EDGE);
		T1 = TIMER1_getIcrReg();

	}
	else if(g == 2)
	{
		T2 = TIMER1_getIcrReg();
		TIMER1_setIcrEdge(RISING_EDGE);
		g = 0;
	}
}
void TIEMR1_OVF_ISR_FUNCTION(void)
{
	c++;
}
void ULTRASONIC_init(void)
{
	TIMER1_config config = {NORMAL_MODE,CLK_8,OC1A_NORMAL,OC1B_NORMAL};
	TIMER1_INTERRUPT_config icu_config = {TIMER1_ICR,ENABLE};
	TIMER1_INTERRUPT_config ovf_config = {TIMER1_OVF,ENABLE};
	TIMER1_setIcrEdge(RISING_EDGE);
	TIMER1_init(&config);
	TIMER1_setInterrupt(&ovf_config);
	TIMER1_setInterrupt(&icu_config);
	TIMER1_setCallBack(ICUISR_FUNCTION, TIMER1_ICR);
	TIMER1_setCallBack(TIEMR1_OVF_ISR_FUNCTION, TIMER1_OVF);

}
static void ULTRASONIC_trigger(void)
{
	GPIO_setupPinDirection(PORT, PIN, PIN_OUTPUT);
	GPIO_setupPinDirection(PORTD_ID, PIN6_ID, PIN_INPUT);
	GPIO_writePin(PORT,PIN , LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(PORT,PIN , LOGIC_LOW);
}
uint32 ULTRASONIC_getDestance(void)
{
	ULTRASONIC_trigger();
	uint32 Distance;
	Distance = ((T2-T1+c*65535)*34600*CLOCK)/(2*F_CPU);
	return Distance ;

}
