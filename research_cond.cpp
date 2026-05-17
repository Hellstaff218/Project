#include "research_cond.h"

#include <algorithm>
#include <cmath>

namespace
{
constexpr double kPi = 3.14159265358979323846;
constexpr double kMinResistance = 1e-12;
constexpr double kMinCapacitance = 1e-12;

double normalizePhase(double curTime, double period)
{
    if (period <= 0.0)
    {
        return 0.0;
    }

    double phase = std::fmod(curTime, period);
    if (phase < 0.0)
    {
        phase += period;
    }

    return phase / period;
}
}

CircuitWork::ParamCircuit::ParamCircuit(double c1, double r1, double r2)
    : _C1(std::max(c1, kMinCapacitance)),
      _R1(std::max(r1, kMinResistance)),
      _R2(std::max(r2, kMinResistance))
{
}

CircuitWork::ParamVoltSource::ParamVoltSource(double e1, TypeSignal signal, double period)
    : _E1(e1), _signalForm(signal), _period(period)
{
}

CircuitWork::CircuitWork(
    const ParamCircuit &valueElements,
    const ParamVoltSource &voltage,
    double totalTime,
    double stepTime)
    : schemeParam_(valueElements),
      voltageSource_(voltage),
      totalTime_(totalTime > 0.0 ? totalTime : 1.0),
      stepTime_(stepTime > 0.0 ? stepTime : 1e-3),
      sw1Closed_(true),
      sw2Closed_(true)
{
}

double CircuitWork::getVoltageE1(double curTime) const
{
    if (voltageSource_._signalForm == TypeSignal::constV)
    {
        return voltageSource_._E1;
    }

    const double phase = normalizePhase(curTime, voltageSource_._period);
    const double angle = 2.0 * kPi * phase;

    switch (voltageSource_._signalForm)
    {
    case TypeSignal::constV:
        return voltageSource_._E1;
    case TypeSignal::meandr:
        return phase < 0.5 ? voltageSource_._E1 : 0.0;
    case TypeSignal::sinus:
        return voltageSource_._E1 * std::sin(angle);
    case TypeSignal::triangle:
        return phase < 0.5 ? voltageSource_._E1 * 2.0 * phase
                           : voltageSource_._E1 * 2.0 * (1.0 - phase);
    case TypeSignal::sawtooth:
        return voltageSource_._E1 * phase;
    case TypeSignal::halfSinus:
        return std::max(0.0, voltageSource_._E1 * std::sin(angle));
    case TypeSignal::doubleHalfSinus:
        return std::abs(voltageSource_._E1 * std::sin(angle));
    }

    return voltageSource_._E1;
}

double CircuitWork::getVoltageCharge(double curTime) const
{
    if (curTime <= 0.0)
    {
        return 0.0;
    }

    const double tau = schemeParam_._R1 * schemeParam_._C1;
    return voltageSource_._E1 * (1.0 - std::exp(-curTime / tau));
}

double CircuitWork::getVoltageDischarge(double curTime) const
{
    if (curTime <= 0.0)
    {
        return voltageSource_._E1;
    }

    const double tau = schemeParam_._R2 * schemeParam_._C1;
    return voltageSource_._E1 * std::exp(-curTime / tau);
}

bool CircuitWork::toggle_SW1()
{
    sw1Closed_ = !sw1Closed_;
    return sw1Closed_;
}

bool CircuitWork::status_SW1() const
{
    return sw1Closed_;
}

bool CircuitWork::switch_SW1(bool on)
{
    sw1Closed_ = on;
    return sw1Closed_;
}

bool CircuitWork::toggle_SW2()
{
    sw2Closed_ = !sw2Closed_;
    return sw2Closed_;
}

bool CircuitWork::status_SW2() const
{
    return sw2Closed_;
}

bool CircuitWork::switch_SW2(bool on)
{
    sw2Closed_ = on;
    return sw2Closed_;
}

double CircuitWork::getVoltage(double curTime) const
{
    return getVoltage(curTime, sw1Closed_, sw2Closed_);
}

double CircuitWork::getVoltage(double curTime, bool statusSW1, bool statusSW2) const
{
    if (statusSW1 && statusSW2)
    {
        return getVoltageC(curTime);
    }

    if (statusSW1)
    {
        return getVoltageCharge(curTime);
    }

    if (statusSW2)
    {
        return getVoltageDischarge(curTime);
    }

    return 0.0;
}

double CircuitWork::getVoltageC(double curTime) const
{
    if (curTime <= 0.0)
    {
        return 0.0;
    }

    double capacitorVoltage = 0.0;
    double time = 0.0;

    while (time < curTime)
    {
        const double dt = std::min(stepTime_, curTime - time);
        const double sourceVoltage = getVoltageE1(time);
        const double sourceCurrent = (sourceVoltage - capacitorVoltage) / schemeParam_._R1;
        const double dischargeCurrent = capacitorVoltage / schemeParam_._R2;
        const double dVoltage = (sourceCurrent - dischargeCurrent) * dt / schemeParam_._C1;

        capacitorVoltage += dVoltage;
        time += dt;
    }

    return capacitorVoltage;
}

std::vector<std::pair<double, double>> CircuitWork::getSignalVolt() const
{
    std::vector<std::pair<double, double>> result;
    if (voltageSource_._signalForm == TypeSignal::constV)
    {
        return result;
    }

    for (double time = 0.0; time <= totalTime_; time += stepTime_)
    {
        result.push_back({time, getVoltageC(time)});
    }

    if (result.empty() || result.back().first < totalTime_)
    {
        result.push_back({totalTime_, getVoltageC(totalTime_)});
    }

    return result;
}

std::vector<std::pair<double, double>> CircuitWork::getSourceVolt() const
{
    std::vector<std::pair<double, double>> result;
    for (double time = 0.0; time <= totalTime_; time += stepTime_)
    {
        result.push_back({time, getVoltageE1(time)});
    }

    if (result.empty() || result.back().first < totalTime_)
    {
        result.push_back({totalTime_, getVoltageE1(totalTime_)});
    }

    return result;
}

std::vector<std::pair<double, double>> CircuitWork::getChargeVolt() const
{
    std::vector<std::pair<double, double>> result;
    for (double time = 0.0; time <= totalTime_; time += stepTime_)
    {
        result.push_back({time, getVoltageCharge(time)});
    }

    if (result.empty() || result.back().first < totalTime_)
    {
        result.push_back({totalTime_, getVoltageCharge(totalTime_)});
    }

    return result;
}

std::vector<std::pair<double, double>> CircuitWork::getDischargeVolt() const
{
    std::vector<std::pair<double, double>> result;
    for (double time = 0.0; time <= totalTime_; time += stepTime_)
    {
        result.push_back({time, getVoltageDischarge(time)});
    }

    if (result.empty() || result.back().first < totalTime_)
    {
        result.push_back({totalTime_, getVoltageDischarge(totalTime_)});
    }

    return result;
}
