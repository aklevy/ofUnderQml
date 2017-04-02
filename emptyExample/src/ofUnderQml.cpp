#include "ofUnderQml.h"
#include <GL/glew.h>
#include <QtQuick/qquickwindow.h>
//--------------------------------------------------------------

ofUnderQml::ofUnderQml()
{

    connect(this, &QQuickItem::windowChanged, this, &ofUnderQml::handleWindowChanged);

    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::AllButtons);
    setFlag(ItemAcceptsInputMethod, true);
    setFlag(ItemIsFocusScope, true);

}

//--------------------------------------------------------------

void ofUnderQml::init(QQuickView& view)
{
    if (!m_ofApp)
    {
        m_ofApp = new ofAppQml();
    }
    m_ofApp->setup(view);

}


//--------------------------------------------------------------

void ofUnderQml:: transformToPixCoord()
{
    // rotate upside down
    glRotatef(-180,1,0,0);

    // translate to make the origin on the down left corner
    glTranslatef(-1,-1,0.);

    // scale to a coordinate system width x height
    QSize winSize = window()->size();//* window()->devicePixelRatio();
    glScalef(2./winSize.width(),2./winSize.height(),1.);
}
//--------------------------------------------------------------

void ofUnderQml::handleWindowChanged(QQuickWindow *win)
{

    if (win)
    {
        connect(win, &QQuickWindow::beforeSynchronizing, this, &ofUnderQml::sync, Qt::DirectConnection);
        connect(win, &QQuickWindow::sceneGraphInvalidated, this, &ofUnderQml::cleanup, Qt::DirectConnection);
        connect(window(), &QQuickWindow::beforeRendering, this, &ofUnderQml::render, Qt::DirectConnection);

        // If we allow QML to do the clearing, they would clear what we paint
        // and nothing would show.
        win->setClearBeforeRendering(false);
    }
}

//--------------------------------------------------------------

void ofUnderQml::cleanup()
{
    if (m_ofApp) {
        delete m_ofApp;
        m_ofApp = 0;
    }
}


//--------------------------------------------------------------

void ofUnderQml::sync()
{
    if (!m_ofApp)
    {
        m_ofApp = new ofAppQml();
    }
    glUseProgram(0);

    // update ofApp
    m_ofApp->update();

    window()->resetOpenGLState();
}


//--------------------------------------------------------------

void ofUnderQml::render()
{
    if (m_ofApp)
    {

        glUseProgram(0);
        glPushMatrix();
        transformToPixCoord();

        // render ofApp
        m_ofApp->draw();
        glPopMatrix();

        // call this at the end of each draw()
        window()->resetOpenGLState();

        // force to update the render
        m_ofApp->update();
    }
}
//--------------------------------------------------------------


void ofUnderQml::keyPressEvent(QKeyEvent *event)
{
    if(event)
    {
        m_ofApp->keyPressed(event->key());
    }
}


//--------------------------------------------------------------


void ofUnderQml::keyReleaseEvent(QKeyEvent *event)
{
    if(event)
    {
        m_ofApp->keyReleased(event->key());
    }
}

//--------------------------------------------------------------

void ofUnderQml::mousePressEvent(QMouseEvent *event)
{
    if(event)
    {
        setFocus(true); //set focus to get key inputs
        m_ofApp->mousePressed(event->pos().x(),
                              event->pos().y(),event->button());
    }
}

//--------------------------------------------------------------

void ofUnderQml::mouseMoveEvent(QMouseEvent *event)
{
    if(event)
    {
        m_ofApp->mouseDragged(event->pos().x(),
                              event->pos().y(),event->button());
    }
}

//--------------------------------------------------------------

void ofUnderQml::mouseReleaseEvent(QMouseEvent *event)
{
    if(event)
    {
        m_ofApp->mouseReleased(event->pos().x(),
                               event->pos().y(),event->button());
    }
}
//--------------------------------------------------------------

void ofUnderQml::hoverEnterEvent(QHoverEvent *event)
{
    if(event)
    {
        m_ofApp->mouseEntered(event->pos().x(),
                              event->pos().y());
    }
}

//--------------------------------------------------------------

void ofUnderQml::hoverMoveEvent(QHoverEvent *event)
{
    if(event)
    {
        m_ofApp->mouseMoved(event->pos().x(),
                            event->pos().y());
    }
}
//--------------------------------------------------------------

void ofUnderQml::hoverLeaveEvent(QHoverEvent *event)
{
    if(event)
    {
        m_ofApp->mouseExited(event->pos().x(),
                             event->pos().y());
    }
}
