#ifndef DEFINE_H
#define DEFINE_H

u_int16_t handle_ethernet(u_char *args,const struct pcap_pkthdr* pkthdr,const u_char* packet);
void callback(u_char *args, const struct pcap_pkthdr* pkthdr, const u_char* packet);
//void store(char *src, char *des);
/*
void begin(char *dev, bpf_u_int32 net, bpf_u_int32 mask, char errbuf[]);
void compile(pcap_t* des, struct bpf_program fp, char **argv, bpf_u_int32 net);
void filter(pcap_t* des, struct bpf_program fp);
*/
#endif
