# TCP server using C++ on Windows

# usage
> // Compile
> g++ -g server.cpp -lwsock32 -lWs2_32 -o server
> g++ -g client.cpp -lwsock32 -lWs2_32 -o client
> 
> // Run
> ./server.exe
> ./client.exe
> then type something in client and server will answer it