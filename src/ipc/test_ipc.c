#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mqueue.h"


int main(char **argv, int argc) {

	int qid;
        int rc;
	char *response = NULL;

	qid = mqueue_open();

        mqueue_flush(qid);
        
	rc = mqueue_send(qid, "Hello World");
        
	if (rc) {
		fprintf(stderr, "mqueue_send failed");
		exit(1);
	}

	rc = mqueue_rcv_nw(qid, &response);


	if (rc) {
		fprintf(stderr, "mqueue_rcv_nw failed %d\n", rc);
		exit(1);
	}


	printf("Received : %s\n", response);


	free(response);
}
