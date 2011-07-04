
/* Author: Alejandro Santos, alejolp@alejolp.com.ar */

#include <Python.h>
#include <structmember.h>

#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netax25/ax25.h>
#include <netax25/axlib.h>

/* forward declarations */

typedef struct {
    PyObject_HEAD
    ax25_address field;
} ax25_address_object;

typedef struct {
    PyObject_HEAD
    struct full_sockaddr_ax25 field;
} full_sockaddr_ax25_object;

/* ax25_address */

static int ax25_address_init(ax25_address_object *self, PyObject *args, PyObject *kwds);

static PyObject* ax25_address_new(PyTypeObject *type, PyObject *args, PyObject *kwds);

/* full_sockaddr_ax25 */

static PyObject* full_sockaddr_ax25_getsax25_call(full_sockaddr_ax25_object *self, void *closure);

static int full_sockaddr_ax25_setsax25_call(full_sockaddr_ax25_object *self, PyObject *value, void *closure);

static PyObject* full_sockaddr_ax25_getdigipeater(full_sockaddr_ax25_object *self, void *closure);

static int full_sockaddr_ax25_setdigipeater(full_sockaddr_ax25_object *self, PyObject *value, void *closure);

static PyObject* full_sockaddr_ax25_new(PyTypeObject *type, PyObject *args, PyObject *kwds);

static int full_sockaddr_ax25_init(full_sockaddr_ax25_object *self, PyObject *args, PyObject *kwds);


/* ax25_address */

static int
ax25_address_init(ax25_address_object *self, PyObject *args, PyObject *kwds)
{
    const char* addr;

    if (!PyArg_ParseTuple(args, "s", &addr))
        return -1;

    if (-1 == ax25_aton_entry(addr, self->field.ax25_call)) {
        PyErr_SetFromErrno(PyExc_ValueError);
        return -1;
    }

    return 0;
}

static PyObject *
ax25_address_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    ax25_address_object *self;

    self = (ax25_address_object*) type->tp_alloc(type, 0);
    if (self != NULL) {
        memset(&self->field, 0, sizeof(ax25_address));
    }

    return (PyObject*) self;
}

static PyObject *
ax25_address_repr(ax25_address_object* self)
{
    PyObject *b, *r, *f;
    
    b = PyBytes_FromStringAndSize(self->field.ax25_call, 7);
    if (b == NULL)
        return NULL;

    r = PyObject_Repr(b);
    if (r == NULL) {
        Py_DECREF(b);
        return NULL;
    }

    f = PyUnicode_FromFormat("<ax25_address %U>", r);
    if (f == NULL) {
        Py_DECREF(r);
        Py_DECREF(b);
        return NULL;
    }

    Py_DECREF(r);
    Py_DECREF(b);
    return f;
}

static PyObject *
ax25_address_str(ax25_address_object* self)
{
    const char* ret;

    ret = ax25_ntoa(&self->field);
    return PyUnicode_FromStringAndSize(ret, strlen(ret));
}

static PyTypeObject ax25_address_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "ax25_address",             /* tp_name */
    sizeof(ax25_address_object), /* tp_basicsize */
    0,                         /* tp_itemsize */
    0,                         /* tp_dealloc */
    0,                         /* tp_print */
    0,                         /* tp_getattr */
    0,                         /* tp_setattr */
    0,                         /* tp_reserved */
    (reprfunc)ax25_address_repr,                         /* tp_repr */
    0,                         /* tp_as_number */
    0,                         /* tp_as_sequence */
    0,                         /* tp_as_mapping */
    0,                         /* tp_hash  */
    0,                         /* tp_call */
    (reprfunc)ax25_address_str,                         /* tp_str */
    0,                         /* tp_getattro */
    0,                         /* tp_setattro */
    0,                         /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,        /* tp_flags */
    "ax25_address objects",           /* tp_doc */
    0,		               /* tp_traverse */
    0,		               /* tp_clear */
    0,		               /* tp_richcompare */
    0,		               /* tp_weaklistoffset */
    0,		               /* tp_iter */
    0,		               /* tp_iternext */
    0,             /* tp_methods */
    0,             /* tp_members */
    0,           /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc) ax25_address_init,      /* tp_init */
    0,                         /* tp_alloc */
    ax25_address_new,                 /* tp_new */

};

/* full_sockaddr_ax25 */


