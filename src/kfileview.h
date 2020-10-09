/****************************************************************************
** $Id: kfileview.h,v 1.3 1998/12/22 16:11:21 carp Exp $
**
** KFileView - a small filebrowser window based on kfile
**
** Created : 98
**
** Copyright (C) 1998 by Carsten Pfeiffer.  All rights reserved.
**
****************************************************************************/

#ifndef KFILEVIEW_H
#define KFILEVIEW_H

#include <qevent.h>

#include <kfileinfo.h>
#include <kfilesimpleview.h>
#include <kdir.h>

class KFileView : public KFileSimpleView
{
  Q_OBJECT

public:
  KFileView( QString start, bool s, int filter, int sorting,
	     const char *nameFilter="*",
	     QWidget *parent=0, const char *name=0);
  ~KFileView();

  int 		removeItem( KFileInfo * );
  int 		currentIndex();
  KFileInfo*	current();
  KFileInfo*	firstFile( bool moveCursor=true );
  KFileInfo*    first( bool moveCursor=true );
  KFileInfo*	last( bool moveCursor=true );
  KFileInfo* 	next( bool moveCursor=true );
  KFileInfo*	prev( bool moveCursor=true );
  QString 	directory();
  QString       filename( KFileInfo * );

  void		setNameFilter( const char * );
  void 		setCurrentPosition( int item );
  const char *  nameFilter();
  //  void		setSorting( int, bool update=true );
  QDir::SortSpec sorting();
  void 		setFilter( int, bool update=true );
  QDir::FilterSpec filter();

  bool		hasFiles()    { return numFiles() >= 1; }
  bool 		showsHidden() { return myShowsHidden; }
  bool 		isEmptyDir()  { return ( viewDir->count() <= 1 ); }
  void          enterDir( const char * );

protected:
  KDir 		*viewDir;
  bool          myShowsHidden;

public slots:
  void 		reloadDir() { refresh( true ); }
  void  	refresh( bool reRead=false );
  void		slotToggleHidden();


protected slots:
  void 		slotDirSelected( KFileInfo * );
  void 		slotAddNewItems( const KFileInfoList* );

  virtual void  mousePressEvent( QMouseEvent * );

};
	
#endif
