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
	double RSRP_fBS[12][3];

	void Initialize(int ms);
	void Feedback(int msID, int type);
	void MuMimoFeedback(int msID, int type);
	void ReceivedSINR(int msID, int slotnumber, int type);
	arma::cx_mat* PrecodingMatrix(enum Precoding_Matrix precodingtype, arma::cx_mat *codebook, int type);
	double GetSpectralEfficiency(double SINR, int &MCS);
	void ConcludeIteration(); // Iteration conclusion
	void Conclude(); // Simulation conclusion

	// LAA...
	// Inter-system Interference
	int *InterferenceTimeFromBsForCQI;		// Variable: Inter-system Interference Time for CQI Report (BS->UE)
	int *InterferenceTimeFromUeForCQI;		// Variable: Inter-system Interference Time for CQI Report (UE->UE)
	//int *InterferenceTimeFromApForCQI;		// Variable: Inter-system Interference Time for CQI Report (AP->UE)
	//int *InterferenceTimeFromStaForCQI;		// Variable: Inter-system Interference Time for CQI Report (STA->UE)
	int *InterferenceTimeFromBsForFER;		// Variable: Inter-system Interference Time for FER Check (BS->UE)
	int *InterferenceTimeFromUeForFER;		// Variable: Inter-system Interference Time for FER Check (UE->UE)
	//int *InterferenceTimeFromApForFER;		// Variable: Inter-system Interference Time for FER Check (AP->BS)
	//int *InterferenceTimeFromStaForFER;		// Variable: Inter-system Interference Time for FER Check (STA->BS)
	double *AvgInterferenceFromBsForFER;	// Variable: Inter-system Average Interference for FER Check (BS->UE)
	double *AvgInterferenceFromBsForCQI;	// Variable: Inter-system Average Interference for CQI Report (BS->UE)
	void DynamicInitilize();
	void SinrCalculationForCqiReport(int msID, int type);
	// Resource Allocation & MCS Decision
	int *AllocatedRB;						// State: RB Allocation MAP // 0: No, 1: Yes
	int TotalNumOfAllocatedRB;				// Variable: Total # of Allocated RB
	double PfAverageR;						// Variable: 평균 수율 (PF)
	double InstantR;						// Variable: 현재 TTI에서 처리한 수율
	int TempMCSindex;						// Variable: MCS Decision을 통해 결정된 MCS Index
	double TempSpectralEfficiency;			// Variable: MCS Decision을 통해 결정된 MCS의 SE
	int ModulationOrderDL;					// Variable: Modulation Order of MCS
	// SINR (Pre, Post)
	double ***PreSINR;						// SINR for CQI Report
	double *FerSINR;						// Variable: Post SINR per RB
	double *AvgSinrEESM;					// Variable: Link-to-System SINR Mapping Value according to Modulation Order
	double **SinrOfRbEESM;					// Variable: EESM을 사용했을 때, RB의 SINR 값 according to Modulation Order
	double EffectiveSINR;					// Variable: Final Effective SINR Value for MCS Decision
	// HARQ
	int	HarqProcessID;						// Variable: 현재 수신중인 DL Frame의 HARQ Process ID (8개의 process를 사용함)
	int *HarqReTxNum;						// Variable: # of Retransmission per HARQ Process
	int *HarqMCSindex;						// Variable: 해당 HARQ Process의 MCS Index (Non-adaptive HARQ 기준으로는, 초기 전송 것을 계속 사용)
	double *HarqSpectralEfficiency;			// Variable: 해당 HARQ Process의 MCS의 SE
	double **HarqSINR;						// Variable: SINR per HARQ Process per RB
	double *HarqEffectiveSINR;				// Variable: Combined Effective SINR Value per HARQ Process
	// 기타
	int RealRxMode;							// State: Data Rx Mode // 0: OFF, 1: ON
};


#endif