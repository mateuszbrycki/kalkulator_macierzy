Kalkulator macierzy 1.0
Autorzy: Mateusz Brycki, Mateusz Bryzik.

Program napisany w C++/Qt realizujący działania na macierzach podanych przez użytkownika. Dodatkowo program jest wyposażony w tryb ćwiczeń, dzięki którym użytkownik może utrwalić nabyte umiejętności. Aplikacja jest projektem wykonanym w dwuosobowej grupie na potrzeby przedmiotu Metody Obliczeniowe.
Obecnie wymaga kilku poprawek m.in. przerobienie klasy Equation tak aby nie powodowała wycieków pamięci (tworzone są obiekty "C" - macierz wynikowa, a następnie zwracane - brak użycia operatora delete) oraz konstruktor kopiujący w klasie Matrix.
