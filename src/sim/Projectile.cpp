/*
 * Copyright 2017 Thomas Glamsch
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <cmath>
#include "sim/Projectile.hpp"


Projectile::Projectile()
    :
    Projectile(0.0f, 0.0f, 0.0f)
{
}

Projectile::Projectile(float x, float y, float moveDirection)
    :
    m_positionX(x),
    m_positionY(y),
    m_moveDirection(moveDirection),
    m_explosionTimout(EXPLODE_TIMEOUT)
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

    if (m_explosionTimout > 0)
    {
        m_explosionTimout -= 1;
    }
}

bool Projectile::isDestroyed() const
{
    return m_explosionTimout <= 0;
}

void Projectile::destroy()
{
    m_explosionTimout = 0;
}
