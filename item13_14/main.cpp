							/* ================== ITEM 13 ==================
									 ~ Use objects to manage resources ~     */
									  
			  
		  
/* Avem nevoie de a factory function care sa returneze un pointer spre un obiect alocat dinamic in ierarhia noastra de obiecte.
In plus obiectul care invoca acest tip de functie trebuie sa se ocupe si de stergerea lui.

		void factory_function(){
			Exemplu *exp = createEx();
			//some code
			delete xp;
		}
		
	Ce avem mai sus nu este neaparat o metoda rea, doar ca exista probleme:
		* S-ar putea sa apara situatii exceptionale in partea de //some code, si astfel executia sa nu mai ajunga la partea de delete
			a) avem un return 
			b) stergerea s-ar face intr-un loop si avem break inainte de partea de delete
			c) sa avem raise la un tip de Exception si astfel sa nu mai ajungem la delete
		(acelasi lucru il intalnim de exemplu si in lucru cu fisierele, trebuie sa ne asiguram ca executia prgramului ajunge la file.close()
		 de accea in Python de exemplu avem Context Managers, care implementeaza un protocol de enter si exit, care se asigura ca daca in exit am
		 avea stergerea, aceasta ar avea loc indiferent de faptul ca au aparut situatii exceptionale sau nu.)
		 
	In C++ ca sa ne asiguram ca mereu e distrus/released obiectul in cauza, putem sa il punem intr-un obiect al carui constructor e apelat in momentul
	in care iese din functie.
		* auto_ptr e un smart pointer al carui destructor invoca delete automat a supra ce pointeaza.
		
		void factory_function(){
			std::auto_ptr<Exemplu> exp(createEx());
			
			//some code
		}
		
	Acest exemplu ilustreaza:
		1) sa ne folosim de obiecte ca sa manage resurse: RAII (Resource Acquisition Is Initialization)
		2) cand un obiect iese din scope-ul lui, va fi sters.
		
	!!! Nu trebuie sa existe mai mult de un singur auto_ptr care sa pointeze spre un obiect !!!
		(obiectul ar fi sters de mai multe ori)
		
		Din fericire, auto_ptr au un comportament mai special:
		
			std::auto_ptr<Exemplu> exp1(createEx(());
			std::auto_ptr<Exemplu> exp2(exp);
			exp1 = exp2;
			
		fie ca incercam sa copiem prin copy constructor sau copy assignment operator, obiectul care este copiat este pus pe null
		iar cel in care se copiaza va fi cel care se ocupa de resursa.
		
	O alta metoda pe langa auto_ptr ar fi sa folosim reference-counting smart pointer (RCSP)
		* un RCSP e tot un smart pointer care numara cate obiecte pointeaza spre o anumita resursa si distruge acea resursa atunci cand counter = 0
		
		

		void factory_function(){
			//some code
			std::tr1_share_ptr<Exemplu> exp(createEx());
			//some more code
		}
		
		
	!!! cand incercam sa copiem !!!
		std::tr1::shared_ptr<Exemplu> exp1(createEx());
		std::tr1::shared_ptr<Exemplu> exp2(exp1);
		exp1 = exp2
		
		Spre deosebire de auto_ptr, unde cand ii invocat copy constructor sau copy assigment operator, obiectul din care se copiaza e pus pe null,
		la tr1::shared_ptr, exp1 si exp2 vor pointa spre acelasi obiect, urmand ca la final cei pointeri sa fie stersi (counter = 0) si deci obiectul
		resursa sa fie sters si el.
		
	!!! sa folosim auto_ptr sau tr1::shared_ptr in cazul unor vectori alocati dinamic, e o idee proasta.
	!!! smart pointers precum auto_ptr si tr1::shared_ptr sunt folositi pentru resurse alocate pe heap, in caz contrar nu ar fi o optiune buna, chit 
		ca ar fi compilabila
	
	
	
								/* ================== ITEM 14 ==================
									 ~ Copying behavior in resource-managing classes ~     */
									

/*
	class Lock{
		public:
		explicit Lock(Mutex *pm)
		:mutexPtr(pm)		.
		{lock(mutexPtr);} // aici facem rost de resursa
		~Lock() {unlock(mutexPtr);} // aici ii dam release
		
		private:
			Mutex *mutexPtr;
	}
	
	Mutex m;	//obiectul pe care il vom folosi
	//some code
	{
		Lock ml(&m); //ii dam lock
	//some code		//operatii care s-ar putea termina intr-o situatie exceptionala
	} // obiectul mutex va fi deblocat la finalul acestui bloc de cod
	
	
	!!! ce se intampla cand vrem sa copiem un RAII? !!!
		1) in mod normal nu are sens sa lasam obiectele de acest tip sa fie copiate
		   adica trebuie sa ii mentionam compilatorului ca operatie de copy o sa fie privata
		2) vrem sa avem acces la resursa si existe atata timp cat inca exista obiecte care se folosesc de ea
		   ceva asemanator am vazut si la tr1::shared_ptr, prin faptul ca numara cate obiecte utilizeaza resursa
		   cand ajunge la counter = 0, resursa o sa fie released. Trebuie sa venim cu o solutie ca resursa sa fie unlocked in cazul acesta, nu stearsa
		
			spre norocul nostru, putem modifica functia de deleter din tr1::shared_ptr, care este invocata atunci cand numarul de obiecte care utilieaza resursa ajunge la 0
			
			
	
	Exemplu:
		class Lock{
			public:
				explicit Lock(Mutex *pm)
				:mutexPtr(pm, unlock)
				{
					lock(mutexPtr.get());
				}
			private:
				std::tr1::shared_ptr<Mutex> mutexPtr;
				
			!!! nu mai avem un destructor declarat aici, deoarece orice constructor va fi automat invocat prin intermediul
				unui deconstructor deja existent al unui membru dinamic (mutexPtr) -> delter-ul lui adica functia de unlock pe
				care o pasam ca si parametru
	
*/									
									 
									 

#include <iostream>
#include <memory>
using namespace std;

class A {
public:
void show() {cout << "A::show()" << endl;}
};

int main()
{
auto_ptr<A> p1(new A);
p1->show();

cout << p1.get() << endl; // prin get obtinem locatia


auto_ptr<A> p2(p1); // ne folosim de copy constructor
p2->show();

	//dupa cum am vazut in conspectul de mai sus, cand avem auto_ptr si ne folosim de fie copy constructor sau copy assignment operator
	// auto_ptr din care se copiaza va fi pus pe nul, iar cel in care se copiaza ca avea acces la resursa


cout << p1.get() << endl; //va afisa nul

cout << p2.get() << endl; // va afisa locatia de memorie a resursei



shared_ptr<A> p3(new A);

cout << p3.get() << endl;
p3->show();

shared_ptr<A> p4(p3);
p4->show();

cout << p3.get() << endl;  // va afisa locatia de memorie a resursei
cout << p4.get() << endl;

cout << p3.use_count() << endl; //metoda de .use_count() ne va returna numarul de shared_ptr care folosesc la aceeasi resursa
cout << p4.use_count() << endl;

p3.reset();
cout << p3.get() << endl;
cout << p4.use_count() << endl;
cout << p4.get() << endl;

return 0;
}