#ifndef _NUC4XX_ADC_H_
#define _NUC4XX_ADC_H_


//*****************************************************************************
//
//! \addtogroup CoX_Peripheral_Lib
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup ADC
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_ADC
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_ADC_Channel_IDs NUC4xx ADC Channel ID
//! \brief ADC Channel ID/index
//! @{
//
//*****************************************************************************

//
//! Internal Temperature Sensor
//
#define ADC_CTL_TS              13

//
//!Analog Input Channel 0
//
#define ADC_CTL_CH0             0

//
//!Analog Input Channel 1
//
#define ADC_CTL_CH1             1

//
//!Analog Input Channel 2
//
#define ADC_CTL_CH2             2

//
//!Analog Input Channel 3
//
#define ADC_CTL_CH3             3

//
//!Analog Input Channel 4
//
#define ADC_CTL_CH4             4

//
//!Analog Input Channel 5
//
#define ADC_CTL_CH5             5

//
//!Analog Input Channel 6
//
#define ADC_CTL_CH6             6

//
//!Analog Input Channel 7
//
#define ADC_CTL_CH7             7

//
//!Analog Input Channel 8
//
#define ADC_CTL_CH8             8

//
//!Analog Input Channel 9
//
#define ADC_CTL_CH9            9

//
//!Analog Input Channel 10
//
#define ADC_CTL_CH10            10

//
//!Analog Input Channel 11
//
#define ADC_CTL_CH11            11

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_ADC_Comp_IDs NUC4xx ADC Comparator ID
//! \brief ADC digital comparator ID/index
//! @{
//
//*****************************************************************************

//
// Analog Comparator 0
//
#define ADC_COMP_0              0

//
// Analog Comparator 1
//
#define ADC_COMP_1              1

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_ADC_Input_Mode NUC4xx ADC Input Mode
//! \brief ADC analog input mode, single-end / difference.
//! @{
//
//*****************************************************************************

//
//! Single-end Input Mode
//
#define ADC_CTL_END             0x00000000

//
//! Differential Input Mode
//
#define ADC_CTL_D               0x00000400

//
//! A/D differential input Mode Output Format is unsigned format.
//
#define ADC_DIFF_UNSIGNED       0x00000000

//
//! A/D differential input Mode Output Format is 2'complement format
//
#define ADC_DIFF_2C             0x80000000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_ADC_Operation_Mode NUC4xx ADC Operation Mode
//! \brief ADC A/D Converter Operation Mode.
//! @{
//
//*****************************************************************************

//
//! A/D Converter Operation Mode is Single conversion
//
#define ADC_OP_SINGLE           0x00000000

//
//! A/D Converter Operation Mode is Single-cycle scan
//
#define ADC_OP_SINGLE_CYCLE     0x00000008

//
//! A/D Converter Operation Mode is Continuous scan
//
#define ADC_OP_CONTINUOUS       0x0000000C


//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_ADC_Tigger_Source NUC4xx ADC Tigger Source
//! \brief ADC trigger Source that can start the convertion.
//! @{
//
//*****************************************************************************
//
//! Processor event(Software)
//
#define ADC_TRIGGER_PROCESSOR   0x00000000

//
//! External Pin event(external STADC pin PB8)
//
#define ADC_TRIGGER_EXT_PB8     0x00000100

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_ADC_EXT_Trigger_Mode NUC4xx ADC External Tigger Mode
//! \brief ADC external trigger Mode when the trigger source is external
//! pin.
//! @{
//
//*****************************************************************************

//
//! EXT Tigger is low level.
//
#define ADC_TRIGGER_EXT_LOW_LEVEL                                             \
                                0x00000000

//
//! EXT Tigger is high level.
//
#define ADC_TRIGGER_EXT_HIGH_LEVEL                                            \
                                0x00000040

//
//! EXT Tigger is falling edge.
//
#define ADC_TRIGGER_EXT_FALLING_EDGE                                          \
                                0x00000080


//
//! EXT Tigger is rising edge.
//
#define ADC_TRIGGER_EXT_RISING_EDGE                                           \
                                0x000000C0

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_ADC_Inside_Channel_Source NUC4xx_ADC Inside Channel Source
//! \brief ADC Inside channel analog input source config.
//! @{
//
//*****************************************************************************

//
//! Analog Input Channel source is External analog input
//
#define ADC_IN_CH_EXT           0x00000000

//
//! Analog Input Channel 13 source is Internal bandgap voltage
//

#define ADC_IN_CH_INT_BV        0x00010000

//
//! Analog Input Channel 13 source is Internal temperature sensor
//

#define ADC_IN_CH_INT_TS        0x00020000

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_ADC_Ints NUC4xx ADC Interrupt
//! \brief Values that show the ADC Interrupt source.
//! @{
//
//*****************************************************************************

//
//! Interrupt after single cycle conversion
//
#define ADC_INT_END_CONVERSION  0x00000001

//
//!  Interrupt when the comparator 0 match
//
#define ADC_INT_COMP0           0x00000002

//
//! Interrupt when the comparator 1 match
//
#define ADC_INT_COMP1           0x00000004

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_ADC_Data_Status NUC4xx ADC Data Status
//! \brief Check the convertion data if valid or overrun.
//! @{
//
//*****************************************************************************

//
//! Channel n Data is valid
//
#define ADC_DATA_VALID          0x00000001

//
//! Channel n Data is overrun
//
#define ADC_DATA_OVERRUN        0x00000002

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_ADC_Data_Resolution NUC4xx ADC Data Resolution
//! \brief Values that show the ADC Data Resolution (Data Mask, Data Length).
//! @{
//
//*****************************************************************************

//
//! Channel n Data mask
//

#define ADC_DATA_MASK           0x00000FFF

//
//! Channel n Data bit length
//
#define ADC_DATA_BIT_SIZE       12

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_ADC_Comp_Conditions NUC4xx ADC Comparator Interrupt Condition
//! \brief Conditions when the digital comparator generate and interrupt.
//! @{
//
//*****************************************************************************

//
//! Compare condition is less than
//
#define ADC_COMP_LESS_THAN      0x00000000

//
//! Compare condition is greater or equal
//
#define ADC_COMP_GREATER_EQUAL  0x00000004

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC4xx_ADC_Exported_APIs NUC4xx ADC API
//! \brief NUC4xx ADC API Reference
//! @{
//
//*****************************************************************************
extern void ADCConfigure(unsigned long ulBase, unsigned long ulInputMode,
                         unsigned long ulOpMode, unsigned long ulTrigger);

extern void ADCChannelEnable(unsigned long ulBase, unsigned long ulChannel);
extern void ADCChannelDisable(unsigned long ulBase, unsigned long ulChannel);
extern void ADCInsideChannleConfigure(unsigned long ulBase,
                                 unsigned long ulInputSrc);

extern unsigned long ADCIntStatus(unsigned long ulBase);
extern void ADCIntClear(unsigned long ulBase, unsigned long ulIntFlags);


extern void ADCConvertStop(unsigned long ulBase);
extern xtBoolean ADCBusy(unsigned long ulBase);

extern unsigned long ADCDataStatus(unsigned long ulBase,
                                   unsigned long ulChannel);
extern unsigned long ADCDataGet(unsigned long ulBase, unsigned long ulChannel);

extern void ADCCompDataSet(unsigned long ulBase, unsigned long ulComp,
                           unsigned long ulCompData,
                           unsigned long ulMatchCnt);
extern void ADCCompConfigure(unsigned long ulBase, unsigned long ulComp,
                 unsigned long ulCompChannel, unsigned long ulCondition);
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
