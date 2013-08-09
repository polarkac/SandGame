#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <iostream>
#include "CPlayer.h"
#include "CEvent.h"

CPlayer::CPlayer( CEvent* event ) : CEntity() {
    m_event = event;
    this->init();
}

CPlayer::CPlayer( CEvent* event, int x, int y ) : CEntity( x, y ) {
    m_event = event;
    this->init();
}

void CPlayer::init() {
    this->loadImage( "player.png" );
    m_frame = 0;
    m_isMoving = false;
    m_isJumping = false;
    m_yVelocity = 0;
    m_xVelocity = 0;
    m_collidingEntities = new std::vector<CEntity*>();
}

void CPlayer::loadImage( char filename[] ) {
    m_image = al_load_bitmap( "player.png" );

    if ( m_image == NULL ) {
        std::cerr << "Can not load player image." << std::endl;
    }
}

void CPlayer::render() {
    int x = this->getPosX();
    int y = this->getPosY();

    ALLEGRO_BITMAP* subImage = al_create_sub_bitmap( m_image, 64 * (int) m_frame, 0, 64, 64 );
    al_draw_bitmap( subImage, x, y, 0 );
}

void CPlayer::update() {
    if ( !m_collidingEntities->empty() ) {
        for ( int a = 0; a < m_collidingEntities->size(); a++ ) {
            int xDiff = this->getPosX() - m_collidingEntities->at( a )->getPosX();
            int yDiff = this->getPosY() - m_collidingEntities->at( a )->getPosY();
            if ( xDiff < 0 ) {
                xDiff += 64;
            } else {
                xDiff -= 64;
            }   
            if ( yDiff < 0 ) {
                yDiff += 64;
            } else {
                yDiff -= 64;
            }
            this->setPosX( this->getPosX() + xDiff * -1 );
            /*this->setPosY( this->getPosY() + yDiff * -1 );*/
        }
        m_collidingEntities->clear();
    }

    this->move();

    m_frame += 0.10;
    if ( m_frame > 3 ) {
        m_frame = 0;
    }
}


void CPlayer::move() {
    m_isMoving = false;
    if ( m_event->isKeyDown( ALLEGRO_KEY_A ) ) {
        m_xVelocity = -5;
        m_isMoving = true;
    } 
    if ( m_event->isKeyDown( ALLEGRO_KEY_D ) ) {
        m_xVelocity = 5;
        m_isMoving = true;
    }
    
    if ( m_xVelocity != 0  && m_isMoving) {
        this->setPosX( this->getPosX() + m_xVelocity );
    }    
}

void CPlayer::isColliding( CEntity* entity ) {
    int playerX = this->getPosX();
    int playerY = this->getPosY();
    int entityX = entity->getPosX();
    int entityY = entity->getPosY();

    if ( playerX < ( entityX + 64 ) && playerY < ( entityY + 64 ) &&
            ( playerX + 64 ) > entityX && ( playerY + 64 ) > entityY ) {
        m_collidingEntities->push_back( entity );
    }
}
