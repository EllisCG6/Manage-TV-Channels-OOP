#include <iostream>
#include <string>
#include <vector>

using namespace std;

class IOInterface {
 public:
  virtual istream &Citire(istream &) = 0;
  virtual ostream &Afisare(ostream &) const = 0;

};

class CanalTV : public IOInterface {
 protected:
  const int id;
  static int CONTOR;

  string numeCanal;
  int nrAngajati;
  float bugetCanal;
  float ratingMediu;
 public:
  //Constructor fara parametrii CanalTV
  CanalTV();

  //Constructor cu toti parametrii CanalTV
  CanalTV(string, int, float, float);

  //Copy constructor CanalTV
  CanalTV(const CanalTV &);

  //Operator egal CanalTV
  CanalTV &operator=(const CanalTV &);

  //Destructor CanalTV
  ~CanalTV() {}

  //Operator citire CanalTV
  friend istream &operator>>(istream &, CanalTV &);

  //Functie citire CanalTV
  istream &Citire(istream &);

  //Operator afisare CanalTV
  friend ostream &operator<<(ostream &, const CanalTV &);

  //Functie afisare CanalTV
  ostream &Afisare(ostream &) const;

  //Functionalitate comparare rating/buget
  bool operator < (const CanalTV&) ;

  //Functionlitate obtinere indicator performanta
 float calculIndicatorPerformanta()  const ;

 //Functionalitate verificare buget
 bool checkBuget();
 //Functionalitate calc buget
  virtual float calcBuget() const =0;


};

//Variabila statica CONTORid CanalTV
int CanalTV::CONTOR = 1000;

//Constructor fara parametrii CanalTV
CanalTV::CanalTV() : id(CONTOR++), numeCanal("Empty"), nrAngajati(0), bugetCanal(0), ratingMediu(0) {}

//Constructor cu toti parametrii CanalTV
CanalTV::CanalTV(string numeCanal, int nrAngajati,
                 float bugetCanal, float ratingMediu)
    : id(CONTOR++), numeCanal(numeCanal), nrAngajati(nrAngajati),
      bugetCanal(bugetCanal), ratingMediu(ratingMediu) {}

//Copy constructor CanalTV
CanalTV::CanalTV(const CanalTV &obj) : id(obj.id), numeCanal(obj.numeCanal), nrAngajati(obj.nrAngajati),
                                       bugetCanal(obj.bugetCanal), ratingMediu(obj.ratingMediu) {}

//Operator egal CanalTV
CanalTV &CanalTV::operator=(const CanalTV &obj) { //CanalTV& pt ca se returneaza o adresa de tip CanalTV
  if (this != &obj) {
    this->numeCanal = obj.numeCanal;
    this->nrAngajati = obj.nrAngajati;
    this->bugetCanal = obj.bugetCanal;
    this->ratingMediu = obj.ratingMediu;
  }
  return *this; // operator egal returneaza adresa lui this
}

//Operator citire CanalTV
istream &operator>>(istream &in, CanalTV &obj) {
  return obj.Citire(in);
}

//Functie citire CanalTV
istream &CanalTV::Citire(istream &in) {
  in.get();
  cout << "Nume canal: " << endl;
  getline(in, numeCanal);
  cout << "Nr. angajati: " << endl;
  in >> nrAngajati;
  cout << "Buget canal (euro): " << endl;
  in >> bugetCanal;
  cout << "Rating mediu: " << endl;
  in >> ratingMediu;

  return in;
}

//Operator afisare CanalTV
ostream &operator<<(ostream &out, const CanalTV &obj) {
  return obj.Afisare(out);
}

//Functie afisare CanalTV
ostream &CanalTV::Afisare(ostream &out) const {
  out << "Id: " << id << endl;
  out << "Nume canal: " << numeCanal << endl;
  out << "Nr. angajati: " << nrAngajati << endl;
  out << "Buget canal (euro): " << bugetCanal << endl;
  out << "Rating mediu: " << ratingMediu << endl;

  return out;
}

 float CanalTV ::  calculIndicatorPerformanta() const
{
  return ratingMediu / bugetCanal;
}

bool CanalTV :: operator<(const CanalTV &obj)
{
  return this->calculIndicatorPerformanta() < obj.calculIndicatorPerformanta();
}

bool CanalTV ::checkBuget() {
  if (this->calcBuget() < bugetCanal)
    return true;
  return false;
}

//Final CanalTV

