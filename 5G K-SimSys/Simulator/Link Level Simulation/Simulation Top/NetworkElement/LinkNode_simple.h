#ifndef LINKNODE_H
#define LINKNODE_H

#include "../../../Simulation Top/Global/SystemSimConfiguration.h"

class LinkNode
{
    int id; // ID
    LinkNode* p; // Pointer to self
    LLS_Scheme scheme; // Transmission and reception schemes
    LLS_Length length; // Data length
    LLS_NumError numError; // # of errors
    LLS_ErrorRate errorRate; // Error rates
    LLS_ResourceAllocation resourceAlloc; // Resource allocation
    LLS_FeedbackInfo feedback; // Feedback information
    LLS_Data data; // Link simulation data

	LinkNode() { }; // Create and initialize
    ~LinkNode(); // Delete
    void Transmit(LinkNode* rx); // Transmission process with its own parameters
    void Receive(LinkNode* tx, LinkChannel* channel); // Reception process with transmitter parameters
    void Noise(); // Generate noise
    void Channel(LinkNode* tx, LinkChannel* channel); // Add TX data to received signal
    void InitializeIteration();
    void ConcludeIteration();
};


extern LinkNode* TX[LLS_MAX_TX];
extern LinkNode* RX[LLS_MAX_RX];

#endif