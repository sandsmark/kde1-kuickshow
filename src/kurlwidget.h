/*  
 *  This file is part of kISDN, Copyright (C) 1998 by
 *
 *  Thorsten Westheider <twesthei@phya1.physik.uni-bielefeld.de>
 *  Carsten Pfeiffer <carpdjih@sp.zrz.tu-berlin.de>
 *
 ****************************************************************/
 
 
#ifndef __KURLWIDGET_H 
#define __KURLWIDGET_H

#include <qevent.h>
#include <qlabel.h>
#include <qpainter.h>
#include <qwidget.h>

#include <kfm.h>
#include <kurl.h>


class KURLWidget : public QLabel
{
  Q_OBJECT
  
  protected:

    KFM   *kfm;
    char  *u;

  public:
  
    KURLWidget( char *, QWidget *, const char *name=0 );
    ~KURLWidget();

    void  mousePressEvent ( QMouseEvent * );
    void  paintEvent ( QPaintEvent * );
};

#endif
