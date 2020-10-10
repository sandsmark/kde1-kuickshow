#include "mainwidget.h"

MainWidget::MainWidget( QString startDir, KuickData *kdata, QWidget *parent,
			const char *name ) : QWidget ( parent, name )
{	
  // FIXME, make sorting and filter configurable

  box = new FileView( startDir, true, (QDir::Dirs | QDir::Files),
		      (QDir::Name | QDir::IgnoreCase | QDir::DirsFirst),
		      kdata->fileFilter, this, "fileview" );

}


MainWidget::~MainWidget()
{

}

#include "mainwidget.moc"
