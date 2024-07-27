/******************************************************************************
 *
 * Module: ULTRASONIC
 *
 * File Name: ultrasonic.c
 *
 * Description: Source file for the ULTRASONIC driver
 *
 * Author: Joe Metwally
 *
 *******************************************************************************/
#include "ultrasonic.h"
#include <util/delay.h>
volatile uint8 g_edgeCount = 0;
uint16 g_time = 0;

void Ultrasonic_init(void) {
	/* Create configuration structure for ICU driver */
	ICU_ConfigType ICU_Configurations = { F_CPU_8, RISING };
	ICU_init(&ICU_Configurations);
	/* Set the Call back function pointer in the ICU driver */
	ICU_setCallBack(Ultrasonic_edgeProcessing);
	GPIO_setupPinDirection(TRIGGER_PORT, TRIGGER_PIN, PIN_OUTPUT);
	GPIO_writePin(TRIGGER_PORT, TRIGGER_PIN, LOGIC_LOW);
}

void Ultrasonic_Trigger(void) {
	GPIO_writePin(TRIGGER_PORT, TRIGGER_PIN, LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(TRIGGER_PORT, TRIGGER_PIN, LOGIC_LOW);
}

uint16 Ultrasonic_readDistance(void) {
	Ultrasonic_Trigger();
	if (g_edgeCount >= 2) {
		g_edgeCount = 0;
	}
	return (g_time / 58 + 1);
}

void Ultrasonic_edgeProcessing(void) {
	g_edgeCount++;
	if (g_edgeCount == 1) {
		/*
		 * Clear the timer counter register to start measurements from the
		 * first detected rising edge
		 */
		ICU_clearTimerValue();
		/* Detect falling edge */
		ICU_setEdgeDetectionType(FALLING);
	} else if (g_edgeCount == 2) {
		/* Store the High time value */
		g_time = ICU_getInputCaptureValue();

		ICU_setEdgeDetectionType(RISING);
	}

}
