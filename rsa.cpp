#include <pybind11/pybind11.h>
#include <RSA.hpp>

namespace py = pybind11;

PYBIND11_MODULE(example, m) {
    py::class_<RSA_generation_lib<int>>(m, "RSA_lib")
        .def(py::init<>())
        .def("get_n", &RSA_generation_lib<int>::get_n, "get the product of p1 and p1.")
		.def("encode", &RSA_generation_lib<int>::encode, "encode message.")
		.def("decode", &RSA_generation_lib<int>::decode, "decode message.");
}