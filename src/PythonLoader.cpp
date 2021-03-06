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

#include <PythonLoader.h>
#include <QProcess>
#include <QCoreApplication>


#include <QDebug>

/*---------------------------------------------------------------------------*/

static const char STR_GET_MEMBERS[] = {"getmembers"};
static const char STR_IS_FUNCTION[] = {"isfunction"};


static const char STR_UNIX_PYTHON_26[] = {"libpython2.6"};
static const char STR_UNIX_PYTHON_27[] = {"libpython2.7"};
static const char STR_WIN_PYTHON_26[] = {"python26"};
static const char STR_WIN_PYTHON_27[] = {"python27"};
static const char STR_WIN_PYTHON_33[] = {"python33"};
static const char STR_WIN_PYTHON_34[] = {"python34"};

/*---------------------------------------------------------------------------*/

PythonLoader* PythonLoader::m_inst = NULL;

PythonLoader::PythonLoader()
{

   m_foundFuncs = false;
   m_safeCheckFailed = false;

}

/*---------------------------------------------------------------------------*/

PythonLoader::~PythonLoader()
{

    qDebug()<<"PythonLoader::~PythonLoader() \n\r";

    if(m_foundFuncs)
    {
       foreach(QString key, m_functionMap.keys())
       {
          pyFunc *pf = m_functionMap[key];
          if(pf->pFunc)
              Py_DecRef(pf->pFunc);
          if(pf->pModule)
              Py_DecRef(pf->pModule);
          if(pf->pDict)
              Py_DecRef(pf->pDict);

          if(pf->retVals != NULL)
             delete [] pf->retVals;
          pf->retVals = NULL;

          delete pf;
       }

       m_functionMap.clear();
       Py_Finalize();
    }
}

/*---------------------------------------------------------------------------*/

void PythonLoader::callFunc(QString module,
                            QString func,
                            pyReturnType returnType)
{

    long lsize;
   QString pfKey = module+func;
   if(false == m_foundFuncs && false == m_functionMap.contains(pfKey))
   {
      throw pyException(pyException::FUNC_NOT_FOUND);
   }

   pyFunc* pf = m_functionMap[pfKey];
   if(pf == NULL)
   {
      m_functionMap.remove(pfKey);
      throw pyException(pyException::FUNC_PTR_NULL);
   }

   //if(pf->pDict != NULL)
   //   Py_IncRef(pf->pDict);

   PyObject* pRetVal = NULL;
   try
   {
      pRetVal = PyObject_CallObject(pf->pFunc, pf->pArgs);
   }
   catch(...)
   {
      throw pyException(pyException::CALL_FUNC_THROW_EXCP);
   }

   switch(returnType)
   {
   case RET_LIST:
      if (pRetVal != NULL)
      {
         if(pf->retCnt > 0)
         {
            long lsize = PyList_Size(pRetVal);

            if(lsize == pf->retCnt)
            {
               for(int i=0; i<lsize; i++)
               {
                  PyObject* oX = PyList_GetItem(pRetVal, i);
                  pf->retVals[i] = PyFloat_AsDouble(oX);
               }
            }
            else
            {
               PyErr_Print();
               qDebug()<<"Error PythonLoader::callFunc; returned wrong list size.";
               throw pyException(pyException::RETURN_WRONG_LIST_SIZE);
            }
         }
      }
      else
      {
          PyErr_Print();
          qDebug()<<"PythonLoader::python call failed! Check the python script";
          throw pyException(pyException::NULL_RETURNED_FOR_LIST);
      }
      break;
   case RET_DOUBLE_DICT:
      if (pRetVal != NULL)
      {
         if(pf->retCnt > 0)
         {
            pf->retDict.clear();
            PyObject *keys = PyDict_Keys(pRetVal);
            lsize = PyList_Size(keys);

            if(lsize == pf->retCnt)
            {
               for(int i=0; i<lsize; i++)
               {
                  PyObject* key = PyList_GetItem(keys, i);
                  PyObject* pValue = PyDict_GetItem(pRetVal, key);
                  if(pValue)
                  {
                     QString sKey = QString(PyString_AsString(key));
                     double val = PyFloat_AsDouble(pValue);
                     pf->retDict.insert(sKey, val);
                  }

               }
            }
            else
            {
               qDebug()<<"Error PythonLoader::callFunc; returned wrong list size.";
               throw pyException(pyException::RETURN_WRONG_LIST_SIZE);
            }
         }
      }
      else
      {
         throw pyException(pyException::NULL_RETURNED_FOR_DICT);
      }
   case RET_STR_DICT:
      if (pRetVal != NULL)
      {
         if(pf->retCnt > 0)
         {
            pf->retStrDict.clear();
            PyObject *keys = PyDict_Keys(pRetVal);
            lsize = PyList_Size(keys);
            for(int i=0; i<lsize; i++)
            {
               PyObject* key = PyList_GetItem(keys, i);
               PyObject* pValue = PyDict_GetItem(pRetVal, key);
               if(pValue && pValue->ob_refcnt > 0)
               {
                  QString sKey = QString(PyString_AsString(key));
                  QString val = "";
                  bool gotVal = false;

                    //string
                    val = QString(PyString_AsString(pValue));
                    if (val.length() < 1)
                    {
                        PyErr_Clear();
                        PyErr_Print();
                        double dval = PyFloat_AsDouble(pValue);
                        val = QString::number(dval);
                    }
                  //int
                    //long lval = PyInt_AsLong(pValue);
                    //val = QString::number(lval);
                  /*
                  {
                      qDebug()<<"Warning: Unknown type for Key "<<sKey;
                  }
                    */
                  pf->retStrDict.insert(sKey, val);
               }
            }
         }
      }
      else
      {
          if(pRetVal != 0)
            Py_DecRef(pRetVal);
         throw pyException(pyException::NULL_RETURNED_FOR_DICT);
      }
      break;
   default:
      if (pRetVal == NULL)
      {
          if(pRetVal != 0)
            Py_DecRef(pRetVal);
         throw pyException(pyException::VOID_CALL_FAILED);
      }
   break;
   }

   if(pRetVal != 0)
     Py_DecRef(pRetVal);

}

