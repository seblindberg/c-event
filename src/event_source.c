#include <event/event_source.h>

/* Macros ------------------------------------------------------------------- */



/* Private Functions -------------------------------------------------------- */




/* Global Variables --------------------------------------------------------- */




/* Function Definitions ----------------------------------------------------- */


void
event_source__dispatch(event_source_t const *es, event__value_t value)
{  
  event_listener_t *listener = event_source__first_listener(es);
    
  if (listener == NULL) {
    return;
  }
  
  /* Allocate and create the event */
  event_t event;
  event__ctor(&event, es, value);
  
  while (listener != NULL) {
    event_listener__call(listener, &event);
    listener = event_listener__next(listener);
  }
}
