/****************************************************************************

Scheduling header (FD MIMO)


PROJECT NAME : System Level Simulator
FILE NAME    : Scheduling_NRLAA.h
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
2017.1.20   Minsig Han      Created

===========================================================================*/

#ifndef SCHEDULING_H
#define SCHEDULING_H

/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         INCLUDE FILES FOR MODULE                        */
/*                                                                         */
/*-------------------------------------------------------------------------*/


#include "../../Simulation Top/Global/SystemSimConfiguration.h"
using namespace std;

/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         ENUM DEFINITION                                 */
/*                                                                         */
/*-------------------------------------------------------------------------*/

// Scheduling traffic model type

namespace RRM {
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

	/*enum Precoding_Matrix{
		Analogbeamforming,
		Digitalbeamforming
	};*/
}

enum Precoding_Matrix {
	Analogbeamforming,
	Digitalbeamforming
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
	int checkNetworkParameter;
	enum RRM::Scheduling_TrafficModel trafficModel; // Traffic model
	enum RRM::Scheduling_Algorithm algorithm; // Scheduling algorithm
	int numMaxLayer;
	int numRB; // # of resource blocks
	int realisticFeedback; // 0: Ideal, 1: Realistic	
	int realisticChannelEstimation; // 0: Ideal, 1: Realistic
	double dataSize;

	void Initialize(string fileName); // Scheduling initialization
	void FrameStructure(SLS::TDDType tddtype); // MS feedback
	void Feedback(); // MS feedback
	void Schedule(); // Scheduling
	void ReceivedSINRCalculation();
	void Conclude(); // Simulation conclusion
	
					 
	
	void ConcludeIteration(); // Iteration conclusion 	

	// LAA...
	int numSubband=1;	// # of Subband
	double FFTSize; // FFT size for whole band
	void ListenBeforeTalk();							// Whole LBT Procedures							// 
	void LbtCategory();									// LBT Operation based on LBT Category			// Inter-BS Operation
	void DLLBT_simple();								// 기본 LBT 동작 (Test 위해)					// Inter-BS Operation
	void ISITcalculation();
	void DLLBT_new();
	void DCFforWiFiBS();
	void DCFforWiFiMS();
	// Inter-system Interference Time Calculation	// Inter-BS Operation
	double EESM(double SINR, int ModOrder);				// Link-to-System SINR Mapping
	double EESMdemapping(double SINR, int ModOrder);	// Link-to-System SINR Demapping
	double MCSdecision(double SINRdB_QPSK, double SINRdB_16QAM, double SINRdB_64QAM, int &MCSindex, double &SINRfinal);	// MCS Decision
	void StartAction();

	int DIFS;
	int SIFS;

};


#endif