
#include <Python.h>

#include <netax25/ax25.h>
#include <netax25/axlib.h>

static PyObject* amateurradio_test(PyObject* self, PyObject* args)
{
    int x;

    if (!PyArg_ParseTuple(args, "i", &x))
        return NULL;

    return Py_BuildValue("i", x);
}

static PyObject* amateurradio_ax25_aton(PyObject* seld, PyObject* args)
{
    const char* cp;
    struct full_sockaddr_ax25 fsap;

    memset(&fsap, 0, sizeof(fsap));

    if (!PyArg_ParseTuple(args, "s", &cp))
        return NULL;

    if (-1 == ax25_aton(cp, &fsap))
        return PyErr_SetFromErrno(NULL);

    return Py_BuildValue("iccccccc", 
        fsap.fsa_ax25.sax25_family, 
        fsap.fsa_ax25.sax25_call.ax25_call[0],
        fsap.fsa_ax25.sax25_call.ax25_call[1],
        fsap.fsa_ax25.sax25_call.ax25_call[2],
        fsap.fsa_ax25.sax25_call.ax25_call[3],
        fsap.fsa_ax25.sax25_call.ax25_call[4],
        fsap.fsa_ax25.sax25_call.ax25_call[5],
        fsap.fsa_ax25.sax25_call.ax25_call[6]);
}

static PyMethodDef amateurradio_methods[] = {
    {"test", amateurradio_test, METH_VARARGS, "Test!"},
    {"ax25_aton", amateurradio_ax25_aton, METH_VARARGS, "ax25_aton"},
    {NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC
initamateurradio(void)
{
    PyObject* m;

    m = Py_InitModule("amateurradio", amateurradio_methods);
    if (m == NULL)
        return;
}

