#ifndef _CSANDBALL_H_
    #define _CSANDBALL_H_

#include "CEntity.h"

class CGameScreen;
class CPlayer;
class CEntity;

class CSandBall : public CEntity {
    public:
        CSandBall( CGameScreen* gameScreen, CPlayer* player );
        void render( int cameraX, int cameraY );
        void update();
        int getPosX();
        int getPosY();
        bool isColliding( CEntity* ent, int x, int y );

    private:
        float m_posX;
        float m_posY;
        float  m_xVelocity;
        float m_yVelocity;
        int m_ticksAlive;
        CGameScreen* m_gameScreen;
        CPlayer* m_player;
};

#endif
