#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <iostream>
#include "CPlayer.h"
#include "CEvent.h"
#include "CGameScreen.h"
#include "CSandBall.h"

CPlayer::CPlayer( CGameScreen* gameScreen, CEvent* event, int x, int y ) : CEntity( x, y ) {
    m_event = event;
    m_gameScreen = gameScreen;
    this->loadImage( "player.png" );
    m_frame = 0;
    m_yVelocity = 0;
    m_xVelocity = 0;
    m_facing = FACING_RIGHT;
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

    if ( m_event->isKeyDownTimed( ALLEGRO_KEY_LCTRL, 250 ) ) {
        m_gameScreen->addEntity( new CSandBall( m_gameScreen, this ) );
    }

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
        m_facing = FACING_RIGHT;
    } else if ( m_event->isKeyDown( ALLEGRO_KEY_LEFT ) ) {
        m_xVelocity = -5;
        m_facing = FACING_LEFT;
    } else {
        m_xVelocity = 0;
    }
    std::list<CEntity*>* ents = m_gameScreen->getVisibleEntities();
    std::list<CEntity*>::iterator i;
    for( i = ents->begin(); i != ents->end(); i++ ) {
        if ( !(*i)->canCollide() ) {
            continue;
        }
        bool isColliding = this->isColliding( (*i), this->getPosX() + m_xVelocity, 
                this->getPosY() );
        if ( isColliding ) {
            m_xVelocity = 0;
        }
    }
}

void CPlayer::jump() {
    if( m_yVelocity == 0 && m_event->isKeyDown( ALLEGRO_KEY_SPACE ) ) {
        m_yVelocity = -10;
    }
    
    m_yVelocity += 0.4;
    std::list<CEntity*>* ents = m_gameScreen->getVisibleEntities();
    std::list<CEntity*>::iterator i;
    for( i = ents->begin(); i != ents->end(); i++ ) {
        if ( !(*i)->canCollide() ) {
            continue;
        }
        bool isColliding = this->isColliding( (*i), this->getPosX(), 
                this->getPosY() + m_yVelocity );
        if ( isColliding ) {
            m_yVelocity = 0;
        } 
    }
}

unsigned char CPlayer::getFacing() {
    return m_facing;
}
