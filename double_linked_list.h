#ifndef _DOUBLE_LINKED_LIST_H
#define _DOUBLE_LINKED_LIST_H

#include <vector>
#include <utility>

struct Data {
    std::vector<std::pair<double, double>> points;
    double amplitude = 0.0;
    double normCoef = 1.0;
};

struct Node {
    Data* data;   
    Node* prev;   
    Node* next;

    Node(Data* d) : data(d), prev(nullptr), next(nullptr) {}
};
class DoubleLinkedList {
private:
    Node* Head;   
    Node* Tail;    
    int countNodes;   

public:
    DoubleLinkedList();   
    ~DoubleLinkedList(); 

    void push_back(const Data* d);  
    void push_front(const Data* d);  
    void pop_front();                
    void pop_back();              
    void insert(const Data* d, int num_node);  
    std::vector<std::pair<double, double>> get_Node(int num_node) const;
    int getCountNodes() const;
};

enum class SaveTo {
    show = 0,
    png = 1,
    jpeg = 2
};

class ProcessPulses : public DoubleLinkedList {
private:
    double normalizationCoef() const;

public:
    ProcessPulses();
    ProcessPulses(const char* fileName);
    ~ProcessPulses();

    std::vector<std::pair<double, double>> getPulse(int numNode, bool normalize = false) const;
    std::vector<std::pair<double, double>> averPulse(int startNode, int countNode) const;
    std::vector<std::pair<double, double>> diffPulse(int numNode) const;
    std::vector<std::pair<double, double>> intPulse(int numNode, int start, int end) const;

    double getRiseTime(int numNode) const;
    double getFailTime(int numNode) const;
    double getAmpl(int numNode) const;
    int getCountPulse() const;
    double getDurPulse(int numNode, int start, int end) const;
};

class Gnuplot {
public:
        void buildPulse(const std::vector<std::pair<double, double>>& pulse, SaveTo paramToSave);
};

#endif 
