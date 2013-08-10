#ifndef _CMAINWINDOW_H_
    #define _CMAINWINDOW_H_

struct ALLEGRO_DISPLAY;
class CEvent;
class CScreen;

enum {
    GAME_SCREEN = 0,
    PAUSE_SCREEN = 1
};

class CMainWindow {
    public:
        CMainWindow();
        int execute();
        bool init();
        void exit();
        CEvent* getEvent();
        ALLEGRO_DISPLAY* getDisplay();
        double  getMiliseconds();
        void changeScreenTo( int screenCode );

    private:
        bool m_isRunning;
        ALLEGRO_DISPLAY* m_display;
        CEvent* m_event;
        CScreen* m_activeScreen;
        CScreen* m_pauseMenu;
        CScreen* m_gameScreen;

        void    update();
        void    render();
};

#endif
