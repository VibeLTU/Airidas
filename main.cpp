#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct duomenys {
    string vardas;
    string pavarde;
    double nd; // namu darbu rezultatai
    double eg; // egzamino rezultatai
    double ndvid; // namu darbu vidurkis
    double galutinis; // bendras vidurkis
};

int main() {
    duomenys A[50];
    int n, m;
    cout << "Iveskite studentu skaiciu: ";
    cin >> m;
    cout << "Iveskite namu darbu skaiciu: ";
    cin >> n;

    for (int i = 0; i < m; i++) {
        A[i].ndvid = 0;
        cout << "Iveskite varda: " << endl;
        cin >> A[i].vardas;
        cout << "Iveskite pavarde: " << endl;
        cin >> A[i].pavarde;
        for (int j = 0; j < n; j++) {
            cout << "Iveskite namu darbu rezultatus: " << endl;
            cin >> A[i].nd;
            A[i].ndvid += A[i].nd;
        }
        A[i].ndvid = A[i].ndvid / n;
        cout << "Iveskite egzamino rezultatus: " << endl;
        cin >> A[i].eg;
        A[i].galutinis = 0.4 * A[i].ndvid + 0.6 * A[i].eg;
    }
    cout << "Vardas" << "         " << "Pavarde" << "        " << "Galutinis (Vid.)" << endl;
    cout << "--------------------------------------" << endl;
    for (int i = 0; i < m; i++) {
        cout << left << setw(15) << A[i].vardas << left << setw(15) << A[i].pavarde << left << setw(15) << setprecision(3) << A[i].galutinis << endl;
    }
}
