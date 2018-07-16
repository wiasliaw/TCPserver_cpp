/*
    This code can be compiled and run ok.
	
	For the sake of understanding TPC server construction,
	I build a server, listening to localhost 127.0.0.1.
	Waiting for client's connnection, then chat according 
	to request and response.

	usage:
		./client.exe
		> (then message to chat)

	input file:
		none

	output file:
		none

	compile:
		g++ -g client3.cpp -lwsock32 -lWs2_32 -o client
		(MinGW)

    pseudocode:
		Part1:
			declaration
		Part2:
			Setup TCP server
				* server default setting
				* create server object
		Part3:
			connect to server
			cin message and send to server
			print out chatting message

    coded by 廖家緯, ID: H34061050, email: leewei48750@gmail.com
    date: 2018.5.29
*/

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>

using namespace std;

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define DEFAULT_BUFLEN 512
#define IP_ADDRESS "127.0.0.1"
#define DEFAULT_PORT "3504"

int main(int argc, char const *argv[])
{
	// PART1:DECLARATION
	WSADATA data;
	struct addrinfo hints;
	struct addrinfo *server = NULL;
	struct addrinfo *ptr = NULL;

	SOCKET ConnectSocket = INVALID_SOCKET;

	int result = 0;
	char sendbuf[DEFAULT_BUFLEN];
	char recvbuffer[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;

	// PART2:SERVER SETUP
		// Initial Winsock
	cout<<"Initial Winsock..."<<endl;
	WSAStartup(MAKEWORD(2,2), &data);

	ZeroMemory(&hints, sizeof (hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
		// Setup Server
	getaddrinfo(static_cast<LPCTSTR>(IP_ADDRESS), DEFAULT_PORT, &hints, &server);
	
	// Part3: Connect
		//Attempt to connect
	for(ptr=server;ptr!=NULL;ptr=ptr->ai_next){
			//Create Socket and connect
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		if( (connect(ConnectSocket,ptr->ai_addr,(int)ptr->ai_addrlen)) == SOCKET_ERROR ){
			closesocket(ConnectSocket);
			ConnectSocket = INVALID_SOCKET;
			continue;
		}
		cout<<"Connected"<<endl;
		cout<<"Ready to Chat"<<endl;
		break;
	}
	while(1){
		memset(sendbuf,0,sizeof(sendbuf));
		cout<<"####################"<<endl;
		cout<<"Enter Message:";
		cin.getline(sendbuf,sizeof(sendbuf));
			// Send Buffer
		send( ConnectSocket, sendbuf, (int)strlen(sendbuf), 0 );
			// Receive
		result = recv(ConnectSocket,recvbuffer,recvbuflen,0);
		if(result>0){
			cout<<"Client: "<<sendbuf<<endl;
			cout<<"Server: "<<recvbuffer<<endl;
		}

	}
	closesocket(ConnectSocket);
	WSACleanup();
	return 0;
}