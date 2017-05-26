/*
 * Run with arguments
 *   -I../include ../lib/event/event.c
 */

#include <compiler.h>
#include <event/event.h>

//#include "helper.h"

void test__create(void)
{
  event_t event;
  event__ctor(&event, NULL, 0xDEAD);
  
  assert(event__value(&event) == 0xDEAD);
  assert(event__source(&event) == NULL);
  
  //printf("%4X\n", event__value(&event));
}

int main(int argc, char *argv[])
{
  test__create();

  return 0;
}
