#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <linux/if_arp.h>

int main(int argc, char **argv)
{
    int s; /*socketdescriptor*/

    s = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (s == -1)
    {
	perror("You can't get the socket descriptor"); 
    }
    else
    {
	void* buffer = (void*)malloc(ETH_FRAME_LEN); /*Buffer for ethernet frame*/
	int length = 0; /*length of the received frame*/ 

	length = recvfrom(s, buffer, ETH_FRAME_LEN, 0, NULL, NULL);
	if (length == -1) 
	{
	    /* errorhandling .... */
	    printf("Nothing to see here move along! %s", strerror(errno));
	}
	else
	{
	    int i=0;
	    for(;i<ETH_FRAME_LEN;i++)
	    {
		printf("received-> %x\n",(unsigned int)buffer + i);
	    }
	}
    }
    return 0;
}
