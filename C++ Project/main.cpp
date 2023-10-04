#include "grafoT.h"


#include <string>
#include <iostream>
#include <ostream>

void test_fondamentali() {
  grafoT<int> g1(0);
  int i = 0;
  bool b = false;

  std::cout << "******** Test metodi fondamentali su grafo di interi ******** " << '\n';
  g1.aggiungiNodo(10);
  g1.aggiungiNodo(20);
  g1.aggiungiNodo(30);
  g1.aggiungiArco(10,10);
  g1.aggiungiArco(10,20);
  g1.aggiungiArco(10,30);
  g1.aggiungiArco(30,20);
  g1.aggiungiArco(20,30);

  std::cout << "Test stampa matrice, operatore di stream dopo aver aggiunto nodi e archi:" << '\n';
  g1.stampaMat();
  std::cout << g1 << '\n';
  std::cout << "Test metodi numero nodi e numero archi:" << '\n';
  i = g1.getNumNodi();
  std::cout << "numero nodi: " << i << '\n';
  i = g1.getNumArchi();
  std::cout << "numero archi: " << i << '\n';

  std::cout << "Test stampa matrice, operatore di stream dopo aver rimosso nodi e archi:" << '\n';
  g1.rimuoviNodo(20);
  g1.rimuoviArco(10,10);
  g1.stampaMat();
  std::cout << g1 << '\n';
  std::cout << "Test metodi numero nodi e numero archi:" << '\n';
  i = g1.getNumNodi();
  std::cout << "numero nodi: " << i << '\n';
  i = g1.getNumArchi();
  std::cout << "numero archi: " << i << '\n';

  std::cout << "Test copy constructor:" << '\n';
  grafoT<int> g2(g1);
  g2.stampaMat();
  g2.aggiungiNodo(5);
  g2.aggiungiNodo(50);
  g2.aggiungiArco(5,50);
  g2.aggiungiArco(50,10);
  g2.stampaMat();
  std::cout << g2 << '\n';
  i = g2.getNumNodi();
  std::cout << "numero nodi: " << i << '\n';
  i = g2.getNumArchi();
  std::cout << "numero archi: " << i << '\n';

  std::cout << "Test metodi exist e hasEdge:" << '\n';
  b = g2.exist(20);
  std::cout << "exist(20)=  " << b << '\n';
  b = g2.exist(5);
  std::cout << "exist(5)=  " << b << '\n';

  b = g2.hasEdge(10,50);
  std::cout << "hasEdge(10,50)= " << b << '\n';
  b = g2.hasEdge(50,10);
  std::cout << "hasEdge(50,10)= " << b << '\n';

  std::cout << "Test operatori:" << '\n';
  std::cout << "g1: " << g1;
  std::cout << "g1: " << g2;
  std::cout << "g1 dopo aver scambiato secondo valore: " << '\n';
  g1[1] = g2[3];
  std::cout << g1;
  std::cout << "accesso g1[0]: " << g1[0] << '\n';
  std::cout << "Assegnamento g2=g1: ";
  g2 = g1;
  std::cout << g2 << '\n';

  std::cout << "Test numero nodi e archi dopo clear():" << '\n';
  g1.clear();
  g2.clear();
  i = g1.getNumNodi();
  std::cout << "numero nodi: " << i << '\n';
  i = g1.getNumArchi();
  std::cout << "numero archi: " << i << '\n';
}


void test_grafo_stringhe_iteratori() {
  std::cout << '\n' << "******** Test sul grafo di stringhe ********" << std::endl;
  grafoT<std::string> g1(0);
  int i2 = 0;
  int b = false;

  g1.aggiungiNodo("pippo");
  g1.aggiungiNodo("pluto");
  g1.aggiungiNodo("minnie");
  g1.aggiungiNodo("paperino");

  g1.aggiungiArco("pippo", "paperino");
  g1.aggiungiArco("pippo", "pluto");
  g1.aggiungiArco("pippo", "minnie");
  g1.aggiungiArco("pippo", "pippo");
  g1.aggiungiArco("pluto", "paperino");

  std::cout << "Test stampa matrice, operatore di stream dopo aver aggiunto nodi e archi:" << '\n';
  g1.stampaMat();
  std::cout << g1;

  std::cout << "Stampa con iteratori" << std::endl;
  grafoT<std::string>::const_iterator i, ie;
  for(i=g1.begin(), ie=g1.end(); i != ie; ++i)
		std::cout << *i << std::endl;

  std::cout << "Test stampa matrice, operatore di stream dopo aver rimosso nodi:" << '\n';
  g1.rimuoviNodo("pippo");
  g1.stampaMat();
  std::cout << "g1: " << g1 << '\n';

  std::cout << "Test numero nodi e archi:" << '\n';
  i2 = g1.getNumNodi();
  std::cout << "numero nodi: " << i2 << '\n';
  i2 = g1.getNumArchi();
  std::cout << "numero archi: " << i2 << '\n';

  g1.clear();

}

