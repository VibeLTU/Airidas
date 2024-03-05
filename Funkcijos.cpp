#include "Struktura.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <chrono>
#include <iomanip>
#include <random>
using namespace std;

double median(const vector<double>& arr) {
    vector<double> temp = arr;
    sort(temp.begin(), temp.end());
    int size = temp.size();
    if (size % 2 == 0) {
        return (temp[size / 2 - 1] + temp[size / 2]) / 2.0;
    } else {
        return temp[size / 2];
    }
}

void generuotiBalus(vector<double>& nd_rezultatai, double& eg) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> nd_distribution(1, 10);
    uniform_int_distribution<> eg_distribution(1, 10);

    for (size_t i = 0; i < nd_rezultatai.size(); ++i) {
        nd_rezultatai[i] = nd_distribution(gen);
    }
    eg = eg_distribution(gen);
}

void atspausdintiDuomenis(const vector<Duomenys>& A, bool iFaila) {
    if (iFaila) {
        ofstream out("Isvedimas.txt");
        out << "Vardas" << "         " << "Pavarde" << "        " << "Galutinis (Vid.)" << "        " << "Galutinis (Med.)" << endl;
        out << "------------------------------------------------------------------------" << endl;
        for (const auto& studentas : A) {
            out << left << setw(15) << studentas.vardas << left << setw(15) << studentas.pavarde << left << setw(15) << setprecision(3) << studentas.galutinis <<  "         " << left << setw(15) << setprecision(3) <<  studentas.mediana << endl;
        }
        out.close();
        cout << "Duomenys irasyti i faila 'Isvedimas.txt'" << endl;
    } else {
        cout << "Vardas" << "         " << "Pavarde" << "        " << "Galutinis (Vid.)" << "        " << "Galutinis (Med.)" << endl;
        cout << "------------------------------------------------------------------------" << endl;
        for (const auto& studentas : A) {
            cout << left << setw(15) << studentas.vardas << left << setw(15) << studentas.pavarde << left << setw(15) << setprecision(3) << studentas.galutinis <<  "         " << left << setw(15) << setprecision(3) <<  studentas.mediana << endl;
        }
    }
}

void rikiuotiPagalVarda(vector<Duomenys>& A) {
    sort(A.begin(), A.end(), [](const Duomenys& a, const Duomenys& b) {
        return a.vardas < b.vardas;
    });
}

void rikiuotiPagalPavarde(vector<Duomenys>& A) {
    sort(A.begin(), A.end(), [](const Duomenys& a, const Duomenys& b) {
        return a.pavarde < b.pavarde;
    });
}

void rikiuotiPagalGalutiniVidurki(vector<Duomenys>& A) {
    sort(A.begin(), A.end(), [](const Duomenys& a, const Duomenys& b) {
        return a.galutinis < b.galutinis;
    });
}

void rikiuotiPagalMediana(vector<Duomenys>& A) {
    sort(A.begin(), A.end(), [](const Duomenys& a, const Duomenys& b) {
        return a.mediana < b.mediana;
    });
}

void skaitytiIsFailo(vector<Duomenys>& A, const string& failoPavadinimas) {
    ifstream failas(failoPavadinimas);
    if (!failas.is_open()) {
        cout << "Klaida: Nepavyko atidaryti failo " << failoPavadinimas << endl;
        return;
    }

    auto start = chrono::high_resolution_clock::now(); // funkcijos pradzioj
    string eilute;
    getline(failas, eilute); // Praleisti pirma eilute
    while (getline(failas, eilute)) {
        istringstream eilutesSrautas(eilute);
        Duomenys naujas;
        eilutesSrautas >> naujas.vardas >> naujas.pavarde;
        double pazymys;
        while (eilutesSrautas >> pazymys) {
            naujas.nd.push_back(pazymys);
        }
        if (!naujas.nd.empty()) {
            naujas.eg = naujas.nd.back();
            naujas.nd.pop_back();
        }
        naujas.ndvid = accumulate(naujas.nd.begin(), naujas.nd.end(), 0.0) / naujas.nd.size();
        vector<double> visiRezultatai = naujas.nd;
        visiRezultatai.push_back(naujas.eg);
        naujas.mediana = median(visiRezultatai);
        naujas.galutinis = 0.4 * naujas.ndvid + 0.6 * naujas.eg;
        A.push_back(naujas);
    }
    cout << "Nuskaitymas uztruko " << (chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count())/1000.0 << " s\n"; // funkcijos pabaigoj
    failas.close();
}

void generuotiFailaSuStudentais(int irasu_skaicius) {
    ofstream failas;
    string failo_pavadinimas = "Studentai_" + to_string(irasu_skaicius) + ".txt";
    failas.open(failo_pavadinimas);

    if (!failas.is_open()) {
        cout << "Klaida: Nepavyko sukurti failo " << failo_pavadinimas << endl;
        return;
    }

    failas << "Vardas              Pavarde             ND1       ND2       ND3       ND4       ND5       ND6       ND7       ND8       ND9      ND10      ND11      ND12      ND13      ND14      ND15      Egz." << endl;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> nd_distribution(1, 10);
    uniform_int_distribution<> eg_distribution(1, 10);

for (int i = 0; i < irasu_skaicius; ++i) {
    failas << setw(20) << left << ("Vardas" + to_string(i + 1)) << setw(20) << left << ("Pavarde" + to_string(i + 1));
    for (int j = 0; j < 15; ++j) {
        failas << setw(10) << left << nd_distribution(gen);
    }
    failas << setw(10) << left << eg_distribution(gen) << endl;
}

    failas.close();
    cout << "Failas " << failo_pavadinimas << " sukurtas sekmingai." << endl;
}

