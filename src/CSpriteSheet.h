#ifndef _CSPRITESHEET_H_
    #define _CSPRITESHEET_H_

class CSpriteSheet {
    public:
        CSpriteSheet( char* filename );
        ALLEGRO_BITMAP* getSprite( int x, int y );

    private:
        ALLEGRO_BITMAP* m_spriteSheet;
};

#endif