/*---------------------------------------------------------------------------*/

bool PythonLoader::init()
{

   return init("");

}

/*---------------------------------------------------------------------------*/

PythonLoader* PythonLoader::inst()
{

   if(m_inst == NULL)
      m_inst = new PythonLoader();

   return m_inst;

}

/*---------------------------------------------------------------------------*/

bool PythonLoader::init(QString sharedLibName)
{

   m_foundFuncs = false;
   bool foundLib = false;

   if(m_safeCheckFailed)
   {
	   return false;
   }

   myLib.setLoadHints(QLibrary::ExportExternalSymbolsHint
                    | QLibrary::ResolveAllSymbolsHint);


   if(false == sharedLibName.isEmpty())
   {
      qDebug()<<"Searching for python library: "<<sharedLibName;
      myLib.setFileName(sharedLibName);
      if(myLib.load())
      {
         qDebug()<<"Found python library: "<<sharedLibName;
         foundLib = true;
      }
   }

   if(!foundLib)
   {
      myLib.setFileName(STR_UNIX_PYTHON_27);
      if(myLib.load())
      {
         qDebug()<<"Found python 2.7";
         foundLib = true;
      }
      else
          qDebug()<<myLib.errorString();
   }

   if(!foundLib)
   {
      myLib.setFileName(STR_UNIX_PYTHON_26);
      if(myLib.load())
      {
         qDebug()<<"Found python 2.6";
         foundLib = true;
      }
   }

   if(!foundLib)
   {
      myLib.setFileName(STR_WIN_PYTHON_27);
      if(myLib.load())
      {
         qDebug()<<"Found python 2.7";
         foundLib = true;
      }
   }

   if(!foundLib)
   {
      myLib.setFileName(STR_WIN_PYTHON_26);
      if(myLib.load())
      {
         qDebug()<<"Found python 2.6";
         foundLib = true;
      }
   }
/*
   if(!foundLib)
   {
      myLib.setFileName(STR_WIN_PYTHON_33);
      if(myLib.load())
      {
         qDebug()<<"Found python 3.3";
         foundLib = true;
      }
   }

   if(!foundLib)
   {
      myLib.setFileName(STR_WIN_PYTHON_34);
      if(myLib.load())
      {
         qDebug()<<"Found python 3.4";
         foundLib = true;
      }
   }
*/
   if(false == foundLib)
   {
      qDebug()<<"Python not found on system";
      myLib.unload();
      throw pyException(pyException::PYTHON_NOT_FOUND_ON_SYSTEM);
   }

   Py_Initialize = NULL;
   Py_Finalize = NULL;
   PySys_GetObject = NULL;
   PyString_FromString = NULL;
   PyList_Append = NULL;
   PyImport_Import = NULL;
   PyImport_ReloadModule = NULL;
   PyObject_GetAttrString = NULL;
   PyCallable_Check = NULL;
   PyDict_New = NULL;
   PyTuple_New = NULL;
   PyLong_FromLong = NULL;
   PyFloat_FromDouble = NULL;
   PyDict_SetItem = NULL;
   Py_IncRef = NULL;
   Py_DecRef = NULL;
   PyTuple_SetItem = NULL;
   PyObject_CallObject = NULL;
   PyList_Size = NULL;
   PyList_GetItem = NULL;
   PyTuple_GetItem = NULL;
   PyFloat_AsDouble = NULL;
   PyString_AsString = NULL;
   PyInt_AsLong = NULL;
   PyDict_Keys = NULL;
   PyDict_GetItem = NULL;
   PyDict_Size = NULL;
   PyErr_Print = NULL;
   PyErr_Clear = NULL;


   Py_Initialize = (Py_InitializeDef) myLib.resolve("Py_Initialize");
   if(!Py_Initialize)
      return false;
   Py_Finalize = (Py_FinalizeDef) myLib.resolve("Py_Finalize");
   if(!Py_Finalize)
      return false;
   PySys_GetObject = (PySys_GetObjectDef) myLib.resolve("PySys_GetObject");
   if(!PySys_GetObject)
      return false;
   PyString_FromString = (PyString_FromStringDef) myLib.resolve("PyString_FromString");
   if(!PyString_FromString)
      return false;
   PyList_Append = (PyList_AppendDef) myLib.resolve("PyList_Append");
   if(!PyList_Append)
      return false;
   PyImport_Import = (PyImport_ImportDef) myLib.resolve("PyImport_Import");
   if(!PyImport_Import)
      return false;
   PyImport_ReloadModule = (PyImport_ReloadModuleDef) myLib.resolve("PyImport_ReloadModule");
   if(!PyImport_ReloadModule)
      return false;
   PyObject_GetAttrString = (PyObject_GetAttrStringDef) myLib.resolve("PyObject_GetAttrString");
   if(!PyObject_GetAttrString)
      return false;
   PyCallable_Check = (PyCallable_CheckDef) myLib.resolve("PyCallable_Check");
   if(!PyCallable_Check)
      return false;
   PyDict_New = (PyDict_NewDef) myLib.resolve("PyDict_New");
   if(!PyDict_New)
      return false;
   PyTuple_New = (PyTuple_NewDef) myLib.resolve("PyTuple_New");
   if(!PyTuple_New)
      return false;
   PyLong_FromLong = (PyLong_FromLongDef) myLib.resolve("PyLong_FromLong");
   if(!PyLong_FromLong)
      return false;
   PyFloat_FromDouble = (PyFloat_FromDoubleDef) myLib.resolve("PyFloat_FromDouble");
   if(!PyFloat_FromDouble)
      return false;
   PyDict_SetItem = (PyDict_SetItemDef) myLib.resolve("PyDict_SetItem");
   if(!PyDict_SetItem)
      return false;
   Py_IncRef = (Py_IncRefDef) myLib.resolve("Py_IncRef");
   if(!Py_IncRef)
      return false;
   Py_DecRef = (Py_DecRefDef) myLib.resolve("Py_DecRef");
   if(!Py_DecRef)
      return false;
   PyTuple_SetItem = (PyTuple_SetItemDef) myLib.resolve("PyTuple_SetItem");
   if(!PyTuple_SetItem)
      return false;
   PyObject_CallObject = (PyObject_CallObjectDef) myLib.resolve("PyObject_CallObject");
   if(!PyObject_CallObject)
      return false;
   PyList_Size = (PyList_SizeDef) myLib.resolve("PyList_Size");
   if(!PyList_Size)
      return false;
   PyList_GetItem = (PyList_GetItemDef) myLib.resolve("PyList_GetItem");
   if(!PyList_GetItem)
      return false;
   PyTuple_GetItem = (PyTuple_GetItemDef) myLib.resolve("PyTuple_GetItem");
   if(!PyTuple_GetItem)
      return false;
   PyFloat_AsDouble = (PyFloat_AsDoubleDef) myLib.resolve("PyFloat_AsDouble");
   if(!PyFloat_AsDouble)
      return false;
   PyString_AsString = (PyString_AsStringDef) myLib.resolve("PyString_AsString");
   if(!PyString_AsString)
      return false;
   PyInt_AsLong = (PyInt_AsLongDef) myLib.resolve("PyInt_AsLong");
   if(!PyInt_AsLong)
      return false;
   PyDict_Keys = (PyDict_KeysDef) myLib.resolve("PyDict_Keys");
   if(!PyDict_Keys)
      return false;
   PyDict_Size = (PyDict_SizeDef) myLib.resolve("PyDict_Size");
   if(!PyDict_Size)
   {
       qDebug()<<"Failed to load python function PyDict_Size";
       return false;
   }
   PyDict_GetItem = (PyDict_GetItemDef) myLib.resolve("PyDict_GetItem");
   if(!PyDict_GetItem)
   {
       qDebug()<<"Failed to load python function PyDict_GetItem";
       return false;
   }
   PyErr_Print = (PyErr_PrintDef) myLib.resolve("PyErr_Print");
   if(!PyErr_Print)
   {
       qDebug()<<"Failed to load python function PyErr_Print";
       return false;
   }
   PyErr_Clear = (PyErr_ClearDef) myLib.resolve("PyErr_Clear");
   if(!PyErr_Clear)
   {
       qDebug()<<"Failed to load python function PyErr_Clear";
       return false;
   }




   qDebug()<<"All required python functions found.";
   Py_Initialize();
   m_foundFuncs = true;

   return m_foundFuncs;
}

