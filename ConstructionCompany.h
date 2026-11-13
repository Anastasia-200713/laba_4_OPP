#pragma once
#include <string>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include "Brigade.h"
#include "Utils.h"
using namespace std;
class ConstructionCompany {
    string companyName;
    vector<Brigade> brigades;

public:
    map<string, Worker*> workerMap;
    set<Worker*> workerSet;
    multimap<double, Worker*> salaryMultimap;
    multiset<string> positionsMultiset;
    unordered_map<string, Worker*> workerUnorderedMap;
    unordered_set<Worker*, WorkerHash> workerUnorderedSet;
    unordered_multimap<double, Worker*> salaryUnorderedMultimap;
    unordered_multiset<string> positionsUnorderedMultiset;

    ConstructionCompany(const string& name);

    void addBrigade(const Brigade& b);
    void addBrigadeMenu();
    void removeBrigadeMenu();
    void editBrigadeMenu();
    void addWorkerToBrigadeMenu();
    void removeWorkerFromBrigadeMenu();
    void editWorkerInBrigadeMenu();
    void printAllCompany(ostream& os) const;

    void updateContainers();
};

template<typename MapT>
void manageMap(MapT& c, const string& title, bool isUnordered = false) {
    int ch;
    do {
        cout << "\n--- МЕНЮ [" << title << "] ---\n"
            << "1. Добавить\n"
            << "2. Удалить по ключу (ФИО)\n"
            << "3. Редактировать\n"
            << "4. Вывод на экран\n"
            << "5. Поиск по ключу\n"
            << "6. Сортировка\n"
            << "7. Фильтрация (по статусу)\n"
            << "8. Сохранить в файл\n"
            << "0. Назад\nВыбор: ";
        ch = inputInt();
        if (ch == 1) {
            Worker* w = inputNewWorkerPointer();
            c[w->getName()] = w;
            cout << "Элемент добавлен!\n";
        }
        else if (ch == 2) {
            cout << "Введите ФИО для удаления: ";
            string key = inputLine();
            size_t count = c.erase(key);
            cout << "Удалено элементов: " << count << "\n";
        }
        else if (ch == 3) {
            cout << "Введите ФИО для редактирования: ";
            string key = inputLine();
            auto it = c.find(key);
            if (it != c.end()) {
                cout << "Новая зарплата: ";
                it->second->setSalary(inputDouble());
                cout << "Обновлено!\n";
            }
            else cout << "Элемент не найден.\n";
        }
        else if (ch == 4) {
            if (c.empty()) cout << "Контейнер пуст.\n";
            else {
                cout << "------------------------------------------------------------------------\n";
                cout << left << setw(4) << "№"
                    << "| " << setw(14) << "ФИО"
                    << "| " << setw(10) << "Должн."
                    << "| " << setw(10) << "Статус"
                    << "| " << setw(10) << "Зарплата"
                    << "| " << setw(10) << "Разряд/Надб." << "\n";
                cout << "------------------------------------------------------------------------\n";
                int idx = 0;
                for (auto& p : c) {
                    cout << left << setw(4) << idx++;
                    p.second->print(cout);
                    cout << "\n";
                }
                cout << "------------------------------------------------------------------------\n";
            }
        }
        else if (ch == 5) {
            cout << "Введите ФИО для поиска: ";
            string key = inputLine();
            auto it = c.find(key);
            if (it != c.end()) {
                cout << "Найдено:\n";
                cout << "------------------------------------------------------------------------\n";
                cout << left << setw(16) << "ФИО" << "| " << setw(10) << "Должн." << "| " << setw(10) << "Статус" << "| " << setw(10) << "Зарплата" << "| " << setw(10) << "Разряд/Надб." << "\n";
                cout << "------------------------------------------------------------------------\n";
                it->second->print(cout);
                cout << "\n------------------------------------------------------------------------\n";
            }
            else cout << "Элемент не найден.\n";
        }
        else if (ch == 6) {
            if (!isUnordered) {
                cout << "[Сортировка MAP]: Элементы автоматически отсортированы по ключу (ФИО).\n";
            }
            else {
                cout << "[Сортировка UNORDERED_MAP]: Копирование в вектор для сортировки:\n";
                vector<pair<string, Worker*>> vec(c.begin(), c.end());
                sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) { return a.first < b.first; });
                cout << "------------------------------------------------------------------------\n";
                cout << left << setw(4) << "№"
                    << "| " << setw(14) << "ФИО"
                    << "| " << setw(10) << "Должн."
                    << "| " << setw(10) << "Статус"
                    << "| " << setw(10) << "Зарплата"
                    << "| " << setw(10) << "Разряд/Надб." << "\n";
                cout << "------------------------------------------------------------------------\n";
                int idx = 0;
                for (const auto& p : vec) {
                    cout << left << setw(4) << idx++;
                    p.second->print(cout);
                    cout << "\n";
                }
                cout << "------------------------------------------------------------------------\n";
            }
        }
        else if (ch == 7) {
            cout << "Показать: 1 - Активных, 0 - В отпуске: ";
            bool act = (inputInt() == 1);

            bool found = false;
            for (auto& p : c) {
                if (p.second->getActive() == act) {
                    found = true;
                    break;
                }
            }

            if (!found) {
                cout << "Ничего не найдено.\n";
            }

            else {
                cout << "------------------------------------------------------------------------\n";
                cout << left << setw(4) << "№"
                    << "| " << setw(14) << "ФИО"
                    << "| " << setw(10) << "Должн."
                    << "| " << setw(10) << "Статус"
                    << "| " << setw(10) << "Зарплата"
                    << "| " << setw(10) << "Разряд/Надб." << "\n";
                cout << "------------------------------------------------------------------------\n";
                int idx = 0;
                for (auto& p : c) {
                    if (p.second->getActive() == act) {
                        cout << left << setw(4) << idx++;
                        p.second->print(cout);
                        cout << "\n";
                    }
                }
                cout << "------------------------------------------------------------------------\n";
            }
        }
        else if (ch == 8) {
            ofstream f(title + "_data.txt");
            for (auto& p : c) {
                p.second->saveToFile(f);
                f << "\n";
            }
            f.close();
            cout << "Сохранено в файл " << title << "_data.txt\n";
        }
    } while (ch != 0);
}

