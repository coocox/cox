\page xSPI_page xSPI page 

[TOC]

xSPI document
======
本篇文章主要讲解，CoX.SPI的规范，包括：
- 宏参数
    - 参数的意义？
    - 传给哪个API？
    - 参数的形式
    - 各个厂商系列的实现情况
- API函数
    - 函数原型
    - 需要实现的功能和每个参数的意义
    - 函数之间的组合应用（功能）

CoX SPI Data Format Base Tab   {#xSPI_Config_Fomart_md}
====================
- 这里定义的是SPI支持的一些传输格式，包括:
    - TI(非强制) \ref xSPI_TI_FORMAT_MODE
    - NMW(非强制) \ref xSPI_NMW_FORMAT_MODE
    - moto0 \ref xSPI_MOTO_FORMAT_MODE_0
    - moto1 \ref xSPI_MOTO_FORMAT_MODE_1
    - moto2 \ref xSPI_MOTO_FORMAT_MODE_2
    - moto3 \ref xSPI_MOTO_FORMAT_MODE_3
- 这组宏作为 xSPIConfigSet() 的ulConfig参数传入。

Data Format\Series      | LPC17xx | STM32F1xx | Mini51 | M051 | NUC1xx | NUC122 | NUC123 | NUC2xx | KLx | HT32F125x | HT32F175x |   
----------------------- | --------| ----------| -------| -----| -------| -------| -------| -------| ----| ----------| ----------|   
xSPI_TI_FORMAT_MODE     |    N    |     N     |    N   |   N  |    N   |    N   |    N   |    N   |  N  |     N     |     N     |
xSPI_NMW_FORMAT_MODE    |    N    |     N     |    N   |   N  |    N   |    N   |    N   |    N   |  N  |     N     |     N     |
xSPI_MOTO_FORMAT_MODE_0 |    Y    |     Y     |    Y   |   Y  |    Y   |    Y   |    Y   |    Y   |  Y  |     Y     |     Y     |
xSPI_MOTO_FORMAT_MODE_1 |    Y    |     Y     |    Y   |   Y  |    Y   |    Y   |    Y   |    Y   |  Y  |     Y     |     Y     |
xSPI_MOTO_FORMAT_MODE_2 |    Y    |     Y     |    Y   |   Y  |    Y   |    Y   |    Y   |    Y   |  Y  |     Y     |     Y     |
xSPI_MOTO_FORMAT_MODE_3 |    Y    |     Y     |    Y   |   Y  |    Y   |    Y   |    Y   |    Y   |  Y  |     Y     |     Y     |

xSPI Master/Slave Mode      {#xSPI_Config_Master_md}
=====================
- 这组宏定义是SPI的工作模式：主模式(xSPI_MODE_MASTER)或者从模式(xSPI_MODE_SLAVE)

Operating Mode\Series | LPC17xx | STM32F1xx | Mini51 | M051 | NUC1xx | NUC122 | NUC123 | NUC2xx | KLx | HT32F125x | HT32F175x |   
--------------------- | --------| ----------| -------| -----| -------| -------| -------| -------| ----| ----------| ----------|   
xSPI_MODE_MASTER      |    Y    |     Y     |    Y   |   Y  |    Y   |    Y   |    Y   |    Y   |  Y  |     Y     |     Y     |
xSPI_MODE_SLAVE       |    Y    |     Y     |    Y   |   Y  |    Y   |    Y   |    Y   |    Y   |  Y  |     Y     |     Y     |

xSPI SPI MSB/LSB Mode       {#xSPI_Config_MSB_md}
====================
- 这组宏定义是SPI传输数据的模式：高位(BIT7)先传送(xSPI_MSB_FIRST)或者低位(BIT0)先传送(xSPI_LSB_FIRST)

Operating Mode\Series | LPC17xx | STM32F1xx | Mini51 | M051 | NUC1xx | NUC122 | NUC123 | NUC2xx | KLx | HT32F125x | HT32F175x |   
--------------------- | --------| ----------| -------| -----| -------| -------| -------| -------| ----| ----------| ----------|   
xSPI_MSB_FIRST        |    Y    |     Y     |    Y   |   Y  |    Y   |    Y   |    Y   |    Y   |  Y  |     Y     |     Y     |
xSPI_LSB_FIRST        |    Y    |     Y     |    Y   |   Y  |    Y   |    Y   |    Y   |    Y   |  Y  |     Y     |     Y     |


xSPI Data Width Tab         {#xSPI_Config_DataWidth_md}
==============
- 这组宏定义是定义 SPI一次传送的数据位数
- 其宏的形式 是 xSPI_DATA_WIDTHn，其中WIDTHn表示 具体的位数，芯片不同 具体支持的n的范围 也会不同。

Data Width\Series |       LPC17xx    |      STM32F1xx   | Mini51/M051/NUC1xx/NUC122/NUC123/NUC2xx |        KLx       | HT32F125x/HT32F175x |   
------------------| -----------------| -----------------| ----------------------------------------| -----------------| --------------------|  
xSPI_DATA_WIDTHn  | xSPI_DATA_WIDTH8 | xSPI_DATA_WIDTH1 |           xSPI_DATA_WIDTH1              | xSPI_DATA_WIDTH8 |  xSPI_DATA_WIDTH1   |
                | |        ...       |        ...       |                   ...                   |                  |          ...        |
                | | xSPI_DATA_WIDTH16| xSPI_DATA_WIDTH16|           xSPI_DATA_WIDTH32             |                  |  xSPI_DATA_WIDTH16  |

				  
xSPI DMA Mode               {#xSPI_Config_DMA_md}
==============
- 这组宏定义是定义 SPI是否工作在DMA模式下。包括:
    - \ref xSPI_DMA_TX
    - \ref xSPI_DMA_RX
	- \ref xSPI_DMA_BOTH
-其中xSPI_DMA_BOTH是非强制类型，

DMA Mode\Series | LPC17xx | STM32F1xx | Mini51 | M051 | NUC1xx | NUC122 | NUC123 | NUC2xx | KLx | HT32F125x | HT32F175x |
--------------- | --------| ----------| -------| -----| -------| -------| -------| -------| ----| ----------| ----------|
xSPI_DMA_TX     |    N    |     Y     |    N   |   N  |    Y   |    N   |    Y   |    Y   |  Y  |     N     |     Y     |
xSPI_DMA_RX     |    N    |     Y     |    N   |   N  |    Y   |    N   |    Y   |    Y   |  Y  |     N     |     Y     |
xSPI_DMA_BOTH   |    N    |     Y     |    N   |   N  |    Y   |    N   |    Y   |    Y   |  N  |     N     |     N     |


xSPI Slave Select Mode             {#xSPI_Config_SlaveSel_md}
==============
- 这组宏定义是定义 SPI的SS管脚工作模式。包括:
    - \ref xSPI_SS_HARDWARE
    - \ref xSPI_SS_SOFTWARE

SlaveSelMode\Series | LPC17xx | STM32F1xx | Mini51 | M051 | NUC1xx | NUC122 | NUC123 | NUC2xx | KLx | HT32F125x | HT32F175x |  
------------------- | --------| ----------| -------| -----| -------| -------| -------| -------| ----| ----------| ----------|
xSPI_SS_HARDWARE    |    Y    |     Y     |    Y   |   Y  |    Y   |    Y   |    Y   |    Y   |  Y  |     Y     |     Y     |
xSPI_SS_SOFTWARE    |    N    |     Y     |    Y   |   Y  |    Y   |    Y   |    Y   |    Y   |  N  |     Y     |     Y     |


xSPI SS(Slave Select) Pin Tab    {#xSPI_Config_SSPin_md}
==============
- 这组宏定义是定义 SPI可使用的SS管脚集合。包括:
    - \ref xSPI_SS_NONE
    - \ref xSPI_SSn
-其中xSPI_DMA_BOTH是非强制类型，

SS_Pin\Series | LPC17xx | STM32F1xx | Mini51 | M051 | NUC1xx | NUC122 | NUC123 | NUC2xx | KLx | HT32F125x | HT32F175x |   
------------- | --------| ----------| -------| -----| -------| -------| -------| -------| ----| ----------| ----------|
xSPI_SS_NONE  |    N    |     Y     |    Y   |   Y  |    Y   |    Y   |    Y   |    Y   |  Y  |     Y     |     Y     |
xSPI_SSn      |    N    |     Y     |    Y   |   Y  |    Y   |    Y   |    Y   |    Y   |  N  |     N     |     N     |
xSPI_SS1      |    N    |     N     |    N   |   N  |    Y   |    Y   |    Y   |    Y   |  N  |     N     |     N     |
xSPI_SS01     |    N    |     N     |    N   |   N  |    Y   |    Y   |    Y   |    Y   |  N  |     N     |     N     |


xSPI Interrupt Tab             {#xSPI_Config_Interrupt_md}
==============
- 这组宏定义是定义 SPI是否工作在DMA模式下。包括:
    - \ref xSPI_INT_EOT
    - \ref xSPI_INT_TX
	- \ref xSPI_INT_RX
	- \ref xSPI_INT_ERROR
-其中xSPI_DMA_BOTH是非强制类型，

Interrupts\Series | LPC17xx | STM32F1xx | Mini51 | M051 | NUC1xx | NUC122 | NUC123 | NUC2xx | KLx | HT32F125x | HT32F175x |   
----------------- | --------| ----------| -------| -----| -------| -------| -------| -------| ----| ----------| ----------|
xSPI_INT_EOT      |    Y    |     Y     |    Y   |   Y  |    Y   |    Y   |    Y   |    Y   |  Y  |     Y     |     Y     |
xSPI_INT_TX       |    Y    |     Y     |    N   |   N  |    N   |    N   |    N   |    N   |  Y  |     Y     |     Y     |
xSPI_INT_RX       |    Y    |     Y     |    N   |   N  |    N   |    N   |    N   |    N   |  Y  |     Y     |     Y     |
xSPI_INT_ERROR    |    Y    |     Y     |    N   |   N  |    N   |    N   |    N   |    N   |  Y  |     Y     |     Y     |

xSPI Interrupt Event Tab         {#xSPI_Config_Event_md}
==============
- 这组宏定义是定义 SPI是否工作在DMA模式下。包括:
    - \ref xSPI_EVENT_EOT
    - \ref xSPI_EVENT_TX
	- \ref xSPI_EVENT_RX
	- \ref xSPI_EVENT_ERROR
	
-其中xSPI_DMA_BOTH是非强制类型，

Ints_Event\Series | LPC17xx | STM32F1xx | Mini51 | M051 | NUC1xx | NUC122 | NUC123 | NUC2xx | KLx | HT32F125x | HT32F175x |   
----------------- | --------| ----------| -------| -----| -------| -------| -------| -------| ----| ----------| ----------|
xSPI_EVENT_EOT    |    Y    |     Y     |    Y   |   Y  |    Y   |    Y   |    Y   |    Y   |  Y  |     Y     |     Y     |
xSPI_EVENT_TX     |    Y    |     N     |    N   |   N  |    N   |    N   |    N   |    N   |  Y  |     Y     |     Y     |
xSPI_EVENT_RX     |    Y    |     N     |    N   |   N  |    N   |    N   |    N   |    N   |  Y  |     Y     |     Y     |
xSPI_EVENT_ERROR  |    Y    |     N     |    N   |   N  |    N   |    N   |    N   |    N   |  N  |     Y     |     Y     |
