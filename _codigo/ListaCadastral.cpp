#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

template <typename T>
class Node{

        public:
            T info;
            Node* next;


            Node(T info, Node* next){
                this->info = info;
                this->next = next;
            }

            Node(T info){
                this->info = info;
                this->next = NULL;
            }
            Node(){
                this->next = NULL;
            }
};

template <class T>
class ListaCadastral{

	private:
		Node<T>* primeiro;
		Node<T>* atual;

	public:
		ListaCadastral();
		bool PegaOprimeiro(T&);
		bool PegaOproximo(T&);
		bool Vazia();
		bool Cheia();
		bool EstaNaLista(T);
		bool Insere(T);
		bool Retira(T);
		void ImprimeTodos();
		int Quantidade();	
};

template <class T>
ListaCadastral<T>::ListaCadastral(){
    this->primeiro = NULL;
    this->atual = NULL;
}



template <class T>
bool ListaCadastral<T>::Cheia(){
	Node<T> *aux = new Node<T>();

    if(aux = NULL){
        delete(aux);
        return true;
    }else{
        delete(aux);
        return false;
    }
                           
}

template <class T>
bool ListaCadastral<T>::Vazia(){
	if(this->primeiro == NULL){
		return true;
	}else{
		return false;
	}
}

template <class T>
bool ListaCadastral<T>::Retira(T elemento){
	Node<T>* anterior = new Node<T>();
	Node<T>* aux = new Node<T>();
	
	aux = this->primeiro;
	anterior = NULL;
	
	while(aux != NULL && aux->info != elemento ){
		anterior = aux;
		aux = aux->next;
		
	}
	
	if(aux != NULL && aux->info == elemento){
		if(aux != this->primeiro){
			anterior->next = aux->next;
			aux = NULL;
			anterior = NULL;
		}else{
			primeiro = primeiro->next;
			aux = NULL;	
		}
		return true;
	}else{
		return false;
	}
	
}

template <class T>
bool ListaCadastral<T>::Insere(T elemento){
	Node<T>* P;
	Node<T>* anterior;
	Node<T>* novoNo;
	bool AchouX;
	
	P = this->primeiro;
	anterior = NULL;
	
	while(P!= NULL && P->info != elemento){
		anterior = P;
		P = P->next;
	}
	
	if(P != NULL && P->info == elemento){
		
		AchouX = true;
	}else{
		
		AchouX = false;
	}
	
	if(!AchouX){
		if(P!= this->primeiro){
			novoNo = new Node<T>();
			novoNo->info = elemento;
			anterior->next = novoNo;
			novoNo->next = P;
			novoNo = NULL;
			anterior = NULL;
			P = NULL;
		}else{
			novoNo = new Node<T>();
			novoNo->info = elemento;
			novoNo->next = P;
			this->primeiro = novoNo;
			novoNo = NULL;
			anterior = NULL;
			P = NULL;
		}
		return true;
	}else{
		return false;
	}
	
}

template <class T>
bool ListaCadastral<T>::EstaNaLista(T elemento){
	
	Node<T>* anterior = new Node<T>();
	Node<T>* aux = new Node<T>();	
	
	aux = this->primeiro;
	anterior = NULL;
	
	while(aux != NULL && aux->info != elemento ){
		anterior = aux;
		aux = aux->next;
	}
	
	if(aux != NULL && aux->info == elemento){
		return true;
	}else{
		return false;
	}
}

template <class T>
bool ListaCadastral<T>::PegaOprimeiro(T& elemento){
	this->atual = this->primeiro;
	
	if(this->atual != NULL){
		elemento = atual->info;
		return true;
	}else{
		return false;
	}
}

template <class T>
bool ListaCadastral<T>::PegaOproximo(T& elemento){
	if(this->atual->next != NULL){
		this->atual = this->atual->next;
		elemento = this->atual->info;
		return true;
	}else{
		return false;
	}
}

template <class T>
void ListaCadastral<T>::ImprimeTodos(){
	T x;
	bool tem;
	tem = this->PegaOprimeiro(x);
	
	while(tem==true){
		cout << x << " ";
		tem = this->PegaOproximo(x);
	}
	
	cout << endl;
}

template <class T>
int ListaCadastral<T>::Quantidade(){
	T x;
	bool tem;
	int cont = 0;
	tem = this->PegaOprimeiro(x);
	
	while(tem==true){
		tem = this->PegaOproximo(x);
		cont ++;
	}
	
	return cont;
}


