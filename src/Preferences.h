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

#ifndef TXM_PREFERENCES_H
#define TXM_PREFERENCES_H

/*---------------------------------------------------------------------------*/

#include <QMap>
#include <QString>
#include <QVariant>

/*---------------------------------------------------------------------------*/

/**
 * @brief Read and save preferences between application restarts, the vaule key
 * is divided into PVList, EnergyFlux, MirrorEnery, HISTBins, which is
 * corresponding to the preference dialog. Preferences settings are recorded
 * using QSetting class.
 */
class Preferences
{

public:

   /**
    * List of enumerated values that may be stored in the application's
    * preferences file.
    */
   enum ValueKey {
      PVList,
      EnergyFlux,
      MirrorEnergy,
      HISTBins,                   /*!< Number of bins for histogram. */
      PVConditionsName,           /*!< PV conditions name. */
      PVConditionsOperator,       /*!< PV conditions operator. */
      PVConditionsValue,          /*!< PV conditions value. */
      PVConditionOperatorLogic,   /*!< PV logic operator. */
      PVConditionComment,         /*!< PV comment. */
      PVConditionsEnabled,        /*!< PV conditions enabled flag. */
      CameraOption,
      FontSize,                   /*!< Applicaiton wide font size. */
      AutoIncrementNumber,        /*!< Auto increment number for filename. */
      AutoIncrementSelection,     /*!< Radio button related to auto inc. */
      HDF5_FileName,              /*!< Radio button related to auto inc. */
      RulerUnitLabel,             /*!< Ruler unit label. */
      RulerUnitX,                 /*!< Ruler unit x. */
      RulerUnitY,                 /*!< Ruler unit y. */
      PVAreaDetector,
      PVSimAreaDetector,
      PVNeoAndorAreaDetector,
      PVPcoEdgeAreaDetector,
      PVCoolSnapAreaDetector,
      PVMotorList,               /*!< List of motors. */
      PVMotorLinks,              /*!< Links from motor to scan builder. */
      TomoProperties,            /*!< Tomo Widget properties */
      MainWindowSavedWidth,      /*!< Saved width for main window */
      MainWindowSavedHeight,     /*!< Saved height for main window */
      WindowTitle,               /*!< Title to display for window */
      ShutterLogic,              /*!< Logic for shutter status */
      PythonButtonFileName,
      PythonButtonFilePath,
      ProgrammableButtonList,
      SendXmlStringToHdf,
      HdfSaveDestPv,
      HdfSaveDestNormStr,
      HdfSaveDestBlackStr,
      HdfSaveDestWhiteStr,
      LastScanSave,
      UserScans,
      acquisitonWindowHide
   };

   /**
    * Constructor
    */
   Preferences();

   /**
    * Read a ValueKey from persistent storage.
    *
    * @param key - the ValueKey enum for the key to read
    * @return value for given key as a QVariant
    */
   QVariant readValueKey(Preferences::ValueKey key);

   /**
    * Save a ValueKey to persistent storage.
    *
    * @param key - the ValueKey enum for the key to read
    * @param value - the value to store as a QVariant
    */
   void saveValueKey(Preferences::ValueKey key, QVariant value);

private:

   /**
    * Helper method to create value-key map
    */
   void createValueKeyMap();

   /**
    * Map storing value keys and their text descriptions
    */
   QMap<Preferences::ValueKey, QString> m_mapValueKey;

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
