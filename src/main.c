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
#include <defines.h>

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
	bpf_u_int32 maskp;
	bpf_u_int32 netp;

	if(argc != 2) {
		fprintf(stdout, "Usage: %s \"filter program\"\n", argv[0]);    
		return 0;
	}

	printf("%s\n",argv[1]);
	printf("%d\n",argc);
	

	if(argc == 2 && help(argv[1])) {
		displayHelp();
		exit(1);
	}

	dev = "wlan0";

	des = begin(dev, netp, maskp, errbuf, fp, argv);
	pcap_loop(des,10,callback,NULL);

	return 0;
}
