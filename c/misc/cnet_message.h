#define MINIMUM_ARCNET_NODE_ID     ((unsigned char)0xC0)
#define ALLOK 	                   ((unsigned char)0)
#define NOMOSAPS                   ((unsigned char)1)
#define SAPUSED                    ((unsigned char)2)
#define UNKNOWNBUFHAND             ((unsigned char)3)
#define OUTOFMEMORY                ((unsigned char)4)
#define PARAMOUTOFRANGE            ((unsigned char)5)
#define INTERNALSAPERROR           ((unsigned char)6)
#define CNET_NOMSG                 ((unsigned char)7)
#define WELL_KNOWN_SAPID_TOO_LARGE ((unsigned char)8)
#define SERVER_ERROR               ((unsigned char)9)

#define SKIPOLD    	           0x00
#define SKIPNEW		           0x01
#define BLOCK			   0x02

#define PDU_L2_REQ		   0x0a
#define PDU_L2_TIME_SYNC_REQ	   0x0f
#define PDU_L2_XON_XOFF_REQ	   0x03

#define PDU_L4_UPDATE_VARIABLE 	   0x01

#define ACKOK 		           0x00
#define NOACK 		           0x01
#define EXCNAK 		           0x02
#define XOFFNAK		           0x03
#define RECONFNAK                  0x04
                                   
#define WAITING		           0xfd
#define TRANSMITTING	           0xff
#define TIMEOUT		           0xfe
#define DONTCARE		   0xff

#define MAXMSGSIZE		   96

enum TagSapStatus 
{
    SAPOK=0,
    SAPBLOCKING
};

#define SENT_ON_ARC_CHANNEL_A      0xA
#define SENT_ON_ARC_CHANNEL_B      0xB
#define RECEIVED_ON_ARC_CHANNEL_A  0xA
#define RECEIVED_ON_ARC_CHANNEL_B  0xB
#define MESSAGE_HEADER_SIZE 16

typedef struct MESSAGE {
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
