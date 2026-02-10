#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stdio.h>

// Version 
#define PYODX_VERSION "1.2.0"

// return version  
static PyObject* odbMeta_version(PyObject *self, PyObject *Py_UNUSED(ignored)) {
    return Py_BuildValue("s", PYODX_VERSION);
}


// Get platform , build etc  info 
static PyObject* odbMeta_info(PyObject *self, PyObject *Py_UNUSED(ignored)) {
    return Py_BuildValue(
        "{s:s, s:s, s:s, s:s}",
        "version"     , PYODX_VERSION,
        "compiler"    , Py_GetCompiler() ,
        "platform"    , Py_GetPlatform() ,
        "python_build", Py_GetBuildInfo()
    );
}


// Méthode stub pour initialiser des variables ODB
/*static PyObject* odbMeta_env(PyObject *self, PyObject *Py_UNUSED(ignored)) {
    // Ici tu pourrais initialiser des variables env spécifiques à ODB
    // Par exemple : setenv("ODB_IO_METHOD", "default", 0);
    // Pour l'instant, on renvoie juste un message
    return Py_BuildValue("s", "ODB environment stub initialized.");
}*/


