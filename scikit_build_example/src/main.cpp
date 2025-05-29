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
    xlim({0, 1000}); 
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

std::vector<std::vector<double>> prostokatny(double start, double koniec, int probki, double czestoliwosc) {
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
    int polowa = N / 2;

    std::vector<double> energia(polowa);
    std::vector<double> czestotliwosci(polowa);

    for (int k = 0; k < polowa; ++k) {
        czestotliwosci[k] = static_cast<double>(k) * czestotliwosc_probkowania / N;
        energia[k] = std::norm(dft_wynik[k]);  
    }

    auto p = plot(czestotliwosci, energia);
    p->color({1.f, 0.2f, 0.f});
    xlabel("Częstotliwość [Hz]");
    ylabel("Energia");
    title("Widmo energetyczne sygnału (DFT)");
    grid(on);

    xlim({0, czestotliwosc_probkowania / 2});
    ylim({0, *std::max_element(energia.begin(), energia.end()) * 1.05});

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

std::vector<std::vector<double>> Autokorelcja_sygnalu(const std::vector<double>& sygnal, double czestotliwosc_probkowania) {
    int N = sygnal.size();
    std::vector<double> lagi;
    std::vector<double> wartosci;

    for (int lag = -(N - 1); lag < N; ++lag) {
        double suma = 0.0;
        int start = std::max(0, -lag);
        int end = std::min(N, N - lag);
        for (int i = start; i < end; ++i) {
            suma += sygnal[i] * sygnal[i + lag];
        }
        lagi.push_back(static_cast<double>(lag) / czestotliwosc_probkowania);  
        wartosci.push_back(suma / N);
    }

    std::vector<std::vector<double>> wynik(2);
    wynik[0] = lagi;
    wynik[1] = wartosci;

    return wynik;
}

std::vector<double> FiltracjaD1(const std::vector<double>& sygnal) {
    
    const int N = 5; 
    std::vector<double> filtr(sygnal.size(), 0.0);

    for (size_t i = 0; i < sygnal.size(); ++i) {
        double suma = 0.0;
        int licznik = 0;
        
        
        for (int j = static_cast<int>(i) - N/2; j <= static_cast<int>(i) + N/2; ++j) {
            if (j >= 0 && j < static_cast<int>(sygnal.size())) {
                suma += sygnal[j];
                licznik++;
            }
        }
        filtr[i] = (licznik > 0) ? suma / licznik : 0.0;
    }

    return filtr;
}

namespace py = pybind11;

PYBIND11_MODULE(_core, m) {
    m.def("DFT",&DFT);
    m.def("WidmoDFT",&WidmoDFT);
    m.def("SygnalD1", &SygnalD1);
    m.def("SygnalD2", &SygnalD2);
    m.def("sinus", &sinus);
    m.def("cosinus",&cosinus);
    m.def("prostokatny",&prostokatny);
    m.def("pila",&pila);
    m.def("FiltracjaD1", &FiltracjaD1);
    m.def("Autokorelcja_sygnalu",&Autokorelcja_sygnalu);
    m.def("IDFT", &IDFT); 
    
    
#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}
