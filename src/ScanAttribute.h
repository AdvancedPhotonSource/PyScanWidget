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

#ifndef SCANATTRIBUTE_H
#define SCANATTRIBUTE_H

/*---------------------------------------------------------------------------*/

#include <QString>
#include <QList>
#include <ScanAttributeGroup.h>

/*---------------------------------------------------------------------------*/

class ScanAttributeGroup;
class ScanAttribute;

/*---------------------------------------------------------------------------*/

/**
 * @brief Attributes definition class, each attribute can have its own
 * type, name, value, enabled.
 */
class ScanAttribute
{

public:

   /**
    * Constructor
    */
   ScanAttribute();

   /**
    * Constructor
    */
   ScanAttribute(QString name,
               QString value,
               QString type,
               bool enabled=false);

   /**
    * Destructor
    */
   ~ScanAttribute();

   /**
    * @brief insertPlayProperty
    * @param attr
    */
   void insertPlayProperty(ScanAttribute attr);

   /**
    * @brief insertStopProperty
    * @param attr
    */
   void insertStopProperty(ScanAttribute attr);

   /**
    * @brief insertPlayProperties
    * @param propertyList
    */
   void insertPlayProperties(QStringList propertyList);

   /**
    * @brief insertStopProperties
    * @param propertyList
    */
   void insertStopProperties(QStringList propertyList);

   /**
    * @brief Check weather the enable flag is turned on.
    *
    * @return boolean flag value
    */
   bool getIsEnable() const;

   /**
    * @brief Name of the attribute e.g. motor record
    *
    * @return Name of the attribute.
    */
   QString getName() const;

   /**
    * @brief Type of the attribute
    *
    * @return Type of the attribute.
    */
   QString getType() const;

   /**
    * @brief value of the attribute e.g perch:m1
    *
    * @return Value of the attribute.
    */
   QString getValue() const;

   /**
    * @brief getParent
    * @return
    */
   ScanAttribute* getParent() const;

   /**
    * @brief getPropertyPlayList
    * @return
    */
   QList<ScanAttribute> getPropertyPlayList() const;

   /**
    * @brief getPropertyStopList
    * @return
    */
   QList<ScanAttribute> getPropertyStopList() const;

   /**
    * Set the enable flag
    *
    * @param boolean flag
    */
   void setIsEnable(bool enable);

   /**
    * Set the name of the attribute
    */
   void setName(QString name);

   /**
    * Set attribute description
    */
   void setType(QString type);

   /**
    * Set the value of the attribute
    */
   void setValue(QString value);

   /**
    * @brief setParent
    * @param parent
    */
   void setParent(ScanAttribute* parent);

   /**
    * @brief setPropertyPlayNameAt
    * @param index
    * @param value
    */
   void setPropertyPlayNameAt(int index, QString value);

   /**
    * @brief setPropertyPlayValueAt
    * @param index
    * @param value
    */
   void setPropertyPlayValueAt(int index, QString value);

   /**
    * @brief setPropertyPlayTypeAt
    * @param index
    * @param value
    */
   void setPropertyPlayTypeAt(int index, QString value);

   /**
    * @brief setPropertyPlayNameAt
    * @param index
    * @param value
    */
   void setPropertyPlayEnabledAt(int index, QString value);


   /**
    * @brief setPropertyStopNameAt
    * @param index
    * @param value
    */
   void setPropertyStopNameAt(int index, QString value);

   /**
    * @brief setPropertyStopValueAt
    * @param index
    * @param value
    */
   void setPropertyStopValueAt(int index, QString value);

   /**
    * @brief setPropertyStopTypeAt
    * @param index
    * @param value
    */
   void setPropertyStopTypeAt(int index, QString value);

   /**
    * @brief setPropertyStopEnabledAt
    * @param index
    * @param value
    */
   void setPropertyStopEnabledAt(int index, QString value);

   /**
    * @brief setPropertyPlayAt
    * @param index
    * @param value
    */
   void setPropertyStopAt(int index, QString value);

   /**
    * Get as a QVariant string type
    */
   QString toString();

private:

   /**
    * @brief m_parent
    */
   ScanAttribute* m_parent;

   /**
    * @brief m_propertyPlayList
    */
   QList<ScanAttribute> m_propertyPlayList;

   /**
    * @brief m_propertyStopList
    */
   QList<ScanAttribute> m_propertyStopList;

   /**
    * Type of solver e.g. motor record
    */
   QString m_name;

   /**
    * Value
    */
   QString m_value;

   /**
    * A brief description of the Solver.
    */
   QString m_type;

   /**
    * Indicate weather this Solver is enabled or not.
    */
   bool m_enabled;

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