/*---------------------------------------------------------------------------*/

bool PythonLoader::loadFunction(QString path,
                                QString moduleName,
                                QString functionnName)
{

   QString pfKey = moduleName+functionnName;
   //qDebug()<<"load Function";

   if(m_foundFuncs)
   {
        PyObject *pyModule = NULL;
        if( false == m_functionMap.contains(pfKey))
        {
            PyObject *sys_path;
            PyObject *pyPath;
            //QString binaryPath;

            sys_path = PySys_GetObject("path");
            if (sys_path == NULL)
                return false;
            qDebug()<<"Python path object found."<<endl;

            int pyPathSize = PyList_Size(sys_path);
            for (int ia=0; ia<pyPathSize; ia++)
            {
                PyObject *obj = PyList_GetItem(sys_path, ia);
                QString QPyPath = QString(PyString_AsString(obj));
                //Py_DecRef(obj);
                qDebug()<<"Python path = "<<QPyPath;
            }

            pyPath = PyString_FromString(path.toStdString().c_str());
            if (pyPath == NULL)
                return false;

            qDebug()<<"appending to python path: "<<path;
            if (PyList_Append(sys_path, pyPath) < 0)
                throw pyException(pyException::COULD_NOT_APPEND_PATH_TO_PYPATH);
            qDebug()<<"Path appended";

            Py_DecRef(pyPath);
            //Py_DecRef(sys_path);

            qDebug()<<"modulename "<<moduleName;

            PyObject *pyName = PyString_FromString(moduleName.toStdString().c_str());
            if(pyName)
                qDebug()<<"pName init";
            pyModule = PyImport_Import(pyName);
            Py_DecRef(pyName);
        }
        else
        {
            qDebug()<<"Reloaded python function ! " <<moduleName<<" "<<functionnName;
            pyFunc* pf = m_functionMap[pfKey];
            if (pf != NULL)
            {
                //Py_DecRef(pf->pModule);
/*
                if(pf->pArgs)
                    Py_DecRef(pf->pArgs);
                if(pf->pTuple)
                    Py_DecRef(pf->pTuple);
                if(pf->pTupleTuple)
                    Py_DecRef(pf->pTupleTuple);
                if(pf->pDict)
                    Py_DecRef(pf->pDict);
                if(pf->pFunc)
                    Py_DecRef(pf->pFunc);
                if(pf->pModule)
                    Py_DecRef(pf->pModule);
*/

                pyModule = PyImport_ReloadModule(pf->pModule);
                PyErr_Print();
            }
            else
            {
               qDebug()<<"Error: null python module while reloading ! " <<moduleName<<" "<<functionnName;
               m_functionMap.remove(pfKey);
               return false;
            }
        }
        if (pyModule != NULL)
        {
            qDebug()<<"Module found";
            pyFunc* pf = new pyFunc();
            pf->pModule = pyModule;

            pf->pFunc = PyObject_GetAttrString(pyModule,
                                           functionnName.toStdString().c_str());
            if (pf->pFunc && PyCallable_Check(pf->pFunc))
            {
             qDebug()<<"function found and callable, adding: "
                    <<moduleName<<" "<<functionnName;
             pf->pDict = PyDict_New();
             //Py_IncRef(m_pDict);
             //Py_IncRef(m_pArgs);
             //Py_IncRef(m_pFunc);
             pf->pArgs = NULL;
             pf->argCnt = 0;
             pf->retCnt = 0;
             pf->retVals = NULL;
             m_functionMap.insert(pfKey, pf);

             return true;
            }
            else
            {
                PyErr_Print();
                delete pf;
                qDebug()<<"Cound not find function, or function is not callable: "<<functionnName;
                throw pyException(pyException::COULD_NOT_FIND_FUNCTION);
            }
        }
        else
        {
            PyErr_Print();
            qDebug()<<"Cound not find module: "<<moduleName;
            throw pyException(pyException::COULD_NOT_FIND_MODULE);
        }
    }
    return m_foundFuncs;

}

