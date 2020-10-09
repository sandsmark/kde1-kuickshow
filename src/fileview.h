/****************************************************************************
** $Id: fileview.h,v 1.6 1998/09/22 18:44:09 gis Exp $
**
** Definition of something or other
**
** Created : 979899
**
** Copyright (C) 1998 by Carsten Pfeiffer.  All rights reserved.
**
****************************************************************************/

#ifndef FILEVIEW_H
#define FILEVIEW_H

#include <qdir.h>
#include <qevent.h>
#include <qpopmenu.h>

#include <kfm.h>

#include "kfileview.h"


class FileView : public KFileView
{
  Q_OBJECT

public:
  FileView( QString, bool, int filter, int sorting,
	    const char *nameFilter, QWidget *parent=0, const char *name=0 );
  ~FileView();

protected:
  QPopupMenu    *menu;
  KFM           *kfm;
  uint 		viewItem, renameItem, deleteItem, printItem, propertiesItem;
  uint 		cdirItem;

  void 		changeDirDialog();
  void 		keyPressEvent( QKeyEvent * );
  void 		mousePressEvent( QMouseEvent * );

public slots:
  void 		fileCompletion( const char * );

protected slots:
  void 		emitFileSelected( KFileInfo *fi ) { emit sigFileSelected( fi ); }
  void		popupMenuActivated( int );
  void		cdHome();

signals:
  void 		sigFileSelected( KFileInfo * );
  void 		sigDeleteItem( QString );
  void 		sigPrintImage( QString );

};


#endif
