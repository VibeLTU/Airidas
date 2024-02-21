#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <random>
using namespace std;

struct duomenys {
    string vardas;
    string pavarde;
    double *nd;
    int nd_sk;
    double eg;
    double ndvid;
    double galutinis;
    double mediana;
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

// Funkcija, kuri sugeneruoja atsitiktinius balus už namų darbus ir egzaminą
void generuotiBalus(double *nd_rezultatai, int nd_sk, double &eg) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> nd_distribution(1, 10);
    uniform_int_distribution<> eg_distribution(1, 10);

    for (int i = 0; i < nd_sk; ++i) {
        nd_rezultatai[i] = nd_distribution(gen);
    }
    eg = eg_distribution(gen);
}

// Funkcija, kuri atspausdina studentų duomenis
void atspausdintiDuomenis(duomenys *A, int m) {
    cout << "Vardas" << "         " << "Pavarde" << "        " << "Galutinis (Vid.)" << "        " << "Galutinis (Med.)" << endl;
    cout << "------------------------------------------------------------------------" << endl;
    for (int i = 0; i < m; i++) {
        cout << left << setw(15) << A[i].vardas << left << setw(15) << A[i].pavarde << left << setw(15) << setprecision(3) << A[i].galutinis <<  "         " << left << setw(15) << setprecision(3) <<  A[i].mediana << endl;
    }
}

