#include "xhw_types.h"
#include "xsysctl.h"
#include "xdebug.h"
#include "xhw_memmap.h"
#include "xhw_ints.h"
#include "xcore.h"
#include "xgpio.h"
#include "xled_3.h"


void test(void)
{

	xled3_Init();

	while(1)
		xled3_Scan(123,-1);

}
