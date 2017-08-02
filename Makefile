all : main.o defines.o
	gcc -o all main.o defines.o -lpcap 

main.o : src/main.c include/defines.c 
	sudo gcc -c -Iinclude src/main.c include/defines.c -Wall

defines.o: include/defines.c 
	sudo gcc -c include/defines.c -Wall

clean: 
	rm -rf all main.o defines.o
