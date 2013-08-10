#ifndef _CSANDBALL_H_
    #define _CSANDBALL_H_

#include "CEntity.h"

class CSandBall : public CEntity {
    public:
        CSandBall( int x, int y, int xVelocity );
        void render( int cameraX, int cameraY );
        void update();
        int getPosX();
        int getPosY();

    private:
        float m_posX;
        float m_posY;
        float  m_xVelocity;
        float m_yVelocity;
        int m_ticksAlive;
};

#endif
