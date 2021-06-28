/****************************************************************************

Link Level Simulation PerformanceBS (simpleLink)


PROJECT NAME : System Level Simulator High Level Design
FILE NAME    : PerformanceBS_simpleLink.h
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

#ifndef PERFORMANCEBS_H
#define PERFORMANCEBS_H

#include "../../Link Level Simulation/Simulation Top/Global/LinkSim_simple.h"
#include "../../Link Level Simulation/Simulation Top/Network Element/LinkNode_simple.h"
#include "../../Link Level Simulation/Simulation Top/Network Element/LinkChannel_simple.h"


class PerformanceBS
{
public:

    int id; // BS ID
    class LinkNode* link; // Link level simulation data and parameters

    void Initialize(int bs); // Initialization
    void InitializeIteration(); // Iteration initialization
    void ConcludeIteration(); // Iteration conclusion
    void Conclude(); // Simulation conclusion*/
};

#endif