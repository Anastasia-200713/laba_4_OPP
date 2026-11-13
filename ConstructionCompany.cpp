#include "ConstructionCompany.h"
#include <iostream>

using namespace std;

ConstructionCompany::ConstructionCompany(const string& name) : companyName(name) {}

void ConstructionCompany::addBrigade(const Brigade& b) {
    brigades.push_back(b);
    updateContainers();
}

void ConstructionCompany::updateContainers() {
    workerMap.clear();
    workerSet.clear();
    salaryMultimap.clear();
    positionsMultiset.clear();
    workerUnorderedMap.clear();
    workerUnorderedSet.clear();
    salaryUnorderedMultimap.clear();
    positionsUnorderedMultiset.clear();

    for (auto& b : brigades) {
        for (Worker* w : b.getWorkers()) {
            if (!w) continue;
            workerMap[w->getName()] = w;
            workerSet.insert(w);
        
            salaryMultimap.insert({ w->getSalary(), w });
            positionsMultiset.insert(w->getType());

            workerUnorderedMap[w->getName()] = w;
            workerUnorderedSet.insert(w);
            salaryUnorderedMultimap.insert({ w->getSalary(), w });
            positionsUnorderedMultiset.insert(w->getType());
        }
    }
}

void ConstructionCompany::addBrigadeMenu() {
    cout << "Введите название новой бригады: ";
    string name = inputLine();
    brigades.push_back(Brigade(name));
    updateContainers();
    cout << "Бригада зарегистрирована!\n";
}

void ConstructionCompany::removeBrigadeMenu() {
    if (brigades.empty()) { cout << "Список бригад пуст.\n"; return; }
    for (size_t i = 0; i < brigades.size(); ++i) {
        cout << i << ". " << brigades[i].getName() << "\n";
    }
    cout << "Введите номер бригады для удаления: ";
    int idx = inputInt();
    if (idx >= 0 && idx < (int)brigades.size()) {
        brigades.erase(brigades.begin() + idx);
        updateContainers();
        cout << "Бригада удалена.\n";
    }
    else cout << "Неверный индекс.\n";
}

void ConstructionCompany::editBrigadeMenu() {
    if (brigades.empty()) { cout << "Список бригад пуст.\n"; return; }
    for (size_t i = 0; i < brigades.size(); ++i) {
        cout << i << ". " << brigades[i].getName() << "\n";
    }
    cout << "Введите номер бригады для редактирования: ";
    int idx = inputInt();
    if (idx >= 0 && idx < (int)brigades.size()) {
        cout << "Текущее имя: " << brigades[idx].getName() << "\n";
        cout << "Введите новое имя: ";
        brigades[idx].setName(inputLine());
        cout << "Название обновлено.\n";
    }
    else cout << "Неверный индекс.\n";
}

void ConstructionCompany::addWorkerToBrigadeMenu() {
    if (brigades.empty()) { cout << "Сначала создайте хотя бы одну бригаду!\n"; return; }
    for (size_t i = 0; i < brigades.size(); ++i) {
        cout << i << ". " << brigades[i].getName() << "\n";
    }
    cout << "Выберите номер бригады: ";
    int idx = inputInt();
    if (idx >= 0 && idx < (int)brigades.size()) {
        Worker* w = inputNewWorkerPointer();
        brigades[idx].addWorker(w);
        updateContainers();
        cout << "Сотрудник добавлен в бригаду.\n";
    }
    else cout << "Неверный индекс.\n";
}

void ConstructionCompany::removeWorkerFromBrigadeMenu() {
    if (brigades.empty()) { cout << "Нет бригад.\n"; return; }
    for (size_t i = 0; i < brigades.size(); ++i) {
        cout << i << ". " << brigades[i].getName() << "\n";
    }
    cout << "Выберите номер бригады: ";
    int bIdx = inputInt();
    if (bIdx >= 0 && bIdx < (int)brigades.size()) {
        brigades[bIdx].print(cout);
        if (brigades[bIdx].workerCount() == 0) return;
        cout << "Введите номер работника для удаления: ";
        int wIdx = inputInt();
        if (brigades[bIdx].removeWorker(wIdx)) {
            updateContainers();
            cout << "Работник удален.\n";
        }
        else cout << "Неверный номер работника.\n";
    }
    else cout << "Неверный индекс бригады.\n";
}

void ConstructionCompany::editWorkerInBrigadeMenu() {
    if (brigades.empty()) { cout << "Нет бригад.\n"; return; }
    for (size_t i = 0; i < brigades.size(); ++i) {
        cout << i << ". " << brigades[i].getName() << "\n";
    }
    cout << "Выберите номер бригады: ";
    int bIdx = inputInt();
    if (bIdx >= 0 && bIdx < (int)brigades.size()) {
        brigades[bIdx].print(cout);
        if (brigades[bIdx].workerCount() == 0) return;
        cout << "Введите номер работника для редактирования: ";
        int wIdx = inputInt();
        Worker* w = brigades[bIdx].getWorker(wIdx);
        if (w) {
            cout << "Новое ФИО: "; w->setName(inputLine());
            cout << "Новая зарплата: "; w->setSalary(inputDouble());
            cout << "Статус (1 - Активен, 0 - Отпуск): "; w->setActive(inputInt() == 1);
            if (Builder* b = dynamic_cast<Builder*>(w)) {
                cout << "Новый разряд: "; b->setQualification(inputInt());
            }
            else if (Engineer* e = dynamic_cast<Engineer*>(w)) {
                cout << "Новая надбавка: "; e->setAllowance(inputDouble());
            }
            updateContainers();
            cout << "Данные работника обновлены.\n";
        }
        else cout << "Работник не найден.\n";
    }
    else cout << "Неверный индекс.\n";
}

void ConstructionCompany::printAllCompany(ostream& os) const {
    os << "\n========================================================================\n";
    os << " ОРГАНИЗАЦИЯ: " << companyName << "\n";
    os << "========================================================================\n";
    if (brigades.empty()) os << "(нет зарегистрированных бригад)\n";
    for (size_t i = 0; i < brigades.size(); ++i) {
        os << "[Бригада #" << i << "]";
        brigades[i].print(os);
    }
    os << "========================================================================\n";
}