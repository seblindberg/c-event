#ifndef EVENT_DEBUGGER_H
#define EVENT_DEBUGGER_H 1

/* Includes ----------------------------------------------------------------- */

#include <compiler.h>
#include <event/event.h>
#include <event/event_listener.h>


/* Constants -------------------------------------+-------------------------- */




/* Data Types --------------------------------------------------------------- */

#ifndef NDEBUG
typedef struct {
  event_listener_t _super;
  const char       *label;
} event_debugger_t;

#else
typedef void * event_debugger_t;
#endif


/* Global Variables --------------------------------------------------------- */




/* Public Functions --------------------------------------------------------- */

#ifndef NDEBUG
void
  event_debugger__ctor(event_debugger_t *ed, const char *label)
  NONNULL;

void
  event_debugger__handler(event_debugger_t *ed, event_t *event)
  NONNULL;
  
#else
#define event_debugger__ctor(ed, label)
#define event_debugger__handler(ed, event)
#endif

/* Macros ----------------------------------------+--------+----------------- */




/* Inline Function Definitions ---------------------------------------------- */



#endif /* EVENT_DEBUGGER_H */