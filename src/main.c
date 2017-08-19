/*
 * Author : Satyajit Simhadri
 * purpose : capture and store network packets
 * copyright notice :
 *
 *
*/

#include <pcap.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/if_ether.h>
#include <netinet/ether.h>
#include <netinet/ether.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <defines.h>

#define NUM_CHARS 256
#define PCAP_SAVEFILE "./pcap_savefile"

int help(char* arg)
{
	char *h = "-h";
	char *h1 = "--help";
	if( (strcmp(arg,h) == 0) || (strcmp(arg,h1) == 0) ) {
		return 1;
	}
	else {
		return 0;
	}
}

void displayHelp() 
{
	printf("specify filter program for wlan0\n");
	printf("ex. src 127.0.0.1\n");
}

int main(int argc, char **argv)
{
	char *dev;
	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_t* des;
	struct bpf_program fp;
	bpf_u_int32 maskp = 0;
	bpf_u_int32 netp = 0;
	dev = "wlan0";
//	dev = malloc(sizeof(char)*(NUM_CHARS + 1));

//	printf("Enter type of device: \n");
//	printf("eth0\nlo\nwlan0\n");
//	scanf("%s",dev);

	if(argc != 2) {
		fprintf(stdout, "Usage: %s \"filter program\"\n", argv[0]);    
		return 0;
	}

	if(argc == 2 && help(argv[1])) {
		displayHelp();
		exit(1);
	}

	FILE *f = fopen("test.pcap","w");
	fclose(f);

	des = begin(dev, netp, maskp, errbuf, fp, argv);
	pcap_loop(des,10,callback,NULL);

	addQueue();

	return 0;
}



























