#ifndef STRUKTURA_H_INCLUDED
#define STRUKTURA_H_INCLUDED

#include <string>
#include <vector>

struct Duomenys {
    std::string vardas;
    std::string pavarde;
    std::vector<double> nd;
    double eg;
    double ndvid;
    double galutinis;
    double mediana;
};

double median(const std::vector<double>& arr);
void generuotiBalus(std::vector<double>& nd_rezultatai, double& eg);
void atspausdintiDuomenis(const std::vector<Duomenys>& A, bool iFaila = false);
void rikiuotiPagalVarda(std::vector<Duomenys>& A);
void rikiuotiPagalPavarde(std::vector<Duomenys>& A);
void rikiuotiPagalGalutiniVidurki(std::vector<Duomenys>& A);
void rikiuotiPagalMediana(std::vector<Duomenys>& A);
void skaitytiIsFailo(std::vector<Duomenys>& A, const std::string& failoPavadinimas);

#endif // STRUKTURA_H_INCLUDED
