#include <allegro5/allegro.h>
#include <iostream>
#include "CGameScreen.h"
#include "CPlayer.h"
#include "CMainWindow.h"
#include "CSpriteSheet.h"
#include "CTile.h"

CGameScreen::CGameScreen( CMainWindow* const mainWindow, CScreen* parent ) 
    : CScreen( mainWindow, parent ) {
    m_rColor = 0;
    m_player = new CPlayer( m_mainWindow->getEvent(), 100, 0 );
    m_spriteSheet = new CSpriteSheet( "spritesheet.png" );
    m_tiles = new std::vector<CTile*>();
    for( int a = 0; a < 5; a++ ) {
        m_tiles->push_back( new CTile( m_spriteSheet->getSprite( 0, 0 ), 64 * a, 536 ) );
    }
    m_tiles->push_back( new CTile( m_spriteSheet->getSprite( 0, 0 ), 500, 0 ) );
    m_tiles->push_back( new CTile( m_spriteSheet->getSprite( 0, 0 ), 0, 0 ) );
}

void CGameScreen::render() {
    m_player->render();
    for( int a = 0; a < m_tiles->size(); a++ ) {
        CTile* tile = m_tiles->at(a);
        tile->render();
    }
}   

void CGameScreen::update() {
    for( int a = 0; a < m_tiles->size(); a++ ) {
        CTile* tile = m_tiles->at(a);
        tile->update();
        m_player->isColliding( tile );
    }
    m_player->update();
}
