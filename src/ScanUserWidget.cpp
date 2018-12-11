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

#include <ScanUserWidget.h>

/*---------------------------------------------------------------------------*/

ScanUserWidget::ScanUserWidget(QWidget* parent)
: QWidget(parent)
{

   m_preferences = new Preferences();

   m_selectedScan = NULL;

   // Create GUI components
   createComponents();

   if(m_preferences != NULL)
   {
      QString loadList = m_preferences->readValueKey(Preferences::UserScans).toString();
      m_loadTable->getModel()->fromStringList(loadList);
   }

}

/*---------------------------------------------------------------------------*/

ScanUserWidget::~ScanUserWidget()
{

   if(m_preferences != NULL)
   {
      QString loadList = m_loadTable->getModel()->toStringList();
      m_preferences->saveValueKey(Preferences::UserScans, loadList);
      delete m_preferences;
   }

   m_preferences = NULL;

   foreach (ScanAdminWidget *saw, m_loadTable->getModel()->getAttrs())
   {
      saw->updateScan();
   }

}


/*---------------------------------------------------------------------------*/

void ScanUserWidget::createComponents()
{

   createVariableWidget();
   createLoadWidget();
   createLayout();

}

/*---------------------------------------------------------------------------*/

void ScanUserWidget::createLayout()
{

   QVBoxLayout* vlayout = new QVBoxLayout();
   vlayout->setContentsMargins(0, 0, 0, 0);
   vlayout->setSpacing(0);
   vlayout->addLayout(m_VariableLayout);
   vlayout->addLayout(m_loadLayout);

   setLayout(vlayout);

}

/*---------------------------------------------------------------------------*/

void ScanUserWidget::createLoadWidget()
{

   QVBoxLayout* layout = new QVBoxLayout();
   layout->setContentsMargins(0, 0, 0, 0);
   layout->setSpacing(0);
   layout->addStretch(0);

   m_loadTable = new ScanLoadTable();

   QFont font;
   font.setBold(true);
   font.setWeight(75);

   QLabel* lblLoad = new QLabel("Load table:");
   lblLoad->setFont(font);

   layout->addWidget(lblLoad);
   layout->addWidget(m_loadTable);
   connect(m_loadTable,
           SIGNAL(chosenItem(ScanAdminWidget*)),
           this,
           SLOT(chosenItem(ScanAdminWidget*)));

   connect(m_loadTable,
           SIGNAL(removeItem(int)),
           this,
           SLOT(removeItem(int)));

   m_loadLayout = layout;

}

/*---------------------------------------------------------------------------*/

void ScanUserWidget::chosenItem(ScanAdminWidget *saw)
{

   m_playTabWidget->setModel(saw->getPlayVariableModel());

   m_selectedScan = saw;

   emit newScanSelected(saw);

}

/*---------------------------------------------------------------------------*/

void ScanUserWidget::createVariableWidget()
{

   QVBoxLayout* layout = new QVBoxLayout();
   layout->setContentsMargins(0, 0, 0, 0);
   layout->setSpacing(1);

   m_playTabWidget = new ScanVariableTable(false, this);


   m_tabWidget = new QTabWidget();
   m_tabWidget->setAutoFillBackground(true);

   m_tabWidget->addTab(m_playTabWidget, QIcon(), "Scan Variables");


   QFont font;
   font.setBold(true);
   font.setWeight(75);

   QLabel* lblVar = new QLabel("Variable table:");
   lblVar->setFont(font);



   layout->addWidget(lblVar);
   layout->addWidget(m_tabWidget);

   m_VariableLayout = layout;

}

/*---------------------------------------------------------------------------*/

ScanAdminWidget* ScanUserWidget::getSelectedScan()
{

   return m_selectedScan;

}

/*---------------------------------------------------------------------------*/

void ScanUserWidget::removeItem(int selectRow)
{

   m_playTabWidget->removeItems();

}

/*---------------------------------------------------------------------------*/
