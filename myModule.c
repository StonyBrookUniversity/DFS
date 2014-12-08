/*#include<stdio.h>
#include "Python.h"

int main()
{
    printf("Hello World");
    return 0;
}

int hello()
{
    printf("Hello");
    return 0;
}*/


#ifdef __cplusplus
extern "C" {
#endif

#include <Python.h>

/*
 * Function to be called from Python
 */
static PyObject* py_myFunction(PyObject* self, PyObject* args)
{
    char *s = (char *)"Hello from C!";
    return Py_BuildValue("s", s);
}
static PyObject* elephantFlowArrival(PyObject* self, PyObject* args)
{
    char *s = (char *)"Hello from C!";

    //return Py_BuildValue("s", s);

    PyObject *object;
    PyObject *callback = NULL;
    PyObject *result = NULL;

    if (PyArg_UnpackTuple(args, "ref", 1, 2, &object, &callback)) {
        result = PyWeakref_NewRef(object, callback);
    }


}

/*
 * Bind Python function names to our C functions
 */
static PyMethodDef myModule_methods[] = {
    {"myFunction", py_myFunction, METH_VARARGS},
    {"elephantFlowArrival", elephantFlowArrival, METH_VARARGS},
   // {NULL, NULL}
};

/*
int elephantFlowArrival(string flowID,int source, int destination,int time) {

	if (this->alg==tDBeam) return 1;
	if (this->alg==cThrough) return 1;
	currentTime=time;
	flow f;
	f.flowID=flowID;
	f.source=source;
	f.destination=destination;
	this->unprocessesFlows.push_back(f);
	this->computTopo(time);
	return 1;
}
*/


/*
 * Python calls this to let us initialize our module
 */
void initmyModule()
{
    (void) Py_InitModule("myModule", myModule_methods);
}

#ifdef __cplusplus
}  // extern "C"
#endif
