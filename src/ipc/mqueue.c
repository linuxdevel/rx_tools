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
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h> 
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include "mqueue.h"

#define MAX_MSG_SZ 80

typedef struct {
           long int mtype;
           char mtext[MAX_MSG_SZ+1];
} RX_SDR_MSG_BUF;

// TODO make mqueue_key configurable
const char *mqueue_key = "/tmp/rx_sdr_ipc.queue";

static void init_q_file();

int mqueue_open(void) {
        key_t key;
        int msg_id;
        
        init_q_file(); 
        
        key = ftok(mqueue_key, 65);

        if (-1 == key) {
                perror("mqueue.open: ftok() failed");
                exit(1);
                
        }
        msg_id = msgget(key, 0666 | IPC_CREAT);
        if (-1 == msg_id) {
                perror("mqueue.open: msgget() failed");
                exit(1);
                
        }
        
        return msg_id;
}

int mqueue_close(int qid) {
        return 0;
}

int mqueue_send(int qid, const char *out) {
        int rc;
        size_t out_len;
        RX_SDR_MSG_BUF msg;
        
        msg.mtype = 1;
        
        snprintf(msg.mtext, sizeof(msg.mtext), out);
        
        if (msgsnd(qid, (void *) &msg, sizeof(msg.mtext), IPC_NOWAIT) == -1) {
                perror("msgsnd error");
                exit(EXIT_FAILURE);
        }
                
        return rc;
}

int mqueue_rcv_nw(int qid, char **in) {
        int rc = -1;
        RX_SDR_MSG_BUF msg = {0};

        if (msgrcv(qid, &msg, sizeof(msg.mtext), 1, MSG_NOERROR | IPC_NOWAIT) == -1) {
              if (errno != ENOMSG) {
                   perror("msgrcv");
                   exit(EXIT_FAILURE);
               }
        } else {
                rc = 0;
                size_t msglen = strlen(msg.mtext);
                *in = malloc(msglen + 1);
                if (NULL == *in) {
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		snprintf(*in, msglen+1, msg.mtext);
        }
        
        return rc;
}

void mqueue_flush(int qid) {
        char *msg = NULL;
        while (0 == mqueue_rcv_nw(qid, &msg)) {
                free(msg);
        }
}

static void init_q_file() {
        FILE *f;

        f = fopen(mqueue_key, "a");

        if (!f) {
                perror("mqueue init_q_file error");
                exit(1);
        }
        fclose(f);
}