static PyObject *
full_sockaddr_ax25_getsax25_call(full_sockaddr_ax25_object *self, void *closure)
{
    ax25_address_object* ax25o;

    ax25o = (ax25_address_object*) ax25_address_new(&ax25_address_type, NULL, NULL);
    if (ax25o != NULL) {
        ax25o->field = self->field.fsa_ax25.sax25_call;
    }

    return (PyObject*) ax25o;
}

static int
full_sockaddr_ax25_setsax25_call(full_sockaddr_ax25_object *self, PyObject *value, void *closure)
{
    if (value == NULL) {
        PyErr_SetString(PyExc_TypeError, "Cannot delete the attribute.");
        return -1;
    }

    PyErr_SetString(PyExc_TypeError, "Not implemented.");
    return -1;
}

static PyObject *
full_sockaddr_ax25_getdigipeater(full_sockaddr_ax25_object *self, void *closure)
{
    PyErr_SetString(PyExc_TypeError, "Not implemented.");
    return NULL;
}

static int
full_sockaddr_ax25_setdigipeater(full_sockaddr_ax25_object *self, PyObject *value, void *closure)
{
    if (value == NULL) {
        PyErr_SetString(PyExc_TypeError, "Cannot delete the attribute.");
        return -1;
    }

    PyErr_SetString(PyExc_TypeError, "Not implemented.");
    return -1;
}

static PyObject*
full_sockaddr_ax25_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    full_sockaddr_ax25_object *self;

    self = (full_sockaddr_ax25_object*) type->tp_alloc(type, 0);
    if (self != NULL) {
        memset(&self->field, 0, sizeof(self->field));
    }

    return (PyObject*) self;
}

static int
full_sockaddr_ax25_init(full_sockaddr_ax25_object *self, PyObject *args, PyObject *kwds)
{
    return 0;
}

static PyGetSetDef full_sockaddr_ax25_getseters[] = {
    {"sax25_call", 
     (getter)full_sockaddr_ax25_getsax25_call,
     (setter)full_sockaddr_ax25_setsax25_call,
     "sax25_call, an ax25_address.",
     NULL},
    {"fsa_digipeater", 
     (getter)full_sockaddr_ax25_getdigipeater,
     (setter)full_sockaddr_ax25_setdigipeater,
     "fsa_digipeater, list of ax25_address.",
     NULL},
    {NULL}  /* Sentinel */
};

static PyTypeObject full_sockaddr_ax25_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "full_sockaddr_ax25",             /* tp_name */
    sizeof(full_sockaddr_ax25_object), /* tp_basicsize */
    0,                         /* tp_itemsize */
    0,                         /* tp_dealloc */
    0,                         /* tp_print */
    0,                         /* tp_getattr */
    0,                         /* tp_setattr */
    0,                         /* tp_reserved */
    0,                         /* tp_repr */
    0,                         /* tp_as_number */
    0,                         /* tp_as_sequence */
    0,                         /* tp_as_mapping */
    0,                         /* tp_hash  */
    0,                         /* tp_call */
    0,                         /* tp_str */
    0,                         /* tp_getattro */
    0,                         /* tp_setattro */
    0,                         /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,        /* tp_flags */
    "full_sockaddr_ax25 objects",           /* tp_doc */
    0,		               /* tp_traverse */
    0,		               /* tp_clear */
    0,		               /* tp_richcompare */
    0,		               /* tp_weaklistoffset */
    0,		               /* tp_iter */
    0,		               /* tp_iternext */
    0,             /* tp_methods */
    0,             /* tp_members */
    full_sockaddr_ax25_getseters,           /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc) full_sockaddr_ax25_init,      /* tp_init */
    0,                         /* tp_alloc */
    full_sockaddr_ax25_new,                 /* tp_new */

};

/* *********************************************************** */

static PyObject* amateurradio_test(PyObject* self, PyObject* args)
{
    int x;

    if (!PyArg_ParseTuple(args, "i", &x))
        return NULL;

    return PyLong_FromLong(x);
}

static PyObject* amateurradio_ax25_aton(PyObject* self, PyObject* args)
{
    const char* cp;
    full_sockaddr_ax25_object* fsao;

    if (!PyArg_ParseTuple(args, "s", &cp))
        return NULL;

    fsao = (full_sockaddr_ax25_object*)
        full_sockaddr_ax25_new(&full_sockaddr_ax25_type, NULL, NULL);
    if (fsao == NULL)
        return NULL;

    if (-1 == ax25_aton(cp, &fsao->field)) {
        Py_DECREF(fsao);
        return PyErr_SetFromErrno(PyExc_ValueError);
    }

    return (PyObject*) fsao;
}

