// Copyright Scott Louvau, 2018. All rights reserved.
// Licensed under the MIT License.

#include <stdio.h>
#include <wiringPi.h>

// Use GPIO24, pin 18 on pinout.
// GPIO24 is off by default when the Pi boots.
const int StartButtonPin = 24;

void pressStart(int presses)
{
	// Press button for 1/4 sec and wait one sec between presses
	for(int i = 0; i < presses; ++i)
	{
		printf("+");
		digitalWrite(StartButtonPin, HIGH);
		delay(250);
		printf("-");
		digitalWrite(StartButtonPin, LOW);
		delay(1000);
	}
}

int main(void)
{
	// Set Raspberry Pi StartButtonPin identification to 'GPIO' numbering
	wiringPiSetupGpio();
	
	// Set the Start Button pin to be an output pin
	digitalWrite(StartButtonPin, LOW);
	pinMode(StartButtonPin, OUTPUT);
	
	// Write stdout output immediately (not only after newlines)
	setbuf(stdout, NULL);
	
	// Off -> Acc -> Run ten times
	for(int i = 1; i <= 10; ++i)
	{
		printf("%d: ", i);
		pressStart(3);
		printf("\n");
		delay(5000);
	}

	printf("\nDone.\n");
	return 0;
}
