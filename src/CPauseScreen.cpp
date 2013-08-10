#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <iostream>
#include "CPauseScreen.h"
#include "CEvent.h"
#include "CMainWindow.h"

CPauseScreen::CPauseScreen( CMainWindow* mainWindow, CScreen* parent ) 
    : CScreen( mainWindow, parent ) {
    m_options = new std::string[3];
    m_options[0] = "Resume game";
    m_options[1] = "About";
    m_options[2] = "Quit game";

    m_selectedOption = 0;

    m_font = al_load_ttf_font( "8bitlim.ttf", 36, 0 );
}

void CPauseScreen::render() {
    m_parent->render();

    al_draw_filled_rectangle( 100, 50, 700, 550, al_map_rgba( 0, 0, 0, 128 ) );
    
    for( int a = 0; a < 3; a++ ) {
        al_draw_text( m_font, al_map_rgb( 0, 0, 255 ), 
                120, a * 60 + 65, 0, m_options[a].c_str() );
    }   

    al_draw_line( 115, m_selectedOption * 60 + 105, 600, m_selectedOption * 60 + 105,
            al_map_rgb( 255, 0, 0 ), 5 );
}

void CPauseScreen::update() {
    CEvent* event = m_mainWindow->getEvent();
    if ( event->isKeyDownTimed( ALLEGRO_KEY_DOWN, 100 ) ) {
        m_selectedOption++;
        if ( m_selectedOption > 2 ) {
            m_selectedOption = 0;
        }
    }
    if ( event->isKeyDownTimed( ALLEGRO_KEY_UP, 100 ) ) {
        m_selectedOption--;
        if ( m_selectedOption < 0 ) {
            m_selectedOption = 2;
        }
    }

    if ( event->isKeyDown( ALLEGRO_KEY_ENTER ) ) {
        switch ( m_selectedOption ) {
            case 0:
                m_mainWindow->changeScreenTo( GAME_SCREEN ); break;
            case 2:
                m_mainWindow->exit(); break;
        }
    }
}

