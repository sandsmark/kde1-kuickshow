/****************************************************************************
** $Id: imlibwidget.h,v 1.11 1998/09/24 16:26:56 gis Exp $
**
** ImlibWidget: maps an Xlib window with Imlib's contents on a QWidget
**
** Created : 98
**
** Copyright (C) 1998 by Carsten Pfeiffer.  All rights reserved.
**
****************************************************************************/

#ifndef IMLIBWIDGET_H
#define IMLIBWIDGET_H

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/shape.h>

#ifdef TrueColor
#undef TrueColor
#endif

#include <qevent.h>
#include <qpopmenu.h>
#include <qwidget.h>

#include "imlibconfig.h"

class ImlibWidget : public QWidget
{
  Q_OBJECT

public:

  ImlibWidget( const char *filename, ImlibConfig *_idata=0, QWidget *parent=0, const char *name=0 );

  void 		 flipImage( bool );
  bool		 loadImage( const char * );
  bool 		 preloadImage( const char * );
  void 		 rotate( int );
  void 		 scrollImage( int, int, bool restrict=true );
  void		 setFullscreen( bool );
  void 		 setPopupMenu( bool );
  bool 		 showNextImage( const char * );
  void 		 zoomImage( float );

  bool 		 isFullscreen;

protected:
  ImlibConfig    *idata;

  ~ImlibWidget(); // deletes itself, just tell it to close( true );

  void 		 init( const char *filename );
  bool 		 loadImageInternal( char *, bool cacheOnly=false );
  void 		 centerImage();
  void 	       	 almostCenterImage();
  void 		 paintImage();
  void 		 showImage();
  void           changeBrightness( int, bool rerender = true );
  void 		 changeContrast( int, bool rerender = true );
  void 		 changeGamma( int, bool rerender = true );
  void           setImageModifier() {
#if 0
      imlib_context_set_image(im);
      imlib_context_set_color_modifier(mod);
#endif
  }

  void 		 closeEvent( QCloseEvent * );
  void           resizeEvent( QResizeEvent * );
  void		 keyPressEvent( QKeyEvent * );
  void 		 keyReleaseEvent( QKeyEvent * );
  void 		 mousePressEvent( QMouseEvent * );
  void 	         mouseReleaseEvent( QMouseEvent * );
  void 		 mouseMoveEvent( QMouseEvent * );

  uint 		 itemViewerZoomIn, itemViewerZoomOut, itemViewerFlipH;
  uint 		 itemRotate90, itemRotate270, itemViewerFlipV, itemViewerPrint;
  uint           itemViewerSave;
  uint           desktopWidth, desktopHeight;
  uint 		 xmove, ymove;	// used for scrolling the image with the mouse
  int		 xpos, ypos; 	// top left corner of the image
  int 		 xzoom, yzoom;  // used for zooming the image with the mouse
  uint 		 xposPress, yposPress;
  bool		 stillResizing, deleteImlibConfig, deleteImlibData;
  bool           imlibModifierChanged, shiftPressed;

  QPopupMenu     *viewerMenu, *gammaMenu, *brightnessMenu, *contrastMenu;
  QString 	 currentFilename;
  QWidget        *transWidget;

  Display        *disp;
  Window         win;
  QPixmap         *p;
  Pixmap         m;
  QPixmap     *im, *imCache;
  uint 		 cw, ch;
  uint 		 w, h, wCache, hCache;
  QString	 cachedImage;

public slots:
  void 		 zoomIn() 	 { zoomImage( 1.5 ); }
  void 		 zoomOut() 	 { zoomImage( 0.66666667 ); }
  void 		 flipHoriz() 	 { flipImage( true ); }
  void 		 flipVert() 	 { flipImage( false ); }
  void 		 printImage();
  void 		 rotate90() 	  { rotate( 1 );            }
  void 		 rotate270() 	  { rotate( -1 );           }
  void           moreBrightness() { changeBrightness(  1 ); }
  void           lessBrightness() { changeBrightness( -1 ); }
  void           moreContrast()   { changeContrast(  1 );   }
  void           lessContrast()   { changeContrast( -1 );   }
  void           moreGamma()      { changeGamma(  1 );      }
  void           lessGamma()      { changeGamma( -1 );      }

protected slots:
  void 		 renderImage( uint, uint, bool dontMove=false );
  void           saveImage();

signals:
  void 		 sigBadImage( const char * );
  void 		 sigPrintImage( QPixmap *, QString );

};


#endif
