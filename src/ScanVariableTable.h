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

#ifndef SCANVARIABLETABLE_H_
#define SCANVARIABLETABLE_H_

/*---------------------------------------------------------------------------*/

#include <QWidget>
#include <QMessageBox>
#include <QList>
#include <QItemSelectionModel>

#include <ScanAttribute.h>
#include <ScanAttributeTableModel.h>

class QItemSelection;
class QTableView;

/*---------------------------------------------------------------------------*/

/**
 * @brief SolverTable the table having all the parameters of the solver
 */
class ScanVariableTable
: public QWidget
{

   Q_OBJECT

public:

   /**
    * Constructor
    *
    * @param parent - the Qt parent widget
    */
   ScanVariableTable(bool editable = true, QWidget* parent = 0);

   /**
    * Destructor
    */
   ~ScanVariableTable();

   /**
    * @brief Process changes when parent dialog calls its accept
    */
   void acceptChanges();

   /**
    * @brief Internal slot to add an item. Called by the add item button.
    * @param
    */
   void addItem(ScanAttribute attr);

   /**
    * @brief addItems
    * @param
    */
   void addItems(QList<ScanAttribute*>& attrList);

   /**
    * @brief addItems
    * @param
    */
   void addItems(QList<ScanAttribute>& attrList);

   /**
    * @brief Set the model's state as a string list
    * @param list - a string list where iach string is one comma separated pair
    */
   void fromStringList(const QStringList& list);

   /**
    * @brief fromAttributeList
    * @param list
    */
   void fromAttributeList(const QList<ScanAttribute>& list);

   /**
    * @brief Get the model's state as a list of pairs
    *
    * @return list of pairs
    */
   QList<ScanAttribute>  getAttrs();

   /**
    * @brief hideAddRemoveButtons
    */
   void hideAddRemoveButtons();

   /**
    * @brief clearAll
    */
   void removeItems();

   /**
    * @brief setRow
    * @param index
    */
   void setRow(int index);

   /**
    * @brief setModel
    */
   void setModel(ScanAttributeTableModel*model);

   /**
    * @brief getModel
    * @return
    */
   ScanAttributeTableModel* getModel();

   /**
    * @brief Generate and return the table as a comma separated string list.
    *
    * @return a string list where each string is one comma separated pair
    */
   QStringList toStringList();

signals:

   /**
    * @brief addItem
    * @param name
    * @param desc
    */
   void addItem(QString name, QString desc);

   /**
    * @brief deleteItem
    * @param name
    * @param desc
    */
   void removeItem(int selectRow);

   /**
    * @brief editItem
    * @param index
    * @param value
    */
   void editItem(const QModelIndex&, QString);

   /**
    * @brief switchItem
    * @param
    * @param
    */
   void switchItem(const QItemSelection &, const QItemSelection &);

public slots:

   /**
    * @brief Set pairs for the model
    *
    * @param pairs - a list of pairs that represent the model
    */
   void setAttrs(const QList<ScanAttribute>& solverAttrs);

private:

   /**
    * @brief Layouts GUI components
    */
   void createComponents(bool editable);

private slots:

   /**
    * @brief Internal slot to add an item. Called by the add item button.
    */
   void addItem();

   /**
    * @brief Internal slot to remove the selected item. Called by the remove
    * item button.
    */
   void removeItem();

   /**
    * @brief editItem
    * @param
    * @param
    */
   void editItem(const QModelIndex&, const QModelIndex&);

private:

   bool m_editable;

   /**
    * @brief m_calSelectionModel
    */
   QItemSelectionModel* m_selectionModel;

   /**
    * @brief Add button
    */
   QPushButton* m_btnAdd;

   /**
    * @brief Remove button
    */
   QPushButton* m_btnRemove;

   /**
    * @brief Table model
    */
   ScanAttributeTableModel* m_tableModel;

   /**
    * @brief Table view for displaying model
    */
   QTableView* m_tableView;

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
