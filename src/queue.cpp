#include "queue.h"

void queue_init(queue_s q){
    q.head = 0;
    q.tail = 0;
    q.currentQueueNumber = 0;
}