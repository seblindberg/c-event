#include <event/event_debugger.h>

/* Macros ––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––– */



/* Private Functions –––––––––––––––––––––––––––––––––––––––––––––––––––––––– */




/* Global Variables ––––––––––––––––––––––––––––––––––––––––––––––––––––––––– */




/* Function Definitions ––––––––––––––––––––––––––––––––––––––––––––––––––––– */

void event_debugger__ctor(event_debugger_t *ed, const char *label)
{
  event_listener__ctor(&ed->_super, ed,
    (event_listener__callback_t) event_debugger__handler);
  ed->label = label;
}

void event_debugger__handler(event_debugger_t *ed, event_t *event)
{
  printf("-> %s:\n\t", ed->label);
  event__inspect(event);
}

