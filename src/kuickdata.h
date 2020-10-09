/****************************************************************************
** $Id: kuickdata.h,v 1.3 1998/09/23 20:01:11 gis Exp $
**
** KuickData, a class containing/loading/saving  all preferences of KuickShow
**
** Created : 98
**
** Copyright (C) 1998 by Carsten Pfeiffer.  All rights reserved.
**
****************************************************************************/

#ifndef KUICKDATA_H
#define KUICKDATA_H

#include <qstring.h>

#include "imlibconfig.h"

class KuickData
{
public:
  KuickData();
  ~KuickData();

  void 		load();
  void 		save();

  QString 	fileFilter;
  uint 		slideDelay;
  bool 		preloadImage;
  ImlibConfig   *idata;
};


#endif
