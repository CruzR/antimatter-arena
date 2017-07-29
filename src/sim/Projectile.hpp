class Projectile
{
    public:
    Projectile();
    float getPositionX() const;
    float getPositionY() const;
    void setPosition(float x, float y);
    float getMoveDirection() const;
    void setMoveDirection(float moveDirection);
    float getVelocityX() const;
    float getVelocityY() const;

    /* Equivalent to 120 km/h. */
    static constexpr float SPEED = 0.555556f;

    private:
    float m_positionX;
    float m_positionY;
    float m_moveDirection;
    float m_velocityX;
    float m_velocityY;

    void updateVelocity();
};