class CanalStiri : virtual public CanalTV {
 protected:
  int nrBuletineLive;
  int durataBuletin;
  int salariuModerator;
  int salariuReporter;
  int nrModeratori;
  int nrReporteri;
  string orarBuletine;//separate de spatiu
  vector<string> moderatori;
  vector<string> reporteri;

 public:
  //Constructor fara parametrii CanalStiri
  CanalStiri();

  //Constructor cu toti parametrii CanalStiri
  CanalStiri(string, int, float, float, int, int, int, int, int, int, string, vector<string>, vector<string>);

  //Copy constructor CanalStiri
  CanalStiri(const CanalStiri &);

  //Operator egal CanalStiri
  CanalStiri &operator=(const CanalStiri &);

  //Destructor CanalStiri
  ~CanalStiri() {}

  //Functie citire CanalStiri
  istream &Citire(istream &);

  //Citire proprie CanalStiri
  istream& CitireSt(istream&);

  //Functie afisare CanalStiri
  ostream &Afisare(ostream &) const;

  //Afisare proprie CanalStiri
  ostream& AfisareSt(ostream&) const;

  //Functionalitate adaugare moderator
  void adaugaModerator();

  //Functionalitate adaugare reporter
  void adaugaReporter();

  //Calc buget
  float calcBuget()const;

};

//Constructor fara parametrii CanalStiri
CanalStiri::CanalStiri() : CanalTV(), nrBuletineLive(0), durataBuletin(0), salariuModerator(0),
                           salariuReporter(0), nrModeratori(0), nrReporteri(0), orarBuletine("empty") {}

//Constructor cu toti parametrii CanalStiri
CanalStiri::CanalStiri(string numeCanal,
                       int nrAngajati,
                       float bugetCanal,
                       float ratingMediu,
                       int nrBuletineLive,
                       int durataBuletin,
                       int salariuModerator,
                       int salariuReporter,
                       int nrModeratori,
                       int nrReporteri,
                       string orarBuletine,
                       vector<string> moderatori,
                       vector<string> reporteri) : CanalTV(numeCanal,
                                                           nrAngajati,
                                                           bugetCanal,
                                                           ratingMediu),
                                                   nrBuletineLive(nrBuletineLive),
                                                   durataBuletin(durataBuletin),
                                                   salariuModerator(salariuModerator),
                                                   salariuReporter(salariuReporter),
                                                   nrModeratori(nrModeratori),
                                                   nrReporteri(nrReporteri),
                                                   orarBuletine(orarBuletine),
                                                   moderatori(moderatori),
                                                   reporteri(reporteri) {}

//Copy constructor CanalStiri
CanalStiri::CanalStiri(const CanalStiri &obj) : CanalTV(obj), nrBuletineLive(obj.nrBuletineLive),
                                                durataBuletin(obj.durataBuletin),
                                                salariuModerator(obj.salariuModerator),
                                                salariuReporter(obj.salariuReporter),
                                                nrModeratori(obj.nrModeratori),
                                                nrReporteri(obj.nrReporteri),
                                                orarBuletine(obj.orarBuletine),
                                                moderatori(obj.moderatori),
                                                reporteri(obj.reporteri) {}

CanalStiri &CanalStiri::operator=(const CanalStiri &obj) {
  if (this != &obj) {
    CanalTV::operator=(obj);
    this->nrBuletineLive = obj.nrBuletineLive;
    this->durataBuletin = obj.durataBuletin;
    this->salariuModerator = obj.salariuModerator;
    this->salariuReporter = obj.salariuReporter;
    this->nrModeratori = obj.nrModeratori;
    this->nrReporteri = obj.nrReporteri;
    this->orarBuletine = obj.orarBuletine;
    this->moderatori = obj.moderatori;
    this->reporteri = obj.reporteri;
  }
  return *this;
}

//Functie citire CanalStiri
istream &CanalStiri::Citire(istream &in) {
  this->CanalTV::Citire(in);
  CitireSt(in);

  return in;
}

//Citire proprie CanalStiri
istream& CanalStiri:: CitireSt(istream&in){
  cout << "Nr. buletine live: " << endl;
  in >> nrBuletineLive;
  cout << "Durata buletin (min): " << endl;
  in >> durataBuletin;
  cout << "Salariu general moderatori (euro): " << endl;
  in >> salariuModerator;
  cout << "Salariu general reporteri (euro): " << endl;
  in >> salariuReporter;
  cout << "Numar moderatori: " << endl;
  in >> nrModeratori;
  cout << "Numar reporteri: " << endl;
  in >> nrReporteri;
  in.get();
  cout << "Orele de inceput ale buletinelor (separate de spatiu): " << endl;
  getline(in, orarBuletine);

  string t;
  for (int i = 0; i < nrModeratori; i++) {
    cout << "Moderator " << i + 1 << ": " << endl;
    getline(in, t);
    moderatori.push_back(t);
  }
  for (int i = 0; i < nrReporteri; i++) {
    cout << "Reporter " << i + 1 << ": " << endl;
    getline(in, t);
    reporteri.push_back(t);
  }

  return in;
};


