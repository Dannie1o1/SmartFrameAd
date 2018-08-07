/*
 Name:		SmartMirror.ino
 Created:	8/3/2018 1:13:11 PM
 Author:	Danny G
*/

#include <LiquidCrystal.h>
#include "ProximitySensor.h"

LiquidCrystal lcdScr1(2, 3, 10, 11, 12, 13);
ProximitySensor ps1(4, 8, 9, lcdScr1);//Proximity Sensor 1

// the setup function runs once when you press reset or power the board
void setup() 
{
	lcdScr1.begin(16,2);
	lcdScr1.clear();
	Serial.begin(115200);
	ps1.setup();
}

// the loop function runs over and over again until power down or reset
void loop() 
{
	ps1.loop();
}
