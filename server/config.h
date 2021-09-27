#ifndef CONFIG_H
#define CONFIG_H

/*
Fencer Server
*/

#define SSID "Fencer"
#define PASSWORD "dArtagnan"

#define SERVER_HOST_NAME "fencer_server"

#define TCP_PORT 7050
#define DNS_PORT 53

// constants 
// Advised PINs (in brackets) are for Wemos D1 R2 board

// variables
char Score[10]  = "init 0";                // Score to display


/*
LED Display Config
* CS  - MISO/D6
* DIN - MOSI/D7
* CLK - SCL/D5
*/

// 8x8 LED display driver type hardware type
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
//#define HARDWARE_TYPE MD_MAX72XX::GENERIC_HW

#define MAX_DEVICES 3 // Number of 8x8 LED displays
#define CS_PIN D6     // Cable Select PIN (D6)

const String Fencer1HitSign = ">>>";      // Fencer 1 hit sign for display
const String Fencer2HitSign = "<<<";      // Fencer 2 hit sign for display

#endif // CONFIG_H
