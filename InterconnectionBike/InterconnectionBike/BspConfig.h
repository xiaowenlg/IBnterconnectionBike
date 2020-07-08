#ifndef __BSPCONFIG_H
#define __BSPCONFIG_H
#include "stdint.h"
#include "stm32f1xx_hal.h"
#include "system.h"
//����ӿ����Ŷ���
#define REED_Pin GPIO_PIN_0   //�ɻɹ�����
#define REED_GPIO_Port GPIOA
#define REED_EXTI_IRQn EXTI0_IRQn

//------------------------------------------ ����оƬWTN6040
#define WTN_BUSY_Pin			GPIO_PIN_15//æ����
#define WTN_GPIO_Port			GPIOB
#define WTN_BUSY_EXTI_IRQn		EXTI15_10_IRQn
#define  CLK_2A                 PBout(13) //ʱ�������λ��������
#define  P_DATA_2A               PBout(12) //���������λ��������
#define  CLK_2A_PIN             GPIO_PIN_13//ʱ������
#define  P_DATA_2A_PIN          GPIO_PIN_12//��������
#define  SYSCLOSE_PIN		GPIO_PIN_8 //�ر�ϵͳ���ţ��ߵ�ƽ�ر�
#define  SYSCLOSE_PORT		GPIOB
#define  SYSIO				PBout(8)   //λ������




#define  SYSCLOSE_PIN		GPIO_PIN_8 //�ر�ϵͳ���ţ��ߵ�ƽ�ر�
#define  SYSCLOSE_PORT		GPIOB
#define  SYSIO				PBout(8)   //λ������

//�豸���ڲ���������
#define BLE_BAND				115200        //��������
#define DEBUG_BAND				115200        //�����ô���
#define HMI_BAND				115200		//HML������(�Ծ���)

//���ڷ���

#define  UART_BLE				&huart1			//����
#define  UART_CONNECTION		&huart2			//�����ӿ�	
#define  UART_TFT				&huart3			//TFT��(�人����)


//�����ڷֶ�����
#define TIMER_ALL_PERIOD        10            //��λms  ��ʱ����������(������)
//����������

#define PERIOD_DO_EXECUTE(TICK,PERIOD)          ((TICK)%(PERIOD/TIMER_ALL_PERIOD) == 0)

#define TEST_SENSOR_DATA        1000				//��⴫����ֵ
#define SENDDATA				100
#define MES_PERIOD              200
#define TIMER2_PLAY_WAIT          5                 //�ȴ�����ʱ�䣬��λ��s
//������ַ
#define S_TEN               10               //ʮ
#define S_HUNDRED			11				//��
#define S_THOUSAND          12				//ǧ
#define S_THISSPORT         0x00		    //��������ˣ�
#define S_SPORTTIM          0x19              //�ʱ��
#define S_THISKCAL          0x02				//��������
#define S_NUMBER			0x01			//��
#define S_HOUR				0x12				//ʱ
#define S_MINUTE            0x13				//��
#define S_SECOND			0x14				//��
#define S_KCAL              0x03				//ǧ��
#define S_POINT             21           //�� ��ַ
#define S_WELCOME           0x04				//��ӭ�ٴ�ʹ��
#define S_MAXSPORT_TIP		0x20            //�˶�Ƶ�ʹ�����ʾ

#define PLAYARRAYLENGTH        50			//�������鳤��
//��Ϣ
#define WEIGHT 60.00                     //����
//�˶���Ϣ�ṹ��
typedef struct SportInfo      //�˶���Ϣ
{
	uint16_t count;//�˶�����
	uint16_t freq;//�˶�Ƶ��
	long hot;//��������
	uint16_t tim;//�˶�ʱ��
	uint8_t    playstate;//����״̬
}Customerinfo;
//������Ϣ�б�
#define ERROR_XQUEUE_CREAT				0x01			//��Ϣ���д�������

//

#endif // !__BSPCONFIG_H
