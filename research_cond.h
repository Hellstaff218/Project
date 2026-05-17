#ifndef RESEARCH_COND_H
#define RESEARCH_COND_H

#include <utility>
#include <vector>

enum class TypeSignal
{
    constV = 0,
    meandr = 1,
    sinus = 2,
    triangle = 3,
    sawtooth = 4,
    halfSinus = 5,
    doubleHalfSinus = 6,
};

class CircuitWork
{
public:
    struct ParamCircuit
    {
        double _C1;
        double _R1;
        double _R2;

        ParamCircuit() = delete;
        ParamCircuit(double c1, double r1, double r2);
    };

    struct ParamVoltSource
    {
        double _E1;
        TypeSignal _signalForm;
        double _period;

        ParamVoltSource() = delete;
        ParamVoltSource(double e1, TypeSignal signal, double period);
    };

    CircuitWork() = delete;
    CircuitWork(
        const ParamCircuit &valueElements,
        const ParamVoltSource &voltage,
        double totalTime,
        double stepTime);

    double getVoltageC(double curTime) const;
    double getVoltageE1(double curTime) const;
    double getVoltageCharge(double curTime) const;
    double getVoltageDischarge(double curTime) const;

    bool toggle_SW1();
    bool status_SW1() const;
    bool switch_SW1(bool on);
    bool toggle_SW2();
    bool status_SW2() const;
    bool switch_SW2(bool on);

    double getVoltage(double curTime) const;
    double getVoltage(double curTime, bool statusSW1, bool statusSW2) const;

    std::vector<std::pair<double, double>> getSignalVolt() const;
    std::vector<std::pair<double, double>> getSourceVolt() const;
    std::vector<std::pair<double, double>> getChargeVolt() const;
    std::vector<std::pair<double, double>> getDischargeVolt() const;

private:
    ParamCircuit schemeParam_;
    ParamVoltSource voltageSource_;
    double totalTime_;
    double stepTime_;
    bool sw1Closed_;
    bool sw2Closed_;
};

#endif
