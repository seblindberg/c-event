/*
 * Run with arguments
 *   -I../include -I../ext/list/include ../ext/list/lib/s_list_item.c ../ext/list/lib/s_list.c ../lib/event/event.c ../lib/event/event_listener.c ../lib/event/event_debugger.c ../lib/event/event_source.c
 */

#include <compiler.h>

#include <event/event.h>
#include <event/event_listener.h>
#include <event/event_debugger.h>
#include <event/event_source.h>

#include "helper.h"

void test__create(void)
{
  event_source_t event_source;
  event_source__ctor(&event_source);
  
  assert(event_source__listeners(&event_source) == 0);
}

void test__attatch(void)
{
  event_source_t   *es = helper__event_source();
  event_listener_t *el = helper__event_listener();
  
  event_source__attach(es, el);
  
  assert(event_source__listeners(es) == 1);
}

void test__detatch(void)
{
  event_source_t   *es = helper__event_source();
  event_listener_t *el = helper__event_listener();
                      
  assert(event_source__detach(es, el) == 0);
    
  event_source__attach(es, el);
  
  assert(event_source__detach(es, el) != 0);
  assert(event_source__listeners(es) == 0);
}

void test__dispatch(void)
{
  event_source_t   *es = helper__event_source();
  event_listener_t *el = helper__event_listener();
  
  event__value_t const value = 0xBEEF;
  
  /* Should not cause any problems */
  event_source__dispatch(es, value);
  assert(event__value(helper__last_received_event()) != value);
  
  /* Attatch a listener and repeat the dispatch */
  event_source__attach(es, el);
  
  event_source__dispatch(es, value);
  assert(event__value(helper__last_received_event()) == value);
  assert(helper__last_received_listener() == el);
  
  /* Detach, and the listener should no longer be called */
  event_source__detach(es, el);
  event_source__dispatch(es, value + 1);
  
  assert(event__value(helper__last_received_event()) == value);
}

void test__debug()
{
  event_source_t  *es = helper__event_source();
  event_debugger_t ed;
  
  event_debugger__ctor(&ed, "Test Debug");
  event_source__debug(es, &ed);
  
  event_source__dispatch(es, 42);
}

int main(int argc, char *argv[])
{
  test__create();
  test__attatch();
  test__detatch();
  test__dispatch();
  test__debug();
  
  return 0;
}
