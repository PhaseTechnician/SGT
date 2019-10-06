#ifndef _TEST_H
#define _TEST_H

#include "BSP.h"
#include "SequenceController.h"

/*BSP function*/
void DelayAndSYStickTest(void);//pass
void USARTTest(void);//PASS
void ServerTest(void);//PASS
void LCDTest(void);//partPass
void MPUTest(void);
void MontorDriverOutputTest(void);
void MontorEncoderTest(void);
void UltrasonicTest(void);//one compent pass
/*Control function*/
void SequenceControllerTest(void);//pass

//change LCD pin 
//change EXTI A3

#endif
