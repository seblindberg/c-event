/*
 * Run with arguments
 *   -I../include -I../ext/list/include ../lib/event/event.c ../ext/list/lib/s_list_item.c ../lib/event/event_listener.c
 */

#include <compiler.h>
#include <event/event.h>
#include <event/event_listener.h>

// #include "helper.h"

static void *callback_listener;
static event_t *callback_event;

static void event_listener_callback(void *listener, event_t *event)
{
  callback_listener = listener;
  callback_event    = event;
  
  event__inspect(event);
}

void test__create(void)
{
  event_listener_t el;
  uint_fast8_t object;
  event_t event;
  
  event__ctor(&event, test__create, 42);
  
  event_listener__ctor(&el, (void *) &object, event_listener_callback);
  
  assert(event_listener__next(&el) == NULL);
}

void test__call(void)
{
  event_listener_t el;
  uint_fast8_t     listener;
  uint_fast8_t     source;
  event_t          event;
  
  event_listener__ctor(&el, &listener, event_listener_callback);

  event__ctor(&event, &source, 42);

  /* Call the event listener. */
  event_listener__call(&el, &event);

  assert(callback_listener == &listener);
  assert(callback_event == &event);
}

int main(int argc, char *argv[])
{
  test__create();
  test__call();
  
  return 0;
}
