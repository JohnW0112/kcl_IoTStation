#include "queue.h"

void queue_init(queue_s *q)
{
    q->head = 0;
    q->tail = 0;
    q->currentQueueNumber = 0;
    q->currentWaterAmount = 0;
    q->isFull = false;
}

queue_stat_e queue_insert(queue_s *q, uint8_t waterAmount)
{
    uint8_t newTail = (q->tail + 1) % queueArraySize;
    uint16_t prevQueueNum = q->queueNum[q->tail];

    // check if queue is full
    if (q->isFull == true)
        return QUEUE_INSERT_FULL_ERROR;

    // check for invalid water input
    if (waterAmount < 0 || waterAmount > 20)
        return QUEUE_INSERT_INVALID_WATER_ERROR;

    q->queueNum[q->tail] = prevQueueNum + 1;
    q->waterAmount[q->tail] = waterAmount;

    q->tail = newTail;
    if (newTail == q->head)
        q->isFull = true;

    return QUEUE_INSERT_SUCCESSFUL;
}
queue_stat_e queue_pop(queue_s *q)
{
    uint8_t newHead = (q->head + 1) % queueArraySize;
    // check if queue is empty or not
    if (q->head == q->tail && q->isFull != true)
        return QUEUE_POP_EMPTY_ERROR;

    q->currentQueueNumber = q->queueNum[q->head];
    q->currentWaterAmount = q->waterAmount[q->head];

    // if queue was full, set full flag to false
    if (q->isFull == true)
    {
        q->tail = (q->tail + 1) % queueArraySize;
        q->isFull = false;
    }

    q->head = newHead;

    return QUEUE_POP_SUCCESSFUL;
}