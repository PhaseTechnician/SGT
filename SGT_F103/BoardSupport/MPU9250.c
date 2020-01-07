#include "MPU9250.h"

// 定义MPU9250内部地址
/*****************************************************************/
#define SMPLRT_DIV 0x19 //陀螺仪采样率
#define CONFIG 0x1A
#define GYRO_CONFIG 0x1B
#define ACCEL_CONFIG 0x1C
#define ACCEL_CONFIG_2 0x1D
#define WHO_AM_I 0x75 //测试连接，器件ID

#define INT_ENABLE 0x38
#define INT_PIN_CFG 0x37 //中断配置
#define USER_CTRL 0x6a
#define I2C_MST_CTRL 0x24
#define I2C_MST_DELAY_CTRL 0x67
//--------------------i2c slv4-------------------------------//
#define I2C_SLV0_ADDR 0X25
#define I2C_SLV0_REG 0X26
#define I2C_SLV0_CTRL 0X27
#define I2C_SLV1_ADDR 0X28
#define I2C_SLV1_REG 0X29
#define I2C_SLV1_CTRL 0X2A
#define I2C_SLV4_ADDR 0x31
#define I2C_SLV4_REG 0x32
#define I2C_SLV4_CTRL 0x34
#define I2C_SLV4_DO 0x33 //output reg
#define I2C_SLV4_DI 0x35
#define I2C_MST_STATUS 0x36
//--------------------AK8963 reg addr------------------------//
#define MPU9250_AK8963_ADDR 0x0C //AKM addr
#define AK8963_WHOAMI_REG 0x00   //AKM ID addr
#define AK8963_WHOAMI_ID 0x48	//ID
#define AK8963_ST1_REG 0x02		 //Data Status1
#define AK8963_ST2_REG 0x09		 //Data reading end register & check Magnetic sensor overflow occurred
#define AK8963_ST1_DOR 0x02
#define AK8963_ST1_DRDY 0x01 //Data Ready
#define AK8963_ST2_BITM 0x10
#define AK8963_ST2_HOFL 0x08 // Magnetic sensor overflow
#define AK8963_CNTL1_REG 0x0A
#define AK8963_CNTL2_REG 0x0B
#define AK8963_CNTL2_SRST 0x01 //soft Reset
#define AK8963_ASAX 0x10	   //X-axis sensitivity adjustment value
#define AK8963_ASAY 0x11	   //Y-axis sensitivity adjustment value
#define AK8963_ASAZ 0x12	   //Z-axis sensitivity adjustment value
//--------------------9axis  reg addr-----------------------//
#define ACCEL_XOUT_H 0x3B
#define ACCEL_XOUT_L 0x3C
#define ACCEL_YOUT_H 0x3D
#define ACCEL_YOUT_L 0x3E
#define ACCEL_ZOUT_H 0x3F
#define ACCEL_ZOUT_L 0x40

#define TEMP_OUT_H 0x41 //temperture
#define TEMP_OUT_L 0x42

#define GYRO_XOUT_H 0x43
#define GYRO_XOUT_L 0x44
#define GYRO_YOUT_H 0x45
#define GYRO_YOUT_L 0x46
#define GYRO_ZOUT_H 0x47
#define GYRO_ZOUT_L 0x48

#define MAG_XOUT_L 0x03
#define MAG_XOUT_H 0x04
#define MAG_YOUT_L 0x05
#define MAG_YOUT_H 0x06
#define MAG_ZOUT_L 0x07
#define MAG_ZOUT_H 0x08
//--------------------other reg addr-----------------------//
#define PWR_MGMT_1 0x6B //电源管理，典型值：0x00(正常启用)
#define PWR_MGMT_2 0x6C
#define WHO_AM_I 0x75 //ID地址寄存器(正确数值0x71，只读)

#define EXT_SENS_DATA_00 0x49 //MPU9250 IIC外挂器件读取返回寄存器00
#define EXT_SENS_DATA_01 0x4a //MPU9250 IIC外挂器件读取返回寄存器01
#define EXT_SENS_DATA_02 0x4b //MPU9250 IIC外挂器件读取返回寄存器02
#define EXT_SENS_DATA_03 0x4c //MPU9250 IIC外挂器件读取返回寄存器03

#ifdef MPU9250_SPI

#define NSS_Low() GPIO_ResetBits(GPIOA, GPIO_Pin_4)
#define NSS_High() GPIO_SetBits(GPIOA, GPIO_Pin_4)

#define ADDR_Write(addr) (addr & 0x7f)
#define ADDR_Read(addr) (addr | 0x80)
#define DATA(value) value
#define EMPTY_CODE 0x00

float ACC_ADJUST[3] = {0.0f};
float GRY_ADJUST[3] = {0.0f};
float MAG_ADJUST[3] = {0.0f};

