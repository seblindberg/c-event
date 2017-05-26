/*
 * Run with arguments
 *   -I../include -I../ext/list/include -I../ext/fifo/include -L../ext/list/lib -L../ext/fifo/lib -lfifo -llist ../lib/event/event.c ../lib/event/event_queue.c
 */


#include <compiler.h>

#include <event/event.h>
#include <event/event_queue.h>

#include "helper.h"

void test__create(void)
{
  event_queue_t *event_queue = helper__event_queue();
  
  assert(event_queue__is_empty(event_queue));
  assert(!event_queue__is_full(event_queue));
  assert(event_queue__size(event_queue) == 2);
  assert(event_queue__used(event_queue) == 0);
  assert(event_queue__available(event_queue) == 2);
}

void test__put(void)
{
  event_queue_t *event_queue = helper__event_queue();
  event_t        event;
  uint_fast8_t   res;
  
  res = event_queue__put(event_queue, &event);
  assert(res == EVENT_QUEUE__OK);
  
  assert(!event_queue__is_empty(event_queue));
  assert(!event_queue__is_full(event_queue));
  
  assert(event_queue__used(event_queue) == 1);
  assert(event_queue__available(event_queue) == 1);
  
  res = event_queue__put(event_queue, &event);
  assert(res == EVENT_QUEUE__OK);
  
  assert(!event_queue__is_empty(event_queue));
  assert(event_queue__is_full(event_queue));
  
  assert(event_queue__used(event_queue) == 2);
  assert(event_queue__available(event_queue) == 0);
  
  res = event_queue__put(event_queue, &event);
  assert(res == EVENT_QUEUE__FULL);
}

void test__take(void)
{
  event_queue_t *event_queue = helper__event_queue();
  event_t event;
  event_t dest;
  
  assert(event_queue__take(event_queue, &dest) ==
    EVENT_QUEUE__EMPTY);
  
  event__ctor(&event, NULL, 0xDEAD);
  event_queue__put(event_queue, &event);
  
  assert(event_queue__take(event_queue, &dest) ==
    EVENT_QUEUE__OK);
  
  assert(event__value(&event) == event__value(&dest));
  
  event_queue__put(event_queue, &event);
  event_queue__put(event_queue, &event);
  
  assert(event_queue__take(event_queue, &dest) ==
    EVENT_QUEUE__OK);
  assert(event_queue__take(event_queue, &dest) ==
    EVENT_QUEUE__OK);
  assert(event_queue__take(event_queue, &dest) ==
    EVENT_QUEUE__EMPTY);
}

void test__grow(void)
{
  event_queue_t *event_queue = helper__event_queue();
  event_t event;
  
  event_queue__put(event_queue, &event);
  event_queue__put(event_queue, &event);
  
  assert(event_queue__is_full(event_queue));
  
  event_queue__grow(event_queue);
  assert(event_queue__size(event_queue) == 4);
  
  assert(!event_queue__is_full(event_queue));
  
  event_queue__put(event_queue, &event);
  assert(event_queue__put(event_queue, &event) ==
    EVENT_QUEUE__OK);
  
  /* Now the buffer shuould be full again */
  assert(event_queue__put(event_queue, &event) ==
    EVENT_QUEUE__FULL);
}

void test__shrink(void)
{
  event_queue_t *event_queue = helper__event_queue();
  event_t event;
  
  event_queue__put(event_queue, &event);
  
  assert(!event_queue__is_full(event_queue));
  
  event_queue__shrink(event_queue);
  
  assert(event_queue__size(event_queue) == 1);
  assert(event_queue__is_full(event_queue));
}

void test__empty_queue(void)
{
  event_queue_t event_queue;
  event_t event;
  event_queue__ctor(&event_queue, NULL, 0);
  
  assert(event_queue__is_empty(&event_queue));
  assert(event_queue__is_full(&event_queue));
  assert(event_queue__put(&event_queue, &event) == EVENT_QUEUE__FULL);
}

int main(int argc, char *argv[])
{
  test__create();
  test__put();
  test__take();
  test__grow();
  test__shrink();
  test__empty_queue();

  return 0;
}
