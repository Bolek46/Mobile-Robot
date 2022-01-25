
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 


#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>

//Przesłanie danych do robotaw
void sendData( int sockfd, int x ) {
	int n;
	char buffer[32];
	sprintf( buffer, "%d\n", x );
	n = write( sockfd, buffer, strlen(buffer) );
	buffer[n] = '\0';
}
//Odbieranie Danych od robota
int getData( int sockfd ) {
	char buffer[32];
	int n;
	n = read(sockfd,buffer,31);
	buffer[n] = '\0';
	return atoi( buffer );
}
int main(int argc, char *argv[])
{
	//Deklaracja zmiennych odpowiedzialnaych za połaczenie bezzprzewodowe
	int sockfd, portno = 51719, n;
	char serverIp[] = "192.168.1.11";
	struct sockaddr_in serv_addr;
	struct hostent *server;
	char buffer[256];
	int data;
	
	char znak=0;
	
	//Konifguracja parametrów odpowiedzialnaych za połaczenie bezprzewodowe
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	server = gethostbyname( serverIp ) ;       
	bzero( (char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy( (char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(portno);
	connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
	//Główna pętla
	while (znak!=27)
	{ 	
		// initscr i getchar pozwalają na wczytywanie znaków bez potiwerdzania enterem
		initscr();
		znak=getchar();
		printf(" %i ",znak );
		
		//Przesyłanie danych odpwiedizlanych za sterowanie robotem
		if(znak=='w') sendData( sockfd, 'w');	//w
		if(znak=='s') sendData( sockfd, 's');	//s
		if(znak=='a') sendData( sockfd, 'a');	//a
		if(znak=='d') sendData( sockfd, 'd');	//d
		if(znak==' ') sendData( sockfd, ' ');	// 

		//Odbieranie danych o odległości od najbliższej przeszkody
		data=getData(sockfd);
		printf("Dystans: %i cm \n",data);
		//Zakończenie programu po wcisnieciu Esc
		if(znak==27) break;
	}
	//Przesłanie znaku do robota, który zadalnie wyłaczy program
    sendData( sockfd, -2 );
	//Zamknięcie Socketu
    close( sockfd );
    return 0;
}
