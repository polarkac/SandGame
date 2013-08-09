#ifndef _CSCREEN_H_
    #define _CSCREEN_H_

class CMainWindow;

class CScreen {
    public:
        CScreen( CMainWindow* const mainWindow, CScreen* parent = NULL );
        CScreen* getParent();
        virtual void render() = 0;
        virtual void update() = 0;

    protected:
        CScreen* m_parent;
        CMainWindow* m_mainWindow;
};

#endif
