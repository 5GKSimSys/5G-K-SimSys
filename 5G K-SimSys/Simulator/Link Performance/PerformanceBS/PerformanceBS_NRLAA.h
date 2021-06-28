/****************************************************************************

Performance header (FD MIMO)


PROJECT NAME : System Level Simulator
FILE NAME : PerformanceBS_FD MIMO.h
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
	void Measure(int bsID, int link); // Throughput measurement
	void MuMimoMeasure(int bsID);
	void ConcludeIteration(); // Iteration conclusion
	void Conclude(); // Simulation conclusion

	// LAA...
	void BsOperationEnd(int bsID);			// BS End Operation
	void PostSinrCalculation(int bsID);		// SINR Calculation for FER Check-up (After Packet Reception)
	void FerCheckDL(int bsID);				// DL FER Check		
	void BsEndAction(int bsID);				// DL End Action

	double FER(double SINR, int MCS);
};


#endif