
#include "WiFi.h"


//your network SSID (name)
uint8_t ssid[] = "yourNetwork";

//your network password (use for WPA, or use as key for WEP)
uint8_t pass[] = "secretPassword";

int32_t status = WL_IDLE_STATUS;

// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//uint8_t server[] = {173,194,73,105};  // numeric IP for Google (no DNS)
uint8_t server[] = "www.google.com";    // name address for Google (using DNS)

uint8_t LocalIP[20];


uint8_t SocketCmd[] =
{
        "GET /search?q=arduino HTTP/1.1\r\n"
        "Host:www.google.com\r\n"
        "Connection: close\r\n"
        "\r\n"
};

//macro for ITM printf method
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

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):

static void delay(volatile uint32_t tick)
{
    while(tick--);
}

void PrintWifiStatus(void)
{
    //printf("WiFi Status is below:\r\n");
    // print the SSID of the network you're attached to:
    //printf("SSID: %s\r\n", WiFiDrv_GetCurrentSSID());

    // print your WiFi shield's IP address:
    WiFi_LocalIPGet(LocalIP);
    //printf("IP Address: %s\r\n", LocalIP);

    // print the received signal strength:
    //printf("signal strength (RSSI):%d dBm\r\n", WiFiDrv_GetCurrentRSSI());
}

void main(void)
{

    // check for the presence of the shield:
    if (WiFi_StatusGet() == WL_NO_SHIELD)
    {
        //printf("WiFi shield not present\r\n");
        // don't continue:
        while(1);
    }

    // attempt to connect to Wifi network:
    while ( status != WL_CONNECTED)
    {
        //printf("Attempting to connect to SSID: %s\r\n", ssid);
        // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
        status = WiFi_Begin(WPA, ssid, pass);

        // wait 10 seconds for connection:
        delay(10000);
    }

    //printf("Connected to wifi\r\n");
    PrintWifiStatus();

    //printf("\nStarting connection to server...\r\n");
    // if you get a connection, report back via serial:
    if (WiFiClient_Connect(server, 80))
    {
        //printf("connected to server");
        // Make a HTTP request:
        WiFiClient_WriteBlock(SocketCmd, sizeof(SocketCmd));
    }

    // if there are incoming bytes available
    // from the server, read them and print them:
    while (WiFiClient_Available())
    {
        uint8_t Recv = WiFiClient_ReadByte();
        //printf("%c", Recv);
    }

    // if the server's disconnected, stop the client:
    if (!WiFiClient_Connected())
    {
        //printf("\r\ndisconnecting from server.\r\n");
        WiFiClient_Stop();

        // do nothing forevermore:
        while(1);
    }
}