template<typename SetT>
void manageSet(SetT& c, const string& title, bool isUnordered = false) {
    int ch;
    do {
        cout << "\n--- МЕНЮ [" << title << "] ---\n"
            << "1. Добавить\n"
            << "2. Удалить по имени\n"
            << "3. Редактировать\n"
            << "4. Вывод на экран\n"
            << "5. Поиск\n"
            << "6. Сортировка\n"
            << "7. Фильтрация (по мин. зарплате)\n"
            << "8. Сохранить в файл\n"
            << "0. Назад\nВыбор: ";
        ch = inputInt();

        if (ch == 1) {
            Worker* w = inputNewWorkerPointer();

            auto it = find_if(c.begin(), c.end(), [&](Worker* existing) {
                return existing->getName() == w->getName()
                    && existing->getSalary() == w->getSalary()
                    && existing->getActive() == w->getActive();
                });

            if (it != c.end()) {
                cout << "Такой работник уже есть в " << title << "! Добавление отменено.\n";
                delete w;
            }
            else {
                c.insert(w);
                cout << "Добавлено!\n";
            }
        }
        else if (ch == 2) {
            cout << "Введите ФИО для удаления: ";
            string name = inputLine();
            auto it = find_if(c.begin(), c.end(), [&](Worker* w) {
                return w->getName().find(name) != string::npos;
                });
            if (it != c.end()) {
                c.erase(it);
                cout << "Удалено.\n";
            }
            else cout << "Не найдено.\n";
        }
        else if (ch == 3) {
            cout << "Введите ФИО для редактирования: ";
            string name = inputLine();
            auto it = find_if(c.begin(), c.end(), [&](Worker* w) {
                return w->getName().find(name) != string::npos;
                });
            if (it != c.end()) {
                cout << "Новая зарплата: ";
                (*it)->setSalary(inputDouble());
                cout << "Обновлено!\n";
            }
            else cout << "Не найдено.\n";
        }
        else if (ch == 4) {
            if (c.empty()) cout << "Контейнер пуст.\n";
            else {
                cout << "------------------------------------------------------------------------\n";
                cout << left << setw(4) << "№" << "| " << setw(14) << "ФИО" << "| " << setw(10) << "Должн." << "| " << setw(10) << "Статус" << "| " << setw(10) << "Зарплата" << "| " << setw(10) << "Разряд/Надб." << "\n";
                cout << "------------------------------------------------------------------------\n";
                int idx = 0;
                for (auto w : c) {
                    cout << left << setw(4) << idx++;
                    w->print(cout);
                    cout << "\n";
                }
                cout << "------------------------------------------------------------------------\n";
            }
        }
        else if (ch == 5) {
            cout << "Введите ФИО для поиска: ";
            string name = inputLine();
            auto it = find_if(c.begin(), c.end(), [&](Worker* w) {
                return w->getName().find(name) != string::npos;
                });
            if (it != c.end()) {
                cout << "Найдено:\n";
                (*it)->print(cout);
                cout << "\n";
            }
            else cout << "Не найдено.\n";
        }
        else if (ch == 6) {
            if (!isUnordered) {
                cout << "[Сортировка SET]: Автоматически отсортировано по operator< (ФИО).\n";
            }
            else {
                cout << "[Сортировка UNORDERED_SET]: Копирование в вектор для сортировки:\n";
                vector<Worker*> vec(c.begin(), c.end());
                sort(vec.begin(), vec.end(), [](Worker* a, Worker* b) { return a->getName() < b->getName(); });
                int idx = 0;
                for (auto w : vec) {
                    cout << left << setw(4) << idx++;
                    w->print(cout);
                    cout << "\n";
                }
            }
        }
        else if (ch == 7) {
            cout << "Введите минимальную зарплату: ";
            double minS = inputDouble();
            bool found = false;
            int idx = 0;
            for (auto w : c) {
                if (w->getSalary() >= minS) {
                    cout << left << setw(4) << idx++;
                    w->print(cout);
                    cout << "\n";
                    found = true;
                }
            }
            if (!found) cout << "Ничего не найдено.\n";
        }
        else if (ch == 8) {
            ofstream f(title + "_data.txt");
            for (auto w : c) {
                w->saveToFile(f);
                f << "\n";
            }
            f.close();
            cout << "Сохранено в файл " << title << "_data.txt\n";
        }
    } while (ch != 0);
}

