#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>
#include <QMouseEvent>
#include "../../stira/common/common/Point.h"

class ClickableLabel : public QLabel
{
    Q_OBJECT
public:
    ClickableLabel( QWidget * parent = 0 );
    ~ClickableLabel(){}

    /** \brief Gets the point in the image where the user clicked */
    stira::common::Point<int> GetPointClicked();

signals:
    void leftButtonClicked();
    void middleButtonClicked();
    void rightButtonClicked();
    void wheelUpEvent();
    void wheelDownEvent();

public slots:

protected:
    void mousePressEvent ( QMouseEvent * event ) ;
    void wheelEvent(QWheelEvent* event);

    int mClickX;
    int mClickY;
    int mClickStartX;
    int mClickStartY;
};

#endif // CLICKABLELABEL_H
