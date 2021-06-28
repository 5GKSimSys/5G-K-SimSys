/****************************************************************************

Performance header (FD MIMO)


PROJECT NAME : System Level Simulator
FILE NAME : PerformanceMS_FD MIMO.h
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

#ifndef PERFORMANCEMS_H
#define PERFORMANCEMS_H

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

// Performance mobile station
class PerformanceMS
{
public:
	int id; // MS ID
	double uplinkThroghput; // Throughput
	double downlinkThroghput;
	double instantThroughput;
	double receivedSinr;

	void Initialize(int ms); // Initialization
	void Measure(); // Throughput measurement
	void ConcludeIteration(); // Iteration conclusion
	void Conclude(); // Simulation conclusion

	// LAA...
	void ISIPcalculationForFerCheck(int msID, int type);
	void SINRCalculationForFerCheck(int msID, int type);
	arma::cx_mat* PrecodingMatrix(enum Precoding_Matrix precodingtype, arma::cx_mat *codebook, int type);
};


#endif