/****************************************************************************
** $Id: kuickshow.h,v 1.11 1998/09/22 18:44:16 gis Exp $
**
** KuickShow - a fast and comfortable image viewer based on Rasterman's Imlib
**
** Created : 98
**
** Copyright (C) 1998 by Carsten Pfeiffer.  All rights reserved.
**
****************************************************************************/

#ifndef KUICKSHOW_H
#define KUICKSHOW_H

#include <qdir.h>
#include <qevent.h>
#include <qpopmenu.h>
#include <qstring.h>
#include <qwidget.h>

#include <drag.h>
#include <kconfig.h>
#include <kfileinfo.h>
#include <ktmainwindow.h>

#include "aboutwidget.h"
#include "filefinder.h"
#include "fileview.h"
#include "kuickconfigdlg.h"
#include "kuickdata.h"
#include "imlibwidget.h"
#include "mainwidget.h"


class KuickShow : public KTMainWindow
{
  Q_OBJECT

public:
  KuickShow( QString start="", const char *name=0 );

protected:
  ~KuickShow();

  virtual void          closeEvent ( QCloseEvent * );
  //void 			initImlibParams( ImlibConfig *, ImlibInitParams * );

private:

  bool	       		eventFilter( QObject *, QEvent * );
  void                  resizeEvent( QResizeEvent * );
  bool 			isImage( KFileInfo * );
  //void 			initImlib();
  void 			readProperties( KConfig * );
  void 			saveProperties( KConfig * );

  void 			saveSettings();

  uint 			viewItem, renameItem, deleteItem, printItem;
  uint 			viewerCount;
  bool 			noBrowser;
  QString 		highlightWorkaround;

  AboutWidget           *aboutWidget;
  MainWidget            *mainWidget;
  QPopupMenu            *menu;
  QString 		oldSlideName;
  FileFinder            *finder;
  FileView     		*box;
  KToolBar              *tBar;
  KStatusBar  		*sBar;
  KuickConfigDialog 	*dialog;
  KuickData             *kdata;
  //ImlibData             *id;
  ImlibWidget 		*viewer;

private slots:
  void 			slotQuit() { delete this; }
  void 			slotConfigApplied();
  void 			slotConfigRejected();
  void 			messageCantLoadImage( const char * );
  void         		showImage( KFileInfo * );
  void		        fileHighlighted( KFileInfo * );
  void			dirSelected( KFileInfo * );
  void		        configuration();
  void	      		about();
  void	       		help();
  void 			startSlideShow();
  void 			nextSlide();
  void			viewerDeleted();
  void 			deleteFinder();
  void 			dropEvent( KDNDDropZone * );
  void 			printImage( QString );
  void 			printImage( QPixmap *, QString );
  bool 			deleteFile( QString );

  void 			slotToggleHidden( int );
};


#endif
