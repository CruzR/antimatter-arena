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
