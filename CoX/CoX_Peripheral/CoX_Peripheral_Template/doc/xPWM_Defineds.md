\page xPWM_page xPWM page 

[TOC]

xPWM document
======
本篇文章主要讲解，CoX.PWM的规范，包括：
- 宏参数
    - 参数的意义？
    - 传给哪个API？
    - 参数的形式
    - 各个厂商系列的实现情况
- API函数
    - 函数原型
    - 需要实现的功能和每个参数的意义
    - 函数之间的组合应用（功能）

CoX PWM Output Mode Tab   {#xPWM_Config_Mode_md}
====================
- 这里定义的是PWM工作的一些模式，包括:
    - 单次输出(非强制) \ref xPWM_ONE_SHOT_MODE
    - 触发输出(非强制) \ref xPWM_TOGGLE_MODE
    - 电平反转输出 \ref xPWM_OUTPUT_INVERTER_EN
    - 电平不反转输出 \ref xPWM_OUTPUT_INVERTER_DIS
    - 死区开启输出 \ref xPWM_DEAD_ZONE_EN
    - 死区关闭输出 \ref xPWM_DEAD_ZONE_DIS
- 这组宏作为 xPWMInitConfigure() 的ulConfig参数传入。

   PWM Mode\Series      | LPC17xx | STM32F1xx | Mini51 | M051 | NUC1xx | NUC122 | NUC123 | NUC2xx | KLx | HT32F125x | HT32F175x |   
----------------------- | --------| ----------| -------| -----| -------| -------| -------| -------| ----| ----------| ----------|   
xPWM_ONE_SHOT_MODE      |  **Y**  |   **N**   |  **Y** | **Y**|  **N** |  **Y** |  **Y** |  **Y** |**Y**|   **Y**   |   **Y**   |
xPWM_TOGGLE_MODE        |  **Y**  |   **Y**   |  **Y** | **Y**|  **N** |  **Y** |  **Y** |  **Y** |**Y**|   **Y**   |   **Y**   |
xPWM_OUTPUT_INVERTER_EN |  **N**  |   **Y**   |  **Y** | **N**|  **Y** |  **Y** |  **Y** |  **Y** |**N**|   **N**   |   **N**   |
xPWM_OUTPUT_INVERTER_DIS|  **N**  |   **Y**   |  **Y** | **N**|  **Y** |  **Y** |  **Y** |  **Y** |**N**|   **N**   |   **N**   |
xPWM_DEAD_ZONE_EN       |  **N**  |   **Y**   |  **Y** | **N**|  **Y** |  **Y** |  **Y** |  **Y** |**N**|   **N**   |   **N**   |
xPWM_DEAD_ZONE_DIS      |  **N**  |   **Y**   |  **Y** | **N**|  **Y** |  **Y** |  **Y** |  **Y** |**N**|   **N**   |   **N**   |

xPWM Channel Tab         {#xPWM_Config_Channel_md}
==============
- 这组宏定义是定义 PWM 输出通道数
- 其宏的形式 是 xPWM_CHANNELn，其中CHANNELn表示 具体的通道，芯片不同 具体支持的n的范围也会不同。
- 使用了这个宏的API
    -  \ref xPWMStart <br>
	-  \ref xPWMInitConfigure <br>
	-  \ref xPWMFrequencySet <br>
	-  \ref xPWMFrequencyConfig <br>
	-  \ref xPWMFrequencyGet <br>
	-  \ref xPWMOutputEnable <br>
	-  \ref xPWMOutputDisable <br>
	-  \ref xPWMStart <br>
	-  \ref xPWMStop <br>
	-  \ref xPWMDutySet <br>
	-  \ref xPWMDutyGet <br>
	-  \ref xPWMIntEnable <br>
	-  \ref xPWMIntDisable <br>
	-  \ref xPWMIntFlagGet <br>

  Channel\Series  |       LPC17xx    |    STM32F1xx   |     Mini51    |   M051/NUC1xx | NUC2xx/NUC122/NUC123 |        KLx       | HT32F125x/HT32F175x |   
------------------| -----------------| ---------------| --------------|---------------| ---------------------| -----------------| --------------------|  
xPWM_CHANNELn     | xPWM_CHANNEL0    | xPWM_CHANNEL0  | xPWM_CHANNEL0 | xPWM_CHANNEL0 |     xPWM_CHANNEL0    |   xPWM_CHANNEL0  |    xPWM_CHANNEL0    |
                | |        ...       |        ...     |      ...      |   ...         |           ...        |                  |          ...        |
                | | xPWM_CHANNEL7    | xPWM_CHANNEL3  | xPWM_CHANNEL5 | xPWM_CHANNEL7 |     xPWM_CHANNEL3    |   xPWM_CHANNEL5  |    xPWM_CHANNEL7    |


xPWM Interrupt Tab             {#xPWM_Config_Interrupt_md}
==============
- 这里定义的是PWM支持的一些中断类型，包括:
    - \ref xPWM_INT_PWM
- 使用了这个宏的API
    -  \ref xPWMIntEnable <br>
    -  \ref xPWMIntDisable <br>
	-  \ref xPWMIntFlagGet  <br>
	
Interrupts\Series | LPC17xx | STM32F1xx | Mini51 | M051 | NUC1xx | NUC122 | NUC123 | NUC2xx | KLx | HT32F125x | HT32F175x |   
----------------- | --------| ----------| -------| -----| -------| -------| -------| -------| ----| ----------| ----------|
xPWM_INT_PWM      |  **Y**  |   **Y**   |  **Y** | **Y**|  **Y** |  **Y** |  **Y** |  **Y** |**Y**|   **Y**   |   **Y**   |


xPWM Interrupt Event Tab         {#xPWM_Config_Event_md}
==============
- 这里定义的是SPI支持的一些时间类型，包括:
    - \ref xPWM_EVENT_PWM
    - \ref xPWM_EVENT_CAP
- 其中xPWM_EVENT_CAP是非强制类型，
- 使用了这个宏的API
    -  \ref xPWMIntEnable <br>
    -  \ref xPWMIntDisable <br>
	-  \ref xPWMIntFlagGet  <br>
	
Ints_Event\Series | LPC17xx | STM32F1xx | Mini51 | M051 | NUC1xx | NUC122 | NUC123 | NUC2xx | KLx | HT32F125x | HT32F175x |   
----------------- | --------| ----------| -------| -----| -------| -------| -------| -------| ----| ----------| ----------|
xPWM_EVENT_PWM    |  **Y**  |   **Y**   |  **Y** | **Y**|  **Y** |  **Y** |  **Y** |  **Y** |**Y**|   **Y**   |   **Y**   |
xPWM_EVENT_CAP    |  **Y**  |   **N**   |  **Y** | **Y**|  **Y** |  **Y** |  **Y** |  **Y** |**N**|   **N**   |   **N**   |
