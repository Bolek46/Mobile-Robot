#include <wiringPi.h>
#include "sensor.h"


Sensor::Sensor(){};

void Sensor::OnAll()
{
	pinMode(TRIGGER, OUTPUT);
	pinMode(ECHO, INPUT);
	digitalWrite(TRIGGER, LOW);
}

void Sensor::OffAll()
{
	pinMode(TRIGGER, INPUT);
	pinMode(ECHO, INPUT);
	digitalWrite(TRIGGER, LOW);
	digitalWrite(ECHO, LOW);
}

void Sensor::setup(int TRI,int ECH)
{
	TRIGGER=TRI;
	ECHO=ECH;
}

//Funkcja mierząca czas trawania stanu wysokiego
void Sensor::timing()
{
	startTime = micros();
	while ( digitalRead(ECHO) == HIGH );
	stopTime = micros();
}
//Funkcja obliczajaca odległość od przeszkody
double Sensor::distance(int timeout)
{
	delay(10);
	//Wysłanie impulsu trwajacego 10  us
	digitalWrite(TRIGGER, HIGH);
	delayMicroseconds(10);
	digitalWrite(TRIGGER, LOW);
	int now=micros();
	while (digitalRead(ECHO) == LOW);
	//   while (digitalRead(ECHO) == LOW && micros()-now<timeout);
	
	timing();//Obliczanie czasu od wsyłania do odberania imulusu
	durationTime = stopTime - startTime;
	//Przeliczanie odległości na cm
	distanceCM = 100*((durationTime/1000000.0)*340.29)/2;
	//distanceCM=((durationTime*34)/1000)/2;

	return distanceCM;
}
