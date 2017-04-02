
#pragma once

#include "ofAppQml.h"




class ofUnderQml : public QQuickItem
{
    Q_OBJECT

public:
    ofUnderQml();
    void init(QQuickView& view);

    void transformToPixCoord();

signals:


public slots:
    void sync();
    void cleanup();
    void render();

private slots:
    void handleWindowChanged(QQuickWindow *win);


    // QQuickItem interface
protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void hoverEnterEvent(QHoverEvent *event) override;
    void hoverMoveEvent(QHoverEvent *event) override;
    void hoverLeaveEvent(QHoverEvent *event) override;

private:
    ofAppQml *m_ofApp{};


};

