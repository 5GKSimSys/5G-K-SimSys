/****************************************************************************

Link Level Simulation header (Simple)


PROJECT NAME : System Level Simulator High Level Design
FILE NAME    : LLS_simple.h
DATE         : 2016.11.5
VERSION      : 0.11
ORGANIZATION : Korea University, Dongguk University

Copyright (C) 2016, by Korea University, Dongguk University, All Rights Reserved

****************************************************************************/

/*===========================================================================

EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

when		who				what, where, why
----------	------------	-------------------------------------------------
2016.11.5	Minjoong Rim 	Created

===========================================================================*/


#ifndef LLS_H
#define LLS_H

/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         INCLUDE FILES FOR MODULE                        */
/*                                                                         */
/*-------------------------------------------------------------------------*/

#include <cstdlib>
#include <string>
#include <complex>
#include <string>
#include "../../../Library/Math/armadillo-7.400.4/include/armadillo"
using namespace std;


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         CONSTANT                                        */
/*                                                                         */
/*-------------------------------------------------------------------------*/

// Modulation
#define LLS_BPSK		1
#define LLS_QPSK		2
#define LLS_16QAM		4
#define LLS_64QAM		6
#define LLS_256QAM		8

// For memory assignments
#define LLS_MAX_DATA_LENGTH	5000
#define LLS_MAX_TX			50
#define LLS_MAX_RX			50


/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                         ENUM DEFINITION                                 */
/*                                                                         */
/*-------------------------------------------------------------------------*/

namespace LLS
{
	enum ChannelType {
		Ideal,
		AWGN,
		Fading
	};


	enum CodingScheme {
		NoCoding,
		ConvolutionalCoding,
		TurboCoding,
		LdpcCoding,
		PolarCoding
	};


	enum Direction {
		Downlink,
		Uplink,
		RandomAccess
	};


	enum WaveformScheme {
		OFDMA,
		SCFDMA
	};
}

/*-------------------------------------------------------------------------*/
/*                                                                         */
/*                             TYPE DECLARATION                            */
/*                                                                         */
/*-------------------------------------------------------------------------*/

typedef struct {
	int source; // Source data length
	int coded; // Coded data length
	int symbol; // Symbol length after modulation
	int frame; // Frame length
} LLS_Length; // Data lengths


typedef struct {
	int uncodedBit; // # of uncoded bit errors
	int codedBit; // # of coded bit errors
	int frame; // # of frame errors for multiple frames; 0: no error, 1: error for a single frame
} LLS_NumError; // # of errors


typedef struct {
	double uncodedBit; // Uncoded BER
	double codedBit; // Coded BER
	double frame; // FER
} LLS_ErrorRate; // Error rates


typedef struct {
	LLS::Direction direction; // Downlink, Uplink, Random Access
	LLS::ChannelType channelType; // Channel type
	int numTX; // # of TX nodes
	int numRX; // # of RX nodes
} LLS_Scenario; // Simulation scenario


typedef struct {
	int timing; // Timing synchronization
	int frequency; // Frequency synchronization
	int channelEstimation; // Channel estimation
} LLS_Synchronization; // Synchronization algorithm on 


typedef struct {
	int modulation; // Modulation order (1: BPSK, 2: QPSK, 4: 16QAM, 6: 64QAM)
	int codeRate; // Reciprocal value of coding rate
	LLS::CodingScheme coding; // Coding scheme
	LLS::WaveformScheme waveform; // Waveform scheme
	int interferenceCancellation; // Whether interference cancellation is performed
	double txPower; // Transmission power
} LLS_Scheme; // Transmission and reception schemes


typedef struct {
    int source[LLS_MAX_DATA_LENGTH]; // Source data
    int coded[LLS_MAX_DATA_LENGTH]; // Coded data
    int hardDecision[LLS_MAX_DATA_LENGTH]; // Hard decision
    int softDecision[LLS_MAX_DATA_LENGTH]; // Soft decision
    int decoded[LLS_MAX_DATA_LENGTH]; // Decoded data
	std::complex<double> txFrame[LLS_MAX_DATA_LENGTH]; // Transmission frame
	std::complex<double> rxFrame[LLS_MAX_DATA_LENGTH]; // Reception frame
	std::complex<double> compensated[LLS_MAX_DATA_LENGTH]; // Channel compensated
} LLS_Data; // Data


// Will be defined clealry later
typedef struct {
    
} LLS_ResourceAllocation; // Resource allocation


typedef struct {
 
} LLS_FeedbackInfo; // Feedback information

#endif