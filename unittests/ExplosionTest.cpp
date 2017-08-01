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
