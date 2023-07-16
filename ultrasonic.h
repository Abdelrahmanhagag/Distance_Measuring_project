
#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_
#include "std_types.h"
#define CLOCK                 8.0
#define PORT                  PORTB_ID
#define PIN                   PIN5_ID
typedef enum {
	PORTA_ID,PORTB_ID,PORTC_ID
}ULTRASONIC_PORT;
typedef enum {
	PIN0_ID,PIN1_ID,PIN2_ID,PIN3_ID,PIN4_ID,PIN5_ID,PIN6_ID,PIN7_ID
}ULTRASONIC_PIN;
typedef struct {
	ULTRASONIC_PORT port;
	ULTRASONIC_PIN  pin;
}ULTRASONIC_CHANNEL;
void ULTRASONIC_init(void);
uint32 ULTRASONIC_getDestance(void);
#endif /* ULTRASONIC_H_ */
