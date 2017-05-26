#ifndef EVENT_H
#define EVENT_H 1

/* Includes ----------------------------------------------------------------- */

#include <compiler.h>


/* Constants -------------------------------------+-------------------------- */


/* Data Types --------------------------------------------------------------- */

typedef void const * event__source_t;
typedef uint16_t     event__value_t;

/* Main event data type.
 * Size: 4 bytes. */
typedef struct {
  event__source_t const source;
  event__value_t  const value;
} event_t;


/* Macros ----------------------------------------+--------+----------------- */




/* Global Variables --------------------------------------------------------- */




/* Public Functions ---------+----------------------------------------------- */

void
  event__ctor(event_t *event, event__source_t source, event__value_t value);

static inline event__source_t
  event__source(event_t const *event);
  
static inline event__value_t
  event__value(event_t const *event);


#ifndef NDEBUG
void
  event__inspect(event_t const *event);
#else
#define event__inspect(e)
#endif /* NDEBUG */


/* Inline Function Definitions ---------------------------------------------- */

event__source_t event__source(event_t const *event)
{
  assert(event != NULL);
  return event->source;
}

event__value_t event__value(event_t const *event)
{
  assert(event != NULL);
  return event->value;
}

#endif /* EVENT_H */