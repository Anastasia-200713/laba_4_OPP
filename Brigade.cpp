#include "Brigade.h"
#include <iomanip>

using namespace std;

Brigade::Brigade() : brigadeName("") {}
Brigade::Brigade(const string& name) : brigadeName(name) {}
Brigade::~Brigade() { clear(); }

Brigade::Brigade(const Brigade& other) {
    brigadeName = other.brigadeName;
    for (const Worker* w : other.workers) {
        if (const Builder* b = dynamic_cast<const Builder*>(w))
            workers.push_back(new Builder(*b));
        else if (const Engineer* e = dynamic_cast<const Engineer*>(w))
            workers.push_back(new Engineer(*e));
    }
}

Brigade& Brigade::operator=(const Brigade& other) {
    if (this == &other) return *this;
    clear();
    brigadeName = other.brigadeName;
    for (const Worker* w : other.workers) {
        if (const Builder* b = dynamic_cast<const Builder*>(w))
            workers.push_back(new Builder(*b));
        else if (const Engineer* e = dynamic_cast<const Engineer*>(w))
            workers.push_back(new Engineer(*e));
    }
    return *this;
}

void Brigade::clear() {
    for (Worker* w : workers) delete w;
    workers.clear();
}

void Brigade::addWorker(Worker* w) {
    if (w) workers.push_back(w);
}

bool Brigade::removeWorker(int index) {
    if (index < 0 || index >= (int)workers.size()) return false;
    delete workers[index];
    workers.erase(workers.begin() + index);
    return true;
}

Worker* Brigade::getWorker(int index) {
    if (index < 0 || index >= (int)workers.size()) return nullptr;
    return workers[index];
}

void Brigade::print(ostream& os) const {
    os << "\nБригада: " << (brigadeName.empty() ? "(Без названия)" : brigadeName)
        << " [Количество работников: " << workers.size() << "]\n";
    if (workers.empty()) {
        os << "  (нет сотрудников)\n";
        return;
    }
    os << "------------------------------------------------------------------------\n";
    os << left << setw(4) << "№"
        << "| " << setw(14) << "ФИО"
        << "| " << setw(10) << "Должн."
        << "| " << setw(10) << "Статус"
        << "| " << setw(10) << "Зарплата"
        << "| " << setw(10) << "Разряд/Надб." << "\n";
    os << "------------------------------------------------------------------------\n";

    int idx = 0;
    for (Worker* w : workers) {
        os << left << setw(4) << idx++;
        w->print(os);
        os << "\n";
    }
    os << "------------------------------------------------------------------------\n";
}