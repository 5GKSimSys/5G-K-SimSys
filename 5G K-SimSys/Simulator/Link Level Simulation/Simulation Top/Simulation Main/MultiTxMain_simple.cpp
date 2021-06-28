int main()
{
    Link.Initialize(); // Initialize simulation parameters
    Link.InitializeNode(); // Initialize transmitters, receiver, and channel
    for (int snr = Link.snr.min; snr <= Link.snr.max; snr += Link.snr.step)
    {
        Link.InitializeIteration(snr); // Initialize simulation parameters for an iteration
        for (int i = 0; i < Link.numIteration; i++)
        {
            RX[0]->Noise(); // Noise generation
            for (int j = 0; j < Link.scenario.numTX; j++)
            {
                TX[j]->Transmit(RX[0]); // Transmission process
                RX[0]->Channel(TX[j], CH[j][0]); // Add to the received signal
             }
            for (int j = 0; j < Link.scenario.numTX; j++)
            {
                RX[0]->Receive(TX[j], CH[j][0]); // Reception process
            }
        }
        Link.ConcludeIteration(); // Calculate BER and FER
    }
    Link.Conclude(); // Conclude simulation
    return 0;
}

