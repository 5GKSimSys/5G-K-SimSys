/****************************************************************************

Performance header (NR mMTC)


PROJECT NAME : System Level Simulator
FILE NAME : PerformanceBS_NRmMTC.h
DATE : 2017.1.31
VERSION : 0.0
ORGANIZATION : Korea University, Dongguk University

Copyright(C) 2016, by Korea University, Dongguk University, All Rights Reserved

****************************************************************************/

/*===========================================================================

EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.

when		who				what, where, why
----------	------------	-------------------------------------------------
2017.3.1	Minsig Han    	Created

===========================================================================*/

#ifndef PERFORMANCE_H
#define PERFORMANCE_H

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

// Performance
class Performance
{
public:
	int checkPerformanceParameter;
	int realisticChannelEstimation; // 0: Ideal, 1: Realistic
	double throughput; // Throughput
	double targetConnectionDensity;
	double connectionDensity;

	double FER(double SINR, int MCS);
	void Initialize(string fileName); // Initialization
	void Conclude(); // Simulation conclusion
	void Measure(); // Throughput measurement
	void ConcludeIteration(); // Iteration conclusion 


};


#endif