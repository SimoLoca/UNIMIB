#ifndef GRAFOT_H
#define GRAFOT_H

#include <algorithm>	// std::swap
#include <cassert>
#include <ostream>
#include <iostream>
#include <iterator> // std::forward_iterator_tag
#include <cstddef>  // std::ptrdiff_t

/**
	Eccezione custom, lanciata quando fallisce un costruttore

	@brief Eccezione custom per la classe grafoT
*/
class fallimento_costruttore_exception {};

/**
	Eccezione custom, lanciata quando si aggiunge un nodo già esistente nel grafo

	@brief Eccezione custom per la classe grafoT
*/
class aggiunta_nodo_esistente_exception {};

/**
	Eccezione custom, lanciata quando si rimuove un nodo non esistente nel grafo

	@brief Eccezione custom per la classe grafoT
*/
class rimozione_nodo_non_esistente_exception {};

/**
	Eccezione custom, lanciata quando si aggiunge un arco non esistente nel grafo

	@brief Eccezione custom per la classe grafoT
*/
class aggiunta_arco_matrNonEsistente_exception {};

/**
	Eccezione custom, lanciata quando si rimuove un arco non esistente nel grafo

	@brief Eccezione custom per la classe grafoT
*/
class rimozione_arco_matrNonEsistente_exception {};


/**
	Funtore di comparazione generico per tipi standard che valuta
	l'uguaglianza tra i dati usando l'operatore standard.
	Il funtore ritorna true se a==b.

	@brief Funtore di comparazione generico per tipi standard
*/
template <typename T>
struct uguale {
	bool operator()(const T &a, const T &b) const {
		return a==b;
	}
};


/**
	Classe che implementa un grafo orientato di dati generici T mediante una
	matrice di adiacenza.
	Possono essere aggiunti/rimossi nodi/archi.
	L'uguaglianza e' fatta usando un funtore di comparazione U.

	@brief Classe che rappresenta un Grafo Orientato usando una matrice di
	adiacenza come supporto

	@param T tipo del nodo
	@param U funtore di comparazione (==) di due dati
	*/
template <typename T, typename U=uguale<T> >
class grafoT {

public:
	typedef unsigned int dimT;

private:
	/** Numero massimo di nodi che contiene il grafo */
	dimT _nMax;
	/** Puntatore a puntatori di booleani (la matrice di adiacenza) */
	bool **_matr;
	/** Puntatore ad array nodi di tipo T */
	T *_nodi;

	/** Numero di nodi nel grafo */
	int _numNodi;
	/** Oggetto Funtore per la comparazione di dati */
	U _uG;

	/**
	Funzione privata per l'inizializzazione del grafo

	@param n dimensione iniziale grafo
	@throw eccezione fallimento del costruttore
	*/
	void init(dimT n) {
		try {
			_nMax = n;
			_matr = new bool*[n];
			_nodi = new T[n];
			_numNodi = 0;

			for (dimT i = 0; i < n; ++i) {
				_matr[i] = new bool[n];
				for (dimT j = 0; j < n; ++j) {
					_matr[i][j] = 0;
				}
			}
		} catch (...) {
			clear();
			throw fallimento_costruttore_exception();
		}

	}

public:
	/**
	Costruttore di Default
	*/
	grafoT() : _nMax(0), _matr(0), _numNodi(0) {}

	/**
	Costruttore Primario

	@param n numero di nodi massimo
	*/
	explicit grafoT(dimT n) : _nMax(0), _matr(0), _nodi(0), _numNodi(0) {
		init(n);
	}

	/**
	Costruttore di Copia

	@param other grafo da copiare
	@throw eccezione nel caso non si riesce a costruire il grafo
	*/
	grafoT(const grafoT &other) : _nMax(0), _matr(0), _nodi(0), _numNodi(0) {
		init(other._nMax);

		try {
			for (dimT i = 0; i < _nMax; ++i) {
				_nodi[i] = other._nodi[i];
				for (dimT j = 0; j < _nMax; ++j) {
					_matr[i][j] = other._matr[i][j];
				}
			}
			_numNodi = other._numNodi;
			_nMax = other._nMax;
		} catch(...) {
			clear();
			throw fallimento_costruttore_exception();
		}
	}

