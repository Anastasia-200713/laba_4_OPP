#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <clocale>
#include <windows.h>
#include "ConstructionCompany.h"
#include "Utils.h"

using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    ConstructionCompany company("Монолит-Строй");

    Brigade b1("Бригада монолитчиков");
    b1.addWorker(new Builder("Иванов И. И.", 1600.0, 5, true));
    b1.addWorker(new Builder("Петров П. П.", 1300.0, 4, true));

    Brigade b2("Инженерный отдел");
    b2.addWorker(new Engineer("Смирнова Е. А.", 2200.0, 450.0, true));

    company.addBrigade(b1);
    company.addBrigade(b2);
    company.updateContainers();

    vector<pair<string, function<void()>>> menu = {
        {"Показать всю организацию и структуру бригад", [&]() { company.printAllCompany(cout); }},
        {"Добавить новую бригаду",                      [&]() { company.addBrigadeMenu(); }},
        {"Удалить бригаду",                             [&]() { company.removeBrigadeMenu(); }},
        {"Редактировать название бригады",              [&]() { company.editBrigadeMenu(); }},
        {"Добавить работника в бригаду",                [&]() { company.addWorkerToBrigadeMenu(); }},
        {"Удалить работника из бригады",                [&]() { company.removeWorkerFromBrigadeMenu(); }},
        {"Редактировать данные работника в бригаде",    [&]() { company.editWorkerInBrigadeMenu(); }},
        {"MAP (std::map)",                              [&]() { manageMap(company.workerMap, "MAP", false); }},
        {"SET (std::set)",                              [&]() { manageSet(company.workerSet, "SET", false); }},
        {"MULTIMAP (std::multimap)",                    [&]() { manageMultimap(company.salaryMultimap, "MULTIMAP", false); }},
        {"MULTISET (std::multiset)",                    [&]() { manageMultiset(company.positionsMultiset, "MULTISET", false); }},
        {"UNORDERED_MAP (std::unordered_map)",          [&]() { manageMap(company.workerUnorderedMap, "UNORDERED_MAP", true); }},
        {"UNORDERED_SET (std::unordered_set)",          [&]() { manageSet(company.workerUnorderedSet, "UNORDERED_SET", true); }},
        {"UNORDERED_MULTIMAP (std::unordered_multimap)",[&]() { manageMultimap(company.salaryUnorderedMultimap, "UNORDERED_MULTIMAP", true); }},
        {"UNORDERED_MULTISET (std::unordered_multiset)",[&]() { manageMultiset(company.positionsUnorderedMultiset, "UNORDERED_MULTISET", true); }},
        
        {"Сортировка работников по убыванию зарплаты", [&]() {
            vector<Worker*> all;
            for (auto& p : company.workerMap) all.push_back(p.second);
            sort(all.begin(), all.end(), [](Worker* a, Worker* b) { return a->getSalary() > b->getSalary(); });
            cout << "\nСписок работников (от наибольшей зарплаты к наименьшей):\n";
            for (auto w : all) { w->print(cout); cout << "\n"; }
        }}
    };
  

    int choice = -1;
    do {
        cout << "\n===================================================================\n";
        cout << " ЛАБОРАТОРНАЯ РАБОТА №4: АССОЦИАТИВНЫЕ И НЕУПОРЯДОЧЕННЫЕ КОНТЕЙНЕРЫ STL\n";
        cout << " Предметная область: Учет данных о работниках строительной организации\n";
        cout << "===================================================================\n";

        for (size_t i = 0; i < menu.size(); ++i) {
            cout << " " << i + 1 << ". " << menu[i].first << "\n";
        }
        cout << " 0. Выход из программы\n";
        cout << "Ваш выбор: ";

        choice = inputInt();

        if (choice > 0 && choice <= (int)menu.size()) {
            menu[choice - 1].second();
        }
        else if (choice != 0) {
            cout << "Неверный выбор! Попробуйте снова.\n";
        }
    } while (choice != 0);

    cout << "Завершение работы программы.\n";
    return 0;
}