/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the demonstration applications of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/
#include "ofUnderQml.h"
#include <GL/glew.h>
#include <QtQuick/qquickwindow.h>
//--------------------------------------------------------------

ofUnderQml::ofUnderQml()
    : m_scale(0)
{

    connect(this, &QQuickItem::windowChanged, this, &ofUnderQml::handleWindowChanged);

    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::AllButtons);
    setFlag(ItemAcceptsInputMethod, true);
    setFlag(ItemIsFocusScope, true);
  /*  setFlag(ItemHasContents, true);
    setFlag(ItemAcceptsDrops, true);*/

}

//--------------------------------------------------------------

void ofUnderQml::init(QQuickView& view)
{
    QObject* qmlButton = view.rootObject()->findChild<QObject*>("changeColorButton");
    if(qmlButton)
       connect(qmlButton, SIGNAL(pressed()), this, SLOT(changeColor()));
    if (!m_ofApp)
    {
        m_ofApp = new ofAppQml();
     }
    m_ofApp->setup();

}

//--------------------------------------------------------------

void ofUnderQml::setScale(qreal sc)
{
    if (sc == m_scale)
        return;
    m_scale = sc;
    emit scaleChanged();
    if (window())
        window()->update();
}

//--------------------------------------------------------------

ofVec2f ofUnderQml:: GLCoordToPixCoord(QPoint pt)
{
    ofVec2f size = ofVec2f(window()->size().width(),window()->size().height());
    return ofVec2f(pt.x()/size.x*2-1., 1. - pt.y()/size.y*2 );

}


//--------------------------------------------------------------

void ofUnderQml:: transformToPixCoord()
{
    // rotate upside down
    glRotatef(180,1,0,0);

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
       // connect(window(), &QQuickWindow::beforeRendering, m_ofApp, &ofAppQml::draw, Qt::DirectConnection);
    }
   glUseProgram(0);

   glPushMatrix();
  transformToPixCoord();
   // update ofApp
   m_ofApp->update();
   glPopMatrix();

   window()->resetOpenGLState();

    m_ofApp->setScale(m_scale);
    m_ofApp->setWindow(window());


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
        setFocus(true);
        qDebug() << event->pos();
        ofVec2f posGLCoord = GLCoordToPixCoord(event->pos());
        m_ofApp->mousePressed(event->pos().x(),
                              event->pos().y(),event->button());
    }
}

//--------------------------------------------------------------

void ofUnderQml::mouseMoveEvent(QMouseEvent *event)
{
    if(event)
    {
        ofVec2f posGLCoord = GLCoordToPixCoord(event->pos());
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
        ofVec2f posGLCoord = GLCoordToPixCoord(event->pos());
        m_ofApp->mouseEntered(event->pos().x(),
                              event->pos().y());
    }
}

//--------------------------------------------------------------

void ofUnderQml::hoverMoveEvent(QHoverEvent *event)
{
    if(event)
    {
        ofVec2f posGLCoord = GLCoordToPixCoord(event->pos());
        m_ofApp->mouseMoved(event->pos().x(),
                            event->pos().y());
    }
}
//--------------------------------------------------------------

void ofUnderQml::hoverLeaveEvent(QHoverEvent *event)
{
    if(event)
    {
        ofVec2f posGLCoord = GLCoordToPixCoord(event->pos());

        m_ofApp->mouseExited(event->pos().x(),
                             event->pos().y());
    }
}
