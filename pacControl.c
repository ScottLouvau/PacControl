// Copyright Scott Louvau, 2018. All rights reserved.
// Licensed under the MIT License.

#include <stdio.h>
#include <wiringPi.h>

// Use GPIO24, pin 18 on pinout.
// GPIO24 is off by default when the Pi boots.
const int StartButtonPin = 24;

// Restart every 28 minutes (Before Climate off @29, Car off @30)
// Restart 25 times (26 x 28 = 728 min total (12:08))
const int RestartAfterMin = 28;
const int RestartTimes = 25;

const int MsPerMin = 60 * 1000;

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
	
	// Off -> Acc -> Run just before 30m timeout for ~12 hours
	for(int i = 1; i <= RestartTimes; ++i)
	{
		printf("%d: ", i);
		pressStart(3);
		printf("\n");
		delay(RestartAfterMin * MsPerMin);
	}

	printf("\nDone.\n");
	return 0;
}
