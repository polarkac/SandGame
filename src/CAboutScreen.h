#ifndef _CABOUTSCREEN_H_
    #define _CABOUTSCREEN_H_

#include <string>
#include "CScreen.h"

struct ALLEGRO_FONT;

class CAboutScreen : public CScreen {
    public:
        CAboutScreen( CMainWindow* mainWindow );
        void render();
        void update();

    private:
        std::string* m_lines;
        ALLEGRO_FONT* m_font;

};

#endif
