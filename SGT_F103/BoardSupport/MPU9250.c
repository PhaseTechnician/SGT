#include "MPU9250.h"

#define NSS_Low()  GPIO_ResetBits(GPIOA,GPIO_Pin_4)
#define NSS_High() GPIO_SetBits(GPIOA,GPIO_Pin_4)

#define ADDR_Write(addr) (addr&0x7f)
#define ADDR_Read(addr)  (addr|0x80)
#define DATA(value)      value
#define EMPTY_CODE 0xff

// ����MPU9250�ڲ���ַ
/*****************************************************************/
#define	SMPLRT_DIV		                      0x19 //�����ǲ�����
#define	CONFIG			                        0x1A	
#define	GYRO_CONFIG		                      0x1B	
#define	ACCEL_CONFIG	                      0x1C	
#define	ACCEL_CONFIG_2                      0x1D 
#define WHO_AM_I                            0x75 //�������ӣ�����ID

#define INT_PIN_CFG                         0x37 //�ж�����
#define USER_CTRL                           0x6a
#define I2C_MST_CTRL                        0x24
#define I2C_MST_DELAY_CTRL                  0x67
//--------------------i2c slv0-------------------------------//
#define I2C_SLV0_ADDR                       0x25  
#define I2C_SLV0_REG                        0x26
#define I2C_SLV0_CTRL                       0x27 
#define I2C_SLV0_DO                         0x63 //output reg
//--------------------AK8963 reg addr------------------------//
#define MPU9250_AK8963_ADDR                 0x0C  //AKM addr
#define AK8963_WHOAMI_REG                   0x00  //AKM ID addr
#define AK8963_WHOAMI_ID                    0x48  //ID
#define AK8963_ST1_REG                      0x02  //Data Status1
#define AK8963_ST2_REG                      0x09  //Data reading end register & check Magnetic sensor overflow occurred
#define AK8963_ST1_DOR                      0x02
#define AK8963_ST1_DRDY                     0x01 //Data Ready
#define AK8963_ST2_BITM                     0x10
#define AK8963_ST2_HOFL                     0x08 // Magnetic sensor overflow 
#define AK8963_CNTL1_REG                    0x0A
#define AK8963_CNTL2_REG                    0x0B
#define AK8963_CNTL2_SRST                   0x01 //soft Reset
#define AK8963_ASAX                         0x10 //X-axis sensitivity adjustment value 
#define AK8963_ASAY                         0x11 //Y-axis sensitivity adjustment value
#define AK8963_ASAZ                         0x12 //Z-axis sensitivity adjustment value
//--------------------9axis  reg addr-----------------------//
#define	ACCEL_XOUT_H	0x3B
#define	ACCEL_XOUT_L	0x3C
#define	ACCEL_YOUT_H	0x3D
#define	ACCEL_YOUT_L	0x3E
#define	ACCEL_ZOUT_H	0x3F
#define	ACCEL_ZOUT_L	0x40

#define	TEMP_OUT_H		0x41   //temperture
#define	TEMP_OUT_L		0x42

#define	GYRO_XOUT_H		0x43
#define	GYRO_XOUT_L		0x44	
#define	GYRO_YOUT_H		0x45
#define	GYRO_YOUT_L		0x46
#define	GYRO_ZOUT_H		0x47
#define	GYRO_ZOUT_L		0x48
		
#define MAG_XOUT_L		0x03
#define MAG_XOUT_H		0x04
#define MAG_YOUT_L		0x05
#define MAG_YOUT_H		0x06
#define MAG_ZOUT_L		0x07
#define MAG_ZOUT_H		0x08
//--------------------other reg addr-----------------------//
#define	PWR_MGMT_1		0x6B	//��Դ��������ֵ��0x00(��������)
#define	WHO_AM_I		  0x75	//ID��ַ�Ĵ���(��ȷ��ֵ0x71��ֻ��)

#define EXT_SENS_DATA_00    0x49  //MPU9250 IIC���������ȡ���ؼĴ���00
#define EXT_SENS_DATA_01    0x4a  //MPU9250 IIC���������ȡ���ؼĴ���01
#define EXT_SENS_DATA_02    0x4b  //MPU9250 IIC���������ȡ���ؼĴ���02
#define EXT_SENS_DATA_03    0x4c  //MPU9250 IIC���������ȡ���ؼĴ���03


