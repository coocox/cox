
#include "WiFi.h"

//macro for ITM printf function.
#define ITM_Port8(n)    (*((volatile unsigned char *)(0xE0000000+4*n)))
#define ITM_Port32(n)   (*((volatile unsigned long *)(0xE0000000+4*n)))

#define DEMCR           (*((volatile unsigned long *)(0xE000EDFC)))

#define TRCENA          0x01000000

int fputc(int ch, FILE *f)
{

    if (DEMCR & TRCENA)
    {

        while (ITM_Port32(0) == 0);

        ITM_Port8(0) = ch;

    }

    return(ch);
}

static void delay(volatile uint32_t tick)
{
    while(tick--);
}

//your Network SSID
uint8_t ssid[] = "yourNetwork";
// your network password
uint8_t pass[] = "secretPassword";

int main(void)
{
    int status = WL_IDLE_STATUS;

    WiFi_Init();

    // attempt to connect to WPA Wifi network:
    while ( status != WL_CONNECTED)
    {
        status = WiFi_Begin(WPA, ssid, pass);
        //printf("Trying to connect WPA Network:%s\r\n", ssid);
        delay(10000);
    }

    //printf("OK, Connect to Network\r\n");
    while(1);

}

