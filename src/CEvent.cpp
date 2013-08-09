#include <allegro5/allegro.h>
#include <iostream>
#include "CEvent.h"
#include "CMainWindow.h"

CEvent::CEvent( CMainWindow* mainWindow ) {
    m_eventQueue = al_create_event_queue();
    m_mainWindow = mainWindow;
    m_keys = new Key[ALLEGRO_KEY_MAX];

    for ( int a = 0; a < ALLEGRO_KEY_MAX; a++ ) {
        m_keys[a].isDown = false;
        m_keys[a].lastTime = 0;
    }
}

ALLEGRO_EVENT_QUEUE* CEvent::getEventQueue() {
    return m_eventQueue;
}

void CEvent::processEvents() {
    ALLEGRO_EVENT* event = new ALLEGRO_EVENT;
    al_get_next_event( m_eventQueue, event );
    switch( event->type ) {
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            m_mainWindow->exit(); break;
        case ALLEGRO_EVENT_KEY_DOWN:
            this->toggleKey( event->keyboard.keycode, true ); break;
        case ALLEGRO_EVENT_KEY_UP:
            this->toggleKey( event->keyboard.keycode, false ); break;
    }
}

void CEvent::toggleKey( int keyCode, bool isDown ) {
    m_keys[keyCode].isDown = isDown;
}

bool CEvent::isKeyDown( int keyCode ) {
    return m_keys[keyCode].isDown;
}

bool CEvent::isKeyDownTimed( int keyCode, int msTime ) {
    if ( ( m_mainWindow->getMiliseconds() - m_keys[keyCode].lastTime ) > msTime && 
            m_keys[keyCode].isDown ) {
        m_keys[keyCode].lastTime = m_mainWindow->getMiliseconds();
        return true;
    } 
    
    return false;
}

