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
