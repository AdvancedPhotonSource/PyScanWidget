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

#include <ScanLoadTableModel.h>
#include <QDebug>

/*---------------------------------------------------------------------------*/

ScanLoadTableModel::ScanLoadTableModel(
   QObject* parent)
: QAbstractTableModel(parent)
{

   // Initialize header data
   m_headers[NAME] = tr("Name");
   m_headers[PATH] = tr("Path");

}

/*---------------------------------------------------------------------------*/

int ScanLoadTableModel::add(ScanAdminWidget *saw)
{

   // Indicate beginning of insert,
   beginInsertRows(QModelIndex(),
                  m_attrs.size(),
                  m_attrs.size());

   m_attrs.append(saw);
   // Indicate end of insert
   endInsertRows();

   // Return index of newly added pair
   return m_attrs.size() - 1;

}

/*---------------------------------------------------------------------------*/

void ScanLoadTableModel::clearAll()
{

   // Remove all rows
   while (rowCount(QModelIndex()) > 0)
   {
      removeRows(0, 1);
   }

}

/*---------------------------------------------------------------------------*/

int ScanLoadTableModel::columnCount(
   const QModelIndex &parent) const
{

   // Mark unused
   Q_UNUSED(parent);

   return 2;

}

/*---------------------------------------------------------------------------*/

QVariant ScanLoadTableModel::data(
   const QModelIndex &index, int role) const
{

   // Mark unused
   Q_UNUSED(role);

   // Check valid index
   if (!index.isValid())
   {
      return QVariant();
   }

   // Check valid index
   if (index.row() >= m_attrs.size() || index.row() < 0)
   {
      return QVariant();
   }

   // Return values for display and edit roles
   if (role == Qt::DisplayRole || role == Qt::EditRole)
   {

      ScanAdminWidget *d = m_attrs.at(index.row());
      // Insert data
      if (index.column() == NAME) return d->getName();
      else if (index.column() == PATH) return d->getPath();
   }


   // Return empty data
   return QVariant();

}

/*---------------------------------------------------------------------------*/

Qt::ItemFlags ScanLoadTableModel::flags(
   const QModelIndex &index) const
{

   // Check valid index
   if (!index.isValid())
   {
      return Qt::ItemIsSelectable;
   }

   return Qt::ItemIsEnabled | Qt::ItemIsSelectable;

}

/*---------------------------------------------------------------------------*/

QList<ScanAdminWidget*> ScanLoadTableModel::getAttrs()
{

   // Return a copy of the list
   return m_attrs;

}

/*---------------------------------------------------------------------------*/

QVariant ScanLoadTableModel::headerData(
   int section,
   Qt::Orientation orientation,
   int role) const
{

   // Check this is DisplayRole
   if (role != Qt::DisplayRole) return QVariant();

   // Horizontal headers
   if (orientation == Qt::Horizontal)
   {
      switch (section)
      {
         case NAME:
            return m_headers[section];
         case PATH:
            return m_headers[section];
         default:
            return QVariant();
      }
   }

   // Return empty data
   return QVariant();

}

/*---------------------------------------------------------------------------*/

bool ScanLoadTableModel::removeRows(int row,
                                  int count,
                                  const QModelIndex& parent)
{

   // Mark unused
   Q_UNUSED(parent);

   // Check bounds
   if ((row < 0) || ((row + count - 1) >= m_attrs.size())) return false;

   // Indicate beginning of removal
   beginRemoveRows(QModelIndex(), row, row + count - 1);

   // Remove count rows
   for (int r = row + count - 1 ; r >= row ; r--)
   {
      // Remove row
      m_attrs.removeAt(r);
   }

   // Indicate end of removal
   endRemoveRows();

   // Return true
   return true;

}

/*---------------------------------------------------------------------------*/

ScanAdminWidget* ScanLoadTableModel::at(int row)
{

   if(m_attrs.size() > row)
      return m_attrs.at(row);
   return NULL;

}

/*---------------------------------------------------------------------------*/

int ScanLoadTableModel::rowCount(const QModelIndex &parent) const
{

   // Mark unused
   Q_UNUSED(parent);

   // Return number of rows
   return m_attrs.size();

}

/*---------------------------------------------------------------------------*/

bool ScanLoadTableModel::setData(const QModelIndex &index,
                                              const QVariant &value,
                                              int role)
{

   Q_UNUSED(index);
   Q_UNUSED(value);
   Q_UNUSED(role);

   // Return true
   return true;

}

/*---------------------------------------------------------------------------*/

bool ScanLoadTableModel::setHeaderData(
   int section,
   Qt::Orientation orientation,
   const QVariant &value,
   int role)
{

   // Mark unused
   Q_UNUSED(role);

   // Check for horizontal orientation
   if (orientation != Qt::Horizontal)
   {
      return false;
   }

   // Assign headers
   if (section == NAME || section == PATH)
   {
      m_headers[section] = value.toString();
   }
   else
   {
      return false;
   }

   // Return true
   return true;

}

/*---------------------------------------------------------------------------*/

void ScanLoadTableModel::setAttrs(
   QList<ScanAdminWidget*> attrs)
{

   // Begin reset
   beginResetModel();

   // Set new conditionals
   m_attrs = attrs;

   // End reset
   endResetModel();

}

/*---------------------------------------------------------------------------*/

void ScanLoadTableModel::fromStringList(QString data)
{

   QStringList subData = data.split(";");
   foreach (QString str, subData)
   {
      QStringList list = str.split(",");
      if(list.length() > 1)
      {
         ScanAdminWidget* saw = new ScanAdminWidget(0);
         if(saw->loadScan(list[1]))
         {
//            m_attrs.append(saw);
            add(saw);
         }
         else
         {
            delete saw;
         }
      }
   }

}

/*---------------------------------------------------------------------------*/

QString ScanLoadTableModel::toStringList()
{

   QString list;

   foreach (ScanAdminWidget *saw, m_attrs)
   {
      list.append(saw->getName()+","+saw->getPath()+";");
   }

   return list;

}

/*---------------------------------------------------------------------------*/
