#include "sim/Projectile.hpp"
#include "gtest/gtest.h"


class ProjectileTest : public ::testing::Test
{
    protected:
    Projectile projectile;
};


TEST_F(ProjectileTest, SpawnsAtOrigin)
{
    EXPECT_FLOAT_EQ(0.0f, projectile.getPositionX());
    EXPECT_FLOAT_EQ(0.0f, projectile.getPositionY());
}

TEST_F(ProjectileTest, SetPositionWorks)
{
    projectile.setPosition(1.0f, 2.0f);
    EXPECT_FLOAT_EQ(1.0f, projectile.getPositionX());
    EXPECT_FLOAT_EQ(2.0f, projectile.getPositionY());
}

TEST_F(ProjectileTest, FacesEastAtSpawn)
{
    EXPECT_FLOAT_EQ(0.0f, projectile.getMoveDirection());
}

TEST_F(ProjectileTest, SetMoveDirectionWorks)
{
    projectile.setMoveDirection(90.0f);
    EXPECT_FLOAT_EQ(90.0f, projectile.getMoveDirection());
}

TEST_F(ProjectileTest, SetMoveDirectionChangesVelocity)
{
    EXPECT_NEAR(Projectile::SPEED, projectile.getVelocityX(), 1.0e-6f);
    EXPECT_NEAR(0.0f, projectile.getVelocityY(), 1.0e-6f);

    projectile.setMoveDirection(90.0f);

    EXPECT_NEAR(0.0f, projectile.getVelocityX(), 1.0e-6f);
    EXPECT_NEAR(Projectile::SPEED, projectile.getVelocityY(), 1.0e-6f);
}

TEST_F(ProjectileTest, ChangesPositionOverTime)
{
    for (int i = 0; i < 90; ++i)
    {
        projectile.tick();
    }

    EXPECT_NEAR(50.0f, projectile.getPositionX(), 1.0e-4f);
    EXPECT_NEAR(0.0f, projectile.getPositionY(), 1.0e-4f);
}

TEST_F(ProjectileTest, IsNotDestroyedAtSpawn)
{
    EXPECT_FALSE(projectile.isDestroyed());
}

TEST_F(ProjectileTest, IsDestroyedAfterTimeout)
{
    for (int i = 0; i < Projectile::EXPLODE_TIMEOUT; ++i)
    {
        projectile.tick();
    }

    EXPECT_TRUE(projectile.isDestroyed());
}
