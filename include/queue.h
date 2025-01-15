#ifndef QUEUE_H_
#define QUEUE_H_

#include "unistd.h"

#define queueArraySize  200
/*variables*/
typedef struct{
  uint16_t queueNum[queueArraySize];
  uint8_t waterAmount[queueArraySize];
  uint16_t currentQueueNumber;
  uint8_t head, tail;
}queue_s;

void queue_init(queue_s q);


#endif