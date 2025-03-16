#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


class Abonament {
private:
    string tip;
    double pret;
    int durata;

public:
    Abonament();
    Abonament(string tip, double pret, int durata);
    Abonament(const Abonament& other);
    ~Abonament() {}

    void setPret(double p);
    double getPret();
    string getTip();

    Abonament operator+(const Abonament& other) const;

    void citire(istream &in);
    void afisare(ostream &out);
    friend istream& operator>>(istream& in, Abonament& a);
    friend ostream& operator<<(ostream& out, Abonament& a);
};

Abonament::Abonament() {
    tip = "";
    pret = 0.0;
    durata = 0;
}

Abonament::Abonament(string tip, double pret, int durata) {
    this->tip = tip;
    this->pret = pret;
    this->durata = durata;
}

Abonament::Abonament(const Abonament& other) {
    this->tip = other.tip;
    this->pret = other.pret;
    this->durata = other.durata;
}

void Abonament::setPret(double p) {
    this->pret = p;
}

double Abonament::getPret() {
    return this->pret;
}

string Abonament::getTip() {
    return this->tip;
}

Abonament Abonament::operator+(const Abonament& other) const{
    return Abonament(
        this->tip + " & " + other.tip,
        this->pret + other.pret,
        this->durata + other.durata
    );
}

void Abonament::citire(istream &in) {
    cout << "Introdu tipul abonamentului: ";
    in.ignore();
    getline(in, tip);
    cout << "Introdu pretul: ";
    in >> pret;
    cout << "Introdu durata (luni): ";
    in >> durata;
}

void Abonament::afisare(ostream &out) {
    out << "Tip: " << tip << ", Pret: " << pret << " lei, Durata: " << durata << " luni";
}

istream& operator>>(istream& in, Abonament& a) {
    a.citire(in);
    return in;
}

ostream& operator<<(ostream& out, Abonament& a) {
    a.afisare(out);
    return out;
}



class Membru {
private:
    string nume;
    int varsta;
    Abonament abonament;

public:
    Membru();
    Membru(string nume, int varsta, Abonament abonament);
    Membru(const Membru& other);
    Membru& operator=(const Membru& other);
    ~Membru() {}

    void setVarsta(int varsta);
    int getVarsta();
    string getNume();

    void citire(istream &in);
    void afisare(ostream &out);
    friend istream& operator>>(istream& in, Membru& m);
    friend ostream& operator<<(ostream& out, Membru& m);
};

Membru::Membru() {
    nume = "";
    varsta = 0;
}

Membru::Membru(string nume, int varsta, Abonament abonament) {
    this->nume = nume;
    this->varsta = varsta;
    this->abonament = abonament;
}

Membru::Membru(const Membru& other) {
    this->nume = other.nume;
    this->varsta = other.varsta;
    this->abonament = other.abonament;
}

void Membru::setVarsta(int varsta) {
    this->varsta = varsta;
}

int Membru::getVarsta() {
    return this->varsta;
}

string Membru::getNume() {
    return this->nume;
}

Membru& Membru::operator=(const Membru& other) {
    if (this != &other) {
        this->nume = other.nume;
        this->varsta = other.varsta;
        this->abonament = other.abonament;
    }
    return *this;
}

void Membru::citire(istream &in) {
    cout << "Introdu numele membrului: ";
    in.ignore();
    getline(in, nume);
    cout << "Introdu varsta membrului: ";
    in >> varsta;
}

void Membru::afisare(ostream &out) {
    out << "Nume: " << nume << ", Varsta: " << varsta << " ani" << endl;
    out << "Abonament: " << abonament << endl;
}

istream& operator>>(istream& in, Membru& m) {
    m.citire(in);
    return in;
}

ostream& operator<<(ostream& out, Membru& m) {
    m.afisare(out);
    return out;
}



class Sala {
private:
    vector<Membru> membri;
    vector<Abonament> abonamente;

public:
    Sala();
    void adaugaMembru(Membru m);
    void afisareMembri();
    void afisareAbonamente();
    Abonament alegereAbonament();
    void stergeMembruFisier(const string& nume);
};


Sala::Sala(){
    abonamente.push_back(Abonament("Standard", 180, 1));
    abonamente.push_back(Abonament("Premium", 485, 3));
    abonamente.push_back(Abonament("VIP", 850, 6));
    abonamente.push_back(Abonament("Hero", 1500, 12));
}

