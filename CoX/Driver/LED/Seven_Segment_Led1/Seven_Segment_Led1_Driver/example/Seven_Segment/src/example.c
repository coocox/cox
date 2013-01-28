#include "xhw_types.h"
#include "xsysctl.h"
#include "xdebug.h"
#include "xhw_memmap.h"
#include "xhw_ints.h"
#include "xcore.h"
#include "xgpio.h"
#include "xled_1.h"


void test(void)
{

	xled1_Init();

	xled1_Show(8);

}