template<typename MultiMapT>
void manageMultimap(MultiMapT& c, const string& title, bool isUnordered = false) {
    int ch;
    do {
        cout << "\n--- МЕНЮ [" << title << "] ---\n"
            << "1. Добавить\n"
            << "2. Удалить по зарплате (ключу)\n"
            << "3. Редактировать по зарплате\n"
            << "4. Вывод на экран\n"
            << "5. Поиск (equal_range)\n"
            << "6. Сортировка\n"
            << "7. Фильтрация (по должности)\n"
            << "8. Сохранить в файл\n"
            << "0. Назад\nВыбор: ";
        ch = inputInt();
        if (ch == 1) {
            Worker* w = inputNewWorkerPointer();
            c.insert({ w->getSalary(), w });
            cout << "Добавлено!\n";
        }
        else if (ch == 2) {
            cout << "Введите зарплату для удаления: ";
            double sal = inputDouble();
            size_t cnt = c.erase(sal);
            cout << "Удалено записей: " << cnt << "\n";
        }
        else if (ch == 3) {
            cout << "Введите зарплату для редактирования: ";
            double sal = inputDouble();
            auto range = c.equal_range(sal);
            if (range.first != range.second) {
                for (auto it = range.first; it != range.second; ++it) {
                    cout << "Сотрудник: " << it->second->getName() << ". Новая ЗП: ";
                    it->second->setSalary(inputDouble());
                }
                cout << "Обновлено!\n";
            }
            else cout << "Записей с такой зарплатой не найдено.\n";
        }
        else if (ch == 4) {
            if (c.empty()) cout << "Контейнер пуст.\n";
            else {
                cout << "------------------------------------------------------------------------\n";
                cout << left << setw(4) << "№"
                    << "| " << setw(14) << "ФИО"
                    << "| " << setw(10) << "Должн."
                    << "| " << setw(10) << "Статус"
                    << "| " << setw(10) << "Зарплата"
                    << "| " << setw(10) << "Разряд/Надб." << "\n";
                cout << "------------------------------------------------------------------------\n";
                int idx = 0;
                for (const auto& p : c) {
                    cout << left << setw(4) << idx++;
                    p.second->print(cout);
                    cout << "\n";
                }
                cout << "------------------------------------------------------------------------\n";
            }
        }
        else if (ch == 5) {
            cout << "Введите ЗП для поиска: ";
            double sal = inputDouble();
            auto range = c.equal_range(sal);

            if (range.first == range.second) {
                cout << "Ничего не найдено.\n";
            }
            else {

                cout << "------------------------------------------------------------------------\n";
                cout << left << setw(4) << "№"
                    << "| " << setw(14) << "ФИО"
                    << "| " << setw(10) << "Должн."
                    << "| " << setw(10) << "Статус"
                    << "| " << setw(10) << "Зарплата"
                    << "| " << setw(10) << "Разряд/Надб." << "\n";
                cout << "------------------------------------------------------------------------\n";
                int idx = 0;
                for (auto it = range.first; it != range.second; ++it) {
                    cout << left << setw(4) << idx++;
                    it->second->print(cout);
                    cout << "\n";
                }
                cout << "------------------------------------------------------------------------\n";
            }
        }
        else if (ch == 6) {
            if (!isUnordered) {
                cout << "[Сортировка MULTIMAP]: Упорядочено по ключу-зарплате.\n";
            }
            else {
                cout << "[Сортировка UNORDERED_MULTIMAP]: Копирование в вектор и сортировка по ЗП:\n";
                vector<pair<double, Worker*>> vec(c.begin(), c.end());
                sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) { return a.first < b.first; });
                cout << "------------------------------------------------------------------------\n";
                cout << left << setw(4) << "№"
                    << "| " << setw(14) << "ФИО"
                    << "| " << setw(10) << "Должн."
                    << "| " << setw(10) << "Статус"
                    << "| " << setw(10) << "Зарплата"
                    << "| " << setw(10) << "Разряд/Надб." << "\n";
                cout << "------------------------------------------------------------------------\n";
                int idx = 0;
                for (const auto& p : vec) {
                    cout << left << setw(4) << idx++;
                    p.second->print(cout);
                    cout << "\n";
                }
                cout << "------------------------------------------------------------------------\n";
            }
        }
        else if (ch == 7) {
            cout << "Введите тип должности (Builder/Engineer): ";
            string t = inputLine();
            bool found = false;
            cout << "------------------------------------------------------------------------\n";
            cout << left << setw(4) << "№"
                << "| " << setw(14) << "ФИО"
                << "| " << setw(10) << "Должн."
                << "| " << setw(10) << "Статус"
                << "| " << setw(10) << "Зарплата"
                << "| " << setw(10) << "Разряд/Надб." << "\n";
            cout << "------------------------------------------------------------------------\n";
            int idx = 0;
            for (const auto& p : c) {
                if (p.second->getType() == t) {
                    cout << left << setw(4) << idx++;
                    p.second->print(cout);
                    cout << "\n";
                    found = true;
                }
            }
            cout << "------------------------------------------------------------------------\n";
            if (!found) cout << "Ничего не найдено.\n";
        }
        else if (ch == 8) {
            ofstream f(title + "_data.txt");
            for (const auto& p : c) {
                f << p.first << ";";
                p.second->saveToFile(f);
                f << "\n";
            }
            f.close();
            cout << "Сохранено в файл " << title << "_data.txt\n";
        }
    } while (ch != 0);
}

