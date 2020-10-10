#include <qkeycode.h>

#include "filefinder.h"

FileFinder::FileFinder( QWidget *parent, const char *name ) :
                                            QLineEdit( parent, name )
{
  // make this widget just as large, as the font is + 12 Pixels
  int height = this->fontMetrics().height() + 8;
  setFixedSize( 100, height );
  setFrame( true );

  setGeometry( 2, 2, 96, height-4 );
  setFocusPolicy( ClickFocus );
}

FileFinder::~FileFinder()
{
}


QString FileFinder::contents()
{
  QString s = this->text();
  s.detach();
  return s;
}


void FileFinder::focusOutEvent( QFocusEvent * )
{
  emit sigDeleteMe();
}

void FileFinder::keyPressEvent( QKeyEvent *e )
{
  int key = e->key();
  if ( key == Key_Escape || key == Key_Return )
  {
    emit sigDeleteMe();
    e->accept();
  }
  else
  {
    QLineEdit::keyPressEvent( e );
    e->ignore();
  }
}

#include "filefinder.moc"
