#ifndef SENSOR_H
#define SENSOR_H


class Sensor
{
private:

	int TRIGGER;
	int ECHO;
	volatile int startTime;
	volatile int stopTime;
	volatile int durationTime;
	int distanceCM;

public:
	Sensor();
	//Przypisanie pinów do parametrów obiektu
	void setup(int TRI,int ECH);
	//Przypisanie pinów do parametrów obiektu
	void OnAll();
	//Wyłaczenie wszytkich pinów i ustawienie ich n "0"
	void OffAll();
	//Obliczanie dystansu do obiektu
	double distance(int timeout);
	//Mierzenie czasu od wsyłania do odebrania impuslu
	void timing();
};



#endif // SENSOR_H
