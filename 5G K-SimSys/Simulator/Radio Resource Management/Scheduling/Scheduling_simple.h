/****************************************************************************

		Scheduling header (Simple)


PROJECT NAME : System Level Simulator
FILE NAME    : Scheduling_simple.h
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

#ifndef SCHEDULING_H
#define SCHEDULING_H

/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         INCLUDE FILES FOR MODULE                        */
/*                                                                         */
/*-------------------------------------------------------------------------*/


#include "../../Simulation Top/Global/SystemSimConfiguration.h"


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         ENUM DEFINITION                                 */
/*                                                                         */
/*-------------------------------------------------------------------------*/

// Scheduling traffic model type
enum Scheduling_TrafficModel {
	FullBuffer,
	NonFullBuffer,
	IotTraffic
};

// Scheduling algorithm
enum Scheduling_Algorithm {
	SimpleScheduling,
	RoundRobin,
	BestSINR,
	MaxMin,
	ProportionalFairness
};


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                             CLASS DECLARATION                           */
/*                                                                         */
/*-------------------------------------------------------------------------*/

// Scheduling
class Scheduling
{
  public:
	Scheduling_TrafficModel trafficModel; // Traffic model
	double trafficLoad; // Traffic load (0 ~ 1)
	int dataSize; // Data size (Kbytes) for non-full-buffer
	Scheduling_Algorithm algorithm; // Scheduling algorithm
	int numRB; // # of resource blocks
	int realisticFeedback; // 0: Ideal, 1: Realistic

	void Initialize(string fileName); // Scheduling initialization
	void Feedback(); // MS feedback
	void Schedule(); // Scheduling
	void ConcludeIteration(); // Iteration conclusion
	void Conclude(); // Simulation conclusion
};


#endif