void BSP_MPU_Config(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure); 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	SPI_InitTypeDef SPI_InitStructure;
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;//32����
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;//��λ��ǰ
	SPI_InitStructure.SPI_CRCPolynomial = 2;
	SPI_Init(SPI1, &SPI_InitStructure);
	
	NSS_High();
	SPI_Cmd(SPI1,ENABLE);
}

void BSP_MPU_RegesterConfig(void)
{
	/*IIC
	MPUWrite(INT_PIN_CFG ,0x30);// INT Pin / Bypass Enable Configuration  
	MPUWrite(I2C_MST_CTRL,0x4d);//I2C MAster mode and Speed 400 kHz
	MPUWrite(USER_CTRL ,0x20); // I2C_MST _EN 
	MPUWrite(I2C_MST_DELAY_CTRL ,0x01);//��ʱʹ��I2C_SLV0 _DLY_ enable  
	MPUWrite(I2C_SLV0_CTRL ,0x81); //enable IIC and EXT_SENS_DATA==1 Byte*/

	MPUWrite(CONFIG, 0x07);      //��ͨ�˲�Ƶ�ʣ�����ֵ��0x07(3600Hz)�˼Ĵ����ھ���Internal_Sample_Rate==8K
	MPUWrite(SMPLRT_DIV, 0x07);  //�����ǲ����ʣ�����ֵ��0x07(1kHz) (SAMPLE_RATE= Internal_Sample_Rate / (1 + SMPLRT_DIV) )
	MPUWrite(GYRO_CONFIG, 0x08); //�������Լ켰������Χ������ֵ��0x18(���Լ죬2000deg/s)
	MPUWrite(ACCEL_CONFIG_2, 0x08);//���ټƸ�ͨ�˲�Ƶ�� ����ֵ ��0x08  ��1.13kHz�� 
	MPUWrite(ACCEL_CONFIG, 0x08);//���ټ��Լ졢������Χ����ͨ�˲�Ƶ�ʣ�����ֵ��0x00/+-2g. 0x08/+-4g. 0x10/+-8g. 0x18(���Լ죬16G)
}

inline void BSP_MPU_WakeUp(void)
{
	MPUWrite(PWR_MGMT_1,0X80);
}

inline bool BSP_MPU_CheckOnLine(void)
{
	return MPURead(WHO_AM_I)==0x71;
}

inline int16_t BSP_MPU_ReadACCX(void)
{
	return MPURead(ACCEL_XOUT_H)<<8|MPURead(ACCEL_XOUT_L); 
}

inline int16_t BSP_MPU_ReadACCY(void)
{
	return MPURead(ACCEL_YOUT_H)<<8|MPURead(ACCEL_YOUT_L); 
}

inline int16_t BSP_MPU_ReadACCZ(void)
{
	return MPURead(ACCEL_ZOUT_H)<<8|MPURead(ACCEL_ZOUT_L); 
}

inline int16_t BSP_MPU_ReadOMGX(void)
{
	return MPURead(GYRO_XOUT_H)<<8|MPURead(GYRO_XOUT_L); 
}

inline int16_t BSP_MPU_ReadOMGY(void)
{
	return MPURead(GYRO_YOUT_H)<<8|MPURead(GYRO_YOUT_L); 
}

inline int16_t BSP_MPU_ReadOMGZ(void)
{
	return MPURead(GYRO_ZOUT_H)<<8|MPURead(GYRO_ZOUT_L); 
}

inline int16_t BSP_MPU_ReadTEMP(void)
{
	return MPURead(TEMP_OUT_H)<<8|MPURead(TEMP_OUT_L); 
}

unsigned char MPUReadSendByte(unsigned char byte)
{
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1, byte);
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
	return SPI_I2S_ReceiveData(SPI1); 
}

void MPUWrite(unsigned char addr,unsigned char value)
{
	NSS_Low();
	MPUReadSendByte(ADDR_Write(addr));
	MPUReadSendByte(value);
	NSS_High();
}

unsigned char MPURead(unsigned char addr)
{
	NSS_Low();
	MPUReadSendByte(ADDR_Read(addr));
	unsigned char res = MPUReadSendByte(EMPTY_CODE);
	NSS_High();
	return res;
}
