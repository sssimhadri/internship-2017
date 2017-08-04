/*
 * Author :
 * purpose :
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
#include <defines.h>

int main (int argc, char **argv)
{
	char *dev;
	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_t* des;
//	const u_char *packet;
//	struct pcap_pkthdr header;
	struct bpf_program fp;
	bpf_u_int32 maskp;
	bpf_u_int32 netp;

	if(argc != 2) {
		fprintf(stdout, "Usage: %s \"filter program\"\n", argv[0]);    
		return 0;
	}

	dev = "wlan0";

//	void begin(dev, netp, maskp, errbuf);
	pcap_lookupnet(dev,&netp,&maskp,errbuf);

    des = pcap_open_live(dev,BUFSIZ,1,1,errbuf);
    if( des == NULL )
    {   
        printf("pcap_open_live: %s \n", errbuf);
        exit(1);
    }   
    else
    {   
        printf("opened\n");
    }   

//	void compile(des, fp, argv, netp);
	int comp = pcap_compile(des,&fp,argv[1],0,netp);
    
    if(comp == -1) 
    {   
        fprintf(stderr,"cant pcap_compile\n");
        exit(1);
    }   
    else 
    {   
        fprintf(stdout, "compiled\n");
    } 

//	void filter(des, fp);		
	int filt = pcap_setfilter(des,&fp);
    if(filt == -1) 
    {   
        fprintf(stderr,"cant filter\n");
        exit(1);
    }   
    else
    {   
        fprintf(stdout, "filtered\n");
    }

	pcap_loop(des,10,callback,NULL);

	return 0;

}
