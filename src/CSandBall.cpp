#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "CSandBall.h"

CSandBall::CSandBall( int x, int y, int xVelocity ) {
    m_posX = x;
    m_posY = y;
    m_xVelocity = xVelocity;
    m_yVelocity = 0.03;
    m_ticksAlive = 0;
    m_canCollide = false;
}

void CSandBall::render( int cameraX, int cameraY ) {
    al_draw_filled_circle( this->getPosX() - cameraX, this->getPosY() - cameraY,
            5, al_map_rgb( 150, 131, 87 ) );
}

void CSandBall::update() {
    m_posX += m_xVelocity;
    m_posY += m_yVelocity;
    m_yVelocity += 0.02;

    m_ticksAlive++;
    if ( m_ticksAlive > 60 * 2 ) {
        m_shouldRemove = true;
    }
}

int CSandBall::getPosX() {
    return (int) m_posX;
}

int CSandBall::getPosY() {
    return (int) m_posY;
}
