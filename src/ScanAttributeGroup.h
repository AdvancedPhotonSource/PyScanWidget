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

#ifndef TXM_SCAN_ATTRIBUTE_GROUP_H
#define TXM_SCAN_ATTRIBUTE_GROUP_H

/*---------------------------------------------------------------------------*/

#include <ScanAttribute.h>

#include <QStringList>
#include <QMap>
#include <QDebug>

/*---------------------------------------------------------------------------*/

class ScanAttribute;

/*---------------------------------------------------------------------------*/

/**
 * @brief
 */
class ScanAttributeGroup : QObject
{
    Q_OBJECT

public:

   /**
    * Default constructor
    */
   ScanAttributeGroup(ScanAttributeGroup* parent = 0);


   /**
    * Constructor
    */
   ScanAttributeGroup(QString name,
                      QString type,
                      QList<ScanAttributeGroup*> attrsChild = QList<ScanAttributeGroup*>(),
                      QList<ScanAttribute*> propertyList = QList<ScanAttribute*>(),
                      ScanAttributeGroup* parent = 0);

   /**
    * Destructor
    */
   ~ScanAttributeGroup();

   /**
    * @brief appendChild
    * @param child
    */
   void appendChild(ScanAttributeGroup* child);

   /**
    * @brief indexAmongChildren
    * @return
    */
   int indexAsChildren() const;

   /**
    * @brief insertChildren
    * @param index
    * @param number
    * @return
    */
   bool insertChildren(int index, int number);

   /**
    * @brief insertProperty
    * @param attr
    */
   void insertProperty(ScanAttribute *attr);

   /**
    * @brief insertProperty
    * @param propertyList
    */
   void insertProperties(QStringList propertyList);

   /**
    * @brief isEnabled
    * @return
    */
   bool isEnabled();

   /**
    * Initialize pv attributes from a string list
    */
//   bool fromString(QString str);

   /**
    * @brief getChildAt
    * @param index
    * @return
    */
   ScanAttributeGroup* getChildAt(int index);

   /**
    * @brief getChildCount
    * @return
    */
   int getChildCount() const;

   /**
    * @brief getAttrListAt
    * @param index
    * @return
    */
//   QList<ScanAttribute*>* getAttrListAt(int index);

   QList<ScanAttributeGroup*> getChildren();

   /**
    * @brief getGroupName
    * @return
    */
   QString getGroupName();

   /**
    * @brief getGroupType
    * @return
    */
   QString getGroupType();

   /**
    * @brief getParent
    * @return
    */
   ScanAttributeGroup *getParent();

   /**
    * @brief getPropertyList
    * @return
    */
   QList<ScanAttribute*> getPropertyList();



   /**
    * @brief moveAttrDown
    * @param attr
    * @return
    */
//   bool moveAttrDown(ScanAttribute* attr);

   /**
    * @brief moveAttrUp
    * @param attr
    * @return
    */
   bool moveAttrUp(ScanAttributeGroup* attr);

   /**
    * @brief removeChildren
    * @param index
    * @param number
    */
   bool removeChildren(int index, int number);

   /**
    * @brief setEnabled
    */
   void setEnabled(bool state);

   /**
    * @brief setGroupName
    */
   void setGroupName(QString name);

   /**
    * @brief setGroupType
    */
   void setGroupType(QString type);

   /**
    * @brief setGroupParent
    * @param parent
    */
   void setGroupParent(ScanAttributeGroup* parent);

   /**
    * @brieGREATER_EQUALf setPropertyAt
    * @param index
    * @param value
    */
   void setPropertyAt(int index, QString value);
   /**
    * @brief toString
    * @return
    */
//   QString toString();

signals:

   /**
    * @brief pvInserted
    */
//   void pvInserted(ScanAttributeGroup*, int);

   /**
    * @brief pvReOrdered
    */
//   void pvReOrdered(ScanAttributeGroup*, int, int);

   /**
    * @brief pvRemoved
    */
//   void pvRemoved(ScanAttributeGroup*, int);

protected:

   /**
    * @brief clearAndDeleteAttributes
    */
   void clearAndDeleteAttributes();

public:

   /**
    * @brief m_attrsChild
    */
   QList<ScanAttributeGroup*> m_attrsChild;

private:

   /**
    * @brief m_enabled
    */
   bool m_enabled;

   /**
    * @brief m_groupName
    */
   QString m_groupName;

   /**
    * @brief m_groupType
    */
   QString m_groupType;

   /**
    * @brief m_pvAttrs
    */
//   QList<ScanAttribute*> m_attrs;



   /**
    * @brief m_propertyList
    */
//   QList< QList<ScanAttribute*>* > m_attrsList;
   QList<ScanAttribute*> m_propertyList;

   /**
    * @brief m_parentItem
    */
   ScanAttributeGroup* m_parentItem;

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
