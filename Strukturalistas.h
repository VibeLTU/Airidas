#ifndef STRUKTURA_H_INCLUDED
#define STRUKTURA_H_INCLUDED

#include <string>
#include <list>

struct Duomenys {
    std::string vardas;
    std::string pavarde;
    std::list<double> nd;
    double eg;
    double ndvid;
    double galutinis;
    double mediana;
};

double median(const std::list<double>& arr);
void generuotiBalus(std::list<double>& nd_rezultatai, double& eg);
void atspausdintiDuomenis(const std::list<Duomenys>& A, bool iFaila = false);
void rikiuotiPagalVarda(std::list<Duomenys>& A);
void rikiuotiPagalPavarde(std::list<Duomenys>& A);
void rikiuotiPagalGalutiniVidurki(std::list<Duomenys>& A);
void rikiuotiPagalMediana(std::list<Duomenys>& A);
void skaitytiIsFailo(std::list<Duomenys>& A, const std::string& failoPavadinimas);
void generuotiFailaSuStudentais(int irasu_skaicius);
void rikiuotiStudentus(std::list<Duomenys>& geri_studentai, std::list<Duomenys>& blogi_studentai);

#endif // STRUKTURA_H_INCLUDED
