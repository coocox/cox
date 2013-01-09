#include "xhw_types.h"
#include "xsysctl.h"
#include "xdebug.h"
#include "xhw_memmap.h"
#include "xhw_ints.h"
#include "xcore.h"
#include "xgpio.h"
#include "xled_4.h"


void test(void)
{

	xled4_Init();

	while(1)
	    xled4_Scan(1234,-1);

}
