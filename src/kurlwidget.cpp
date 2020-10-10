/*
 *  This file is part of kISDN, Copyright (C) 1998 by
 *
 *  Thorsten Westheider <twesthei@phya1.physik.uni-bielefeld.de>
 *  Carsten Pfeiffer <carpdjih@sp.zrz.tu-berlin.de>
 *
 ****************************************************************/


#include "kurlwidget.h"


KURLWidget::KURLWidget( char *url, QWidget *parent, const char *name ) :
            QLabel( url, parent, name )
{
  u = url;
  this->adjustSize();
  this->show();
}

KURLWidget::~KURLWidget()
{
}


void KURLWidget::mousePressEvent( QMouseEvent * )
{
  KURL ku( u );
  if ( !ku.isMalformed() )
  {
    kfm = new KFM();
    kfm->openURL( u );
  }
}


void KURLWidget::paintEvent(QPaintEvent *)
{
  QPainter p;
  p.begin(this);
  p.setPen(blue);
  p.drawText(rect(), AlignLeft, u);
  p.end();
}

#include "kurlwidget.moc"
