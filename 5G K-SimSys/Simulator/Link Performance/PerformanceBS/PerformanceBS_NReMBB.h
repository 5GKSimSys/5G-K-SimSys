/****************************************************************************

Performance header (NR eMBB)


PROJECT NAME : System Level Simulator
FILE NAME : PerformanceBS_NReMBB.h
DATE : 2017.1.31
VERSION : 0.0
ORGANIZATION : Korea University, Dongguk University

Copyright(C) 2016, by Korea University, Dongguk University, All Rights Reserved

**************************************************************************** /

/*===========================================================================

EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.

when		who				what, where, why
----------	------------	-------------------------------------------------
2017.3.1	Minsig Han    	Created

===========================================================================*/

#ifndef PERFORMANCEBS_H
#define PERFORMANCEBS_H

/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         INCLUDE FILES FOR MODULE                        */
/*                                                                         */
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
	int MUMIMOGroup;

	void Initialize(int bs); // Initialization
	void FERCheckup(int bsID, int link);
	void HARQInformation(int bsID, int link);
	void Measure(int bsID, int link); // Throughput measurement
	void MuMimoMeasure(int bsID);
	void ConcludeIteration(); // Iteration conclusion
	void Conclude(); // Simulation conclusion
};


#endif