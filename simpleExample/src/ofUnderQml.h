
#pragma once

#include "ofAppQml.h"




class ofUnderQml : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(qreal scale READ scale WRITE setScale NOTIFY scaleChanged)

public:
    ofUnderQml();
    void init(QQuickView& view);

    qreal scale() const { return m_scale; }
    void setScale(qreal sc);

    ofVec2f GLCoordToPixCoord(QPoint pt);
    void transformToPixCoord();

signals:
    void scaleChanged();


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
    qreal m_scale;
    ofAppQml *m_ofApp{};


};

