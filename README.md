# TCP server using C++ on Windows

# usage
> // Compile<br>
> g++ -g server.cpp -lwsock32 -lWs2_32 -o server<br>
> g++ -g client.cpp -lwsock32 -lWs2_32 -o client<br>
> 
> // Run<br>
> ./server.exe<br>
> ./client.exe<br>
> then type something in client and server will answer it<br>