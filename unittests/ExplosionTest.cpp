#include "sim/Explosion.hpp"
#include "gtest/gtest.h"


namespace
{

class ExplosionTest : public ::testing::Test
{
    protected:
    Explosion explosion;
};

TEST_F(ExplosionTest, SpawnsAtOriginByDefault)
{
    EXPECT_FLOAT_EQ(0.0f, explosion.getPositionX());
    EXPECT_FLOAT_EQ(0.0f, explosion.getPositionY());
}

TEST_F(ExplosionTest, SpawnsWhereItShouldSpawn)
{
    Explosion otherExplosion(1.0f, 1.0f);
    EXPECT_FLOAT_EQ(1.0f, otherExplosion.getPositionX());
    EXPECT_FLOAT_EQ(1.0f, otherExplosion.getPositionY());
}

TEST_F(ExplosionTest, IsActiveAtSpawn)
{
    EXPECT_FALSE(explosion.isDestroyed());
}

TEST_F(ExplosionTest, DisappearsAfterTimeout)
{
    for (int i = 0; i < Explosion::VANISH_TIMEOUT; ++i)
    {
        explosion.tick();
    }

    EXPECT_TRUE(explosion.isDestroyed());
}

} // namespace
