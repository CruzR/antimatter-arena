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

#ifndef GLADIATOR_CONTROLLER_HPP
#define GLADIATOR_CONTROLLER_HPP

#include "SDL.h"
#include "sim/World.hpp"

class GladiatorController
{
    public:
    GladiatorController(World & world, int gladiator, SDL_GameController * gamepad);
    void update();

    private:
    World & m_world;
    int m_gladiatorId;
    SDL_GameController * m_gamepad;
    float m_lastAimDirection;
    float m_lastMoveDirection;
    float m_lastMoveSpeed;

    void getAimDirection();
    void getMoveParameters();
};

#endif // GLADIATOR_CONTROLLER_HPP
