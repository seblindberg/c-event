#include <event/event.h>

/* Macros ------------------------------------------------------------------- */



/* Private Functions -------------------------------------------------------- */




/* Global Variables --------------------------------------------------------- */




/* Function Definitions ----------------------------------------------------- */

void event__ctor(event_t *event, event__source_t source, event__value_t value)
{
  assert(event != NULL);
  
  /* Events should generally be immutable. */
  WRITE_CONST(event->source, event__source_t, source);
  WRITE_CONST(event->value, event__value_t, value);
}

#ifndef NDEBUG
void event__inspect(event_t const *event)
{
  if (event == NULL) {
    puts("Event: NULL");
  } else {
    printf("Event (%0zX): %u\n", (size_t) event__source(event), event__value(event));
  }
}
#endif /* NDEBUG */