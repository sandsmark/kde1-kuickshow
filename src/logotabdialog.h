/*
 *  This file is part of kISDN, Copyright (C) 1998 by
 *
 *  Thorsten Westheider <twesthei@phya1.physik.uni-bielefeld.de>
 *  Carsten Pfeiffer <carpdjih@sp.zrz.tu-berlin.de>
 *
 ****************************************************************/


#ifndef __LOGO_H
#define __LOGO_H

#include <qevent.h>
#include <qlabel.h>
#include <qtabdlg.h>

#include <kapp.h>
#include <kiconloader.h>


class LogoTabDialog : public QTabDialog
{
  Q_OBJECT

  public:

    LogoTabDialog(QWidget *parent=0, const char *name=0, bool modal=true,
                  bool defaultButton=false );
    LogoTabDialog(const char **, QWidget *parent = 0, const char *name = 0, bool modal = true);
    LogoTabDialog(const char **, uint, uint, QWidget *parent = 0, const char *name = 0, bool modal = true);
    LogoTabDialog(uint, uint, QWidget *parent = 0, const char *name = 0, bool modal = true);

    ~LogoTabDialog() {}
  
  void addWidget( QWidget * );

  protected:
    virtual void    resizeEvent( QResizeEvent * );

  protected slots:
    virtual void    resetDefaults();

  private:

  bool hasWidget;
  QWidget *w;
  QLabel  *Logo;

};

#endif

