#include <allegro5/allegro.h>
#include "CTile.h"
#include "CSpriteSheet.h"

CTile::CTile( ALLEGRO_BITMAP* bitmap, int x, int y ) : CEntity( x, y ) {
    m_image = bitmap;
}

void CTile::render( int cameraX, int cameraY ) {
    al_draw_bitmap( m_image, (float) this->getPosX() - cameraX, (float) this->getPosY() - cameraY, 0 );
}

void CTile::update() {

}
