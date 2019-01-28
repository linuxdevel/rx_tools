/*
 * rx_sdr_ipc.c 
 * Starting point...
 */

#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/msg.h>
#include "mqueue.h"
/* Testprogram that shows how to send new center frequency
 * to rx_sdr
 * */
int main(int argc, char **argv) {
	int qid;
        int rc;
        
        qid = mqueue_open();
        
        mqueue_flush(qid);
        
	rc = mqueue_send(qid, "CFREQ:120450000");

	if (rc) {
		fprintf(stderr, "mqueue_Send failed\n");
		exit(1);
	}

        return 0;
}