static PyObject* amateurradio_ax25_aton_entry(PyObject* self, PyObject* args)
{
    const char* cp;
    char dest[7]; /* segun ax25.h son 7 bytes maximo. */

    if (!PyArg_ParseTuple(args, "s", &cp))
        return NULL;

    if (-1 == ax25_aton_entry(cp, dest)) {
        return PyErr_SetFromErrno(PyExc_ValueError);
    }

    return PyBytes_FromStringAndSize(dest, 7);
}

static PyObject* amateurradio_ax25_validate(PyObject* self, PyObject* args)
{
    Py_buffer cp;

    if (!PyArg_ParseTuple(args, "y*", &cp))
        return NULL;

    if (ax25_validate(cp.buf)) {
        Py_RETURN_TRUE;
    } else {
        Py_RETURN_FALSE;
    }
}

static PyObject* amateurradio_libax25_version(PyObject* self, PyObject* args)
{
    return PyUnicode_FromString("");
}

/* Methods, Module */

static PyMethodDef amateurradio_methods[] = {
    {"test", amateurradio_test, METH_VARARGS, "Test!"},
    {"ax25_aton", amateurradio_ax25_aton, METH_VARARGS, "ax25_aton"},
    {"ax25_aton_entry", amateurradio_ax25_aton_entry, METH_VARARGS, "ax25_aton_entry"},
    {"ax25_validate", amateurradio_ax25_validate, METH_VARARGS, "ax25_validate"},
    {"libax25_version", amateurradio_libax25_version, METH_VARARGS, "ax25_version"},
    {NULL, NULL, 0, NULL}
};

static PyModuleDef amateurradio_module = {
    PyModuleDef_HEAD_INIT,
    "amateurradio",
    NULL,
    -1,
    amateurradio_methods
};


/* INIT */


