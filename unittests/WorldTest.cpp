#include "sim/World.hpp"
#include "gtest/gtest.h"


namespace
{

class WorldTest : public ::testing::Test
{
    protected:
    World world;
};

TEST_F(WorldTest, IsEmptyAfterInitialization)
{
    EXPECT_EQ(0, world.getNumGladiators());
    EXPECT_EQ(0, world.getNumProjectiles());
    EXPECT_EQ(0, world.getNumExplosions());
}

TEST_F(WorldTest, SpawnGladiatorIncreasesGladiatorCount)
{
    world.spawnGladiatorAt(0.0f, 0.0f);
    EXPECT_EQ(1, world.getNumGladiators());

    world.spawnGladiatorAt(1.0f, 1.0f);
    EXPECT_EQ(2, world.getNumGladiators());
}

TEST_F(WorldTest, CanRetrieveSpawnedGladiator)
{
    int id = world.spawnGladiatorAt(0.0f, 0.0f);
    EXPECT_NO_THROW(world.getGladiator(id));
    EXPECT_ANY_THROW(world.getGladiator(id + 1));
}

TEST_F(WorldTest, SpawnsGladiatorAtCorrectLocation)
{
    int id = world.spawnGladiatorAt(1.0f, 1.0f);
    EXPECT_FLOAT_EQ(1.0f, world.getGladiator(id).getPositionX());
    EXPECT_FLOAT_EQ(1.0f, world.getGladiator(id).getPositionY());
}

TEST_F(WorldTest, SpawnProjectileIncreasesProjectileCount)
{
    world.spawnProjectileAt(0.0f, 0.0f, 0.0f);
    EXPECT_EQ(1, world.getNumProjectiles());

    world.spawnProjectileAt(1.0f, 1.0f, 90.0f);
    EXPECT_EQ(2, world.getNumProjectiles());
}

TEST_F(WorldTest, CanRetrieveSpawnedProjectile)
{
    int id = world.spawnProjectileAt(0.0f, 0.0f, 0.0f);
    EXPECT_NO_THROW(world.getProjectile(id));
    EXPECT_ANY_THROW(world.getProjectile(id + 1));
}

TEST_F(WorldTest, SpawnsProjectileAtCorretLocationAndAngle)
{
    int id = world.spawnProjectileAt(1.0f, 1.0f, 90.0f);
    EXPECT_FLOAT_EQ(1.0f, world.getProjectile(id).getPositionX());
    EXPECT_FLOAT_EQ(1.0f, world.getProjectile(id).getPositionY());
    EXPECT_FLOAT_EQ(90.0f, world.getProjectile(id).getMoveDirection());
}

TEST_F(WorldTest, RemovesDestroyedProjectiles)
{
    world.spawnProjectileAt(0.0f, 0.0f, 0.0f);

    for (int i = 0; i < Projectile::EXPLODE_TIMEOUT; ++i)
    {
        world.tick();
    }

    EXPECT_EQ(0, world.getNumProjectiles());
}

TEST_F(WorldTest, GladiatorLaunchRocketSpawnsProjectile)
{
    int id = world.spawnGladiatorAt(0.0f, 0.0f);
    EXPECT_EQ(0, world.getNumProjectiles());
    world.gladiatorLaunchProjectile(id);
    EXPECT_EQ(1, world.getNumProjectiles());
}

TEST_F(WorldTest, GladiatorCannotLaunchTwice)
{
    int id = world.spawnGladiatorAt(0.0f, 0.0f);
    world.gladiatorLaunchProjectile(id);
    world.gladiatorLaunchProjectile(id);
    EXPECT_EQ(1, world.getNumProjectiles());
}

TEST_F(WorldTest, SpawnExplosionIncreasesExplosionCount)
{
    world.spawnExplosionAt(0.0f, 0.0f);
    EXPECT_EQ(1, world.getNumExplosions());

    world.spawnExplosionAt(1.0f, 1.0f);
    EXPECT_EQ(2, world.getNumExplosions());
}

TEST_F(WorldTest, CanRetrieveSpawnedExplosion)
{
    int id = world.spawnExplosionAt(0.0f, 0.0f);
    EXPECT_NO_THROW(world.getExplosion(id));
    EXPECT_ANY_THROW(world.getExplosion(id + 1));
}

TEST_F(WorldTest, SpawnsExplosionAtCorrectLocation)
{
    int id = world.spawnExplosionAt(1.0f, 1.0f);
    EXPECT_FLOAT_EQ(1.0f, world.getExplosion(id).getPositionX());
    EXPECT_FLOAT_EQ(1.0f, world.getExplosion(id).getPositionY());
}

TEST_F(WorldTest, RemovesDestroyedExplosions)
{
    world.spawnExplosionAt(0.0f, 0.0f);

    for (int i = 0; i < Explosion::VANISH_TIMEOUT; ++i)
    {
        world.tick();
    }

    EXPECT_EQ(0, world.getNumExplosions());
}

TEST_F(WorldTest, DestroyedRocketsAreReplacedByExplosions)
{
    world.spawnProjectileAt(0.0f, 0.0f, 0.0f);

    for (int i = 0; i < Projectile::EXPLODE_TIMEOUT; ++i)
    {
        world.tick();
    }

    EXPECT_EQ(1, world.getNumExplosions());
}

TEST_F(WorldTest, DestroyTwoCollidingRockets)
{
    world.spawnProjectileAt(-1*Projectile::SPEED, 0.0f, 0.0f);
    world.spawnProjectileAt(Projectile::SPEED, 0.0f, 180.0f);

    world.tick();

    EXPECT_EQ(0, world.getNumProjectiles());
    EXPECT_EQ(2, world.getNumExplosions());
}

TEST_F(WorldTest, DestroyRocketsCollidingWithPlayers)
{
    world.spawnProjectileAt(-1*Projectile::SPEED, 0.0f, 0.0f);
    world.spawnGladiatorAt(0.0f, 0.0f);

    world.tick();

    EXPECT_EQ(0, world.getNumProjectiles());
    EXPECT_EQ(1, world.getNumExplosions());
}

TEST_F(WorldTest, KnockbackPlayerWhenCollidingWithRocket)
{
    world.spawnProjectileAt(-1*Projectile::SPEED, 0.0f, 0.0f);
    int id = world.spawnGladiatorAt(0.0f, 0.0f);
    world.getGladiator(id).setMoveDirection(180.0f);

    world.tick();

    EXPECT_TRUE(world.getGladiator(id).isInKnockbackMode());
    EXPECT_FLOAT_EQ(0.0f, world.getGladiator(id).getMoveDirection());
}

TEST_F(WorldTest, DamagePlayerWhenCollidingWithRockets)
{
    world.spawnProjectileAt(-1*Projectile::SPEED, 0.0f, 0.0f);
    int id = world.spawnGladiatorAt(0.0f, 0.0f);
    world.getGladiator(id).setMoveDirection(180.0f);

    world.tick();

    EXPECT_GT(Gladiator::MAX_HEALTH, world.getGladiator(id).getHealth());
    EXPECT_EQ(Gladiator::MAX_HEALTH - Projectile::DAMAGE, world.getGladiator(id).getHealth());
}

TEST_F(WorldTest, CollisionIgnoresDeadPlayers)
{
    world.spawnProjectileAt(-1*Projectile::SPEED, 0.0f, 0.0f);
    int id = world.spawnGladiatorAt(0.0f, 0.0f);
    world.getGladiator(id).applyDamage(Gladiator::MAX_HEALTH);

    world.tick();

    EXPECT_EQ(1, world.getNumProjectiles());
    EXPECT_EQ(0, world.getNumExplosions());
}

} // namespace