/*---------------------------------------------------------------------------*/

QStringList PythonLoader::getFunctionList(QString path, QString moduleName)
{
   QStringList funcList;

   if(m_foundFuncs)
   {
     PyObject *sys_path;
     PyObject *pyPath;
     //QString binaryPath;

     sys_path = PySys_GetObject("path");
     if (sys_path == NULL)
         return funcList;
     qDebug()<<"Python path object found.";

     pyPath = PyString_FromString(path.toStdString().c_str());
     if (pyPath == NULL)
         return funcList;


     qDebug()<<"appending to python path: "<<path;
     if (PyList_Append(sys_path, pyPath) < 0)
         return funcList;
     qDebug()<<"Path appended";

     Py_DecRef(pyPath);


     PyObject *pyInspectName = PyString_FromString("inspect");
     PyObject *pyInspectModule = PyImport_Import(pyInspectName);

     PyObject *pyName = PyString_FromString(moduleName.toStdString().c_str());
     PyObject *pyModule = PyImport_Import(pyName);
     //Py_DECREF(m_pName);

     if (pyInspectModule && pyModule)
     {
        PyObject *pMemberFunc = PyObject_GetAttrString(pyInspectModule,
                                                       STR_GET_MEMBERS);
        PyObject *pIsFunc = PyObject_GetAttrString(pyInspectModule,
                                                   STR_IS_FUNCTION);
        if (pMemberFunc &&
            pIsFunc &&
            PyCallable_Check(pMemberFunc) &&
            PyCallable_Check(pIsFunc))
        {
            PyObject *pArgs = PyTuple_New(2);
            PyTuple_SetItem(pArgs, 0, pyModule);
            PyTuple_SetItem(pArgs, 1, pIsFunc);
            PyObject* pRetVal = PyObject_CallObject(pMemberFunc, pArgs);
            if (pRetVal)
            {

               long lsize = PyList_Size(pRetVal);
               if(lsize > 0)
               {
                  qDebug()<<"ret size = "<<lsize;
                  for(int i=0; i<lsize; i++)
                  {
                      PyObject* funcTup = PyList_GetItem(pRetVal, i);
                      if(funcTup)
                      {
                         PyObject* pFuncName = PyTuple_GetItem(funcTup,0);
                         if(pFuncName)
                         {
                            char* tempStr = PyString_AsString(pFuncName);
                            funcList.append(QString(tempStr));
                         }
                      }
                  }
               }
            }
         }
      }
   }

   return funcList;
}

