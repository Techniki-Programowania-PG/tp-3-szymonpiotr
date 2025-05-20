
import scikit_build_example as test

sygnal = test.sinus(0, 8, 1000, 5)
test.SygnalD2(sygnal[0], sygnal[1], "Czas", "Amplituda", "Sinus")
test.SygnalD1(sygnal[1], "Probka", "Amplituda", "Sinus")


