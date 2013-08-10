#include "CEntity.h"

CEntity::CEntity( int x, int y ) {
    m_posX = x;
    m_posY = y;
    m_shouldRemove = false;
    m_canCollide = true;
}

CEntity::CEntity() {
    m_posX = 0;
    m_posY = 0;
    m_shouldRemove = false;
    m_canCollide = true;
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

bool CEntity::isColliding( CEntity* entity, int x, int y ) {
    int playerX = x;
    int playerY = y;
    int entityX = entity->getPosX();
    int entityY = entity->getPosY();

    if ( playerX < ( entityX + 64 ) && playerY < ( entityY + 64 ) &&
            ( playerX + 64 ) > entityX && ( playerY + 64 ) > entityY ) {
        return true;
    }

    return false;
}

bool CEntity::isReadyToRemove() {
    return m_shouldRemove;
}

bool CEntity::canCollide() {
    return m_canCollide;
}

void CEntity::hurt( int damage ) {
    m_health -= damage;

    if ( m_health <= 0 ) {
        m_shouldRemove = true;
    }   
}
