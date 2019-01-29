/*
 * mqueue a simplified linux mqueue interface
 * Copyright (C) 2019 by Arne Brune Olsen
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
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
