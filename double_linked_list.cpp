#include "double_linked_list.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstdint>
DoubleLinkedList::DoubleLinkedList() {
    Head = nullptr;
    Tail = nullptr;
    countNodes = 0;
}

DoubleLinkedList::~DoubleLinkedList() {
    while (Head != nullptr) {
        pop_front();
    }
}

int DoubleLinkedList::getCountNodes() const {
    return countNodes;
}

void DoubleLinkedList::push_back(const Data* d) {
    Data* newData = new Data(*d);
    Node* newNode = new Node(newData);

    if (Tail == nullptr) {
        Head = newNode;
        Tail = newNode;
    }
    else {
        newNode->prev = Tail;
        Tail->next = newNode;
        Tail = newNode;
    }
    countNodes++;
}

void DoubleLinkedList::push_front(const Data* d) {
    Data* newData = new Data(*d);
    Node* newNode = new Node(newData);

    if (Head == nullptr) {
        Head = newNode;
        Tail = newNode;
    }
    else {
        newNode->next = Head;
        Head->prev = newNode;
        Head = newNode;
    }
    countNodes++;
}

void DoubleLinkedList::pop_front() {
    if (Head == nullptr) return;

    Node* oldHead = Head;
    Head = Head->next;

    if (Head != nullptr) {
        Head->prev = nullptr;
    } else {
        Tail = nullptr;
    }
    delete oldHead->data;
    delete oldHead;
    countNodes--;
}

void DoubleLinkedList::pop_back() {
    if (Tail == nullptr) return;

    Node* oldTail = Tail;
    Tail = Tail->prev;

    if (Tail != nullptr) {
        Tail->next = nullptr;
    }
    else {
        Head = nullptr;
    }

    delete oldTail->data;
    delete oldTail;
    countNodes--;
}

void DoubleLinkedList::insert(const Data* d, int num_node) {
    if (Head == nullptr || num_node <= 0) {
        push_front(d);
        return;
    }
    if (num_node > countNodes) {
        push_back(d);
        return;
    }
    Data* newData = new Data(*d);
    Node* newNode = new Node(newData);
    Node* current = Head;
    for (int i = 1; i < num_node; i++) {
        current = current->next;
    }
    newNode->prev = current->prev;
    newNode->next = current;
    current->prev->next = newNode;
    current->prev = newNode;
    countNodes++;
}

std::vector<std::pair<double, double>> DoubleLinkedList::get_Node(int num_node) const {
    if (Head == nullptr) {
        return {};
    }

    Node* target = nullptr;
    if (num_node <= 0) {
        target = Head;
    } else if (num_node > countNodes) {
        target = Tail;
    } else {
        target = Head;
        for (int i = 1; i < num_node; i++) {
            target = target->next;
        }
    }
    return target->data->points;
}

ProcessPulses::ProcessPulses() {}

ProcessPulses::ProcessPulses(const char* fileName) {
    std::ifstream file(fileName, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error: cannot open file " << fileName << std::endl;
        return;
    }

    file.seekg(0, std::ios::end);
    size_t fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    size_t countWords = fileSize / 2;
    std::vector<uint16_t> allData(countWords);
    file.read(reinterpret_cast<char*>(allData.data()), fileSize);
    file.close();

    std::vector<uint16_t> current;
    for (size_t i = 1; i < allData.size(); i += 2) {
        current.push_back(allData[i]);
    }

    size_t i = 0;
    while (i < current.size()) {
        while (i < current.size() && current[i] < 100) {
            i++;
        }
        if (i >= current.size()) break;

        size_t start = i;

        while (i < current.size() && current[i] >= 100) {
            i++;
        }
        size_t end = i;

        size_t pulseLength = end - start;

        if (pulseLength > 50) {
            Data* pulseData = new Data;

            for (size_t j = start; j < end; j++) {
                double t = static_cast<double>(j - start);
                double value = static_cast<double>(current[j]);
                pulseData->points.push_back({t, value});
            }

            double maxVal = 0.0;
            for (const auto& p : pulseData->points) {
                if (p.second > maxVal) maxVal = p.second;
            }
            pulseData->amplitude = maxVal;

            push_back(pulseData);
        }
    }
}

ProcessPulses::~ProcessPulses() {}

double ProcessPulses::normalizationCoef() const {
    double globalMax = 0.0;
    for (int i = 1; i <= getCountNodes(); i++) {
        double amp = getAmpl(i);
        if (amp > globalMax) {
            globalMax = amp;
        }
    }
    return globalMax;
}

int ProcessPulses::getCountPulse() const {
    return getCountNodes();
}

