#include "xhw_types.h"
#include "xsysctl.h"
#include "xdebug.h"
#include "xhw_memmap.h"
#include "xhw_ints.h"
#include "xcore.h"
#include "xgpio.h"
#include "xled_2.h"


void test(void)
{

	xled2_Init();

	while(1)
		xled2_Scan(12,-1);

}