//Functie afisare CanalStiri
ostream &CanalStiri::Afisare(ostream &out) const {
  cout << "Canal stiri: " << endl <<endl;
  this->CanalTV::Afisare(out);
  AfisareSt(out);
  return out;
}

//Afisare proprie CanalStiri
ostream& CanalStiri:: AfisareSt(ostream&out) const{
  out << "Nr. buletine live: ";
  out << nrBuletineLive << endl;
  out << "Durata buletin (min): ";
  out << durataBuletin << endl;
  out << "Salariu general moderatori (euro): ";
  out << salariuModerator << endl;
  out << "Salariu general reporteri (euro): ";
  out << salariuReporter << endl;
  out << "Numar moderatori: ";
  out << nrModeratori << endl;
  out << "Numar reporteri: ";
  out << nrReporteri << endl;
  out << "Orele de inceput ale buletinelor (separate de spatiu): ";
  out << orarBuletine << endl;

  for (int i = 0; i < nrModeratori; i++) {
    out << "Moderator " << i + 1 << ": ";
    out << moderatori[i] << endl;
  }
  for (int i = 0; i < nrReporteri; i++) {
    out << "Reporter " << i + 1 << ": ";
    out << reporteri[i] << endl;
  }

  return out;
};

void CanalStiri::adaugaModerator() {
  string u;
  cout << "Numele moderatorului: " << endl ;
  getline(cin, u);
  nrModeratori++;
  moderatori.push_back(u);
}

void CanalStiri::adaugaReporter() {
  string u;
  cout << "Numele reporterului: " << endl ;
  getline(cin, u);
  nrReporteri++;
  reporteri.push_back(u);
}


float CanalStiri::calcBuget() const {
  float salarii = 0;
  salarii = (float) (nrModeratori * salariuModerator + nrReporteri * salariuReporter);
  return salarii;
}


//FINAL CanalStiri

class CanalDivertisment : virtual public CanalTV {
 protected:
  int nrEmisiuni;
  int salariuPrezentator;
  vector<string> emisiuni;
  vector<string> genuriEmisiuni;
  vector<string> prezentatori;

 public:
  //Constructor fara parametrii CanalDivertisment
  CanalDivertisment();

  //Constructor cu toti parametrii CanalDivertisment
  CanalDivertisment(int, int, vector<string>, vector<string>, vector<string>, string, int, float, float);

  //Copy constructor CanalDivertisment
  CanalDivertisment(const CanalDivertisment &);

  //Operator egal CanalDivertisment
  CanalDivertisment &operator=(const CanalDivertisment &);

  //Destructor CanalDivertisment
  ~CanalDivertisment() {};

  //Functie citire CanalDivertisment
  istream &Citire(istream &);

  //Citire CanalDiv proprie
  istream& CitireDiv(istream&);

  //Functie afisare CanalDivertisment
  ostream &Afisare(ostream &) const;

  //Afisare CanalDiv proprie
  ostream &AfisareDiv(ostream &) const;

  //Functionlitate adaugare emisiune in grila
  void adaugaEmisiune();


  //Calcul buget
  float calcBuget() const;
};

//Constructor fara parametrii CanalDivertisment
CanalDivertisment::CanalDivertisment() : CanalTV(), nrEmisiuni(0), salariuPrezentator(0) {}

//Constructor cu toti parametrii CanalDivertisment
CanalDivertisment::CanalDivertisment(int nrEmisiuni,
                                     int salariuPrezentator,
                                     vector<string> emisiuni,
                                     vector<string> genuriEmisiuni,
                                     vector<string> prezentatori,
                                     string numeCanal,
                                     int nrAngajati,
                                     float bugetCanal,
                                     float ratingMediu) : CanalTV(numeCanal, nrAngajati, bugetCanal, ratingMediu),
                                                          nrEmisiuni(nrEmisiuni),
                                                          salariuPrezentator(salariuPrezentator),
                                                          emisiuni(emisiuni),
                                                          genuriEmisiuni(genuriEmisiuni),
                                                          prezentatori(prezentatori) {}

