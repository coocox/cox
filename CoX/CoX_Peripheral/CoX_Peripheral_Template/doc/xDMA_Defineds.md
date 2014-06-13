\page xDMA_page xDMA page 

[TOC]

xDMA document
======
本篇文章主要讲解，CoX.DMA的规范，包括：
- 宏参数
    - 参数的意义？
    - 传给哪个API？
    - 参数的形式
    - 各个厂商系列的实现情况
- API函数
    - 函数原型
    - 需要实现的功能和每个参数的意义
    - 函数之间的组合应用（功能）

xDMA Interrupt Tab             {#xDMA_Interrupt_md}
==============
- 这里定义的是GPIO支持的一些中断类型，包括:
    - \ref xDMA_INT_TC
    - \ref xDMA_INT_ERROR
- 使用了这个宏的API
    -  \ref xDMAChannelIntEnable  <br>
    -  \ref xDMAChannelIntDisable <br>
	-  \ref xDMAChannelIntFlagGet <br>
	-  \ref xDMAChannelIntFlagClear <br>
	
Interrupts\Series | LPC17xx | STM32F1xx | Mini51 | M051 | NUC1xx | NUC122 | NUC123 | NUC2xx | KLx | HT32F125x | HT32F175x |   
----------------- | --------| ----------| -------| -----| -------| -------| -------| -------| ----| ----------| ----------|
xDMA_INT_TC       |  **Y**  |   **Y**   |  **Y** | **Y**|  **Y** |  **Y** |  **Y** |  **Y** |**Y**|   **N**   |   **N**   |
xDMA_INT_ERROR    |  **Y**  |   **Y**   |  **N** | **N**|  **N** |  **N** |  **N** |  **N** |**Y**|   **N**   |   **N**   |

xDMA Interrupt Event Tab         {#xDMA_Event_md}
==============
- 这里定义的是 DMA 支持的一些事件类型，包括:
    - \ref xDMA_EVENT_TC
    - \ref xDMA_EVENT_ERROR
- 使用了这个宏的API
    -  \ref xDMAChannelIntEnable  <br>
    -  \ref xDMAChannelIntDisable <br>
	-  \ref xDMAChannelIntFlagGet <br>
	-  \ref xDMAChannelIntFlagClear <br>
	
Ints_Event\Series | LPC17xx | STM32F1xx | Mini51 | M051 | NUC1xx | NUC122 | NUC123 | NUC2xx | KLx | HT32F125x | HT32F175x |   
----------------- | --------| ----------| -------| -----| -------| -------| -------| -------| ----| ----------| ----------|
xDMA_EVENT_TC     |  **Y**  |   **Y**   |  **Y** | **Y**|  **Y** |  **Y** |  **Y** |  **Y** |**Y**|   **N**   |   **N**   |
xDMA_EVENT_ERROR  |  **Y**  |   **Y**   |  **N** | **N**|  **N** |  **N** |  **N** |  **N** |**Y**|   **N**   |   **N**   |

xDMA Request Connections Mode      {#xDMA_Connect_md}
=====================
- 这组宏定义是 DMA 工作的通道模式：

Request Connect\Series | LPC17xx | STM32F1xx | Mini51 | M051 | NUC1xx | NUC122 | NUC123 | NUC2xx | KLx | HT32F125x | HT32F175x |   
---------------------- | --------| ----------| -------| -----| -------| -------| -------| -------| ----| ----------| ----------|   
xDMA_REQUEST_NOT_EXIST |  **N**  |   **Y**   |  **N** | **N**|  **Y** |  **Y** |  **Y** |  **Y** |**Y**|   **N**   |   **N**   |
xDMA_REQUEST_MEM       |  **N**  |   **Y**   |  **N** | **N**|  **Y** |  **Y** |  **Y** |  **Y** |**Y**|   **N**   |   **N**   |
xDMA_REQUEST_UARTn_RX  |  **N**  |   **Y**   |  **N** | **N**|  **Y** |  **Y** |  **Y** |  **Y** |**Y**|   **N**   |   **N**   |
xDMA_REQUEST_UARTn_TX  |  **N**  |   **Y**   |  **N** | **N**|  **Y** |  **Y** |  **Y** |  **Y** |**Y**|   **N**   |   **N**   |
xDMA_REQUEST_SPIn_RX   |  **N**  |   **Y**   |  **N** | **N**|  **Y** |  **Y** |  **Y** |  **Y** |**Y**|   **N**   |   **N**   |
xDMA_REQUEST_SPIn_TX   |  **N**  |   **Y**   |  **N** | **N**|  **Y** |  **Y** |  **Y** |  **Y** |**Y**|   **N**   |   **N**   | 
xDMA_REQUEST_IISn_RX   |  **N**  |   **Y**   |  **N** | **N**|  **Y** |  **Y** |  **Y** |  **Y** |**N**|   **N**   |   **N**   |
xDMA_REQUEST_IISn_TX   |  **N**  |   **Y**   |  **N** | **N**|  **Y** |  **Y** |  **Y** |  **Y** |**N**|   **N**   |   **N**   |
xDMA_REQUEST_ADC_RX    |  **N**  |   **Y**   |  **N** | **N**|  **Y** |  **Y** |  **Y** |  **Y** |**Y**|   **N**   |   **N**   |


xDMA Channel Tab         {#xDMA_Channel_md}
==============
- 这组宏定义是定义 DMA 所支持的通道数
- 其宏的形式 是 xDMA_CHANNEL_n, 其中 CHANNEL_n 表示 具体的通道，芯片不同 具体支持的n的范围 也会不同。

  Channel\Series  |       LPC17xx    |      STM32F1xx   | Mini51/M051 | NUC1xx/NUC122/NUC123/NUC2xx |        KLx       | HT32F125x/HT32F175x |   
------------------| -----------------| -----------------| ------------------------------------------| -----------------| --------------------|  
xDMA_CHANNEL_n    |        **N**     |  xDMA_CHANNEL_0  |     **N**   |     xDMA_CHANNEL_0          |  xDMA_CHANNEL_0  |        **N**        |
                | |                  |        ...       |             |          ...                |      ...         |                     |
                | |                  |  xDMA_CHANNEL_31 |             |     xDMA_CHANNEL_31         |  xDMA_CHANNEL_63 |                     |

				  
xDMA Attribution Mode               {#xDMA_Attribution_md}
==============
- 这组宏定义是定义 DMA 的 Attribution 模式。包括:
    - \ref xDMA_ATTR_PRIORITY_NORMAL
    - \ref xDMA_ATTR_PRIORITY_HIGH
	
Attribution Mode\Series   | LPC17xx | STM32F1xx | Mini51 | M051 | NUC1xx | NUC122 | NUC123 | NUC2xx | KLx | HT32F125x | HT32F175x |
------------------------- | --------| ----------| -------| -----| -------| -------| -------| -------| ----| ----------| ----------|
xDMA_ATTR_PRIORITY_NORMAL |  **N**  |   **N**   |  **N** | **N**|  **N** |  **N** |  **N** |  **N** |**Y**|   **N**   |   **N**   |
xDMA_ATTR_PRIORITY_HIGH   |  **N**  |   **Y**   |  **N** | **N**|  **N** |  **N** |  **N** |  **N** |**Y**|   **N**   |   **N**   |


xDMA Config Mode             {#xDMA_Config_md}
==============
- 这组宏定义是定义 DMA 通道工作模式。包括:
    - \ref xDMA_DST_INC_n
    - \ref xDMA_SRC_INC_n
	- \ref xDMA_SRC_SIZE_n
	- \ref xDMA_DST_SIZE_n
	- \ref xDMA_ARB_n
	- \ref xDMA_MODE_BASIC
	- \ref xDMA_MODE_AUTO
	
- 这组宏作为 DMAChannelControlSet() 的 ulControl 参数传入。

SlaveSelMode\Series | LPC17xx | STM32F1xx | Mini51 | M051 | NUC1xx | NUC122 | NUC123 | NUC2xx | KLx | HT32F125x | HT32F175x |  
------------------- | --------| ----------| -------| -----| -------| -------| -------| -------| ----| ----------| ----------|
xDMA_DST_INC_8      |  **N**  |   **Y**   |  **N** | **N**|  **Y** |  **Y** |  **Y** |  **Y** |**Y**|   **N**   |   **N**   |
xDMA_DST_INC_16     |  **N**  |   **Y**   |  **N** | **N**|  **Y** |  **Y** |  **Y** |  **Y** |**Y**|   **N**   |   **N**   |
xDMA_DST_INC_32     |  **N**  |   **Y**   |  **N** | **N**|  **Y** |  **Y** |  **Y** |  **Y** |**Y**|   **N**   |   **N**   |
xDMA_SRC_INC_8      |  **N**  |   **Y**   |  **N** | **N**|  **Y** |  **Y** |  **Y** |  **Y** |**Y**|   **N**   |   **N**   |
xDMA_SRC_INC_16     |  **N**  |   **Y**   |  **N** | **N**|  **Y** |  **Y** |  **Y** |  **Y** |**Y**|   **N**   |   **N**   |
xDMA_SRC_INC_32     |  **N**  |   **Y**   |  **N** | **N**|  **Y** |  **Y** |  **Y** |  **Y** |**Y**|   **N**   |   **N**   |
xDMA_SRC_SIZE_8     |  **N**  |   **Y**   |  **N** | **N**|  **Y** |  **Y** |  **Y** |  **Y** |**Y**|   **N**   |   **N**   |
xDMA_SRC_SIZE_16    |  **N**  |   **Y**   |  **N** | **N**|  **Y** |  **Y** |  **Y** |  **Y** |**Y**|   **N**   |   **N**   |
xDMA_SRC_SIZE_32    |  **N**  |   **Y**   |  **N** | **N**|  **Y** |  **Y** |  **Y** |  **Y** |**Y**|   **N**   |   **N**   |
xDMA_DST_SIZE_8     |  **N**  |   **Y**   |  **N** | **N**|  **Y** |  **Y** |  **Y** |  **Y** |**Y**|   **N**   |   **N**   |
xDMA_DST_SIZE_16    |  **N**  |   **Y**   |  **N** | **N**|  **Y** |  **Y** |  **Y** |  **Y** |**Y**|   **N**   |   **N**   |
xDMA_DST_SIZE_32    |  **N**  |   **Y**   |  **N** | **N**|  **Y** |  **Y** |  **Y** |  **Y** |**Y**|   **N**   |   **N**   |
xDMA_MODE_BASIC     |  **N**  |   **N**   |  **N** | **N**|  **N** |  **N** |  **N** |  **N** |**N**|   **N**   |   **N**   |
xDMA_MODE_AUTO      |  **N**  |   **N**   |  **N** | **N**|  **N** |  **N** |  **N** |  **N** |**N**|   **N**   |   **N**   |
