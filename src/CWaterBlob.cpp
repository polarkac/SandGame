#include <allegro5/allegro.h>
#include <iostream>
#include <vector>
#include "CWaterBlob.h"
#include "CGameScreen.h"

CWaterBlob::CWaterBlob( CGameScreen* gameScreen, int x, int y ) : CEntity( x, y ) {
    m_image = al_load_bitmap( "waterblob.png" );
    m_frame = 0;
    m_centerX = x;
    m_xVelocity = 3;
    m_gameScreen = gameScreen;
    m_radius = 25;
    m_health = 5;
    m_shouldRemove = false;
    m_canCollide = false;
}

void CWaterBlob::render( int cameraX, int cameraY ) {
    ALLEGRO_BITMAP* frameImage = al_create_sub_bitmap( m_image, (int) m_frame * 64, 0, 64, 64 );
    al_draw_bitmap( frameImage, this->getPosX() - cameraX, this->getPosY() - cameraY, 0 );
}

void CWaterBlob::update() {
    this->move();
    m_frame += 0.08;
    if ( m_frame > 3 ) {
        m_frame = 0;
    }
}

void CWaterBlob::move() {
    if ( !( this->getPosX() < m_radius + m_centerX && this->getPosX() > m_radius - m_centerX ) ) {
        m_xVelocity = -m_xVelocity;
    }
    std::list<CEntity*>* ents = m_gameScreen->getVisibleEntities();
    std::list<CEntity*>::iterator i;
    for( i = ents->begin(); i != ents->end(); i++ ) {
        if ( (*i) == this ) continue;
        bool isColliding = this->isColliding( (*i), this->getPosX() + m_xVelocity, 
                this->getPosY() );
        if ( isColliding ) {
            m_xVelocity = -m_xVelocity;
        }
    }   
    this->setPosX( this->getPosX() + this->m_xVelocity );
}

void CWaterBlob::hurt( int damage ) {
    m_health -= damage;

    if ( m_health <= 0 ) {
        m_shouldRemove = true;
    }
}
