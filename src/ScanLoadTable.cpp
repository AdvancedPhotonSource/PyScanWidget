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

#include <ScanLoadTable.h>
#include <QHeaderView>
#include <QPushButton>
#include <QSortFilterProxyModel>
#include <QTableView>
#include <QVBoxLayout>
#include <QDebug>
#include "ScanAdminWidget.h"

/*---------------------------------------------------------------------------*/

ScanLoadTable::ScanLoadTable(QWidget* parent) : QWidget(parent)
{

   m_btnAdd = NULL;
   m_btnRemove = NULL;
   m_tableModel = NULL;
   m_tableView = NULL;

   createComponents();

}

/*---------------------------------------------------------------------------*/

ScanLoadTable::~ScanLoadTable()
{



}

/*---------------------------------------------------------------------------*/

void ScanLoadTable::acceptChanges()
{

}

/*---------------------------------------------------------------------------*/

void ScanLoadTable::addItem()
{

   ScanAdminWidget *saw = new ScanAdminWidget(0);

   if( saw->loadScan() )
   {
      m_tableModel->add(saw);
      emit chosenItem(saw);
   }
   else
   {
      delete saw;
   }

   if (m_tableModel->rowCount(QModelIndex()) > 0) m_btnRemove->setEnabled(true);
//   ScanAdminWidget *local = m_tableModel->getAttrs().at(m_tableModel->getAttrs().size()-1);
//   qDebug()<<local->getName();
}

/*---------------------------------------------------------------------------*/

void ScanLoadTable::createComponents()
{

   m_tableView = new QTableView;
   m_tableModel = new ScanLoadTableModel();

   m_selectionModel = new QItemSelectionModel(m_tableModel);

   // Setup table
   m_tableView->setModel(m_tableModel);
   m_tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
   m_tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
//   m_tableView->hideColumn(1);
//   m_tableView->hideColumn(2);
//   m_tableView->hideColumn(3);

   m_tableView->verticalHeader()->hide();
   m_tableView->verticalHeader()->setDefaultSectionSize(
   m_tableView->verticalHeader()->minimumSectionSize());
//   m_tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
   m_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
   m_tableView->setSelectionMode(QAbstractItemView::SingleSelection);
   m_tableView->setAlternatingRowColors(true);
   m_tableView->resizeColumnsToContents();

   m_tableView->setSelectionModel(m_selectionModel);
 //  m_tableModel->setHeaderData(0, Qt::Horizontal, tr(""));
//   m_tableView->setFixedHeight(100);
/*
   connect(m_tableModel,
           SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)),
           this,
           SLOT(editItem(const QModelIndex&, const QModelIndex&)));
*/
   connect(m_selectionModel,
           SIGNAL(selectionChanged(const QItemSelection &,
                                   const QItemSelection &)),
           this,
           SLOT(switchItem(const QItemSelection &,
                           const QItemSelection &)));
   // Add button
   m_btnAdd = new QPushButton;
   m_btnAdd -> setIcon(QIcon(":images/list-add.png"));
   m_btnAdd -> setFlat(true);
   m_btnAdd -> setFixedSize(32, 32);
   connect(m_btnAdd, SIGNAL(clicked()), this, SLOT(addItem()));

   // Remove button
   m_btnRemove = new QPushButton;
   m_btnRemove -> setIcon(QIcon(":images/list-remove.png"));
   m_btnRemove -> setFlat(true);
   m_btnRemove->setEnabled(true);
   m_btnRemove -> setFixedSize(32, 32);
   connect(m_btnRemove, SIGNAL(clicked()), this, SLOT(removeItem()));

   // Layout for buttons
   QHBoxLayout* buttonLayout = new QHBoxLayout;
   buttonLayout -> addWidget(m_btnAdd);
   buttonLayout -> addWidget(m_btnRemove);
   buttonLayout -> addStretch();
   buttonLayout -> setSpacing(0);
   buttonLayout -> setContentsMargins(0, 0, 0, 0);

   QVBoxLayout* mainLayout = new QVBoxLayout;
   mainLayout->setContentsMargins(0, 0, 0, 0);
   mainLayout->addWidget(m_tableView);
   mainLayout->addLayout(buttonLayout);
   setLayout(mainLayout);

}

/*---------------------------------------------------------------------------*/

void ScanLoadTable::editItem(const QModelIndex& topLeft,
                             const QModelIndex& bottomRight)
{

   if(!topLeft.isValid())
   {
      return;
   }

   //QString editValue = m_tableModel->data(topLeft, Qt::DisplayRole).toString();
   //int position = topLeft.column();

   //emit editItem(position, editValue);
}

/*---------------------------------------------------------------------------*/

void ScanLoadTable::removeItem()
{

   // Check valid model
   //if (m_tableModel == NULL) return;

   // Get current selection
   QModelIndexList list = m_tableView->selectionModel()->selectedIndexes();

   // Check for selected indexes
   if (list.size() < 1) return;

   // Get first one
   QModelIndex index = list.at(0);

   // Get row of current selection
   int row = index.row();
   int selectRow = row;

   // Remove row if it's valid
   if (row >= 0 && row < m_tableModel->rowCount(QModelIndex()))
   {
      // Remove from model
      m_tableModel->removeRows(row, 1);
   }

   emit removeItem(selectRow);

   // Update selected row
   if (m_tableModel->rowCount(QModelIndex()) > 0)
   {
      // If row removed was last row in model
      if (row >= m_tableModel->rowCount(QModelIndex()))
      {
         row = m_tableModel->rowCount(QModelIndex()) - 1;
      }
      // Select
    // m_tableView->selectionModel()->clearSelection();
      m_tableView->selectRow(row);
   }

   // Disable remove button
   if (m_tableModel->rowCount(QModelIndex()) <= 0)
   {
      m_btnRemove->setEnabled(false);
   }

}

/*---------------------------------------------------------------------------*/

void ScanLoadTable::setRow(int index)
{

   m_tableView->selectRow(index);

}

/*---------------------------------------------------------------------------*/

ScanLoadTableModel* ScanLoadTable::getModel()
{

   return m_tableModel;

}

/*---------------------------------------------------------------------------*/

void ScanLoadTable::setModel(ScanLoadTableModel* model)
{

   m_tableModel = model;
   m_tableView->setModel(model);

}

/*---------------------------------------------------------------------------*/

//void ScanLoadTable::setAttrs(const QList<ScanAttribute>& attrs)
//{

//   m_tableModel->setAttrs(attrs);

//}

/*---------------------------------------------------------------------------*/

void ScanLoadTable::switchItem(const QItemSelection& selected,
                                  const QItemSelection& deselected)
{

   QModelIndexList items = selected.indexes();
   foreach(QModelIndex index, items)
   {
      emit chosenItem(m_tableModel->at(index.row()));
      return;
   }

}

/*---------------------------------------------------------------------------*/