/*---------------------------------------------------------------------------*/

bool PythonLoader::isLoaded()
{

    return m_foundFuncs;

}

/*---------------------------------------------------------------------------*/

bool PythonLoader::getRetDouble(QString module,
                                QString func,
                                int idx,
                                double *val)
{

   QString pfKey = module+func;
   if(m_foundFuncs && m_functionMap.contains(pfKey))
   {
      pyFunc* pf = m_functionMap[pfKey];

      if(pf->retCnt > idx)
      {
         *val = pf->retVals[idx];
         return true;
      }
      else
      {
         return false;
      }

   }
   else
      return false;

}

/*---------------------------------------------------------------------------*/

bool PythonLoader::getRetDict(QString module,
                              QString func,
                              QMap<QString, double> *val)
{

   QString pfKey = module+func;
   if(m_foundFuncs && m_functionMap.contains(pfKey))
   {
      pyFunc* pf = m_functionMap[pfKey];

      foreach(QString key, pf->retDict.keys())
      {
         val->insert(key, pf->retDict[key]);
      }
      return true;
   }
   else
      return false;

}

/*---------------------------------------------------------------------------*/

bool PythonLoader::getRetStrDict(QString module,
                              QString func,
                              QMap<QString, QString> *val)
{

   QString pfKey = module+func;
   if(m_foundFuncs && m_functionMap.contains(pfKey))
   {
      pyFunc* pf = m_functionMap[pfKey];

      foreach(QString key, pf->retStrDict.keys())
      {
         val->insert(key, pf->retStrDict[key]);
      }
      return true;
   }
   else
      return false;

}

