#ifndef EVENT_SOURCE_H
#define EVENT_SOURCE_H 1

/* Includes ----------------------------------------------------------------- */

#include <compiler.h>
#include <list/s_list_item.h>
#include <list/s_list.h>
#include <event/event.h>
#include <event/event_listener.h>

#ifndef NDEBUG
#include <event/event_debugger.h>
#endif /* NDEBUG */


/* Data Types --------------------------------------------------------------- */

typedef struct event_source {
  s_list_t _super;
} event_source_t;



/* Macros ----------------------------------------+-------------------------- */

// #define EVENT_SOURCE__ID                          (__COUNTER__ + 1)


/* Global Variables --------------------------------------------------------- */




/* Public Functions --------------------------------------------------------- */

/* Create an event source.
 */
static inline void
  event_source__ctor(event_source_t *es);

/* Get the number of listeners attached to the event source.
 */

static inline size_t
  event_source__listeners(event_source_t const *es);

/* Attatch an event listener to the event source.
 */
 
static inline void
  event_source__attach(event_source_t *es, event_listener_t *el);
  
#ifndef NDEBUG
static inline void
  event_source__debug(event_source_t *es, event_debugger_t *ed);
#else
#define event_source__debug(es, ed)
#endif /* NDEBUG */

/* Detatch an event listener from the event source. The operation will fail
 * (return false) if the listener is not connected to this source.
 */
 
static inline bool_t
  event_source__detach(event_source_t *es, event_listener_t *el);

static inline event_listener_t *
  event_source__first_listener(event_source_t *es);

/* Dispatch an event from this event source.
 */
 
void
  event_source__dispatch(event_source_t *es, event__value_t value);


/* Inline Function Definitions ---------------------------------------------- */

void event_source__ctor(event_source_t *es)
{
  assert(es != NULL);
  s_list__ctor(&es->_super);
}

void event_source__attach(event_source_t *es, event_listener_t *el)
{
  assert(es != NULL);
  
  s_list__push(&es->_super, (s_list_item_t *) el);
}

#ifndef NDEBUG
void event_source__debug(event_source_t *es, event_debugger_t *ed)
{
  event_source__attach(es, (event_listener_t *) ed);
}
#endif /* NDEBUG */

bool_t event_source__detach(event_source_t *es, event_listener_t *el)
{
  assert(es != NULL);
  return s_list__delete(&es->_super, (s_list_item_t *) el);
}

size_t event_source__listeners(event_source_t const *es)
{
  assert(es != NULL);
  return s_list__length(&es->_super);
}

event_listener_t *event_source__first_listener(event_source_t *es)
{
  assert(es != NULL);
  return (event_listener_t *) s_list__first(&es->_super);
}


#endif /* EVENT_SOURCE_H */