int main() {
    int choice;
    int m = 0;
    duomenys *A = nullptr;

    while (true) {
        cout << "Pasirinkite veiksma: " << endl;
        cout << "1. Ivesti duomenis ranka" << endl;
        cout << "2. Generuoti pazymius" << endl;
        cout << "3. Generuoti pazymius ir studentu vardus, pavardes" << endl;
        cout << "4. Baigti darba" << endl;
        cout << "Jusu pasirinkimas: ";
        cin >> choice;
        if (cin.fail() || choice < 1 || choice > 4) {
            cout << "Klaida: Pasirinkimas turi buti sveikas skaicius nuo 1 iki 4." << endl;
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
            while (true) {
                cout << "Iveskite kiek namu darbu rezultatu norite suvesti: ";
                cin >> naujas.nd_sk;
                if (naujas.nd_sk <= 0) {
                    cout << "Klaida: Prasome ivesti teigiama skaiciu." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                } else {
                    naujas.nd = new double[naujas.nd_sk];
                    cout << "Iveskite namu darbu rezultatus (nuo 1 iki 10): ";
                    for (int i = 0; i < naujas.nd_sk; ++i) {
                        cin >> naujas.nd[i];
                        if (naujas.nd[i] < 1 || naujas.nd[i] > 10 || cin.fail()) {
                            cout << "Klaida: Ivestas netinkamas skaicius. Prasome ivesti sveikaji skaiciu nuo 1 iki 10." << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            i--; // Pakartotinai įvedimas to paties elemento
                        }
                    }
                    break;
                }
            }
            cout << "Iveskite egzamino rezultata: ";
            for (int i = 0; i < 1; ++i) {
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
            for (int j = 0; j < naujas.nd_sk; j++) {
                naujas.ndvid += naujas.nd[j];
            }
            naujas.ndvid /= naujas.nd_sk;

            // Skaičiuojame medianą iš visų rezultatų
            double *visiRezultatai = new double[naujas.nd_sk + 1];
            for (int j = 0; j < naujas.nd_sk; j++) {
                visiRezultatai[j] = naujas.nd[j];
            }
            visiRezultatai[naujas.nd_sk] = naujas.eg;
            naujas.mediana = median(visiRezultatai, naujas.nd_sk + 1);
            delete[] visiRezultatai;

            // Skaičiuojame galutinį vidurkį
            naujas.galutinis = 0.4 * naujas.ndvid + 0.6 * naujas.eg;

            // Praplečiame masyvą nauju elementu
            duomenys *temp = new duomenys[m + 1];
            for (int i = 0; i < m; i++)
                temp[i] = A[i];
            temp[m] = naujas;

            delete[] A;
            A = temp;

            m++;
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
                for (int i = 0; i < 1; ++i) {
                cin >> naujas.nd_sk;
                if (naujas.nd_sk < 1 || naujas.nd_sk > 10 || cin.fail()) {
                cout << "Klaida: Ivestas netinkamas skaicius. Prasome ivesti sveikaji skaiciu" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                i--; // Pakartotinai įvedimas to paties elemento
                }
                }
                naujas.nd = new double[naujas.nd_sk];

                // Sugeneruojame atsitiktinius namų darbų rezultatus
                for (int j = 0; j < naujas.nd_sk; j++) {
                    naujas.nd[j] = rand() % 10 + 1; // Sugeneruojame rezultatus nuo 1 iki 10
                }

                // Sugeneruojame atsitiktinį egzamino rezultatą
                naujas.eg = rand() % 10 + 1; // Sugeneruojame rezultatą nuo 1 iki 10

                // Skaičiuojame namų darbų vidurkį
                naujas.ndvid = 0;
                for (int j = 0; j < naujas.nd_sk; j++) {
                    naujas.ndvid += naujas.nd[j];
                }
                naujas.ndvid /= naujas.nd_sk;

                // Skaičiuojame medianą iš visų rezultatų
                double *visiRezultatai = new double[naujas.nd_sk + 1];
                for (int j = 0; j < naujas.nd_sk; j++) {
                    visiRezultatai[j] = naujas.nd[j];
                }
                visiRezultatai[naujas.nd_sk] = naujas.eg;
                naujas.mediana = median(visiRezultatai, naujas.nd_sk + 1);
                delete[] visiRezultatai;

                // Skaičiuojame galutinį vidurkį
                naujas.galutinis = 0.4 * naujas.ndvid + 0.6 * naujas.eg;

                // Praplečiame masyvą nauju elementu
                duomenys *temp = new duomenys[m + 1];
                for (int i = 0; i < m; i++)
                    temp[i] = A[i];
                temp[m] = naujas;

                delete[] A;
                A = temp;

                m++;
            }
        } else if (choice == 3) {
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
                naujas.nd_sk = rand() % 10 + 1; // Sugeneruoti atsitiktinį kiekį namų darbų rezultatų nuo 1 iki 10
                naujas.nd = new double[naujas.nd_sk];
                generuotiBalus(naujas.nd, naujas.nd_sk, naujas.eg); // Sugeneruoti atsitiktinius namų darbų ir egzamino rezultatus
                naujas.vardas = "Vardas" + to_string(i + 1); // Sugeneruoti atsitiktinį vardą
                naujas.pavarde = "Pavarde" + to_string(i + 1); // Sugeneruoti atsitiktinę pavardę

                // Skaičiuojame namų darbų vidurkį
                naujas.ndvid = 0;
                for (int j = 0; j < naujas.nd_sk; j++) {
                    naujas.ndvid += naujas.nd[j];
                }
                naujas.ndvid /= naujas.nd_sk;

                // Skaičiuojame medianą iš visų rezultatų
                double *visiRezultatai = new double[naujas.nd_sk + 1];
                for (int j = 0; j < naujas.nd_sk; j++) {
                    visiRezultatai[j] = naujas.nd[j];
                }
                visiRezultatai[naujas.nd_sk] = naujas.eg;
                naujas.mediana = median(visiRezultatai, naujas.nd_sk + 1);
                delete[] visiRezultatai;

                // Skaičiuojame galutinį vidurkį
                naujas.galutinis = 0.4 * naujas.ndvid + 0.6 * naujas.eg;

                // Praplečiame masyvą nauju elementu
                duomenys *temp = new duomenys[m + 1];
                for (int i = 0; i < m; i++)
                    temp[i] = A[i];
                temp[m] = naujas;

                delete[] A;
                A = temp;

                m++;
            }
        } else if (choice == 4) {
            break;
        } else {
            cout << "Pasirinkimas neteisingas. Bandykite dar karta." << endl;
        }
    }

    atspausdintiDuomenis(A, m);

    // Atlaisviname dinaminį masyvą
    for (int i = 0; i < m; i++) {
        delete[] A[i].nd;
    }
    delete[] A;

    return 0;
}
