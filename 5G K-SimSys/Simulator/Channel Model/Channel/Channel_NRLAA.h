/****************************************************************************

Channel model header (FD MIMO)


PROJECT NAME : System Level Simulator High Level Design
FILE NAME    : Channel_NRLAA.h
DATE         : 2016.01.26
VERSION      :
ORGANIZATION : Korea University, Dongguk University

Copyright (C) 2016, by Korea University, Dongguk University, All Rights Reserved

****************************************************************************/

/*===========================================================================

EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.

when		who				what, where, why
----------	------------	-------------------------------------------------
2017.1.20  Minsig Han      Created

===========================================================================*/

#ifndef CHANNEL_H
#define CHANNEL_H

/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         INCLUDE FILES FOR MODULE                        */
/*                                                                         */
/*-------------------------------------------------------------------------*/

#include "../../Simulation Top/Global/SystemSimConfiguration.h"


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         ENUM DEFINITION                                 */
/*                                                                         */
/*-------------------------------------------------------------------------*/

// Channel model
namespace CHANNEL {
	
	enum Antenna_Model {
		UniformLinearArray,
		CrossPolarization
	};

	enum Interference_Type {
		OtherCellInterference,
		CrossLinkInterference
	};
}


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                           TYPE DEFINITION                               */
/*                                                                         */
/*-------------------------------------------------------------------------*/

// Channel parameter
typedef struct {
	double carrierFrequency; // Carrier frequency (GHz)
	double bandwidth; // Bandwidth (MHz)
	double txPower; // TX power (dBm)
	double rxPower; // RX power (dBm)
	double noiseFigure; // Noise figure (dB)
	double carrierFrequencyOfSmallCell; // Carrier frequency (GHz)
	double bandwidthOfSmallCell; // Bandwidth (MHz)
	double txPowerOfSmallCell; // TX power (dBm)
	double rxPowerOfSmallCell; // RX power (dBm)
	double noiseFigureOfSmallCell; // Noise figure (dB)
} Channel_Parameter;

/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                             CLASS DECLARATION                           */
/*                                                                         */
/*-------------------------------------------------------------------------*/

// Channel
class Channel
{
public:
	enum SLS::Scenario ChannelModel; // Traffic model
	enum CHANNEL::Antenna_Model MsAntennaModel; // Traffic model
	enum CHANNEL::Antenna_Model BsAntennaModel; // Traffic model
	
	Channel_Parameter NReMBB; // FD MIMO channel parameter
	CHANNEL::Antenna_Model AntennaConfiguration;
	
	int AntennaTilting;
	int PolarizedAntennaModel; 
	int NumberOfBS;
	int NumberOfChannelProcess;
	int numberOfTxVerticalAntenna;
	int NumberOfTxHorizontalAntenna;
	int numberOfTxVerticalPanel;
	int NumberOfTxHorizontalPanel;
	int NumberOfTransmitAntennaPort;
	double TxVerticalAntennaDistance;
	double TxHorizontalAntennaDistance;
	double TxVerticalPanelDistance;
	double TxHorizontalPanelDistance;
	int numberOfRxVerticalAntenna;
	int NumberOfRxHorizontalAntenna;
	int numberOfRxVerticalPanel;
	int NumberOfRxHorizontalPanel;
	int NumberOfReceiveAntennaPort;
	double RxVerticalAntennaDistance;
	double RxHorizontalAntennaDistance;
	double RxVerticalPanelDistance;
	double RxHorizontalPanelDistance;

	int NumberOfChannelProcessOfSmallCell;
	int numberOfTxVerticalAntennaOfSmallCell;
	int NumberOfTxHorizontalAntennaOfSmallCell;
	int numberOfTxVerticalPanelOfSmallCell;
	int NumberOfTxHorizontalPanelOfSmallCell;
	int NumberOfTransmitAntennaPortOfSmallCell;
	double TxVerticalAntennaDistanceOfSmallCell;
	double TxHorizontalAntennaDistanceOfSmallCell;
	double TxVerticalPanelDistanceOfSmallCell;
	double TxHorizontalPanelDistanceOfSmallCell;

	double WaveLengthOfElectomageneticWave;
	void Initialize(string fileName); // Initialization
	void TemporaryGlobalVariableInitialize(int msID);
	void TemporaryGlobalVariableInitializeForBS(int bsID);
	void LongTermChannel(); // LongTermChannel
	void ShortTermChannel(); // ShortTermChannel
	
	void PathlossforMS();
	void PathlossforWiFiBS();
	void PathlossforWiFiMS();

	void ConcludeIteration(); // Iteration conclusion
	void Conclude(); // Simulation conclusion

	// LAA...
	int NumberOfStrongInterferenceBS;

	double ***distancefrom;
	double ***LOS;
	double ***PLoS;
	double ***pathlosss;
};

#endif