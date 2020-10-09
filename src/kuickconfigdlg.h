/****************************************************************************
** $Id: kuickconfigdlg.h,v 1.5 1998/09/23 20:01:09 gis Exp $
**
** Configuration dialog for KuickShow
**
** Created : 98
**
** Copyright (C) 1998 by Carsten Pfeiffer.  All rights reserved.
**
****************************************************************************/

#ifndef KUICKCONFIGDLG_H
#define KUICKCONFIGDLG_H

#include <qchkbox.h>
#include <qevent.h>
#include <qgrpbox.h>
#include <qlined.h>
#include <qwidget.h>

#include <kintegerline.h>

#include "logotabdialog.h"

class KuickConfigDialog : public LogoTabDialog
{
  Q_OBJECT

public:
  KuickConfigDialog( QWidget *parent=0, const char *name=0, bool modal=true );
  ~KuickConfigDialog();

  void 		setConfig( QString, uint, bool, bool, bool, bool, bool,
			   bool, bool, bool, uint );
  void		getConfig( QString &, uint &, bool &, bool &, bool &, bool &,
			   bool &, bool &, bool &, bool &, uint & );

private:
  uint  	TOPMARGIN;
  uint 		MARGIN;
  QGroupBox 	*gbox1, *gbox2;
  QCheckBox     *cbFullscreen, *cbShrinkToScreen, *cbRemap, *cbFastrender;
  QCheckBox 	*cbDither16bit, *cbDither8bit, *cbPreload, *cbOwnPalette;
  QLineEdit     *editFilter;
  KIntegerLine  *editSlide, *editMaxCache;

  void 		resizeEvent( QResizeEvent * );
  void 		resetDefaults();

private slots:
  void 		useOwnPalette();

};

#endif
