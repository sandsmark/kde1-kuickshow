/****************************************************************************
** $Id: kuickdata.cpp,v 1.3 1998/09/23 20:01:10 gis Exp $
**
** KuickData, a class containing/loading/saving  all preferences of KuickShow
**
** Created : 98
**
** Copyright (C) 1998 by Carsten Pfeiffer.  All rights reserved.
**
****************************************************************************/

#include <kapp.h>
#include <kconfig.h>

#include "kuickdata.h"


KuickData::KuickData()
{
  fileFilter   = "*.jpg *.gif *.xpm *.ppm *.pgm *.png *.eim *.tiff";
  slideDelay   = 3000;
  preloadImage = true;
  idata = new ImlibConfig;
}

KuickData::~KuickData()
{
  delete idata;
}


void KuickData::load()
{
  KConfig *kc = kapp->getConfig();

  kc->setGroup( "GeneralConfiguration" );
  fileFilter   = kc->readEntry( "FileFilter", fileFilter );
  slideDelay   = kc->readNumEntry( "SlideShowDelay", slideDelay );
  preloadImage = ( kc->readEntry( "PreloadNextImage", "yes" ) == "yes" );

  idata->load( kc );
}


void KuickData::save()
{
  KConfig *kc = kapp->getConfig();
  kc->setGroup( "GeneralConfiguration" );
  kc->writeEntry( "FileFilter", fileFilter );
  kc->writeEntry( "SlideShowDelay", slideDelay );
  kc->writeEntry( "PreloadNextImage", preloadImage ? "yes" : "no" );

  idata->save( kc );

  kc->sync();
}
