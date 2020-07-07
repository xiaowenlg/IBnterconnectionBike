#ifndef __BSPCONFIG_H
#define __BSPCONFIG_H

//外设接口引脚定义
#define Sensor_Mag_Pin GPIO_PIN_0
#define Sensor_Mag_GPIO_Port GPIOA

#define WTN6040_DATA_Pin GPIO_PIN_12
#define WTN6040_DATA_GPIO_Port GPIOB

#define WTN6040_CLK_Pin GPIO_PIN_13
#define WTN6040_CLK_GPIO_Port GPIOB

#define WTN6040_BUSY_Pin GPIO_PIN_15
#define WTN6040_BUSY_GPIO_Port GPIOB

//设备串口波特率设置
#define BLE_BAND				115200        //蓝牙串口
#define DEBUG_BAND				115200        //调试用串口
#define HMI_BAND				115200		//HML串口屏(淘晶驰)

//串口分配

#define  UART_BLE				&huart1			//蓝牙
#define  UART_CONNECTION		&huart2			//互联接口	
#define  UART_TFT				&huart3			//TFT屏(武汉晶显)


//周期内分段运行
#define TIMER_ALL_PERIOD        10            //单位ms  定时器运行周期(大周期)
//按周期运行

#define PERIOD_DO_EXECUTE(TICK,PERIOD)          ((TICK)%(PERIOD/TIMER_ALL_PERIOD) == 0)

#define TEST_SENSOR_DATA        1000				//检测传感器值
#define ADC_PERIOD				1000
#define MES_PERIOD              200
#endif // !__BSPCONFIG_H
