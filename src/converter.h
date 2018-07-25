#ifndef CONVERTER_H
#define CONVERTER_H

#include <boost/python.hpp>
#include <boost/python/tuple.hpp>

namespace py = boost::python;

template<typename T1, typename T2>
struct PairToPythonConverter {
    static PyObject* convert(const std::pair<T1, T2>& pair)
    {
        return py::incref(py::make_tuple(pair.first, pair.second).ptr());
    }

    static PyTypeObject const *get_pytype () {return &PyTuple_Type; }
};

template<typename T1, typename T2>
struct PythonToPairConverter {
    PythonToPairConverter()
    {
        py::converter::registry::push_back(&convertible, &construct, py::type_id<std::pair<T1, T2> >());
    }
    static void* convertible(PyObject* obj)
    {
        if (!PyTuple_CheckExact(obj)) return 0;
        if (PyTuple_Size(obj) != 2) return 0;
        return obj;
    }
    static void construct(PyObject* obj, py::converter::rvalue_from_python_stage1_data* data)
    {
        py::tuple tuple(py::borrowed(obj));
        void* storage = ((py::converter::rvalue_from_python_storage<std::pair<T1, T2> >*) data)->storage.bytes;
        new (storage) std::pair<T1, T2>(py::extract<T1>(tuple[0]), py::extract<T2>(tuple[1]));
        data->convertible = storage;
    }
};

template<typename T1, typename T2>
struct pair_tuple_converter {
    py::to_python_converter< std::pair<T1, T2>, PairToPythonConverter<T1, T2>, true > toPy;
    PythonToPairConverter<T1, T2> fromPy;
};

#endif // CONVERTER_H
