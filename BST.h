/*
Clase BST usando template
métodos add y remove
Consuelo Cabello marzo 2022
*/

#ifndef BST_h
#define BST_h

#include "Node.h"

template<class T>
class BST {
private:
    Node<T>* root;
    void printTree(Node<T>* aux, int level);
    int numChildren(Node<T>* aux);
    Node<T>* predecesor(Node<T>* aux);
public:
    BST();
    void add(T data);
    bool find(T data);
    void remove(T data);
    void borrar(T data);
    void print();
    bool isEmpty();
};

template<class T>
BST<T>::BST() {
    root = nullptr;
}

template<class T>
void BST<T>::add(T data) {
    //Validamos si el arbol está vacío
    if (isEmpty()) {
        // apuntamos root a un nodo nuevo
        root = new Node<T>(data);
    } else {
        // creamos un apuntador auxliar que apunte a root
        Node<T>* aux = root;
        // Recorrer el arbol hasta encontrar donde insertar el nodo nuevo
        while (aux != nullptr) {
            // comparamos el valor del dato nuevo con el valor del nodo auxiliar
            if (data < aux->data) {
                // Verificamos si el apuntador left es igual a nulo
                if (aux->left == nullptr) {
                    // agregamos el nodo nuevo en al apuntador left de aux
                    aux->left = new Node<T>(data);
                    // nos salimos del ciclo
                    aux = nullptr;
                } else {
                    // asignamos a aux a aux->left
                    aux = aux->left;
                }
            } else {
                // Verificamos si el apuntador right es igual a nulo
                if (aux->right == nullptr) {
                    // agregamos el nodo nuevo en al apuntador left de aux
                    aux->right = new Node<T>(data);
                    // nos salimos del ciclo
                    aux = nullptr;
                } else {
                    // asignamos a aux a aux->right
                    aux = aux->right;
                }
            }
        }
    }
}

// find
template<class T>
bool BST<T>::find(T data) {
    // Creamos un nodo auxiliara que apunte a root
    Node<T>* aux = root;
    // Recorremos el arbol hasta encontrar el dato
    while (aux != nullptr) {
        // Validamos si el dato a buscar es igual al dato de auxiliar
        if (data == aux->data) {
            // regresamos true para decir que si lo encontramos
            return true;
        } else {
            // if (data < aux->data) {
            //     // Recorremos el auxiliar a la izquierda
            //     aux = aux->left;
            // } else {
            //     // Recorremos el auxiliar a la derecho
            //     aux = aux->right;
            // }
            // Vamos a hacerlos de otra forma más sencilla
            data < aux->data ? aux = aux->left : aux = aux->right;
        }
    }
    // No encontré el dato en el BST
    return false;
}

// numero de hijos
template<class T>
int BST<T>::numChildren(Node<T>* aux) {
    if (aux->left == nullptr && aux->right == nullptr) {
        return 0; // 0 hijos
    } else {
        if (aux->left != nullptr && aux->right != nullptr) {
            return 2; // 2 hijos
        } else {
            return 1; // 1 hijo
        }
    }
}
template<class T>
Node<T>* BST<T>::predecesor(Node<T>* aux){
  aux = aux->left;
  while (aux->right!= nullptr){
    aux= aux->right;
  }
  return aux;
}
//borrar
template<class T>
void BST<T>::borrar(T data) {
  Node<T>* aux = root;
  Node<T>* father = aux;
  while (aux->data != data){
    father = aux;
    if (data < aux->data){
      aux = aux->left;}
    else{
      aux = aux->right;
    }
  }//while
  if (aux==root){
    switch (numChildren(aux)) {
      case 0: 
              delete aux;
              root = nullptr;
              break; 
      case 1: if (aux->left!=nullptr)
                  root = aux->left;
              else
                  root = aux->right;
              delete aux;
              break;
      case 2: // Node<T>* pred = predecesor(aux);
              Node<T>* pred = aux->left;
              int level = 0;
              while (pred->right!= nullptr){
                    father = pred;
                    pred= pred->right;
                    level++;
              }
              aux->data = pred->data;
              if (level == 0) {
                  father->left = pred->left;
              } else {
                  father->right = pred->left;
              }
              delete pred;
      }
  }else{
  if (aux->data == data){
    switch (numChildren(aux)) {
      case 0: if (father->left == aux)
                  father->left = nullptr;
              else father->right = nullptr;
                delete aux;
                break;
      case 1: if (aux->left!=nullptr){
                  if (father->left == aux){
                      father->left = aux->left;
                  }else{
                    father->right = aux->left;}
              }else {
                  if (father->left == aux){
                      father->left = aux->right;
                  }else{
                    father->right = aux->right;}
              }
              delete aux;
              break;
      case 2: Node<T>* pred = predecesor(aux);
              T datoTemp = pred->data;
              borrar(pred->data);
              aux->data = datoTemp;
      }
  }
  }
}

