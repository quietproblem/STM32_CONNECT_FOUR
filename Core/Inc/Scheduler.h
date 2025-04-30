#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include <stdint.h>

#define APP_DELAY_FLAG_EVENT (1 << 0)
#define DROP_CHIP_EVENT (1<<1)
#define RESTART_GAME_EVENT (1<<2)

uint32_t getScheduledEvents ();
void addScheduleEvent (uint32_t event);
void removeSchedulerEvent (uint32_t event);



#endif /* SCHEDULER_H_ */
