/****************************************************************************

		Performance Base Station header (Simple)


PROJECT NAME : System Level Simulator
FILE NAME    : PerformanceBS_simple.h
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
2016.10.5	Minjoong Rim 	Created

===========================================================================*/

#ifndef PERFORMANCEBS_H
#define PERFORMANCEBS_H

/*-------------------------------------------------------------------------*/
/*                                                                          */
/*                         INCLUDE FILES FOR MODULE                         */
/*                                                                          */
/*-------------------------------------------------------------------------*/

#include "../../Simulation Top/Global/SystemSimConfiguration.h"


/*-------------------------------------------------------------------------*/
/*                                                                          */
/*                             CLASS DECLARATION                            */
/*                                                                          */
/*-------------------------------------------------------------------------*/

// Performance base station
class PerformanceBS
{
  public:
	int id; // BS ID
	double throughput; // Throughput

	void Initialize(int bs); // Initialization
	void Measure(); // Throughput measurement
	void ConcludeIteration(); // Iteration conclusion
	void Conclude(); // Simulation conclusion
};


#endif