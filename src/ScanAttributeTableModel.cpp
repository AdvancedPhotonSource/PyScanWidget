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

#include <ScanAttributeTableModel.h>
#include <QDebug>

/*---------------------------------------------------------------------------*/

ScanAttributeTableModel::ScanAttributeTableModel(bool editable,
   QObject* parent)
: QAbstractTableModel(parent)
{

   // Initialize header data
   m_headers[NAME] = tr("Name");
   m_headers[VALUE] = tr("Value");
   m_headers[TYPE] = tr("Type");
   m_headers[ENABLED] = tr("Enabled");
   m_editable = editable;
   m_propertyModel = false;

}

/*---------------------------------------------------------------------------*/

int ScanAttributeTableModel::addAttr(QString name,
                                     QString value,
                                     QString type,
                                     bool enabled)
{

   // Indicate beginning of insert
   beginInsertRows(QModelIndex(),
                  m_attrs.size(),
                  m_attrs.size());

   ScanAttribute attr(name, value, type, enabled);
   m_attrs.append(attr);

   // Indicate end of insert
   endInsertRows();

   // Return index of newly added pair
   return m_attrs.size() - 1;

}

/*---------------------------------------------------------------------------*/

void ScanAttributeTableModel::clearAll()
{

   // Remove all rows
   while (rowCount(QModelIndex()) > 0)
   {
      removeRows(0, 1);
   }

}

/*---------------------------------------------------------------------------*/

int ScanAttributeTableModel::columnCount(
   const QModelIndex &parent) const
{

   // Mark unused
   Q_UNUSED(parent);

   return 2;

  // return 4;
}

/*---------------------------------------------------------------------------*/

QVariant ScanAttributeTableModel::data(
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

      ScanAttribute attr = m_attrs.at(index.row());
      // Insert data
      if (index.column() == NAME) return attr.getName();
      else if (index.column() == VALUE) return attr.getValue();
      else if (index.column() == TYPE) return attr.getType();
      else if (index.column() == ENABLED)
      {
         return attr.getIsEnable();
      }
   }


   // Return empty data
   return QVariant();

}

/*---------------------------------------------------------------------------*/

Qt::ItemFlags ScanAttributeTableModel::flags(
   const QModelIndex &index) const
{

   // Check valid index
   if (!index.isValid())
   {
      return Qt::ItemIsSelectable;
   }

   if (index.column() == NAME)
   {
      if (m_propertyModel == true)
      {
         if(m_editable)
         {
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
         }
         else
            return  Qt::ItemIsSelectable;
      }
   }

   if (index.column() == VALUE)
      return Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable;

   if(m_editable)
   {
      return Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable;
   }
   return Qt::ItemIsEnabled | Qt::ItemIsSelectable;

}

/*---------------------------------------------------------------------------*/

QList<ScanAttribute> ScanAttributeTableModel::getAttrs()
{

   // Return a copy of the list
   return m_attrs;

}

/*---------------------------------------------------------------------------*/

bool ScanAttributeTableModel::getValueByName(QString name, QString *value, QString *sType)
{

   foreach (ScanAttribute s, m_attrs)
   {
      if(s.getName() == name)
      {
         *value = s.getValue();
         *sType = s.getType();
         return true;
      }
   }
   return false;

}

/*---------------------------------------------------------------------------*/

bool ScanAttributeTableModel::getAttributeByName(QString name, ScanAttribute *attr)
{

   foreach (ScanAttribute s, m_attrs)
   {
      if(s.getName() == name)
      {
         *attr = s;
         return true;
      }
   }
   return false;

}

/*---------------------------------------------------------------------------*/

QVariant ScanAttributeTableModel::headerData(
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
         case VALUE:
            return m_headers[section];
         case TYPE:
            return m_headers[section];
         case ENABLED:
            if(m_editable)
               return m_headers[section];
         default:
            return QVariant();
      }
   }

   // Return empty data
   return QVariant();

}

/*---------------------------------------------------------------------------*/


void ScanAttributeTableModel::insertPlayProperties(QStringList strList, int index)
{

   m_attrs[index].insertPlayProperties(strList);

}

