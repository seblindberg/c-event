#ifndef HELPER_H
#define HELPER_H 1

/* Includes ----------------------------------------------------------------- */

#include <compiler.h>
#include <event.h>


/* Constants -------------------------------------+-------------------------- */



/* Data Types --------------------------------------------------------------- */




/* Global Variables --------------------------------------------------------- */




/* Public Functions --------------------------------------------------------- */

event_listener_t *
  helper__event_listener();
  
void *
  helper__last_received_listener();
  
event_t *
  helper__last_received_event();

event_queue_t *
  helper__event_queue(void);

event_source_t *
  helper__event_source(void);

// event_listener_t *
//   helper__event_listener(void);
//
// event_t *
//   helper__event(event__value_t value);
//
// event_source_t *
//   helper__event_source(void);


/* Macros ----------------------------------------+--------+----------------- */




/* Inline Function Definitions ---------------------------------------------- */



#endif /* HELPER_H */