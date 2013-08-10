#ifndef _CGAMESCREEN_H_
    #define _CGAMESCREEN_H_

#include <vector>
#include "CScreen.h"

class CPlayer;
class CSpriteSheet;
class CEntity;
struct ALLEGRO_BITMAP;

struct Camera {
    int posX;
};

class CGameScreen : public CScreen {
    public:
        CGameScreen( CMainWindow* mainWindow, CScreen* parent = NULL);
        void render();
        void update();
        std::vector<CEntity*>* getVisibleEntities();

    private:
        int m_rColor;
        CPlayer* m_player;
        Camera* m_cameraControl;
        std::vector<CEntity*>* m_entities;
        CSpriteSheet* m_spriteSheet;
        ALLEGRO_BITMAP* m_background;
};

#endif
