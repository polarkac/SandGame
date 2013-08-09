#include <iostream>
#include <allegro5/allegro.h>
#include "CSpriteSheet.h"

CSpriteSheet::CSpriteSheet( char* filename ) {
    m_spriteSheet = al_load_bitmap( filename );
    if ( m_spriteSheet == NULL ) {
        std::cerr << "Can not load sprite sheet ( " << filename << " )." << std::endl;
    }
}

ALLEGRO_BITMAP* CSpriteSheet::getSprite( int x, int y ) {
    ALLEGRO_BITMAP* bitmap = al_create_sub_bitmap( m_spriteSheet, x, y, 64, 64 );

    return bitmap;
}   
