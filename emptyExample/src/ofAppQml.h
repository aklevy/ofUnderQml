#pragma once

//#include <QtGui/QOpenGLFunctions>

#include "ofMain.h"

#include <QtQuick/qquickwindow.h>
#include <QtQuick/QQuickItem>
#include <QtQuick/QQuickView>

/* Class similar to ofApp
 * but with every input connected to ofUnderQml class
 *  every position is in OpenGL coordinate system ([-1,1])
 *  and not in pixels (as usually in OF)
*/

class ofAppQml : public QObject, public ofBaseApp
{
    Q_OBJECT

public:
    ofAppQml();
    ~ofAppQml();

    // connect Qml objects to this class
    void setup(QQuickView& view);

public slots:
    void draw();
    void update();

    void keyPressed(int key);
    void keyReleased(int key);

    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);

private:
    // fps counter (ofGetFrameRate() does not work here so a manual fps counter is required)
    ofFpsCounter m_fps;


};
