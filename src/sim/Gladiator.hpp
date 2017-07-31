#ifndef GLADIATOR_HPP
#define GLADIATOR_HPP

class Gladiator
{
    public:
    Gladiator();
    Gladiator(float positionX, float positionY);
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

    private:
    bool m_alive;
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

    void updateVelocity();
};

#endif // GLADIATOR_HPP
