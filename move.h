#ifndef MOVE_H
#define MOVE_H


class Move
{
private:
    int STBY;
    //Silnik A
    int PWMA;
    int AIN1;
    int AIN2;
    //Silnik B
    int PWMB;
    int BIN1;
    int BIN2;
    int speed;

public:
    Move();
	//Przypisanie pinów do parametrów obiektu
    void setup(int ST, int PWA, int AI1, int AI2,int PWB,int BI1,int BI2,int SP);
	//Właczenie i konfiguracja niezbędnych pinów
    void OnAll();
	//Wyłaczenie wszytkich pinów i ustawienie ich n "0"
    void OffAll();
	//Poruszanie się do przodu
    void forward();
	//Poruszanie się do tyłu
    void backwards();
	//Obrót w lewo
    void left();
	//Obrót w prawo
    void right();
	//Zatrzymanie wszytkich silników
    void stop();

};


#endif // MOVE_H
