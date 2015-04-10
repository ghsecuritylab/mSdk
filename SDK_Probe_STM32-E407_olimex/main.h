/*
 * bioloid_test.h
 *
 * Created: 5/1/2015 12:22:37 AM
 *  Author: Iulian Gheorghiu (morgoth.creator@gmail.com)
 */
/*#####################################################*/
#ifndef MAIN_H_
#define MAIN_H_
/*#####################################################*/
#define USE_MPU60x0 \
	new_mpu60x0 *MPU60x0
/*#####################################################*/
#define MPU60x0_INIT \
	MPU60x0 = new_(new_mpu60x0);\
	MPU60x0->TWI = TWI[0];
/*#####################################################*/
#define USE_AK8975 \
	new_ak8975 *AK8975
/*#####################################################*/
#define AK8975_INIT \
	AK8975 = new_(new_ak8975);\
	AK8975->TWI = TWI[0];
/*#####################################################*/
#define USE_BMP180 \
	new_bmp180 *BMP180
/*#####################################################*/
#define BMP180_INIT \
	BMP180 = new_(new_bmp180);\
	BMP180->TWI = TWI[0];
/*#####################################################*/
#define UART_0_INIT \
	Uart[5] = new_(new_uart);\
	Uart[5]->BaudRate = 115200;\
	Uart[5]->Priority = 0;\
	Uart[5]->UartNr = 2;\
	Uart[5]->TxPort = IOB;\
	Uart[5]->RxPort = IOB;\
	Uart[5]->TxPin = 10;\
	Uart[5]->RxPin = 11;\
	uart_open(Uart[5]);\
	DebugCom = Uart[5];

/*#####################################################*/
#define TWI_1_INIT \
	UARTPuts(DebugCom, "Setup TWI1 with RxBuff = 258, TxBuff = 258....." , -1);\
	TWI[0] = new_(new_twi);\
	TWI[0]->BaudRate = 400000;\
	TWI[0]->TwiNr = 0;\
	TWI[0]->Priority = 0;\
	TWI[0]->UseDma = false;\
	TWI[0]->RxBuffSize = 258;\
	TWI[0]->TxBuffSize = 258;\
	TWI[0]->BusyTimeOut = 5;\
	TWI[0]->SclPort = IOB;\
	TWI[0]->SdaPort = IOB;\
	TWI[0]->SclPin = 8;\
	TWI[0]->SdaPin = 9;\
	twi_open(TWI[0]);\
	UARTPuts(DebugCom, "OK.\n\r" , -1);
/*#####################################################*/
#define ADC_0_INIT \
	UARTPuts(DebugCom, "Setup ADC 0....." , -1);\
	ADC[0] = new_(new_adc);\
	ADC[0]->Align = ADC_ALIGN_RIGHT;\
	ADC[0]->ContinuousMode = ADC_CONTINUOUS_MODE_CONTINUOUS;\
	ADC[0]->ConvMode = ADC_CONV_MODE_MULTICHANNEL;\
	ADC[0]->DmaChannel = 0;\
	ADC[0]->DmaUnitNr = 0;\
	ADC[0]->EnCh[0] = 1;\
	ADC[0]->EnCh[1] = 2;\
	ADC[0]->EnCh[2] = 17;\
	ADC[0]->ExtTrig = ADC_EXT_TRIG_NONE;\
	ADC[0]->ExtTrigEdge = ADC_EXT_TRIG_ADGE_NONE;\
	ADC[0]->IntRefEn = true;\
	ADC[0]->Mode = ADC_MODE_INDEPENDENT;\
	ADC[0]->SampleTime[0] = ADC_SAMPLE_TIME_5;\
	ADC[0]->SampleTime[1] = ADC_SAMPLE_TIME_5;\
	ADC[0]->SampleTime[2] = ADC_SAMPLE_TIME_6;\
	ADC[0]->TempSensorEn = true;\
	ADC[0]->UnitNr = 0;\
	ADC[0]->Prescaller = 2;\
	ADC[0]->ResolutionBits = 12;\
	if(adc_init(ADC[0])) UARTPuts(DebugCom, "OK.\n\r" , -1);\
	else  UARTPuts(DebugCom, "FAILED.\n\r" , -1);
/*#####################################################*/
#endif /* MAIN_H_ */
/*#####################################################*/
