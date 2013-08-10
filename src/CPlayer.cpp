#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <iostream>
#include "CPlayer.h"
#include "CEvent.h"
#include "CGameScreen.h"

CPlayer::CPlayer( CGameScreen* gameScreen, CEvent* event, int x, int y ) : CEntity( x, y ) {
    m_event = event;
    m_gameScreen = gameScreen;
    this->loadImage( "player.png" );
    m_frame = 0;
    m_yVelocity = 0;
    m_xVelocity = 0;
}

CPlayer::~CPlayer() {
    al_destroy_bitmap( m_image );
}

void CPlayer::loadImage( char filename[] ) {
    m_image = al_load_bitmap( "player.png" );

    if ( m_image == NULL ) {
        std::cerr << "Can not load player image." << std::endl;
    }
}

void CPlayer::render( int cameraX, int cameraY ) {
    int x = this->getPosX();
    int y = this->getPosY();

    ALLEGRO_BITMAP* subImage = al_create_sub_bitmap( m_image, 64 * (int) m_frame, 0, 64, 64 );
    al_draw_bitmap( subImage, x - cameraX, y - cameraY, 0 );
}

void CPlayer::update() {
    this->move();
    this->jump();

    this->setPosX( this->getPosX() + m_xVelocity );
    this->setPosY( this->getPosY() + m_yVelocity );
    m_frame += 0.10;
    if ( m_frame > 3 ) {
        m_frame = 0;
    }
}


void CPlayer::move() {
    if ( m_event->isKeyDown( ALLEGRO_KEY_RIGHT ) ) {
        m_xVelocity = 5;
    } else if ( m_event->isKeyDown( ALLEGRO_KEY_LEFT ) ) {
        m_xVelocity = -5;
    } else {
        m_xVelocity = 0;
    }
    std::vector<CEntity*>* ents = m_gameScreen->getVisibleEntities();
    for ( int a = 0; a < ents->size(); a++ ) {
        CEntity* ent = ents->at( a );
        bool isColliding = this->isColliding( ent, this->getPosX() + m_xVelocity, 
                this->getPosY() );
        if ( isColliding ) {
            m_xVelocity = 0;
        }
    }

}

void CPlayer::jump() {
    if( m_yVelocity == 0 && m_event->isKeyDown( ALLEGRO_KEY_SPACE ) ) {
        m_yVelocity = -5;
        return;
    }
    
    m_yVelocity += 0.4;
    std::vector<CEntity*>* ents = m_gameScreen->getVisibleEntities();
    for ( int a = 0; a < ents->size(); a++ ) {
        CEntity* ent = ents->at( a );
        bool isColliding = this->isColliding( ent, this->getPosX(), 
                this->getPosY() + m_yVelocity );
        if ( isColliding ) {
            m_yVelocity = 0;
        }
    }
}

bool CPlayer::isColliding( CEntity* entity, int x, int y ) {
    int playerX = x;
    int playerY = y;
    int entityX = entity->getPosX();
    int entityY = entity->getPosY();

    if ( playerX < ( entityX + 64 ) && playerY < ( entityY + 64 ) &&
            ( playerX + 64 ) > entityX && ( playerY + 64 ) > entityY ) {
        return true;
    }

    return false;
}

bool CPlayer::isColliding( CEntity* entity ) {
   return this->isColliding( entity, this->getPosX(), this->getPosY() ); 
}
