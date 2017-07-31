#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>
#include "sim/Gladiator.hpp"
#include "sim/Projectile.hpp"

class World
{
    public:
    World();
    int getNumGladiators() const;
    int getNumProjectiles() const;
    int spawnGladiatorAt(float x, float y);
    Gladiator & getGladiator(int id);
    int spawnProjectileAt(float x, float y, float rot);
    Projectile & getProjectile(int id);
    void tick();
    void gladiatorLaunchProjectile(int id);
    std::vector<Gladiator> & getGladiators();

    private:
    std::vector<Gladiator> m_gladiators;
    std::vector<Projectile> m_projectiles;
};

#endif // WORLD_HPP