#include "CEntity.h"

CEntity::CEntity( int x, int y ) {
    m_posX = x;
    m_posY = y;
}

CEntity::CEntity() {
    m_posX = 0;
    m_posY = 0;
}

CEntity::~CEntity() {}

int CEntity::getPosX() {
    return m_posX;
}   

void CEntity::setPosX( int x ) {
    m_posX = x;
}

int CEntity::getPosY() {
    return m_posY;
}

void CEntity::setPosY( int y ) {
    m_posY = y;
}
