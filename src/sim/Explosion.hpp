#ifndef EXPLOSION_HPP
#define EXPLOSION_HPP

class Explosion
{
    public:
    Explosion();
    Explosion(float x, float y);
    float getPositionX() const;
    float getPositionY() const;
    bool isDestroyed() const;
    void tick();

    static const int VANISH_TIMEOUT = 20;

    private:
    int m_vanishTimeout;
    float m_positionX;
    float m_positionY;
};

#endif // EXPLOSION_HPP
