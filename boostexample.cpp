#include <stdlib.h>
#include <string>
#include <vector>
#include <boost/python.hpp>

using namespace boost::python;
/*
struct World
{
    World(std::string msg): msg(msg) {} // added constructor
    void set(std::string msg) { this->msg = msg; }
    std::string greet() { return msg; }
    std::string msg;
};
*/
struct World
{
    void add(double n)
    {
        this->myvec.push_back(n);
    }

    void massadd(boost::python::list& ns)
    {
        for (int i = 0; i < len(ns); ++i)
        {
            add(boost::python::extract<double>(ns[i]));
        }
    }

    std::vector<double> show()
    {
     return this->myvec;
    }
    std::vector<double> myvec;
};

struct Var
{
    Var(std::string name) : name(name), value() {}
    std::string const name;
    float value;
};


BOOST_PYTHON_MODULE(myexample)
{
/*
    class_<World>("World", init<std::string>())
    .def("greet", &World::greet)
    .def("set", &World::set)
    ;
*/
    class_<Var>("Var", init<std::string>())
    .def_readonly("name", &Var::name)
    .def_readwrite("value", &Var::value)
    ;


    class_<std::vector<double> >("double_vector")
    .def(vector_indexing_suite<std::vector<double> >())
    ;

    class_<World>("World")
     .def("show", &World::show)
     .def("add", &World::add)
     //.def("massadd", &World::massadd)
    ;
}

