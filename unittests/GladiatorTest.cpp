#include "sim/Gladiator.hpp"
#include "gtest/gtest.h"


namespace
{

class GladiatorTest : public ::testing::Test
{
    protected:
    Gladiator gladiator;
};

TEST_F(GladiatorTest, IsInactiveByDefault)
{
    EXPECT_FALSE(gladiator.isActive());
}

TEST_F(GladiatorTest, IsActiveAfterInitialization)
{
    gladiator.initialize();
    EXPECT_TRUE(gladiator.isActive());
}

TEST_F(GladiatorTest, AimsEastByDefault)
{
    EXPECT_FLOAT_EQ(0.0f, gladiator.getAimDirection());
}

TEST_F(GladiatorTest, SetAimDirectionWorks)
{
    gladiator.setAimDirection(45.0f);
    EXPECT_FLOAT_EQ(45.0f, gladiator.getAimDirection());
}

TEST_F(GladiatorTest, SetAimDirectionClampsValue)
{
    gladiator.setAimDirection(450.0f);
    EXPECT_LT(-360.0f, gladiator.getAimDirection());
    EXPECT_GT(360.0f, gladiator.getAimDirection());
    EXPECT_FLOAT_EQ(90.0f, gladiator.getAimDirection());

    gladiator.setAimDirection(-450.0f);
    EXPECT_LT(-360.0f, gladiator.getAimDirection());
    EXPECT_GT(360.0f, gladiator.getAimDirection());
    EXPECT_FLOAT_EQ(-90.0f, gladiator.getAimDirection());
}

TEST_F(GladiatorTest, HasZeroSpeedByDefault)
{
    EXPECT_FLOAT_EQ(0.0f, gladiator.getSpeed());
}

TEST_F(GladiatorTest, SetSpeedWorks)
{
    gladiator.setSpeed(1.0f);
    EXPECT_FLOAT_EQ(1.0f, gladiator.getSpeed());
}

TEST_F(GladiatorTest, MoveDirectionIsEastByDefault)
{
    EXPECT_FLOAT_EQ(0.0f, gladiator.getMoveDirection());
}

TEST_F(GladiatorTest, SetMoveDirectionWorks)
{
    gladiator.setMoveDirection(45.0f);
    EXPECT_FLOAT_EQ(45.0f, gladiator.getMoveDirection());
}

TEST_F(GladiatorTest, SetMoveDirectionClampsValues)
{
    gladiator.setMoveDirection(450.0f);
    EXPECT_LT(-360.0f, gladiator.getMoveDirection());
    EXPECT_GT(360.0f, gladiator.getMoveDirection());
    EXPECT_FLOAT_EQ(90.0f, gladiator.getMoveDirection());

    gladiator.setMoveDirection(-450.0f);
    EXPECT_LT(-360.0f, gladiator.getMoveDirection());
    EXPECT_GT(360.0f, gladiator.getMoveDirection());
    EXPECT_FLOAT_EQ(-90.0f, gladiator.getMoveDirection());
}

TEST_F(GladiatorTest, HasZeroVelocityByDefault)
{
    EXPECT_FLOAT_EQ(0.0f, gladiator.getVelocityX());
    EXPECT_FLOAT_EQ(0.0f, gladiator.getVelocityY());
}

TEST_F(GladiatorTest, SetSpeedChangesVelocity)
{
    gladiator.setSpeed(1.0f);
    EXPECT_FLOAT_EQ(1.0f, gladiator.getVelocityX());
    EXPECT_FLOAT_EQ(0.0f, gladiator.getVelocityY());
}

TEST_F(GladiatorTest, SetMoveDirectionChangesVelocity)
{
    gladiator.setSpeed(1.0f);
    gladiator.setMoveDirection(90.0f);
    EXPECT_NEAR(0.0f, gladiator.getVelocityX(), 1.0e-6f);
    EXPECT_FLOAT_EQ(1.0f, gladiator.getVelocityY());
}

TEST_F(GladiatorTest, CanLaunchRocketAfterSpawn)
{
    EXPECT_TRUE(gladiator.canLaunchRocket());
}

TEST_F(GladiatorTest, CannotLaunchTwoRockets)
{
    gladiator.launchRocket();
    EXPECT_FALSE(gladiator.canLaunchRocket());
}

TEST_F(GladiatorTest, CanLaunchSecondRocketAfterCooldown)
{
    gladiator.launchRocket();

    for (int i = 0; i < Gladiator::ROCKET_LAUNCH_COOLDOWN; ++i)
    {
        gladiator.tick();
    }

    EXPECT_TRUE(gladiator.canLaunchRocket());
}

TEST_F(GladiatorTest, CanEngageJetpackAfterSpawn)
{
    EXPECT_TRUE(gladiator.canEngageJetpack());
}

TEST_F(GladiatorTest, CannotEngageJetpackTwice)
{
    gladiator.engageJetpack();
    EXPECT_FALSE(gladiator.canEngageJetpack());
}

TEST_F(GladiatorTest, CanEngageJetpackAgainAfterCooldown)
{
    gladiator.engageJetpack();

    for (int i = 0; i < Gladiator::JETPACK_COOLDOWN; ++i)
    {
        gladiator.tick();
    }

    EXPECT_TRUE(gladiator.canEngageJetpack());
}

} // namespace
