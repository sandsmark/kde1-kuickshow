/****************************************************************************
** $Id: aboutwidget.h,v 1.4 1998/09/16 22:26:14 gis Exp $
**
** AboutWidget, shows some logos and copyright notice
**
** Created : 979899
**
** Copyright (C) 1998 by Thorsten Westheider and
**                       Carsten Pfeiffer.
** All rights reserved.
**
****************************************************************************/

#ifndef ABOUTWIDGET_H
#define ABOUTWIDGET_H

#include <qevent.h>
#include <qdialog.h>
#include <qgrpbox.h>
#include <qlabel.h>
#include <qpixmap.h>
// #include <qpushbt.h>
#include <qwidget.h>

#include "imlibwidget.h"
#include "kurlwidget.h"

class AboutWidget : public QFrame
{
  Q_OBJECT

  private:

    QGroupBox    *GBox;
    QLabel       *Logo, *Tux, *Version, *Authors, *Thorsten, *Carsten, *Copy;
    QPixmap      pm;
  //    QPushButton  *License;
    KURLWidget   *Homepage;
    ImlibWidget  *im;
  
    bool eventFilter( QObject*, QEvent * );
    void resizeEvent( QResizeEvent * );

  //   private slots:

  //     void showLicense();

  public:

    AboutWidget(QWidget *parent = 0, const char *name = 0);

    QSize        minimumSize();

  protected:
    ~AboutWidget();
};


#endif