PyMODINIT_FUNC
PyInit_amateurradio(void)
{
    PyObject* m;

    /* full_sockaddr_ax25_type.tp_new = PyType_GenericNew; */
    if (PyType_Ready(&full_sockaddr_ax25_type) < 0)
        return NULL;

    /* */
    if (PyType_Ready(&ax25_address_type) < 0)
        return NULL;

    m = PyModule_Create(&amateurradio_module);
    if (m == NULL)
        return NULL;

    Py_INCREF(&full_sockaddr_ax25_type);
    PyModule_AddObject(m, "full_sockaddr_ax25", (PyObject *)&full_sockaddr_ax25_type);

    Py_INCREF(&ax25_address_type);
    PyModule_AddObject(m, "ax25_address", (PyObject *)&ax25_address_type);

    PyModule_AddObject(m, "SOL_AX25", PyLong_FromLong(SOL_AX25));
    PyModule_AddObject(m, "AF_AX25", PyLong_FromLong(AF_AX25));
    PyModule_AddObject(m, "PF_AX25", PyLong_FromLong(PF_AX25));

    PyModule_AddObject(m, "AX25_WINDOW", PyLong_FromLong(AX25_WINDOW));
    PyModule_AddObject(m, "AX25_T1", PyLong_FromLong(AX25_T1));
    PyModule_AddObject(m, "AX25_T2", PyLong_FromLong(AX25_T2));
    PyModule_AddObject(m, "AX25_T3", PyLong_FromLong(AX25_T3));
    PyModule_AddObject(m, "AX25_N2", PyLong_FromLong(AX25_N2));
    PyModule_AddObject(m, "AX25_BACKOFF", PyLong_FromLong(AX25_BACKOFF));
    PyModule_AddObject(m, "AX25_EXTSEQ", PyLong_FromLong(AX25_EXTSEQ));
    PyModule_AddObject(m, "AX25_PIDINCL", PyLong_FromLong(AX25_PIDINCL));
    PyModule_AddObject(m, "AX25_IDLE", PyLong_FromLong(AX25_IDLE));
    PyModule_AddObject(m, "AX25_PACLEN", PyLong_FromLong(AX25_PACLEN));
    PyModule_AddObject(m, "AX25_IPMAXQUEUE", PyLong_FromLong(AX25_IPMAXQUEUE));
    PyModule_AddObject(m, "AX25_IAMDIGI", PyLong_FromLong(AX25_IAMDIGI));
    PyModule_AddObject(m, "AX25_KILL", PyLong_FromLong(AX25_KILL));
    PyModule_AddObject(m, "SIOCAX25GETUID", PyLong_FromLong(SIOCAX25GETUID));
    PyModule_AddObject(m, "SIOCAX25ADDUID", PyLong_FromLong(SIOCAX25ADDUID));
    PyModule_AddObject(m, "SIOCAX25DELUID", PyLong_FromLong(SIOCAX25DELUID));
    PyModule_AddObject(m, "SIOCAX25NOUID", PyLong_FromLong(SIOCAX25NOUID));
    PyModule_AddObject(m, "SIOCAX25BPQADDR", PyLong_FromLong(SIOCAX25BPQADDR));
    PyModule_AddObject(m, "SIOCAX25GETPARMS", PyLong_FromLong(SIOCAX25GETPARMS));
    PyModule_AddObject(m, "SIOCAX25SETPARMS", PyLong_FromLong(SIOCAX25SETPARMS));
    PyModule_AddObject(m, "SIOCAX25OPTRT", PyLong_FromLong(SIOCAX25OPTRT));
    PyModule_AddObject(m, "SIOCAX25CTLCON", PyLong_FromLong(SIOCAX25CTLCON));
    PyModule_AddObject(m, "SIOCAX25GETINFO", PyLong_FromLong(SIOCAX25GETINFO));
    PyModule_AddObject(m, "SIOCAX25ADDFWD", PyLong_FromLong(SIOCAX25ADDFWD));
    PyModule_AddObject(m, "SIOCAX25DELFWD", PyLong_FromLong(SIOCAX25DELFWD));
    PyModule_AddObject(m, "AX25_NOUID_DEFAULT", PyLong_FromLong(AX25_NOUID_DEFAULT));
    PyModule_AddObject(m, "AX25_NOUID_BLOCK", PyLong_FromLong(AX25_NOUID_BLOCK));
    PyModule_AddObject(m, "AX25_SET_RT_IPMODE", PyLong_FromLong(AX25_SET_RT_IPMODE));
    PyModule_AddObject(m, "AX25_DIGI_INBAND", PyLong_FromLong(AX25_DIGI_INBAND));
    PyModule_AddObject(m, "AX25_DIGI_XBAND", PyLong_FromLong(AX25_DIGI_XBAND));
    PyModule_AddObject(m, "AX25_MAX_DIGIS", PyLong_FromLong(AX25_MAX_DIGIS));
    PyModule_AddObject(m, "AX25_VALUES_IPDEFMODE", PyLong_FromLong(AX25_VALUES_IPDEFMODE));
    PyModule_AddObject(m, "AX25_VALUES_AXDEFMODE", PyLong_FromLong(AX25_VALUES_AXDEFMODE));
    PyModule_AddObject(m, "AX25_VALUES_NETROM", PyLong_FromLong(AX25_VALUES_NETROM));
    PyModule_AddObject(m, "AX25_VALUES_TEXT", PyLong_FromLong(AX25_VALUES_TEXT));
    PyModule_AddObject(m, "AX25_VALUES_BACKOFF", PyLong_FromLong(AX25_VALUES_BACKOFF));
    PyModule_AddObject(m, "AX25_VALUES_CONMODE", PyLong_FromLong(AX25_VALUES_CONMODE));
    PyModule_AddObject(m, "AX25_VALUES_WINDOW", PyLong_FromLong(AX25_VALUES_WINDOW));
    PyModule_AddObject(m, "AX25_VALUES_EWINDOW", PyLong_FromLong(AX25_VALUES_EWINDOW));
    PyModule_AddObject(m, "AX25_VALUES_T1", PyLong_FromLong(AX25_VALUES_T1));
    PyModule_AddObject(m, "AX25_VALUES_T2", PyLong_FromLong(AX25_VALUES_T2));
    PyModule_AddObject(m, "AX25_VALUES_T3", PyLong_FromLong(AX25_VALUES_T3));
    PyModule_AddObject(m, "AX25_VALUES_N2", PyLong_FromLong(AX25_VALUES_N2));
    PyModule_AddObject(m, "AX25_VALUES_DIGI", PyLong_FromLong(AX25_VALUES_DIGI));
    PyModule_AddObject(m, "AX25_VALUES_IDLE", PyLong_FromLong(AX25_VALUES_IDLE));
    PyModule_AddObject(m, "AX25_VALUES_PACLEN", PyLong_FromLong(AX25_VALUES_PACLEN));
    PyModule_AddObject(m, "AX25_VALUES_IPMAXQUEUE", PyLong_FromLong(AX25_VALUES_IPMAXQUEUE));
    PyModule_AddObject(m, "AX25_MAX_VALUES", PyLong_FromLong(AX25_MAX_VALUES));

    return m;
}

