#include "ofAppQml.h"



//--------------------------------------------------------------
ofAppQml::ofAppQml()
    : m_scale(0),
      m_color(ofColor::aquamarine),
      m_position(640)
{
    // general OF settings
    ofSetCircleResolution(100);
    ofEnableSmoothing();
    ofEnableAlphaBlending();

    // log verbose
    ofSetLogLevel(OF_LOG_VERBOSE);

    // load font
    m_font.load("Roboto-Light.ttf",50,true, false, true);

    // allocate fbo
    m_fbo.allocate(1280,720,GL_RGBA);
}
//--------------------------------------------------------------
ofAppQml::~ofAppQml()
{
    if(m_fbo.isAllocated())
    {
        m_fbo.clear();
    }
    if(m_videoGrabber.isInitialized())
    {
        m_videoGrabber.close();
    }

}

//--------------------------------------------------------------
void ofAppQml::setup(QQuickView& view)
{
    // initialize video
    m_videoGrabber.setVerbose(true);
    m_videoGrabber.listDevices();
    m_videoGrabber.setDeviceID(0);
    m_videoGrabber.setup(1280,720,false);

    // setup QML connections
    QObject* qmlButton = view.rootObject()->findChild<QObject*>("changeColorButton");
    if(qmlButton)
       connect(qmlButton, SIGNAL(pressed()), this, SLOT(changeColor()));

}

//--------------------------------------------------------------

void ofAppQml::draw()
{
    //update fps
    m_fps.newFrame();

    // clear buffer before drawing
    ofClear(100);
    ofBackground(100);


    // draw video, for unknown reason, the grabber's texture contains nothing
    // so we manually copy the grabber's pixels to a texture
    drawVideo();


    // draw font
    if(m_font.isLoaded())
        m_font.drawString("fps : " + ofToString(m_fps.getFps()),400,400);

    // draw smth
    ofPushStyle();
    ofSetColor(m_color);
    ofDrawCircle(m_position,100*m_scale);
    ofPopStyle();

    // draw fbo
    if(m_fbo.isAllocated() )
    {
        m_fbo.draw(0,0,m_fbo.getWidth(),m_fbo.getHeight());
    }



}
//--------------------------------------------------------------

void ofAppQml::drawVideo()
{
    if(m_videoGrabber.isInitialized())
    {
        ofTexture texPlane;
        texPlane.loadData(m_videoGrabber.getPixels().getPlane(0));
        texPlane.draw(0,0);
    }
}

//--------------------------------------------------------------

void ofAppQml::update()
{
    if(m_videoGrabber.isInitialized())
    {
        m_videoGrabber.update();
    }
    if(m_fbo.isAllocated() )
    {
        // here coordinates are in OpenGL system (normalized)
        // so we convert the mouse position which is in pixels to normalized system
        // by converting we also flip vertically
        ofVec2f posNorm = ofVec2f(m_position.x/m_fbo.getWidth()-1.,m_position.y/m_fbo.getHeight() - 1.);
       // posNorm.x = posNorm.x/2. -1.;
        m_fbo.bind();
        ofBackground(0,0,0,0);

        ofPushStyle();
        ofSetColor(0,0,255,255);
        ofDrawCircle(posNorm,0.02);
        ofPopStyle();

        m_fbo.unbind();
    }


}

//--------------------------------------------------------------
void ofAppQml::keyPressed(int key)
{
}

//--------------------------------------------------------------
void ofAppQml::keyReleased(int key)
{

}

//--------------------------------------------------------------
void ofAppQml::mouseMoved(int x, int y)
{
    m_position.set(x,y);

}


//--------------------------------------------------------------
void ofAppQml::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofAppQml::mousePressed(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofAppQml::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofAppQml::mouseEntered(int x, int y)
{

}

//--------------------------------------------------------------
void ofAppQml::mouseExited(int x, int y)
{

}
