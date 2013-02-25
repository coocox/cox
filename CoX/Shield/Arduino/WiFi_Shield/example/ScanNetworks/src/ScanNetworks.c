
#include "WiFi.h"

//macro for ITM printf method
#define ITM_Port8(n)    (*((volatile unsigned char *)(0xE0000000+4*n)))
#define ITM_Port32(n)   (*((volatile unsigned long *)(0xE0000000+4*n)))

#define DEMCR           (*((volatile unsigned long *)(0xE000EDFC)))

#define TRCENA          0x01000000

int fputc(int ch, FILE *f) {

  if (DEMCR & TRCENA) {

    while (ITM_Port32(0) == 0);

    ITM_Port8(0) = ch;

  }

  return(ch);
}  

static void delay(volatile uint32_t tick)
{
    while(tick--);
}

void PrintMacAddress(void)
{
    // the MAC address of your Wifi shield
    uint8_t mac[6] = {0, 0, 0, 0, 0, 0};

    // print your MAC address:
    WiFi_MacAddrGet(mac);

    //Print the wifi mac
    //printf("MAC:%X:%X:%X:%X:%X:%X\r\n",
    //        mac[5], mac[4], mac[3], mac[2], mac[1], mac[0]);
}

void WiFi_Cfg(void) 
{
    //Configure the WiFi Module.
    WiFi_Init();

    // check for the presence of the shield:
    if (WiFi_StatusGet() == WL_NO_SHIELD) 
    {
        //printf("WiFi shield not present\r\n");

        //Stop
        while(1);
    } 

    // Print WiFi MAC address:
    PrintMacAddress();

}

void PrintEncryptionType(uint8_t Type)
{
    // read the encryption type and print out the name:
    switch (Type)
    {
        case ENC_TYPE_WEP:
            //printf("WEP\r\n");
            break;
        case ENC_TYPE_TKIP:
            //printf("WPA\r\n");
            break;
        case ENC_TYPE_CCMP:
            //printf("WPA2\r\n");
            break;
        case ENC_TYPE_NONE:
            //printf("None\r\n");
            break;
        case ENC_TYPE_AUTO:
            //printf("Auto\r\n");
            break;
    }
}

void ListNetworks(void)
{
    int num = 0;
    int i   = 0;

    // scan for nearby networks:
    
    num = WiFi_ScanNetworks();
    if (num == -1)
    { 
        //printf("Couldn't get a wifi connection\r\n");
        while(1);
    }

    if(num != 0)
    {
        // print the list of networks seen:
        //printf("number of available networks:%d\r\n", num);
        
        // print the network number and name for each network found:
        for (i = 0; i < num; i++)
        {
            //printf("(%d) %s\t\tSignal: %d dBm\tEncryption:",
            //       i, WiFi_SSIDGet(i), WiFi_RSSIGet(i));
            PrintEncryptionType(WiFi_EncryptionTypeGet(i));
        }
        //printf("\r\n");
    }
}

void main(void)
{

    WiFi_Cfg();
    //printf("Scanning available networks...\r\n");
    while(1)
    {
        delay(0xFFF);
        // scan for existing networks:        
        ListNetworks();
    }
}

