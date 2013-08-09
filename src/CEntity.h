#ifndef _CENTITY_H_
    #define _CENTITY_H_

class CEntity {
    public:
        CEntity( int x, int y );
        CEntity();
        int getPosX();
        void setPosX( int x );
        int getPosY();
        void setPosY( int y );
        virtual void render() = 0;
        virtual void update() = 0;

    private:
        int m_posX;
        int m_posY;
};

#endif