// remove
template<class T>
void BST<T>::remove(T data) {
    // Creamos apuntador auxiliar que apunta a root
    Node<T>* aux = root;
    // Validamos si el dato que vamos a borrar esta en root
    if (data == aux->data) {
        // Revisamos cuantos hijos tiene
        switch (numChildren(aux)) {
        case 0:
            // root apuntamos a nulo
            root = nullptr;
            // borramos aux
            delete aux;
            break;
        case 1: 
            // apuntamos root al hijo correspondiente
            aux->left != nullptr ? root = aux->left : root = aux->right;
            // borramos aux
            delete aux;
            break;
        case 2:       
            // Creamos un apuntador auxiliar 2 que apunta al hijo del lado izquierdo de aux
            Node<T>* aux2 = aux->left;
            // Validamos si el lado derecho del hijo del lado izquierdo apunta a nulo
            if (aux2->right == nullptr) {
                // aux2 es el hijo más grandel del laso izquierdo
                // Cambiamos el valor de aux al valor de aux 2
                aux->data = aux2->data;
                // Apuntamos aux->left a aux2->left sin importar que no tenga hijos
                aux->left = aux2->left;
                // Borramos aux2
                delete aux2;
            } else {
                // Buscamos el hijo mayor del lado izquierdo
                // creamos un apuntador auxiliar apuntando a aux2;
                Node<T>* father = aux2;
                // recorremos aux2 
                aux2 = aux2->right;
                while (aux2->right != nullptr) {
                    // Recorremos los apuntadores
                    father = aux2;
                    aux2 = aux2->right;
                }
                // Cambiamos el valor de aux por el valor de aux2
                aux->data = aux2->data; 
                // Apntamos el apuntador del lado derecho del papá al lado izquierdo de aux2
                father->right = aux2->left;
                // borramos aux2
                delete aux2;
            }
            break;
        }
    } else { 
        // Vamos a buscar el nodo a borrar
        // Creamos un apuntador auxiliar que apunte al papa de aux
        Node<T>* father = aux;
        // Recorremos aux
        data < aux->data ? aux = aux->left : aux = aux->right;
        // Recorremos el arbol para buscar el data
        while (aux != nullptr) {
            // Validamos si el dato a borrar es aux->data
            if (data == aux->data) {
                // Borramos aux
                switch (numChildren(aux)) {
                case 0:
                    // apuntamos el lado correspondiente de aux a nulo
                    data < father->data ? father->left = nullptr : father->right = nullptr;
                    // Borramos aux
                    delete aux;
                    break;
                case 1:
                    // apuntamos el lado correspondiente de aux al hijo
                    if (aux->left != nullptr) {
                        data < father->data ? father->left = aux->left : father->right = aux->left;
                    } else {
                        data < father->data ? father->left = aux->right : father->right = aux->right;
                    }
                    // borramos aux
                    delete aux;
                    break;
                case 2:
                    // Creamos un apuntador auxiliar 2 que apunta al hijo del lado izquierdo de aux
                    Node<T>* aux2 = aux->left;
                    // Validamos si el lado derecho del hijo del lado izquierdo apunta a nulo
                    if (aux2->right == nullptr) {
                        // aux2 es el hijo más grandel del laso izquierdo
                        // Cambiamos el valor de aux al valor de aux 2
                        aux->data = aux2->data;
                        // Apuntamos aux->left a aux2->left sin importar que no tenga hijos
                        aux->left = aux2->left;
                        // Borramos aux2
                        delete aux2;
                    } else {
                        // Buscamos el hijo mayor del lado izquierdo
                        // creamos un apuntador auxiliar apuntando a aux2;
                        Node<T>* father = aux2;
                        // recorremos aux2 
                        aux2 = aux2->right;
                        while (aux2->right != nullptr) {
                            // Recorremos los apuntadores
                            father = aux2;
                            aux2 = aux2->right;
                        }
                        // Cambiamos el valor de aux por el valor de aux2
                        aux->data = aux2->data; 
                        // Apntamos el apuntador del lado derecho del papá al lado izquierdo de aux2
                        father->right = aux2->left;
                        // borramos aux2
                        delete aux2;
                    }
                    break;
                }
                aux = nullptr;
            } else {
                // Recorremos los apuntadores
                father = aux;
                data < aux->data ? aux = aux->left : aux = aux->right;
            }
        }
    }
}


template<class T>
void BST<T>::printTree(Node<T>* aux, int level) {
    if (aux != NULL) {
        printTree(aux->right,level+1);
        for (int i=0;i<level;i++) {
            cout << "  ";
        }
        cout << aux->data << endl;
        printTree(aux->left,level+1);
    }
}

template<class T>
void BST<T>::print() {
    if (!isEmpty()) {
        int level = 0;
        cout << endl;
        printTree(root, level);
        cout << endl;
    } else {
        cout << endl << "The BST is empty" << endl << endl;
    }
}

template<class T>
bool BST<T>::isEmpty() {
    return root == nullptr;
}

#endif