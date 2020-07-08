#ifndef __BSPCONFIG_H
#define __BSPCONFIG_H

//����ӿ����Ŷ���
#define Sensor_Mag_Pin GPIO_PIN_0
#define Sensor_Mag_GPIO_Port GPIOA

#define WTN6040_DATA_Pin GPIO_PIN_12
#define WTN6040_DATA_GPIO_Port GPIOB

#define WTN6040_CLK_Pin GPIO_PIN_13
#define WTN6040_CLK_GPIO_Port GPIOB

#define WTN6040_BUSY_Pin GPIO_PIN_15
#define WTN6040_BUSY_GPIO_Port GPIOB

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
#define S_THISSPORT         13				//��������ˣ�
#define S_SPORTTIM          14              //�ʱ��
#define S_THISKCAL          15				//��������
#define S_NUMBER			16				//��
#define S_HOUR				17				//ʱ
#define S_MINUTE            18				//��
#define S_SECOND			19				//��
#define S_KCAL              20				//ǧ��
#define S_POINT             21           //�� ��ַ
#define S_WELCOME           22				//��ӭ�ٴ�ʹ��
#define S_MAXSPORT_TIP		0x20            //�˶�Ƶ�ʹ�����ʾ


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

#endif // !__BSPCONFIG_H
