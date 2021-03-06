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

#include <algorithm>
#include <cassert>
#include <cmath>
#include "sim/Gladiator.hpp"

Gladiator::Gladiator()
    :
    Gladiator(0.0f, 0.0f, COLOR_RED)
{
}

Gladiator::Gladiator(float x, float y, Color color)
    :
    m_aimDirection(0.0f),
    m_speed(0.0f),
    m_moveDirection(0.0f),
    m_velocityX(0.0f),
    m_velocityY(0.0f),
    m_launchCooldown(0),
    m_jetpackCooldown(0),
    m_jetpackActive(false),
    m_jetpackActiveCooldown(0),
    m_positionX(x),
    m_positionY(y),
    m_inKnockbackMode(false),
    m_health(MAX_HEALTH),
    m_color(color)
{
}

Gladiator::Color Gladiator::getColor() const
{
    return m_color;
}

bool Gladiator::isAlive() const
{
    return m_health > 0;
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

    if (!m_jetpackActive && !m_inKnockbackMode)
    {
        m_speed = speed;
        updateVelocity();
    }
}

float Gladiator::getMoveDirection() const
{
    return m_moveDirection;
}

void Gladiator::setMoveDirection(float moveDirection)
{
    if (!m_jetpackActive && !m_inKnockbackMode)
    {
        m_moveDirection = clampAngles(moveDirection);
        updateVelocity();
    }
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
    return isAlive() && m_launchCooldown <= 0;
}

void Gladiator::launchRocket()
{
    if (!canLaunchRocket())
    {
        return;
    }

    m_launchCooldown = ROCKET_LAUNCH_COOLDOWN;
}

void Gladiator::tick()
{
    m_positionX += m_velocityX;
    m_positionY += m_velocityY;

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

        if (m_jetpackActiveCooldown == 0)
        {
            m_jetpackActive = false;
            m_speed = 0.0f;
            updateVelocity();
        }
    }

    if (m_knockbackTimeout > 0)
    {
        m_knockbackTimeout -= 1;

        if (m_knockbackTimeout == 0)
        {
            m_inKnockbackMode = false;
            m_speed = 0.0f;
            updateVelocity();
        }
    }

    if (m_positionX < -20.0f || m_positionY < -20.0f || m_positionX > 20.0f || m_positionY > 20.0f)
    {
        applyDamage(1);
    }
}

bool Gladiator::canEngageJetpack() const
{
    return !m_inKnockbackMode && m_jetpackCooldown <= 0;
}

void Gladiator::engageJetpack()
{
    if (!canEngageJetpack())
    {
        return;
    }

    m_speed = JETPACK_SPEED;
    m_moveDirection = m_aimDirection;
    updateVelocity();
    m_jetpackCooldown = JETPACK_COOLDOWN;
    m_jetpackActive = true;
    m_jetpackActiveCooldown = JETPACK_ACTIVE_COOLDOWN;
}

bool Gladiator::isJetpackActive() const
{
    return m_jetpackActive;
}

float Gladiator::getPositionX() const
{
    return m_positionX;
}

float Gladiator::getPositionY() const
{
    return m_positionY;
}

bool Gladiator::isInKnockbackMode() const
{
    return m_inKnockbackMode;
}

void Gladiator::knockBack(float energy, float direction)
{
    m_speed = energy * KNOCKBACK_SPEED;
    m_moveDirection = direction;
    updateVelocity();

    m_inKnockbackMode = true;
    m_knockbackTimeout = KNOCKBACK_TIMEOUT;
}

const int Gladiator::MAX_HEALTH = 250;

int Gladiator::getHealth() const
{
    return m_health;
}

void Gladiator::applyDamage(int amount)
{
    m_health = std::max(0, m_health - amount);
}
