#define _USE_MATH_DEFINES
#include <pybind11/pybind11.h>
#include <matplot/matplot.h>
#include <cmath>
#include <pybind11/stl.h> 
#include <pybind11/complex.h>
#include <string>
#include <complex>
#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

int add(int i, int j) {
    return i + j;
}

 //dodać lepsze napisy na wykresie, moze kolor tła

void SygnalD2(const std::vector<double>& wartoscX, const std::vector<double>& wartoscY, const std::string& OSX, const std::string& OSY, const std::string& tytul) {
     using namespace matplot;

    plot(wartoscX, wartoscY)->color({0.f, 0.9f, 0.f});
    ylim({-2, +2}); 
    grid(on);
    title(tytul);
    xlabel(OSX);
    ylabel(OSY);
    show();
}
void SygnalD1(const std::vector<double>& wartoscY, const std::string& OSX, const std::string& OSY, const std::string& tytul){
     using namespace matplot;

    std::vector<double> wartoscX(wartoscY.size());
    for (size_t i=0; i<wartoscY.size(); i++)
    {
        wartoscX[i] = static_cast<double>(i);
    }


    plot(wartoscX, wartoscY)->color({0.f, 0.9f, 0.f});
    ylim({-2, +2}); 
    grid(on);
    title(tytul);
    xlabel(OSX);
    ylabel(OSY);
    show();
}

 std::vector<std::vector<double>> sinus(double start, double koniec, int probki, double czestoliwosc) {
    using namespace matplot;
    std::vector<std::vector<double>> sygnal(2);

    std::vector<double> x = linspace(start, koniec, probki);
    std::vector<double> y = transform(x, [czestoliwosc](auto x) { 
        return sin(2 * M_PI * czestoliwosc * x); 
    });
    
    sygnal[0] = x;
    sygnal[1] = y;

    return sygnal;
}

std::vector<std::vector<double>> cosinus(double start, double koniec, int probki, double czestoliwosc) {
    using namespace matplot;
    std::vector<std::vector<double>> sygnal(2);

    std::vector<double> x = linspace(start, koniec, probki);
    std::vector<double> y = transform(x, [czestoliwosc](auto x) { 
        return cos(2 * M_PI * czestoliwosc * x); 
    });

    sygnal[0] = x;
    sygnal[1] = y;

    return sygnal;
}

std::vector<std::vector<double>> puls(double start, double koniec, int probki, double czestoliwosc) {
    using namespace matplot;
    std::vector<std::vector<double>> sygnal(2);

    std::vector<double> x = linspace(start, koniec, probki);
    std::vector<double> y = transform(x, [czestoliwosc](auto x) { 
        return sin(2 * M_PI * czestoliwosc * x) > 0 ? 1.0 : -1.0; 
    });

    sygnal[0] = x;
    sygnal[1] = y;

    return sygnal;
}

std::vector<std::vector<double>> pila(double start, double koniec, int probki, double czestoliwosc) {
    using namespace matplot;
    std::vector<std::vector<double>> sygnal(2);

    std::vector<double> x = linspace(start, koniec, probki);
    std::vector<double> y = transform(x, [czestoliwosc](auto x) { 
        return 2 * (fmod(czestoliwosc * x, 1.0)) - 1; 
    });

    sygnal[0] = x;
    sygnal[1] = y;

    return sygnal;
}

//DFT

std::vector<std::complex<double>> DFT(const std::vector<double>& wartoscY) {
    int N = wartoscY.size();
    std::vector<std::complex<double>> X(N);
    
    for(int i = 0; i < N; i++) 
    {
        X[i] = std::complex<double>(0.0, 0.0);
        for(int k = 0; k < N; k++) 
        {
            double kat = -2 * M_PI * k * i / N;
            X[i] += wartoscY[k] * std::complex<double>(cos(kat), sin(kat));
        }
    }
    return X;
}

void WidmoDFT(const std::vector<std::complex<double>>& dft_wynik, double czestotliwosc_probkowania) {
    using namespace matplot;

    int N = dft_wynik.size();
    std::vector<double> amplitudy(N);
    std::vector<double> czestotliwosci(N);

    for (int k = 0; k < N; ++k) {
       
        int przesuniecie = (k + N / 2) % N;
        czestotliwosci[k] = (k - N / 2) * czestotliwosc_probkowania / N;
        amplitudy[k] = std::abs(dft_wynik[przesuniecie]) / N;  
    }

    plot(czestotliwosci, amplitudy)->color({0.f, 0.9f, 0.f});
    xlabel("Częstotliwość [Hz]");
    ylabel("Amplituda");
    title("Centrowane widmo amplitudowe DFT");
    grid(on);
    show();
}

std::vector<double> IDFT(const std::vector<std::complex<double>>& DFT) {
    int N = DFT.size();
    std::vector<double> sygnal_z_DFT(N);

    for (int n = 0; n < N; ++n) {
        std::complex<double> suma(0.0, 0.0);
        for (int k = 0; k < N; ++k) {
            double kat = 2 * M_PI * k * n / N;
            suma += DFT[k] * std::complex<double>(cos(kat), sin(kat));
        }
        sygnal_z_DFT[n] = suma.real() / N;  
    }
    return sygnal_z_DFT;
}

namespace py = pybind11;

PYBIND11_MODULE(_core, m) {
    m.def("DFT",&DFT);
    m.def("WidmoDFT",&WidmoDFT);
    m.def("SygnalD1", &SygnalD1);
    m.def("SygnalD2", &SygnalD2);
    m.def("sinus", &sinus);
    m.def("cosinus",&cosinus);
    m.def("puls",&puls);
    m.def("pila",&pila);
    m.def("IDFT", &IDFT); 
    // m.def("FiltracjaD1",&FiltracjaD1);

#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}
