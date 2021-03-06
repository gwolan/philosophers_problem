#pragma once

#include <string>
#include <cstdint>
#include <thread>
#include <memory>
#include <Miscellanous/Dice.hpp>
#include <Console/Graphics.hpp>
#include <PhilosophersProblem/Fork.hpp>
#include <PhilosophersProblem/DiningScheduler.hpp>


class Philosopher
{
    public:
    enum PhilosopherState
    {
        THINKING,
        EATING,
        WAITING_FOR_FORKS
    };

    Philosopher(uint32_t id, const std::string& philosopherName, Fork& leftFork,
                                                                 Fork& rightFork, DiningScheduler& diningScheduler,
                                                                                  std::unique_ptr<Graphics>& graphics);
    Philosopher(Philosopher&& other);
    ~Philosopher();

    uint32_t getId() const;
    std::string getName() const;
    PhilosopherState getState() const;
    std::string convertStateToString(PhilosopherState philosopherState);
    void startThinking();
    void startEating();


    private:
    void startDinner();
    void performStateTransitionTo(PhilosopherState philosopherState);
    bool stoppedDining();
    void aquireForks();

    uint32_t _id;
    const std::string _philosopherName;
    PhilosopherState _philosopherCurrentState;
    Fork& _leftFork;
    Fork& _rightFork;
    DiningScheduler& _diningScheduler;
    std::unique_ptr<Graphics>& _graphics;
    Dice _activityTimeDice;
    Dice _forkLeftOrRightDice;
    std::thread _philosopherThread;
};
