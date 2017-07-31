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
