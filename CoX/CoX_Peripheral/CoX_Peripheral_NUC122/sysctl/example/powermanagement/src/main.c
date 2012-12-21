#include "sysctlpwr.h"

int main(void)
{
    PWRCtlStandby();
    WakeUpFromPowerDown();
    while(1)
    {
        
    }
}