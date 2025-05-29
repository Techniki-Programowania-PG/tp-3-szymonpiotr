
import scikit_build_example as test
import numpy as np

t = np.linspace(0, 16*np.pi, 1000)
sygnal = np.sin(t) + 0.1*np.random.randn(1000)
test.SygnalD1(sygnal, "Probka", "Amplituda", "Sinus zaszumiony")
Filtr=test.FiltracjaD1(sygnal)
test.SygnalD1(Filtr, "Probka", "Amplituda", "Sinus odszumiony")



"""
sygnal = test.sinus(0, 8, 1000, 1)
test.SygnalD2(sygnal[0], sygnal[1], "Czas", "Amplituda", "Sinus")
test.SygnalD1(sygnal[1], "Probka", "Amplituda", "Sinus")

dft_wynik = test.DFT(sygnal[1])
test.WidmoDFT(dft_wynik, 125)

sygnal_pierwotny = test.IDFT(dft_wynik)
test.SygnalD1(sygnal_pierwotny, "Probka", "Amplituda", "Odtworzony sygnał (IDFT)")

Filtr=test.FiltracjaD1(sygnal[1])
test.SygnalD1(Filtr, "Probka", "Amplituda", "Sinus od szumiony")
"""