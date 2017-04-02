#include "ofAppQml.h"

//--------------------------------------------------------------

ofAppQml::ofAppQml()
{

}

//--------------------------------------------------------------

ofAppQml::~ofAppQml()
{

}

//--------------------------------------------------------------
void ofAppQml::setup(QQuickView& view)
{

}

//--------------------------------------------------------------

void ofAppQml::draw()
{
    //update fps
    m_fps.newFrame();

    // clear buffer before drawing
    ofClear(100);
    ofBackground(100);

}

//--------------------------------------------------------------

void ofAppQml::update()
{



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
