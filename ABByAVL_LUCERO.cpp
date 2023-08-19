#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

struct NodoB {
    int valor;
    NodoB* izquierdo;
    NodoB* derecho;

    NodoB(int val) {
        valor = val;
        izquierdo = nullptr;
        derecho = nullptr;
    }
};

class ArbolBinario {
private:
    NodoB* raiz;

    NodoB* insertarNodoRecursivo(NodoB* nodoActual, int valor) {
        if (nodoActual == nullptr) {
            return new NodoB(valor);
        }

        if (valor < nodoActual->valor) {
            nodoActual->izquierdo = insertarNodoRecursivo(nodoActual->izquierdo, valor);
        }
        else if (valor > nodoActual->valor) {
            nodoActual->derecho = insertarNodoRecursivo(nodoActual->derecho, valor);
        }

        return nodoActual;
    }

    NodoB* buscarNodo(NodoB* nodoActual, int valor) {
        if (nodoActual == nullptr || nodoActual->valor == valor) {
            return nodoActual;
        }

        if (valor < nodoActual->valor) {
            return buscarNodo(nodoActual->izquierdo, valor);
        }
        else {
            return buscarNodo(nodoActual->derecho, valor);
        }
    }

    NodoB* encontrarNodoMinimo(NodoB* nodoActual) {
        NodoB* actual = nodoActual;
        while (actual && actual->izquierdo != nullptr) {
            actual = actual->izquierdo;
        }
        return actual;
    }

    NodoB* eliminarNodoRecursivo(NodoB* nodoActual, int valor) {
        if (nodoActual == nullptr) {
            return nodoActual;
        }

        if (valor < nodoActual->valor) {
            nodoActual->izquierdo = eliminarNodoRecursivo(nodoActual->izquierdo, valor);
        }
        else if (valor > nodoActual->valor) {
            nodoActual->derecho = eliminarNodoRecursivo(nodoActual->derecho, valor);
        }
        else {
            if (nodoActual->izquierdo == nullptr) {
                NodoB* temp = nodoActual->derecho;
                delete nodoActual;
                return temp;
            }
            else if (nodoActual->derecho == nullptr) {
                NodoB* temp = nodoActual->izquierdo;
                delete nodoActual;
                return temp;
            }

            NodoB* temp = encontrarNodoMinimo(nodoActual->derecho);
            nodoActual->valor = temp->valor;
            nodoActual->derecho = eliminarNodoRecursivo(nodoActual->derecho, temp->valor);
        }

        return nodoActual;
    }

    void calcularAlturaRecursivo(NodoB* nodoActual, int nivel, int& maxAltura) {
        if (nodoActual == nullptr) {
            return;
        }

        if (nivel > maxAltura) {
            maxAltura = nivel;
        }

        calcularAlturaRecursivo(nodoActual->izquierdo, nivel + 1, maxAltura);
        calcularAlturaRecursivo(nodoActual->derecho, nivel + 1, maxAltura);
    }

    int contarNodosRecursivo(NodoB* nodoActual) {
        if (nodoActual == nullptr) {
            return 0;
        }

        return 1 + contarNodosRecursivo(nodoActual->izquierdo) + contarNodosRecursivo(nodoActual->derecho);
    }

    void mostrarCaminoRecursivo(NodoB* nodo, int valor) {
        if (nodo == nullptr) {
            return;
        }

        cout << nodo->valor << " ";

        if (valor < nodo->valor) {
            mostrarCaminoRecursivo(nodo->izquierdo, valor);
        }
        else if (valor > nodo->valor) {
            mostrarCaminoRecursivo(nodo->derecho, valor);
        }
    }

    void mostrarEnOrdenRecursivo(NodoB* nodoActual) {
        if (nodoActual != nullptr) {
            mostrarEnOrdenRecursivo(nodoActual->izquierdo);
            cout << nodoActual->valor << " ";
            mostrarEnOrdenRecursivo(nodoActual->derecho);
        }
    }

    void mostrarPreOrdenRecursivo(NodoB* nodoActual) {
        if (nodoActual != nullptr) {
            cout << nodoActual->valor << " ";
            mostrarPreOrdenRecursivo(nodoActual->izquierdo);
            mostrarPreOrdenRecursivo(nodoActual->derecho);
        }
    }

