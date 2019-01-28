/*
 * rx_sdr_ipc.c 
 * Starting point...
 */

#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/msg.h>
#include "mqueue.h"



int main(int argc, char **argv) {
	int qid;
        int rc;
        //char *msg = NULL;
        
        qid = mqueue_open();
        
        mqueue_flush(qid);
        
	rc = mqueue_send(qid, "CFREQ:120450000");

	if (rc) {
		fprintf(stderr, "mqueue_Send failed\n");
		exit(1);
	}

        //rc = mqueue_rcv_nw(qid, &msg);

        // if (!rc) printf("Received: %s\n", msg);
        
        //if (msg) free(msg);
        return 0;
}


