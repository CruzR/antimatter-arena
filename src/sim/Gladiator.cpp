#include <cassert>
#include <cmath>
#include "sim/Gladiator.hpp"

Gladiator::Gladiator()
    :
    m_active(false),
    m_aimDirection(0.0f),
    m_speed(0.0f),
    m_moveDirection(0.0f),
    m_velocityX(0.0f),
    m_velocityY(0.0f),
    m_launchCooldown(0),
    m_jetpackCooldown(0),
    m_jetpackActive(false),
    m_jetpackActiveCooldown(0)
{
}

void Gladiator::initialize()
{
    m_active = true;
}

bool Gladiator::isActive() const
{
    return m_active;
}

float Gladiator::getAimDirection() const
{
    return m_aimDirection;
}

static float clampAngles(float angle)
{
    return std::fmod(angle, 360.0f);
}

void Gladiator::setAimDirection(float aimDirection)
{
    m_aimDirection = clampAngles(aimDirection);
}

float Gladiator::getSpeed() const
{
    return m_speed;
}

void Gladiator::setSpeed(float speed)
{
    assert(speed >= 0.0f);
    m_speed = speed;
    updateVelocity();
}

float Gladiator::getMoveDirection() const
{
    return m_moveDirection;
}

void Gladiator::setMoveDirection(float moveDirection)
{
    m_moveDirection = clampAngles(moveDirection);
    updateVelocity();
}

float Gladiator::getVelocityX() const
{
    return m_velocityX;
}

float Gladiator::getVelocityY() const
{
    return m_velocityY;
}

void Gladiator::updateVelocity()
{
    const float moveDirectionRad = (m_moveDirection / 360.0f) * 2.0f * M_PI;
    m_velocityX = std::cos(moveDirectionRad) * m_speed;
    m_velocityY = std::sin(moveDirectionRad) * m_speed;
}

bool Gladiator::canLaunchRocket() const
{
    return m_launchCooldown <= 0;
}

void Gladiator::launchRocket()
{
    m_launchCooldown = ROCKET_LAUNCH_COOLDOWN;
}

void Gladiator::tick()
{
    if (m_launchCooldown > 0)
    {
        m_launchCooldown -= 1;
    }

    if (m_jetpackCooldown > 0)
    {
        m_jetpackCooldown -= 1;
    }

    if (m_jetpackActiveCooldown > 0)
    {
        m_jetpackActiveCooldown -= 1;
        m_jetpackActive = m_jetpackActiveCooldown > 0;
    }
}

bool Gladiator::canEngageJetpack() const
{
    return m_jetpackCooldown <= 0;
}

void Gladiator::engageJetpack()
{
    m_jetpackCooldown = JETPACK_COOLDOWN;
    m_jetpackActive = true;
    m_jetpackActiveCooldown = JETPACK_ACTIVE_COOLDOWN;
}

bool Gladiator::isJetpackActive() const
{
    return m_jetpackActive;
}
