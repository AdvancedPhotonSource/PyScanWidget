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

#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QApplication>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QGridLayout>
#include <QFileInfo>
#include <QFileDialog>
#include <QDebug>

#include <ScanBuilderWidget.h>

/*---------------------------------------------------------------------------*/

ScanBuilderWidget::ScanBuilderWidget(Preferences* preferences, QWidget* parent)
: QWidget(parent)
{

   // Create GUI components
   createComponents();

   m_preferences = preferences;

}

/*---------------------------------------------------------------------------*/

ScanBuilderWidget::~ScanBuilderWidget()
{


}

/*---------------------------------------------------------------------------*/

void ScanBuilderWidget::chosenItem(QList<ScanAttribute*>& attrList)
{

   if(!attrList.empty())
   {
      m_scanPropertyTable->removeItems();
      m_scanPropertyTable->addItems(attrList);
   }

}

/*---------------------------------------------------------------------------*/

void ScanBuilderWidget::createComponents()
{

   createControlWidget();

   createScanCommandWidget();

   createVariableWidget();
   createPropertyWidget();


   createLayout();

}

/*---------------------------------------------------------------------------*/

void ScanBuilderWidget::createControlWidget()
{

   QHBoxLayout* layout = new QHBoxLayout();

   layout->setContentsMargins(0, 0, 0, 0);
   layout->setSpacing(0);

   m_ControlLayout = layout;

}

/*---------------------------------------------------------------------------*/

void ScanBuilderWidget::createLayout()
{

   QHBoxLayout* hlayout = new QHBoxLayout();
   QVBoxLayout* vlayout = new QVBoxLayout();
   hlayout->setSpacing(30);

   // The scan command widget
   hlayout->addLayout(m_ScanCommandLayout);

   vlayout->addLayout(m_VariableLayout);
   vlayout->addLayout(m_PropertyLayout);

   hlayout->addLayout(vlayout);

   setLayout(hlayout);

}

/*---------------------------------------------------------------------------*/

void ScanBuilderWidget::createVariableWidget()
{

   QVBoxLayout* layout = new QVBoxLayout();

   m_variableTable = new ScanVariableTable(true);
   layout->setContentsMargins(0, 0, 0, 0);
   layout->setSpacing(0);
   layout->addWidget(new QLabel(tr("Variable table")));
   layout->addWidget(m_variableTable);

   m_VariableLayout = layout;

}

/*---------------------------------------------------------------------------*/

ScanAttributeTableModel* ScanBuilderWidget::getVariableModel()
{

   return m_variableTable->getModel();

}

/*---------------------------------------------------------------------------*/

void ScanBuilderWidget::createPropertyWidget()
{

   m_scanPropertyTable = new ScanPropertyTable();

   QVBoxLayout* layout = new QVBoxLayout();


   layout->setContentsMargins(0, 0, 0, 0);
   layout->setSpacing(0);
   layout->addWidget(new QLabel(tr("Property table")));
   layout->addWidget(m_scanPropertyTable);

   m_PropertyLayout = layout;

}

/*---------------------------------------------------------------------------*/

void ScanBuilderWidget::createScanCommandWidget()
{


   QVBoxLayout* layout = new QVBoxLayout();

   layout->setContentsMargins(0, 0, 0, 0);
   layout->setSpacing(0);
   layout->addLayout(m_ControlLayout);
   layout->addWidget(new QLabel(tr("Scan Command Builder Table")));

   m_ScanCommandLayout = layout;

}

/*---------------------------------------------------------------------------*/

