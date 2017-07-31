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
    int newId = m_gladiators.size();
    m_gladiators.emplace_back(x, y);
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
    std::vector<Projectile> liveProjectiles;
    liveProjectiles.reserve(m_projectiles.size());

    for (Projectile & projectile : m_projectiles)
    {
        projectile.tick();
        if (!projectile.isDestroyed())
        {
            liveProjectiles.push_back(projectile);
        }
    }

    m_projectiles = liveProjectiles;

    for (Gladiator & gladiator : m_gladiators)
    {
        gladiator.tick();
    }
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
