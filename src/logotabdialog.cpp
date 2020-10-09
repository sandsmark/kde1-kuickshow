/*
 *  This file is part of kISDN, Copyright (C) 1998 by
 *
 *  Thorsten Westheider <twesthei@phya1.physik.uni-bielefeld.de>
 *  Carsten Pfeiffer <carpdjih@sp.zrz.tu-berlin.de>
 *
 ****************************************************************/


#include <qpixmap.h>

#include "logotabdialog.h"


LogoTabDialog::LogoTabDialog(QWidget *parent, const char *name, bool modal, bool defaultButton):QTabDialog(parent, name, modal)
{
  KIconLoader *loader = kapp->getIconLoader();
  Logo = new QLabel(this);
  Logo->setPixmap(QPixmap(loader->loadIcon("logo.gif")));
  Logo->move(10, 370);
  if ( defaultButton )
  {
    setDefaultButton();
    connect( this, SIGNAL( defaultButtonPressed() ), 
             this, SLOT( resetDefaults() ) );
  }

  hasWidget = false;
}


LogoTabDialog::LogoTabDialog(const char **XPM, QWidget *parent, const char *name, bool modal):QTabDialog(parent, name, modal)
{
  KIconLoader *loader = kapp->getIconLoader();
  Logo = new QLabel(this);
  Logo->setPixmap(QPixmap(loader->loadIcon(**XPM)));
  Logo->move(10, 370);
  hasWidget = false;
}


LogoTabDialog::LogoTabDialog(const char **XPM, uint x, uint y, QWidget *parent, const char *name, bool modal):QTabDialog(parent, name, modal)
{
  KIconLoader *loader = kapp->getIconLoader();
  Logo = new QLabel(this);
  Logo->setPixmap(QPixmap(loader->loadIcon(**XPM)));
  Logo->move(x, y);
  hasWidget = false;
}


LogoTabDialog::LogoTabDialog(uint x, uint y, QWidget *parent, const char *name, bool modal):QTabDialog(parent, name, modal)
{
  KIconLoader *loader = kapp->getIconLoader();
  Logo = new QLabel(this);
  Logo->setPixmap(QPixmap(loader->loadIcon("logo.gif")));
  Logo->move(x, y);
  hasWidget = false;
}


void LogoTabDialog::addWidget( QWidget *widget )
{
  w = widget;
  w->setGeometry( 0, 0, width(), height() - Logo->height() - 10 );
  hasWidget = true;
}

void LogoTabDialog::resetDefaults()
{}


void LogoTabDialog::resizeEvent( QResizeEvent *e )
{
  QTabDialog::resizeEvent( e );
  uint MARGIN = 5;
  Logo->resize( Logo->pixmap()->width(), Logo->pixmap()->height() );
  Logo->move( 2*MARGIN, height() - MARGIN - Logo->height() );
  if ( hasWidget )
    w->resize( width(), height() - Logo->height() - 2*MARGIN );
}
