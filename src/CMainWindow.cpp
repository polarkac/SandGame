#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <iostream>
#include "CMainWindow.h"
#include "CEvent.h"
#include "CGameScreen.h"
#include "CPauseScreen.h"

CMainWindow::CMainWindow() {
    m_isRunning = false;
    m_display = NULL;
    m_event = NULL;
}

int CMainWindow::execute() {
    if ( this->init() == false ) {
        return -1;
    }

    double lastTime = this->getMiliseconds();
    double resetTime = lastTime;
    double unprocessedTicks = 0;
    double msPerTick = 1000.0 / 60.0;
    int FPS = 0;
    int ticks = 0;

    while ( m_isRunning ) {
        double nowTime = this->getMiliseconds();
        unprocessedTicks += ( nowTime - lastTime ) / msPerTick;
        lastTime = nowTime;
        while ( unprocessedTicks >= 1 ) {
            m_event->processEvents();            
            ticks++;
            unprocessedTicks--;
            this->update();
        }

        FPS++;
        this->render();

        if ( ( this->getMiliseconds() - resetTime ) > 1000 ) {
            std::cout << "FPS: " << FPS << ", ticks: " << ticks << std::endl;
            FPS = 0;
            ticks = 0;
            resetTime = this->getMiliseconds();
        }
    }
}

bool CMainWindow::init() {
    if ( !al_init() ) {
        std::cerr << "Can not init allegro." << std::endl;
        return false;
    }

    if ( !al_install_keyboard() ) {
        std::cerr << "Can not init keyboard." << std::endl;
        return false;
    }

    m_display = al_create_display( 800, 600 );
    if ( m_display == NULL ) {
        std::cerr << "Allegro can not make display." << std::endl;
        return false;
    }

    al_init_primitives_addon();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    m_event = new CEvent( this );
    al_register_event_source( m_event->getEventQueue(), al_get_display_event_source( m_display ) );
    al_register_event_source( m_event->getEventQueue(), al_get_keyboard_event_source() );
    m_isRunning = true;

    m_gameScreen = new CGameScreen( this );
    m_pauseMenu = new CPauseScreen( this, m_gameScreen );
    m_activeScreen = m_gameScreen;
    
    return true;
}

void CMainWindow::update() {
    if ( m_event->isKeyDownTimed( ALLEGRO_KEY_ESCAPE, 250 ) ) {
        if ( m_activeScreen == m_pauseMenu ) {
            this->changeScreenTo( GAME_SCREEN );
        } else {
            this->changeScreenTo( PAUSE_SCREEN );
        }
    }
    m_activeScreen->update();
}

void CMainWindow::render() {

    al_clear_to_color( al_map_rgb( 255 ,255 ,255 ) );
    
    m_activeScreen->render();

    al_flip_display();
}

void CMainWindow::changeScreenTo( int screenCode ) {
    switch ( screenCode ) {
        case 0:
            m_activeScreen = m_gameScreen; break;
        case 1:
            m_activeScreen = m_pauseMenu; break;
    }
}

void CMainWindow::exit() {
    m_isRunning = false;
}

CEvent* CMainWindow::getEvent() {
    return m_event;
}

ALLEGRO_DISPLAY* CMainWindow::getDisplay() {
    return m_display;
}

double CMainWindow::getMiliseconds() {
    return al_get_time() * 1000.0;
}

