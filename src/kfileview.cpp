/****************************************************************************
** $Id: kfileview.cpp,v 1.3 1998/12/22 16:11:21 carp Exp $
**
** KFileView - a small filebrowser window based on kfile
**
** Created : 98
**
** Copyright (C) 1998 by Carsten Pfeiffer.  All rights reserved.
**
****************************************************************************/

#include <qdir.h>
#include <qmsgbox.h>
#include <qstring.h>

#include <kapp.h>

#include "kfileview.h"

KFileView::KFileView( QString start, bool s, int filter, int sorting,
		      const char *nameFilter, QWidget *parent,
		      const char *name)
	: KFileSimpleView( s, (QDir::SortSpec)sorting, parent, name )
{
  myShowsHidden = (filter & QDir::Hidden);

  viewDir = new KDir;
  viewDir->setNameFilter( nameFilter );
  if ( !start.isEmpty() )
    viewDir->setPath( start.data() );
  connect( viewDir, SIGNAL( newFilesArrived(const KFileInfoList*) ),
	   this, SLOT( slotAddNewItems(const KFileInfoList*) ) );
  addItemList( viewDir->entryInfoList( filter, sorting ) );

  connectDirSelected( this, SLOT( slotDirSelected( KFileInfo *) ) );
}


KFileView::~KFileView()
{
  delete viewDir;
}


int KFileView::currentIndex()
{
  return ( curCol * rowsVisible + curRow );
}

KFileInfo* KFileView::current() // currently selected file
{
  return ( KFileInfo *) at( currentIndex() );
}

KFileInfo* KFileView::firstFile( bool moveCursor ) // the first _file_ in list
{
  if ( !hasFiles() ) return 0L;
  uint index = 0;
  while ( isDir( ++index ) ); // just move ahead to the first non-directory
  if ( moveCursor ) highlightItem( index );
  return (KFileInfo *) at( index );
}

KFileInfo* KFileView::first( bool moveCursor ) // first item (file/directory) in list
{
  if ( isEmptyDir() ) return 0L;
  if ( moveCursor ) highlightItem( 1 );
  return (KFileInfo *) at( 1 ); // 0 = ".." directory
}

KFileInfo* KFileView::last( bool moveCursor ) // last file in list
{
  if ( isEmptyDir() ) return 0L;
  uint index = KFileInfoContents::count() - 1;
  if ( moveCursor ) highlightItem( index );
  return (KFileInfo *) at( index );
}

KFileInfo* KFileView::next( bool moveCursor ) // next file
{
  if ( isEmptyDir() ) return 0L;
  uint index = currentIndex() +1;
  uint count = KFileInfoContents::count() - 1;
  if ( index > count )
    index = count;
  if ( moveCursor ) highlightItem( index );
  return (KFileInfo *) at( index );
}

KFileInfo* KFileView::prev( bool moveCursor ) // guess what...
{
  if ( isEmptyDir() ) return 0L;
  int index = currentIndex() -1;
  if ( index < 1 )
    index = 1;
  if ( moveCursor ) highlightItem( index );
  return (KFileInfo *) at( index );
}

QString KFileView::directory()
{
  return viewDir->path();
}

void KFileView::slotDirSelected( KFileInfo *fi )
{
  QString oldDir = directory();
  QString newDir = filename( fi );

  viewDir->setURL( newDir );
  clear();
  addItemList( viewDir->entryInfoList( viewDir->filter(),
				       viewDir->sorting() ) );

  // DO NOT access KFileInfo fi anymore, it is already deleted by addItemList()

  /*
  // set selection if we're going to parent directory via ..
  if ( newDir.right( 2 )  == ".." )
  {
    int len = oldDir.length();
    int lastSlash = oldDir.findRev( "/", len -2 );
    QString selectedDir = oldDir.right( len - lastSlash -1 );
    selectedDir = selectedDir.left( selectedDir.length() -1 );
    selectedDir.detach();

    debug("currentDir: %s, dir to be highlighted: %s", directory().data(), selectedDir.data() );
    //    setSorting( viewDir->sorting() ); // hack to force a full sort
//    setCurrentItem( selectedDir );
  }
  */
}

int KFileView::removeItem( KFileInfo *fi )
{
  KFileInfoList *list = (KFileInfoList *)
			viewDir->entryInfoList( viewDir->filter(),
						viewDir->sorting() );

  KFileInfo *newFi = current();
  if ( fi == newFi ) // current == fi to delete?
    newFi = prev();

  if ( list->remove( fi ) )
  {
    clear();
    
    addItemList( list );
    setCurrentItem( 0L, newFi );
    return currentIndex();
  }

  return -1;
}

void KFileView::slotAddNewItems( const KFileInfoList *fi )
{
  addItemList( fi );
}

void KFileView::setNameFilter( const char *filter )
{
  viewDir->setNameFilter( filter );
}

const char *KFileView::nameFilter()
{
  return viewDir->nameFilter();
}

void KFileView::enterDir( const char *dir )
{
  KFileInfo fi ( dir, "" );
  if ( fi.isDir() )
  {
    viewDir->setURL( dir );
    clear();
    addItemList( viewDir->entryInfoList( viewDir->filter(),
					 viewDir->sorting() ) );
  }
  else
  {
    QString text = i18n("I can't change into\n\"");
    text += dir;
    text += i18n("\"\nas it is not a directory.");
    QMessageBox::warning(this, i18n("Not a directory"), text );
  }
}

void KFileView::refresh( bool reRead )
{
  if ( reRead ) {
    viewDir->setURL( directory() );
  }

  clear();
  addItemList( viewDir->entryInfoList( viewDir->filter(), viewDir->sorting() ) );
}


// KFileInfo::absURL() is sort of broken... KFileInfo::fileName(), too, tho :-/
QString KFileView::filename( KFileInfo *fi )
{
  if ( fi )
    return ( directory() + fi->fileName() );
  else return "";
}

/*
void KFileView::setSorting( int sorting, bool update )
{
  viewDir->setSorting( sorting );
  if ( update )
    refresh(); // don't reread from disk
}
*/

void KFileView::setFilter( int filter, bool update )
{
  viewDir->setFilter( filter );
  if ( update )
    refresh(); // don't reread from disk
}


void KFileView::setCurrentPosition( int item )
{
  if ( item >= 0 ) {
    KFileSimpleView::highlightItem( item );
  }
}


void KFileView::slotToggleHidden()
{
  int filter = QDir::Files | QDir::Dirs;

  if ( myShowsHidden ) {
    myShowsHidden = false;
  }
  else {
    filter |= QDir::Hidden;
    myShowsHidden = true;
  }

  setFilter( filter );
}


void KFileView::mousePressEvent( QMouseEvent *e )
{
  KFileSimpleView::mousePressEvent( e );

  if ( !useSingle() || !isDir( currentIndex() ) ) {
    // make sure, selected column is completely visible
#if KDE_VERSION_MAJOR > 0
    while ( curCol > leftCell() && !isColCompletelyVisible( curCol ) ) {
      setLeftCell( leftCell()+1 );
    }
#endif
  }
}

#include "kfileview.moc"
