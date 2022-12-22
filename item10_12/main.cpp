// ======================== ITEM 10 ======================== //
// ======= Operatorii de asignare returneaza o referinta la *this ======= //
/*Asignarea poate sa fie in lant: x = y = z = 15 > si se ia incepand din dreapta
	-> 15 o sa fie asignat lui z -> lui y o sa ii fie asignata valoarea noua a lui z -> la fel si pentru x
Asignarea returneaza o referinta la argumentul din stanga sa, fiind o conventie care este respectata inclusiv in built-ins

class Exemplu {
	public:
		Exemplu& operator=(const Exemplu& rhs)
		{
			return *this; //
		}
		
		-> Exemplu e1, e2, e3;
		
		e3 = e2 = e1 <==> e3.operator=(e2.operator=(p1));
		// daca operator= nu ar avea ca si return o referinta la *this, nu am avea ce sa pasam mai departe la e3
		// deci implementarea acestui operator ne ajuta in special cand avem asignari inlantuite
		//Asignarea returneaza o referinta la argumentul din stanga sa, adica la obiectul pe care s-a apelat operatia de asignare
		//Conventia se respecta si in cazul altor operatori, +=, -=, *=

*/
	
// ============= ITEM 11 ============= //
// ======= Asignare to self in operator=() ======= //
/*
Exemple de asignare la sine
	-> Exemplu e1 => e1 = e1
	-> a[i] = a[j] => daca i == j
	-> *px = *py => daca cei 2 pointeri daca se refera la acelasi lucru
	
	class Lucru {...};
	class Exemplu{
		private:
			Lucru *l;
	};
	
	**implementare nesigura, deoarece exista sansa ca *this si rhs sa fie acelasi obiect**
		-> daca cumva sunt acelasi obiect, va fi distrus atat obiectul l pentru this cat si pentru rhs
		-> la final Exemplu va avea un pointer care pointeaza spre un obiect care nu mai exista
	Exemplu&Exemplu::operator=(const Exemplu &rhs)
	{
		delete l;
		l = new Lucru(*rhs.l);
		return *this;
	}
	
	** o alta varianta de implementare mai sigura prin identity test **
	
	Exemplu&Exemplu::operator=(const Exemple &rhs)
	{
		if (this == &rhs) return *this;
		
		delete l;
		l = new Lucru(*rhs.l);
		return *this;
	}
	
	//chiar daca e mai sigura aceasta varianta, tot exista niste probleme legate de exceptii cand cream acel nou obiect Lucru in interior
		-> ce se intampla daca nu avem suficienta memorie?
		-> ce se intampla daca copy constructorul obiectului Lucru ne da o exceptie
	//daca unul din cazurile de mai sus are loc, Exemplu va avea o referinta la un obiect Lucru care nu mai exista.
	
	
	
	** varianta care este si self-assignment safe si exception-safe **
		Exemplu& Exemplu::operator=(const Exemplu &rhs)
		{
			Lucru *lOrig = l;
			l = new Lucru(*rhs.l);
			delete lOrig;
			
			return *this;
		}
	// acum in cazul in care "new Lucru" ar duce la una din exceptiile mentionate mai sus, l si Exemplu in care se afla, raman neschimbate
	
	
	** varianta cu swap ** 
		
		class Exemplu {
			void swap(Exemplu &rhs);
		};
		Exemplu& Exemplu::operator=(const Exemplu &rhs) //sau putem sa transmitem prin valoarea Exemplu rhs si nu mai avem nevoie de temp
		{
			Exemplu temp(rhs); //facem o copie temporara a lui rhs
			swap(temp); // schimba continutul lui *this cu ce am facut in copia temp
			return *this;
		}
		

*/

// ============= ITEM 12 ============= //
// ======= Copierea tuturor componentelor unui obiect ======= //
/*
	Intr-o lume ideala avem doar doua functii de copiere:
		-> copy constructor si copy assignment operator

Trebuie avut grija in momentul in care ne declaram propriile functii de copiere, deoarece compilatorul
nu ne va semnala daca nu copiem tot dint-un obiect in altul.
		
Copierea tuturor componentelor consta in :
	1) copierea atributelor existente si a celor care pot fi adaugate ulterior 
	2) copierea acelor atribute care depind de clasa parinte din care clasa curenta este derivata
	
	2) aici ce trebuie sa facem este sa invocam functiile de copiere deja existente in clasa de baza :Parinte(rhs), Parinte::operator=(rhs); 

*/


#include <iostream>
using namespace std;
using std::string;

class Author {
	public:
		Author() {};
		Author(const string& nume)
		:nume(nume)
		{}
		Author& operator=(const Author &a1){
			nume = a1.nume;
			return *this;
		}
	string getNume(){
		return nume;
	}

	private:
		string nume;
};

class Book {
    public:
		Book() {};
		Book(const string& name, Author &author, const int price)
		:name(name),
		author(author),
		price(price)
		{}


		// o varianta de implementare a operator=()
		// Book& operator=(const Book &b1){
        // name = b1.name;
		// price= b1.price; //daca am omite unul dintre atribute, acesta nu ar fi copiat
		// Author *auth = author;
		// author = new Author(*b1.author);
		// delete auth;

		// return *this;
		// }

		void swap(Book &b1){
			Author auth = Author(b1.author);
			Book temp = Book(b1.name, auth, b1.price);

			b1.name = this->name;
			b1.price = this->price;
			b1.author = this->author;

			this->name = temp.name;
			this->price = temp.price;
			this->author = temp.author;
		}

		Book& operator=(Book b1){
			swap(b1);
			return *this;
		}

		string getName(){
			return name;
		}

		string getAuthor(){
			return author.getNume();
		}

	protected:
		string name;
		Author author;
		int price;
};

class FantasyBook : public Book {
	public:
		FantasyBook() {}
		FantasyBook(const string& name, Author &author, const int price, const string& genre)
		:Book(name, author, price),
		genre(genre)
		{}
	FantasyBook& operator=(const FantasyBook& b1){
		if (this == &b1) return *this;

		Book::operator=(b1);
		//genre = b1.genre; //am decis sa omit copierea atribului specific FantasyBook in scopul de a evidentia punctul 2) de la item12

		return *this;
	}
	string getGenre(){
		return genre;
	}
	protected:
		string genre;
};
int main () {

	//Exemplu pentru item 10
	Author author1("Rick Riordan");
	Book book1("Percy Jackson", author1, 20);
	Book book2;
	Book book3;

	book3 = book2 = book1;

	cout << book1.getName() << " " << book1.getAuthor() << " " << "\n";
	cout << book2.getName() << " " << book2.getAuthor() << " " << "\n";
	cout << book3.getName() << " " << book3.getAuthor() << " " << "\n";
	//echivalent cu : book3.operator=(book2.operator=(book1));

	Author author2("Tolkien");
	FantasyBook fbook1("Lord of The Rings", author2 , 40, "medieval");
	fbook1 = fbook1; // evidentiem itemul 11 si itemul 12 prin faptul ca FantasyBook va copia si atributele specifice Book, pe langa cele ale sale
	FantasyBook fbook2;

	fbook2 = fbook1;

	cout << fbook1.getName() << " " << fbook1.getAuthor() << " " << " " << fbook1.getGenre() << "\n";
	cout << fbook2.getName() << " " << fbook2.getAuthor() << " " << " " << fbook2.getGenre() << "\n";


	return 0;
}