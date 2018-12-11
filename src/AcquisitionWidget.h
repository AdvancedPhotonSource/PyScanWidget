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

#ifndef ACQUISITION_WIDGET_H
#define ACQUISITION_WIDGET_H

/*---------------------------------------------------------------------------*/

#include <QWidget>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QButtonGroup>
#include <QScrollArea>
#include <QSplitter>
#include <QToolBar>

#include <ScanBuilder.h>
#include <ScanUserWidget.h>


/*---------------------------------------------------------------------------*/

/**
 * @brief When open the acquisition window, the widget is showing for capturing
 * the image from the area detector writer, the window will also be updated to
 * show the image.
 */
class AcquisitionWidget : public QWidget
{

   Q_OBJECT

public:

   /**
    * Constructor.
    */
   AcquisitionWidget(QWidget* parent = NULL);

   /**
    * @brief returns the current loaded and selected scan to run
    * @return
    */
   //ScanAdminWidget* getSelectedScan();

   void newScanLoaded(ScanAdminWidget* saw);

  /**
    * @brief start built scan
    */
   void startScanAcquisition();

   /**
    * Indicate user request for stopping the live acquisition/recording.
    */
   void stopAcquisition();


signals:

   /**
    * Signal emitted when the acquisition mode is changed 
    * through this widget
    */
   void emitAcquisitionModeUpdated(int);

   /**
    * Signal emitted when start button is clicked 
    */
   void emitStartAcquisition();

   /**
    * Signal emitted when stop button is clicked.
    */
   void emitStopAcquisition();

   /**
    * Signal emitted when record buttong is clicked
    */
   void emitRecordAcquisition();

   /**
    * signal for m_spinNumberOfImages changed
    */
   void imagesChanged(int);

private:

   /**
    * Start playing action
    */
   QAction* m_startAction;

   /**
    * Stop playing action
    */
   QAction* m_stopAction;

   QActionGroup*  m_acquisitionGroup;

   std::shared_ptr<ScanPythonProcess> m_playScan;
   ScanUserWidget* m_scanUserWidget;

};


/*---------------------------------------------------------------------------*/

#endif /* ACQUISITIONWIDGET_H_ */

/*---------------------------------------------------------------------------*/
