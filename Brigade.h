#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Worker.h"

using namespace std;

class Brigade {
    string brigadeName;
    vector<Worker*> workers;
public:
    Brigade();
    Brigade(const string& name);
    ~Brigade();

    Brigade(const Brigade& other);
    Brigade& operator=(const Brigade& other);

    string getName() const { return brigadeName; }
    void setName(const string& n) { brigadeName = n; }

    void addWorker(Worker* w);
    bool removeWorker(int index);
    Worker* getWorker(int index);
    int workerCount() const { return (int)workers.size(); }
    const vector<Worker*>& getWorkers() const { return workers; }

    void print(ostream& os) const;
    void clear();
};