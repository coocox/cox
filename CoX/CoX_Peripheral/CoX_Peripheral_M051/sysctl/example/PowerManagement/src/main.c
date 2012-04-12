extern void PWRCtlStandby(void);
extern void WakeUpFromPowerDown(void);

int main(void)
{
    PWRCtlStandby();
    WakeUpFromPowerDown();
    while(1)
    {
        
    }
}