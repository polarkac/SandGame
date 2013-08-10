#ifndef _CPLAYER_H_
    #define _CPLAYER_H_

#include <vector>
#include "CEntity.h"

class CEvent;
class CGameScreen;
struct ALLEGRO_BITMAP;

class CPlayer : public CEntity {
    public:
        CPlayer( CGameScreen* gameScreen, CEvent* event, int x, int y );
        ~CPlayer();
        void render( int cameraX, int cameraY );
        void update();
        void init();
        void loadImage( char filename[] );
        void move();
        void jump();
        bool isColliding( CEntity* entity, int x, int y );
        bool isColliding( CEntity* entity );

    private:
        CEvent* m_event;
        CGameScreen* m_gameScreen;
        ALLEGRO_BITMAP* m_image;
        float m_frame;
        float m_yVelocity;
        float m_xVelocity;
};

#endif
