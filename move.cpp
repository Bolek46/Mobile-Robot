#include <wiringPi.h>
#include "move.h"

Move::Move(){};

void Move::setup(int ST, int PWA, int AI1, int AI2,int PWB,int BI1,int BI2,int SP)
{
	STBY=ST;
	//Silnik A
	PWMA=PWA;
	AIN1=AI1;
	AIN2=AI2;
	//Silnik B
	PWMB=PWB;
	BIN1=BI1;
	BIN2=BI2;
	speed=SP;
}

void Move::OnAll()
{
	//Ustawienie wszytkich pinów jako wyjście
	pinMode(PWMA, PWM_OUTPUT);
	pinMode(PWMB, PWM_OUTPUT);
	pinMode(AIN1, OUTPUT);
	pinMode(AIN2, OUTPUT);
	pinMode(BIN1, OUTPUT);
	pinMode(BIN2, OUTPUT);
	//UStawienie Pinu STBY na wysoki (niezbędne do 'właczenia' modułu silników)
	pinMode(STBY, OUTPUT);
	digitalWrite(STBY, HIGH);
}

void Move::OffAll()
{
	pinMode(PWMA, INPUT);
	pinMode(PWMB, INPUT);
	pinMode(AIN1, INPUT);
	pinMode(AIN2, INPUT);
	pinMode(BIN1, INPUT);
	pinMode(BIN2,INPUT);
	digitalWrite(STBY, LOW);
	pinMode(STBY, INPUT);
}

void Move::forward()
{
	digitalWrite(AIN1,HIGH);
	digitalWrite(AIN2,LOW);
	digitalWrite(BIN1,LOW);
	digitalWrite(BIN2,HIGH);
	pwmWrite(PWMA, speed);
	pwmWrite(PWMB, speed);
}

void Move::backwards()
{
	digitalWrite(AIN1,LOW);
	digitalWrite(AIN2,HIGH);
	digitalWrite(BIN1,HIGH);
	digitalWrite(BIN2,LOW);
	pwmWrite(PWMA, speed);
	pwmWrite(PWMB, speed);
}

void Move::left()
{
	digitalWrite(AIN1,HIGH);
	digitalWrite(AIN2,LOW);
	pwmWrite(PWMA, speed);
}


void Move::right()
{
	digitalWrite(BIN1,LOW);
	digitalWrite(BIN2,HIGH);
	pwmWrite(PWMB, speed);
}


void Move::stop()
{
	digitalWrite(AIN1,LOW);
	digitalWrite(AIN2,LOW);
	digitalWrite(BIN1,LOW);
	digitalWrite(BIN2,LOW);
}










