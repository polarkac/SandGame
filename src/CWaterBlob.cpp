#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <vector>
#include "CWaterBlob.h"
#include "CGameScreen.h"

CWaterBlob::CWaterBlob( CGameScreen* gameScreen, int x, int y ) : CEntity( x, y ) {
    m_image = al_load_bitmap( "waterblob.png" );
    m_frame = 0;
    m_centerX = x;
    m_xVelocity = 3;
    m_yVelocity = 0;
    m_gameScreen = gameScreen;
    m_radius = 25;
    m_shouldRemove = false;
    m_canCollide = false;
    m_health = 10;
    m_hurtTime = 0;
}

void CWaterBlob::render( int cameraX, int cameraY ) {
    ALLEGRO_BITMAP* frameImage = al_create_sub_bitmap( m_image, (int) m_frame * 64, 0, 64, 64 );
    al_draw_bitmap( frameImage, this->getPosX() - cameraX, this->getPosY() - cameraY, 0 );
    int x = this->getPosX();
    int y = this->getPosY();
    if ( m_hurtTime > 0 ) {
        al_draw_filled_rectangle( x - cameraX, y - cameraY, x + 64 - cameraX, y + 64 - cameraY, 
                al_map_rgba( 255, 0, 0, 80 ) );
        m_hurtTime--;
    }
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

    m_yVelocity += 0.4;
    std::list<CEntity*>::iterator ii;
    for( ii = ents->begin(); ii != ents->end(); ii++ ) {
        if ( !(*ii)->canCollide() ) {
            continue;
        }
        bool isColliding = this->isColliding( (*ii), this->getPosX(), 
                this->getPosY() + m_yVelocity );
        if ( isColliding ) {
            m_yVelocity = 0;
        } 
    }
    this->setPosY( this->getPosY() + this->m_yVelocity );
}

void CWaterBlob::hurt( int damage ) {
    CEntity::hurt( damage );

    m_hurtTime = 30;
}
