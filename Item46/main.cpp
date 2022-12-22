/*
============== Item 4 ==================

In C++ initializarea unei valori poate fi
    -> fie zero, fie altceva
    -> pentru siguranta mereu initializam obiectele inainte sa le folosim
        -> int x = 0; // pentru int
        -> const char *text = "A string"  // pentru un pointer
        -> double d; std:: cin>>d; // initializare prin citire din input stream
    -> pentru aproape orice altceva, initializarea e facuta prin intermediul constructorului
        !!! ne asiguram ca in constructor tot din cadrul obiectului va fi initializat !!!
        

        !!! ce avem aici e asignare de valori, nu initializare !!!

        ============ Constructor assignment-version ================

        -> data members sunt initializati inainte sa intram in corpul constructorului
        -> initializarea lor a avut loc inainte, cand construcorii lor default au fost invocati
           automati, inainte sa intram in corpul constructorului AEBentry
        -> au fost initializate campurile, dupa care le atribuim alte valori peste cele construite default
           deci toata procedura e oarecum folosita degeaba



        ABEntry::ABEntry(const std::string& name, const std::string& address,
        const std::list<PhoneNumber>& phones)
        {
            theName = name; // these are all assignments,
            theAddress = address; // not initializations
            thePhones = phones;
            numTimesConsulted = 0;
        }

       ============ Constructor member-initialization ================

        -> argumentele din lista de initializare sunt folositi ca si parametru pentru
           constructorii pentru membrii obiectului
        -> ex: theName e copy constructed din name
        -> aceasta metoda e mai eficienta, deoarece avem doar o singura invocare catre copy constructor
            pe cand la cealalta, avem o invocare catre constructorul default, apoi o alta invocare catre
            copy assignment operator
        -> pentru obiecte built-in (cum ii numTimesConsulted) ambele metode sunt la fel de eficiente, dar e
            recomandat sa folosim aceeasi metoda pentru uniformitate
            
        ABEntry::ABEntry(const std::string& name, const std::string& address,
        const std::list<PhoneNumber>& phones)
        :   theName(name),
            theAddress(address), // these are now all initializations
            thePhones(phones),
            numTimesConsulted(0)
        {} // the ctor body is now empty

        ====== Exemplu Constructor fara Parametrii =========

        ABEntry::ABEntry()
        :   theName(), // call theName’s default ctor;
            theAddress(), // do the same for theAddress;
            thePhones(), // and for thePhones;
            numTimesConsulted(0) // but explicitly initialize
        {} // numTimesConsulted to zero


        Clasa de baza e mereu initializata inaintea unei clase derivate
            -> in interiorul unei clase, atributele sunt initializare in ordinea in care au fost declarate
            (pentru a evita anumite probleme, preferabil ca atributele din lista de initializare sa fie in aceeasi ordine cu
            modul in care au fost declarate in interiorul clasei)

    Un obiect static exista din momentul in care a fost construit pana la terminarea programului
        -> obiecte globale, obiecte definite in scope-ul namespace-ului, obiectele declarate static in clase
            obiecte declarate static in interiorul unei functii
        -> pentru obiecte delcarate static la nivel de functie, local static objects (sunt locale functiei)
        -> destructorul lor e apelat cand un program isi termina executia


    Translation Unit 
        -> un fisier sursa unic, la care adaugam toate fisierele header




==================== Item 5 ========================
    -> daca nu le declaram noi singurei, compilatoarele o sa isi declare singure
        propriile versiune de:
            -> copy constructor
            -> copy assigment constructor
            -> deconstructor
    -> daca nu declaram nici1 constructor, compilatorul va declara el unul de asemenea
    -> functiile sunt generate doar daca este nevoie de el, dar va fi nevoie de ele (chiar rapid)

    !!! toate functiile enumerate mai sus for fi publice si inline !!!

    class Empty{}; acelasi lucru cu  class Empty {
                                            public:
                                            Empty() { ... } // default constructor
                                            Empty(const Empty& rhs) { ... } // copy constructor
                                            ~Empty() { ... } // destructor — see below
                                            // for whether it’s virtual
                                            Empty& operator=(const Empty& rhs) { ... } // copy assignment operator
                                            };
    
    Empty e1; // default constructor // destructor
    Empty e2(e1); // copy constructor
    e2 = e1; // copy assignment operator


    === Copy Constructor si Copy Assignment Op ===
        -> versiunile generate de compilator pur si simplu vor copia fiecare atribut non static din source in target


    ===== Exemplu =====
    !!! avem constructor care are nevoie de argumente cand va fi invocat, compilatorul nu va genera un nou constructor 
        care sa nu aiba nevoie de argumente, dar va genera copy constructor si copy assignment operator cand va fi nevoie de ele !!!

        template<typename T>
        class NamedObject {
        public:
        NamedObject(const char *name, const T& value);
        NamedObject(const std::string& name, const T& value);
        ...
        private:
        std::string nameValue;
        T objectValue;
        };
    
    !!! daca avem referinte catre un tip de date sau valori const, copy assignment operator generat de compilator
        nu va stie exact ce sa faca si va trebui sa ne declaram propriu copy assignment operator

            1) atributele care sunt referinte la acelasi tip de data, vor referi catre obiecte diferite
                in C++ nu avem posibilitatea sa modificam obiectul spre care indica o referinta 
            2) nu avem voie sa modificam atribute const
            3) compilatorul refuza copy assigment operator din clase derivate care mostenesc din clase de baza a caror copy assignment operator e declarat privat





================ Item 6 ==================
    
    -> E posibil sa avem clase care sa desemneze obiecte care sunt unice (CNP exemplu), si nu ar trebui sa avem acces
    la copy constructor si la copy assigment operator
    -> toate metodele create de compilator sunt publice, pentru a evita ca acestea sa fie generate
        trebuie sa le declaram noi ca fiind private 
    -> o alta metoda ar fi sa avem o clasa privata Uncopyable, pe care clasa noastra, care nu ar trebui sa fie copiabila, sa o mesteneasca
        
*/
#include <iostream>
using namespace std;
using std::string;

class Book {
    public:
    Book(const string& name, const string& author);

    private:
        string theName;
        string theAuthor;
        int thePrice;
};

// Aici avem metoda in care in constructor facem asignare //

// Book::Book(const std::string& name, const std::string& author)
// {
//     theName = name;
//     theAuthor = author;
//     thePrice = 0;
// }

// Aici avem constructor cu lista de initializare pentru fiecare atribut //

Book::Book(const std::string& name, const std::string& author)
   :theName(name),
    theAuthor(author),
    thePrice(0)

{}

// Exemplu de clasa in care nu declaram noi consturctor, destructor, copy constructor si nici copy assigment operator
// ele totusi vor fi implementate de compilator
class Book1 {};

class Book2 {
    public:
        Book2(string name);

    private:
        string theName;
};

Book2::Book2(string name)
    :theName(name)
{}

class Book3 {
    public:
    
    private:
        Book3(const Book3&);
        Book3& operator = (const Book3&);
};



int main()
{
    //nu vom avea eroare de la compilator ca sunt declarate, el va face asta singur
    //Book1 b1;
    //Book1 b2(b1);
    //b2 = b1;

    //nu vom putea compila codul, deoarece compilatorul nu ne lasa sa copiem cand e vorba de referinte
    // std::string& name("Percy Jackson");
    // Book2 b3(name);
    // Book2 b4(b3);

    Book3 b5;
    Book3 b6;

    Book3 b7(b5);

    b5 = b6;

    return 0;
}
