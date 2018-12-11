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

#include <ScanAttributeGroup.h>

#include <QDebug>

/*---------------------------------------------------------------------------*/

ScanAttributeGroup::ScanAttributeGroup(ScanAttributeGroup* parent) : QObject(parent)
{

   m_groupName = "";
   m_groupType = "";
   m_enabled = true;
   m_parentItem = parent;

}

/*---------------------------------------------------------------------------*/

ScanAttributeGroup::ScanAttributeGroup(QString name,
                                       QString type,                    
                                       QList<ScanAttributeGroup*> attrsChild,
                                       QList<ScanAttribute*> propertyList,
                                       ScanAttributeGroup* parent)
   : QObject(parent)
{

   m_groupName = name;
   m_groupType = type;
   m_enabled = true;
   m_parentItem = parent;

   for(int i = 0; i< attrsChild.count(); i++)
   {
      ScanAttributeGroup* item = new ScanAttributeGroup(attrsChild[i]->getGroupName(),
                                                        attrsChild[i]->getGroupType(),
                                                        attrsChild[i]->getChildren(),
                                                        attrsChild[i]->getPropertyList(),
                                                        this);
      m_attrsChild.append(item);
   }

   for(int i = 0; i< propertyList.count(); i++)
   {

      ScanAttribute* item = new ScanAttribute(propertyList[i]->getName(),
                                              propertyList[i]->getValue(),
                                              propertyList[i]->getType(),
                                              propertyList[i]->getIsEnable());
      m_propertyList.append(item);

   }


}

/*---------------------------------------------------------------------------*/

ScanAttributeGroup::~ScanAttributeGroup()
{

   clearAndDeleteAttributes();

}

/*---------------------------------------------------------------------------*/

void ScanAttributeGroup::appendChild(ScanAttributeGroup* child)
{

   m_attrsChild.append(child);

}

/*---------------------------------------------------------------------------*/

//void ScanAttributeGroup::append(ScanAttribute *attr, QList<ScanAttribute*>* attrList)
//{

//   attr->setParent(this);
//   m_attrs.append(attr);
//   int idx = m_attrs.indexOf(attr);

//   m_attrsList.append(attrList);

//   emit pvInserted(this, idx);

//}

/*---------------------------------------------------------------------------*/

void ScanAttributeGroup::clearAndDeleteAttributes()
{

   qDeleteAll(m_attrsChild);

   qDeleteAll(m_propertyList);

}

/*---------------------------------------------------------------------------*/

QList<ScanAttributeGroup*> ScanAttributeGroup::getChildren()
{

   return m_attrsChild;

}

/*---------------------------------------------------------------------------*/

bool ScanAttributeGroup::insertChildren(int index, int number)
{

   if(index > - 1 && index <= m_attrsChild.count())
   {
      for (int row = 0; row < number; ++row)
      {

          ScanAttributeGroup* node = new ScanAttributeGroup(this);
          m_attrsChild.insert(index, node);
//          index++;
      }
      return true;
   }
   return false;

}

/*---------------------------------------------------------------------------*/

void ScanAttributeGroup::insertProperty(ScanAttribute *attr)
{

   m_propertyList.append(attr);

}

/*---------------------------------------------------------------------------*/

void ScanAttributeGroup::insertProperties(QStringList propertyList)
{

   foreach (QString property, propertyList)
   {
      ScanAttribute* attr = new ScanAttribute(property, "", "", false);
      m_propertyList.append(attr);
   }

}

/*---------------------------------------------------------------------------*/

//QList<ScanAttribute*>* ScanAttributeGroup::getAttrListAt(int index)
//{

//   QList<ScanAttribute*>* attrList = NULL;
//   if(index > - 1 && index < m_attrsList.count())
//   {
//      attrList = m_attrsList.at(index);
//   }
//   return attrList;

//}

/*---------------------------------------------------------------------------*/

ScanAttributeGroup* ScanAttributeGroup::getChildAt(int index)
{

   ScanAttributeGroup* attr = NULL;
   if(index > - 1 && index < m_attrsChild.count())
   {
      attr = m_attrsChild.at(index);
   }
   return attr;

}

