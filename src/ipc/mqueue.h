#ifndef _MQUEUE_H
#define _MQUEUE_H


int mqueue_open(void);
int mqueue_close(int qid);
int mqueue_send(int qid, const char *out);
int mqueue_rcv_nw(int qid, char **in);
void mqueue_flush(int qid);

#endif