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
#endif // !__BSPCONFIG_H