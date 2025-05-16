#include <pybind11/pybind11.h>
#include <matplot/matplot.h>
#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

int add(int i, int j) {
    return i + j;
}

void sin(){
    using namespace matplot;

    std::vector<double> x = linspace(0, 10, 1000);
    std::vector<double> y = transform(x, [](auto x) { return sin(2 * x); });
    plot(x, y)->color({0.f, 0.7f, 0.9f});
    title("2-D Line Plot");
    xlabel("x");
    ylabel("sin(2x)");
    ylim({-2, +2});
    show();
}

void cos(){
    using namespace matplot;

    std::vector<double> x = linspace(0, 10, 1000);
    std::vector<double> y = transform(x, [](auto x) { return cos(2 * x); });
    plot(x, y)->color({0.f, 0.7f, 0.9f});
    title("2-D Line Plot");
    xlabel("x");
    ylabel("cos(2x)");
    ylim({-2, +2});
    show();
}
void puls(){
    using namespace matplot;

    std::vector<double> x = linspace(0, 10, 1000);
    std::vector<double> y = transform(x, [](auto x) { return sin(2 * x) > 0 ? 1.0 : 0.0; });
    plot(x, y)->color({0.f, 0.7f, 0.9f});
    title("2-D Line Plot");
    xlabel("x");
    ylabel("puls(2x)");
    ylim({-2, +2});
    show();
}

namespace py = pybind11;

PYBIND11_MODULE(_core, m) {
    m.def("sin",&sin);
    m.def("cos",&cos);
    m.def("puls",&puls);

#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}
