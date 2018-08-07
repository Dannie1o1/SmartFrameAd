#include "Arduino.h"
#include <LiquidCrystal.h>
#include "ProximitySensor.h"



ProximitySensor::ProximitySensor(byte PIR_PIN, byte RED_LED, byte GREEN_LED, LiquidCrystal &lcdScr) 
	: PIR_PIN(PIR_PIN), RED_LED(RED_LED), GREEN_LED(GREEN_LED), lcdScr(&lcdScr)
{
}

void ProximitySensor::setup()
{
	Serial.println("Initializing PIR sensor");
	lcdScr->println("Hello World!");
	lcdScr->setCursor(0, 1);
	lcdScr->println("Your boy did it!");
	pinMode(PIR_PIN, INPUT);
	pinMode(GREEN_LED, OUTPUT);
	pinMode(RED_LED, OUTPUT);
	isMovement = false;
	wasMovement = false;
	timer = 0;
	digitalWrite(GREEN_LED, 0);
	digitalWrite(RED_LED, 1);

	Serial.print("PIR sensor on pin: ");
	Serial.print(PIR_PIN);
	Serial.println(" initialized");
}

void ProximitySensor::detect()
{
	//Detect movement of a nearby person
	isMovement = digitalRead(PIR_PIN);
	//Serial.println(isMovement);

	if (isMovement && !wasMovement) //If there is movement now and there wasn't before
	{
		//Turn on green led and turn off red led (with a colddown of 5secs)
		if (millis() - timer >= 5000)
		{
			tellTime(timer, "Time since last active is now...");
			toggleLED(1, 0);// Turn green LED on and red LED off
			timer = millis();

			Serial.println("Welcome CUSTOMER!");
			Serial.println("*Ad-mode OFF*");
			printMsg("Welcome CUSTOMER!", "*Ad-mode OFF*");

		}

	}
	else if (digitalRead(GREEN_LED) && isMovement == wasMovement) //If there currently no movement and there was movement
	{
		//Turn on green LED and turn off red LED (with a colddown of 10secs)
		if (millis() - timer >= 10000)
		{
			tellTime(timer, "The time(s) is now...");
			toggleLED(0, 1);
			timer = millis(); //Tracks the time on for the timerON
			Serial.println("Ad-mode ON");
			displayAd("Ad-mode ON");
		}

	}
}

void ProximitySensor::loop()
{
	detect();
}

void ProximitySensor::tellTime(unsigned long currTime, String msg)
{
	Serial.print(msg);
	Serial.println((millis() - currTime) / 1000.00);
}

void ProximitySensor::toggleLED(bool glState, bool rlState)
{
	//Toggle the the red and green leds based on the input parameters
	digitalWrite(GREEN_LED, glState);
	digitalWrite(RED_LED, rlState);
}

void ProximitySensor::displayAd(String msg = "*AD Placeholder*")
{
	lcdScr->clear();
	for (int i = 0; i < 2; i++)
	{
		lcdScr->setCursor(0, i);
		lcdScr->print(msg);
	}
}

void ProximitySensor::printMsg(String line1, String line2)
{
	lcdScr->clear();
	lcdScr->setCursor(0, 0);
	lcdScr->print(line1);
	lcdScr->setCursor(0, 1);
	lcdScr->print(line2);
}



ProximitySensor::~ProximitySensor()
{
	
}
