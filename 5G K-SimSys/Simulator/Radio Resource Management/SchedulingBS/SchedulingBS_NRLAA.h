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
	arma::uvec scheduledMS; // Scheduled MS
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
	
	void FrequencyChannelInterferenceTimeFromBsForCQI(int msID);
	void Feedback(int msID);
	void MuMimoFeedback(int msID, int type);
	void ReceivedSINR(int msID, int link, int slotnumber);
	arma::cx_mat* PrecodingMatrix(enum Precoding_Matrix precodingtype, arma::cx_mat *codebook);
	double GetSpectralEfficiency(double SINR, int &MCS);
	void ConcludeIteration(); // Iteration conclusion
	void Conclude(); // Simulation conclusion

	// LAA...
	int *DIFS_on;						// State: DIFS period // 0: off, 1: on
	int *ECCA_on;						// State: ECCA period // 0: off, 1: on
	int *ECCA_count_CCA;				// Variable: Number of remaining CCA slots (Random back-off counter)
	int *ECCA_count_time;				// Variable: CCA slot duration (count down from 9us)
	double *ECCA_criteria;				// Variable: Detected Energy in a CCA slot (linear scale)
	int *Transmission_on;				// State: Transmission period // 0: off, 1: on
	int *Transmit_total_time;			// Variable: COT // us단위
	int Subband_LBT_Mode;				// Indicator: Subband vs. Wideband-LBT // 0: Initial value, 1: 20MHz Subband-LBT, 2: 40MHz Wideband-LBT, 3: 80MHz Wideband-LBT
	int *Subband_LBT_Try;				// State: Subband 별로 LBT를 시도할 지의 여부	// 0: 시도 안함, 1: 시도 함
	int *Subband_Take_Channel;			// State: Subband 별로 채널 획득에 성공했는지의 여부	// 0: 실패, 1: 성공
	int *Transmission_on_sum;

	int LBT_step;
	int res_Td;
	int tf;
	int res_mp;
	int ECCA_slot_size;
	int CtDecre;
	double exp_bo_num;


	// priority_class
	int p_class;
	int mp;
	int LBT_q;
	double exp_bo_num_max;
	int LTEU_Transmit_block;			// Variable: MCOT = Number of TTI


	// error;
	int error;
	int error_sum;
	int error_tot;

	int MAC_time;


	int ECCA_count_ava;
	double sensing_time;
	double *RSRP_fBS;
	double LBT_thereshold;

	int DL_Traffic_Existence;			// State: DL traffic in buffer // 0: No, 1: Yes
	int UL_Traffic_Existence;			// State: DL traffic in buffer // 0: No, 1: Yes
	int *reservation;					// State: Initial signal TX // 0: off, 1: on
	int *jamming_start_time;			// Variable: Initial signal start time
	int *jamming_end_time;				// Variable: Initial signal end time
	int *fake_LTEU_transmit_block_size;	// Variable: COT = Actual number of TTI
	int *Max_DL_Subframe_Num;			// Variable: Number of DL TTI in COT
	int *Max_UL_Subframe_Num;			// Variable: Number of UL TTI in COT
	int *DL_Subframe;					// State: DL data transmission period // 0: off, 1: on
	int *UL_Subframe;					// State: UL data transmission period // 0: off, 1: on
	int **Transmit_start_time;			// Variable: Start time of each TTI
	int **Transmit_end_time;			// Variable: End time of each TTI
	int Transmit_current_fr;			// Variable: Number of currently transmitted TTI
	int Not_alloc_count;				// Variable: Number of not allocated TTI
	int *real_tx_on;					// State: Real transmission period // 0: No, 1: Yes
	int p_cqi_report;					// State: CQI Report Condition // 0: off, 1: on
	int *InterferenceTimeFromBsForCQI;		// Variable: Inter-system Interference Time for CQI Report (BS->BS)
	int *InterferenceTimeFromUeForCQI;		// Variable: Inter-system Interference Time for CQI Report (UE->BS)
	int *InterferenceTimeFromApForCQI;		// Variable: Inter-system Interference Time for CQI Report (AP->BS)
	int *InterferenceTimeFromStaForCQI;		// Variable: Inter-system Interference Time for CQI Report (STA->BS)
	int *InterferenceTimeFromBsForFER;		// Variable: Inter-system Interference Time for FER Check (BS->BS)
	int *InterferenceTimeFromUeForFER;		// Variable: Inter-system Interference Time for FER Check (UE->BS)
	int *InterferenceTimeFromApForFER;		// Variable: Inter-system Interference Time for FER Check (AP->BS)
	int *InterferenceTimeFromStaForFER;		// Variable: Inter-system Interference Time for FER Check (STA->BS)
	int HarqProcessID;						// Variable: 현재 전송중인 Frame의 HARQ Process ID (8개의 process를 사용함)

	void DynamicInitilize();						// Dynamic Memory Allocation and Initialization
	void CqiReportCondition(int bsID);				// DL CQI Report Condition Check
	void PreSinrCalculation(int bsID);				// SINR Calculation for CQI Report (Before Resource Allocation)
	void WiderBwOperation(int bsID);				// Subband vs. Wideband decision 
	void Transmission_Decision(int bsID);			// Initial signal, Data Frame Transmit Timing Decision
	void TddConfiguration(int bsID);				// DL, UL Configuration Decision
	void BsOperationStart(int bsID);				// BS Start Operation
	void ISITinitializationForFER(int bsID);		// Inter-system Interference Time Initialization for FER // Inter-BS
	void SchedulingDL(int bsID);					// DL resource allocation for UE
	void McsAssignDL(int bsID);						// DL MCS Assign for UE
};


#endif