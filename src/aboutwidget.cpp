/*
 *  This file is part of KuickShow, Copyright (C) 1998 by
 *
 *  Thorsten Westheider <twesthei@phya1.physik.uni-bielefeld.de>
 *  Carsten Pfeiffer <carpdjih@sp.zrz.tu-berlin.de>
 *
 ****************************************************************/

#include <stdio.h>

#include <kapp.h>

#include "aboutwidget.h"
#include "version.h"

#include "imlibconfig.h"

AboutWidget::AboutWidget(QWidget *parent, const char *name) : QFrame(parent, name, WStyle_Customize )
{
  setFrameStyle( WinPanel | Raised );

  GBox = new QGroupBox(this);
  GBox->setGeometry( 10, 10, width()-20, height()-20 );
  GBox->setTitle(i18n("About"));
  GBox->show();
  GBox->installEventFilter( this );

  GBox->setPalette( QPalette( QColor( white ) ) );
  GBox->setBackgroundMode( PaletteBackground );
  
  if ( !pm.load( kapp->kde_datadir() + "/kuickshow/pics/logo.gif" ) )
    fprintf( stderr, "logo.gif not found");
  else
  {
    Logo = new QLabel(GBox);
    Logo->resize( pm.width(), pm.height() );
    Logo->setPixmap(pm);
    Logo->installEventFilter( this );
    Logo->show();
  }

  Version = new QLabel("Release "KUICKSHOWVERSION, this);
  Version->setFont(QFont("helvetica", 12, QFont::Bold));
  Version->adjustSize();
  Version->installEventFilter( this );
  Version->setPalette( QPalette( QColor( white ) ) );
  Version->setBackgroundMode( PaletteBackground );

  if ( !pm.load( kapp->kde_datadir() + "/kuickshow/pics/eqx2.gif" ) )
    fprintf( stderr, "logo.gif not found");
  else
  {
    Tux = new QLabel( GBox );
    Tux->resize( pm.width(), pm.height() );
    Tux->setPixmap( pm );
    Tux->installEventFilter( this );
    Tux->show();
  }
  
  /*
  ImlibConfig idata;
  idata.fastrender = false; idata.remap = false; idata.dither16bit = true;
  QString filename = kapp->kde_datadir() + "/kuickshow/pics/eqx2.gif";
  im = new ImlibWidget( 0, &idata, GBox );
  if ( im->showNextImage( filename.data() ) )
  {
    im->show();
    im->installEventFilter( this );
  }
  else im = 0L;
  */
  
  Authors = new QLabel("was brought to you by", GBox);
  Authors->adjustSize();
  Authors->installEventFilter( this );
  Authors->show();

  Carsten = new QLabel("equinoxe Software", GBox);
  Carsten->adjustSize();
  Carsten->installEventFilter( this );
  Carsten->show();

  Copy = new QLabel("(C) 1998", GBox);
  Copy->adjustSize();
  Copy->installEventFilter( this );
  Copy->show();

  Homepage = new KURLWidget("http://kisdn.headlight.de", GBox);
  QFont link;
  link.setUnderline(true);
  Homepage->setFont(link);
  Homepage->adjustSize();

  /*  License = new QPushButton( i18n("License"), this );
  License->adjustSize();
  License->setGeometry( 25, 290, Homepage->width(), License->height() );
  connect( License, SIGNAL( clicked() ), this, SLOT( showLicense() ));
  */

  setFocus();
}

AboutWidget::~AboutWidget()
{
  //  if ( im ) delete im;
}

/*
void AboutWidget::showLicense()
{
  QString  licensepath = kapp->kde_datadir() + "/kisdn/LICENSE";

  SplashScreen *ss = new SplashScreen(licensepath, 0, false);
  ss->setCaption("kISDN "KISDNVERSION" License");
  ss->exec();
  delete ss;
}
*/

QSize AboutWidget::minimumSize()
{
  QSize s(328, 314); // fix this!
  return s;
}


void AboutWidget::resizeEvent( QResizeEvent * )
{
  ushort  margin = 10;
  GBox->resize(width()-2*margin, height()-2*margin);

  uint    w      = GBox->width();
  uint    wmid   = w/2;
  uint    h      = GBox->height();
  uint 	  hmid   = h/2;

  if ( Logo ) Logo->move( wmid - Logo->width()/2, 20 );
  //  if ( im ) im->move( wmid - im->width()/2, hmid - im->height()/2 );
  if ( Tux ) Tux->move( wmid - Tux->width()/2, hmid - Tux->height()/2 );
  if (Logo) Version->move( Logo->x() + Logo->width() - Version->width(), Logo->y() + Logo->height() + 10);
  Authors->move( wmid - Authors->width()/2, 250 );
  Carsten->move( wmid - Carsten->width()/2, Authors->y() + Authors->height() + 5 );
  Copy->move( wmid - Copy->width()/2, Carsten->y() + Carsten->height() + 5 );
  Homepage->move( margin, h-margin - Homepage->height() );
  //  License->move( margin, h-margin - License->height() );
}

bool AboutWidget::eventFilter( QObject *, QEvent *e )
{
  int ret = false;
  if ( e->type() == Event_MouseButtonPress )
  {
    delete this;
    ret = true;
  }

  return ret;
}

#include "aboutwidget.moc"
