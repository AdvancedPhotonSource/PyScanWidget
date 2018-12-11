/*
* Copyright (c) 2016, UChicago Argonne, LLC. All rights reserved.
*
* Copyright 2016. UChicago Argonne, LLC. This software was produced 
* under U.S. Government contract DE-AC02-06CH11357 for Argonne National 
* Laboratory (ANL), which is operated by UChicago Argonne, LLC for the 
* U.S. Department of Energy. The U.S. Government has rights to use, 
* reproduce, and distribute this software.  NEITHER THE GOVERNMENT NOR 
* UChicago Argonne, LLC MAKES ANY WARRANTY, EXPRESS OR IMPLIED, OR 
* ASSUMES ANY LIABILITY FOR THE USE OF THIS SOFTWARE.  If software is 
* modified to produce derivative works, such modified software should 
* be clearly marked, so as not to confuse it with the version available 
* from ANL.

* Additionally, redistribution and use in source and binary forms, with 
* or without modification, are permitted provided that the following 
* conditions are met:
*
*   * Redistributions of source code must retain the above copyright 
*     notice, this list of conditions and the following disclaimer. 
*
*   * Redistributions in binary form must reproduce the above copyright 
*     notice, this list of conditions and the following disclaimer in 
*     the documentation and/or other materials provided with the 
*     distribution. 
*
*   * Neither the name of UChicago Argonne, LLC, Argonne National 
*     Laboratory, ANL, the U.S. Government, nor the names of its 
*     contributors may be used to endorse or promote products derived 
*     from this software without specific prior written permission. 

* THIS SOFTWARE IS PROVIDED BY UChicago Argonne, LLC AND CONTRIBUTORS 
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS 
* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL UChicago 
* Argonne, LLC OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, 
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT 
* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN 
* ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
* POSSIBILITY OF SUCH DAMAGE.
*/

#include <ScanAdminWidget.h>
#include <QPushButton>
#include <QLabel>
#include <QFileInfo>
#include <QFileDialog>
#include <PythonLoader.h>

/*---------------------------------------------------------------------------*/

ScanAdminWidget::ScanAdminWidget(Preferences* preferences, QWidget* parent)
: QWidget(parent)
{

   m_preferences = preferences;
   // Create GUI components
   createComponents();

   if(m_preferences != NULL)
   {
      QString lastSave = m_preferences->readValueKey(Preferences::LastScanSave).toString();
      if(lastSave.length() > 0)
      {
         loadScan(lastSave);
      }
   }
}

/*---------------------------------------------------------------------------*/

ScanAdminWidget::~ScanAdminWidget()
{


}

/*---------------------------------------------------------------------------*/

void ScanAdminWidget::createComponents()
{

   QPushButton* btnSave = new QPushButton("Save Scan");
   connect (btnSave,
            SIGNAL(clicked()),
            this,
            SLOT(saveScan()));
   QPushButton* btnLoad = new QPushButton("Load Scan");
   connect (btnLoad,
            SIGNAL(clicked()),
            this,
            SLOT(loadScan()));

   m_playTabWidget = new ScanBuilderWidget(m_preferences, this);

   m_tabWidget = new QTabWidget();
   m_tabWidget->setAutoFillBackground(true);

   m_tabWidget->addTab(m_playTabWidget, QIcon(), "Play Scan Builder");

   QHBoxLayout* layout = new QHBoxLayout();
   QVBoxLayout* mainLayout = new QVBoxLayout();

   layout->addWidget(btnSave);
   layout->addWidget(btnLoad);

   m_scanFilename = new QLabel();

   QHBoxLayout* hlayout = new QHBoxLayout();
   hlayout->addWidget(new QLabel("Scan filename:"));
   hlayout->addWidget(m_scanFilename);


   mainLayout->addLayout(hlayout);
   mainLayout->addLayout(layout);
   mainLayout->addWidget(m_tabWidget);

   setLayout(mainLayout);
}
/*---------------------------------------------------------------------------*/

ScanAttributeTableModel* ScanAdminWidget::getPlayVariableModel()
{
   return m_playTabWidget->getVariableModel();
}

/*---------------------------------------------------------------------------*/


bool ScanAdminWidget::loadScan()
{

   QString fileName = QFileDialog::getOpenFileName(this,
      "Open scan file", ".", "Scan (*.xml *.py)");
   return loadScan(fileName);

}

/*---------------------------------------------------------------------------*/

bool ScanAdminWidget::loadScan(QString fileName)
{

   // Dialog returns a null string if user press cancel.
   if (fileName.isNull() || fileName.isEmpty()) return false;

   QFileInfo fileInfo = QFileInfo(fileName);
   m_fileBaseName = fileInfo.baseName();
   m_filePath = fileName;
   QString path = fileInfo.path();

   if(m_filePath.endsWith(".py"))
   {
       try
       {
           if(false == PythonLoader::inst()->isLoaded())
           {
               PythonLoader::inst()->init();
           }
           QMap<QString, QString> variables;
           //if(!PythonLoader::inst()-> loadFunction(path, m_fileBaseName, "getVariableDict"))
           //    QMessageBox::warning(NULL, "Error loading scan", "Error loading scan. Missing global variable called 'variableDict'.");
           if(!PythonLoader::inst()-> loadFunction(path, m_fileBaseName, "getVariableDict"))
           {
               QMessageBox::warning(NULL, "Error loading scan", "Error loading scan. Missing global variable called 'variableDict'.");
               return false;
           }

           PythonLoader::inst()->setRetCnt(m_fileBaseName, "getVariableDict", 1);
           PythonLoader::inst()->callFunc(m_fileBaseName, "getVariableDict", PythonLoader::RET_STR_DICT);

           ScanAttributeTableModel* play_attributes = m_playTabWidget->getVariableModel();
           if(PythonLoader::inst()->getRetStrDict(m_fileBaseName, "getVariableDict", &variables))
           {
               foreach (QString key, variables.keys())
               {
                   qDebug()<< key <<" : "<< variables[key];
                   play_attributes->addAttr(key, variables[key], "float", true);
               }
               m_scanFilename->setText(fileName);
               return true;
           }
        }
       catch(PythonLoader::pyException ex)
       {
           qDebug()<<ex.what();
           QMessageBox::warning(NULL, "Error loading scan", "Error loading scan. Missing global variable called 'variableDict'.");
           return false;
       }
   }
   return false;
}

/*---------------------------------------------------------------------------*/

QString ScanAdminWidget::getName()
{

   return m_fileBaseName;

}

/*---------------------------------------------------------------------------*/

QString ScanAdminWidget::getPath()
{

   return m_filePath;

}

/*---------------------------------------------------------------------------*/


void ScanAdminWidget::updateScan()
{

   QString fileName = m_scanFilename->text();

   if (fileName.isNull() || fileName.isEmpty()) return;
   if (fileName.endsWith(".py")) return;

}

/*---------------------------------------------------------------------------*/

