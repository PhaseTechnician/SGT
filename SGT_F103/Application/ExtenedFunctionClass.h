#ifndef _EXTENEDFUNCTIONCLASS_H
#define _EXTENEDFUNCTIONCLASS_H

typedef enum ExtenedLEDOrderEnum
{
	ExtenedOrder_LED_Board_On,
	ExtenedOrder_LED_Board_Off,
	ExtenedOrder_LED_Board_Blink,
	ExtenedOrder_LED_RED_On,
	ExtenedOrder_LED_RED_Off,
	ExtenedOrder_LED_RED_Blink,
	ExtenedOrder_LED_BLUE_On,
	ExtenedOrder_LED_BLUE_Off,
	ExtenedOrder_LED_BLUE_Blink
}ExtendLEDOrder;

typedef enum ExtenedBeepOrderEnum
{
	ExtenedOrder_Beep_On,
	ExtenedOrder_Beep_Off
}ExtenedBeepOrder;

void BeepNoisyTask(void);

void LEDControlsTask(void);

#endif
