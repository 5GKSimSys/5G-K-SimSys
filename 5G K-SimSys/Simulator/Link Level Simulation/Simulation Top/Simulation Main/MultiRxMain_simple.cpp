int main()
{
    Link.Initialize(); // Initialize simulation parameters
    Link.InitializeNode(); // Initialize transmitter, receivers, and channels
    for (int snr = Link.snr.min; snr <= Link.snr.max; snr += Link.snr.step)
    {
        Link.InitializeIteration(snr); // Initialize simulation parameters for an iteration
        for (int i = 0; i < Link.numIteration; i++)
        {
            for (in j = 0; j < Link.scenario.numRX; j++)
            {
                 RX[j]->Noise(); // Noise generation
             }
            for (int j = 0; j < Link.scenario.numRX; j++) // One transmitter sends multiple data 
            {
                TX[j]->Transmit(RX[j]); // One transmitter performs multiple transmission processing
                 for (int k = 0; k < Link.scenario.numRX; k++) // Multiple receivers
                 {
                      RX[k]->Channel(TX[j], CH[0][k]); // Use RX channel
                  }
             }
            for (int j = 0; j < Link.scenario.numRX; j++)
            {
                RX[j]->Receive(TX[j], CH[0][j]); // Reception process
            }
        }
        Link.ConcludeIteration(); // Calculate BER and FER
    }
    Link.Conclude(); // Conclude simulation
    return 0;
}

