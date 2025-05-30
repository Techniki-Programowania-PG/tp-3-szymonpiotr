import scikit_build_example as funkcja
import numpy as np

t = np.linspace(0, 16*np.pi, 1000)
sygnal = np.sin(t) + 0.1*np.random.randn(1000)

funkcja.SygnalD1(sygnal, "Probka", "Amplituda", "Sinus zaszumiony","Sinus_zaszumiony_1D.png")

Filtr=funkcja.FiltracjaD1(sygnal)

funkcja.SygnalD1(Filtr, "Probka", "Amplituda", "Sinus odszumiony","Sinus_odszumiony_1D.png")

#(Początek, koniec, ilość próbek, częstotliwość)
sygnal=funkcja.sinus(0,8,1000,1) 

#(Wartości y, nazwa OSX, nazwa OSY. nazwa wykresu, nazwa pliku )
funkcja.SygnalD1(sygnal[1],"Próbka","Amplituda","Sinus o f=1Hz","Sinus_f=1_1D.png")

#(Wartości x, wartości y, nazwa OSX, nazwa OSY. nazwa wykresu, nazwa pliku )
funkcja.SygnalD2(sygnal[0],sygnal[1],"Czas","Amplituda","Sinus o f=1Hz","Sinus_f=1_2D.png")

sygnal=funkcja.sinus(0,8,1000,10) 

funkcja.SygnalD1(sygnal[1],"Próbka","Amplituda","Sinus o f=10Hz","Sinus_f=10_1D.png")

#(Początek, koniec, ilość próbek, częstotliwość)
sygnal=funkcja.cosinus(0,8,1000,1) 

#(Wartości y, nazwa OSX, nazwa OSY. nazwa wykresu, nazwa pliku )
funkcja.SygnalD1(sygnal[1],"Próbka","Amplituda","Cosinus o f=1Hz","Cosinus_f=1_1D.png")

#(Wartości x, wartości y, nazwa OSX, nazwa OSY. nazwa wykresu, nazwa pliku )
funkcja.SygnalD2(sygnal[0],sygnal[1],"Czas","Amplituda","Cosinus o f=1Hz","Cosinus_f=1_2D.png")

sygnal=funkcja.cosinus(0,8,1000,5) 

funkcja.SygnalD1(sygnal[1],"Próbka","Amplituda","Cosinus o f=5Hz","Cosinus_f=5_1D.png")

#(Początek, koniec, ilość próbek, częstotliwość)
sygnal=funkcja.pila(0,8,1000,1) 

#(Wartości y, nazwa OSX, nazwa OSY. nazwa wykresu, nazwa pliku )
funkcja.SygnalD1(sygnal[1],"Próbka","Amplituda","Piłokształtny o f=1Hz","Pila_f=1_1D.png")

#(Wartości x, wartości y, nazwa OSX, nazwa OSY. nazwa wykresu, nazwa pliku )
funkcja.SygnalD2(sygnal[0],sygnal[1],"Czas","Amplituda","Piłokształtny o f=1Hz","Pila_f=1_2D.png")

sygnal=funkcja.pila(0,8,1000,7) 

funkcja.SygnalD1(sygnal[1],"Próbka","Amplituda","Piłokształtny o f=7Hz","Pila_f=7_1D.png")

#(Początek, koniec, ilość próbek, częstotliwość)
sygnal=funkcja.prostokatny(0,8,1000,1) 

#(Wartości y, nazwa OSX, nazwa OSY. nazwa wykresu, nazwa pliku )
funkcja.SygnalD1(sygnal[1],"Próbka","Amplituda","Prostokątna o f=1Hz","Prost_f=1_1D.png")

#(Wartości x, wartości y, nazwa OSX, nazwa OSY. nazwa wykresu, nazwa pliku )
funkcja.SygnalD2(sygnal[0],sygnal[1],"Czas","Amplituda","Piła o f=1Hz","Prost_f=1_2D.png")

sygnal=funkcja.prostokatny(0,8,1000,3) 

funkcja.SygnalD1(sygnal[1],"Próbka","Amplituda","Prostokątna o f=3Hz","Prost_f=3_1D.png")

#(Początek, koniec, ilość próbek, częstotliwość)
sygnal=funkcja.sinus(0,8,1000,15) 

#Wyświetlenie funkcji sinus
funkcja.SygnalD1(sygnal[1],"Próbka","Amplituda","Sinus o f=15Hz","Sinus_f=15_1D.png")

#DFT
wynik=funkcja.DFT(sygnal[1])

#Wykres DFT (wynik DFT, czestoliowsc próbkowania: (ilosc próbek)/(Koniec - start), nazwa pliku wykresu)
funkcja.WidmoDFT(wynik,125, "Dft_sinus_f=15.png")

#Powrót do orginalnej funkcji (IDFT)
orginal=funkcja.IDFT(wynik)

#Wyświetlenie orginału po powrocie
funkcja.SygnalD1(orginal,"Próbka","Amplituda","Orginalna funkcja","Orginal_1D.png")

t = np.linspace(0, 16*np.pi, 1000)
sygnal = np.sin(t) + 0.1*np.random.randn(1000)

funkcja.SygnalD1(sygnal, "Probka", "Amplituda", "Sinus zaszumiony","Sinus_zaszumiony_1D.png")

Filtr=funkcja.FiltracjaD1(sygnal)

funkcja.SygnalD1(Filtr, "Probka", "Amplituda", "Sinus odszumiony","Sinus_odszumiony_1D.png")

#(Początek, koniec, ilość próbek, częstotliwość)
sygnal=funkcja.sinus(0,8,1000,1) 

#(Wartości x, wartości y, nazwa OSX, nazwa OSY. nazwa wykresu, nazwa pliku )
funkcja.SygnalD2(sygnal[0],sygnal[1],"Czas","Amplituda","Sinus o f=1Hz","Sinusauto_f=1_2D.png")

#Autokorelacja syngału sinus (wartości y, cześtolitowść próbkowania (ilość próbek)/(koniec-start))
wynik=funkcja.Autokorelcja_sygnalu(sygnal[1],125)

#Wyświetlenie autokorelacji na wykresie 2D
funkcja.SygnalD2(wynik[0],wynik[1],"Opóźnienie","Autokorelacja","Autokorelacja sygnału","auto_2D.png")