/*---------------------------------------------------------------------------*/

bool PythonLoader::safeCheck()
{

   QString path =  QCoreApplication::applicationFilePath();
   //QString appName = QCoreApplication::applicationName();
   //path += appName;
   QStringList arguments;
   arguments << "-testPython";

   QProcess proc; 
   proc.start(path, arguments);
   proc.waitForFinished();
   if ( 0 == proc.exitCode() )
   {
	   m_safeCheckFailed = false;
      return true;
   }

   m_safeCheckFailed = true;
   return false;

}

/*---------------------------------------------------------------------------*/

bool PythonLoader::setArgDict(QString module,
                              QString func,
                              int idx,
                              QMap<QString, double> globalVars)
{

   QString pfKey = module+func;
   if(m_foundFuncs && m_functionMap.contains(pfKey))
   {
      pyFunc* pf = m_functionMap[pfKey];
      PyObject *pKey, *pValue;

      PyObject * tempDict =PyDict_New();
      if(pf->argCnt > idx)
      {
         foreach(QString key, globalVars.keys())
         {
             pKey = PyString_FromString(key.toStdString().c_str());
             pValue = PyFloat_FromDouble(globalVars[key]);
//             PyDict_SetItem(pf->pDict, pKey, pValue);
             PyDict_SetItem(tempDict, pKey, pValue);
         }

//         PyTuple_SetItem(pf->pArgs, idx, pf->pDict);
         PyTuple_SetItem(pf->pArgs, idx, tempDict);
         return true;
      }
      else
         return false;
      if(tempDict != NULL)
         Py_IncRef(tempDict);
   }

   return false;

}

/*---------------------------------------------------------------------------*/

