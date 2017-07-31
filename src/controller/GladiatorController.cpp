#include <cmath>
#include "controller/GladiatorController.hpp"


GladiatorController::GladiatorController(World & world, int gladiator, SDL_GameController * gamepad)
    :
    m_world(world),
    m_gladiatorId(gladiator),
    m_gamepad(gamepad),
    m_lastAimDirection(0.0f)
{
}


void GladiatorController::update()
{
    getAimDirection();
    getMoveParameters();

    Gladiator & gladiator = m_world.getGladiator(m_gladiatorId);

    gladiator.setAimDirection(m_lastAimDirection);
    gladiator.setMoveDirection(m_lastMoveDirection);
    gladiator.setSpeed(m_lastMoveSpeed);

    if (SDL_GameControllerGetAxis(m_gamepad, SDL_CONTROLLER_AXIS_TRIGGERLEFT) > 30000)
    {
        if (gladiator.canEngageJetpack())
        {
            gladiator.engageJetpack();
        }
    }

    if (SDL_GameControllerGetAxis(m_gamepad, SDL_CONTROLLER_AXIS_TRIGGERRIGHT) > 30000)
    {
        if (gladiator.canLaunchRocket())
        {
            m_world.gladiatorLaunchProjectile(m_gladiatorId);
        }
    }
}


static bool aboveDeadzone(Sint16 x, Sint16 y)
{
    float xNorm = std::abs(x / 32768.0f);
    float yNorm = std::abs(y / 32768.0f);
    return xNorm + yNorm >= 0.125f;
}


void GladiatorController::getAimDirection()
{
    Sint16 axisX = SDL_GameControllerGetAxis(m_gamepad, SDL_CONTROLLER_AXIS_RIGHTX);
    Sint16 axisY = SDL_GameControllerGetAxis(m_gamepad, SDL_CONTROLLER_AXIS_RIGHTY);

    if (aboveDeadzone(axisX, axisY))
    {
        m_lastAimDirection = std::atan2(axisY, axisX) / 2 / M_PI * 360.0f;
    }
}


void GladiatorController::getMoveParameters()
{
    Sint16 axisX = SDL_GameControllerGetAxis(m_gamepad, SDL_CONTROLLER_AXIS_LEFTX);
    Sint16 axisY = SDL_GameControllerGetAxis(m_gamepad, SDL_CONTROLLER_AXIS_LEFTY);

    if (aboveDeadzone(axisX, axisY))
    {
        m_lastMoveDirection = std::atan2(axisY, axisX) / 2 / M_PI * 360.0f;
        float xNorm = axisX / 32768.0f;
        float yNorm = axisY / 32768.0f;
        m_lastMoveSpeed = std::sqrt(xNorm * xNorm + yNorm * yNorm) * Gladiator::MOVEMENT_SPEED;
    }
    else
    {
        m_lastMoveDirection = 0.0f;
        m_lastMoveSpeed = 0.0f;
    }
}
