/* Event Listener
 *
 * Attached to an event source, the listener will be notified via a registered
 * callback function every time an event is dispached from the source.
 */

#ifndef EVENT_LISTENER_H
#define EVENT_LISTENER_H 1

/* Includes ----------------------------------------------------------------- */

#include <compiler.h>
#include <s_list_item.h>
#include <event/event.h>


/* Constants -------------------------------------+-------------------------- */


/* Data Types --------------------------------------------------------------- */

typedef void (*event_listener__callback_t)(void *listener, event_t *event);

/* Main data structure
 * Size: 2+2+2 = 6 bytes
 */

typedef struct event_listener {
  s_list_item_t              _super;
  void                       *listener;
  event_listener__callback_t  callback;
} event_listener_t;


/* Macros ----------------------------------------+--------+----------------- */




/* Global Variables --------------------------------------------------------- */




/* Public Functions --------------------------------------------------------- */

void
  event_listener__ctor(event_listener_t *el, void *listener,
                       event_listener__callback_t callback);

static inline event_listener_t *
  event_listener__next(event_listener_t *el);

static inline void
  event_listener__call(event_listener_t * const el, event_t *event);


/* Inline Function Definitions ---------------------------------------------- */

/* Access the next event listener attatched to the event source.
 */
 
event_listener_t *event_listener__next(event_listener_t *el)
{
  assert(el != NULL);
  return (event_listener_t *) s_list_item__next(&el->_super);
}

/* Call the callback function registered with the event listener.
 */

void event_listener__call(event_listener_t * const el, event_t *event)
{
  assert(el != NULL);
  el->callback(el->listener, event);
}

#endif /* EVENT_LISTENER_H */
