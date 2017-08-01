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
