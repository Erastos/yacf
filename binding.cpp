
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "process.h"
#include "socket.h"


namespace py = pybind11;

PYBIND11_MODULE(yacf, m) {
    py::class_<Process>(m, "Process")
        .def(py::init<std::string, std::vector<std::string>>())
        .def("start", &Process::start)
        .def("get", &Process::get)
        .def("send", &Process::send);

    py::class_<Socket>(m, "Socket")
        .def(py::init<std::string, int>())
        .def("start", &Socket::start)
        .def("get", &Socket::get)
        .def("put", &Socket::put);
}
