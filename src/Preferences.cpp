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

#include <Preferences.h>

#include <QSettings>

/*---------------------------------------------------------------------------*/

Preferences::Preferences()
{

   // Create map of value keys to string names
   createValueKeyMap();

}

/*---------------------------------------------------------------------------*/

void Preferences::createValueKeyMap()
{

   m_mapValueKey.insert(PVList, "PVList");
   m_mapValueKey.insert(PVMotorList, "PVMotorList");
   m_mapValueKey.insert(PVMotorLinks, "PVMotorLinks");
   m_mapValueKey.insert(EnergyFlux, "EnergyFlux");
   m_mapValueKey.insert(MirrorEnergy, "MirrorEnergy");
   m_mapValueKey.insert(HISTBins, "HistogramBins");

   // PV boolean expressions values
   m_mapValueKey.insert(PVConditionsName, "PVConditionsName");
   m_mapValueKey.insert(PVConditionsOperator, "PVConditionsOperator");
   m_mapValueKey.insert(PVConditionsValue, "PVConditionsValue");
   m_mapValueKey.insert(PVConditionOperatorLogic, "PVConditionOperatorLogic");
   m_mapValueKey.insert(PVConditionComment, "PVConditionComment");
   m_mapValueKey.insert(PVConditionsEnabled, "PVConditionsEnabled");

   // PV area detectors
   m_mapValueKey.insert(PVAreaDetector, "PVAreaDetector");
   m_mapValueKey.insert(PVSimAreaDetector, "PVSimAreaDetector");
   m_mapValueKey.insert(PVNeoAndorAreaDetector, "PVNeoAndorAreaDetector");
   m_mapValueKey.insert(PVPcoEdgeAreaDetector, "PVPcoEdgeAreaDetector");
   m_mapValueKey.insert(PVCoolSnapAreaDetector, "PVCoolSnapAreaDetector");
   m_mapValueKey.insert(CameraOption, "CameraOption");

   m_mapValueKey.insert(FontSize, "FontSize");

   m_mapValueKey.insert(AutoIncrementNumber, "AutoIncrementNumber");
   m_mapValueKey.insert(AutoIncrementSelection, "AutoIncrementSelection");

   m_mapValueKey.insert(RulerUnitLabel, "RulerUnitLabel");
   m_mapValueKey.insert(RulerUnitX, "RulerUnitX");
   m_mapValueKey.insert(RulerUnitY, "RulerUnitY");

   m_mapValueKey.insert(HDF5_FileName, "HDF5_FileName");

   m_mapValueKey.insert(TomoProperties, "TomoProperties");

   m_mapValueKey.insert(MainWindowSavedWidth, "MainWindowSavedWidth");
   m_mapValueKey.insert(MainWindowSavedHeight, "MainWindowSavedHeight");

   m_mapValueKey.insert(WindowTitle, "WindowTitle");

   m_mapValueKey.insert(ShutterLogic, "ShutterLogic");

   m_mapValueKey.insert(PythonButtonFileName, "PythonButtonFileName");
   m_mapValueKey.insert(PythonButtonFilePath, "PythonButtonFilePath");
   m_mapValueKey.insert(ProgrammableButtonList, "ProgrammableButtonList");

   m_mapValueKey.insert(SendXmlStringToHdf, "SendXmlStringToHdf");
   m_mapValueKey.insert(HdfSaveDestPv, "HdfSaveDestPv");
   m_mapValueKey.insert(HdfSaveDestNormStr, "HdfSaveDestNormStr");
   m_mapValueKey.insert(HdfSaveDestBlackStr, "HdfSaveDestBlackStr");
   m_mapValueKey.insert(HdfSaveDestWhiteStr, "HdfSaveDestWhiteStr");

   m_mapValueKey.insert(LastScanSave, "LastScanSave");
   m_mapValueKey.insert(UserScans, "UserScans");

   // window hide check box
   m_mapValueKey.insert(acquisitonWindowHide, "acquisitonWindowHide");


}

/*---------------------------------------------------------------------------*/

QVariant Preferences::readValueKey(Preferences::ValueKey key)
{

   // Settings
   QSettings s(QSettings::IniFormat,
               QSettings::UserScope,
               "UChicagoArgonneLLC",
               "TXM");

   // Read value
   s.beginGroup("Values");
   QVariant value = s.value(m_mapValueKey[key]);
   s.endGroup();

   // Return value
   return value;

}

/*---------------------------------------------------------------------------*/

void Preferences::saveValueKey(Preferences::ValueKey key, QVariant value)
{

   // Settings
   QSettings s(QSettings::IniFormat,
               QSettings::UserScope,
               "UChicagoArgonneLLC",
               "TXM");

   // Write value
   s.beginGroup("Values");
   s.setValue(m_mapValueKey[key], value);
   s.endGroup();

}

/*---------------------------------------------------------------------------*/
