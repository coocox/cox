#ifndef _NUC1XX_ACMP_H_
#define _NUC1XX_ACMP_H_

//*****************************************************************************
//
//! \addtogroup NUC1xx_ACMP
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_ACMP_Comparator_IDs xACMP Analog Comparator ID
//! \brief Analog Comparator ID (index), The ID index is always like 0£¬ 1, and so on.
//! @{
//
//*****************************************************************************

//
//! Comparator 0
//
#define ACMP_0                  0x00000000

//
//! Comparator 1
//
#define ACMP_1                  0x00000001

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_ACMP_Analog_Src_negative NUC1xx negative(ACMP-) Input Source
//! \brief Analog comparator negative input select.
//! @{
//
//*****************************************************************************

//
//! Comp-(Analog source negative input) is CPN pin
//
#define ACMP_ASRCN_PIN          0x00000000

//
//! Comp-(Analog source negative input) is Internal voltage reference(1.2V)
//
#define ACMP_ASRCN_REF          0x00000010

//*****************************************************************************
//
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup NUC1xx_ACMP_Exported_APIs NUC1xx ACMP API
//! \brief NUC1xx ACMP API Reference.
//! @{
//
//*****************************************************************************

extern void ACMPHysEnable(unsigned long ulBase, unsigned long ulComp);
extern void ACMPHysDisable(unsigned long ulBase, unsigned long ulComp);

extern xtBoolean ACMPIntStatus(unsigned long ulBase, unsigned long ulComp);
extern void ACMPIntClear(unsigned long ulBase, unsigned long ulComp);

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
