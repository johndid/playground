#define ETH_TYPE_MAN (0x0c0c)
#define ETH_MAC_ADDR_LEN (6)
#define ETH_FRAME_LEN (1514)

struct ETH_NET_HEADER
{
    char dest[ETH_MAC_ADDR_LEN];
    char source[ETH_MAC_ADDR_LEN];
    short int type;
};

struct ETH_NET_802_HEADER
{
    char dest[ETH_MAC_ADDR_LEN];
    char source[ETH_MAC_ADDR_LEN];
    short int type;
    short int tpid;
    short int tci;
};


