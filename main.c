
#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include <wiringPi.h> 
#include <wiringSerial.h> 
#include "move.h"
#include "sensor.h"

//Przypisanie Pinów z malinki (WiringPi)
int const STBY=11;
//Silnik A
int const PWMA=26;
int const AIN1=27;
int const AIN2=28;
//Silnik B
int const PWMB=26;
int const BIN1=6;
int const BIN2=10;
int const SPEED=800;
//Czujnik odległości
int TRIGGER=1;
int ECHO=16;
float dystans;

//Wysłanie danych na numer gniazda, z którym się łaczymy
void sendData( int sockfd, int x ) {
	int n;
	char buffer[32];
	sprintf( buffer, "%d\n", x );
	n = write( sockfd, buffer, strlen(buffer) );
	buffer[n] = '\0';
}
//Odbieranie danych z numeru gniazda, z którym się łaczymy
int getData( int sockfd ) {
	char buffer[32];
	int n;
	n = read(sockfd,buffer,31) ;
	buffer[n] = '\0';
	return atoi( buffer );
}

int main(int argc, char *argv[]) {

	//Sprawdzenie czy biloteka WiringPi poprawnie się załadowała
    if (wiringPiSetup() == -1) 
    { 
        printf("Nie mozna wystartowac wiringPi!\n"); 
        return 1; 
    } 
	
	//Deklaracja zmiennych odpowiedzialnaych za połaczenie bezzprzewodowe
	int sockfd, newsockfd, portno = 51719, clilen;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	int n;
	int data;
	
	//Deklaracja obiektu i konkfiguracja elementów odpowedizalncyh za poruszanie się 
	Move move;
	move.setup(STBY,PWMA,AIN1,AIN2,PWMB,BIN1,BIN2,SPEED);
	move.OnAll();
	
	//Deklaracja obiektu i konkfiguracja elementów odpowiedzialnych za obsługę czujnika odległości
	Sensor sensor;
	sensor.setup(TRIGGER,ECHO);
	sensor.OnAll();

	//Konifguracja parametrów odpowiedzialnaych za połaczenie bezprzewodowe
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons( portno );
	bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr));
	listen(sockfd,5);
	clilen = sizeof(cli_addr);

	//Petla odpowiedzialan za połączenie z urządzeniem sterujacym
	while ( 1 ) {
		newsockfd = accept( sockfd, (struct sockaddr *) &cli_addr, (socklen_t*) &clilen);

		//Petla odpowiedzialan za sterowanie robotem i przesyłanie danych pomiedzy nim a urządzeniem sterujacym
		while ( data!=27 ) 
		{

			data = getData( newsockfd );
			printf( "", data );
			if ( data < 0 ) 
				break;


			switch(data)
			{
				case 'w':
				move.forward();
				break;
				case 's':
				move.backwards();
				break;
				case 'a':
				move.left();
				break;
				case 'd':
				move.right();
				break;
				default:
				move.stop();
			}

			dystans=sensor.distance(3000000);
			printf( "dystans: %.2f \n", dystans );
			sendData( newsockfd, dystans );

		}

	
        
	
	sendData( newsockfd, data );
	close( newsockfd );
	
	//Zakończenie połączenia
	if ( data == -2 ){ return 0; }


    }
     return 0; 
}