//Copy constructor CanalDivertisment
CanalDivertisment::CanalDivertisment(const CanalDivertisment &obj) : CanalTV(obj),
                                                                     nrEmisiuni(obj.nrEmisiuni),
                                                                     salariuPrezentator(obj.salariuPrezentator),
                                                                     emisiuni(obj.emisiuni),
                                                                     genuriEmisiuni(obj.genuriEmisiuni),
                                                                     prezentatori(obj.prezentatori) {}

//Operator egal CanalDivertisment
CanalDivertisment &CanalDivertisment::operator=(const CanalDivertisment &obj) {
  this->CanalTV::operator=(obj);
  this->nrEmisiuni = obj.nrEmisiuni;
  this->salariuPrezentator = obj.salariuPrezentator;
  this->emisiuni = obj.emisiuni;
  this->genuriEmisiuni = obj.genuriEmisiuni;
  this->prezentatori = obj.prezentatori;

  return *this;
}

//Functie citire CanalDivertisment
istream &CanalDivertisment::Citire(istream &in) {
  this->CanalTV::Citire(in);
  CitireDiv(in);
//  cout << "Numar emisiuni: " << endl;
//  in >> nrEmisiuni;
//  cout << "Salariu general prezentator (euro): " << endl;
//  in >> salariuPrezentator;
//
//  in.get();
//  string t;
//  for (int i = 0; i < nrEmisiuni; i++) {
//    cout << "Emisiune " << i + 1 << ": " << endl;
//    getline(in, t);
//    emisiuni.push_back(t);
//    cout << "Genul emisiunii " << i + 1 << ": " << endl;
//    getline(in, t);
//    genuriEmisiuni.push_back(t);
//    cout << "Prezentatorul emisiunii " << i + 1 << ": " << endl;
//    getline(in, t);
//    prezentatori.push_back(t);
//
//  }

  return in;
}

//Citire CanalDiv proprie
istream& CanalDivertisment :: CitireDiv(istream&in){
  cout << "Numar emisiuni: " << endl;
  in >> nrEmisiuni;
  cout << "Salariu general prezentator (euro): " << endl;
  in >> salariuPrezentator;

  in.get();
  string t;
  for (int i = 0; i < nrEmisiuni; i++) {
    cout << "Emisiune " << i + 1 << ": " << endl;
    getline(in, t);
    emisiuni.push_back(t);
    cout << "Genul emisiunii " << i + 1 << ": " << endl;
    getline(in, t);
    genuriEmisiuni.push_back(t);
    cout << "Prezentatorul emisiunii " << i + 1 << ": " << endl;
    getline(in, t);
    prezentatori.push_back(t);

  }
  return in;
}

//Functie afisare CanalDivertisment
ostream &CanalDivertisment::Afisare(ostream &out) const {
  cout << "Canal divertisment: " << endl <<endl;
  this->CanalTV::Afisare(out);
  AfisareDiv(out);

  return out;
}

//Afisare CanalDiv proprie
ostream & CanalDivertisment:: AfisareDiv(ostream &out) const{

  out << "Numar emisiuni: " << nrEmisiuni << endl;
  out << "Salariu general prezentator (euro): " << salariuPrezentator << endl;

  for (int i = 0; i < nrEmisiuni; i++) {
    out << "Emisiune " << i + 1 << ": " << emisiuni[i] << endl;
    out << "Genul: " << genuriEmisiuni[i] << endl;
    out << "Prezentator: " << prezentatori[i] << endl;
  }

  return out;
}
void CanalDivertisment::adaugaEmisiune() {
  nrEmisiuni++;
  string u;
  cout <<"Nume emisiune: " << endl;
  getline(cin, u);
  emisiuni.push_back(u);
  cout << "Prezentator emisiune: " << endl;
  getline(cin, u);
  prezentatori.push_back(u);
  cout << "Genul emisiunii: " << endl;
  getline(cin, u);
  genuriEmisiuni.push_back(u);
}

float CanalDivertisment::calcBuget() const {
  float salarii;
  salarii = (float) (salariuPrezentator*prezentatori.size());
  return salarii;
};

class CanalStiriDivertisment : public CanalStiri, public CanalDivertisment {
 public:
  //Constructor fara parametrii CanalStiriDivertisment
  CanalStiriDivertisment() {};

  //Constructor cu toti parametrii CanalStiriDivertisment
  CanalStiriDivertisment(int,
                         int,
                         vector<string>,
                         vector<string>,
                         vector<string>,
                         string,
                         int,
                         float,
                         float,
                         int,
                         int,
                         int,
                         int,
                         int,
                         int,
                         string,
                         vector<string>,
                         vector<string>);

