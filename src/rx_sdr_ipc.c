/*
 * rx_sdr_ipc.c 
 * Starting point...
 */

#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/msg.h>
#include "rx_sdr_ipc.h"



int main(int argc, char **argv) {
	key_t key;
        RX_SDR_MSG_BUF msg;
	int msg_id;

        key = ftok(mqueue_key, 65);

        msg_id = msgget(key, 0666 | IPC_CREAT);
	msg.msg_type = MSG_TYPE_HELO;
	sprintf(msg.msg, "Hello");
	msg.msg_len = strlen(msg.msg);

	if (0 != msgsnd(msg_id, &msg, sizeof(RX_SDR_MSG_BUF), 0)) {
                perror("msgsnd failed");
		exit(1);
	}

	printf("msgsnd OK\n");

        return 0;
}


