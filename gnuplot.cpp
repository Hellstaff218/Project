#include "gnuplot.h"

#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

namespace
{
std::string quotePath(const std::string &path)
{
    return "\"" + path + "\"";
}

std::string getBaseName(const std::string &fileName)
{
    const std::size_t dotPos = fileName.find_last_of('.');
    if (dotPos == std::string::npos)
    {
        return fileName;
    }

    return fileName.substr(0, dotPos);
}
}

Gnuplot::Gnuplot(std::string executable) : executable_(std::move(executable))
{
}

bool Gnuplot::plot(const PlotOptions &options, const std::vector<Series> &series) const
{
    if (series.empty())
    {
        return false;
    }

    const std::string scriptFileName =
        options.scriptFileName.empty() ? "hw2_plot.plt" : options.scriptFileName;
    const std::string baseName = getBaseName(scriptFileName);

    std::vector<std::string> dataFiles;
    for (std::size_t i = 0; i < series.size(); i++)
    {
        const std::string dataFileName = baseName + "_" + std::to_string(i) + ".dat";
        if (!writeDataFile(dataFileName, series[i]))
        {
            return false;
        }

        dataFiles.push_back(dataFileName);
    }

    if (!options.jpegFileName.empty())
    {
        const std::string saveScript = baseName + "_save.plt";
        if (writeScriptFile(saveScript, options, series, dataFiles, true))
        {
            runScript(saveScript, false);
        }
    }

    if (!writeScriptFile(scriptFileName, options, series, dataFiles, false))
    {
        return false;
    }

    runScript(scriptFileName, options.keepWindowOpen);
    return true;
}

bool Gnuplot::writeDataFile(const std::string &fileName, const Series &series) const
{
    std::ofstream out(fileName, std::ios::trunc);
    if (!out.is_open())
    {
        return false;
    }

    out << std::fixed << std::setprecision(6);
    for (const std::pair<double, double> &point : series.points)
    {
        out << point.first << ' ' << point.second << '\n';
    }

    return true;
}

bool Gnuplot::writeScriptFile(
    const std::string &fileName,
    const PlotOptions &options,
    const std::vector<Series> &series,
    const std::vector<std::string> &dataFiles,
    bool saveToJpeg) const
{
    std::ofstream out(fileName, std::ios::trunc);
    if (!out.is_open())
    {
        return false;
    }

    out << "set grid\n";
    out << "set xlabel " << quotePath(options.xLabel.empty() ? "time" : options.xLabel) << '\n';
    out << "set ylabel " << quotePath(options.yLabel.empty() ? "voltage" : options.yLabel) << '\n';
    out << "set title " << quotePath(options.title.empty() ? "HW_2" : options.title) << '\n';

    if (saveToJpeg)
    {
        out << "set terminal jpeg size 1280,720\n";
        out << "set output " << quotePath(options.jpegFileName) << '\n';
    }
    else
    {
        out << "set terminal qt\n";
    }

    out << "plot ";
    for (std::size_t i = 0; i < dataFiles.size(); i++)
    {
        if (i > 0)
        {
            out << ", ";
        }

        out << quotePath(dataFiles[i]) << " using 1:2 with lines lw 2";
        if (i < series.size() && !series[i].color.empty())
        {
            out << " lc rgb " << quotePath(series[i].color);
        }
        if (i < series.size())
        {
            out << " title " << quotePath(series[i].title);
        }
    }
    out << '\n';

    if (!saveToJpeg)
    {
        out << "pause mouse close\n";
    }

    return true;
}

bool Gnuplot::runScript(const std::string &fileName, bool keepWindowOpen) const
{
    std::ostringstream command;
    command << executable_ << ' ';
    if (keepWindowOpen)
    {
        command << "-persist ";
    }
    command << quotePath(fileName);

    const int exitCode = std::system(command.str().c_str());
    if (exitCode != 0)
    {
        std::cerr << "Warning: gnuplot is unavailable, script saved to " << fileName << std::endl;
        return false;
    }

    return true;
}
