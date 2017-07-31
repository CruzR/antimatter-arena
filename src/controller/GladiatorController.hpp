#ifndef GLADIATOR_CONTROLLER_HPP
#define GLADIATOR_CONTROLLER_HPP

#include "SDL.h"
#include "sim/Gladiator.hpp"

class GladiatorController
{
    public:
    GladiatorController(Gladiator & gladiator, SDL_GameController * gamepad);
    void update();

    private:
    Gladiator & m_gladiator;
    SDL_GameController * m_gamepad;
    float m_lastAimDirection;
    float m_lastMoveDirection;
    float m_lastMoveSpeed;

    void getAimDirection();
    void getMoveParameters();
};

#endif // GLADIATOR_CONTROLLER_HPP
