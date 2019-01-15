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

#include <AcquisitionWidget.h>
#include <QMessageBox>

/*---------------------------------------------------------------------------*/

AcquisitionWidget::AcquisitionWidget(QWidget* parent): QWidget(parent)
{
   m_playScan = new ScanPythonProcess();

   connect(m_playScan, SIGNAL(processFinishedSig()),
           this, SLOT(processFinished()));

   connect(m_playScan, SIGNAL(readReady(QString)),
           this, SLOT(newProcessOutput(QString)));

      // Top level layout
    QVBoxLayout* mainLayout = new QVBoxLayout();
    QVBoxLayout* vLayout = new QVBoxLayout();
    QHBoxLayout* hLayout = new QHBoxLayout();

    QToolBar *scanToolbar = new QToolBar(this);
    scanToolbar->setFloatable(false);
    scanToolbar->setMovable(false);

    outputTextbox = new QPlainTextEdit();
    outputTextbox->resize(300, 400);

   m_startAction = new QAction(QIcon(":images/start.png"), tr("Start"), this);
   m_stopAction = new QAction(QIcon(":images/stop.png"), tr("Stop"), this);
   m_killAction = new QAction(QIcon(":images/kill-proc.png"), tr("Kill"), this);
   m_stopAction->setEnabled(false);

   connect(m_startAction,
           SIGNAL(triggered()),
           this,
           SLOT(startScanAcquisition()));

   connect(m_stopAction,
           SIGNAL(triggered()),
           this,
           SLOT(stopAcquisition()));

   connect(m_killAction,
           SIGNAL(triggered()),
           this,
           SLOT(killAcquisition()));

   scanToolbar->addAction(m_startAction);
   scanToolbar->addAction(m_stopAction);
   scanToolbar->addAction(m_killAction);

   m_scanUserWidget = new ScanUserWidget();

//   connect(m_scanUserWidget,
//           SIGNAL(newScanSelected(ScanAdminWidget*)),
//           this,
//           SLOT(newScanLoaded(ScanAdminWidget*)));

      vLayout->addWidget(scanToolbar);
      vLayout->addWidget(m_scanUserWidget);
      hLayout->addLayout(vLayout);
      hLayout->addWidget(outputTextbox);

      mainLayout->addLayout(hLayout);
      setLayout(mainLayout);
}

/*---------------------------------------------------------------------------*/

void AcquisitionWidget::newProcessOutput(QString output)
{
    outputTextbox->appendPlainText(output);
    //outputTextbox->verticalScrollBar()->setValue(outputTextbox->verticalScrollBar()->maximum());
}

/*---------------------------------------------------------------------------*/

void AcquisitionWidget::newScanLoaded(ScanAdminWidget* saw)
{
/*
   if(saw && m_acquisitionState != AcquisitionModel::ACQUIRING)
   {
      m_startAction->setEnabled(true);
      m_stopAction->setEnabled(false);
   }
   else
   {
      m_startAction->setEnabled(false);
      m_stopAction->setEnabled(false);
   }
*/
}

void AcquisitionWidget::processFinished()
{
    m_startAction->setEnabled(true);
    m_stopAction->setEnabled(false);
}

/*---------------------------------------------------------------------------*/

void AcquisitionWidget::startScanAcquisition()
{
    if(m_playScan != nullptr)
    {
        outputTextbox->clear();
        ScanBuilder::buildScan(m_playScan, m_scanUserWidget->getSelectedScan());
        if( m_playScan->execute() )
        {
            m_startAction->setEnabled(false);
            m_stopAction->setEnabled(true);
        }
    }
}

/*---------------------------------------------------------------------------*/

void AcquisitionWidget::stopAcquisition()
{

    m_playScan->sendSigTerm();

}

/*---------------------------------------------------------------------------*/

void AcquisitionWidget::killAcquisition()
{

    m_playScan->terminateProcess();
    m_startAction->setEnabled(true);
    m_stopAction->setEnabled(false);


}
