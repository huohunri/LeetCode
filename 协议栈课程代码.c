



#define PROTO_IP  0x0800
#define PROTO_UDP  17



#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <sys/poll.h>

#define NETMAP_WITH_LIBS

#include <net/netmap_user.h>


#pragma pack(1)


#define ETH_LENGTH	6

struct ethhdr {
	unsigned char h_dest[ETH_LENGTH];
	unsigned char h_src[ETH_LENGTH];
	unsigned short h_proto;
};


struct iphdr {

	unsigned char version:4,
				  hdrlen:4;
	unsigned char tos;
	unsigned short tot_len;

	unsigned short id;
	unsigned short flag:3,
				   offset:13;

	unsigned char ttl;
	unsigned char protocol;

	unsigned short check;

	unsigned int sip;
	unsigned int dip;
	
};



struct udphdr {

	unsigned short sport;
	unsigned short dport;
	unsigned short len;
	unsigned short check;

};


struct udppkt {

	struct ethhdr eh;
	struct iphdr ip;
	struct udphdr udp;
	unsigned char body[0];

};



int main() {


	struct ethhdr *eh;
	unsigned char *stream = NULL;
	struct nm_pkthdr h;

	struct nm_desc *nmr = nm_open("netmap:eth0", NULL, 0, NULL);
	if (nmr == NULL) {
		return -1;
	}

	struct pollfd pfd = {0};
	pfd.fd = nmr->fd;
	pfd.events = POLLIN;
	
	while (1) {


		int ret = poll(&pfd, 1, -1);
		if (ret < 0)  continue;


		if (pfd.revents & POLLIN) {

			stream = nm_nextpkt(nmr, &h);
			eh = (struct ethhdr*)stream;

			if (ntohs(eh->h_proto) == PROTO_IP) {

				struct udppkt *udp = (struct udppkt*)stream;

				if (udp->ip.protocol == PROTO_UDP) {

					int length = ntohs(udp->udp.len);
					udp->body[length - 8] = '\0';
					
					printf("udp --> %s\n", udp->body);

				}
				
			}

		}
		

	}

}









