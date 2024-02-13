#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
using namespace std;

struct duomenys {
    string vardas;
    string pavarde;
    double nd[50]; // namu darbu rezultatai
    double eg; // egzamino rezultatai
    double ndvid; // namu darbu vidurkis
    double galutinis; // bendras vidurkis
    double mediana; // mediana
};

double median(double arr[], int size) {
    sort(arr, arr + size);
    if (size % 2 == 0) {
        return (arr[size / 2 - 1] + arr[size / 2]) / 2.0;
    } else {
        return arr[size / 2];
    }
}

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
            cin >> A[i].nd[j];
            A[i].ndvid += A[i].nd[j];
        }
        A[i].ndvid /= n;
        cout << "Iveskite egzamino rezultatus: " << endl;
        cin >> A[i].eg;

        double visiRezultatai[n + 1];
        for (int j = 0; j < n; j++) {
            visiRezultatai[j] = A[i].nd[j];
        }
        visiRezultatai[n] = A[i].eg;
        A[i].mediana = median(visiRezultatai, n + 1);
        A[i].galutinis = 0.4 * A[i].ndvid + 0.6 * A[i].eg;
    }

    cout << "Vardas" << "         " << "Pavarde" << "        " << "Galutinis (Vid.)" << "        " << "Galutinis (Med.)" << endl;
    cout << "------------------------------------------------------------------------" << endl;
    for (int i = 0; i < m; i++) {
        cout << left << setw(15) << A[i].vardas << setw(15) << A[i].pavarde << setw(15) << fixed << setprecision(2) << A[i].galutinis << setw(15) << A[i].mediana << endl;
    }

    return 0;
}
