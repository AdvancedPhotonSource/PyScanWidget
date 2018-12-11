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

#ifndef TXM_SCAN_USER_WIDGET_H
#define TXM_SCAN_USER_WIDGET_H

/*---------------------------------------------------------------------------*/


#include <ScanVariableTable.h>
#include <ScanLoadTable.h>

#include <QWidget>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QLayout>
#include <QLabel>
#include <Qt>

/*---------------------------------------------------------------------------*/

/**
 * @brief widget.
 */
class ScanUserWidget : public QWidget
{

   Q_OBJECT

public:

   enum TabIndex{
      PlayScan,
      StopScan
   };


   /**
    * Constructor. See Qt documentation for QWidget.
    */
   ScanUserWidget(QWidget* parent = 0);

   /**
    * Destructor.
    */
   ~ScanUserWidget();

   /**
    * @brief getPropertyPlayList
    */
   QList<ScanAttribute> getPropertyPlayList();

   /**
    * @brief getPropertyStopList
    */
   QList<ScanAttribute> getPropertyStopList();

   /**
    * @brief getSelectedPlayScan
    * @return
    */
   ScanAdminWidget* getSelectedScan();

private:

   /**
    * @brief Create GUI components
    */
   void createComponents();

   /**
    * @brief Layout GUI components
    */
   void createLayout();

   /**
    * @brief Variable table GUI components
    */
   void createVariableWidget();

   /**
    * @brief createLoadWidget
    */
   void createLoadWidget();

   /**
    * @brief tabIndexChanged
    * @param index
    */
//   void tabIndexChanged(int index);

signals:

   /**
    * @brief currentScanChanged
    */
   void currentScanChanged();

   /**
    * @brief newScanSelected
    */
   void newScanSelected(ScanAdminWidget*);

private slots:

   /**
    * @brief chosenItem
    * @param ScanAttribute&
    */
   void chosenItem(ScanAdminWidget*);

   /**
    * @brief deleteItem
    * @param name
    * @param desc
    */
   void removeItem(int);

private:

   /**
    * @brief Layout for variable tables
    */
   QLayout* m_VariableLayout;

   /**
    * @brief Layout for load tables
    */
   QLayout* m_loadLayout;

   /**
    * @brief m_loadTable
    */
   ScanLoadTable* m_loadTable;

   /**
    * @brief m_tabWidget
    */
   QTabWidget* m_tabWidget;

   /**
    * @brief m_playTabWidget
    */
   ScanVariableTable* m_playTabWidget;

   /**
    * @brief m_stopTabWidget
    */
//   ScanVariableTable* m_stopTabWidget;

   /**
    * @brief m_preferences
    */
   Preferences* m_preferences;

   /**
    * @brief m_selectedScan
    */
   ScanAdminWidget *m_selectedScan;

};

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
