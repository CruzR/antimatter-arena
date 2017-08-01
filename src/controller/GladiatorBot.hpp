#ifndef GLADIATOR_BOT_HPP
#define GLADIATOR_BOT_HPP

#include <random>
#include "sim/World.hpp"

class GladiatorBot
{
    public:
    GladiatorBot(World & world, int gladiator);
    void update();

    private:
    World & m_world;
    int m_gladiatorId;
    std::minstd_rand m_gen;
    std::uniform_real_distribution<> m_randPercentage;
    std::normal_distribution<> m_randAngleDisplacement;
};

#endif // GLADIATOR_BOT_HPP
