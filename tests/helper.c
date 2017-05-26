#include "helper.h"

/* Macros ------------------------------------------------------------------- */



/* Private Functions -------------------------------------------------------- */

void
  event_listener_callback(void *listener, event_t *event);


/* Global Variables --------------------------------------------------------- */

static event_t       event_queue_buffer[4];
static event_t       received_event;
static void         *received_listener;

/* Function Definitions ----------------------------------------------------- */


event_listener_t *helper__event_listener()
{
  static event_listener_t event_listener;

  event_listener__ctor(&event_listener, &event_listener, event_listener_callback);

  received_listener = NULL;
  event__ctor(&received_event, NULL, 0);

  return &event_listener;
}

void *helper__last_received_listener()
{
  return received_listener;
}

event_t *helper__last_received_event()
{
  return &received_event;
}

event_queue_t *helper__event_queue()
{
  static event_queue_t event_queue;
  
  event_queue__ctor(&event_queue, event_queue_buffer,
                    sizeof(event_queue_buffer) >> 1);

  return &event_queue;
}

event_source_t *helper__event_source()
{
  static event_source_t event_source;

  event_source__ctor(&event_source);

  return &event_source;
}

// event_listener_t *helper__event_listener()
// {
//   return NULL;
// }
//
// event_t *helper__event(event__value_t value)
// {
//   static event_t event;
//
//   event__ctor(&event, NULL, value);
//
//   return &event;
// }
//
// event_source_t *helper__event_source(void)
// {
//   static event_source_t event_source;
//   event_source__ctor(&event_source);
//
//   return &event_source;
// }

void event_listener_callback(void *listener, event_t *event)
{
  received_listener = listener;
  memcpy(&received_event, event, sizeof(event_t));
}
