#include "gnuplot.h"
#include "research_cond.h"

#include <cmath>
#include <exception>
#include <iostream>
#include <string>
#include <vector>

namespace
{
constexpr double kPi = 3.14159265358979323846;

struct AppConfig
{
    double r1 = 100000.0;
    double r2 = 1000.0;
    double c1 = 100e-6;
    double e1 = 10.0;
    double totalTime = 8.0 * kPi;
    double stepTime = 0.0;
    TypeSignal signal = TypeSignal::constV;
    bool charge = true;
    bool discharge = true;
    std::string jpegFileName;
};

double parseMetricValue(const std::string &text)
{
    if (text.empty())
    {
        throw std::invalid_argument("empty value");
    }

    std::string numberPart = text;
    double multiplier = 1.0;

    const char suffix = text.back();
    if ((suffix >= 'A' && suffix <= 'Z') || (suffix >= 'a' && suffix <= 'z'))
    {
        numberPart = text.substr(0, text.size() - 1);
        switch (suffix)
        {
        case 'p':
        case 'P':
            multiplier = 1e-12;
            break;
        case 'n':
        case 'N':
            multiplier = 1e-9;
            break;
        case 'u':
        case 'U':
            multiplier = 1e-6;
            break;
        case 'k':
            multiplier = 1e3;
            break;
        case 'M':
            multiplier = 1e6;
            break;
        case 'G':
            multiplier = 1e9;
            break;
        default:
            throw std::invalid_argument("unsupported suffix: " + text);
        }
    }

    return std::stod(numberPart) * multiplier;
}

bool parseBoolValue(const std::string &text)
{
    if (text == "true" || text == "1" || text == "on")
    {
        return true;
    }

    if (text == "false" || text == "0" || text == "off")
    {
        return false;
    }

    throw std::invalid_argument("invalid bool value: " + text);
}

TypeSignal parseSignal(const std::string &text)
{
    if (text == "constV")
    {
        return TypeSignal::constV;
    }

    if (text == "meandr")
    {
        return TypeSignal::meandr;
    }

    if (text == "sin" || text == "sinus")
    {
        return TypeSignal::sinus;
    }

    if (text == "triangle")
    {
        return TypeSignal::triangle;
    }

    if (text == "sawtooth")
    {
        return TypeSignal::sawtooth;
    }

    if (text == "halfSin" || text == "halfSinus")
    {
        return TypeSignal::halfSinus;
    }

    if (text == "rectSin" || text == "doubleHalfSinus")
    {
        return TypeSignal::doubleHalfSinus;
    }

    throw std::invalid_argument("unsupported signal: " + text);
}

std::string getValueAfterPrefix(const std::string &arg, const std::string &prefix)
{
    return arg.substr(prefix.size());
}

AppConfig parseArgs(int argc, char **argv)
{
    AppConfig config;

    for (int i = 1; i < argc; i++)
    {
        const std::string arg = argv[i];

        if (arg.rfind("-R1=", 0) == 0)
        {
            config.r1 = parseMetricValue(getValueAfterPrefix(arg, "-R1="));
        }
        else if (arg.rfind("-R2=", 0) == 0)
        {
            config.r2 = parseMetricValue(getValueAfterPrefix(arg, "-R2="));
        }
        else if (arg.rfind("-C1=", 0) == 0)
        {
            config.c1 = parseMetricValue(getValueAfterPrefix(arg, "-C1="));
        }
        else if (arg.rfind("-E1=", 0) == 0)
        {
            config.e1 = std::stod(getValueAfterPrefix(arg, "-E1="));
        }
        else if (arg.rfind("-T=", 0) == 0)
        {
            config.totalTime = parseMetricValue(getValueAfterPrefix(arg, "-T="));
        }
        else if (arg.rfind("--step=", 0) == 0)
        {
            config.stepTime = parseMetricValue(getValueAfterPrefix(arg, "--step="));
        }
        else if (arg.rfind("--signal=", 0) == 0)
        {
            config.signal = parseSignal(getValueAfterPrefix(arg, "--signal="));
        }
        else if (arg.rfind("--jpeg=", 0) == 0)
        {
            config.jpegFileName = getValueAfterPrefix(arg, "--jpeg=");
        }
        else if (arg.rfind("--charge=", 0) == 0)
        {
            config.charge = parseBoolValue(getValueAfterPrefix(arg, "--charge="));
        }
        else if (arg.rfind("--discharge=", 0) == 0)
        {
            config.discharge = parseBoolValue(getValueAfterPrefix(arg, "--discharge="));
        }
    }

    if (config.r1 <= 0.0)
    {
        config.r1 = 1.0;
    }

    if (config.r2 <= 0.0)
    {
        config.r2 = 1.0;
    }

    if (config.c1 <= 0.0)
    {
        config.c1 = 1e-6;
    }

    if (config.totalTime <= 0.0)
    {
        config.totalTime = 8.0 * kPi;
    }

    if (config.stepTime <= 0.0)
    {
        config.stepTime = config.totalTime / 600.0;
    }

    return config;
}

std::string buildJpegName(const std::string &baseName, const std::string &suffix, bool keepOriginalName)
{
    if (baseName.empty())
    {
        return "";
    }

    if (keepOriginalName)
    {
        return baseName;
    }

    const std::size_t dotPos = baseName.find_last_of('.');
    if (dotPos == std::string::npos)
    {
        return baseName + suffix;
    }

    return baseName.substr(0, dotPos) + suffix + baseName.substr(dotPos);
}

void plotConstSignal(const CircuitWork &circuit, const AppConfig &config)
{
    const std::vector<std::pair<double, double>> source = circuit.getSourceVolt();

    if (config.charge)
    {
        Gnuplot::PlotOptions options;
        options.title = "HW_2: charge";
        options.xLabel = "time";
        options.yLabel = "voltage";
        options.scriptFileName = "hw2_charge.plt";
        options.jpegFileName = buildJpegName(config.jpegFileName, "_charge", !config.discharge);

        std::vector<Gnuplot::Series> series = {
            {"E1", "#0B7285", source},
            {"Uc charge", "#D9480F", circuit.getChargeVolt()},
        };

        Gnuplot plotter;
        plotter.plot(options, series);
    }

    if (config.discharge)
    {
        Gnuplot::PlotOptions options;
        options.title = "HW_2: discharge";
        options.xLabel = "time";
        options.yLabel = "voltage";
        options.scriptFileName = "hw2_discharge.plt";
        options.jpegFileName = buildJpegName(config.jpegFileName, "_discharge", !config.charge);

        std::vector<Gnuplot::Series> series = {
            {"E1", "#0B7285", source},
            {"Uc discharge", "#C2255C", circuit.getDischargeVolt()},
        };

        Gnuplot plotter;
        plotter.plot(options, series);
    }
}

void plotVariableSignal(const CircuitWork &circuit, const AppConfig &config)
{
    Gnuplot::PlotOptions options;
    options.title = "HW_2: variable signal";
    options.xLabel = "time";
    options.yLabel = "voltage";
    options.scriptFileName = "hw2_signal.plt";
    options.jpegFileName = config.jpegFileName;

    std::vector<Gnuplot::Series> series = {
        {"E1", "#0B7285", circuit.getSourceVolt()},
        {"Uc", "#E03131", circuit.getSignalVolt()},
    };

    Gnuplot plotter;
    plotter.plot(options, series);
}

void printUsage()
{
    std::cout << "Usage:\n";
    std::cout << "  ./app -R1=100k -R2=1k -C1=100u --signal=sin --jpeg=plot.jpeg\n";
}
}

int main(int argc, char **argv)
{
    try
    {
        const AppConfig config = parseArgs(argc, argv);

        const double signalPeriod =
            config.signal == TypeSignal::constV ? config.totalTime : config.totalTime / 3.0;

        const CircuitWork::ParamCircuit circuitParams(config.c1, config.r1, config.r2);
        const CircuitWork::ParamVoltSource sourceParams(config.e1, config.signal, signalPeriod);
        const CircuitWork circuit(circuitParams, sourceParams, config.totalTime, config.stepTime);

        if (config.signal == TypeSignal::constV)
        {
            plotConstSignal(circuit, config);
        }
        else
        {
            plotVariableSignal(circuit, config);
        }

        std::cout << "R1 = " << config.r1 << " Ohm\n";
        std::cout << "R2 = " << config.r2 << " Ohm\n";
        std::cout << "C1 = " << config.c1 << " F\n";
        std::cout << "E1 = " << config.e1 << " V\n";
        std::cout << "T  = " << config.totalTime << '\n';
        std::cout << "dt = " << config.stepTime << '\n';
    }
    catch (const std::exception &error)
    {
        std::cerr << "Error: " << error.what() << std::endl;
        printUsage();
        return 1;
    }

    return 0;
}
