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
        char *msg = NULL;
        
        qid = mqueue_open();
        
        mqueue_flush(qid);
        
	// rc = mqueue_send(qid, "CFREQ:145500000");
        rc = mqueue_send(qid, "1234567");
        rc = mqueue_rcv_nw(qid, &msg);

        if (!rc) printf("Received: %s\n", msg);
        
        free(msg);
        return 0;
}


