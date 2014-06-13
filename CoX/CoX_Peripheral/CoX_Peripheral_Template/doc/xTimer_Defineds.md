\page xTimer_page xTimer page 

[TOC]

xTimer document
======
本篇文章主要讲解，CoX.Timer 的规范，包括：
- 宏参数
    - 参数的意义？
    - 传给哪个API？
    - 参数的形式
    - 各个厂商系列的实现情况
- API函数
    - 函数原型
    - 需要实现的功能和每个参数的意义
    - 函数之间的组合应用（功能）

CoX Timer Output Mode Tab   {#xTimer_Config_Mode_md}
====================
- 这里定义的是PWM工作的一些模式，包括:
    - 单次计时 \ref xTIMER_MODE_ONESHOT
    - 周期计时 \ref xTIMER_MODE_PERIODIC
    - 触发计时 \ref xTIMER_MODE_TOGGLE
    - 继续计时(非强制) \ref xTIMER_MODE_CONTINUOUS
    - 捕获计时(非强制) \ref xTIMER_MODE_CAPTURE
    - PWM模式(非强制)  \ref xTIMER_MODE_PWM
- 这组宏作为 xTimerInitConfig() 的 ulConfig 参数传入。

 Timer Mode\Series      | LPC17xx | STM32F1xx | Mini51 | M051 | NUC1xx | NUC122 | NUC123 | NUC2xx | KLx | HT32F125x | HT32F175x |   
----------------------- | --------| ----------| -------| -----| -------| -------| -------| -------| ----| ----------| ----------|   
xTIMER_MODE_ONESHOT     |  **Y**  |   **Y**   |  **Y** | **Y**|  **Y** |  **Y** |  **Y** |  **Y** |**Y**|   **Y**   |   **Y**   |
xTIMER_MODE_PERIODIC    |  **Y**  |   **Y**   |  **Y** | **Y**|  **Y** |  **Y** |  **Y** |  **Y** |**Y**|   **Y**   |   **Y**   |
xTIMER_MODE_TOGGLE      |  **N**  |   **Y**   |  **Y** | **Y**|  **Y** |  **Y** |  **Y** |  **Y** |**N**|   **Y**   |   **Y**   |
xTIMER_MODE_CONTINUOUS  |  **Y**  |   **N**   |  **Y** | **Y**|  **Y** |  **Y** |  **Y** |  **Y** |**N**|   **Y**   |   **Y**   |
xTIMER_MODE_CAPTURE     |  **Y**  |   **Y**   |  **N** | **Y**|  **N** |  **N** |  **N** |  **N** |**N**|   **Y**   |   **Y**   |
xTIMER_MODE_PWM         |  **N**  |   **Y**   |  **N** | **N**|  **N** |  **N** |  **N** |  **N** |**N**|   **Y**   |   **Y**   |

xTimer Interrupt Tab             {#xTimer_Config_Interrupt_md}
==============
- 这里定义的是PWM支持的一些中断类型，包括:
    - \ref xTIMER_INT_MATCH
	- \ref xTIMER_INT_CAP_EVENT
	- \ref xTIMER_INT_CAP_MATCH
	- \ref xTIMER_INT_OVERFLOW
	- \ref xTIMER_INT_PWM
- 其中 xTIMER_INT_CAP_MATCH、xTIMER_INT_OVERFLOW、xTIMER_INT_PWM 是非强制。
- 使用了这个宏的API
    -  \ref xTimerIntEnable <br>
    -  \ref xTimerIntDisable <br>
	-  \ref xTimerIntStatus <br>
	-  \ref xTimerIntClear  <br>
	
Interrupts\Series    | LPC17xx | STM32F1xx | Mini51 | M051 | NUC1xx | NUC122 | NUC123 | NUC2xx | KLx | HT32F125x | HT32F175x |   
-------------------- | --------| ----------| -------| -----| -------| -------| -------| -------| ----| ----------| ----------|
xTIMER_INT_MATCH     |  **Y**  |   **Y**   |  **Y** | **Y**|  **Y** |  **Y** |  **Y** |  **Y** |**Y**|   **Y**   |   **Y**   |
xTIMER_INT_CAP_EVENT |  **Y**  |   **Y**   |  **Y** | **Y**|  **Y** |  **N** |  **Y** |  **Y** |**Y**|   **Y**   |   **Y**   | 
xTIMER_INT_CAP_MATCH |  **N**  |   **Y**   |  **N** | **N**|  **N** |  **N** |  **N** |  **N** |**Y**|   **N**   |   **N**   |
xTIMER_INT_OVERFLOW  |  **N**  |   **N**   |  **N** | **N**|  **N** |  **N** |  **N** |  **N** |**Y**|   **N**   |   **N**   |
xTIMER_INT_PWM       |  **N**  |   **N**   |  **N** | **N**|  **N** |  **N** |  **N** |  **N** |**Y**|   **N**   |   **N**   |

xTimer Interrupt Event Tab         {#xTimer_Config_Event_md}
==============
- 这里定义的是SPI支持的一些时间类型，包括:
    - \ref xTIMER_EVENT_MATCH
    - \ref xTIMER_EVENT_CAP_EVENT
	- \ref xTIMER_EVENT_CAP_MATCH
	- \ref xTIMER_EVENT_OVERFLOW
	- \ref xTIMER_EVENT_PWM
- 其中 xTIMER_EVENT_CAP_MATCH、xTIMER_EVENT_OVERFLOW、xPWM_EVENT_CAP 是非强制类型，
- 使用了这个宏的API
    -  \ref xTimerIntEnable <br>
    -  \ref xTimerIntDisable <br>
	-  \ref xTimerIntStatus  <br>
	-  \ref xTimerIntClear  <br>
	
Interrupt Event\Series | LPC17xx | STM32F1xx | Mini51 | M051 | NUC1xx | NUC122 | NUC123 | NUC2xx | KLx | HT32F125x | HT32F175x |   
---------------------- | --------| ----------| -------| -----| -------| -------| -------| -------| ----| ----------| ----------|
xTIMER_EVENT_MATCH     |  **Y**  |   **Y**   |  **Y** | **Y**|  **Y** |  **Y** |  **Y** |  **Y** |**Y**|   **Y**   |   **Y**   |
xTIMER_EVENT_CAP_EVENT |  **Y**  |   **Y**   |  **Y** | **Y**|  **Y** |  **N** |  **Y** |  **Y** |**N**|   **Y**   |   **Y**   |
xTIMER_EVENT_CAP_MATCH |  **N**  |   **N**   |  **N** | **N**|  **N** |  **N** |  **N** |  **N** |**Y**|   **N**   |   **N**   |
xTIMER_EVENT_OVERFLOW  |  **N**  |   **N**   |  **N** | **N**|  **N** |  **N** |  **N** |  **N** |**Y**|   **N**   |   **N**   |
xTIMER_EVENT_PWM       |  **N**  |   **N**   |  **N** | **N**|  **N** |  **N** |  **N** |  **N** |**Y**|   **N**   |   **N**   |


xTimer Channel Tab         {#xTimer_Config_Channel_md}
==============
- 这组宏定义是定义 PWM 输出通道数
- 其宏的形式 是 xTIMER_CHANNELn，其中CHANNELn表示 具体的通道，芯片不同 具体支持的n的范围也会不同。
- 该参数将作为所有 Timer的APIs的 ulChannel 参数传入，具体可以参照 APIs List。

  Channel\Series  |       LPC17xx    |    STM32F1xx    |       Mini51    |    M051/NUC1xx  | NUC2xx/NUC122/NUC123 |        KLx       | HT32F125x/HT32F175x |   
------------------| -----------------| ----------------| ----------------|-----------------| ---------------------| -----------------| --------------------|  
xTIMER_CHANNELn   | xTIMER_CHANNEL0  | xTIMER_CHANNEL0 | xTIMER_CHANNEL0 | xTIMER_CHANNEL0 |   xTIMER_CHANNEL0    | xTIMER_CHANNEL0  |  xTIMER_CHANNEL0    |
                | |                  |       ...       |                 |                 |                      |      ...         |        ...          |
                | | xTIMER_CHANNEL1  | xTIMER_CHANNEL3 |                 |                 |                      | xTIMER_CHANNEL3  |  xTIMER_CHANNEL3    |

				
xTimer Counter Type Tab         {#xTimer_Counter_Type_md}
==============
- 这组宏是定义 Timer 在外部管脚计数模式：处于上升沿或下降沿
    - \ref xTIMER_COUNTER_RISING
    - \ref xTIMER_COUNTER_FALLING	
- 该参数将作为 xTimerCounterDetectPhaseSelect() 的 ulPhase 参数传入。

  Counter Type\Series  | LPC17xx | STM32F1xx | Mini51 | M051 | NUC1xx | NUC122 | NUC123 | NUC2xx | KLx | HT32F125x | HT32F175x |   
---------------------- | --------| ----------| -------| -----| -------| -------| -------| -------| ----| ----------| ----------|
xTIMER_COUNTER_RISING  |  **Y**  |   **Y**   |  **Y** | **Y**|  **Y** |  **Y** |  **Y** |  **Y** |**Y**|   **Y**   |   **Y**   |
xTIMER_COUNTER_FALLING |  **Y**  |   **Y**   |  **Y** | **Y**|  **Y** |  **N** |  **Y** |  **Y** |**N**|   **Y**   |   **Y**   |


xTimer Counter Direction Tab         {#xTimer_Counter_Direction_md}
==============
- 这组宏是定义 Timer 计数方向：向上计数或者向下计数
    - \ref xTIMER_COUNT_UP
    - \ref xTIMER_COUNT_DOWN
- 其中 xTIMER_COUNT_DOWN 是非强制类型
- 该参数将作为 xTimerInitConfig() 的 ulConfig 参数传入。

Counter Direction\Series | LPC17xx | STM32F1xx | Mini51 | M051 | NUC1xx | NUC122 | NUC123 | NUC2xx | KLx | HT32F125x | HT32F175x |   
------------------------ | --------| ----------| -------| -----| -------| -------| -------| -------| ----| ----------| ----------|
xTIMER_COUNT_UP          |  **Y**  |   **Y**   |  **Y** | **Y**|  **Y** |  **Y** |  **Y** |  **Y** |**Y**|   **Y**   |   **Y**   |
xTIMER_COUNT_DOWN        |  **N**  |   **Y**   |  **N** | **N**|  **N** |  **N** |  **N** |  **N** |**N**|   **N**   |   **N**   |



xTimer Capture Type Tab         {#xTimer_Capture_Type_md}
==============
- 这组宏是定义 Timer 捕获边沿的规则：
    - \ref xTIMER_CAP_RISING
    - \ref xTIMER_CAP_FALLING	
	- \ref xTIMER_CAP_BOTH
- 其中 xTIMER_CAP_BOTH 是非强制类型
- 该参数将作为 xTimerCaptureEdgeSelect() 的 ulPhase 参数传入。

  Capture Type\Series  | LPC17xx | STM32F1xx | Mini51 | M051 | NUC1xx | NUC122 | NUC123 | NUC2xx | KLx | HT32F125x | HT32F175x |   
---------------------- | --------| ----------| -------| -----| -------| -------| -------| -------| ----| ----------| ----------|
xTIMER_CAP_RISING      |  **Y**  |   **Y**   |  **Y** | **Y**|  **Y** |  **N** |  **Y** |  **Y** |**Y**|   **Y**   |   **Y**   |
xTIMER_CAP_FALLING     |  **Y**  |   **Y**   |  **Y** | **Y**|  **Y** |  **N** |  **Y** |  **Y** |**Y**|   **Y**   |   **N**   |
xTIMER_CAP_BOTH        |  **Y**  |   **N**   |  **Y** | **Y**|  **Y** |  **N** |  **Y** |  **Y** |**N**|   **N**   |   **N**   |


xTimer Capture Mode Tab         {#xTimer_Capture_Mode_md}
==============
- 这组宏是定义 Timer 捕获模式：
    - \ref xTIMER_CAP_MODE_CAP
    - \ref xTIMER_CAP_MODE_RST
- 其中 xTIMER_CAP_MODE_RST 是非强制类型
- 该参数将作为 xTimerCaptureEdgeSelect() 的 ulPhase 参数传入。

  Capture Mode\Series  | LPC17xx | STM32F1xx | Mini51 | M051 | NUC1xx | NUC122 | NUC123 | NUC2xx | KLx | HT32F125x | HT32F175x |   
---------------------- | --------| ----------| -------| -----| -------| -------| -------| -------| ----| ----------| ----------|
xTIMER_CAP_MODE_CAP    |  **Y**  |   **Y**   |  **Y** | **Y**|  **Y** |  **N** |  **Y** |  **Y** |**Y**|   **Y**   |   **Y**   |
xTIMER_CAP_MODE_RST    |  **N**  |   **Y**   |  **Y** | **Y**|  **Y** |  **N** |  **Y** |  **Y** |**N**|   **N**   |   **N**   |
