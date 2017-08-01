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

#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

class Projectile
{
    public:
    Projectile();
    Projectile(float x, float y, float moveDirection);
    float getPositionX() const;
    float getPositionY() const;
    void setPosition(float x, float y);
    float getMoveDirection() const;
    void setMoveDirection(float moveDirection);
    float getVelocityX() const;
    float getVelocityY() const;
    void tick();
    bool isDestroyed() const;
    void destroy();

    /* Equivalent to 120 km/h. */
    static constexpr float SPEED = 0.555556f;

    static const int EXPLODE_TIMEOUT = 120;

    static constexpr float COLLISION_RADIUS = 0.333334f;

    static const int DAMAGE = 25;

    private:
    float m_positionX;
    float m_positionY;
    float m_moveDirection;
    float m_velocityX;
    float m_velocityY;
    int m_explosionTimout;

    void updateVelocity();
};

#endif // PROJECTILE_HPP
