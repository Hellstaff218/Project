#include "HW1.h"
#include "sorts.h"

#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace
{
const char *kOutputFileName = "HW_1_results.md";

enum class Complexity
{
    quadratic,
    nLogN,
    shell,
    linear
};

struct SortBenchmark
{
    const char *title;
    void (*sortFunc)(int *, int, bool (*)(int, int));
    Complexity complexity;
    bool isEnabled = true;
    bool hasPreviousMeasurement = false;
    int previousSize = 0;
    double previousTime = 0.0;
};

struct Config
{
    int minSize = 10;
    int maxSize = 5000000;
    int stepSize = 0;
    double maxTimeMs = 1000.0;
};

void appendTextToFile(const char *fileName, const std::string &text)
{
    char *buffer = new char[text.size() + 1];
    for (std::size_t i = 0; i < text.size(); i++)
    {
        buffer[i] = text[i];
    }
    buffer[text.size()] = '\0';

    writeStringToFile(fileName, buffer);
    delete[] buffer;
}

std::vector<int> buildSizes(const Config &config)
{
    std::vector<int> sizes;

    if (config.stepSize > 0)
    {
        for (int size = config.minSize; size <= config.maxSize; size += config.stepSize)
        {
            sizes.push_back(size);

            if (size > config.maxSize - config.stepSize)
            {
                break;
            }
        }

        if (sizes.empty() || sizes.back() != config.maxSize)
        {
            sizes.push_back(config.maxSize);
        }

        return sizes;
    }

    long long currentSize = config.minSize;
    bool multiplyByFive = true;

    while (currentSize <= config.maxSize)
    {
        sizes.push_back(static_cast<int>(currentSize));

        const long long multiplier = multiplyByFive ? 5LL : 2LL;
        const long long nextSize = currentSize * multiplier;
        if (nextSize <= currentSize)
        {
            break;
        }

        currentSize = nextSize;
        multiplyByFive = !multiplyByFive;
    }

    if (sizes.empty() || sizes.back() != config.maxSize)
    {
        sizes.push_back(config.maxSize);
    }

    return sizes;
}

double estimateGrowth(Complexity complexity, int previousSize, int currentSize)
{
    const double prev = static_cast<double>(previousSize);
    const double curr = static_cast<double>(currentSize);

    switch (complexity)
    {
    case Complexity::quadratic:
        return (curr * curr) / (prev * prev);
    case Complexity::nLogN:
        return (curr * std::log2(curr)) / (prev * std::log2(prev));
    case Complexity::shell:
        return std::pow(curr, 1.5) / std::pow(prev, 1.5);
    case Complexity::linear:
        return curr / prev;
    }

    return curr / prev;
}

bool isArraySortedByComp(const int *ar, int size, bool (*comp)(int, int))
{
    for (int i = 0; i < size - 1; i++)
    {
        if (comp(ar[i + 1], ar[i]))
        {
            return false;
        }
    }

    return true;
}

double measureSort(
    void (*sortFunc)(int *, int, bool (*)(int, int)),
    const int *source,
    int size,
    bool (*comp)(int, int))
{
    int *buffer = new int[size];
    for (int i = 0; i < size; i++)
    {
        buffer[i] = source[i];
    }

    const double start = getTime(meas::milli);
    sortFunc(buffer, size, comp);
    const double finish = getTime(meas::milli);

    if (!isArraySortedByComp(buffer, size, comp))
    {
        std::cerr << "sort error: result is not sorted" << std::endl;
    }

    delete[] buffer;
    return finish - start;
}

Config parseArgs(int argc, char **argv)
{
    Config config;

    for (int i = 1; i < argc; i++)
    {
        const std::string flag = argv[i];

        if ((flag == "--max_time" || flag == "--mat_time") && i + 1 < argc)
        {
            config.maxTimeMs = std::stod(argv[++i]);
        }
        else if (flag == "--min_size" && i + 1 < argc)
        {
            config.minSize = std::stoi(argv[++i]);
        }
        else if (flag == "--max_size" && i + 1 < argc)
        {
            config.maxSize = std::stoi(argv[++i]);
        }
        else if (flag == "--step_size" && i + 1 < argc)
        {
            config.stepSize = std::stoi(argv[++i]);
        }
    }

    if (config.minSize < 1)
    {
        config.minSize = 1;
    }

    if (config.maxSize < config.minSize)
    {
        config.maxSize = config.minSize;
    }

    if (config.maxTimeMs <= 0.0)
    {
        config.maxTimeMs = 1000.0;
    }

    if (config.stepSize < 0)
    {
        config.stepSize = 0;
    }

    return config;
}

std::string formatTimeValue(double value)
{
    char *buffer = convertDoubleToStr(value);
    const std::string result(buffer);
    delete[] buffer;
    return result;
}

void writeHeader(const char *fileName)
{
    appendTextToFile(fileName, "| кол-во элементов | пузырьковая сортировка | сортировка выбором | сортировка вставками | сортировка слиянием | быстрая сортировка | сортировка Шелла | сортировка подсчётом |\n");
    appendTextToFile(fileName, "| :--------------: | :--------------------: | :----------------: | :-------------------: | :-----------------: | :----------------: | :---------------: | :------------------: |\n");
}
}

int main(int argc, char **argv)
{
    const Config config = parseArgs(argc, argv);
    const std::vector<int> sizes = buildSizes(config);

    {
        std::ofstream clearFile(kOutputFileName, std::ios::trunc);
    }

    writeHeader(kOutputFileName);

    std::vector<SortBenchmark> benchmarks = {
        {"bubble", bubbleSort, Complexity::quadratic},
        {"selection", selectionSort, Complexity::quadratic},
        {"insertion", insertionSort, Complexity::quadratic},
        {"merge", mergeSort, Complexity::nLogN},
        {"quick", quickSort, Complexity::nLogN},
        {"shell", sortShell, Complexity::shell},
        {"count", countSort, Complexity::linear},
    };

    for (const int size : sizes)
    {
        int *source = new int[size];
        randomFillAr(source, size);

        std::string row = "| ";
        row += std::to_string(size);
        row += " ";

        for (SortBenchmark &benchmark : benchmarks)
        {
            row += "| ";

            if (!benchmark.isEnabled)
            {
                row += "--- ";
                continue;
            }

            if (benchmark.hasPreviousMeasurement)
            {
                const double estimatedTime =
                    benchmark.previousTime * estimateGrowth(
                                                  benchmark.complexity,
                                                  benchmark.previousSize,
                                                  size);

                if (estimatedTime > config.maxTimeMs)
                {
                    benchmark.isEnabled = false;
                    row += "--- ";
                    continue;
                }
            }

            const double elapsed = measureSort(benchmark.sortFunc, source, size, lessComp);
            row += formatTimeValue(elapsed);
            row += " ";

            benchmark.hasPreviousMeasurement = true;
            benchmark.previousSize = size;
            benchmark.previousTime = elapsed;

            if (elapsed > config.maxTimeMs)
            {
                benchmark.isEnabled = false;
            }
        }

        row += "|\n";
        appendTextToFile(kOutputFileName, row);

        delete[] source;
    }

    std::cout << "Results saved to " << kOutputFileName << std::endl;
    std::cout << "max_time = " << config.maxTimeMs << " ms" << std::endl;
    std::cout << "min_size = " << config.minSize << std::endl;
    std::cout << "max_size = " << config.maxSize << std::endl;
    if (config.stepSize > 0)
    {
        std::cout << "step_size = " << config.stepSize << std::endl;
    }
    else
    {
        std::cout << "step_size = variable" << std::endl;
    }

    return 0;
}
