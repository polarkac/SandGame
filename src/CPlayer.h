#ifndef _CPLAYER_H_
    #define _CPLAYER_H_

#include <vector>
#include "CEntity.h"

class CEvent;
struct ALLEGRO_BITMAP;

class CPlayer : public CEntity {
    public:
        CPlayer( CEvent* event );
        CPlayer( CEvent* event, int x, int y );
        void render();
        void update();
        void init();
        void loadImage( char filename[] );
        void move();
        void isColliding( CEntity* entity );

    private:
        CEvent* m_event;
        ALLEGRO_BITMAP* m_image;
        float m_frame;
        bool m_isMoving;
        bool m_isJumping;
        float m_yVelocity;
        float m_xVelocity;
        std::vector<CEntity*>* m_collidingEntities;
};

#endif
