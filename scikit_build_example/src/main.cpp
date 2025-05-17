#include <pybind11/pybind11.h>
#include <matplot/matplot.h>
#include <cmath>
#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

int add(int i, int j) {
    return i + j;
}

void sin_dyskretyny(){
    using namespace matplot;

    // Tylko 10 próbek na osi x
    std::vector<double> x = linspace(0, 10, 10);
    std::vector<double> y = transform(x, [](auto x) { return sin(2 * x); });

    // Wykres punktowy zamiast liniowego, dla podkreślenia dyskretności
    stem(x, y)->color({0.f, 0.7f, 0.9f});
    title("Dyskretny wykres sin(2x)");
    xlabel("x");
    ylabel("sin(2x)");
    ylim({-2, +2});
    show();
}

void sin(){
    using namespace matplot;

    std::vector<double> x = linspace(0, 10, 10);
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
void pila(){
    using namespace matplot;

    std::vector<double>  x = linspace(0, 10, 1000);
    std::vector<double> y = transform(x, [](auto x) { return  2 * (fmod(x, 1.0)) - 1;  });
    plot(x, y)->color({0.f, 0.7f, 0.9f});
    title("2-D Line Plot");
    xlabel("x");
    ylabel("pila");
    ylim({-2, +2});
    show();
}



namespace py = pybind11;

PYBIND11_MODULE(_core, m) {
    m.def("sin_dyskretyny",&sin_dyskretyny);
    m.def("sin",&sin);
    m.def("cos",&cos);
    m.def("puls",&puls);
    m.def("pila",&pila);

#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}