/*---------------------------------------------------------------------------*/

int ScanAttributeGroup::getChildCount() const
{

    return m_attrsChild.count();

}

/*---------------------------------------------------------------------------*/

QString ScanAttributeGroup::getGroupName()
{

   return m_groupName;

}

/*---------------------------------------------------------------------------*/

QString ScanAttributeGroup::getGroupType()
{

   return m_groupType;

}

/*---------------------------------------------------------------------------*/

ScanAttributeGroup *ScanAttributeGroup::getParent()
{
    return m_parentItem;
}

/*---------------------------------------------------------------------------*/

QList<ScanAttribute*> ScanAttributeGroup::getPropertyList()
{

   return m_propertyList;

}

/*---------------------------------------------------------------------------*/

bool ScanAttributeGroup::isEnabled()
{

   return m_enabled;

}

/*---------------------------------------------------------------------------*/

//bool ScanAttributeGroup::moveAttrDown(ScanAttribute *attr)
//{

//   int pos = m_attrs.indexOf(attr);
//   if(pos > -1 && pos < m_attrs.count() - 1)
//   {
//      m_attrs.removeAt(pos);
//      m_attrs.insert(pos+1, attr);
//      emit pvReOrdered(this, pos, pos+1);
//      return true;
//   }
//   return false;

//}

/*---------------------------------------------------------------------------*/

bool ScanAttributeGroup::moveAttrUp(ScanAttributeGroup *attr)
{

   int pos = m_attrsChild.indexOf(attr);

   if(pos > 0 && pos < m_attrsChild.count())
   {
      m_attrsChild.removeAt(pos);
      m_attrsChild.insert(pos-1, attr);

      return true;
   }
   return false;

}

/*---------------------------------------------------------------------------*/

int ScanAttributeGroup::indexAsChildren() const
{
    if (m_parentItem)
        return m_parentItem->
                    m_attrsChild.indexOf(const_cast<ScanAttributeGroup*>(this));

    return 0;
}

/*---------------------------------------------------------------------------*/

bool ScanAttributeGroup::removeChildren(int index, int number)
{

      if(index > - 1 && index + number <= m_attrsChild.count())
      {
         for (int row = 0; row < number; ++row)
         {

            delete m_attrsChild.takeAt(index);
         }

         return true;
      }

      return false;

}

/*---------------------------------------------------------------------------*/

void ScanAttributeGroup::setEnabled(bool state)
{

   m_enabled = state;
   foreach(ScanAttributeGroup* attrGrp, m_attrsChild)
   {
      attrGrp->setEnabled(state);
   }

}

/*---------------------------------------------------------------------------*/

void ScanAttributeGroup::setGroupName(QString name)
{

   m_groupName = name;

}

/*---------------------------------------------------------------------------*/

void ScanAttributeGroup::setGroupParent(ScanAttributeGroup* parent)
{

   m_parentItem = parent;

}


/*---------------------------------------------------------------------------*/

void ScanAttributeGroup::setGroupType(QString type)
{

   m_groupType = type;

}

/*---------------------------------------------------------------------------*/

void ScanAttributeGroup::setPropertyAt(int index, QString value)
{

   if(index > -1 && index < m_propertyList.count())
      m_propertyList.at(index)->setValue(value);

}

/*---------------------------------------------------------------------------*/

//QString ScanAttributeGroup::toString()
//{

//   QString str;
//   QString enableStr = QString("%1").arg(m_enabled);
//   QString cntStr = QString("%1").arg(m_attrs.count());
//   str.append(m_groupName);
//   str.append(";");
//   str.append(enableStr);
//   str.append(";");
//   str.append(cntStr);
//   for (int i = 0 ; i < m_attrs.size() ; i++)
//   {
//      ScanAttribute* pva = m_attrs.at(i);
//      str.append(";");
//      str.append(pva->toString());
//   }

//   return str;

//}

/*---------------------------------------------------------------------------*/
