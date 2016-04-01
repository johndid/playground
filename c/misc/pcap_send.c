#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#define PDU_L2_REQ		   0x0a
#define PDU_L2_TIME_SYNC_REQ	   0x0f
#define PDU_L2_XON_XOFF_REQ	   0x03
#define PDU_L4_UPDATE_VARIABLE 	   0x01
#define MAXMSGSIZE		   96

struct MESSAGE {
    unsigned char PhysicalSourceAddress;
    unsigned char PhysicalDestinationAddress;
    unsigned char PDUType;
    unsigned char MulticastGroup;
    unsigned char Layer2Status;
    unsigned char Layer2DataFieldLength;
    unsigned char DestinationSegment;
    unsigned char DestinationNode;
    unsigned char DestinationRSAP;
    unsigned char SourceSegment;
    unsigned char SourceNode;
    unsigned char SourceSSAP;
    unsigned char PriorityAndVersion;
    unsigned char MsgSequenceNumber;
    unsigned char DataLength;
    unsigned char Pad1;
    unsigned char Message[MAXMSGSIZE];
};

/* This one must be swapped due to teh way that the type is written!!!! therefore 0x88b6 becomes 0xb688 */
#define ETH_TYPE_MAN (0xb688)
#define ETH_MAC_ADDR_LEN (6)
#define ETH_FRAME_LEN (1514)

struct ETH_NET_HEADER
{
    char dest[ETH_MAC_ADDR_LEN];
    char source[ETH_MAC_ADDR_LEN];
    short int type;
};

typedef struct ETH_NET_802_HEADER
{
    char dest[ETH_MAC_ADDR_LEN];
    char source[ETH_MAC_ADDR_LEN];
    short int tpid;
    short int tci;
    short int type;
};

#define MAX_ID_SIZE (50)
#define MAX_DATA_SIZE (39) // (2 -1 -1 - MAX_ID_SIZE -1);

typedef struct CmdPdu
{
    enum PduType {
	PDU_INVOKE_REQ = 0xf0,
	PDU_INVOKE_ACK = 0xf1,
	PDU_INVOKE_NAK = 0xf2
    };

    unsigned char type;
    unsigned char link;
    unsigned char size;
    char id[MAX_ID_SIZE];
    char data[MAX_DATA_SIZE];

} GCCPACKED;

#define HAVE_REMOTE
#include <pcap/pcap.h>

int main(int argc, char **argv)
{
    /* Check the validity of the command line */
    if (argc != 2)
    {
        printf("usage: %s interface (e.g. 'rpcap://eth0')", argv[0]);
    }
    else 
    {
	pcap_t *fp;
	char errbuf[PCAP_ERRBUF_SIZE];
	fp = pcap_open_live(argv[1], ETH_FRAME_LEN, 1, 1000, errbuf);
	if(NULL == fp)
	{
	    fprintf(stderr,"\nUnable to open the adapter. %s is not supported by WinPcap\n", argv[1]);
	    return 1;
	}
	else
	{
	    /*ETH_NET_HEADER*/
	    ETH_NET_802_HEADER hdr = {0};
	    unsigned char src_mac[ETH_MAC_ADDR_LEN] = {0x00, 0x50, 0xb6, 0x0d, 0x35, 0x9f};
	    unsigned char dest_mac[ETH_MAC_ADDR_LEN] = {0x00, 0x13, 0x95, 0x09, 0x3d, 0xa8};

	    memcpy((void*)hdr.dest,(void*)dest_mac,sizeof(hdr.dest));
	    memcpy((void*)hdr.source,(void*)src_mac,sizeof(hdr.source));
	    hdr.type = ETH_TYPE_MAN;
	    hdr.tpid = 0x0081;

	    MESSAGE msg = {0};
	    msg.PhysicalSourceAddress = 240;
	    msg.PhysicalDestinationAddress = 241;
	    msg.PDUType = PDU_L2_REQ;

	    CmdPdu cmd = {0};
	    cmd.type = CmdPdu::PDU_INVOKE_REQ;
	    cmd.link = 0x01;
	    cmd.size = 20+18+3; // ?????
	    memcpy((void*)cmd.id,(void*)"THIS IS A COMMAND ID",20);
	    memcpy((void*)cmd.data,(void*)"COMMAND DATA STUFF",18);

	    // Dump the command in the message field!?!?!
	    msg.DataLength = cmd.size; 
	    memcpy((void*)msg.Message,(void*)&cmd,msg.DataLength);

	    unsigned char packet[ETH_FRAME_LEN] = {0};
	    int hdr_size = sizeof(hdr);
	    int pkg_size = (int)offsetof(struct MESSAGE,Message)+msg.DataLength;
	    memcpy((void*)packet,(void*)&hdr,hdr_size);
	    memcpy((void*)packet+sizeof(hdr),(void*)&msg,hdr_size + pkg_size);
    
	    /* Send down the packet */
	    if (pcap_sendpacket(fp, packet, hdr_size + pkg_size) != 0)
	    {
		fprintf(stderr,"\nError sending the packet: \n", pcap_geterr(fp));
		return 1;
	    }
	    return 0;
	}
    }
    return 1;
}
