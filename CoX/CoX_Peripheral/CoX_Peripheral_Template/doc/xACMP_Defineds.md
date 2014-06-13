\page xACMP_page xACMP page 

[TOC]

xACMP document
======
本篇文章主要讲解，CoX.ACMP的规范，包括：
- 宏参数
    - 参数的意义？
    - 传给哪个API？
    - 参数的形式
    - 各个厂商系列的实现情况
- API函数
    - 函数原型
    - 需要实现的功能和每个参数的意义
    - 函数之间的组合应用（功能）

xACMP Positive Source Tab            {#xACMP_Positive_Src_md}
==============
- 这里定义的是ACMP正极输入电压的模式，包括:
    - \ref xACMP_ASRCP_PIN
    - \ref xACMP_ASRCP_REF
- 其中 xACMP_ASRCP_REF 是非强制类型，
	
Source \ Series   | LPC17xx | STM32F1xx | Mini51 | M051 | NUC1xx | NUC122 | NUC123 | NUC2xx | KLx | HT32F125x | HT32F175x |   
----------------- | --------| ----------| -------| -----| -------| -------| -------| -------| ----| ----------| ----------|
xACMP_ASRCP_PIN   |  **N**  |   **Y**   |  **Y** | **Y**|  **Y** |  **Y** |  **Y** |  **Y** |**Y**|   **Y**   |   **Y**   |
xACMP_ASRCP_REF   |  **N**  |   **Y**   |  **N** | **N**|  **N** |  **N** |  **N** |  **N** |**N**|   **N**   |   **N**   |

xACMP Negative Source Tab         {#xACMP_Negative_Src_md}
==============
- 这里定义的是ACMP负极输入电压的模式，包括:
    - \ref xACMP_ASRCN_PIN
    - \ref xACMP_ASRCN_REF
- 其中 xACMP_ASRCN_REF 是非强制类型，
	
  Source\Series   | LPC17xx | STM32F1xx | Mini51 | M051 | NUC1xx | NUC122 | NUC123 | NUC2xx | KLx | HT32F125x | HT32F175x |   
----------------- | --------| ----------| -------| -----| -------| -------| -------| -------| ----| ----------| ----------|
xACMP_ASRCN_PIN   |  **N**  |   **Y**   |  **Y** | **Y**|  **Y** |  **Y** |  **Y** |  **Y** |**Y**|   **Y**   |   **Y**   |
xACMP_ASRCN_REF   |  **N**  |   **Y**   |  **Y** | **Y**|  **Y** |  **Y** |  **Y** |  **Y** |**N**|   **N**   |   **N**   |

xACMP Internal Refrence Voltage Tab         {#xACMP_Int_Ref_Volt_md}
==============
- 这里定义的是ACMP内部参考电压的大小，格式:
    - \ref xACMP_REF_*V 
- Here is a list of the Vref.Values of Vref like xACMP_REF_*V, can be:
    - \ref xACMP_REF_?V - Example 2V
    - \ref xACMP_REF_?_?V - Example 2.1V
    - \ref xACMP_REF_?_??V - Example 2.13V
    - \ref xACMP_REF_?_???V - Example 1.375V
    - \ref xACMP_REF_?_????V - Example 1.2375V，
	
  Source\Series   |     LPC17xx    |    STM32F1xx   |      Mini51     |        M051    |      NUC1xx    |      NUC122    |      NUC123    |      NUC2xx    |        KLx     |    HT32F125x   |    HT32F175x   |   
----------------- | ---------------| ---------------| ----------------| ---------------| ---------------| ---------------| ---------------| ---------------| ---------------| ---------------| ---------------|
xACMP_REF_*V      |      **N**     | xACMP_REF_1_2V | xACMP_REF_1_35V | xACMP_REF_1_2V | xACMP_REF_1_2V | xACMP_REF_1_2V | xACMP_REF_1_2V | xACMP_REF_1_2V | xACMP_REF_1_2V | xACMP_REF_1_2V | xACMP_REF_1_2V |

xACMP Comparator IDs Tab         {#xACMP_Comparator_IDs_md}
==============
- 这里定义的是ACMP比较通道数，包括:
    - \ref xACMP_0
    - \ref xACMP_1
	
IDs\Series | LPC17xx | STM32F1xx | Mini51 | M051 | NUC1xx | NUC122 | NUC123 | NUC2xx | KLx | HT32F125x | HT32F175x |   
-----------| --------| ----------| -------| -----| -------| -------| -------| -------| ----| ----------| ----------|
xACMP_0    |  **N**  |   **Y**   |  **Y** | **Y**|  **Y** |  **Y** |  **Y** |  **Y** |**Y**|   **Y**   |   **Y**   |
xACMP_1    |  **N**  |   **Y**   |  **Y** | **Y**|  **Y** |  **Y** |  **Y** |  **Y** |**Y**|   **Y**   |   **Y**   |
