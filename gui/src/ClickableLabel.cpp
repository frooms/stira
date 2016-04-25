#include "ClickableLabel.h"
#include <iostream>
#include <iostream>

ClickableLabel::ClickableLabel( QWidget * parent ) :QLabel(parent)
{
}

//---------------------------------------------------------------------------

stira::common::Point<int> ClickableLabel::GetPointClicked()
{
    return stira::common::Point<int>( mClickX, mClickY );
}

//---------------------------------------------------------------------------

void ClickableLabel::mousePressEvent ( QMouseEvent * event )
{
    Qt::MouseButton myButton = event->button();

    mClickX = event->pos().x();
    mClickY = event->pos().y();

    if (myButton == Qt::LeftButton)
    {
        emit leftButtonClicked();
        std::cout << "Left mouse button click at ( " << mClickX << ", " << mClickY << ")" << std::endl << std:: flush;
    }

    if (myButton == Qt::RightButton)
    {
        emit rightButtonClicked();
        std::cout << "Right mouse button click at ( " << mClickX << ", " << mClickY << ")" << std::endl << std:: flush;
    }
}

//---------------------------------------------------------------------------

void ClickableLabel::wheelEvent(QWheelEvent* event)
{
    //Most mouse types work in steps of 15 degrees, in which case the delta value is a multiple of 120; i.e., 120 units * 1/8 = 15 degrees.

    int delta = event->delta();
    std::cout << "mouse wheel event: delta = " << delta << std::endl << std:: flush;
    if (delta > 0)
    {
        emit wheelUpEvent();
    }
    else
    {
        emit wheelDownEvent();
    }
}
