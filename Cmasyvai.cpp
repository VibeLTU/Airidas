#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
using namespace std;

struct duomenys {
    string vardas;
    string pavarde;
    double *nd; // namu darbu rezultatai (C-stiliaus masyvas)
    int nd_sk; // kiekis namu darbu rezultatu
    double eg; // egzamino rezultatai
    double ndvid; // namu darbu vidurkis
    double galutinis; // bendras vidurkis
    double mediana; // mediana
};

// Funkcija, kuri skaičiuoja medianą
double median(double arr[], int size) {
    sort(arr, arr + size);
    if (size % 2 == 0) {
        return (arr[size / 2 - 1] + arr[size / 2]) / 2.0;
    }
    else {
        return arr[size / 2];
    }
}

int main() {
    int m = 0; // Pradinis studentų skaičius
    duomenys *A = nullptr; // Pradinis masyvas studentams

    while (true) {
        cout << "Iveskite varda (arba 'x', jei norite baigti): ";
        string vardas;
        cin >> vardas;
        if (vardas == "x") // Tikriname, ar įvestas pabaigos ženklas
            break;

        cout << "Iveskite pavarde: ";
        string pavarde;
        cin >> pavarde;

        // Įrašome namų darbų rezultatus
        cout << "Iveskite namu darbu rezultatus (baigti -1): ";
        double *nd_rezultatai = new double[50]; // Dinaminis masyvas namu darbu rezultatams
        int nd_sk = 0;
        double pazymys;
        while (cin >> pazymys && pazymys != -1) {
            nd_rezultatai[nd_sk++] = pazymys;
        }

        duomenys naujas;
        naujas.vardas = vardas;
        naujas.pavarde = pavarde;
        naujas.nd = new double[nd_sk]; // Priskiriame dinaminį masyvą namų darbų rezultatams
        naujas.nd_sk = nd_sk; // Saugome kiekį namų darbų rezultatų
        naujas.ndvid = 0; // Inicializuojame namų darbų vidurkį prieš pradedant skaičiavimus
        for (int j = 0; j < nd_sk; j++) {
            naujas.nd[j] = nd_rezultatai[j];
            naujas.ndvid += nd_rezultatai[j];
        }
        naujas.ndvid /= nd_sk; // Skaičiuojame namų darbų vidurkį

        delete[] nd_rezultatai; // Atlaisviname laikiną dinaminį masyvą

        cout << "Iveskite egzamino rezultatus: ";
        cin >> naujas.eg;

        // Skaičiuojame medianą iš visų rezultatų
        double *visiRezultatai = new double[nd_sk + 1]; // Visų rezultatų masyvas
        for (int j = 0; j < nd_sk; j++) {
            visiRezultatai[j] = naujas.nd[j];
        }
        visiRezultatai[nd_sk] = naujas.eg;
        naujas.mediana = median(visiRezultatai, nd_sk + 1);
        delete[] visiRezultatai; // Atlaisviname laikiną dinaminį masyvą

        // Skaičiuojame galutinį rezultatą
        naujas.galutinis = 0.4 * naujas.ndvid + 0.6 * naujas.eg;

        // Praplečiame masyvą nauju elementu
        duomenys *temp = new duomenys[m + 1];
        for (int i = 0; i < m; i++)
            temp[i] = A[i];
        temp[m] = naujas;

        delete[] A; // Atlaisviname seną masyvą
        A = temp; // Perkeliame naują masyvą į rodyklę

        m++; // Padidiname studentų skaičių
    }

    cout << "Vardas" << "         " << "Pavarde" << "        " << "Galutinis (Vid.)" << "        " << "Galutinis (Med.)" << endl;
    cout << "------------------------------------------------------------------------" << endl;
    for (int i = 0; i < m; i++) {
        cout << left << setw(15) << A[i].vardas << left << setw(15) << A[i].pavarde << left << setw(15) << setprecision(3) << A[i].galutinis << left << setw(15) << setprecision(3) << A[i].mediana << endl;
    }

    // Atlaisviname dinaminį masyvą
    for (int i = 0; i < m; i++) {
        delete[] A[i].nd;
    }
    delete[] A;

    return 0;
}
