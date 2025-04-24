#include "Scheduler.h"

uint32_t scheduledEvents;



uint32_t getScheduledEvents ()
{
	return scheduledEvents;
}
void addScheduleEvent (uint32_t event)
{
	scheduledEvents|=event;
}
void removeSchedulerEvent (uint32_t event)
{
	scheduledEvents&=~(event);
}


