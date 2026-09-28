#include "double_linked_list.h"
#include <iostream>

int main() {
    ProcessPulses pulses("current_pulse.bin");

    std::cout << "Found pulses: " << pulses.getCountPulse() << std::endl;

    Gnuplot plot;

    plot.buildPulse(pulses.getPulse(1), SaveTo::show);
    plot.buildPulse(pulses.getPulse(1), SaveTo::png);
    plot.buildPulse(pulses.getPulse(1), SaveTo::jpeg);

    std::cout << "Saved pulse.png and pulse.jpeg" << std::endl;

    return 0;
}
