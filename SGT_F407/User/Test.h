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
//N �����¶��/ 0ȫ���鵽0λ��/ C �ɲٿصĶ������
void ServerTest(char mode);//PASS
void LCDTest(void);//partPass
void MPUTest(void);//partPass
void LineTrackTest(void);
//N �Ӽ��ٲ���/ C ���Ʋ���
void MontorDriverOutputTest(char c);//pass
//A �����ĸ�������/ M ����������ֵ��M1
void MontorEncoderTest(char c,const MontorInstance* instance);//pass
void UltrasonicTest(void);//one compent pass
/*Control function*/
void SequenceControllerTest(void);//pass
//P PID/ L �߼�Ѳ��
void PIDTest(const MontorInstance* instance);
//B ����Ӧ��mask�����˶�����/ P ����PID���ڻ���
void MotionAnalysisTest(char c);
void SystermCallBackTest(void);
#endif
