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

#ifndef GLADIATOR_HPP
#define GLADIATOR_HPP

class Gladiator
{
    public:

    enum Color
    {
        COLOR_RED = 0,
        COLOR_BLUE,
        COLOR_GREEN,
        COLOR_YELLOW,
        NUM_COLORS
    };

    Gladiator();
    Gladiator(float positionX, float positionY, Color color);
    bool isAlive() const;
    float getAimDirection() const;
    void setAimDirection(float aimDirection);
    float getSpeed() const;
    void setSpeed(float speed);
    float getMoveDirection() const;
    void setMoveDirection(float moveDirection);
    float getVelocityX() const;
    float getVelocityY() const;
    bool canLaunchRocket() const;
    void launchRocket();
    void tick();

    Color getColor() const;

    static const int ROCKET_LAUNCH_COOLDOWN = 120;
    static const int JETPACK_COOLDOWN = 600;

    bool canEngageJetpack() const;
    void engageJetpack();
    bool isJetpackActive() const;

    static const int JETPACK_ACTIVE_COOLDOWN = 60;

    /* Equivalent to 12 km/h, approximately jogging speed. */
    static constexpr float MOVEMENT_SPEED = 0.055556f;

    /* Equivalent to 100 km/h. */
    static constexpr float JETPACK_SPEED = 0.462963f;

    float getPositionX() const;
    float getPositionY() const;

    static constexpr float PROJECTILE_DISTANCE = 1.25f;

    static constexpr float COLLISION_RADIUS = 0.5f;

    bool isInKnockbackMode() const;
    void knockBack(float energy, float direction);

    static const int KNOCKBACK_TIMEOUT = 60;
    /* Equivalent to 54 km/h. */
    static constexpr float KNOCKBACK_SPEED = 0.25f;

    int getHealth() const;
    void applyDamage(int amount);

    static const int MAX_HEALTH;

    private:
    float m_aimDirection;
    float m_speed;
    float m_moveDirection;
    float m_velocityX;
    float m_velocityY;
    int m_launchCooldown;
    int m_jetpackCooldown;
    bool m_jetpackActive;
    int m_jetpackActiveCooldown;
    float m_positionX;
    float m_positionY;

    bool m_inKnockbackMode;
    int m_knockbackTimeout;

    int m_health;

    Color m_color;

    void updateVelocity();
};

#endif // GLADIATOR_HPP
