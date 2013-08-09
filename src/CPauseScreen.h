#ifndef _CPAUSESCREEN_H_
    #define _CPAUSESCREEN_H_

#include <string>
#include "CScreen.h"

class CMainWindow;

class CPauseScreen : public CScreen {
    public:
        CPauseScreen( CMainWindow* mainWindow, CScreen* parent );
        void render();
        void update();

    private:
        std::string* m_options;
        ALLEGRO_FONT* m_font;
        char m_selectedOption;
};

#endif
