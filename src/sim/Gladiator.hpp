class Gladiator
{
    public:
    Gladiator();
    void initialize();
    bool isActive() const;
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

    private:
    bool m_active;
    float m_aimDirection;
    float m_speed;
    float m_moveDirection;
    float m_velocityX;
    float m_velocityY;
    int m_launchCooldown;

    void updateVelocity();
};