    void mostrarPostOrdenRecursivo(NodoB* nodoActual) {
        if (nodoActual != nullptr) {
            mostrarPostOrdenRecursivo(nodoActual->izquierdo);
            mostrarPostOrdenRecursivo(nodoActual->derecho);
            cout << nodoActual->valor << " ";
        }
    }

public:
    ArbolBinario() {
        raiz = nullptr;
    }

    void insertarNodo(int valor) {
        raiz = insertarNodoRecursivo(raiz, valor);
    }

    bool buscarNodo(int valor) {
        NodoB* resultado = buscarNodo(raiz, valor);
        return resultado != nullptr;
    }

    void eliminarNodo(int valor) {
        raiz = eliminarNodoRecursivo(raiz, valor);
    }

    int calcularAltura() {
        int maxAltura = 0;
        calcularAlturaRecursivo(raiz, 0, maxAltura);
        return maxAltura;
    }

    int contarNodos() {
        return contarNodosRecursivo(raiz);
    }


    void mostrarCamino(int valor) {
        mostrarCaminoRecursivo(raiz, valor);
    }


    void mostrarEnOrden() {
        mostrarEnOrdenRecursivo(raiz);
        cout << endl;
    }

    void mostrarPreOrden() {
        mostrarPreOrdenRecursivo(raiz);
        cout << endl;
    }

    void mostrarPostOrden() {
        mostrarPostOrdenRecursivo(raiz);
        cout << endl;
    }
};

void Binario() {
    ArbolBinario arbol;
    int opcion, valor, numNodos;
    do {
        system("cls");
        cout << "                  MENU ARBOL BINARIO                  " << endl;
        cout << "------------------------------------------------------" << endl;
        cout << "1. Insertar un nuevo nodo" << endl;
        cout << "2. Eliminar nodo" << endl;
        cout << "3. Calcular altura del Arbol,Contar nodos del Arbol" << endl;
        cout << "4. Mostrar camino del nodo" << endl;
        cout << "5. Mostrar en inorden-preorden-postorden" << endl;
        cout << "6. Salir" << endl;
        cout << "------------------------------------------------------" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            cout << "Ingrese el valor del nodo a insertar: ";
            cin >> valor;
            arbol.insertarNodo(valor);
            cout << "Nodo insertado correctamente." << endl;
            system("pause");
            break;

        case 2:
            cout << "Ingrese el nodo a eliminar: ";
            cin >> valor;
            arbol.eliminarNodo(valor);
            cout << "Nodo eliminado correctamente." << endl;
            system("pause");
            break;

        case 3:
            cout << "La altura del arbol es: " << arbol.calcularAltura() << endl;
            cout << endl;
            cout << "La cantidad de nodos del arbol es: " << arbol.contarNodos() << endl;
            system("pause");
            break;
        case 4:
            int valor;
            cout << "Ingrese el valor del nodo inicial: ";
            cin >> valor;
            cout << "Camino: ";
            arbol.mostrarCamino(valor);
            cout << endl;
            system("pause");
            break;
        case 5:
            cout << "Recorrido en inorden: ";
            arbol.mostrarEnOrden();
            cout << endl;
            cout << "Recorrido en preorden: ";
            arbol.mostrarPreOrden();
            cout << endl;
            cout << "Recorrido en postorden: ";
            arbol.mostrarPostOrden();
            system("pause");
            break;
        }
    } while (opcion != 6);
}
class NodoA {
public:
    int valor;
    NodoA* izquierdo;
    NodoA* derecho;

    NodoA(int valor) {
        this->valor = valor;
        izquierdo = nullptr;
        derecho = nullptr;
    }
};

class AVL {
public:
    NodoA* raiz;

    AVL();
    void insertarNodo(int valor);
    void eliminarNodo(int valor);
    int calcularAltura();
    int contarNodos();
    void mostrarCamino(int valor);
    void mostrarInOrden();
    void mostrarPreOrden();
    void mostrarPostOrden();

private:
    NodoA* insertarNodoRecursivo(NodoA* nodo, int valor);
    NodoA* eliminarNodoRecursivo(NodoA* nodo, int valor);
    NodoA* obtenerNodoMinimo(NodoA* nodo);
    int calcularAlturaRecursivo(NodoA* nodo);
    int contarNodosRecursivo(NodoA* nodo);
    void mostrarCaminoRecursivo(NodoA* nodo, int valor);
    void mostrarInOrdenRecursivo(NodoA* nodo);
    void mostrarPreOrdenRecursivo(NodoA* nodo);
    void mostrarPostOrdenRecursivo(NodoA* nodo);
};

