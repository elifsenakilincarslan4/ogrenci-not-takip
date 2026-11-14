#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct Ogrenci {
    string numara;
    string ad;
    double notu;
};

vector<Ogrenci> ogrenciler;
const string DOSYA = "ogrenciler.txt";

void yukle() {
    ifstream f(DOSYA);
    string satir;
    while (getline(f, satir)) {
        if (satir.empty()) continue;
        size_t p1 = satir.find(';');
        size_t p2 = satir.find(';', p1 + 1);
        if (p1 == string::npos || p2 == string::npos)
        continue;
        Ogrenci o;
        o.numara = satir.substr(0, p1);
        o.ad     = satir.substr(p1 + 1, p2 - p1 - 1);
        o.notu   = stod(satir.substr(p2 + 1));
        ogrenciler.push_back(o);
    }
}

void kaydet() {
    ofstream f(DOSYA);
    for (const auto& o : ogrenciler)
        f << o.numara << ';' << o.ad << ';' << o.notu << '\n';
}

void ekle() {
    Ogrenci o;
    cout << "Numara: ";   cin >> ws; getline(cin, o.numara);
    cout << "Ad Soyad: "; getline(cin, o.ad);
    cout << "Not: ";      cin >> o.notu;
    ogrenciler.push_back(o);
    kaydet();
    cout << ">> Eklendi.\n";
}

void listele() {
    if (ogrenciler.empty()) { cout << ">> Kayit yok.\n"; return; }
    cout << "\n--- Ogrenciler ---\n";
    for (const auto& o : ogrenciler)
        cout << o.numara << " | " << o.ad << " | Not: " << o.notu << '\n';
    cout << "------------------\n";
}

void ara() {
    string n;
    cout << "Aranacak numara: "; cin >> ws; getline(cin, n);
    for (const auto& o : ogrenciler)
        if (o.numara == n) {
            cout << ">> Bulundu: " << o.ad << " | Not: " << o.notu << '\n';
            return;
        }
    cout << ">> Bulunamadi.\n";
}

void sil() {
    string n;
    cout << "Silinecek numara: "; cin >> ws; getline(cin, n);
    for (size_t i = 0; i < ogrenciler.size(); i++)
        if (ogrenciler[i].numara == n) {
            ogrenciler.erase(ogrenciler.begin() + i);
            kaydet();
            cout << ">> Silindi.\n";
            return;
        }
    cout << ">> Bulunamadi.\n";
}

int main() {
    yukle();
    int secim;
    do {
        cout << "\n=== Ogrenci Not Takip ===\n";
        cout << "1) Ekle\n2) Listele\n3) Ara\n4) Sil\n0) Cikis\nSecim: ";
        cin >> secim;
        switch (secim) {
            case 1: ekle();    break;
            case 2: listele(); break;
            case 3: ara();     break;
            case 4: sil();     break;
            case 0: cout << ">> Cikis yapiliyor...\n"; break;
            default: cout << ">> Gecersiz secim.\n";
        }
    } while (secim != 0);
    return 0;
}
