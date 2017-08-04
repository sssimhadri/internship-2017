#ifndef DEFINE_H
#define DEFINE_H

u_int16_t handle_ethernet(u_char *args,const struct pcap_pkthdr* pkthdr,const u_char* packet);
void callback(u_char *args, const struct pcap_pkthdr* pkthdr, const u_char* packet);

#endif
