/****************************************************************************
** $Id: .emacs,v 1.3 1998/02/20 15:06:53 gis Exp $
**
** The main widget, that contains the fileview, dirview and preview of images
**
** Created : 98
**
** Copyright (C) 1998 by Carsten Pfeiffer.  All rights reserved.
**
****************************************************************************/

#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <qstring.h>
#include <qwidget.h>

#include <knewpanner.h>

#include "fileview.h"
#include "kuickdata.h"

class MainWidget : public QWidget
{
  Q_OBJECT
  
public:
  MainWidget( QString, KuickData *, QWidget *parent, const char *name=0L);
  ~MainWidget();
  
  FileView* 	getFileBox() { return box; }
  
private:
  FileView 	*box;
  
};


#endif
