#ifndef _CENTITY_H_
    #define _CENTITY_H_

class CEntity {
    public:
        CEntity( int x, int y );
        CEntity();
        virtual ~CEntity();
        virtual int getPosX();
        void setPosX( int x );
        virtual int getPosY();
        void setPosY( int y );
        virtual void render( int cameraX, int cameraY ) = 0;
        virtual void update() = 0;
        bool isColliding( CEntity* entity, int x, int y );
        bool isReadyToRemove();
        bool canCollide();

    protected:
        bool m_shouldRemove;
        bool m_canCollide;

    private:
        int m_posX;
        int m_posY;
};

#endif
