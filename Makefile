all : main.o defines.o
	gcc -o all main.o defines.o -lpcap

main.o : src/main.c include/defines.c 
	sudo gcc -c -Iinclude src/main.c include/defines.c

defines.o: include/defines.c 
	sudo gcc -c include/defines.c

clean: 
	rm -rf all main.o defines.o
