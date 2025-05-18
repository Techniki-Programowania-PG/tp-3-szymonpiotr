#define _USE_MATH_DEFINES
#include <pybind11/pybind11.h>
#include <matplot/matplot.h>
#include <cmath>
#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

int add(int i, int j) {
    return i + j;
}

 //dodać lepsze napisy na wykresie, moze kolor tła

 // nwm czy nawet tego użycwać
void sin_dyskretyny(){
    using namespace matplot;

    std::vector<double> x = linspace(0, 10, 10);
    std::vector<double> y = transform(x, [](auto x) { return sin(2 * x); });

    stem(x, y)->color({0.f, 0.7f, 0.9f});
    title("Dyskretny wykres sin(2x)");
    xlabel("x");
    ylabel("sin(2x)");
    ylim({-2, +2});
    show();
}

void sinus(double start, double koniec, int probki, double czestoliwosc){
    using namespace matplot;

    std::vector<double> x = linspace(start*M_PI, koniec*M_PI, probki);
    std::vector<double> y = transform(x, [czestoliwosc](auto x) { return sin(2 * czestoliwosc * x); });
    

    plot(x, y)->color({0.f, 0.9f, 0.f});
    
    
    ylim({-2, +2});
    
    title("Wykres sygnału sinusoidalnego o podanej czestoliwosci");
    xlabel("x");
    ylabel("sin(2πfx)");
    show();
}

void cosinus(double start, double koniec, int probki, double czestoliwosc){
    using namespace matplot;

    std::vector<double> x = linspace(start, koniec, probki);
    std::vector<double> y = transform(x, [czestoliwosc](auto x) { return cos(2 * M_PI * czestoliwosc * x); });
    
    plot(x, y)->color({0.f, 0.9f, 0.f});
    
    ylim({-2, +2});

    title("Wykres sygnału sinusoidalnego o podanej czestoliwosci");
    xlabel("x");
    ylabel("cos(2πfx)");
    show();
}

void puls(double start, double koniec, int probki, double czestoliwosc){
    using namespace matplot;

    std::vector<double> x = linspace(start, koniec, probki);
    std::vector<double> y = transform(x, [czestoliwosc](auto x) { return sin(2 * M_PI * czestoliwosc * x) > 0 ? 1.0 : 0.0; });
    
    plot(x, y)->color({0.f, 0.9f, 0.f});
    
    ylim({-2, +2});
    
    title("Wykres sygnału prostokątengo o podanej czestotliwosci");
    xlabel("x");
    ylabel("puls(2πfx)");
    show();
}

void pila(double start, double koniec, int probki, double czestoliwosc){
    using namespace matplot;

    std::vector<double>  x = linspace(start, koniec, probki);
    std::vector<double> y = transform(x, [czestoliwosc](auto x) { return  2*(fmod(czestoliwosc*x, 1.0)) - 1;  });
    
    plot(x, y)->color({0.f, 0.9f, 0.f});
    
    ylim({-2, +2});
    
    title("Wykres piłowy o podanej czestoliwsoci");
    xlabel("x");
    ylabel("pila");
    show();
}



namespace py = pybind11;

PYBIND11_MODULE(_core, m) {
    m.def("sin_dyskretyny",&sin_dyskretyny);
    m.def("sinus", &sinus);
    m.def("cosinus",&cosinus);
    m.def("puls",&puls);
    m.def("pila",&pila);

#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}
