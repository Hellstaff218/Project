#ifndef GNUPLOT_H
#define GNUPLOT_H

#include <string>
#include <utility>
#include <vector>

class Gnuplot
{
public:
    struct Series
    {
        std::string title;
        std::string color;
        std::vector<std::pair<double, double>> points;
    };

    struct PlotOptions
    {
        std::string title;
        std::string xLabel;
        std::string yLabel;
        std::string scriptFileName;
        std::string jpegFileName;
        bool keepWindowOpen = true;
    };

    explicit Gnuplot(std::string executable = "gnuplot");
    bool plot(const PlotOptions &options, const std::vector<Series> &series) const;

private:
    std::string executable_;

    bool writeDataFile(const std::string &fileName, const Series &series) const;
    bool writeScriptFile(
        const std::string &fileName,
        const PlotOptions &options,
        const std::vector<Series> &series,
        const std::vector<std::string> &dataFiles,
        bool saveToJpeg) const;
    bool runScript(const std::string &fileName, bool keepWindowOpen) const;
};

#endif
