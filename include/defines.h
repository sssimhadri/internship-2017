#ifndef DEFINE_H
#define DEFINE_Hi

#include <pcap.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/if_ether.h>
#include <netinet/ether.h>
#include <netinet/ether.h>
#include <sys/types.h>
#include <unistd.h>

u_int16_t handle_ethernet(u_char *args,const struct pcap_pkthdr* pkthdr,const u_char* packet);
void callback(u_char *args, const struct pcap_pkthdr* pkthdr, const u_char* packet);
pcap_t* begin( char* dev, bpf_u_int32 netp, bpf_u_int32 maskp, char errbuf[], struct bpf_program fp, char **argv);
void addQueue();

#endif
