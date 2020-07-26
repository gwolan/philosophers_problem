#pragma once

#include <string>
#include <map>
#include <cstdint>
#include <memory>
#include <PhilosophersProblem/Fork.hpp>
#include <PhilosophersProblem/Philosopher.hpp>
#include <Console/Graphics.hpp>


class DiningTable
{
    public:
    DiningTable(uint32_t philosophersCount);
    ~DiningTable();

    void startDinner();


    private:
    void initTable();
    void initTableRows(std::vector<std::vector<std::string>>& rows);
    void createForks(uint32_t philosophersCount);
    void createPhilosophers(uint32_t philosophersCount);

    std::map<std::string, Fork> _forksMap;
    std::map<std::string, Philosopher> _philosophersMap;
    std::unique_ptr<Graphics> _diningTableStateGraphicsPtr;
};
