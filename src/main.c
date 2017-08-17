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

	dev = malloc(sizeof(char)*(NUM_CHARS + 1));

	printf("Enter type of device: \n");
	printf("eth0\nlo\nwlan0\n");
	scanf("%s",dev);
/*
	if(argc != 2) {
		fprintf(stdout, "Usage: %s \"filter program\"\n", argv[0]);    
		return 0;
	}

	printf("%s\n",argv[1]);
	printf("%d\n",argc);
*/	

	if(argc == 2 && help(argv[1])) {
		displayHelp();
		exit(1);
	}

//	printf("Set filter: ");
//	gets(filter);

	des = begin(dev, netp, maskp, errbuf, fp);
	pcap_loop(des,10,callback,NULL);

//	node_t* start = NULL;
	printf("trying to read file\n");
	FILE *f;
	char line[256];
	f = fopen("test.pcap","r");
	while (fgets(line,sizeof(line),f)) {
		printf("%s",line);	
	}
	fclose(f);

	

/*	pcap_dumper_t *pd;
	char filename[80];
	strcpy(filename, PCAP_SAVEFILE);
	pd = pcap_dump_open(des,filename);
	if( pd == NULL ) {
		printf("cant open file\n");
	}
	int count; 
	count = pcap_dispatch(des, 20, &pcap_dump, (char*)pd);
	if( count < 0 ) {
		printf("cant read packet\n");
	}
	int linktype = 0;
	if (!(linktype = pcap_datalink(des))) {
		printf("error with link layer\n");
		exit(9);
	}
	int stat;
	struct pcap_stat ps;
	stat = pcap_stats(des,&ps);
	if( stat != 0 ) {
		printf("error with stat\n");
	}
*/
	/* Print the statistics out */
/*	printf("Packet Capture Statistics:\n");
	printf("%d packets received by filter\n", ps.ps_recv);
	printf("%d packets dropped by kernel\n", ps.ps_drop);
*/
        /*
         * Close the savefile opened in pcap_dump_open().
         */
//	pcap_dump_close(pd);
        /*
         * Close the packet capture device and free the memory used by the
         * packet capture descriptor.
         */     
//	pcap_close(des); 
	
	return 0;
}



























