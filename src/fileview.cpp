/****************************************************************************
** $Id: fileview.cpp,v 1.7 1998/09/22 18:44:07 gis Exp $
**
** Definition of something or other
**
** Created : 979899
**
** Copyright (C) 1998 by Carsten Pfeiffer.  All rights reserved.
**
****************************************************************************/

#include <qdir.h>
#include <qdialog.h>
#include <qkeycode.h>
#include <qpoint.h>

#include <kapp.h>

#include "editdlg.h"
#include "fileview.h"

FileView::FileView( QString start, bool s, int filter, int sorting,
		    const char *nameFilter,
		    QWidget *parent, const char *name ):
  KFileView( start, s, filter, sorting, nameFilter, parent, name )
{
  menu = new QPopupMenu( 0L, "popupmenu" );
  viewItem = menu->insertItem( i18n("View") );
  menu->insertSeparator();
  renameItem = menu->insertItem( i18n("Rename...") );
  deleteItem = menu->insertItem( i18n("Delete") );
  menu->insertSeparator();
  printItem = menu->insertItem( i18n("Print image...") );
  menu->insertSeparator();
  cdirItem = menu->insertItem( i18n("Change directory...") );
  menu->insertSeparator();
  propertiesItem = menu->insertItem( i18n("Properties") );
  connect( menu, SIGNAL( activated( int ) ),
           this, SLOT( popupMenuActivated( int )) );
  connectFileSelected( this, SLOT( emitFileSelected( KFileInfo * )) );

  kfm = new KFM;
  //  kfm->allowKFMRestart( true ); // straaaaange things....
  if ( !kfm->isKFMRunning() )
  {
    delete kfm;
    kfm = 0L;
  }
}


FileView::~FileView()
{
  if ( kfm!=0L )
    delete kfm;
}

void FileView::mousePressEvent( QMouseEvent *e )
{
  if ( e->button() == RightButton )
  {
    bool isFile = false;
    bool whitespace = false;

    int col = findCol( e->pos().x() );
    int row = findRow( e->pos().y() );
    whitespace = ( col == -1 || row == -1 ||
		 (col * rowsVisible + row) > (int) count()-1 );

    if ( !whitespace ) // a dir/file is selected, not just whitespace
    {
      highlightItem( row, col );
      isFile = !current()->isDir();
      if ( isFile ) KFileView::mousePressEvent( e );
    }

    menu->setItemEnabled( viewItem, isFile & !whitespace );
    menu->setItemEnabled( renameItem, (kfm!=0L) & !whitespace );
    menu->setItemEnabled( deleteItem, isFile & !whitespace );
    menu->setItemEnabled( printItem, isFile & !whitespace);
    menu->setItemEnabled( propertiesItem, (kfm!=0L) & !whitespace );

    menu->popup( mapToGlobal( e->pos() ) );
  }

  else KFileView::mousePressEvent( e );
}


void FileView::keyPressEvent( QKeyEvent *e )
{
  if ( e->key() == Key_G && e->state() == ControlButton )
    changeDirDialog();
  else
    KFileView::keyPressEvent( e );

  e->accept();
}

void FileView::popupMenuActivated( int item )
{
  if ( item == (int) viewItem ) emitFileSelected( current() );
  else if ( item == (int) cdirItem ) changeDirDialog();

  else if ( item == (int) renameItem )
  {
    QString file = filename( current() );
    QString text = i18n("Rename ") + file + i18n(" to:");
    EditDialog *dlg = new EditDialog( text, file.data(), i18n("Rename item"),
				      this, "editdlg", true );
    if ( dlg->exec() != QDialog::Accepted )
      return;

    QString newname = dlg->text();

    if ( !newname.isEmpty() )
    {
      kfm->move( file, newname );
      reloadDir();
    }
    delete dlg;
  }

  else if ( item == (int) deleteItem )
    emit( sigDeleteItem( filename( current() ) ) );

  else if ( item == (int) propertiesItem )
    kfm->openProperties( filename( current() ) );

  else if ( item == (int) printItem ) emit sigPrintImage( filename( current() ));
}


void FileView::fileCompletion( const char *text )
{
  if ( QString file = findCompletion( text, true ) )
    setCurrentItem( file.data() );
}


void FileView::changeDirDialog()
{
  QString text = i18n("Switch to directory: ");
  EditDialog *dlg = new EditDialog( text, directory().data(),
				    i18n("Change directory"),
				    this, "editdlg", true );
  if ( dlg->exec() != QDialog::Accepted )
    return;
  QString newDir = dlg->text();
  if ( directory() != newDir )
    enterDir( newDir.data() );

  delete dlg;
}


void FileView::cdHome()
{
  enterDir( QDir::homeDirPath().data() );
}

#include "fileview.moc"