  //Copy constructor CanalStiriDivertisment
  CanalStiriDivertisment(const CanalStiriDivertisment &);

  //Operator egal CanalStiriDivertisment
  CanalStiriDivertisment &operator=(const CanalStiriDivertisment &);

  //Destructor CanalStiriDivertisment
  ~CanalStiriDivertisment() {};

  friend istream& operator >>(istream&, CanalStiriDivertisment&);
  friend ostream& operator <<(ostream&, const CanalStiriDivertisment&);

  //Functie citire CanalStiriDivertisment
  istream &Citire(istream &);

  //Functie afisare CanalStiriDivertisment
  ostream &Afisare(ostream &) const;

  //Functionalitate verificare  buget
  float calcBuget() const;
};

//Constructor cu toti parametrii CanalStiriDivertisment
CanalStiriDivertisment::CanalStiriDivertisment(int nrEmisiuni,int salariuPrezentator,vector<string> emisiuni,vector<string> genuriEmisiuni,vector<string> prezentatori,
                                               string numeCanal,
                                               int nrAngajati,
                                               float bugetCanal,
                                               float ratingMediu,
                                               int nrBuletineLive,int durataBuletin,int salariuModerator,
                                               int salariuReporter,int nrModeratori,int nrReporteri,string orarBuletine,vector<string> moderatori,vector<string> reporteri)
                                               :CanalStiri(numeCanal, nrAngajati, bugetCanal, ratingMediu, nrBuletineLive,durataBuletin,salariuModerator,salariuReporter,nrModeratori,nrReporteri,orarBuletine,moderatori,reporteri),
CanalDivertisment( nrEmisiuni,salariuPrezentator,emisiuni,genuriEmisiuni,prezentatori,numeCanal, nrAngajati, bugetCanal, ratingMediu) {}

//Copy constructor CanalStiriDivertisment
CanalStiriDivertisment :: CanalStiriDivertisment(const CanalStiriDivertisment &obj): CanalStiri(obj) , CanalDivertisment(obj)
{}

//Operator egal CanalStiriDivertisment
CanalStiriDivertisment& CanalStiriDivertisment :: operator=(const CanalStiriDivertisment &obj){
  CanalStiri::operator=(obj);
  CanalDivertisment::operator=(obj);
}

//Functie citire CanalStiriDivertisment
istream& CanalStiriDivertisment ::  Citire(istream &in){
  this->CanalTV ::Citire(in);
  cout << "Departamentul stiri: " << endl;
  this->CanalStiri ::CitireSt(in);
  cout << "Departamentul divertisment: " << endl;
  this->CanalDivertisment ::CitireDiv(in);

  return in;
};

//Functie afisare CanalStiriDivertisment
ostream & CanalStiriDivertisment :: Afisare(ostream &out) const{
  cout <<"Canal mixt (stiri+divertisment): "<< endl;
  this->CanalTV::Afisare(out);
  cout << "Departamentul stiri: " << endl;
  this->CanalStiri ::AfisareSt(out);
  cout << "Departamentul divertisment: " << endl;
  this->CanalDivertisment ::AfisareDiv(out);


  return out;
};

istream& operator>>(istream&in, CanalStiriDivertisment &obj)
{
  return obj.Citire(in);
}

ostream& operator << (ostream &in, const CanalStiriDivertisment &obj)
{
  return obj.Afisare(in);
}
float CanalStiriDivertisment::calcBuget() const {
  return (float) (CanalStiri::calcBuget() + CanalDivertisment::calcBuget()) ;
}

int main() {

  vector <CanalTV*> canale;
  int k = 1;

  while(k==1){
    cout << "1. Inregistrati canal de stiri"<< endl << "2. Inregistrati canal de divertisment"<<endl<<"3. Inregistrati canal mixt" << endl<<"4. Afisare canale"<<endl;
    int val;
    cin >> val;
    switch(val){
      case 1:
      {
        CanalTV* canal = new CanalStiri;
        cin >> *canal;
        canale.push_back(canal);
        break;
      }
      case 2:
      {
        CanalTV* canal = new CanalDivertisment;
        cin >> *canal;
        canale.push_back(canal);
        break;
      }
      case 3:
      {

        CanalTV* canal = new CanalStiriDivertisment;
        cin >> *canal;
        canale.push_back(canal);
        break;
      }
      case 4:
      {
        for(int i=0; i<canale.size(); i++)
          cout<<*canale[i]<<endl;
        break;
      }
      case 5:
      default: {k = 0; break;}
    }
  }

  return 0;
}
