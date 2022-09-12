dir_client=Client/
dir_server=Server/

all: server client 

server: main_s server_s
	g++ $(dir_server)main.o $(dir_server)server.o -o $(dir_server)server.out
	
main_s: $(dir_server)main.cpp
	g++ -c $(dir_server)main.cpp -o $(dir_server)main.o

server_s:  $(dir_server)/server.cpp
	g++ -c $(dir_server)/server.cpp -o $(dir_server)server.o
	

client: main_c client_c manager_thread_c semafore_c
	g++ $(dir_client)main.o $(dir_client)client.o $(dir_client)manager_thread.o $(dir_client)semafore.o -o $(dir_client)client.out
	
main_c: $(dir_client)main.cpp
	g++ -c $(dir_client)main.cpp -o $(dir_client)main.o
	
client_c: $(dir_client)client.cpp
	g++ -c $(dir_client)client.cpp -o $(dir_client)client.o

manager_thread_c: $(dir_client)manager_thread.cpp
	g++ -c $(dir_client)manager_thread.cpp -o $(dir_client)manager_thread.o

semafore_c: $(dir_client)semafore.cpp
	g++ -c $(dir_client)semafore.cpp -o $(dir_client)semafore.o
	

clean:
	rm -rf $(dir_server)*.o $(dir_server)server.out
	rm -rf $(dir_client)*.o $(dir_client)client.out

	
