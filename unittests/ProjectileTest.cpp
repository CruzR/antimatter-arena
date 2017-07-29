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