void Sala::adaugaMembru(Membru m) {
    ofstream fout("SALA.TXT", ios::app);
    fout << m << '\n';
    fout.close();
}

void Sala::stergeMembruFisier(const string& nume) {
    ifstream fin("SALA.TXT");

    vector<string> continutNou;
    string linie;
    bool membruGasit = false;

    while (getline(fin, linie)) {
        if (linie.find("Nume: " + nume + ",") != string::npos) {
            membruGasit = true;
            getline(fin, linie);
            continue;
        }
        if (!linie.empty()) {
            continutNou.push_back(linie);
        }
    }
    fin.close();

    if (!membruGasit) {
        cout << "Membrul cu numele \"" << nume << "\" nu a fost gasit in fisier." << endl;
        return;
    }

    ofstream fout("SALA.TXT", ios::trunc);
    int counter = 0;

    for (const string& linieNoua : continutNou) {
        fout << linieNoua << '\n';
        counter++;

        if (counter % 2 == 0) {
            fout << '\n';
            counter=0;
        }
    }

    fout.close();

    cout << "Membrul cu numele \"" << nume << "\" a fost sters din fisier." << endl;
}

void Sala::afisareMembri() {
    ifstream fin("SALA.TXT");
    string getContent;
    while(!fin.eof()){
        getline(fin,getContent);
        cout << getContent << '\n';
    }
    fin.close();
}

void Sala::afisareAbonamente(){
    cout<<"Abonamente disponibile in sala: "<<'\n';
    for (Abonament& a : abonamente) {
        a.afisare(cout);
        cout<<'\n';
    }
}

Abonament Sala::alegereAbonament() {
    int optiune;

    do{
        cout<<"Alege un abonament din urmatoarele: "<<'\n';
        for (int i=0;i<abonamente.size();i++){
            cout<<i+1<<" - ";
            abonamente[i].afisare(cout);
            cout<<'\n';
        }
        cout<<"Alege un numar de la 1 la "<<abonamente.size()<<": ";
        cin>>optiune;

        if (optiune<1 || optiune>abonamente.size()){
            cout<<"Optiune invalida! Te rugam sa incerci din nou."<<'\n';
        }
    } while (optiune<1 || optiune>abonamente.size());

    return abonamente[optiune - 1];
}

int getWhatTheyWant() {
    int choice;

    cout << "1 - INTRODUCE MEMBRU" << '\n';
    cout << "---------------------------------" << '\n';
    cout << "2 - AFISARE MEMBRI" << '\n';
    cout << "---------------------------------" << '\n';
    cout << "3 - AFISARE ABONAMENTE" << '\n';
    cout << "---------------------------------" << '\n';
    cout << "4 - STERGE MEMBRU" << '\n';
    cout << "---------------------------------" << '\n';
    cout << "5 - FINALIZARE" << '\n';
    cout << "---------------------------------" << '\n';

    cin >> choice;
    cout << '\n';

    return choice;
}

int main() {
    Sala sala;
    int whatTheyWant = getWhatTheyWant();

    while (whatTheyWant != 5) { // 5 este acum pentru FINALIZARE
        switch (whatTheyWant) {
            case 1: {
                Membru m;
                cout << "Introduceti detalii pentru membru: " << '\n';
                cin >> m;

                Abonament a = sala.alegereAbonament();
                m = Membru(m.getNume(), m.getVarsta(), a);

                sala.adaugaMembru(m);
                break;
            }
            case 2:
                cout << "Membrii din sala: " << '\n';
                sala.afisareMembri();
                break;
            case 3:
                sala.afisareAbonamente();
                break;
            case 4: {
                string nume;
                cout << "Introduceti numele membrului de sters: ";
                cin.ignore();
                getline(cin, nume);
                sala.stergeMembruFisier(nume);
                break;
            }
            default:
                cout << "Optiune invalida!" << '\n';
                break;
        }
        whatTheyWant = getWhatTheyWant();
    }

    cout << "Operatiuni finalizate!" << '\n';

/*
    Abonament abonament1("Premium", 485, 3);
    Abonament abonament2("Hero", 1500, 12);

    Abonament abonament3 = abonament1 + abonament2;

    cout << "Abonament combinat: " << abonament3 << endl;
*/

/*
    Membru membru1("Ion Ionut", 33, Abonament("Premium", 485, 3));
    Membru membru2;

    membru2 = membru1;
    cout << membru2 << endl;
*/
    return 0;
}