AVL::AVL() {
    raiz = nullptr;
}

void AVL::insertarNodo(int valor) {
    raiz = insertarNodoRecursivo(raiz, valor);
}

NodoA* AVL::insertarNodoRecursivo(NodoA* nodo, int valor) {
    if (nodo == nullptr) {
        return new NodoA(valor);
    }

    if (valor < nodo->valor) {
        nodo->izquierdo = insertarNodoRecursivo(nodo->izquierdo, valor);
    }
    else if (valor > nodo->valor) {
        nodo->derecho = insertarNodoRecursivo(nodo->derecho, valor);
    }


    int alturaIzquierdo = calcularAlturaRecursivo(nodo->izquierdo);
    int alturaDerecho = calcularAlturaRecursivo(nodo->derecho);
    int nuevaAltura = max(alturaIzquierdo, alturaDerecho) + 1;
    return nodo;
}

void AVL::eliminarNodo(int valor) {
    raiz = eliminarNodoRecursivo(raiz, valor);
}

NodoA* AVL::eliminarNodoRecursivo(NodoA* nodo, int valor) {
    if (nodo == nullptr) {
        return nodo;
    }

    if (valor < nodo->valor) {
        nodo->izquierdo = eliminarNodoRecursivo(nodo->izquierdo, valor);
    }
    else if (valor > nodo->valor) {
        nodo->derecho = eliminarNodoRecursivo(nodo->derecho, valor);
    }
    else {
        if (nodo->izquierdo == nullptr) {
            NodoA* temp = nodo->derecho;
            delete nodo;
            return temp;
        }
        else if (nodo->derecho == nullptr) {
            NodoA* temp = nodo->izquierdo;
            delete nodo;
            return temp;
        }


        NodoA* minimoDerecho = obtenerNodoMinimo(nodo->derecho);
        nodo->valor = minimoDerecho->valor;
        nodo->derecho = eliminarNodoRecursivo(nodo->derecho, minimoDerecho->valor);
    }
    return nodo;
}

NodoA* AVL::obtenerNodoMinimo(NodoA* nodo) {
    NodoA* actual = nodo;
    while (actual->izquierdo != nullptr) {
        actual = actual->izquierdo;
    }
    return actual;
}

int AVL::calcularAltura() {
    return calcularAlturaRecursivo(raiz);
}

int AVL::calcularAlturaRecursivo(NodoA* nodo) {
    if (nodo == nullptr) {
        return 0;
    }

    int alturaIzquierdo = calcularAlturaRecursivo(nodo->izquierdo);
    int alturaDerecho = calcularAlturaRecursivo(nodo->derecho);

    return max(alturaIzquierdo, alturaDerecho) + 1;
}

int AVL::contarNodos() {
    return contarNodosRecursivo(raiz);
}

int AVL::contarNodosRecursivo(NodoA* nodo) {
    if (nodo == nullptr) {
        return 0;
    }

    int nodosIzquierdo = contarNodosRecursivo(nodo->izquierdo);
    int nodosDerecho = contarNodosRecursivo(nodo->derecho);

    return nodosIzquierdo + nodosDerecho + 1;
}

void AVL::mostrarCamino(int valor) {
    mostrarCaminoRecursivo(raiz, valor);
}

void AVL::mostrarCaminoRecursivo(NodoA* nodo, int valor) {
    if (nodo == nullptr) {
        return;
    }

    cout << nodo->valor << " ";

    if (valor < nodo->valor) {
        mostrarCaminoRecursivo(nodo->izquierdo, valor);
    }
    else if (valor > nodo->valor) {
        mostrarCaminoRecursivo(nodo->derecho, valor);
    }
}

void AVL::mostrarInOrden() {
    mostrarInOrdenRecursivo(raiz);
    cout << endl;
}

void AVL::mostrarInOrdenRecursivo(NodoA* nodo) {
    if (nodo == nullptr) {
        return;
    }

    mostrarInOrdenRecursivo(nodo->izquierdo);
    cout << nodo->valor << " ";
    mostrarInOrdenRecursivo(nodo->derecho);
}

