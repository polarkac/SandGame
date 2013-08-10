#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "CSandBall.h"
#include "CGameScreen.h"
#include "CPlayer.h"

CSandBall::CSandBall( CGameScreen* gameScreen, CPlayer* player ) {
    m_posX = player->getPosX() + ( player->getFacing() == FACING_RIGHT ? 64 : 0 );
    m_posY = player->getPosY() + 32;
    m_xVelocity = player->getFacing() == FACING_RIGHT ? 5 : -5;
    m_yVelocity = 0.03;
    m_ticksAlive = 0;
    m_canCollide = false;
    m_gameScreen = gameScreen;
    m_player = player;
}

void CSandBall::render( int cameraX, int cameraY ) {
    al_draw_filled_circle( this->getPosX() - cameraX, this->getPosY() - cameraY,
            5, al_map_rgb( 150, 131, 87 ) );
}

void CSandBall::update() {
    m_posX += m_xVelocity;
    m_posY += m_yVelocity;
    m_yVelocity += 0.02;

    std::list<CEntity*>* ents = m_gameScreen->getVisibleEntities();
    std::list<CEntity*>::iterator i;
    for( i = ents->begin(); i != ents->end(); i++ ) {
        if ( (*i) == this || (*i) == m_player ) continue;
        bool isColliding = this->isColliding( (*i), this->getPosX() + m_xVelocity, 
                this->getPosY() );
        if ( isColliding ) {
            (*i)->hurt( 5 );
            m_shouldRemove = true;
        }
    }

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

bool CSandBall::isColliding( CEntity* ent, int x, int y ) {
    int playerX = x - 2.5;
    int playerY = y - 2.5;
    int entityX = ent->getPosX();
    int entityY = ent->getPosY();

    if ( playerX < ( entityX + 64 ) && playerY < ( entityY + 64 ) &&
            ( playerX + 5 ) > entityX && ( playerY + 5 ) > entityY ) {
        return true;
    }

    return false;
}   
