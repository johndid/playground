#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <linux/if_arp.h>

/* #define ETH_FRAME_LEN 1518 /\* why the fuck is this defined to be larger? :O *\/ */
#define MAC_ADR_SIZE ETH_ALEN

int main(int argc, char **argv)
{
    int s; /*socketdescriptor*/
//    opt = "eth0";
    s = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (s == -1) 
    { 
	printf("Socket not available! Err: %s\n", strerror(errno));
	perror("");
    }
    else
    {
	int j = 0;
	struct sockaddr_ll socket_address = {0};        /* target address*/
	void* buffer = (void*)malloc(ETH_FRAME_LEN);    /* buffer for ethernet frame*/
	unsigned char* etherhead = buffer;              /* pointer to ethenet header*/
	unsigned char* data = buffer + ETH_HLEN;        /* userdata in ethernet frame*/
	struct ethhdr *eh = (struct ethhdr *)etherhead; /* another pointer to ethernet header*/
	int send_result = 0;
//	unsigned char src_mac[MAC_ADR_SIZE] = {0xf0, 0xde, 0xf1, 0xdb, 0xb6, 0x53};  /* our MAC address f0:de:f1:db:b6:53 (found using ifconfig -a */
	unsigned char src_mac[MAC_ADR_SIZE] = {0x00, 0x50, 0xb6, 0x0d, 0x35, 0x9f};  /* our MAC address f0:de:f1:db:b6:53 (found using ifconfig -a */
	unsigned char dest_mac[MAC_ADR_SIZE] = {0x00, 0x13, 0x95, 0x09, 0x3d, 0xa8}; /* other host MAC address 00:0c:29:1a:10:8a (found using ipconfig /all (windows!)) */

//	setsockopt(s, SOL_SOCKET, SO_BINDTODEVICE, "eth1", 4);

        /*prepare sockaddr_ll*/
	socket_address.sll_family   = PF_PACKET;        /* RAW communication*/
	socket_address.sll_protocol = htons(ETH_P_IP);	/* we don't use a protocoll above ethernet layer ->just use anything here */
	socket_address.sll_ifindex  = 2;                /* index of the network device see full code later how to retrieve it */
	socket_address.sll_hatype   = ARPHRD_ETHER;     /* ARP hardware identifier is ethernet */
	socket_address.sll_pkttype  = PACKET_OTHERHOST; /*target is another host*/
	socket_address.sll_halen    = ETH_ALEN;		/*address length*/

	memcpy((void*)socket_address.sll_addr,(void*)dest_mac,ETH_ALEN);

        /* set ethernet the frame header */
	memcpy((void*)buffer, (void*)dest_mac, ETH_ALEN);
	memcpy((void*)(buffer+ETH_ALEN), (void*)src_mac, ETH_ALEN);
	eh->h_proto = 0x00;
	/* eh->h_proto = 0x86DD; */

        /* fill the frame with some data */
	for (; j < ETH_DATA_LEN; j++) 
	{
	    data[j] = (unsigned char)((int) (255.0*rand()/(RAND_MAX+1.0)));
	}

	data[0] = 'J';
	data[1] = 'O';
	data[2] = 'H';
	data[3] = 'N';

        /* send the packet */
	send_result = sendto(s, buffer, ETH_FRAME_LEN, 0, (struct sockaddr*)&socket_address, sizeof(socket_address));
	if (send_result == -1) 
	{
	    printf("Sending failed! Err: %s\n", strerror(errno));
	    perror("");
	}
    }
    return 0;
}
