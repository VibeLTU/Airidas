#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <fstream>
using namespace std;

struct duomenys {
    string vardas;
    string pavarde;
    vector<double> nd; // namu darbu rezultatai
    double eg; // egzamino rezultatas
    double ndvid; // namu darbu vidurkis
    double galutinis; // bendras vidurkis
    double mediana; // mediana
};

double median(vector<double>& arr) {
    sort(arr.begin(), arr.end());
    int size = arr.size();
    if (size % 2 == 0) {
        return (arr[size / 2 - 1] + arr[size / 2]) / 2.0;
    }
    else {
        return arr[size / 2];
    }
}

void ivedimas(vector<duomenys>& studentai) {
    int n;
    string baigti;
    while (true) {
        duomenys stud;
        double ndrez;
        cout << "Iveskite varda (jei norite baigti ivedima, iveskite 'x'): ";
        cin >> stud.vardas;
        if (stud.vardas == "x") break;
        cout << "Iveskite pavarde: ";
        cin >> stud.pavarde;
        cout << "Iveskite namu darbo rezultatus (jei norite baigti ivedima, iveskite 'x'): ";
        while (true) {
            cin >> baigti;
            if (baigti == "x") break;
            ndrez = stod(baigti);
            stud.nd.push_back(ndrez);
            stud.ndvid += ndrez;
        }
        int nd_skaicius = stud.nd.size();
        if (nd_skaicius == 0) {
            cout << "Namu darbu rezultatu nepateikta. Iveskite bent viena rezultata." << endl;
            continue;
        }
        stud.ndvid /= nd_skaicius;
        cout << "Iveskite egzamino rezultata: ";
        cin >> stud.eg;
        vector<double> visiRezultatai = stud.nd;
        visiRezultatai.push_back(stud.eg);

        // Skaičiuojame medianą iš visų rezultatų
        stud.mediana = median(visiRezultatai);
        stud.galutinis = 0.4 * stud.ndvid + 0.6 * stud.eg;

        studentai.push_back(stud);
    }
}

void isvedimas(vector<duomenys>& studentai) {
    cout << "Vardas" << "         " << "Pavarde" << "        " << "Galutinis (Vid.)" << "        " << "Galutinis (Med.)" << endl;
    cout << "------------------------------------------------------------------------" << endl;
    for (const auto& stud : studentai) {
        cout << left << setw(15) << stud.vardas << left << setw(15) << stud.pavarde << left << setw(15) << setprecision(3) << stud.galutinis << left << setw(15) << setprecision(3) << stud.mediana << endl;
    }
}

int main() {
    vector<duomenys> studentai;
    ivedimas(studentai);
    isvedimas(studentai);
    return 0;
}

