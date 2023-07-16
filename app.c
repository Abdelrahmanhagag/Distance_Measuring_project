#include "timer1.h"
#include "ultrasonic.h"
#include "lcd.h"
#include "std_types.h"
#include "common_macros.h"
#include <avr/io.h>
int main(void)
{
	uint32 Distance =  0 ;
	GlobalInterruptEnable();
	LCD_init();
	ULTRASONIC_init();
	LCD_displayString("Distance=    cm");
	while(1)
	{
		Distance = ULTRASONIC_getDestance();
		LCD_moveCursor(0, 10);
		LCD_intgerToString(Distance);

	}
	return 0;
}
