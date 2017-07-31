#ifndef GLADIATOR_CONTROLLER_HPP
#define GLADIATOR_CONTROLLER_HPP

#include "SDL.h"
#include "sim/World.hpp"

class GladiatorController
{
    public:
    GladiatorController(World & world, int gladiator, SDL_GameController * gamepad);
    void update();

    private:
    World & m_world;
    int m_gladiatorId;
    SDL_GameController * m_gamepad;
    float m_lastAimDirection;
    float m_lastMoveDirection;
    float m_lastMoveSpeed;

    void getAimDirection();
    void getMoveParameters();
};

#endif // GLADIATOR_CONTROLLER_HPP
