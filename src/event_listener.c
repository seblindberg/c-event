#include <event/event_listener.h>

/* Macros ------------------------------------------------------------------- */



/* Private Functions -------------------------------------------------------- */




/* Global Variables --------------------------------------------------------- */




/* Function Definitions ----------------------------------------------------- */

void event_listener__ctor(event_listener_t *el, void *listener,
                          event_listener__callback_t callback)
{
  assert(el != NULL);
  assert(callback != NULL);
  
  s_list_item__ctor(&el->_super);
  
  el->listener = listener;
  el->callback = callback;
}
