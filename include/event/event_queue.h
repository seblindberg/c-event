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
  event_queue__ctor(event_queue_t *eq, event_t *buffer, size_t size)
  NONNULL_ARGS(1);
  
event_queue__result_t
  event_queue__grow(event_queue_t *eq)
  NONNULL;
  
event_queue__result_t
  event_queue__shrink(event_queue_t *eq)
  NONNULL;

event_queue__result_t
  event_queue__put(event_queue_t *eq, event_t const *event)
  NONNULL;
  
event_queue__result_t
  event_queue__take(event_queue_t *eq, event_t *dest)
  NONNULL;

uint8_t
  event_queue__size(event_queue_t const *eq)
  NONNULL;
  
uint8_t
  event_queue__used(event_queue_t const *eq)
  NONNULL;
  
uint8_t
  event_queue__available(event_queue_t const *eq)
  NONNULL;

static inline bool_t
  event_queue__is_empty(event_queue_t const *eq)
  NONNULL;
  
static inline bool_t
  event_queue__is_full(event_queue_t const *eq)
  NONNULL;


/* Inline Function Definitions ---------------------------------------------- */

bool_t
event_queue__is_empty(event_queue_t const *eq)
{
  return fifo__is_empty(&eq->_super);
}

bool_t
event_queue__is_full(event_queue_t const *eq)
{
  return fifo__is_full(&eq->_super);
}

#endif /* EVENT_QUEUE_H */