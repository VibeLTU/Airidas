#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <list>
#include <random>
#include <fstream>
#include <chrono>
#include "Strukturalistas.h"

using namespace std;

int main() {
    int choice;
    list<Duomenys> A;

    while (true) {
        cout << "Pasirinkite veiksma: " << endl;
        cout << "1. Ivesti duomenis ranka" << endl;
        cout << "2. Generuoti pazymius" << endl;
        cout << "3. Generuoti pazymius ir studentu vardus, pavardes" << endl;
        cout << "4. Nuskaityti duomenis is failo" << endl;
        cout << "5. Rikiuoti duomenis" << endl;
        cout << "6. Isvesti duomenis" << endl;
        cout << "7. Generuoti faila su studentais" << endl;
        cout << "8. Kategorizuoti studentus pagal galutini bala" << endl;
        cout << "9. Baigti darba" << endl;
        cout << "Jusu pasirinkimas: ";
        cin >> choice;

        if (cin.fail()) {
            cout << "Klaida: Netinkamas pasirinkimas. Prasome ivesti skaiciu nuo 1 iki 9." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (choice == 1) {
            Duomenys naujas;
            cout << "Iveskite varda: ";
            cin >> naujas.vardas;
            cout << "Iveskite pavarde: ";
            cin >> naujas.pavarde;
            cout << "Iveskite kiek namu darbu rezultatu norite suvesti: ";
            int nd_sk;
            cin >> nd_sk;
            while (nd_sk < 1 || cin.fail()) {
                cout << "Klaida: Ivestas netinkamas skaicius. Prasome ivesti sveikaji skaiciu" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> nd_sk;
            }
            naujas.nd.resize(nd_sk);
            cout << "Iveskite namu darbu rezultatus (nuo 1 iki 10): ";
            auto it = naujas.nd.begin();
            for (; it != naujas.nd.end(); ++it) {
                cin >> *it;
                while (*it < 1 || *it > 10 || cin.fail()) {
                    cout << "Klaida: Ivestas netinkamas skaicius. Prasome ivesti sveikaji skaiciu nuo 1 iki 10." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin >> *it;
                }
            }

            cout << "Iveskite egzamino rezultata: ";
            cin >> naujas.eg;
            while (naujas.eg < 1 || naujas.eg > 10 || cin.fail()) {
                cout << "Klaida: Ivestas netinkamas skaicius. Prasome ivesti sveikaji skaiciu nuo 1 iki 10." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> naujas.eg;
            }

            // Skaičiuojame namų darbų vidurkį
            naujas.ndvid = 0;
            for (const auto& nd : naujas.nd) {
                naujas.ndvid += nd;
            }
            naujas.ndvid /= naujas.nd.size();

            // Skaičiuojame medianą iš visų rezultatų
            list<double> visiRezultatai = naujas.nd;
            visiRezultatai.push_back(naujas.eg);
            naujas.mediana = median(visiRezultatai);

            // Skaičiuojame galutinį vidurkį
            naujas.galutinis = 0.4 * naujas.ndvid + 0.6 * naujas.eg;

            A.push_back(naujas);

        }  else if (choice == 2) {
            cout << "Kiek mokiniu duomenis sugeneruoti: ";
            int n;
            cin >> n;
            while (n < 1 || n > 10 || cin.fail()) {
                cout << "Klaida: Ivestas netinkamas skaicius. Prasome ivesti sveikaji skaiciu" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> n;
            }

            for (int i = 0; i < n; i++) {
                Duomenys naujas;
                naujas.nd.resize(rand() % 10 + 1);
                for (auto& nd : naujas.nd) {
                    nd = rand() % 10 + 1;
                }
                naujas.eg = rand() % 10 + 1;

                naujas.ndvid = 0;
                for (const auto& nd : naujas.nd) {
                    naujas.ndvid += nd;
                }
                naujas.ndvid /= naujas.nd.size();

                list<double> visiRezultatai = naujas.nd;
                visiRezultatai.push_back(naujas.eg);
                naujas.mediana = median(visiRezultatai);

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
                Duomenys naujas;
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
                list<double> visiRezultatai = naujas.nd;
                visiRezultatai.push_back(naujas.eg);
                naujas.mediana = median(visiRezultatai);

                // Skaičiuojame galutinį vidurkį
                naujas.galutinis = 0.4 * naujas.ndvid + 0.6 * naujas.eg;

                A.push_back(naujas);
            }

        } else if (choice == 4) {
        string failoPavadinimas;
        cout << "Iveskite failo pavadinima: ";
        cin >> failoPavadinimas;

        try {
            auto start = chrono::high_resolution_clock::now();
            skaitytiIsFailo(A, failoPavadinimas);
            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double> diff = end - start;
            cout << "Failo nuskaitymas uztruko: " << diff.count() << " s" << endl;
        } catch (const exception& e) {
            cout << e.what() << endl;
        }
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
            int irasu_skaicius;
            cout << "Iveskite studentu irasu skaiciu: ";
            cin >> irasu_skaicius;

            if (cin.fail() || irasu_skaicius < 1) {
                cout << "Klaida: Netinkamas studentu irasu skaicius. Iveskite teigiama skaiciu." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            auto start = chrono::high_resolution_clock::now();
            generuotiFailaSuStudentais(irasu_skaicius);
            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double> diff = end - start;

            cout << "Failo generavimas uztruko: " << diff.count() << " s" << endl;

        } else if (choice == 8) {
            list<Duomenys> geri_studentai;
            list<Duomenys> blogi_studentai;
            auto start = chrono::high_resolution_clock::now();
            for (const auto& studentas : A) {
            if (studentas.galutinis >= 5.0) {
            geri_studentai.push_back(studentas);
        } else {
            blogi_studentai.push_back(studentas);
        }
    }
            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double> diff = end - start;
            cout << "Rusiavimas uztruko: " << diff.count() << " s" << endl;
    rikiuotiStudentus(geri_studentai, blogi_studentai);
        } else if (choice == 9) {
            break;
        } else {
            cout << "Pasirinkimas neteisingas. Bandykite dar karta." << endl;
        }
    }

    return 0;
}