void AVL::mostrarPreOrden() {
    mostrarPreOrdenRecursivo(raiz);
    cout << endl;
}

void AVL::mostrarPreOrdenRecursivo(NodoA* nodo) {
    if (nodo == nullptr) {
        return;
    }

    cout << nodo->valor << " ";
    mostrarPreOrdenRecursivo(nodo->izquierdo);
    mostrarPreOrdenRecursivo(nodo->derecho);
}

void AVL::mostrarPostOrden() {
    mostrarPostOrdenRecursivo(raiz);
    cout << endl;
}

void AVL::mostrarPostOrdenRecursivo(NodoA* nodo) {
    if (nodo == nullptr) {
        return;
    }

    mostrarPostOrdenRecursivo(nodo->izquierdo);
    mostrarPostOrdenRecursivo(nodo->derecho);
    cout << nodo->valor << " ";
}
void ArbolAVL() {
    AVL arbol;
    int numNodos, opcion, valar;
    do {
        system("cls");
        cout << "                    MENU ARBOL AVL                    " << endl;
        cout << "------------------------------------------------------" << endl;
        cout << "1. Agregar nodo" << endl;
        cout << "2. Eliminar nodo" << endl;
        cout << "3. Altura" << endl;
        cout << "4. Cantidad de nodos" << endl;
        cout << "5. Mostrar camino del nodo" << endl;
        cout << "6. Mostrar In-Orden" << endl;
        cout << "7. Mostrar Post-Orden" << endl;
        cout << "8. Mostrar Pre-Orden" << endl;
        cout << "9. Salir" << endl;
        cout << "------------------------------------------------------" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1: {
            system("cls");
            int valor;
            cout << "Ingrese la cantidad de nodos a insertar: ";
            cin >> valar;
            system("cls");
            cout << valar << " Nodos a insertar" << endl;
            for (int i = 0; i < valar; i++)
            {
                cout << "Ingrese el valor del Nodo a insertar : ";
                cin >> valor;
                arbol.insertarNodo(valor);
            }
            system("cls");
            break;
        }
        case 2: {
            int valor;
            cout << "Ingrese el nodo a eliminar: ";
            cin >> valor;
            arbol.eliminarNodo(valor);
            system("pause");
            break;
        }
        case 3: {
            int altura = arbol.calcularAltura();
            cout << "La altura del arbol es: " << altura << endl;
            cout << endl;
            break;
        }
        case 4: {
            int cantidad = arbol.contarNodos();
            cout << "La cantidad de nodos en el arbol es: " << cantidad << std::endl;
            system("pause");
            break;
        }
        case 5: {
            int valor;
            cout << "Ingrese el valor del nodo inicial: ";
            cin >> valor;
            cout << "Camino: ";
            arbol.mostrarCamino(valor);
            cout << endl;
            system("pause");
            break;
        }
        case 6: {
            cout << "Recorrido In-Orden: ";
            arbol.mostrarInOrden();
            cout << endl;
            system("pause");
            break;
        }
        case 7: {
            cout << "Recorrido Post-Orden: ";
            arbol.mostrarPostOrden();
            cout << endl;
            system("pause");
            break;
        }
        case 8: {
            cout << "Recorrido Pre-Orden: ";
            arbol.mostrarPreOrden();
            system("pause");
            break;
        }
        }
    } while (opcion != 9);
}
int main() {
    int op;
    do {

        cout << "                 BIENVENIDO                " << endl;
        cout << "-------------------------------------------" << endl;
        cout << "| 1-Menu Arbol BINARIO                    |" << endl;
        cout << "| 2-Menu Arbol AVL                        |" << endl;
        cout << "| 3-Salir                                 |" << endl;
        cout << "-------------------------------------------" << endl;
        cout << "Ingrese su opcion: ";
        cin >> op;
        switch (op)
        {
        case 1:
            system("cls");
            Binario();
            system("cls");
            break;
        case 2:
            system("cls");
            ArbolAVL();
            system("cls");
            break;
        }
        if (op > 3) {
            system("cls");
            cout << "Opcion Invalida, por favor seleccione una opcion correcta." << endl << endl << endl;
            return 0;
        }
    } while (op != 3);
    system("cls");
    cout << "Saliendo del programa..." << endl << endl << endl;
    return 0;
}