#include <event/event_queue.h>

/* Macros ------------------------------------------------------------------- */



/* Private Functions -------------------------------------------------------- */




/* Global Variables --------------------------------------------------------- */




/* Function Definitions ----------------------------------------------------- */

void event_queue__ctor(event_queue_t *eq, event_t *buffer, size_t size)
{
  assert((size % sizeof(event_t)) == 0);

  fifo__ctor(&eq->_super, buffer, size);
}

event_queue__result_t event_queue__grow(event_queue_t *eq)
{
  size_t new_size;
  
  assert(eq != NULL);
  
  /* Double the buffer in size. */
  new_size = fifo__size(&eq->_super) << 1;
  
  /* Try to grow it. */
  return (event_queue__result_t) fifo__resize(&eq->_super, new_size);
}

event_queue__result_t event_queue__shrink(event_queue_t *eq)
{
  size_t new_size;
  
  assert(eq != NULL);
  
  /* Half the buffer in size. */
  new_size = fifo__size(&eq->_super) >> 1;
  
  return (event_queue__result_t) fifo__resize(&eq->_super, new_size);
}

event_queue__result_t event_queue__put(event_queue_t *eq, event_t const *event)
{
  size_t written;
  
  assert(eq != NULL);
  assert(event != NULL);
  
  written = fifo__write(&eq->_super, event, sizeof(event_t));
  
  /* Since the buffer size should be divisible by the size
     of one event, the number of bytes written should only
     be 0 or the whole event data. */
  assert(written == 0 || written == sizeof(event_t));
  
  if (written == 0) {
    return EVENT_QUEUE__FULL;
  }
  
  return EVENT_QUEUE__OK;
}

event_queue__result_t event_queue__take(event_queue_t *eq, event_t *dest)
{
  size_t read;
  
  assert(eq != NULL);
  assert(dest != NULL);
  
  read = fifo__read(&eq->_super, dest, sizeof(event_t));
  
  /* Since the buffer size should be divisible by the size
     of one event, the number of bytes read should only be
     0 or the whole event data. */
  assert(read == 0 || read == sizeof(event_t));
  
  if (read == 0) {
    return EVENT_QUEUE__EMPTY;
  }
  
  return EVENT_QUEUE__OK;
}

uint8_t event_queue__size(event_queue_t const *eq)
{
  assert(eq != NULL);
  return fifo__size(&eq->_super) / sizeof(event_t);
}

uint8_t event_queue__used(event_queue_t const *eq)
{
  assert(eq != NULL);
  return fifo__used(&eq->_super) / sizeof(event_t);
}

uint8_t event_queue__available(event_queue_t const *eq)
{
  assert(eq != NULL);
  return fifo__available(&eq->_super) / sizeof(event_t);
}
