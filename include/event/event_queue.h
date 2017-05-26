/* Event Queue
 *
 * The event queue takes a buffer (size = 2^n) and stores events in a FIFO
 * fashion.
 */

#ifndef EVENT_QUEUE_H
#define EVENT_QUEUE_H 1

/* Includes ----------------------------------------------------------------- */

#include <compiler.h>
#include <fifo.h>
#include <event/event.h>


/* Data Types --------------------------------------------------------------- */

typedef struct event_queue {
  fifo_t       _super;
} event_queue_t;

/* Extend the result codes of the parent fifo.
 */
typedef enum {
  EVENT_QUEUE__OK           = FIFO__OK,
  EVENT_QUEUE__EMPTY        = FIFO__EMPTY,
  EVENT_QUEUE__FULL         = FIFO__FULL,
  EVENT_QUEUE__INVALID_SIZE = FIFO__INVALID_SIZE,
} event_queue__result_t;


/* Macros ------------------------------------------------------------------- */




/* Global Variables --------------------------------------------------------- */




/* Public Functions --------------------------------------------------------- */

void
  event_queue__ctor(event_queue_t *eq, event_t *buffer, size_t size);
  
event_queue__result_t
  event_queue__grow(event_queue_t *eq);
  
event_queue__result_t
  event_queue__shrink(event_queue_t *eq);

event_queue__result_t
  event_queue__put(event_queue_t *eq, event_t const *event);
  
event_queue__result_t
  event_queue__take(event_queue_t *eq, event_t *dest);

uint8_t
  event_queue__size(event_queue_t const *eq);
  
uint8_t
  event_queue__used(event_queue_t const *eq);
  
uint8_t
  event_queue__available(event_queue_t const *eq);

static inline bool_t
  event_queue__is_empty(event_queue_t const *eq);
  
static inline bool_t
  event_queue__is_full(event_queue_t const *eq);


/* Inline Function Definitions ---------------------------------------------- */

bool_t event_queue__is_empty(event_queue_t const *eq)
{
  assert(eq != NULL);
  return fifo__is_empty(&eq->_super);
}

bool_t event_queue__is_full(event_queue_t const *eq)
{
  assert(eq != NULL);
  return fifo__is_full(&eq->_super);
}

#endif /* EVENT_QUEUE_H */