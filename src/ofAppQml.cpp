#include "ofAppQml.h"



//--------------------------------------------------------------
ofAppQml::ofAppQml()
    : m_scale(0),
      m_color(ofColor::aquamarine),
      m_position(640)
{
    ofSetCircleResolution(100);
    // ofEnableSmoothing();
     ofEnableAlphaBlending();

    //  ofEnableNormalizedTexCoords();
    //  ofEnableDepthTest();

    //   log verbose
    ofSetLogLevel(OF_LOG_VERBOSE);

    // load font
      m_font.load("Roboto-Light.ttf",50,true, false, true);

    // allocate fbo
    //  ofDisableArbTex();
    //ofEnableNormalizedTexCoords();
     m_fbo.allocate(640,640,GL_RGBA);
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
void ofAppQml::setup()
{
    // initialize video
    m_videoGrabber.setVerbose(true);
    m_videoGrabber.listDevices();
    m_videoGrabber.setDeviceID(0);

    //    m_videoGrabber.initGrabber(1280,720);
    if(m_videoGrabber.setup(1280,720,false))
        ofLog() << "plop";

}

//--------------------------------------------------------------

void ofAppQml::draw()
{

    // clear buffer before drawing
    ofClear(100);
    ofBackground(100);


    // draw video, for unknown reason, the grabber's texture contains nothing
    // so we manually copy the grabber's pixels to a texture
    drawVideo();

    // draw font
    if(m_font.isLoaded())
        m_font.drawString("PLOP",400,400);

    // draw smth
    ofPushStyle();
    ofSetColor(m_color);
    ofDrawCircle(m_position,100*m_scale);
    ofPopStyle();
    //ofDrawBitmapString("fps : " + ofToString(ofGetFrameRate()),100,300);

   if(m_fbo.isAllocated() )//&& m_window)
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
        shared_ptr<ofBaseRenderer> rende = ofGetCurrentRenderer();//->bind(&m_fbo);
        ofBaseGLRenderer* glRend = dynamic_cast<ofBaseGLRenderer*>(rende.get());

       glRend->bind(m_fbo);

        glRend->background(0,0,0,0);

       /*glRend->pushMatrix();
        glRend->rotateX(180);
        // glRotatef(180,1,0,0);
        glRend->translate(-1.,-0.5,0.);
        //glTranslatef(-1,-1,0.);
        glRend->scale(2./640,2./640,1.);*/

        glRend->pushStyle();
        ofSetColor(0,0,255,255);
        // glRend->drawString(m_font,"PLOP",0,0 );
        // glRend->drawString("PLOP",0,0 ,0);
        glRend->drawCircle(m_position.x,m_position.y,0.,100);//300,300,0,100);
       // glRend->popMatrix();
        glRend->popStyle();

        glRend->unbind(m_fbo);
    }
    // glRend->bind(m_fbo);
    /*     m_fbo.bind();
       ofClear(0);
        glPushMatrix();

        ofClear(0);
       // ofDrawCircle(-0.5,-0.5,.5);
       // glRotatef(180,1,0,0);
        glTranslatef(-1,-1,0.);
        glScalef(1./640,1./640,1.);
        ofDrawCircle(m_position,100);

      glPopMatrix();
  //     ofDrawCircle(-1,-1,0.1);
        ofClearAlpha();
      //  glRend->unbind(m_fbo);
        m_fbo.unbind();

    }*/

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
