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

    void setup();

    void setWindow(QQuickWindow *window) { m_window = window;}
    void setScale(float sc) { m_scale = sc; }



public slots:
    void draw();
    void drawVideo();
    void update();

    void changeColor(){m_color.set(ofRandom(0,255),
                                   ofRandom(0,255),
                                   ofRandom(0,255));}

    void keyPressed(int key);
    void keyReleased(int key);

    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);

private:
    // app's general
    //QSize m_viewportSize;
    QQuickWindow *m_window;

    // circle
    float m_scale;
    ofColor m_color;
    ofVec2f m_position;

    // video
    ofVideoGrabber m_videoGrabber;
    ofFbo       m_fbo;
    ofTrueTypeFont m_font;
    ofPixels m_pix;


};
