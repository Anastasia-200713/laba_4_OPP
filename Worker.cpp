#include "Worker.h"
#include "Utils.h"
#include <iomanip>

using namespace std;

Worker::Worker() : name(""), active(true), salary(0.0) {}
Worker::Worker(const string& name, double salary, bool active)
    : name(name), active(active), salary(salary) {
}

void Worker::print(ostream& os) const {
    os << left
        << setw(16) << name
        << "| " << setw(10) << getType()
        << "| " << setw(10) << (active ? "Активен" : "Отпуск")
        << "| " << setw(10) << fixed << setprecision(2) << salary;
}

void Worker::saveToFile(ostream& os) const {
    os << name << ";" << getType() << ";" << (active ? "Active" : "Vacation") << ";" << salary;
}

size_t WorkerHash::operator()(const Worker* w) const {
    if (!w) return 0;
    return hash<string>()(w->getName()) ^ hash<double>()(w->getSalary());
}

Builder::Builder() : Worker(), qualification(1) {}
Builder::Builder(const string& name, double salary, int qualification, bool active)
    : Worker(name, salary, active), qualification(qualification) {
}

void Builder::print(ostream& os) const {
    Worker::print(os);
    os << "| " << setw(10) << qualification;
}

void Builder::saveToFile(ostream& os) const {
    Worker::saveToFile(os);
    os << ";" << qualification;
}

Engineer::Engineer() : Worker(), allowance(0.0) {}
Engineer::Engineer(const string& name, double salary, double allowance, bool active)
    : Worker(name, salary, active), allowance(allowance) {
}

void Engineer::print(ostream& os) const {
    Worker::print(os);
    os << "| " << setw(10) << fixed << setprecision(2) << allowance;
}

void Engineer::saveToFile(ostream& os) const {
    Worker::saveToFile(os);
    os << ";" << allowance;
}

Worker* inputNewWorkerPointer() {
    cout << "Выберите тип сотрудника (1 - Строитель, 2 - Инженер): ";
    int type = inputInt();
    cout << "ФИО сотрудника: "; string name = inputLine();
    cout << "Зарплата: "; double salary = inputDouble();
    cout << "Статус (1 - Активен, 0 - В отпуске): "; bool active = (inputInt() == 1);

    if (type == 1) {
        cout << "Разряд (1-6): "; int q = inputInt();
        return new Builder(name, salary, q, active);
    }
    else {
        cout << "Разрядная надбавка: "; double a = inputDouble();
        return new Engineer(name, salary, a, active);
    }
}