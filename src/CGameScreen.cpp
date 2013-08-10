#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include "CGameScreen.h"
#include "CPlayer.h"
#include "CMainWindow.h"
#include "CSpriteSheet.h"
#include "CTile.h"
#include "CWaterBlob.h"

CGameScreen::CGameScreen( CMainWindow* const mainWindow, CScreen* parent ) 
    : CScreen( mainWindow, parent ) {
    m_rColor = 0;
    m_player = new CPlayer( this, m_mainWindow->getEvent(), 700, 0 );
    m_cameraControl = new Camera;
    m_cameraControl->posX = m_player->getPosX() - 32;
    m_spriteSheet = new CSpriteSheet( "spritesheet.png" );
    m_entities = new std::list<CEntity*>();
    this->initMap( "level01.map" );
    m_background = al_load_bitmap( "background.png" );
}

void CGameScreen::initMap( char* filename ) {
    std::ifstream mapFile( filename );
    if ( mapFile.is_open() ) {
        int rowCounter = 0;
        while ( mapFile.good() ) {
            std::string row;
            getline( mapFile, row );
            for ( int a = 0; a < row.size(); a++ ) {
                char entityChar = row.at( a );
                switch( entityChar ) {
                    case 'A':
                        break;
                    case 'S':
                        m_entities->push_back( new CTile( m_spriteSheet->getSprite( 64 * ( a % 3 ), 0 ),
                                    a * 64, rowCounter * 64 ) ); break;
                    case 'C':
                        m_entities->push_back( new CTile( m_spriteSheet->getSprite( 0, 64 ),
                                    a * 64, rowCounter * 64 ) ); break;
                    case 'B':
                        m_entities->push_back( new CWaterBlob( this, a * 64, rowCounter * 64 ) ); break;
                }
            }
            rowCounter++;
        }
        mapFile.close();
    } else {
        std::cerr << "Can not open map file." << std::endl;
    }

}

void CGameScreen::render() {
    int counter = ceil( m_cameraControl->posX / 4 / 800 );
    al_draw_bitmap( m_background, 800 * ( counter - 1 ) - m_cameraControl->posX / 4, 0, 0 );
    al_draw_bitmap( m_background, 800 * counter - m_cameraControl->posX / 4, 0, 0 );
    al_draw_bitmap( m_background, 800 * ( counter + 1 ) - m_cameraControl->posX / 4, 0, 0 );
    m_player->render( m_cameraControl->posX, 0 );
    std::list<CEntity*>::iterator i;
    for( i = m_entities->begin(); i != m_entities->end(); i++ ) {
        (*i)->render( m_cameraControl->posX, 0 );
    }
}   

void CGameScreen::update() {
    std::list<CEntity*>::iterator i;
    std::vector<CEntity*>* removedEntities = new std::vector<CEntity*>();
    for( i = m_entities->begin(); i != m_entities->end(); i++ ) {
        if ( (*i)->isReadyToRemove() ) {
            removedEntities->push_back( (*i) );
            continue;
        }
        (*i)->update();
    }
    for ( int a = 0; a < removedEntities->size(); a++ ) {
        m_entities->remove( removedEntities->at( a ) );
    }
    m_player->update();
    m_cameraControl->posX = m_player->getPosX() + 32 - 400;
}

std::list<CEntity*>* CGameScreen::getVisibleEntities() {
    return m_entities;
}

void CGameScreen::addEntity( CEntity* entity ) {
    m_entities->push_back( entity );
}
