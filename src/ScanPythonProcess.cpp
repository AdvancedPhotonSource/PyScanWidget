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

#include <ScanPythonProcess.h>
#include <ScanAttributeTableModel.h>
#include <csignal>
#include <QDebug>


using namespace std;

/*---------------------------------------------------------------------------*/

ScanPythonProcess::ScanPythonProcess()
{
    m_Process = nullptr;
    m_stopCntr = 0;
    m_fullPath = "";
}

/*---------------------------------------------------------------------------*/

ScanPythonProcess::ScanPythonProcess(QString fullPath)
{

    m_Process = nullptr;
    setFullPath(fullPath);
    m_stopCntr = 0;
}

/*---------------------------------------------------------------------------*/

ScanPythonProcess::ScanPythonProcess(const std::shared_ptr<ScanPythonProcess>& rhs)
{

    m_fullPath = rhs->m_fullPath;

}


/*---------------------------------------------------------------------------*/

ScanPythonProcess& ScanPythonProcess::operator=(
   const std::shared_ptr<ScanPythonProcess>& rhs)
{

   m_fullPath = rhs->m_fullPath;
   return *this;

}

/*---------------------------------------------------------------------------*/

ScanPythonProcess::~ScanPythonProcess()
{

}


/*---------------------------------------------------------------------------*/

void ScanPythonProcess::dump(int level)
{

   //std::cout<<"Scan Shell full path"<<m_fullPath.toLatin1()<<std::endl;

}

/*---------------------------------------------------------------------------*/

bool ScanPythonProcess::execute()
{
    if( m_Process != nullptr)
    {
        disconnect(m_Process, SIGNAL(readyRead()), this, SLOT(processReadyRead()));
        delete m_Process;
        m_Process = nullptr;
    }

    QStringList m_arguments;
    QString variableDic = "{";

    foreach(ScanAttribute attr, m_variables)
    {
        if(attr.getIsEnable())
        {
            //if(attr.getType() == "String")
            QString value = attr.getValue();
            bool ok = false;
            double testD = value.toDouble(&ok);
            if(!ok)
            {
                variableDic += "\""+ attr.getName() + "\":\"" + attr.getValue() + "\",";
            }
            else
            {
                variableDic += "\""+ attr.getName() + "\":" + attr.getValue() + ",";
            }
        }
    }
    variableDic += "\"__end__\":0}";

    if(m_fullPath.length() < 1)
    {
        qDebug()<<"script path not set! ";
        return false;
    }

    m_arguments.append(m_fullPath);
    m_arguments.append(variableDic);

    m_stopCntr = 0;
    m_Process = new QProcess();
    connect(m_Process, SIGNAL(finished(int ,QProcess::ExitStatus)),
            this, SLOT(processFinished(int ,QProcess::ExitStatus)));

    connect(m_Process, SIGNAL(readyRead()), this, SLOT(processReadyRead()));
    qDebug()<<"start python "<<m_fullPath<<" : "<<variableDic;
    //m_Process->setProcessChannelMode(QProcess::ForwardedChannels);
    m_Process->setProcessChannelMode(QProcess::MergedChannels);
    m_Process->start("python", m_arguments);
    return true;
}

/*---------------------------------------------------------------------------*/

void ScanPythonProcess::processFinished(int exitCode, QProcess::ExitStatus exitStatus)
{

    qDebug()<<"finish python "<<m_fullPath<<" Status "<<exitCode;
    if (m_Process != nullptr)
    {
        disconnect(m_Process, SIGNAL(readyRead()), this, SLOT(processReadyRead()));
        delete m_Process;
    }
    m_Process = nullptr;
    emit(processFinishedSig());
}

/*---------------------------------------------------------------------------*/

void ScanPythonProcess::sendSigTerm()
{
    if(m_Process != nullptr)
    {
        qDebug()<<"Sending SigInt to stop scan pid"<<m_Process->pid();
        m_Process->kill();
    }
}

/*---------------------------------------------------------------------------*/

void ScanPythonProcess::terminateProcess()
{

    if(m_Process != nullptr)
    {
        qDebug()<<"ScanPythonProcess terminate";
        m_Process->terminate();
    }

}

/*---------------------------------------------------------------------------*/

void ScanPythonProcess::processReadyRead()
{

    if(m_Process != nullptr)
    {
        QByteArray output_array = m_Process->readAll();
        QString output = QString(output_array);
        emit readReady(output);
    }

}

/*---------------------------------------------------------------------------*/

void ScanPythonProcess::setFullPath(QString fullPath)
{

    m_fullPath = fullPath;

}

/*---------------------------------------------------------------------------*/

void ScanPythonProcess::setVariables(QList<ScanAttribute> varaibleList)
{

    m_variables = varaibleList;

}

/*---------------------------------------------------------------------------*/
