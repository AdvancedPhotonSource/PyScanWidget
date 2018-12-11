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

#ifndef ScanLoadTableModel_H_
#define ScanLoadTableModel_H_

#include <QAbstractTableModel>
#include <QList>
#include <QModelIndex>
#include <QVariant>
#include <ScanAdminWidget.h>

/*---------------------------------------------------------------------------*/

/**
 * @brief model to control the solver table
 */
class ScanLoadTableModel
: public QAbstractTableModel
{

   Q_OBJECT

public:

   /**
    * Properties corresponding to columns in table.
    */
   enum Properties {
      NAME,   /*!< Name */
      PATH,      /*!< PATH */
   };

   /**
    * Constructor
    *
    * @param parent - parent Qt widget
    */
   ScanLoadTableModel(QObject* parent = 0);

   /**
      * @brief Make a call to underlying model for adding an item to the table.
      * @param name
      * @param energy - energy
      * @param flux - flux
      */
   int add(ScanAdminWidget *saw);

   /**
    * @brief Clear all
    */
   void clearAll();

   /**
    * @brief Reimplemented from QAbstractItemModel. See Qt documentation.
    */
   int columnCount(const QModelIndex &parent) const;

   /**
    * @brief Reimplemented from QAbstractItemModel. See Qt documentation.
    */
   QVariant data(const QModelIndex &index,
                 int role = Qt::DisplayRole) const;

   /**
    * @brief Reimplemented from QAbstractItemModel. See Qt documentation.
    */
   Qt::ItemFlags flags(const QModelIndex &index) const;

   /**
    * @brief Returns a copy of a list of all pairs
    * @return a copy of a list of all pairs
    */
   QList<ScanAdminWidget*> getAttrs();

   /**
    * @brief Reimplemented from QAbstractItemModel. See Qt documentation.
    */
   QVariant headerData(int section,
                       Qt::Orientation orientation,
                       int role) const;

   /**
    * @brief Reimplemented from QAbstractItemModel. See Qt documentation.
    */
   bool removeRows(int row,
                   int count,
                   const QModelIndex& parent = QModelIndex());

   /**
    * @brief Reimplemented from QAbstractItemModel. See Qt documentation.
    */
   int rowCount(const QModelIndex &parent) const;

   /**
    * @brief Reimplemented from QAbstractItemModel. See Qt documentation.
    */
   bool setData(const QModelIndex &index,
                const QVariant &value,
                int role = Qt::EditRole);

   /**
    * @brief Reimplemented from QAbstractItemModel. See Qt documentation.
    */
   bool setHeaderData(int section,
                      Qt::Orientation orientation,
                      const QVariant &value,
                      int role = Qt::EditRole);


   ScanAdminWidget* at(int row);
   /**
    * @brief Set pairs
    *
    * @param pairs - list of pairs
    */
   void setAttrs(QList<ScanAdminWidget*> solverAttrs);

   /**
    * @brief fromStringList
    * @param data
    */
   void fromStringList(QString data);

   /**
    * @brief toStringList
    * @return
    */
   QString toStringList();



private:

   /**
    * @brief Header names
    */
   QString m_headers[2];

   /**
    * @brief List of double pairs
    */
   QList<ScanAdminWidget*> m_attrs;


};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
