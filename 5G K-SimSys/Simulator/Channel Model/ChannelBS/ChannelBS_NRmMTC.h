/****************************************************************************

Channel Model for Base Station header (NR mMTC)


PROJECT NAME : System Level Simulator High Level Design
FILE NAME    : ChannelBS_NRmMTC.h
DATE         : 2017.02.01
VERSION      : 0.11
ORGANIZATION : Korea University, Dongguk University

Copyright (C) 2016, by Korea University, Dongguk University, All Rights Reserved

****************************************************************************/

/*===========================================================================

EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.

when		who				what, where, why
----------	------------	-------------------------------------------------
2017.2.01	Minsig Han     	Created

===========================================================================*/

#ifndef CHANNELBS_H
#define CHANNELBS_H

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
	double carrierFrequency; // Carrier frequency (GHz)
	double bandwidth; // Bandwidth (MHz)
	double txPower; // TX power (dBm)
	double noiseFigure; // Noise figure (dB)
	double antennaGain; // Antenna gain (dBi)
	class Antenna *antenna; // Antenna parameters
	enum Channel_Model model; // Channel model
} Channel_Parameters;


// Channel base station parameter
class ChannelBS
{
public:
	int id; // BS ID
	int site; // Site
	int sector; // Sector number
	int NumAssociatedMS;
	int NumAssociatedUMS;
	class LargeScaleChannel *correlation; // Large scale channel
	Channel_Parameters param; // 
	int numVerticalAntenna;
	arma::vec AnalogBeamPhase;
	arma::vec DigitalBeamPhase;
	arma::vec BeamAmplitude;

	void Initialize(int bs, int site, int sector); // Initialization
												   //	void ConcludeIteration(); // Iteration conclusion
												   //	void Conclude(); // Simulation conclusion
};

#endif