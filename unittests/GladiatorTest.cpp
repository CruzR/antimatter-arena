#include "sim/Gladiator.hpp"
#include "gtest/gtest.h"


namespace
{

class GladiatorTest : public ::testing::Test
{
    protected:
    Gladiator gladiator;
};

TEST_F(GladiatorTest, IsAliveByDefault)
{
    EXPECT_TRUE(gladiator.isAlive());
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

TEST_F(GladiatorTest, JetpackIsNotActiveByDefault)
{
    EXPECT_FALSE(gladiator.isJetpackActive());
}

TEST_F(GladiatorTest, JetpackIsActiveAfterEngaged)
{
    gladiator.engageJetpack();
    EXPECT_TRUE(gladiator.isJetpackActive());
}

TEST_F(GladiatorTest, JetpackBecomesInactiveAfterCooldown)
{
    gladiator.engageJetpack();

    for (int i = 0; i < Gladiator::JETPACK_ACTIVE_COOLDOWN; ++i)
    {
        gladiator.tick();
    }

    EXPECT_FALSE(gladiator.isJetpackActive());
}

TEST_F(GladiatorTest, MoveDirectionIsLockedWhileJetpackActive)
{
    gladiator.engageJetpack();
    const float moveDirection = gladiator.getMoveDirection();
    gladiator.setMoveDirection(moveDirection + 90.0f);
    EXPECT_FLOAT_EQ(moveDirection, gladiator.getMoveDirection());
}

TEST_F(GladiatorTest, SpeedIsLockedWhileJetpackActive)
{
    gladiator.engageJetpack();
    const float speed = gladiator.getSpeed();
    gladiator.setSpeed(speed + 1.0f);
    EXPECT_FLOAT_EQ(speed, gladiator.getSpeed());
}

TEST_F(GladiatorTest, SpeedIsSetToJetpackSpeedWhileJetpackActive)
{
    gladiator.engageJetpack();
    EXPECT_FLOAT_EQ(Gladiator::JETPACK_SPEED, gladiator.getSpeed());
}

TEST_F(GladiatorTest, SpeedIsSetToZeroAfterJetpackActive)
{
    gladiator.engageJetpack();

    for (int i = 0; i < Gladiator::JETPACK_ACTIVE_COOLDOWN; ++i)
    {
        gladiator.tick();
    }

    EXPECT_FLOAT_EQ(0.0f, gladiator.getSpeed());
}

TEST_F(GladiatorTest, PositionIsAtOriginAtSpawn)
{
    EXPECT_FLOAT_EQ(0.0f, gladiator.getPositionX());
    EXPECT_FLOAT_EQ(0.0f, gladiator.getPositionY());
}

TEST_F(GladiatorTest, PositionChangesAccordingToVelocity)
{
    gladiator.setSpeed(1.0f);
    gladiator.tick();
    EXPECT_NEAR(1.0f, gladiator.getPositionX(), 1.0e-6f);
    EXPECT_NEAR(0.0f, gladiator.getPositionY(), 1.0e-6f);
}

TEST_F(GladiatorTest, IsNotInKnockbackModeByDefault)
{
    EXPECT_FALSE(gladiator.isInKnockbackMode());
}

TEST_F(GladiatorTest, IsInKnockbackModeAfterKnockback)
{
    gladiator.knockBack(1.0f, 0.0f);
    EXPECT_TRUE(gladiator.isInKnockbackMode());
}

TEST_F(GladiatorTest, LeavesKnockbackModeAfterTimout)
{
    gladiator.knockBack(1.0f, 0.0f);

    for (int i = 0; i < Gladiator::KNOCKBACK_TIMEOUT; ++i)
    {
        gladiator.tick();
    }

    EXPECT_FALSE(gladiator.isInKnockbackMode());
}

TEST_F(GladiatorTest, MoveDirectionIsLockedDuringKnockback)
{
    gladiator.knockBack(1.0f, 0.0f);
    const float moveDirection = gladiator.getMoveDirection();
    gladiator.setMoveDirection(moveDirection + 90.0f);
    EXPECT_FLOAT_EQ(moveDirection, gladiator.getMoveDirection());
}

TEST_F(GladiatorTest, MoveSpeedIsLockedDuringKnockback)
{
    gladiator.knockBack(1.0f, 0.0f);
    const float moveSpeed = gladiator.getSpeed();
    gladiator.setSpeed(moveSpeed + 0.5f);
    EXPECT_FLOAT_EQ(moveSpeed, gladiator.getSpeed());
}

TEST_F(GladiatorTest, CannotUseJetpackDuringKnockback)
{
    gladiator.knockBack(1.0f, 0.0f);
    EXPECT_FALSE(gladiator.canEngageJetpack());
}

TEST_F(GladiatorTest, SpeedIsKnockbackSpeedDuringKnockback)
{
    gladiator.knockBack(1.0f, 0.0f);
    EXPECT_FLOAT_EQ(Gladiator::KNOCKBACK_SPEED, gladiator.getSpeed());
}

TEST_F(GladiatorTest, LatestKnockbackWins)
{
    gladiator.knockBack(1.0f, 0.0f);
    gladiator.knockBack(1.0f, 90.0f);
    EXPECT_FLOAT_EQ(90.0f, gladiator.getMoveDirection());
}

TEST_F(GladiatorTest, SpawnsWithFullHP)
{
    EXPECT_EQ(Gladiator::MAX_HEALTH, gladiator.getHealth());
}

TEST_F(GladiatorTest, DamageReducesHP)
{
    gladiator.applyDamage(10);
    EXPECT_EQ(Gladiator::MAX_HEALTH - 10, gladiator.getHealth());
}

TEST_F(GladiatorTest, MinHPIsZero)
{
    gladiator.applyDamage(Gladiator::MAX_HEALTH + 10);
    EXPECT_EQ(0, gladiator.getHealth());
}

TEST_F(GladiatorTest, NotAliveIfHPIsZero)
{
    gladiator.applyDamage(Gladiator::MAX_HEALTH);
    EXPECT_FALSE(gladiator.isAlive());
}

} // namespace
