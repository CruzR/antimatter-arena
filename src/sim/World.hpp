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
    int spawnGladiatorAt(float x, float y, Gladiator::Color color);
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
