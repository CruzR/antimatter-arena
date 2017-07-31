#include "sim/Explosion.hpp"

Explosion::Explosion()
    :
    Explosion(0.0f, 0.0f)
{
}

Explosion::Explosion(float x, float y)
    :
    m_vanishTimeout(VANISH_TIMEOUT),
    m_positionX(x),
    m_positionY(y)
{
}

float Explosion::getPositionX() const
{
    return m_positionX;
}

float Explosion::getPositionY() const
{
    return m_positionY;
}

bool Explosion::isDestroyed() const
{
    return m_vanishTimeout <= 0;
}

void Explosion::tick()
{
    if (m_vanishTimeout > 0)
    {
        m_vanishTimeout -= 1;
    }
}