double ProcessPulses::getAmpl(int numNode) const {
    std::vector<std::pair<double, double>> points = get_Node(numNode);
    double maxVal = 0.0;
    for (const auto& p : points) {
        if (p.second > maxVal) {
            maxVal = p.second;
        }
    }
    return maxVal;
}

std::vector<std::pair<double, double>> ProcessPulses::getPulse(int numNode, bool normalize) const {
    std::vector<std::pair<double, double>> points = get_Node(numNode);
    if (!normalize) {
        return points;
    }

    double coef = normalizationCoef();
    std::vector<std::pair<double, double>> normalized;
    for (const auto& p : points) {
        normalized.push_back({p.first, p.second / coef});
    }
    return normalized;
}

double ProcessPulses::getRiseTime(int numNode) const {
    std::vector<std::pair<double, double>> points = get_Node(numNode);
    if (points.empty()) return 0.0;

    double amplitude = 0.0;
    for (const auto& p : points) {
        if (p.second > amplitude) amplitude = p.second;
    }
    if (amplitude == 0.0) return 0.0;

    double lowThreshold = 0.10 * amplitude;
    double highThreshold = 0.90 * amplitude;
    double t10 = -1.0, t90 = -1.0;

    for (size_t i = 0; i < points.size(); i++) {
        if (t10 < 0 && points[i].second >= lowThreshold) {
            if (i == 0) {
                t10 = points[i].first;
            }
	    else {
                double t1 = points[i - 1].first;
                double t2 = points[i].first;
                double I1 = points[i - 1].second;
                double I2 = points[i].second;
                t10 = t1 + (t2 - t1) * (lowThreshold - I1) / (I2 - I1);
            }
        }
        if (t10 >= 0 && t90 < 0 && points[i].second >= highThreshold) {
            if (i == 0) {
                t90 = points[i].first;
            }
	    else {
                double t1 = points[i - 1].first;
                double t2 = points[i].first;
                double I1 = points[i - 1].second;
                double I2 = points[i].second;
                t90 = t1 + (t2 - t1) * (highThreshold - I1) / (I2 - I1);
            }
            break;
        }
    }
    if (t10 < 0 || t90 < 0) return 0.0;
    return t90 - t10;
}

double ProcessPulses::getFailTime(int numNode) const {
    std::vector<std::pair<double, double>> points = get_Node(numNode);
    if (points.empty()) return 0.0;

    double amplitude = 0.0;
    size_t peakIndex = 0;
    for (size_t i = 0; i < points.size(); i++) {
        if (points[i].second > amplitude) {
            amplitude = points[i].second;
            peakIndex = i;
        }
    }
    if (amplitude == 0.0) return 0.0;

    double highThreshold = 0.90 * amplitude;
    double lowThreshold = 0.10 * amplitude;
    double t90 = -1.0, t10 = -1.0;

    for (size_t i = peakIndex; i < points.size(); i++) {
        if (t90 < 0 && points[i].second <= highThreshold) {
            if (i == peakIndex) {
                t90 = points[i].first;
            }
	    else {
                double t1 = points[i - 1].first;
                double t2 = points[i].first;
                double I1 = points[i - 1].second;
                double I2 = points[i].second;
                t90 = t1 + (t2 - t1) * (highThreshold - I1) / (I2 - I1);
            }
        }
        if (t90 >= 0 && t10 < 0 && points[i].second <= lowThreshold) {
            if (i == peakIndex || i == 0) {
                t10 = points[i].first;
            }
	    else {
                double t1 = points[i - 1].first;
                double t2 = points[i].first;
                double I1 = points[i - 1].second;
                double I2 = points[i].second;
                t10 = t1 + (t2 - t1) * (lowThreshold - I1) / (I2 - I1);
            }
            break;
        }
    }
    if (t90 < 0 || t10 < 0) return 0.0;
    return t10 - t90;
}

std::vector<std::pair<double, double>> ProcessPulses::diffPulse(int numNode) const {
    std::vector<std::pair<double, double>> points = get_Node(numNode);
    std::vector<std::pair<double, double>> diff;

    size_t n = points.size();
    if (n < 2) return diff;
    for (size_t i = 0; i < n; i++) {
        double t = points[i].first;
        double dI;

        if (i == 0) {
            double dt = points[i + 1].first - points[i].first;
            double dVal = points[i + 1].second - points[i].second;
            dI = dVal / dt;
        }
       	else if (i == n - 1) {
            double dt = points[i].first - points[i - 1].first;
            double dVal = points[i].second - points[i - 1].second;
            dI = dVal / dt;
        }
       	else {
            double dt = points[i + 1].first - points[i - 1].first;
            double dVal = points[i + 1].second - points[i - 1].second;
            dI = dVal / dt;
        }
        diff.push_back({t, dI});
    }
    return diff;
}

