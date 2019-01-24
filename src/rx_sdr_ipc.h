#ifndef _RX_SDR_IPC
#define _RX_SDR_IPC

#define RX_SDR_MAX_MSG 48

typedef enum {
   MSG_TYPE_HELO = 42
} rx_sdr_msg_type;

const char *mqueue_key = "./rx_sdr_ipc";

typedef struct {
    rx_sdr_msg_type msg_type;
    size_t msg_len;
    char msg[RX_SDR_MAX_MSG];
} RX_SDR_MSG_BUF;


#endif
