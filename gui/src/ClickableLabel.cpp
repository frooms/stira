#include "ClickableLabel.h"
#include <iostream>
#include <iostream>

ClickableLabel::ClickableLabel( QWidget * parent ) :QLabel(parent)
{
    connect( this, SIGNAL( clicked() ), this, SLOT( slotClicked() ) );
}

//---------------------------------------------------------------------------

void ClickableLabel::slotClicked()
{
    std::cout << "slot Clicked" << std::endl << std:: flush;
}

//---------------------------------------------------------------------------

void ClickableLabel::mousePressEvent ( QMouseEvent * event )
{
    Qt::MouseButton myButton = event->button();

    if (myButton == Qt::LeftButton)
    {
        std::cout << "Left mouse button click at ( " << event->pos().x() << ", " << event->pos().y() << ")" << std::endl << std:: flush;
    }

    if (myButton == Qt::RightButton)
    {
        std::cout << "Right mouse button click at ( " << event->pos().x() << ", " << event->pos().y() << ")" << std::endl << std:: flush;
    }

    emit clicked();
}

//---------------------------------------------------------------------------

void ClickableLabel::wheelEvent(QWheelEvent* event)
{
    //Most mouse types work in steps of 15 degrees, in which case the delta value is a multiple of 120; i.e., 120 units * 1/8 = 15 degrees.

    std::cout << "mouse wheel event: delta = " << event->delta() << std::endl << std:: flush;
}