bool PythonLoader::setArgTupleTuples(QString module,
                                     QString func,
                                     int idx,
                                     QList < QList<double> > globalTuple)
{

   QString pfKey = module+func;
   if(m_foundFuncs && m_functionMap.contains(pfKey))
   {
      pyFunc* pf = m_functionMap[pfKey];
      PyObject *pValueValue;
      pf->pTuple=PyTuple_New(globalTuple.size());
      pf->pTupleTuple=PyTuple_New(globalTuple.at(0).size());
      if(pf->argCnt > idx)
      {
          for(int i =0; i< globalTuple.size(); i++)
          {
              PyObject *temp;
              temp = PyTuple_New(globalTuple.at(0).size());
              for(int j = 0; j < globalTuple.at(0).size(); j++)
              {
                pValueValue = PyFloat_FromDouble(globalTuple.at(i).at(j));
                PyTuple_SetItem(temp, j , pValueValue);
              }
              PyTuple_SetItem(pf->pTuple, i, temp);
          }
         PyTuple_SetItem(pf->pArgs, idx, pf->pTuple);
         return true;
      }
      else
         return false;
   }
   else
      return false;

}

/*---------------------------------------------------------------------------*/

bool PythonLoader::setArgDouble(QString module,
                                QString func,
                                int idx,
                                double val)
{

   QString pfKey = module+func;
   if(m_foundFuncs && m_functionMap.contains(pfKey))
   {
      pyFunc* pf = m_functionMap[pfKey];

      if(pf->argCnt > idx && pf->pArgs != NULL)
      {
         PyObject* pVal = PyFloat_FromDouble(val);
         if(pVal != NULL)
         {
            if( 0 == PyTuple_SetItem(pf->pArgs, idx, pVal))
               return true;
            else
               return false;
         }
         else
            return false;
      }
      else
      {
         return false;
      }

   }
   else
      return false;

}

/*---------------------------------------------------------------------------*/

bool PythonLoader::setArgLong(QString module, QString func, int idx, long val)
{

   QString pfKey = module+func;
   if(m_foundFuncs && m_functionMap.contains(pfKey))
   {
      pyFunc* pf = m_functionMap[pfKey];

      if(pf->argCnt > idx && pf->pArgs != NULL)
      {
         PyObject* pVal = PyLong_FromLong(val);
         if(pVal != NULL)
         {
            if(0==PyTuple_SetItem(pf->pArgs, idx, pVal))
               return true;
            else
               return false;
         }
         else
            return false;
      }
      else
      {
         return false;
      }

   }
   else
      return false;

}

/*---------------------------------------------------------------------------*/

bool PythonLoader::setArgString(QString module,
                                QString func,
                                int idx,
                                QString val)
{

   QString pfKey = module+func;
   if(m_foundFuncs && m_functionMap.contains(pfKey))
   {
      pyFunc* pf = m_functionMap[pfKey];

      if(pf->argCnt > idx && pf->pArgs != NULL)
      {
         PyObject* pVal = PyString_FromString(val.toStdString().c_str());
         if(pVal != NULL)
         {
            if(0==PyTuple_SetItem(pf->pArgs, idx, pVal))
               return true;
            else
               return false;
         }
         else
            return false;
      }
      else
      {
         return false;
      }

   }
   else
      return false;

}

/*---------------------------------------------------------------------------*/

bool PythonLoader::setNumArgs(QString module, QString func, int amt)
{

   QString pfKey = module+func;
   if(m_foundFuncs && m_functionMap.contains(pfKey))
   {
      pyFunc* pf = m_functionMap[pfKey];

      pf->pArgs = PyTuple_New(amt);
      pf->argCnt = amt;
      return true;
   }
   else
      return false;

}

/*---------------------------------------------------------------------------*/

bool PythonLoader::setRetCnt(QString module, QString func, int amt)
{

   QString pfKey = module+func;
   if(m_foundFuncs && m_functionMap.contains(pfKey))
   {
      pyFunc* pf = m_functionMap[pfKey];

      pf->retCnt = amt;
      if(pf->retVals != NULL)
         delete [] pf->retVals;
      pf->retVals = new double[amt];
      return true;
   }
   else
      return false;

}

/*---------------------------------------------------------------------------*/

