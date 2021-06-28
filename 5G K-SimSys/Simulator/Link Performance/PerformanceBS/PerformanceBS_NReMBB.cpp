/****************************************************************************

Performance for Base Station(NR eMBB)


PROJECT NAME : System Level Simulator
FILE NAME    : PerformanceBS_NReMBB.cpp
DATE         : 2017.3.1
VERSION      : 0.0
ORGANIZATION : Korea University, Dongguk University

Copyright (C) 2016, by Korea University, Dongguk University, All Rights Reserved

****************************************************************************/

/*===========================================================================

EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.

when		who				what, where, why
----------	------------	-------------------------------------------------
2017.3.1	Minsig Han     	Created

===========================================================================*/



/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         INCLUDE FILES FOR MODULE                        */
/*                                                                         */
/*-------------------------------------------------------------------------*/

#include "PerformanceBS_NReMBB.h"



/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         METHOD                                          */
/*                                                                         */
/*-------------------------------------------------------------------------*/

void PerformanceBS::Initialize(int bs)
{
	id = bs; // BS ID
}

double FER(double SINR, int MCS)
{
	double Frame_Error_Rate = 1;
	double ESINR_L = SINR; //둘다 리니어 값
	switch (MCS)
	{
	case -1: //2015.11.24
		Frame_Error_Rate = 0.0;
		break;

	case 0:
		if (ESINR_L < pow(10.0, -7.737 / 10.0))
			Frame_Error_Rate = 1.0;
		else
			Frame_Error_Rate = exp(69.109 - 410.4 * ESINR_L);
		break;
	case 1:
		if (ESINR_L < pow(10.0, -5.852 / 10.0))
			Frame_Error_Rate = 1.0;
		else
			Frame_Error_Rate = exp(70.072 - 269.63 * ESINR_L);

		break;

	case 2:
		if (ESINR_L < pow(10.0, -3.737 / 10.0))
			Frame_Error_Rate = 1.0;
		else
			Frame_Error_Rate = exp(69.19 - 163.42 * ESINR_L);

		break;

	case 3:
		if (ESINR_L < pow(10.0, -1.718 / 10.0))
			Frame_Error_Rate = 1.0;
		else
			Frame_Error_Rate = exp(70.491 - 104.69 * ESINR_L);

		break;

	case 4:
		if (ESINR_L < pow(10.0, 0.3206 / 10.0))
			Frame_Error_Rate = 1.0;
		else
			Frame_Error_Rate = exp(77.142 - 71.651* ESINR_L);

		break;

	case 5:
		if (ESINR_L < pow(10.0, 2.14 / 10.0))
			Frame_Error_Rate = 1.0;
		else
			Frame_Error_Rate = exp(47.496 - 29.018 * ESINR_L);

		break;

	case 6:
		if (ESINR_L < pow(10.0, 4.096 / 10.0))
			Frame_Error_Rate = 1.0;
		else
			Frame_Error_Rate = exp(45.163 - 17.585 * ESINR_L);

		break;

	case 7:
		if (ESINR_L < pow(10.0, 6.052 / 10.0))
			Frame_Error_Rate = 1.0;
		else
			Frame_Error_Rate = exp(45.936 - 11.402 * ESINR_L);

		break;

	case 8:
		if (ESINR_L < pow(10.0, 8.03 / 10.0))
			Frame_Error_Rate = 1.0;
		else
			Frame_Error_Rate = exp(44.625 - 7.0239 * ESINR_L);

		break;

	case 9:
		if (ESINR_L < pow(10.0, 10.03 / 10.0))
			Frame_Error_Rate = 1.0;
		else
			Frame_Error_Rate = exp(46.766 - 4.6398 * ESINR_L);

		break;

	case 10:
		if (ESINR_L < pow(10.0, 11.82 / 10.0))
			Frame_Error_Rate = 1.0;
		else
			Frame_Error_Rate = exp(41.834 - 2.7525 * ESINR_L);

		break;
	case 11:
		if (ESINR_L < pow(10.0, 13.65 / 10.0))
			Frame_Error_Rate = 1.0;
		else
			Frame_Error_Rate = exp(33.542 - 1.4485 * ESINR_L);

		break;
	case 12:
		if (ESINR_L < pow(10.0, 15.69 / 10.0))
			Frame_Error_Rate = 1.0;
		else
			Frame_Error_Rate = exp(29.392 - 0.79247 * ESINR_L);

		break;
	case 13:
		if (ESINR_L < pow(10.0, 17.5 / 10.0))
			Frame_Error_Rate = 1.0;
		else
			Frame_Error_Rate = exp(29.525 - 0.52504 * ESINR_L);

		break;
	case 14:
		if (ESINR_L < pow(10.0, 18.98 / 10.0))
			Frame_Error_Rate = 1.0;
		else
			Frame_Error_Rate = exp(8.154 - 0.10315 * ESINR_L);

		break;
	}
	return Frame_Error_Rate;
}

void PerformanceBS::FERCheckup(int bsID, int link)
{
	arma::cx_mat tempM, tempRI, tempIRC, temph, signal, interferencePlusNoise;

	double FERvalue, randomFERvalue;
	double noise = pow(10, (-174.0 / 10.0)) * Sim.channel->NReMBB.bandwidth * 1e6 / 1000;
	int siIndex;
	arma::vec FrequencySinr(Sim.channel->NReMBB.bandwidth / 10 * 50), temps;

	if (BS[bsID]->channel->NumAssociatedMS > 0)
	{
		BS[bsID]->performance->MUMIMOGroup = arma::size(BS[bsID]->scheduling->scheduledMS)(0);
		for (int i = 0; i < arma::size(BS[bsID]->scheduling->scheduledMS)(0); i++)
		{
			int msID = BS[bsID]->scheduling->scheduledMS(i);

			randomFERvalue = arma::randu();
			if (link == 0)
				FERvalue = FER(MS[msID]->scheduling->downlinkESINR, MS[msID]->scheduling->MCS);
			else
				FERvalue = FER(MS[msID]->scheduling->uplinkESINR, MS[msID]->scheduling->MCS);

		}

	}

}

void PerformanceBS::HARQInformation(int bsID, int link)
{
	if (BS[bsID]->channel->NumAssociatedMS > 0)
	{
		int temp = 0;
		BS[bsID]->scheduling->HARQscheduledMS.zeros(BS[bsID]->channel->NumAssociatedMS);
		for (int i = 0; i < BS[bsID]->scheduling->numScheduledMS; i++)
		{
			if (arma::randu() < FER(MS[BS[bsID]->scheduling->scheduledMS(i)]->scheduling->downlinkESINR, MS[BS[bsID]->scheduling->scheduledMS(i)]->scheduling->MCS))
			{
				BS[bsID]->scheduling->HARQscheduledMS[temp] = BS[bsID]->scheduling->scheduledMS(i);
				temp++;
			}
		}
	}	

}

void PerformanceBS::Measure(int bsID, int link)
{
	if (BS[id]->channel->NumAssociatedMS != 0)
	{
		for (int i = 0; i < arma::size(BS[bsID]->scheduling->scheduledMS)(0); i++)
			MS[BS[id]->scheduling->scheduledMS(i)]->performance->Measure(link);
	}
	
}

void PerformanceBS::MuMimoMeasure(int bsID)
{
	


}

void PerformanceBS::ConcludeIteration() {

}

void PerformanceBS::Conclude() {

}