template<typename MultiSetT>
void manageMultiset(MultiSetT& c, const string& title, bool isUnordered = false) {
    int ch;
    do {
        cout << "\n--- МЕНЮ [" << title << "] ---\n"
            << "1. Добавить элемент\n"
            << "2. Удалить по значению\n"
            << "3. Редактировать (замена)\n"
            << "4. Вывод на экран\n"
            << "5. Подсчет (count)\n"
            << "6. Сортировка\n"
            << "7. Фильтрация (уникальные элементы)\n"
            << "8. Сохранить в файл\n"
            << "0. Назад\nВыбор: ";
        ch = inputInt();
        if (ch == 1) {
            cout << "Введите строку (должность): ";
            string val = inputLine();
            c.insert(val);
            cout << "Добавлено!\n";
        }
        else if (ch == 2) {
            cout << "Введите значение для удаления: ";
            string val = inputLine();
            size_t cnt = c.erase(val);
            cout << "Удалено записей: " << cnt << "\n";
        }
        else if (ch == 3) {
            cout << "Введите старое значение для замены: ";
            string oldV = inputLine();
            size_t cnt = c.count(oldV);
            if (cnt > 0) {
                c.erase(oldV);
                cout << "Введите новое значение: ";
                string newV = inputLine();
                for (size_t i = 0; i < cnt; ++i) c.insert(newV);
                cout << "Заменено!\n";
            }
            else cout << "Значение не найдено.\n";
        }
        else if (ch == 4) {
            if (c.empty()) cout << "Контейнер пуст.\n";
            else {
                cout << "------------------------------------------------------------------------\n";
                cout << left << setw(4) << "№" << "| Должность\n";
                cout << "------------------------------------------------------------------------\n";
                int idx = 0;
                for (const auto& item : c) {
                    cout << left << setw(4) << idx++ << "| " << item << "\n";
                }
                cout << "------------------------------------------------------------------------\n";
            }
        }
        else if (ch == 5) {
            cout << "Введите должность для подсчета: ";
            string val = inputLine();
            cout << "Количество вхождений: " << c.count(val) << "\n";
        }
        else if (ch == 6) {
            if (!isUnordered) {
                cout << "[Сортировка MULTISET]: Автоматически отсортировано по алфавиту.\n";
            }
            else {
                cout << "[Сортировка UNORDERED_MULTISET]: Копирование в вектор и сортировка:\n";
                vector<string> vec(c.begin(), c.end());
                sort(vec.begin(), vec.end());
                for (const auto& s : vec) cout << "* " << s << "\n";
            }
        }
        else if (ch == 7) {
            set<string> uniqueItems(c.begin(), c.end());
            cout << "Уникальные элементы в контейнере:\n";
            for (const auto& u : uniqueItems) cout << "-> " << u << "\n";
        }
        else if (ch == 8) {
            ofstream f(title + "_data.txt");
            for (const auto& item : c) {
                f << item << "\n";
            }
            f.close();
            cout << "Сохранено в файл " << title << "_data.txt\n";
        }
    } while (ch != 0);
}