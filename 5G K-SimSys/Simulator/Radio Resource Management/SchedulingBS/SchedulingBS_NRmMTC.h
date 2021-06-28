/****************************************************************************

Scheduling header (NR mMTC)


PROJECT NAME : System Level Simulator
FILE NAME    : Scheduling_NRmMTC.h
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

typedef struct {


} MuMimo_Schedule_Parameter;

// Scheduling Base Station
class SchedulingBS
{
public:
	int id; // BS ID
	int scheduledMS; // Scheduled MS
	int numScheduledMS;


	double downlinkBuffer;
	double uplinkBuffer;
	arma::cx_mat precodingMatrix;
	MuMimo_Schedule_Parameter MuMimoScheduleParameter;
	arma::vec framestructure;
	void Initialize(int bs);
	void FrameStructure(int bsID, SLS::TDDType tddtype);
	void Schedule(int bsID);
	void MuMimoSchedule(int bsID, int subband, arma::uvec scheduluedMS, int link);
	void printCombination(arma::uvec arr, arma::uvec groupMetric, double value, int n, int r, int link);
	void combinationUtil(arma::uvec arr, arma::uvec data, arma::uvec groupMetric, double value, int start, int end, int index, int r, int link);
	void Feedback(int msID);
	void MuMimoFeedback(int msID, int type);
	void ReceivedSINR(int msID, int link, int slotnumber);
	arma::cx_mat* PrecodingMatrix(enum Precoding_Matrix precodingtype, arma::cx_mat *codebook);
	double GetSpectralEfficiency(double SINR, int &MCS);
	void ConcludeIteration(); // Iteration conclusion
	void Conclude(); // Simulation conclusion
};


#endif