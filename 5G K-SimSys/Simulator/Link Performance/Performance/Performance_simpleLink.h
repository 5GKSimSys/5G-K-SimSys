/****************************************************************************

Link Level Simulation Performance (simpleLink)


PROJECT NAME : System Level Simulator High Level Design
FILE NAME    : Performance_simpleLink.h
DATE         : 2016.11.5
VERSION      : 0.11
ORGANIZATION : Korea University, Dongguk University

Copyright (C) 2016, by Korea University, Dongguk University, All Rights Reserved

****************************************************************************/

/*===========================================================================

EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

when		who				what, where, why
----------	------------	-------------------------------------------------
2016.11.5	Minjoong Rim 	Created

===========================================================================*/

#ifndef PERFORMANCE_H
#define PERFORMANCE_H

#include "../../Simulation Top/Global/SystemSimConfiguration.h"
#include "../../Link Level Simulation/Simulation Top/Global/LinkSim_simple.h"
#include "../../Link Level Simulation/Simulation Top/Network Element/LinkNode_simple.h"
#include "../../Link Level Simulation/Simulation Top/Network Element/LinkChannel_simple.h"

class Performance
{
public:

	double throughput; // Throughput
	class LinkNode* Link; // Link level simulation data and parameters

	void Initialize(string fileName); // Initialization
	void InitializeIteration(); // Iteration initialization
	void Measure(); // FER measurement
	void ConcludeIteration(); // Iteration conclusion
	void Conclude(); // Simulation conclusion*/
};

#endif