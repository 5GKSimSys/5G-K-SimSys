/****************************************************************************

		Scheduling Base Station header (Simple)


PROJECT NAME : System Level Simulator
FILE NAME    : SchedulingBS_simple.h
DATE         : 2016.10.5
VERSION      : 0.0
ORGANIZATION : Korea University, Dongguk University

Copyright (C) 2016, by Korea University, Dongguk University, All Rights Reserved

****************************************************************************/

/*===========================================================================

EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.

when		who				what, where, why
----------	------------	-------------------------------------------------
2016.10.5	Minjoong Rim	Created

===========================================================================*/

#ifndef SCHEDULINGBS_H
#define SCHEDULINGBS_H

/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         INCLUDE FILES FOR MODULE                        */
/*                                                                         */
/*-------------------------------------------------------------------------*/

#include "../../Simulation Top/Global/SystemSimConfiguration.h"


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                             CLASS DECLARATION                           */
/*                                                                         */
/*-------------------------------------------------------------------------*/

// Scheduling Base Station
class SchedulingBS
{
  public:
	int id; // BS ID
	int scheduledMS; // Scheduled MS

	void Initialize(int bs);
	void Schedule();
	void ConcludeIteration(); // Iteration conclusion
	void Conclude(); // Simulation conclusion
};


#endif