std::vector<std::pair<double, double>> ProcessPulses::intPulse(int numNode, int start, int end) const {
    std::vector<std::pair<double, double>> points = get_Node(numNode);
    std::vector<std::pair<double, double>> integral;

    int n = static_cast<int>(points.size());
    if (n == 0) return integral;

    int idxStart, idxEnd;
    if (start < 0 || end < 0) {
        idxStart = 0;
        idxEnd = n - 1;
    }
    else {
        idxStart = start;
        idxEnd = end;
        if (idxEnd >= n) idxEnd = n - 1;
        if (idxStart > idxEnd) {
            std::swap(idxStart, idxEnd);
        }
    }
    double sum = 0.0;
    integral.push_back({points[idxStart].first, 0.0});

    for (int i = idxStart; i < idxEnd; i++) {
        double dt = points[i + 1].first - points[i].first;
        double avgHeight = (points[i].second + points[i + 1].second) / 2.0;
        sum += avgHeight * dt;
        integral.push_back({points[i + 1].first, sum});
    }
    return integral;
}

double ProcessPulses::getDurPulse(int numNode, int start, int end) const {
    std::vector<std::pair<double, double>> points = get_Node(numNode);
    int n = static_cast<int>(points.size());
    if (n == 0) return 0.0;
    int idxStart = start;
    int idxEnd = end;

    if (idxStart < 0) idxStart = 0;
    if (idxEnd >= n) idxEnd = n - 1;
    if (idxStart > idxEnd) std::swap(idxStart, idxEnd);
    return points[idxEnd].first - points[idxStart].first;
}

std::vector<std::pair<double, double>> ProcessPulses::averPulse(int startNode, int countNode) const {
    std::vector<std::pair<double, double>> result;
    int total = getCountNodes();
    if (total == 0 || countNode <= 0) return result;

    int idxStart = startNode;
    if (idxStart < 1) idxStart = 1;
    int idxEnd = idxStart + countNode - 1;
    if (idxEnd > total) idxEnd = total;
    int actualCount = idxEnd - idxStart + 1;
    if (actualCount <= 0) return result;

    std::vector<std::pair<double, double>> first = get_Node(idxStart);
    size_t length = first.size();
    for (size_t i = 0; i < length; i++) {
        result.push_back({0.0, 0.0});
    }
    for (int node = idxStart; node <= idxEnd; node++) {
        std::vector<std::pair<double, double>> points = get_Node(node);
        for (size_t i = 0; i < length && i < points.size(); i++) {
            result[i].first = points[i].first;
            result[i].second += points[i].second;
        }
    }

    for (size_t i = 0; i < length; i++) {
        result[i].second /= actualCount;
    }
    return result;
}

void Gnuplot::buildPulse(const std::vector<std::pair<double, double>>& pulse, SaveTo paramToSave) {
    if (pulse.empty()) {
        return;
    }

    std::ofstream dataFile("pulse_data.tmp");
    for (const auto& p : pulse) {
        dataFile << p.first << " " << p.second << std::endl;
    }
    dataFile.close();

    std::ofstream scriptFile("plot_script.gp");

    scriptFile << "set grid" << std::endl;
    scriptFile << "set xlabel 'time'" << std::endl;
    scriptFile << "set ylabel 'current'" << std::endl;
    scriptFile << "set title 'impulse'" << std::endl;

    if (paramToSave == SaveTo::show) {
        scriptFile << "set terminal wxt" << std::endl;
        scriptFile << "plot 'pulse_data.tmp' using 1:2 with lines title 'I(t)'" << std::endl;
        scriptFile << "pause mouse close" << std::endl;
    } else if (paramToSave == SaveTo::png) {
        scriptFile << "set terminal png size 800,600" << std::endl;
        scriptFile << "set output 'pulse.png'" << std::endl;
        scriptFile << "plot 'pulse_data.tmp' using 1:2 with lines title 'I(t)'" << std::endl;
    } else if (paramToSave == SaveTo::jpeg) {
        scriptFile << "set terminal jpeg size 800,600" << std::endl;
        scriptFile << "set output 'pulse.jpeg'" << std::endl;
        scriptFile << "plot 'pulse_data.tmp' using 1:2 with lines title 'I(t)'" << std::endl;
    }
    scriptFile.close();
    system("gnuplot plot_script.gp");
    std::remove("pulse_data.tmp");
    std::remove("plot_script.gp");
}
