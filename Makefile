all : main.o defines.o 
	gcc -o all main.o defines.o -lpcap

main.o : src/main.c src/defines.c 
	sudo gcc -c -Iinclude src/main.c src/defines.c -Wall

defines.o: src/defines.c include/defines.h include/queue.h include/list.h
	sudo gcc -c -Iinclude src/defines.c include/defines.h include/queue.h include/list.h -Wall

clean: 
	rm -rf all main.o defines.o
