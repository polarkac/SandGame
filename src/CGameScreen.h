#ifndef _CGAMESCREEN_H_
    #define _CGAMESCREEN_H_

#include <vector>
#include "CScreen.h"

class CPlayer;
class CTile;
class CSpriteSheet;

class CGameScreen : public CScreen {
    public:
        CGameScreen( CMainWindow* mainWindow, CScreen* parent = NULL);
        void render();
        void update();

    private:
        int m_rColor;
        CPlayer* m_player;
        std::vector<CTile*>* m_tiles;
        CSpriteSheet* m_spriteSheet;
};

#endif
