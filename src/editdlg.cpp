#include <qdialog.h>
#include <qlabel.h>
#include <qpushbt.h>
#include <qstring.h>

#include "editdlg.h"

EditDialog::EditDialog( QString text, const char *editText, const char *caption,                         QWidget *parent, const char *name, bool modal ) :
                                               QDialog( parent, name, modal )
{
  setCaption( caption );

  ushort LEFT = 20;
  ushort MARGIN = 5;
  ushort LEWIDTH = 250;
  ushort BWIDTH = 100;
  ushort HEIGHT = 25;

  QLabel *lb = new QLabel( text, this);
  lb->adjustSize();
  lb->move( LEFT, 20 );

  le = new QLineEdit( this );
  le->setText( editText );
  le->setGeometry( LEFT, 40, LEWIDTH, HEIGHT );

  QPushButton *ok, *cancel;
  ok = new QPushButton( "Ok", this );
  ok->setDefault( true );
  ok->setGeometry( LEWIDTH - 2* BWIDTH - MARGIN, 80, BWIDTH, HEIGHT );
  connect( ok, SIGNAL(clicked()), SLOT(accept()) );

  cancel = new QPushButton( "Cancel", this );
  cancel->setGeometry( LEWIDTH - BWIDTH, 80, BWIDTH, HEIGHT );
  connect( cancel, SIGNAL(clicked()), SLOT(reject()) );

  le->setFocus();
  le->selectAll();

  setFixedSize( 300, 120 );
}

