/*
  Arduino based Fencing Scoring detection
  https://github.com/Vilda007/ArduinoWiFiFencingScoringDetection2
  CLIENT (PORT)

  This code has been heavily inspired by the examples you can find at
  https://www.arduino.cc/en/Tutorial/HomePage

  Board:
  ESP8266 Board --> LOLIN(WEMOS) D1 R2 & mini
  ESP8266 Board --> NodeMCU 1.0 (ESP-12E Module)
*/
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>

extern "C" {
#include <osapi.h>
#include <os_type.h>
}

#include "config.h"

static os_timer_t intervalTimer;

static void replyToServer(void* arg) {
	AsyncClient* client = reinterpret_cast<AsyncClient*>(arg);

	// send reply
	if (client->space() > 32 && client->canSend()) {
		char message[32];
		sprintf(message, "this is from %s", WiFi.localIP().toString().c_str());
		client->add(message, strlen(message));
		client->send();
	}
}

/* event callbacks */
static void handleData(void* arg, AsyncClient* client, void *data, size_t len) {
	Serial.printf("\n data received from %s \n", client->remoteIP().toString().c_str());
	Serial.write((uint8_t*)data, len);

	os_timer_arm(&intervalTimer, 20000, true); // schedule for reply to server at next 20s
}

void onConnect(void* arg, AsyncClient* client) {
	Serial.printf("\n client has been connected to %s on port %d \n", SERVER_HOST_NAME, TCP_PORT);
	replyToServer(client);
}


void setup() {
	Serial.begin(115200);
	delay(20);

  // initialize the LED pins as an output:
  pinMode(GreenLED, OUTPUT);
  digitalWrite(GreenLED, HIGH);
  pinMode(YellowLED, OUTPUT);
  digitalWrite(YellowLED, HIGH);
  pinMode(RedLED, OUTPUT);
  digitalWrite(RedLED, LOW);

  // initialize the pushbutton pin as an input:
  pinMode(Hit, INPUT);

	// connects to access point
	WiFi.mode(WIFI_STA);
	WiFi.begin(SSID, PASSWORD);
	while (WiFi.status() != WL_CONNECTED) {
		Serial.print('.');
		delay(500);
	}
  digitalWrite(GreenLED, LOW);
  digitalWrite(RedLED, HIGH);

	AsyncClient* client = new AsyncClient;
	client->onData(&handleData, client);
	client->onConnect(&onConnect, client);
	client->connect(SERVER_HOST_NAME, TCP_PORT);

	os_timer_disarm(&intervalTimer);
	os_timer_setfn(&intervalTimer, &replyToServer, client);
}

void loop() {
//LED Test START
/*
digitalWrite(GreenLED, HIGH);
delay(500);
digitalWrite(YellowLED, HIGH);
delay(500);
digitalWrite(RedLED, HIGH);
delay(500);
digitalWrite(GreenLED, LOW);
delay(500);
digitalWrite(YellowLED, LOW);
delay(500);
digitalWrite(RedLED, LOW);
delay(500);
//LED TEST END
*/

if (digitalRead(Hit) == HIGH) {; //Hit!
    digitalWrite(YellowLED, LOW);
    delay(500);
    digitalWrite(YellowLED, HIGH);
  }
  
}
