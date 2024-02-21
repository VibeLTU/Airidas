#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <random>
#include <fstream>
#include <chrono>

using namespace std;

struct duomenys {
    string vardas;
    string pavarde;
    vector<double> nd;
    double eg;
    double ndvid;
    double galutinis;
    double mediana;
};

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

void atspausdintiDuomenis(const vector<duomenys>& A, bool iFaila = false) {
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

void rikiuotiPagalVarda(vector<duomenys>& A) {
    sort(A.begin(), A.end(), [](const duomenys& a, const duomenys& b) {
        return a.vardas < b.vardas;
    });
}

void rikiuotiPagalPavarde(vector<duomenys>& A) {
    sort(A.begin(), A.end(), [](const duomenys& a, const duomenys& b) {
        return a.pavarde < b.pavarde;
    });
}

void rikiuotiPagalGalutiniVidurki(vector<duomenys>& A) {
    sort(A.begin(), A.end(), [](const duomenys& a, const duomenys& b) {
        return a.galutinis < b.galutinis;
    });
}

void rikiuotiPagalMediana(vector<duomenys>& A) {
    sort(A.begin(), A.end(), [](const duomenys& a, const duomenys& b) {
        return a.mediana < b.mediana;
    });
}

void skaitytiIsFailo(vector<duomenys>& A, const string& failoPavadinimas) {
    ifstream failas(failoPavadinimas);
    if (!failas.is_open()) {
        cout << "Klaida: Nepavyko atidaryti failo " << failoPavadinimas << endl;
        return;
    }

    auto start = std::chrono::high_resolution_clock::now(); //funkcijos pradzioj
    string eilute;
    getline(failas, eilute); // Praleisti pirmąją eilutę
    while (getline(failas, eilute)) {
        istringstream eilutesSrautas(eilute);
        duomenys naujas;
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
    std::cout << "Nuskaitymas uztruko " << (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count())/1000.0 << " s\n"; //funkcijos pabaigoj
    failas.close();
}

int main() {
    int choice;
    vector<duomenys> A;

    while (true) {
        cout << "Pasirinkite veiksma: " << endl;
        cout << "1. Ivesti duomenis ranka" << endl;
        cout << "2. Generuoti pazymius" << endl;
        cout << "3. Generuoti pazymius ir studentu vardus, pavardes" << endl;
        cout << "4. Nuskaityti duomenis is failo" << endl;
        cout << "5. Rikiuoti duomenis" << endl;
        cout << "6. Isvesti duomenis" << endl;
        cout << "7. Baigti darba" << endl;
        cout << "Jusu pasirinkimas: ";
        cin >> choice;

        if (cin.fail()) {
            cout << "Klaida: Netinkamas pasirinkimas. Prasome ivesti skaiciu nuo 1 iki 7." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (choice == 1) {
            duomenys naujas;
            cout << "Iveskite varda: ";
            cin >> naujas.vardas;
            cout << "Iveskite pavarde: ";
            cin >> naujas.pavarde;
            cout << "Iveskite kiek namu darbu rezultatu norite suvesti: ";
            int nd_sk;
            for (int i = 0; i < 1; ++i) {
                cin >> nd_sk;
                if (nd_sk < 1 || cin.fail()) {
                    cout << "Klaida: Ivestas netinkamas skaicius. Prasome ivesti sveikaji skaiciu" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    i--; // Pakartotinai įvedimas to paties elemento
                }
            }
            naujas.nd.resize(nd_sk);
            cout << "Iveskite namu darbu rezultatus (nuo 1 iki 10): ";
            for (int i = 0; i < nd_sk; ++i) {
                cin >> naujas.nd[i];
                if (naujas.nd[i] < 1 || naujas.nd[i] > 10 || cin.fail()) {
                    cout << "Klaida: Ivestas netinkamas skaicius. Prasome ivesti sveikaji skaiciu nuo 1 iki 10." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    i--; // Pakartotinai įvedimas to paties elemento
                }
            }

            for (int i = 0; i < 1; ++i) {
                    cout << "Iveskite egzamino rezultata: ";
                    cin >> naujas.eg;
                if (naujas.eg < 1 || naujas.eg > 10 || cin.fail()) {
                    cout << "Klaida: Ivestas netinkamas skaicius. Prasome ivesti sveikaji skaiciu nuo 1 iki 10." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    i--; // Pakartotinai įvedimas to paties elemento
                }
            }

            // Skaičiuojame namų darbų vidurkį
            naujas.ndvid = 0;
            for (size_t j = 0; j < naujas.nd.size(); j++) {
                naujas.ndvid += naujas.nd[j];
            }
            naujas.ndvid /= naujas.nd.size();

            // Skaičiuojame medianą iš visų rezultatų
            vector<double> visiRezultatai = naujas.nd;
            visiRezultatai.push_back(naujas.eg);
            naujas.mediana = median(visiRezultatai);

            // Skaičiuojame galutinį vidurkį
            naujas.galutinis = 0.4 * naujas.ndvid + 0.6 * naujas.eg;

            A.push_back(naujas);

        } else if (choice == 2) {
            cout << "Kiek mokiniu duomenis sugeneruoti: ";
            int n;
            for (int i = 0; i < 1; ++i) {
            cin >> n;
            if (n < 1 || n > 10 || cin.fail()) {
            cout << "Klaida: Ivestas netinkamas skaicius. Prasome ivesti sveikaji skaiciu" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            i--; // Pakartotinai įvedimas to paties elemento
            }
            }

            for (int i = 0; i < n; i++) {
                duomenys naujas;
                cout << "Iveskite varda: ";
                cin >> naujas.vardas;
                cout << "Iveskite pavarde: ";
                cin >> naujas.pavarde;
                cout << "Iveskite kiek namu darbu rezultatu norite sugeneruoti: ";
                int nd_sk;
                for (int i = 0; i < 1; ++i) {
                cin >> nd_sk;
                if (nd_sk < 1 || cin.fail()) {
                    cout << "Klaida: Ivestas netinkamas skaicius. Prasome ivesti sveikaji skaiciu" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    i--; // Pakartotinai įvedimas to paties elemento
                }
            }
            naujas.nd.resize(nd_sk);

                // Sugeneruojame atsitiktinius namų darbų rezultatus
                for (size_t j = 0; j < naujas.nd.size(); j++) {
                    naujas.nd[j] = rand() % 10 + 1; // Sugeneruojame rezultatus nuo 1 iki 10
                }

                // Sugeneruojame atsitiktinį egzamino rezultatą
                naujas.eg = rand() % 10 + 1; // Sugeneruojame rezultatą nuo 1 iki 10

                // Skaičiuojame namų darbų vidurkį
                naujas.ndvid = 0;
                for (size_t j = 0; j < naujas.nd.size(); j++) {
                    naujas.ndvid += naujas.nd[j];
                }
                naujas.ndvid /= naujas.nd.size();

                // Skaičiuojame medianą iš visų rezultatų
                vector<double> visiRezultatai = naujas.nd;
                visiRezultatai.push_back(naujas.eg);
                naujas.mediana = median(visiRezultatai);

                // Skaičiuojame galutinį vidurkį
                naujas.galutinis = 0.4 * naujas.ndvid + 0.6 * naujas.eg;

                A.push_back(naujas);
            }

        } else if (choice == 3) {
            cout << "Kiek mokiniu duomenis sugeneruoti: ";
            int n;
            for (int i = 0; i < 1; ++i) {
            cin >> n;
            if (n < 1 || cin.fail()) {
            cout << "Klaida: Ivestas netinkamas skaicius. Prasome ivesti sveikaji skaiciu" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            i--; // Pakartotinai įvedimas to paties elemento
            }
            }

            for (int i = 0; i < n; i++) {
                duomenys naujas;
                naujas.nd.resize(rand() % 10 + 1); // Sugeneruoti atsitiktinį kiekį namų darbų rezultatų nuo 1 iki 10
                generuotiBalus(naujas.nd, naujas.eg); // Sugeneruoti atsitiktinius namų darbų ir egzamino rezultatus
                naujas.vardas = "Vardas" + to_string(i + 1); // Sugeneruoti atsitiktinį vardą
                naujas.pavarde = "Pavarde" + to_string(i + 1); // Sugeneruoti atsitiktinę pavardę

                // Skaičiuojame namų darbų vidurkį
                naujas.ndvid = 0;
                for (size_t j = 0; j < naujas.nd.size(); j++) {
                    naujas.ndvid += naujas.nd[j];
                }
                naujas.ndvid /= naujas.nd.size();

                // Skaičiuojame medianą iš visų rezultatų
                vector<double> visiRezultatai = naujas.nd;
                visiRezultatai.push_back(naujas.eg);
                naujas.mediana = median(visiRezultatai);

                // Skaičiuojame galutinį vidurkį
                naujas.galutinis = 0.4 * naujas.ndvid + 0.6 * naujas.eg;

                A.push_back(naujas);
            }

        } else if (choice == 4) {
        string pavadinimas;
        cout << "Iveskite failo pavadinima: ";
        cin >> pavadinimas;
        skaitytiIsFailo(A, pavadinimas);
    }else if (choice == 5) {
            int rikiavimoPasirinkimas;
            cout << "Pasirinkite, kaip rikiuoti duomenis:" << endl;
            cout << "1. Pagal varda" << endl;
            cout << "2. Pagal pavarde" << endl;
            cout << "3. Pagal galutini (vid.)" << endl;
            cout << "4. Pagal galutini (med.)" << endl;
            cout << "Jusu pasirinkimas: ";
                        int n;
            for (int i = 0; i < 1; ++i) {
            cin >> rikiavimoPasirinkimas;
            if (rikiavimoPasirinkimas < 1 || rikiavimoPasirinkimas > 4 || cin.fail()) {
            cout << "Klaida: Ivestas netinkamas skaicius. Prasome ivesti sveikaji skaiciu" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            i--; // Pakartotinai įvedimas to paties elemento
            }
            }

            if (rikiavimoPasirinkimas == 1) {
                rikiuotiPagalVarda(A);
            } else if (rikiavimoPasirinkimas == 2) {
                rikiuotiPagalPavarde(A);
            } else if (rikiavimoPasirinkimas == 3) {
                rikiuotiPagalGalutiniVidurki(A);
            } else if (rikiavimoPasirinkimas == 4) {
                rikiuotiPagalMediana(A);
            } else {
                cout << "Netinkamas pasirinkimas!" << endl;
            }
        } else if (choice == 6) {
            int isvedimoPasirinkimas;
            cout << "Pasirinkite, kaip norite isvesti duomenis:" << endl;
            cout << "1. I konsole" << endl;
            cout << "2. I faila 'Isvedimas.txt'" << endl;
            cout << "Jusu pasirinkimas: ";
            cin >> isvedimoPasirinkimas;

            if (isvedimoPasirinkimas == 1) {
                atspausdintiDuomenis(A);
            } else if (isvedimoPasirinkimas == 2) {
                atspausdintiDuomenis(A, true);
            } else {
                cout << "Netinkamas pasirinkimas!" << endl;
            }
        } else if (choice == 7) {
            break;
        } else {
            cout << "Pasirinkimas neteisingas. Bandykite dar karta." << endl;
        }
    }

    return 0;
}
