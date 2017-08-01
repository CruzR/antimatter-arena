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
#include "controller/GladiatorBot.hpp"


GladiatorBot::GladiatorBot(World & world, int gladiator)
    :
    m_world(world),
    m_gladiatorId(gladiator),
    m_gen(),
    m_randPercentage(0, 1),
    m_randAngleDisplacement(0.0, 5.0)
{
}

void GladiatorBot::update()
{
    Gladiator & g = m_world.getGladiator(m_gladiatorId);

    bool needJetpack = false;
    float aimDirection = 0.0f;
    float moveDirection = 0.0f;

    float x = g.getPositionX();
    float y = g.getPositionY();

    if (x < -20.0f || x > 20.0f || y < -20.0f || y > 20.0f)
    {
        moveDirection = std::atan2(y, x) / 2 / M_PI * 360.0f - 180.0f;

        if (g.canEngageJetpack())
        {
            aimDirection = moveDirection;
            g.setAimDirection(aimDirection);
            g.engageJetpack();
            return;
        }
        else
        {
            g.setMoveDirection(moveDirection);
            g.setSpeed(Gladiator::MOVEMENT_SPEED);
        }
    }

    if (g.canLaunchRocket())
    {
        for (int i = 0; i < m_world.getNumGladiators(); ++i)
        {
            if (i == m_gladiatorId)
            {
                continue;
            }

            if (!m_world.getGladiator(i).isAlive())
            {
                continue;
            }

            if (m_randPercentage(m_gen) >= 0.2)
            {
                continue;
            }

            float aimDirection = std::atan2(y - m_world.getGladiator(i).getPositionY(), x - m_world.getGladiator(i).getPositionX()) / 2 / M_PI * 360.0f - 180.0f + m_randAngleDisplacement(m_gen);
            g.setAimDirection(aimDirection);
            m_world.gladiatorLaunchProjectile(m_gladiatorId);
            break;
        }
    }
}
