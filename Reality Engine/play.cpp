#include "play.hpp"

Player::Player()
    : tick(0), paused(true)
{
    maxTicks = 300;
}

void Player::update()
{
    if (!paused) {
        tick++;
        if (tick >= maxTicks)
            tick = maxTicks - 1;
    }
}

double Player::getProgress()
{
    return double(tick) / maxTicks;
}
