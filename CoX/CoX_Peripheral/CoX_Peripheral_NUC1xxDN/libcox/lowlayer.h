#ifndef _NUC1XX_LOWLAYER_H_
#define _NUC1XX_LOWLAYER_H_

//*****************************************************************************
//
//! \addtogroup NUC1xx_LowLayer
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_LowLayer_Peripheral_Memmap NUC1xx LowLayer Peripheral Memmap
//! The following are defines for the base address of the memories and
//! peripherals.
//!
//! This is always used as ulBase parameter in the peripheral library.
//! @{
//
//*****************************************************************************

#define FLASH_BASE              0x00000000  // FLASH memory
#define SRAM_BASE               0x20000000  // SRAM memory
#define WDT_BASE                0x40004000  // Watchdog0
#define GPIOA_BASE              0x50004000  // GPIO Port A
#define GPIOB_BASE              0x50004040  // GPIO Port B
#define GPIOC_BASE              0x50004080  // GPIO Port C
#define GPIOD_BASE              0x500040C0  // GPIO Port D
#define GPIOE_BASE              0x50004100  // GPIO Port E
#define GPIOF_BASE              0x50004140  // GPIO Port F
#define GPIO_DBNCECON_BASE      0x50004180  // GPIO Port DBNCECON
#define UART0_BASE              0x40050000  // UART0
#define UART1_BASE              0x40150000  // UART1
#define UART2_BASE              0x40154000  // UART2
#define TIMER0_BASE             0x40010000  // Timer0
#define TIMER1_BASE             0x40010020  // Timer1
#define TIMER2_BASE             0x40110000  // Timer2
#define TIMER3_BASE             0x40110020  // Timer3
#define SPI0_BASE               0x40030000  // SPI0
#define SPI1_BASE               0x40034000  // SPI1
#define SPI2_BASE               0x40130000  // SPI2
#define SPI3_BASE               0x40134000  // SPI3
#define I2C0_BASE               0x40020000  // I2C0
#define I2C1_BASE               0x40120000  // I2C1
#define RTC_BASE                0x40008000  // RTC
#define ADC0_BASE               0x400E0000  // ADC0
#define ACMP_BASE               0x400D0000  // ACMP
#define SYSCLK_BASE             0x50000200  // SYSTEM CLOCK
#define GCR_BASE                0x50000000  // GCR
#define INT_BASE                0x50000300  // INT
#define FMC_BASE                0x5000C000  // FMC
#define PS2_BASE                0x40100000  // PS2
#define CAN0_BASE               0x40180000  // CAN0
#define CAN1_BASE               0x40184000  // CAN1
#define USBD_BASE               0x40060000  // USBD
#define PDMA0_BASE              0x50008000  // PDMA0
#define PDMA1_BASE              0x50008100  // PDMA1
#define PDMA2_BASE              0x50008200  // PDMA2
#define PDMA3_BASE              0x50008300  // PDMA3
#define PDMA4_BASE              0x50008400  // PDMA4
#define PDMA5_BASE              0x50008500  // PDMA5
#define PDMA6_BASE              0x50008600  // PDMA6
#define PDMA7_BASE              0x50008700  // PDMA7
#define PDMA8_BASE              0x50008800  // PDMA8
#define PDMA9_BASE              0x50008900  // PDMA9
#define PDMA10_BASE             0x50008A00  // PDMA10
#define PDMA11_BASE             0x50008B00  // PDMA11
#define CRC_BASE                0x50008E00  // CRC
#define PDMA_GCR_BASE           0x50008F00  // PDMA GCR
#define PWMA_BASE               0x40040000  // PWMA
#define PWMB_BASE               0x40140000  // PWMB
#define SC0_BASE                0x40190000  // Smart Card 0
#define SC1_BASE                0x40194000  // Smart Card 0
#define SC2_BASE                0x40198000  // Smart Card 0
#define I2S_BASE                0x401A0000  // I2S
#define DWT_BASE                0xE0001000  // Data Watchpoint and Trace
#define NVIC_BASE               0xE000E000  // Nested Vectored Interrupt Ctrl

#define DMA0_BASE               PDMA0_BASE

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup  NUC1xx_LowLayer_Interrupt_Assignments NUC1xx Interrupt Assignments
//! \brief Macros defines for the fault/interrupt assignments.
//!
//! They can be used as ulInterrupt parameter with xIntEnable(), xIntDisable()
//! to enable/disable the interrupt at the core/NVIC level.
//!
//! @{
//
//*****************************************************************************

#define FAULT_NMI               2           // NMI fault
#define FAULT_HARD              3           // Hard fault
#define FAULT_MPU               4           // MPU fault
#define FAULT_BUS               5           // Bus fault
#define FAULT_USAGE             6           // Usage fault
#define FAULT_SVCALL            11          // SVCall
#define FAULT_DEBUG             12          // Debug monitor
#define FAULT_PENDSV            14          // PendSV
#define FAULT_SYSTICK           15          // System Tick

#define INT_BOD                 16          // BOD interrupt event
#define INT_WWDT                17          // WDT
#define INT_EINT0               18          // EINT0
#define INT_EINT1               19          // EINT1
#define INT_GPAB                20          // GPIO Port A B
#define INT_GPCDEF              21          // GPIO Port C D E F
#define INT_PWMA                22          // PWM Generator A
#define INT_PWMB                23          // PWM Generator B
#define INT_TIMER0              24          // Timer 0
#define INT_TIMER1              25          // Timer 1
#define INT_TIMER2              26          // Timer 2
#define INT_TIMER3              27          // Timer 3
#define INT_UART02              28          // UART0 and UART2 Rx and Tx
#define INT_UART1               29          // UART1 Rx and Tx
#define INT_SPI0                30          // SPI0 Rx and Tx
#define INT_SPI1                31          // SPI1 Rx and Tx
#define INT_SPI2                32          // SPI2 Rx and Tx
#define INT_SPI3                33          // SPI3 Rx and Tx
#define INT_I2C0                34          // I2C0 Master and Slave
#define INT_I2C1                35          // I2C1 Master and Slave
#define INT_CAN0                36          // CAN0
#define INT_SC                  38          // SmartCard 0&1&2
#define INT_USBD                39          // USBD
#define INT_PS2                 40          // PS2
#define INT_ACMP                41          // ACMP
#define INT_DMA0                42          // PDMA
#define INT_I2S0                43          // I2S
#define INT_PWRWU               44          // PWRWU
#define INT_ADC0                45          // ADC
#define INT_IRC                 46          // IRC TRIM
#define INT_RTC                 47          // RTC

#define INT_GPIOA               INT_GPAB
#define INT_GPIOB               INT_GPAB
#define INT_GPIOC               INT_GPCDEF
#define INT_GPIOD               INT_GPCDEF
#define INT_GPIOE               INT_GPCDEF
#define INT_GPIOF               INT_GPCDEF
#define INT_UART0               INT_UART02
#define INT_UART2               INT_UART02
//
//! The total number of interrupts.
//

#define NUM_INTERRUPTS          47

//
//! The total number of priority levels.
//
#define NUM_PRIORITY            4

//
//! The total number of priority levels (bits).
//
#define NUM_PRIORITY_BITS       2

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

#endif