	/**
	Operatore Assegnamento

	@param other grafo da usare per trasferire i dati
	@return Reference all'operando this
	*/
	grafoT& operator=(const grafoT &other) {
		if (this != &other) {
			grafoT tmp(other);
			this->swap(tmp);
		}
		return *this;
	}

	/**
	Distruttore
	*/
	~grafoT() {
		clear();
	}

	/**
	Funzione per lo svuotamento del grafo
	*/
	void clear() {
		for (dimT i = 0; i < _nMax; ++i) {
			delete[] _matr[i];
		}
		delete[] _matr;
		_matr = NULL;
		delete _matr;
		delete[] _nodi;
		_nodi = NULL;
		delete _nodi;
		_nodi = 0;
		_nMax = 0;
		_numNodi = 0;
	}

	/**
	Operatore accesso diretto

	@param n Indice dell'elemento a cui si vuole accedere
	@return Reference al dato richiesto
	*/
	T& operator[](dimT n) {
		assert(n < _nMax);
		return _nodi[n];
	}

	/**
	Operatore accesso diretto in sola lettura

	@param n Indice dell'elemento a cui si vuole accedere
	@return Reference const al dato richiesto
	*/
	const T& operator[](dimT n) const {
	 assert(n < _nMax);
	 return _nodi[n];
 }

 /**
 Funzione costante che ritorna il numero di nodi nel grafo

 @return numero nodi
 */
	int getNumNodi() const {
		return _numNodi;
	}

	/**
  Funzione costante che ritorna il numero di archi nel grafo

  @return numero archi
  */
	int getNumArchi() const {
		int archi = 0;
		for (dimT i = 0; i < _nMax; ++i) {
			for (dimT j = 0; j < _nMax; ++j) {
				if (_matr[i][j] == 1)
					archi++;
			}
		}
		return archi;
	}