void BSP_MPU_Config(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	SPI_InitTypeDef SPI_InitStructure;
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; //高位在前
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(SPI1, &SPI_InitStructure);

	NSS_High();
	SPI_Cmd(SPI1, ENABLE);
}

void BSP_MPU_RegesterConfig(void)
{
	BSP_Delay_DelayMs(10);
	MPUWrite(PWR_MGMT_1, 0X80);
	BSP_Delay_DelayMs(100);
	MPUWrite(PWR_MGMT_1, 0X04);
	BSP_Delay_DelayMs(1);
	MPUWrite(INT_PIN_CFG, 0x10);
	BSP_Delay_DelayMs(1);
	MPUWrite(INT_ENABLE, 0x01);
	BSP_Delay_DelayMs(1);
	MPUWrite(PWR_MGMT_2, 0x00);
	BSP_Delay_DelayMs(1);
	MPUWrite(SMPLRT_DIV, 0x00);
	BSP_Delay_DelayMs(1);
	MPUWrite(GYRO_CONFIG, 0x18);
	BSP_Delay_DelayMs(1);
	MPUWrite(ACCEL_CONFIG, 0x08);
	BSP_Delay_DelayMs(1);
	MPUWrite(CONFIG, 0x00);
	BSP_Delay_DelayMs(1);
	MPUWrite(ACCEL_CONFIG_2, 0x05);
	BSP_Delay_DelayMs(1);
	MPUWrite(USER_CTRL, 0x30);
	BSP_Delay_DelayMs(1);
	MPUWrite(I2C_MST_CTRL, 0x5d);
	BSP_Delay_DelayMs(1);
	MPUWrite(I2C_MST_DELAY_CTRL, 0x80);
	BSP_Delay_DelayMs(1);

	uint8_t res = MPURead(GYRO_CONFIG) & 0x18;
	switch (res)
	{
	case 0x00:
		GRY_ADJUST[0] = GRY_ADJUST[1] = GRY_ADJUST[2] = 1.0f / 131.0f;
		break;
	case 0x08:
		GRY_ADJUST[0] = GRY_ADJUST[1] = GRY_ADJUST[2] = 1.0f / 65.5f;
		break;
	case 0x10:
		GRY_ADJUST[0] = GRY_ADJUST[1] = GRY_ADJUST[2] = 1.0f / 32.8f;
		break;
	case 0x18:
		GRY_ADJUST[0] = GRY_ADJUST[1] = GRY_ADJUST[2] = 1.0f / 16.4f;
		break;
	}

	res = MPURead(ACCEL_CONFIG) & 0x18;
	switch (res)
	{
	case 0x00:
		ACC_ADJUST[0] = ACC_ADJUST[1] = ACC_ADJUST[2] = 1.0f / 16384;
		break;
	case 0x08:
		ACC_ADJUST[0] = ACC_ADJUST[1] = ACC_ADJUST[2] = 1.0f / 8192;
		break;
	case 0x10:
		ACC_ADJUST[0] = ACC_ADJUST[1] = ACC_ADJUST[2] = 1.0f / 4096;
		break;
	case 0x18:
		ACC_ADJUST[0] = ACC_ADJUST[1] = ACC_ADJUST[2] = 1.0f / 2048;
		break;
	}
}

void BSP_AK8963_RegisterConfig(void)
{
	BSP_Delay_DelayMs(1);
	MPUWriteByIIC(AK8963_CNTL2_REG, 0X01);
	BSP_Delay_DelayMs(1);
	MPUWriteByIIC(AK8963_CNTL1_REG, 0X00);
	BSP_Delay_DelayMs(1);
	MPUWriteByIIC(AK8963_CNTL1_REG, 0X1F);
	BSP_Delay_DelayMs(10);
	MAG_ADJUST[0] = MPUReadByIIC(AK8963_ASAX);
	BSP_Delay_DelayMs(1);
	MAG_ADJUST[1] = MPUReadByIIC(AK8963_ASAY);
	BSP_Delay_DelayMs(1);
	MAG_ADJUST[2] = MPUReadByIIC(AK8963_ASAZ);
	BSP_Delay_DelayMs(1);
	MPUWriteByIIC(AK8963_CNTL1_REG, 0X00);
	BSP_Delay_DelayMs(10);
	MPUWriteByIIC(AK8963_CNTL1_REG, 0X16);
	BSP_Delay_DelayMs(10);
	MAG_ADJUST[0] = (MAG_ADJUST[0] - 128) * 0.5 / 128 + 1;
	MAG_ADJUST[1] = (MAG_ADJUST[1] - 128) * 0.5 / 128 + 1;
	MAG_ADJUST[2] = (MAG_ADJUST[2] - 128) * 0.5 / 128 + 1;
	uint8_t res = MPUReadByIIC(AK8963_CNTL1_REG) & 0X10;
	if (res == 0x10)
	{
		MAG_ADJUST[0] *= 0.15f;
		MAG_ADJUST[1] *= 0.15f;
		MAG_ADJUST[2] *= 0.15f;
	}
	else if (res == 0x00)
	{
		MAG_ADJUST[0] *= 0.6f;
		MAG_ADJUST[1] *= 0.6f;
		MAG_ADJUST[2] *= 0.6f;
	}

	BSP_Delay_DelayMs(1);
	MPUWrite(I2C_SLV1_ADDR, MPU9250_AK8963_ADDR | 0x80);
	BSP_Delay_DelayMs(1);
	MPUWrite(I2C_SLV1_REG, AK8963_ST1_REG);
	BSP_Delay_DelayMs(1);
	MPUWrite(I2C_SLV1_CTRL, 0x88); //(EN80|LEN08)
	BSP_Delay_DelayMs(1);
	MPUWrite(I2C_SLV4_CTRL, 0x09);
	BSP_Delay_DelayMs(1);
	res = MPURead(I2C_MST_DELAY_CTRL);
	BSP_Delay_DelayMs(1);
	MPUWrite(I2C_MST_DELAY_CTRL, res | 0x20);
}

