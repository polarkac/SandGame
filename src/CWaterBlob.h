#ifndef _CWATERBLOB_H_
    #define _CWATERBLOB_H_

#include "CEntity.h"

class CGameScreen;

class CWaterBlob : public CEntity {
    public:
        CWaterBlob( CGameScreen* gameScreen, int x, int y );
        void render( int cameraX, int cameraY );
        void update();
        void move();
        void hurt( int damage );

    private:
        ALLEGRO_BITMAP* m_image;
        float m_frame;
        int m_centerX;
        int m_xVelocity;
        CGameScreen* m_gameScreen;
        int m_radius;
        int m_hurtTime;
};

#endif
