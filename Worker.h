#pragma once
#include <string>
#include <iostream>
using namespace std;
class Worker {
protected:
    string name;
    bool active;
    double salary;
public:
    Worker();
    Worker(const string& name, double salary, bool active = true);
    virtual ~Worker() {}

    string getName() const { return name; }
    bool getActive() const { return active; }
    double getSalary() const { return salary; }

    void setName(const string& n) { name = n; }
    void setSalary(double s) { salary = s; }
    void setActive(bool a) { active = a; }
    virtual string getType() const { return "Worker"; }
    virtual void print(ostream& os) const;
    virtual void saveToFile(ostream& os) const;
    

    bool operator<(const Worker& other) const { return name < other.name; }
    bool operator==(const Worker& other) const {
        return name == other.name && salary == other.salary && active == other.active;
    }
};

struct WorkerHash {
    size_t operator()(const Worker* w) const;
};

class Builder : public Worker {
    int qualification;
public:
    Builder();
    Builder(const string& name, double salary, int qualification, bool active = true);

    int getQualification() const { return qualification; }
    void setQualification(int q) { qualification = q; }

    string getType() const override { return "Builder"; }
    void print(ostream& os) const override;
    void saveToFile(ostream& os) const override;
};

class Engineer : public Worker {
    double allowance;
public:
    Engineer();
    Engineer(const string& name, double salary, double allowance, bool active = true);

    double getAllowance() const { return allowance; }
    void setAllowance(double a) { allowance = a; }

    string getType() const override { return "Engineer"; }
    void print(ostream& os) const override;
    void saveToFile(ostream& os) const override;
};

Worker* inputNewWorkerPointer();