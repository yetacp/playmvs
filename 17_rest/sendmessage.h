#ifndef __SEND_MESSAGE_H__
#define __SEND_MESSAGE_H__

#include "../08_fss/aux.h"

#define RESPONSE_SIZE 2048
#define sendmessage SENDMSG

Sint32 sendmessage(char *ip, int port, char *buffer, int size);
#endif