bool BSP_MPU_CheckOnLine(void)
{
	BSP_Delay_DelayMs(1);
	return MPURead(WHO_AM_I) == 0x71;
}

bool BSP_AK8963_CheckOnLine(void)
{
	BSP_Delay_DelayMs(1);
	return MPUReadByIIC(AK8963_WHOAMI_REG) == AK8963_WHOAMI_ID;
}

int16_t BSP_MPU_ReadValue(enum MPUReadValueAddressEnum address)
{
	NSS_Low();
	MPUReadSendByte(address | 0x80);
	uint16_t res = MPUReadSendByte(0x00);
	res <<= 8;
	res |= MPUReadSendByte(0x00);
	NSS_High();
	return res;
}

void BSP_MPU_Calibrate(int times)
{
}

unsigned char MPUReadSendByte(unsigned char byte)
{
	uint8_t retry = 0;
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET)
	{
		retry++;
		if (retry > 200)
			return 0;
	}
	SPI_I2S_SendData(SPI1, byte);
	retry = 0;
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET)
	{
		retry++;
		if (retry > 200)
			return 0;
	}
	return SPI_I2S_ReceiveData(SPI1);
}

void MPUWrite(unsigned char addr, unsigned char value)
{
	NSS_Low();
	MPUReadSendByte(ADDR_Write(addr));
	MPUReadSendByte(value);
	NSS_High();
}

unsigned char MPURead(unsigned char addr)
{
	NSS_Low();
	MPUReadSendByte(addr | 0x80);
	unsigned char res = MPUReadSendByte(0x00);
	NSS_High();
	return res;
}

void MPUWriteByIIC(unsigned char regAddress, unsigned char value)
{
	uint8_t state;
	uint32_t timeout = 200;
	BSP_Delay_DelayMs(1);
	MPUWrite(I2C_SLV4_ADDR, MPU9250_AK8963_ADDR); //设置磁力计地址,mode: write
	BSP_Delay_DelayMs(1);
	MPUWrite(I2C_SLV4_REG, regAddress); //set reg addrs
	BSP_Delay_DelayMs(1);
	MPUWrite(I2C_SLV4_DO, value); //send value
	BSP_Delay_DelayMs(1);
	MPUWrite(I2C_SLV4_CTRL, 0X80);
	do
	{
		BSP_Delay_DelayMs(1);
		state = MPURead(I2C_MST_STATUS);
	} while (((state & 0x40) == 0) && (timeout--));
	BSP_Delay_DelayMs(1);
}

unsigned char MPUReadByIIC(unsigned char reg)
{
	uint8_t state;
	uint32_t timeout = 200;
	BSP_Delay_DelayMs(1);
	MPUWrite(I2C_SLV4_ADDR, MPU9250_AK8963_ADDR | 0x80); //设置磁力计地址，mode：read
	BSP_Delay_DelayMs(1);
	MPUWrite(I2C_SLV4_REG, reg); // set reg addr
	BSP_Delay_DelayMs(1);
	MPUWrite(I2C_SLV4_CTRL, 0x80);
	do
	{
		BSP_Delay_DelayMs(1);
		state = MPURead(I2C_MST_STATUS);
	} while (((state & 0x40) == 0) && (timeout--));
	BSP_Delay_DelayMs(1);
	return MPURead(I2C_SLV4_DI);
}

#endif
#ifdef MPU9250_IIC

void BSP_MPU_Config(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	GPIO_PinRemapConfig(GPIO_Remap_I2C1, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	I2C_InitTypeDef I2CInitStructure;
}
//MPU寄存器设置
void BSP_MPU_RegesterConfig(void);
//MPU9250唤醒设置
void BSP_MPU_WakeUp(void);
//MPU检测是否离线
bool BSP_MPU_CheckOnLine(void);

#endif