struct punto {
  int x;
  int y;

  punto() : x(0), y(0) {};
  punto(int n, int c) : x(n), y(c) {};
};

struct compare_Punto {
	bool operator()(const punto &p1, const punto &p2) const {
		return (p1.x==p2.x && p1.y==p2.y);
	}
};


std::ostream& operator<<(std::ostream &os, const punto &p) {
	os << "{" << p.x << " " << p.y << "}";
	return os;
}

void test_funtore_Punto(void) {
  grafoT<punto, compare_Punto> g1(0);
  int i = 0;
  bool b = false;
  std::cout << '\n' << "******** Test su grafo di punti ********" << std::endl;

  punto p1(1,1);
  punto p2(3,4);
  punto p3(5,2);
  g1.aggiungiNodo(p1);
  g1.aggiungiNodo(p2);
  g1.aggiungiNodo(p3);
  g1.aggiungiArco(p1,p2);
  g1.aggiungiArco(p1,p1);
  g1.aggiungiArco(p1,p3);
  g1.aggiungiArco(p3,p3);

  std::cout << "Test Stampa matrice e con operator<<" << std::endl;
  g1.stampaMat();
	std::cout << g1 << std::endl;

  std::cout << "Test metodi numero nodi e numero archi:" << '\n';
  i = g1.getNumNodi();
  std::cout << "numero nodi: " << i << '\n';
  i = g1.getNumArchi();
  std::cout << "numero archi: " << i << '\n';

  std::cout << "Test stampa matrice, operatore di stream dopo aver rimosso nodi e archi:" << '\n';
  g1.rimuoviNodo(p1);
  g1.stampaMat();
  std::cout << g1 << '\n';
  std::cout << "Test metodi numero nodi e numero archi:" << '\n';
  i = g1.getNumNodi();
  std::cout << "numero nodi: " << i << '\n';
  i = g1.getNumArchi();
  std::cout << "numero archi: " << i << '\n';

  punto p4(2,8);
  punto p5(7,7);
  punto p6(4,5);
  g1.aggiungiNodo(p4);
  g1.aggiungiNodo(p5);
  g1.aggiungiNodo(p6);
  g1.aggiungiArco(p4,p4);
  g1.aggiungiArco(p4,p5);
  g1.aggiungiArco(p4,p6);
  g1.aggiungiArco(p2,p4);
  g1.aggiungiArco(p6,p5);
  g1.aggiungiArco(p3,p6);
  std::cout << "Test copy constructor:" << '\n';
  grafoT<punto, compare_Punto> g2(g1);
  g2.stampaMat();
  punto p7(1,1);
  g2.aggiungiNodo(p7);
  g2.aggiungiArco(p7,p2);
  g2.aggiungiArco(p5,p7);
  g2.stampaMat();
  std::cout << g2 << '\n';
  i = g2.getNumNodi();
  std::cout << "numero nodi: " << i << '\n';
  i = g2.getNumArchi();
  std::cout << "numero archi: " << i << '\n';
  g2.rimuoviNodo(p4);
  g2.stampaMat();
  std::cout << g2 << '\n';
  i = g2.getNumNodi();
  std::cout << "numero nodi: " << i << '\n';
  i = g2.getNumArchi();
  std::cout << "numero archi: " << i << '\n';

  std::cout << "Test metodi exist e hasEdge:" << '\n';
  b = g2.exist(p5);
  std::cout << "exist(p5)=  " << b << '\n';
  punto pp(2,2);
  b = g2.exist(pp);
  std::cout << "exist(pp)=  " << b << '\n';

  b = g2.hasEdge(p7,p2);
  std::cout << "hasEdge(p7,p2)= " << b << '\n';
  b = g2.hasEdge(p2,p7);
  std::cout << "hasEdge(p2,p7)= " << b << '\n';

  std::cout << "Test operatori:" << '\n';
  std::cout << "g1: " << g1;
  std::cout << "g2: " << g2;
  g1[1] = g2[3];
  std::cout << "g1 con secondo nodo scambiato: " << g1;
  std::cout << g1[0] << '\n';
  g2 = g1;
  std::cout << g2 << '\n';

  std::cout << "Test numero nodi e archi dopo clear():" << '\n';
  g1.clear();
  g2.clear();
  i = g1.getNumNodi();
  std::cout << "numero nodi: " << i << '\n';
  i = g1.getNumArchi();
  std::cout << "numero archi: " << i << '\n';
}




int main() {
  test_fondamentali();

  test_grafo_stringhe_iteratori();

  test_funtore_Punto();

  return 0;
}
