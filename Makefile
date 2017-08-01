all : main.o 
	sudo gcc -o all main.o -lpcap

main.o : src/main.c
	sudo gcc -c src/main.c

clean: 
	rm all main.o 
