\page xmenmap_page xmenmap page 

[TOC]






CoX xlowlayer memory map template              {#xlowlayerBaseTemplate}
========
CoX xlowlayer memory map template是ARM Cortex MCU存储分布的通用强制接口的模板，每个存储接口取得是所有系列MCU拥有的外设资源的并集，即涵盖了所有的存储接口。同时也分别列出了各个系列MCU所拥有的存储接口的范围。

> **NOTE:**
>
> 这里的存储接口的范围是指各个外设Base编号的范围。


# GPIO base Table               {#GPIOBaseTemplate}

以下几个表展示了GPIO外设存储接口范围的模板（n从A到H）, 同时也展示了已有的各个CoX系列的GPIO Port Base分布情况。
xGPIO_PORTn_BASE| LPC17xx        | STM32F1xx      |  Mini51        | M051           
----------------|----------------|----------------|----------------|----------------
xGPIO_PORTA_BASE|xGPIO_PORTA_BASE|xGPIO_PORTA_BASE|xGPIO_PORTA_BASE|xGPIO_PORTA_BASE
...             |...             |...             |...             |...             
xGPIO_PORTH_BASE|xGPIO_PORTH_BASE|xGPIO_PORTE_BASE|xGPIO_PORTG_BASE|xGPIO_PORTF_BASE

xGPIO_PORTn_BASE| NUC1xx         | NUC122         | NUC123         | NUC2xx 
----------------|----------------|----------------|----------------|----------------
xGPIO_PORTA_BASE|xGPIO_PORTA_BASE|xGPIO_PORTA_BASE|xGPIO_PORTA_BASE|xGPIO_PORTA_BASE
...             |...             |...             |...             |...             
xGPIO_PORTH_BASE|xGPIO_PORTE_BASE|xGPIO_PORTD_BASE|xGPIO_PORTF_BASE|xGPIO_PORTF_BASE

xGPIO_PORTn_BASE| KLX            | HT32F125x      | HT32F175x      
----------------|----------------|----------------|----------------
xGPIO_PORTA_BASE|xGPIO_PORTA_BASE|xGPIO_PORTA_BASE|xGPIO_PORTA_BASE
...             |...             |...             |...             
xGPIO_PORTH_BASE|xGPIO_PORTE_BASE|xGPIO_PORTB_BASE|xGPIO_PORTE_BASE

# TIMER base Table               {#TIMERBaseTemplate}

以下几个表展示了TIMER外设存储接口范围的模板（n从0到14）, 同时也展示了已有的各个CoX系列的TIMER Base分布情况。
xTIMERn_BASE | LPC17xx     | STM32F1xx   |  Mini51     | M051           
-------------|-------------|-------------|-------------|-------------
xTIMER0_BASE |xTIMER0_BASE |xTIMER1_BASE |xTIMER0_BASE |xTIMER0_BASE
...          |...          |...          |xTIMER1_BASE |...             
xTIMER14_BASE|xTIMER3_BASE |xTIMER14_BASE|...          |xTIMER3_BASE

xTIMERn_BASE | NUC1xx      | NUC122      | NUC123      | NUC2xx 
-------------|-------------|-------------|-------------|-------------
xTIMER0_BASE |xTIMER0_BASE |xTIMER0_BASE |xTIMER0_BASE |xTIMER0_BASE
...          |...          |...          |...          |...             
xTIMER14_BASE|xTIMER3_BASE |xTIMER3_BASE |xTIMER3_BASE |xTIMER3_BASE

xTIMERn_BASE | KLX         | HT32F125x   | HT32F175x      
-------------|-------------|-------------|-------------
xTIMER0_BASE |xTIMER0_BASE |xTIMER0_BASE |xTIMER0_BASE 
...          |xTIMER1_BASE |xTIMER1_BASE |xTIMER1_BASE  
xTIMER14_BASE|xTIMER2_BASE |...          |...


# PWM base Table               {#PWMBaseTemplate}

以下几个表展示了PWM外设存储接口范围的模板（n从A到L）, 同时也展示了已有的各个CoX系列的PWM Base分布情况。
xPWMn_BASE| LPC17xx  | STM32F1xx|  Mini51  | M051     
----------|----------|----------|----------|----------
xPWMA_BASE|...       |xPWMA_BASE|xPWMA_BASE|xPWMA_BASE
...       |xPWMB_BASE|...       |...       |xPWMB_BASE
xPWML_BASE|...       |xPWML_BASE|...       |...

xPWMn_BASE| NUC1xx   | NUC122   | NUC123   | NUC2xx 
----------|----------|----------|----------|----------
xPWMA_BASE|xPWMA_BASE|xPWMA_BASE|xPWMA_BASE|xPWMA_BASE
...       |xPWMB_BASE|...       |xPWMB_BASE|...       
xPWML_BASE|...       |...       |...       |...       

xPWMn_BASE| KLX      | HT32F125x| HT32F175x
----------|----------|----------|----------
xPWMA_BASE|xPWMA_BASE|xPWMA_BASE|xPWMA_BASE
...       |xPWMB_BASE|xPWMB_BASE|xPWMB_BASE
xPWML_BASE|xPWMC_BASE|...       |...       

# DMA base Table               {#DMABaseTemplate}

以下几个表展示了DMA外设存储接口范围的模板（n从0到8）, 同时也展示了已有的各个CoX系列的DMA Base分布情况。
xDMAn_BASE| LPC17xx  | STM32F1xx|  Mini51  | M051     
----------|----------|----------|----------|----------
xDMA0_BASE|xDMA0_BASE|xDMA0_BASE|...       |...       
...       |...       |xDMA1_BASE|...       |...       
xDMA8_BASE|...       |...       |...       |...       

xDMAn_BASE| NUC1xx   | NUC122   | NUC123   | NUC2xx 
----------|----------|----------|----------|----------
xDMA0_BASE|...       |...       |xDMA0_BASE|xDMA0_BASE
...       |...       |...       |...       |...       
xDMA8_BASE|...       |...       |...       |...       

xDMAn_BASE| KLX      | HT32F125x| HT32F175x
----------|----------|----------|----------
xDMA0_BASE|xDMA0_BASE|...       |...       
...       |...       |...       |...       
xDMA8_BASE|...       |...       |...     

# RTC base Table               {#RTCBaseTemplate}

以下几个表展示了RTC外设存储接口范围的模板, 同时也展示了已有的各个CoX系列的RTC Base分布情况。
xRTC_BASE| LPC17xx | STM32F1xx|  Mini51 | M051 
---------|---------|----------|---------|------
xRTC_BASE|xRTC_BASE|xRTC_BASE |...      |...   
  

xRTC_BASE| NUC1xx  | NUC122   | NUC123  | NUC2xx 
---------|---------|----------|---------|----------
xRTC_BASE|xRTC_BASE|...       |xRTC_BASE|xRTC_BASE 

xRTC_BASE| KLX     | HT32F125x| HT32F175x
---------|---------|----------|----------
xRTC_BASE|xRTC_BASE|xRTC_BASE |xRTC_BASE 


# WDT base Table               {#WDTBaseTemplate}

以下几个表展示了WDT外设存储接口范围的模板, 同时也展示了已有的各个CoX系列的WDT Base分布情况。
xWDT_BASE| LPC17xx | STM32F1xx|  Mini51 | M051 
---------|---------|----------|---------|----------
xWDT_BASE|xWDT_BASE|xWDT_BASE |xWDT_BASE|xWDT_BASE
  

xWDT_BASE| NUC1xx  | NUC122   | NUC123  | NUC2xx 
---------|---------|----------|---------|----------
xWDT_BASE|xWDT_BASE|xWDT_BASE |xWDT_BASE|xWDT_BASE 

xWDT_BASE| KLX     | HT32F125x| HT32F175x
---------|---------|----------|----------
xWDT_BASE|xWDT_BASE|xWDT_BASE |xWDT_BASE  


# UART base Table               {#UARTBaseTemplate}

以下几个表展示了UART外设存储接口范围的模板（n从0到5）, 同时也展示了已有的各个CoX系列的UART Base分布情况。
xUARTn_BASE| LPC17xx   | STM32F1xx |  Mini51   | M051     
-----------|-----------|-----------|-----------|----------
xUART0_BASE|xUART0_BASE|xUART1_BASE|xUART0_BASE|xUART0_BASE
...        |xUART1_BASE|...        |...        |xUART1_BASE
xUART5_BASE|...        |xUART5_BASE|...        |...

xUARTn_BASE| NUC1xx    | NUC122    | NUC123    | NUC2xx 
-----------|-----------|-----------|-----------|----------
xUART0_BASE|xUART0_BASE|xUART0_BASE|xUART0_BASE|xUART0_BASE
...        |xUART1_BASE|xUART1_BASE|xUART1_BASE|xUART1_BASE
xUART5_BASE|xUART2_BASE|...        |...        |xUART2_BASE

xUARTn_BASE| KLX       | HT32F125x | HT32F175x
-----------|-----------|-----------|----------
xUART0_BASE|xUART0_BASE|xUART0_BASE|xUART0_BASE
...        |xUART1_BASE|...        |xUART1_BASE
xUART5_BASE|xUART2_BASE|...        |...        


# I2C base Table               {#I2CBaseTemplate}

以下几个表展示了I2C外设存储接口范围的模板（n从0到2）, 同时也展示了已有的各个CoX系列的I2C Base 分布情况。
xI2Cn_BASE| LPC17xx  |STM32F1xx |  Mini51  | M051     
----------|----------|----------|----------|----------
xI2C0_BASE|xI2C0_BASE|xI2C0_BASE|xI2C0_BASE|xI2C0_BASE
xI2C1_BASE|xI2C1_BASE|xI2C1_BASE|...       |...       
xI2C2_BASE|xI2C2_BASE|xI2C2_BASE|...       |...       

xI2Cn_BASE| NUC1xx   | NUC122   | NUC123   | NUC2xx 
----------|----------|----------|----------|----------
xI2C0_BASE|xI2C0_BASE|xI2C0_BASE|xI2C0_BASE|xI2C0_BASE
xI2C1_BASE|xI2C1_BASE|...       |xI2C1_BASE|xI2C1_BASE
xI2C2_BASE|...       |...       |...       |...

xI2Cn_BASE| KLX      | HT32F125x| HT32F175x
----------|----------|----------|----------
xI2C0_BASE|xI2C0_BASE|xI2C0_BASE|xI2C0_BASE
xI2C1_BASE|xI2C1_BASE|...       |xI2C1_BASE
xI2C2_BASE|...       |...       |...       


# SPI base Table               {#SPIBaseTemplate}

以下几个表展示了SPI外设存储接口范围的模板（n从0到3）, 同时也展示了已有的各个CoX系列的SPI Base 分布情况。
xSPIn_BASE| LPC17xx  |STM32F1xx |  Mini51  | M051     
----------|----------|----------|----------|----------
xSPI0_BASE|xSPI0_BASE|...       |xSPI0_BASE|xSPI0_BASE
xSPI1_BASE|...       |xSPI1_BASE|...       |xSPI1_BASE    
xSPI2_BASE|...       |xSPI2_BASE|...       |...       
xSPI3_BASE|...       |xSPI2_BASE|...       |...     

xSPIn_BASE| NUC1xx   | NUC122   | NUC123   | NUC2xx 
----------|----------|----------|----------|----------
xSPI0_BASE|xSPI0_BASE|xSPI0_BASE|xSPI0_BASE|xSPI0_BASE
xSPI1_BASE|xSPI1_BASE|xSPI1_BASE|xSPI1_BASE|xSPI1_BASE
xSPI2_BASE|xSPI2_BASE|...       |xSPI2_BASE|xSPI2_BASE
xSPI3_BASE|xSPI3_BASE|...       |...       |xSPI3_BASE

xSPIn_BASE| KLX      | HT32F125x| HT32F175x
----------|----------|----------|----------
xSPI0_BASE|xSPI0_BASE|xSPI0_BASE|xSPI0_BASE
xSPI1_BASE|xSPI1_BASE|...       |xSPI1_BASE
xSPI2_BASE|...       |...       |...       
xSPI3_BASE|...       |...       |...        

# I2S base Table               {#I2SBaseTemplate}

以下几个表展示了I2S外设存储接口范围的模板（n = 0）, 同时也展示了已有的各个CoX系列的I2S Base 分布情况。
xI2Sn_BASE| LPC17xx  |STM32F1xx |  Mini51  | M051     
----------|----------|----------|----------|----------
xI2S0_BASE|xI2S0_BASE|...       |...       |...             
   

xI2Sn_BASE| NUC1xx   | NUC122   | NUC123   | NUC2xx 
----------|----------|----------|----------|----------
xI2S0_BASE|xI2S0_BASE|...       |xI2S0_BASE|xI2S0_BASE    


xI2Sn_BASE| KLX      | HT32F125x| HT32F175x
----------|----------|----------|----------
xI2S0_BASE|...       |...       |xI2S0_BASE


# CAN base Table               {#CANBaseTemplate}

以下几个表展示了CAN外设存储接口范围的模板（n 为0~2）, 同时也展示了已有的各个CoX系列的CAN Base 分布情况。
xCANn_BASE| LPC17xx  |STM32F1xx |  Mini51  | M051     
----------|----------|----------|----------|----------
xCAN0_BASE|...       |...       |...       |...       
xCAN1_BASE|xCAN1_BASE|...       |...       |...       
xCAN2_BASE|xCAN2_BASE|...       |...       |...       
   

xCANn_BASE| NUC1xx   | NUC122   | NUC123   | NUC2xx 
----------|----------|----------|----------|----------
xCAN0_BASE|xCAN0_BASE|...       |...       |...       
xCAN1_BASE|xCAN0_BASE|...       |...       |...       
xCAN2_BASE|...       |...       |...       |...       


xCANn_BASE| KLX      | HT32F125x| HT32F175x
----------|----------|----------|----------
xCAN0_BASE|...       |...       |...       
xCAN1_BASE|...       |...       |...       
xCAN2_BASE|...       |...       |...       

# ETH base Table               {#ETHBaseTemplate}

以下几个表展示了ETH外设存储接口范围的模板（n 为0）, 同时也展示了已有的各个CoX系列的ETH Base分 布情况。
xETHn_BASE| LPC17xx  |STM32F1xx |  Mini51  | M051     
----------|----------|----------|----------|----------
xETH0_BASE|xETH0_BASE|xETH0_BASE|...       |...       

xETHn_BASE| NUC1xx   | NUC122   | NUC123   | NUC2xx 
----------|----------|----------|----------|----------
xETH0_BASE|...       |...       |...       |...       


xETHn_BASE| KLX      | HT32F125x| HT32F175x
----------|----------|----------|----------
xETH0_BASE|...       |...       |...       

# USB base Table               {#USBBaseTemplate}

以下几个表展示了USB外设存储接口范围的模板, 同时也展示了已有的各个CoX系列的USB Base 分布情况。
xUSB_BASE | LPC17xx  |STM32F1xx |  Mini51  | M051     
----------|----------|----------|----------|----------
xUSBD_BASE|xUSBD_BASE|xUSBD_BASE|...       |...       
xUSBH_BASE|xUSBH_BASE|xUSBH_BASE|...       |...       

xUSB_BASE | NUC1xx   | NUC122   | NUC123   | NUC2xx 
----------|----------|----------|----------|----------
xUSBD_BASE|...       |xUSBD_BASE|xUSBD_BASE|xUSBD_BASE
xUSBH_BASE|...       |...       |...       |...       

xUSB_BASE | KLX      | HT32F125x| HT32F175x
----------|----------|----------|----------
xUSBD_BASE|...       |...       |xUSBD_BASE
xUSBH_B1SE|...       |...       |xUSBH_BASE

# ADC base Table               {#ADCBaseTemplate}

以下几个表展示了ADC外设存储接口范围的模板（n 为0~1）, 同时也展示了已有的各个CoX系列的ADC Base  分布情况。
xADCn_BASE| LPC17xx  |STM32F1xx |  Mini51  | M051     
----------|----------|----------|----------|----------
xADC0_BASE|xADC0_BASE|...       |xADC0_BASE|xADC0_BASE
xADC1_BASE|...       |xADC1_BASE|...       |...        
xADC2_BASE|...       |xADC2_BASE|...       |...      
   

xADCn_BASE| NUC1xx   | NUC122   | NUC123   | NUC2xx 
----------|----------|----------|----------|----------
xADC0_BASE|xADC0_BASE|...       |xADC0_BASE|xADC0_BASE 
xADC1_BASE|...       |...       |...       |...       
xADC2_BASE|...       |xADC2_BASE|...       |...      

xADCn_BASE| KLX      | HT32F125x| HT32F175x
----------|----------|----------|----------
xADC0_BASE|xADC0_BASE|xADC0_BASE|xADC0_BASE
xADC1_BASE|...       |...       |...       
xADC2_BASE|...       |...       |...       

# DAC base Table               {#DACBaseTemplate}

以下几个表展示了DAC外设存储接口范围的模板（n 为0）, 同时也展示了已有的各个CoX系列的DAC Base 分 布情况。
xDACn_BASE| LPC17xx  |STM32F1xx |  Mini51  | M051     
----------|----------|----------|----------|----------
xDAC0_BASE|xDAC0_BASE|xDAC0_BASE|...       |...         

xDACn_BASE| NUC1xx   | NUC122   | NUC123   | NUC2xx 
----------|----------|----------|----------|----------
xDAC0_BASE|...       |...       |...       |...             

xDACn_BASE| KLX      | HT32F125x| HT32F175x
----------|----------|----------|----------
xDAC0_BASE|xDAC0_BASE|...       |...       

# ACMP base Table               {#ACMPBaseTemplate}

以下几个表展示了ACMP外设存储接口范围的模板（n 为0）, 同时也展示了已有的各个CoX系列的ACMP Base  分布情况。
xACMPn_BASE| LPC17xx  |STM32F1xx |  Mini51   | M051     
-----------|----------|----------|-----------|-----------
xACMP0_BASE|...       |...       |xACMP0_BASE|xACMP0_BASE    

xACMPn_BASE| NUC1xx    | NUC122   | NUC123   | NUC2xx 
-----------|-----------|----------|----------|----------
xACMP0_BASE|xACMP0_BASE|...       |...       |xACMP0_BASE       

xACMPn_BASE| KLX       | HT32F125x  | HT32F175x
-----------|-----------|------------|----------
xACMP0_BASE|xACMP0_BASE|xACMP0_BASE |xACMP0_BASE   


