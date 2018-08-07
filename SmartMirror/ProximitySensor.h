#pragma once

/*Write a description of the class here*/

class ProximitySensor
{
	const byte PIR_PIN;
	const byte RED_LED, GREEN_LED;//The red LED represents AD-mode and the green LED represents customer mode
	LiquidCrystal *lcdScr;//Pointer for lcd screen's address
	bool isMovement; //Stores if movement was detected
	bool wasMovement; //Stores previous value of "isMovement" var
	unsigned long timer; //Used for timing within the class

public:
	ProximitySensor(byte PIR_PIN, byte RED_LED, byte GREEN_LED, LiquidCrystal &lcdScr);
	void setup();
	void loop();
	~ProximitySensor();

private:
	void detect();
	void tellTime(unsigned long currTime, String msg);
	void toggleLED(bool glState, bool rlState);
	void displayAd(String msg);
	void printMsg(String line1, String line2);

};

