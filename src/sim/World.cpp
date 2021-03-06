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
#include "sim/World.hpp"


World::World()
{
}

int World::getNumGladiators() const
{
    return m_gladiators.size();
}

int World::getNumProjectiles() const
{
    return m_projectiles.size();
}

int World::spawnGladiatorAt(float x, float y)
{
    return spawnGladiatorAt(x, y, Gladiator::COLOR_RED);
}

int World::spawnGladiatorAt(float x, float y, Gladiator::Color color)
{
    int newId = m_gladiators.size();
    m_gladiators.emplace_back(x, y, color);
    return newId;
}

Gladiator & World::getGladiator(int id)
{
    return m_gladiators.at(id);
}

int World::spawnProjectileAt(float x, float y, float rot)
{
    int newId = m_projectiles.size();
    m_projectiles.emplace_back(x, y, rot);
    return newId;
}

Projectile & World::getProjectile(int id)
{
    return m_projectiles.at(id);
}

void World::tick()
{
    std::vector<Explosion> liveExplosions;
    liveExplosions.reserve(m_explosions.size());

    for (Explosion & explosion : m_explosions)
    {
        explosion.tick();
        if (!explosion.isDestroyed())
        {
            liveExplosions.push_back(explosion);
        }
    }

    m_explosions = liveExplosions;

    std::vector<Projectile> liveProjectiles;
    liveProjectiles.reserve(m_projectiles.size());

    for (Projectile & projectile : m_projectiles)
    {
        projectile.tick();
        if (!projectile.isDestroyed())
        {
            liveProjectiles.push_back(projectile);
        }
        else
        {
            spawnExplosionAt(projectile.getPositionX(), projectile.getPositionY());
        }
    }

    m_projectiles = liveProjectiles;

    for (Gladiator & gladiator : m_gladiators)
    {
        gladiator.tick();
    }

    performCollisionChecks();
}

void World::gladiatorLaunchProjectile(int id)
{
    Gladiator & glad = m_gladiators.at(id);

    if (!glad.canLaunchRocket())
    {
        return;
    }

    float x = glad.getPositionX() + std::cos(glad.getAimDirection() / 360.0f * M_PI * 2) * Gladiator::PROJECTILE_DISTANCE;
    float y = glad.getPositionY() + std::sin(glad.getAimDirection() / 360.0f * M_PI * 2) * Gladiator::PROJECTILE_DISTANCE;
    glad.launchRocket();
    spawnProjectileAt(x, y, glad.getAimDirection());
}

std::vector<Gladiator> & World::getGladiators()
{
    return m_gladiators;
}

int World::getNumExplosions() const
{
    return m_explosions.size();
}

int World::spawnExplosionAt(float x, float y)
{
    int newId = m_explosions.size();
    m_explosions.emplace_back(x, y);
    return newId;
}

Explosion & World::getExplosion(int id)
{
    return m_explosions.at(id);
}

void World::performCollisionChecks()
{
    for (int i = 0; m_projectiles.size() > 0 && i < m_projectiles.size() - 1; ++i)
    {
        float x0 = m_projectiles.at(i).getPositionX();
        float y0 = m_projectiles.at(i).getPositionY();

        for (int j = i + 1; j < m_projectiles.size(); ++j)
        {
            float x1 = m_projectiles.at(j).getPositionX();
            float y1 = m_projectiles.at(j).getPositionY();
            float distSquared = (x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1);

            if (distSquared < 4 * Projectile::COLLISION_RADIUS * Projectile::COLLISION_RADIUS)
            {
                if (!m_projectiles.at(i).isDestroyed())
                {
                    m_projectiles.at(i).destroy();
                    spawnExplosionAt(x0, y0);
                }

                if (!m_projectiles.at(j).isDestroyed())
                {
                    m_projectiles.at(j).destroy();
                    spawnExplosionAt(x1, y1);
                }
            }
        }
    }

    std::vector<Projectile> liveProjectiles;
    liveProjectiles.reserve(m_projectiles.size());

    for (Projectile & projectile : m_projectiles)
    {
        if (projectile.isDestroyed())
        {
            continue;
        }

        float x0 = projectile.getPositionX();
        float y0 = projectile.getPositionY();

        for (Gladiator & gladiator : m_gladiators)
        {
            if (!gladiator.isAlive())
            {
                continue;
            }

            float x1 = gladiator.getPositionX();
            float y1 = gladiator.getPositionY();
            float distSquared = (x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1);
            float radiusSquared = (Projectile::COLLISION_RADIUS + Gladiator::COLLISION_RADIUS) * (Projectile::COLLISION_RADIUS + Gladiator::COLLISION_RADIUS);

            if (distSquared < radiusSquared)
            {
                projectile.destroy();
                spawnExplosionAt(x0, y0);

                gladiator.knockBack(1.0f, std::atan2(y1 - y0, x1 - x0) / 2 / M_PI * 360.0f);
                gladiator.applyDamage(Projectile::DAMAGE);
                break;
            }
        }

        if (!projectile.isDestroyed())
        {
            liveProjectiles.push_back(projectile);
        }
    }

    m_projectiles = liveProjectiles;
}

int World::getNumPlayersAlive() const
{
    int numAlive = 0;

    for (const Gladiator & g : m_gladiators)
    {
        if (g.isAlive())
        {
            numAlive += 1;
        }
    }

    return numAlive;
}

int World::findFirstLivingPlayer() const
{
    int index = -1;

    for (int i = 0; i < m_gladiators.size(); ++i)
    {
        if (m_gladiators.at(i).isAlive())
        {
            index = i;
            break;
        }
    }

    return index;
}