/*---------------------------------------------------------------------------*/

void ScanAttributeTableModel::insertStopProperties(QStringList strList, int index)
{

   m_attrs[index].insertStopProperties(strList);

}

/*---------------------------------------------------------------------------*/

bool ScanAttributeTableModel::removeRows(int row,
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

int ScanAttributeTableModel::rowCount(const QModelIndex &parent) const
{

   // Mark unused
   Q_UNUSED(parent);

   // Return number of rows
   return m_attrs.size();

}

/*---------------------------------------------------------------------------*/

bool ScanAttributeTableModel::setData(const QModelIndex &index,
                                              const QVariant &value,
                                              int role)
{

   // Mark unused
   Q_UNUSED(role);


   // Check for valid index
   if (index.isValid() == false)
   {
      return false;
   }

   // Get column and row
   int column = index.column();
   int row = index.row();

   // Set data
   if (column == NAME && m_editable)
   {
      m_attrs[row].setName(value.toString());
   }
   else if (column == VALUE)
   {
      m_attrs[row].setValue(value.toString());
   }
   else if (column == TYPE && m_editable)
   {
      m_attrs[row].setType(value.toString());
   }
   else if (column == ENABLED && m_editable)
   {
      m_attrs[row].setIsEnable(value.toBool());
   }
   else
   {
      return false;
   }

   // Emit dataChanged signal
   emit(dataChanged(index, index));

   // Return true
   return true;

}

void ScanAttributeTableModel::setEditable(bool val)
{

   m_editable = val;

}

/*---------------------------------------------------------------------------*/

bool ScanAttributeTableModel::setHeaderData(
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
   if (section == NAME || section == VALUE || section == TYPE)
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

void ScanAttributeTableModel::setAttrs(
   QList<ScanAttribute> attrs)
{

   // Begin reset
   beginResetModel();

   // Set new conditionals
   m_attrs = attrs;

   // End reset
   endResetModel();

}

/*---------------------------------------------------------------------------*/

void ScanAttributeTableModel::setPropertyModel(bool propertyModel)
{

   m_propertyModel = propertyModel;

}

/*---------------------------------------------------------------------------*/

void ScanAttributeTableModel::setPropertyPlayAt(const QModelIndex& indexItem,
                                                const QModelIndex& indexProperty,
                                                QString value)
{
   int rowItem = indexItem.row();

   int rowProperty = indexProperty.column();
   int columnProperty = indexProperty.column();

   // Set data
   if (columnProperty == NAME)
   {
      m_attrs[rowItem].setPropertyPlayNameAt(rowProperty, value);
   }
   else if (columnProperty == VALUE)
   {
      m_attrs[rowItem].setPropertyPlayValueAt(rowProperty, value);
   }
   else if (columnProperty == TYPE)
   {
      m_attrs[rowItem].setPropertyPlayTypeAt(rowProperty, value);
   }
   else if (columnProperty == ENABLED)
   {
      m_attrs[rowItem].setPropertyPlayEnabledAt(rowProperty, value);
   }
   else
   {
      return;
   }


}

/*---------------------------------------------------------------------------*/

void ScanAttributeTableModel::setPropertyStopAt(const QModelIndex& indexItem,
                                                const QModelIndex& indexProperty,
                                                QString value)
{
   int rowItem = indexItem.row();

   int rowProperty = indexProperty.column();
   int columnProperty = indexProperty.column();

   // Set data
   if (columnProperty == NAME)
   {
      m_attrs[rowItem].setPropertyStopNameAt(rowProperty, value);
   }
   else if (columnProperty == VALUE)
   {
      m_attrs[rowItem].setPropertyStopValueAt(rowProperty, value);
   }
   else if (columnProperty == TYPE)
   {
      m_attrs[rowItem].setPropertyStopTypeAt(rowProperty, value);
   }
   else if (columnProperty == ENABLED)
   {
      m_attrs[rowItem].setPropertyStopEnabledAt(rowProperty, value);
   }
   else
   {
      return;
   }


}

/*---------------------------------------------------------------------------*/

