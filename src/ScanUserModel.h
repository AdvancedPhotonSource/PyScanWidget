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

#ifndef TXM_SCAN_MODEL_H
#define TXM_SCAN_MODEL_H

/*---------------------------------------------------------------------------*/

#include <ScanAttributeGroup.h>
#include <ScanAttribute.h>


/*---------------------------------------------------------------------------*/

/**
 * @brief Model class for saving the data for the scan
 */
class ScanUserModel
{

public:

   /**
    * @brief
    */
   ScanUserModel();

   /**
    * @brief
    */
   ~ScanUserModel();

   /**
    * @brief setScanCommmandRoot
    * @return root
    */
   ScanAttributeGroup* getScanCommmandRoot();

   /**
    * @brief setScanPVAttrs
    * @return attrs
    */
   QList<ScanAttribute> getScanPVAttrs();

   /**
    * @brief setScanPropertyAttrs
    * @return attrs
    */
   QList<ScanAttribute> getScanPropertyAttrs();

   /**
    * @brief getScanVariablePlayAttrs
    * @return attrs
    */
   QList<ScanAttribute> getScanVariablePlayAttrs();

   /**
    * @brief getScanVariableStopAttrs
    * @return attrs
    */
   QList<ScanAttribute> getScanVariableStopAttrs();

   /**
    * @brief setScanCommmandRoot
    * @param root
    */
   void setScanCommmandRoot(ScanAttributeGroup* root);

   /**
    * @brief setScanPVAttrs
    * @param attrs
    */
   void setScanPVAttrs(QList<ScanAttribute> attrs);

   /**
    * @brief setScanPropertyAttrs
    * @param attrs
    */
   void setScanPropertyAttrs(QList<ScanAttribute> attrs);

   /**
    * @brief setScanVariablePlayAttrs
    * @param attrs
    */
   void setScanVariablePlayAttrs(QList<ScanAttribute> attrs);

   /**
    * @brief setScanVariableStopAttrs
    * @param attrs
    */
   void setScanVariableStopAttrs(QList<ScanAttribute> attrs);

private:


private:

   /**
    * @brief m_pvAttrs
    */
   QList<ScanAttribute> m_pvAttrs;

   /**
    * @brief m_variableAttrsPlay
    */
   QList<ScanAttribute> m_variableAttrsPlay;

   /**
    * @brief m_variableAttrsStop
    */
   QList<ScanAttribute> m_variableAttrsStop;

   /**
    * @brief m_propertyAttrs
    */
   QList<ScanAttribute> m_propertyAttrs;

   /**
    * @brief m_rootItem
    */
   ScanAttributeGroup* m_rootItem;

};


/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
