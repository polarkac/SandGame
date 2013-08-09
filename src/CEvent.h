#ifndef _CEVENT_H_
    #define _CEVENT_H_

#include <allegro5/allegro.h>

struct ALLEGRO_EVENT_QUEUE;
struct ALLEGRo_EVENT;
class CMainWindow;

struct Key {
    bool isDown;
    double lastTime;
};

class CEvent {  
    public:
        CEvent( CMainWindow* mainWindow );
        ALLEGRO_EVENT_QUEUE* getEventQueue();
        void processEvents();
        void toggleKey( int keyCode, bool isDown );
        bool isKeyDown( int keyCode );
        bool isKeyDownTimed( int keyCode, int msTime = 500 );

    private:
        ALLEGRO_EVENT_QUEUE* m_eventQueue;
        CMainWindow* m_mainWindow;
        Key* m_keys;
};

#endif
