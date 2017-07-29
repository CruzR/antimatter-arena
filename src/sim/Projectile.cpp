#include <cmath>
#include "sim/Projectile.hpp"


Projectile::Projectile()
    :
    m_positionX(0.0f),
    m_positionY(0.0f),
    m_moveDirection(0.0f)
{
    updateVelocity();
}

float Projectile::getPositionX() const
{
    return m_positionX;
}

float Projectile::getPositionY() const
{
    return m_positionY;
}

void Projectile::setPosition(float x, float y)
{
    m_positionX = x;
    m_positionY = y;
}

float Projectile::getMoveDirection() const
{
    return m_moveDirection;
}

void Projectile::setMoveDirection(float moveDirection)
{
    m_moveDirection = moveDirection;
    updateVelocity();
}

float Projectile::getVelocityX() const
{
    return m_velocityX;
}

float Projectile::getVelocityY() const
{
    return m_velocityY;
}

void Projectile::updateVelocity()
{
    const float moveDirectionRad = (m_moveDirection / 360.0f) * 2 * M_PI;
    m_velocityX = std::cos(moveDirectionRad) * SPEED;
    m_velocityY = std::sin(moveDirectionRad) * SPEED;
}

void Projectile::tick()
{
    m_positionX += m_velocityX;
    m_positionY += m_velocityY;
}
