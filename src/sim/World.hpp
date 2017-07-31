#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>
#include "sim/Gladiator.hpp"
#include "sim/Projectile.hpp"
#include "sim/Explosion.hpp"

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
    int getNumExplosions() const;
    int spawnExplosionAt(float x, float y);
    Explosion & getExplosion(int id);
    int getNumPlayersAlive() const;
    int findFirstLivingPlayer() const;

    private:
    std::vector<Gladiator> m_gladiators;
    std::vector<Projectile> m_projectiles;
    std::vector<Explosion> m_explosions;

    void performCollisionChecks();
};

#endif // WORLD_HPP
