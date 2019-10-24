#ifndef _TEST_H
#define _TEST_H

#include "BSP.h"
#include "SequenceController.h"
#include "PIDController.h"
#include "MotionAnalysis.h"
#include "Tracker.h"

/*BSP function*/
void DelayAndSYStickTest(void);//pass
void USARTTest(void);//PASS
//N 测试新舵机/ 0全部归到0位置/ C 可操控的舵机控制
void ServerTest(char mode);//PASS
void LCDTest(void);//partPass
void MPUTest(void);//partPass
void LineTrackTest(void);
//N 加减速测试/ C 控制测试
void MontorDriverOutputTest(char c);//pass
//A 测试四个编码器/ M 测试最大编码值在M1
void MontorEncoderTest(char c,const MontorInstance* instance);//pass
void UltrasonicTest(void);//one compent pass
/*Control function*/
void SequenceControllerTest(void);//pass
//P PID/ L 逻辑巡线
void PIDTest(const MontorInstance* instance);
//B 基本应用mask进行运动控制/ P 引入PID调节机制
void MotionAnalysisTest(char c);
void SystermCallBackTest(void);
#endif
