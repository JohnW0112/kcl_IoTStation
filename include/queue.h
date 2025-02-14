#ifndef QUEUE_H_
#define QUEUE_H_

#include "unistd.h"

#define queueArraySize 200
/*variables*/
typedef struct
{
  uint16_t queueNum[queueArraySize];
  uint8_t waterAmount[queueArraySize];
  uint16_t currentQueueNumber;
  uint8_t currentWaterAmount;
  uint8_t head, tail;
  bool isFull;
} queue_s;

typedef enum
{
  QUEUE_INSERT_SUCCESSFUL,
  QUEUE_POP_SUCCESSFUL,
  QUEUE_POP_EMPTY_ERROR,
  QUEUE_INSERT_FULL_ERROR,
  QUEUE_INSERT_INVALID_WATER_ERROR
} queue_stat_e;
void queue_init(queue_s *q);
queue_stat_e queue_insert(queue_s *q, uint8_t waterAmount);
queue_stat_e queue_pop(queue_s *q);

#endif