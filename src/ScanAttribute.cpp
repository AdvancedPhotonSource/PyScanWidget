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

#include <ScanAttribute.h>

/*---------------------------------------------------------------------------*/

ScanAttribute::ScanAttribute()
{

   // Default initialization
   m_name = "Name";
   m_value = "0.0";
   m_type = "QString";
   m_enabled = false;

}

/*---------------------------------------------------------------------------*/

ScanAttribute::ScanAttribute(QString name,
                         QString value,
                         QString type,
                         bool enabled)
{

   m_name = name;
   m_value = value;
   m_type = type;
   m_enabled = enabled;

}

/*---------------------------------------------------------------------------*/

ScanAttribute::~ScanAttribute()
{

}

/*---------------------------------------------------------------------------*/

void ScanAttribute::insertPlayProperty(ScanAttribute attr)
{

   m_propertyPlayList.append(attr);

}

/*---------------------------------------------------------------------------*/

void ScanAttribute::insertStopProperty(ScanAttribute attr)
{

   m_propertyStopList.append(attr);

}

/*---------------------------------------------------------------------------*/

void ScanAttribute::insertPlayProperties(QStringList propertyList)
{

   foreach (QString property, propertyList)
   {
      ScanAttribute attr(property, "", "", false);
      m_propertyPlayList.append(attr);
   }

}

/*---------------------------------------------------------------------------*/

void ScanAttribute::insertStopProperties(QStringList propertyList)
{

   foreach (QString property, propertyList)
   {
      ScanAttribute attr(property, "", "", false);
      m_propertyStopList.append(attr);
   }

}

/*---------------------------------------------------------------------------*/

bool ScanAttribute::getIsEnable() const
{

   return m_enabled;

}
/*---------------------------------------------------------------------------*/

ScanAttribute* ScanAttribute::getParent() const
{

   return m_parent;

}

/*---------------------------------------------------------------------------*/

QString ScanAttribute::getName() const
{

   return m_name;

}

/*---------------------------------------------------------------------------*/

QList<ScanAttribute> ScanAttribute::getPropertyPlayList() const
{

   return m_propertyPlayList;

}

/*---------------------------------------------------------------------------*/

QList<ScanAttribute> ScanAttribute::getPropertyStopList() const
{

   return m_propertyStopList;

}

/*---------------------------------------------------------------------------*/

QString ScanAttribute::getType() const
{

   return m_type;

}

/*---------------------------------------------------------------------------*/

QString ScanAttribute::getValue() const
{

   return m_value;

}

/*---------------------------------------------------------------------------*/

void ScanAttribute::setIsEnable(bool enabled)
{

   m_enabled = enabled;

}

/*---------------------------------------------------------------------------*/

void ScanAttribute::setName(QString name)
{

   m_name = name;

}

/*---------------------------------------------------------------------------*/

void ScanAttribute::setParent(ScanAttribute *parent)
{

   m_parent = parent;

}

/*---------------------------------------------------------------------------*/

void ScanAttribute::setPropertyPlayNameAt(int index, QString value)
{

   if(index > -1 && index < m_propertyPlayList.count())
      m_propertyPlayList[index].setName(value);

}

/*---------------------------------------------------------------------------*/

void ScanAttribute::setPropertyPlayValueAt(int index, QString value)
{

   if(index > -1 && index < m_propertyPlayList.count())
      m_propertyPlayList[index].setValue(value);

}

/*---------------------------------------------------------------------------*/

void ScanAttribute::setPropertyPlayTypeAt(int index, QString value)
{

   if(index > -1 && index < m_propertyPlayList.count())
      m_propertyPlayList[index].setType(value);

}

/*---------------------------------------------------------------------------*/

void ScanAttribute::setPropertyPlayEnabledAt(int index, QString value)
{

   if(index > -1 && index < m_propertyPlayList.count())
      m_propertyPlayList[index].setIsEnable(value.toInt());

}

/*---------------------------------------------------------------------------*/


void ScanAttribute::setPropertyStopNameAt(int index, QString value)
{

   if(index > -1 && index < m_propertyPlayList.count())
      m_propertyStopList[index].setName(value);

}

/*---------------------------------------------------------------------------*/

void ScanAttribute::setPropertyStopValueAt(int index, QString value)
{

   if(index > -1 && index < m_propertyPlayList.count())
      m_propertyStopList[index].setValue(value);

}

/*---------------------------------------------------------------------------*/

void ScanAttribute::setPropertyStopTypeAt(int index, QString value)
{

   if(index > -1 && index < m_propertyPlayList.count())
      m_propertyStopList[index].setType(value);

}

/*---------------------------------------------------------------------------*/

void ScanAttribute::setPropertyStopEnabledAt(int index, QString value)
{

   if(index > -1 && index < m_propertyPlayList.count())
      m_propertyStopList[index].setIsEnable(value.toInt());

}

/*---------------------------------------------------------------------------*/

void ScanAttribute::setType(QString type)
{

   m_type = type;

}

/*---------------------------------------------------------------------------*/

void ScanAttribute::setValue(QString value)
{

   m_value = value;

}

/*---------------------------------------------------------------------------*/

QString ScanAttribute::toString()
{

   return QString("%1,%2,%3,%4").arg(m_name)
                             .arg(m_value)
                             .arg(m_type)
                             .arg(m_enabled);

}

/*---------------------------------------------------------------------------*/
