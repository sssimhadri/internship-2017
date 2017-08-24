/*
 * Author : Satyajit Simhadri
 * purpose : capture, store, and search network packets
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
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <defines.h>

#define NUM_CHARS 256
#define PCAP_SAVEFILE "./pcap_savefile"

int main(int argc, char **argv)
{
	char *dev = "en0";
	int packets = 0;
	int num;
	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_t* des;
	struct bpf_program fp;
	bpf_u_int32 maskp = 0;
	bpf_u_int32 netp = 0;

	printf("Enter amount of packets to receive:  \n");
	scanf("%d",&packets);

	pcap_lookupnet(dev,&netp,&maskp,errbuf);

    des = pcap_open_live(dev,BUFSIZ,1,1,errbuf);
    if( des == NULL ) {
        printf("pcap_open_live: %s \n", errbuf);
        exit(1);
	} else {
        printf("opened\n");
    }
	
	int comp = pcap_compile( des, &fp, NULL, 0, netp );
	
	if(comp == -1) {
		fprintf(stderr,"cant pcap_compile\n");
		exit(1);
	} else {
		fprintf(stdout,"compiled\n");
	}

	int filt = pcap_setfilter(des,&fp);
    if(filt == -1) {   
        fprintf(stderr,"cant filter\n");
        exit(1);
    } else {   
        fprintf(stdout, "filtered\n");
    }

	/* clears content of test.pcap before storing addresses in it */
	FILE *f = fopen("test.pcap","w");
	fclose(f);

	pcap_loop(des,packets,callback,NULL);

	num = 2*packets;
	storing(num);

	return 0;
}



























