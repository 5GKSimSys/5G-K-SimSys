/****************************************************************************

Scheduling header (NR eMBB)


PROJECT NAME : System Level Simulator
FILE NAME    : Scheduling_NReMBB.h
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
2017.3.1    Minsig Han      Created

===========================================================================*/

#ifndef SCHEDULINGMS_H
#define SCHEDULINGMS_H

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

typedef struct {


} MuMimo_Feedback_Parameter;

// Scheduling Mobile Station
class SchedulingMS
{
public:
	int id; // MS ID
	int interArrivalTime; // inter arrival time for non-full buffer traffic
	double msBuffer; // MS buffer for non-full buffer traffic
	int dataSize; // Data size per traffic
	int MCS;
	double downlinkaveragedThroghput, uplinkaveragedThroghput;
	double downlinkspectralEfficiency, uplinkspectralEfficiency;
	double averageUserPerceviedThroughput;
	double downlinkBuffer;
	double uplinkBuffer;
	arma::cx_mat analogPrecodingMatrix;
	arma::cx_mat digitalPrecodingMatrix;
	double CQI;
	double downlinkESINRdB, uplinkESINRdB;
	double downlinkESINR, uplinkESINR;
	double downlinkHARQeSINR, uplinkHARQeSINR;

	void Initialize(int ms);
	void BufferUpdate();
	void Feedback(int msID);
	void MuMimoFeedback(int msID, int type);
	void ReceivedSINR(int msID, int slotnumber, int type);
	arma::cx_mat* Beamforming(enum Precoding_Matrix precodingtype, arma::cx_mat *codebook, int type);
	double GetSpectralEfficiency(double SINR, int &MCS);
	void ConcludeIteration(); // Iteration conclusion
	void Conclude(); // Simulation conclusion
};


#endif