/*
    This code can be compiled and run ok.
	
	For the sake of understanding TPC server construction,
	I build a server, listening to localhost 127.0.0.1.
	Waiting for client's connnection, then chat according 
	to request and response.

	usage:
		./server.exe

	input file:
		resdic.txt

	output file:
		none

	compile:
		g++ -g server3.cpp -lwsock32 -lWs2_32 -o server
		(MinGW)

    pseudocode:
		Part1:
			declaration and readfile
			build response dictionary
		Part2:
			Setup TCP server
				* server default setting
				* create server object
				* bind address
				* listen server
		Part3:
			accept client's connection
			if received request, print out content
			send back response

    coded by 廖家緯, ID: H34061050, email: leewei48750@gmail.com
    date: 2018.5.29
*/

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

#pragma comment (lib, "Ws2_32.lib")

#define IP_ADDRESS "127.0.0.1"
#define DEFAULT_PORT "3504"
#define DEFAULT_BUFLEN 512

int main(int argc, char const *argv[])
{
	// PART1:DECLARATION
	WSADATA data;
	struct addrinfo hints;
	struct addrinfo *server = NULL;

	SOCKET server_socket = INVALID_SOCKET;
	SOCKET client_socket = INVALID_SOCKET;

	int result=0;
	char recvbuffer[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;

	srand(time(NULL));
	fstream file;
	char resdic[] = "resdic.txt";
	string line;
	file.open(resdic,ios::in);
	vector<string> ResDict;
	while( getline(file,line,'\n') ){
		ResDict.push_back(line);
	}
	// PART2:SERVER SETUP
		// Initial Winsock
	cout<<"Initial Winsock..."<<endl;
	WSAStartup(MAKEWORD(2,2), &data);

	ZeroMemory(&hints, sizeof (hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

		// Setup Server
	getaddrinfo(static_cast<LPCTSTR>(IP_ADDRESS), DEFAULT_PORT, &hints, &server);
		// Create Server
	server_socket = socket(server->ai_family, server->ai_socktype, server->ai_protocol);
		// Bind address
	bind(server_socket, server->ai_addr, (int)server->ai_addrlen);
		// Listening
	listen(server_socket, SOMAXCONN);
	cout<<"SERVER DONE!"<<endl;

	// PART3:Accept Client
		// Accept
	client_socket = accept(server_socket,NULL,NULL);
	cout<<"Connected"<<endl;
	cout<<"####################"<<endl;
	while(1){
		int id = rand() % ResDict.size(); 
		memset(recvbuffer,0,sizeof(recvbuffer));
		result = recv(client_socket, recvbuffer, recvbuflen, 0);
		if(result>0){
				// Print Result
			cout<<"Client: "<<recvbuffer<<endl;
				// Send back
			string sendbuffer = ResDict[id];//ResDict[id];//要做字典回復
			send(client_socket,sendbuffer.c_str(),recvbuflen,0);
			cout<<"Server "<<sendbuffer<<endl;
			cout<<"####################"<<endl;
		}
	}
	closesocket(server_socket);
	closesocket(client_socket);
	WSACleanup();
	return 0;
}