	/**
  Funzione costante che stampa la matrice di adiacenza
  */
	void stampaMat() const {
		dimT i, j;
		for (i = 0; i < _nMax; ++i) {
			for (j = 0; j < _nMax; ++j) {
				std::cout << _matr[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}

	/**
	Funzione di swap per scambiare i dati contenuti tra due grafi

	@param other grafo da usare per lo scambio dei dati
	*/
	void swap(grafoT &other) {
		std::swap(_nMax, other._nMax);
		std::swap(_matr, other._matr);
		std::swap(_nodi, other._nodi);
		std::swap(_numNodi, other._numNodi);
	}

	/**
	Funzione per aggiungere un nodo al grafo se non già presente

	@param elem nodo che si vuole aggiungere al grafo
	@throw eccezione aggiunta nodo esistente
	*/
	void aggiungiNodo(const T &elem) {
		bool t = false;
		for (dimT i = 0; i < _nMax; ++i) {
			if (_uG(_nodi[i], elem))
				t = true;
		}

		if (t == true) {
			clear();
			throw aggiunta_nodo_esistente_exception();
		} else {
			if (_numNodi < _nMax) {
				_nodi[_numNodi] = elem;
				_numNodi++;
			} else {
				grafoT tmp(_nMax+1);
				for (dimT i = 0; i < tmp._nMax-1; ++i) {
					tmp._nodi[i] = _nodi[i];
					for (dimT j = 0; j < tmp._nMax-1; ++j) {
						tmp._matr[i][j] = _matr[i][j];
					}
				}
				tmp._numNodi = _numNodi;
				tmp._nodi[_nMax] = elem;
				tmp._numNodi++;
				*this = tmp;
				tmp.clear();
			}
		}
	}

	/**
	Funzione per rimuovere un nodo dal grafo se presente

	@param elem nodo da rimuovere
	@throw eccezione rimozione nodo non esistente
	*/
	void rimuoviNodo(const T &elem) {
		bool t = false;
		dimT p = 0;

		for (dimT i = 0; i < _nMax; ++i) {
			if (_uG(_nodi[i], elem))
				t = true;
		}

		if (t == false) {
			clear();
			throw rimozione_nodo_non_esistente_exception();
		}
		else {
			for (dimT i = 0; i < _nMax; ++i) {
				if (_uG(_nodi[i], elem))
					p = i;
			}
			grafoT tmp(_nMax-1);

			for (dimT i = 0; i < p; ++i)
				tmp._nodi[i] = _nodi[i];
			for (dimT i = p+1; i < _nMax; ++i)
				tmp._nodi[i-1] = _nodi[i];

			for (dimT i = 0; i < p; ++i)
				for (dimT j = 0; j < p; ++j)
					tmp._matr[i][j] = _matr[i][j];

			for (dimT i = p+1; i < _nMax; ++i)
				for (dimT j = 0; j < p; ++j)
					tmp._matr[i-1][j] = _matr[i][j];

			for (dimT i = 0; i < p; ++i)
				for (dimT j = p+1; j < _nMax; ++j)
					tmp._matr[i][j-1] = _matr[i][j];

			for (dimT i = p+1; i < _nMax; ++i)
				for (dimT j = p+1; j < _nMax; ++j)
					tmp._matr[i-1][j-1] = _matr[i][j];

			tmp._numNodi = _numNodi-1;
			*this = tmp;
			tmp.clear();
		 }
	}

	/**
	Funzione per aggiungere un arco al grafo, ovvero inserisce un 1 nella matrice
	di adiacenza per indicare la relazione (se i nodi sono presenti)

	@param n1 I nodo
	@param n2 II nodo
	@throw eccezione aggiunta arco tra nodi non esistenti
	*/
	void aggiungiArco(T n1, T n2) {
		bool t = false;
		dimT x = -1;
		dimT y = -1;
		for (dimT i = 0; i < _nMax; ++i) {
			if (_uG(_nodi[i], n1))
				x = i;
			if (_uG(_nodi[i], n2))
				y = i;
		}
		if (x == -1 || y == -1) {
			clear();
			throw aggiunta_arco_matrNonEsistente_exception();
		} else {
				_matr[x][y] = 1;
			}
	}

	/**
	Funzione per rimuovere un arco dal grafo se presente, mette uno 0 nella
	matrice di adiacenza per indicare l'assenza di relazione

	@param n1 I nodo
	@param n2 II nodo
	@throw eccezione rimozione arco tra nodi non esistenti
	*/
	void rimuoviArco(T n1, T n2) {
		bool t = false;
		dimT x = -1;
		dimT y = -1;
		for (dimT i = 0; i < _nMax; ++i) {
			if (_uG(_nodi[i], n1))
				x = i;
			if (_uG(_nodi[i], n2))
				y = i;
		}
		if (x == -1 || y == -1) {
			clear();
			throw rimozione_arco_matrNonEsistente_exception();
		} else {
				_matr[x][y] = 0;
			}
	}

	/**
	Metodo per verificare l'esistenza di un nodo

	@param n nodo da cercare
	@return booleano per indicare se ha trovato il nodo
	*/
	bool exist(T n) const {
		bool trovato = false;
		for (dimT i = 0; i < _nMax; ++i) {
			if (_uG(_nodi[i], n))
				trovato = true;
		}
		return trovato;
	}

	/**
	Metodo per verificare l'esistenza di un arco

	@param n1 I nodo
	@param n2 II nodo
	@return booleano per indicare se esiste un arco
	*/
	bool hasEdge(T n1, T n2) const {
		bool trovato = false;
		dimT x = 0;
		dimT y = 0;
		for (dimT i = 0; i < _nMax; ++i) {
			if (_uG(_nodi[i], n1))
				x = i;
			if (_uG(_nodi[i], n2))
				y = i;
		}
		if(_matr[x][y] == 1)
			trovato = true;
		return trovato;
	}

	/**
	Iteratore di tipo forward costante del grafo

	@brief Iteratore Forward costante del grafo
	*/
	class const_iterator {

	public:
		typedef std::forward_iterator_tag iterator_category;
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef const T* pointer;
		typedef const T& reference;

		/**
		Costruttore di default per la creazione di un iteratore con puntatore
		inizializzato a NULL
		*/
		const_iterator() : _matr(0) {}

		/**
		Copy constructor per la creazione di un iteratore che punta allo stesso dato
		di un altro iteratore

		@param other Iteratore da usare per ottenere l'indirizzo a cui inizializzare
		il puntatore
		*/
		const_iterator(const const_iterator &other) : _matr(other._matr){}

		/**
		Operatore di assegnamento per trasferire copiare all'interno dell'iteratore
		l'indirizzo di memoria a cui punta un altro iteratore

		@param other Iteratore da usare per ottenere l'indirizzo di memoria a cui
		settare il puntatore
		@return Reference all'operando sinistro dell'operazione di assegnamento
		*/
		const_iterator& operator=(const const_iterator &other) {
			if(this != &other) {
				_matr = other._matr;
			}
			return *this;
		}

		/**
		Distruttore della classe
		*/
		~const_iterator() {
			_matr = 0;
		}

		/**
		Operatore di dereferenziamento per ottenere il dato contenuto nel nodo a
		cui sta puntando l'iteratore

		@return Reference al dato richiesto
		*/
		reference operator*() const {
			return *_matr;
		}

		/**
		Operatore di dereferenziamento per ottenere l'indirizzo di memoria del dato
		contenuto nel nodo a cui sta puntando l'iteratore

		@return Indirizzo di memoria del dato richiesto
		*/
		pointer operator->() const {
			return _matr;
		}

		/**
		Operatore di post-incremento per spostare l'iteratore al nodo successivo
		del grafo

		@return Iteratore che punta al nodo attuale del grafo
		*/
		const_iterator operator++(int) {
			const_iterator tmp(*this);
			++_matr;
			return tmp;
		}

		/**
		Operatore di pre-incremento per spostare l'iteratore al nodo successivo del
		grafo

		@return Iteratore che punta al nodo successivo del grafo
		*/
		const_iterator& operator++() {
			++_matr;
			return *this;
		}

		/**
		Operatore di uguaglianza per controllare se due iteratori puntano allo
		stesso nodo del grafo

		@return TRUE se i due iteratori sono uguali, FALSE altrimenti
		*/
		bool operator==(const const_iterator &other) const {
			return _matr == other._matr;
		}

		/**
		Operatore di diversità per controllare se due iteratori puntano a nodi
		diversi del grafo

		@return TRUE se i due iteratori non sono uguali, FALSE altrimenti
		*/
		bool operator!=(const const_iterator &other) const {
			return _matr != other._matr;
		}


	private:
		/** Puntatore al nodo corrente del grafo */
		T *_matr;

		/**
		La classe grafoT può accedere ai membri privati di questa classe
		*/
		friend class grafoT;

		/**
		Costruttore usato dalla classe grafoT per creare un nuovo iteratore
		*/
		const_iterator(T* nodo2) : _matr(nodo2) {}

	};

	/**
	Funzione per la creazione di un iteratore che punta al primo nodo

	@return Iteratore che punta al primo nodo
	*/
	const_iterator begin() const {
		return _nodi;
	}

	/**
	Funzione per la creazione di un iteratore che punta all'ultimo nodo

	@return Iteratore che punta all'ultimo nodo
	*/
	const_iterator end() const {
		return _nodi+_nMax;
	}


};

/**
	Funzione globale di stampa per stampare il contenuto del set su standard output

	@param os Stream di output
	@param g Grafo da cui ottenere il contenuto da stampare su standard output
	@return Reference allo stream di output

	@brief Funzione globale di stampa per la classe grafoT
*/
template <typename T, typename U>
std::ostream&  operator<<(std::ostream &os, const grafoT<T,U> &g) {
	typename grafoT<T, U>::const_iterator i, ie;

	for (i = g.begin(), ie = g.end(); i != ie; ++i)
		os << *i << " ";
	std::cout << std::endl;

	return os;
}


#endif
