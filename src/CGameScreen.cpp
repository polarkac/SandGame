#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <cmath>
#include "CGameScreen.h"
#include "CPlayer.h"
#include "CMainWindow.h"
#include "CSpriteSheet.h"
#include "CTile.h"

CGameScreen::CGameScreen( CMainWindow* const mainWindow, CScreen* parent ) 
    : CScreen( mainWindow, parent ) {
    m_rColor = 0;
    m_player = new CPlayer( this, m_mainWindow->getEvent(), 100, 0 );
    m_cameraControl = new Camera;
    m_cameraControl->posX = m_player->getPosX() - 32;
    m_spriteSheet = new CSpriteSheet( "spritesheet.png" );
    m_entities = new std::vector<CEntity*>();
    for( int a = -50; a < 800/64 + 50; a++ ) {
        m_entities->push_back( new CTile( m_spriteSheet->getSprite( 0, 0 ), 64 * a, 536 ) );
    }

    m_background = al_load_bitmap( "background.png" );
}

void CGameScreen::render() {
    int counter = ceil( m_cameraControl->posX / 4 / 800 );
    al_draw_bitmap( m_background, 800 * ( counter - 1 ) - m_cameraControl->posX / 4, 0, 0 );
    al_draw_bitmap( m_background, 800 * counter - m_cameraControl->posX / 4, 0, 0 );
    al_draw_bitmap( m_background, 800 * ( counter + 1 ) - m_cameraControl->posX / 4, 0, 0 );
    m_player->render( m_cameraControl->posX, 0 );
    for( int a = 0; a < m_entities->size(); a++ ) {
        CEntity* ent = m_entities->at(a);
        ent->render( m_cameraControl->posX, 0 );
    }
}   

void CGameScreen::update() {
    for( int a = 0; a < m_entities->size(); a++ ) {
        CEntity* ent = m_entities->at(a);
        ent->update();
    }
    m_player->update();
    m_cameraControl->posX = m_player->getPosX() + 32 - 400;
}

std::vector<CEntity*>* CGameScreen::getVisibleEntities() {
    return m_entities;
}
