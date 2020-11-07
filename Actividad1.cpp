#include <iostream>
using namespace std;

struct node{
    float data;
    node *next;
    node *prev;
};

//declarar funciones
void printList(node *list);
void insertStart(node *&list, float new_data);
void insertEnd(node *&list, float new_data);
void insertPosition(node *&list, float new_data, int pos);
void higherRepeated(node *list);
void addElements(node *list);
void orderList(node *list);
void deleteIterative (node *&list,float delete_data);
void deletePosition(node *&list, int pos);
void deleteRecursive(node *&list, node *&aux, float delete_data);
void emptyList(node *&list);
void reverseList(node *&list);
void swapElements(node *&list, int first, int second);

//implementar funciones
void printList(node *list){
    node *aux = list;

    if (list == NULL){
        cout<<"La lista esta vacia."<<endl;
        return;
    }

    do {
        cout << aux->data << " -> ";
        aux = aux->next;
    } while (aux != list);
}
void insertStart(node *&list, float new_data){
    node *new_node = new node();
    new_node->data=new_data;

    if (list == NULL) {
        list = new_node;
        new_node->next = list;
        new_node->prev = list;
        return;
    }

    node *last = list->prev;

    new_node->next = list;
    new_node->prev = last;
    last->next = new_node;
    list->prev = new_node;
    list = new_node;
}
void insertEnd(node *&list, float new_data){
    node *new_node = new node();
    new_node->data=new_data;

    if (list == NULL) {
        list = new_node;
        new_node->next = list;
        new_node->prev = list;
        return;
    }

    node *last = list->prev;

    new_node->next = list;
    list->prev = new_node;
    new_node->prev = last;
    last->next = new_node;
}
void insertPosition(node *&list, float new_data, int pos) {
    node *actual = list;
    node *anterior = NULL;
    int bpos = 1;

    if (list == NULL) {
        cout << "La lista está vacía" << endl;
        return;
    }

    if (pos == 1) {
        cout << "En la posicion " << pos << " esta " << actual->data;
        insertStart(list, new_data);
        cout<<"El dato ha sido introducido correctamente en la posicion indicada."<<endl;
        return;
    }

    do {
        bpos++;
        anterior = actual;
        actual = actual->next;
    } while (actual != list && bpos != pos);

    if (bpos != pos) {
        cout << "La posicion indicada no esta en la lista" << endl;
    } else {
        node *aux = new node();
        aux->data=new_data;
        if (bpos == pos) {
            anterior->next = aux;
            aux->prev = anterior;
            aux->next = actual;
            anterior = aux;
            actual->prev = anterior;
        }
        cout<<"El dato ha sido introducido correctamente en la posicion insertado."<<endl;
    }
}
void higherRepeated(node *list){
    node *aux=list;
    float higher=0;
    int rep = 0;

    if(list==NULL){
        cout<<"La lista esta vacia. "<<endl;
        return;
    }

    do{
        if((list->data)>higher){
            higher=list->data;
        }
        list=list->next;
    }while(aux!=list);
    do{
        if(higher==list->data){
            rep++;
        }
        list=list->next;
    }while(aux!=list);

    cout<<"El mayor elemento es: "<<higher<<endl;
    cout<<"Este dato se repite "<<rep<<" veces. "<<endl;
}
void addElements(node *list){
    float sum = 0;
    node *aux = list;

    if (list == NULL) {
        cout << "La lista esta vacia." << endl;
        cout << "La suma de todos los elementos de la lista es: 0" << endl;
        return;
    }

    do {
        sum = sum + list->data;
        list = list->next;
    } while (aux != list);

    cout << "La suma de todos los elementos de la lista es: " << sum << endl;
}
void orderList(node *list){
    node *aux = list;

    if (list == NULL){
        cout << "La lista esta vacia." << endl;
        return;
    }

    if (list->next == list && list->prev == list){
        cout << "La lista solo tiene un elemento." << endl;
        return;
    }

    if (aux->data > aux->next->data){
        do{
            aux = aux->next;
        }while(aux != list && aux->data > aux->next->data);
        if(aux->next == list){
            cout<<"la lista esta ordenada"<<endl;
            return;
        }
        cout<<"la lista no esta ordenada"<<endl;
        return;
    }

    cout<<"La lista esta desordenada."<<endl;
}
void deleteIterative (node *&list,float delete_data){
    node *aux = list;

    if (list == NULL){
        cout << "La lista esta vacia." << endl;
        return;
    }

    if(list->next == list && list->prev == list){
        if(list->data == delete_data){
            delete(list);
            list=NULL;
        }else{
            cout<<"El dato no se encuentra en la lista."<<endl;
        }
        return;
    }

    node *remove;

    do{
        if(aux->data == delete_data){
            remove=aux;
            aux->prev->next=aux->next;
            aux->next->prev=aux->prev;
            if(aux==list){
                list=aux->next;
            }
            aux=aux->prev;
            delete(remove);
        }
        aux=aux->next;
    }while(aux!=list->prev);

    if(aux->data == delete_data){
        if(aux->next == aux && aux->prev == aux){
            if (list->data == delete_data) {
                delete (list);
                list = NULL;
            }
        }else{
            remove=aux;
            aux->prev->next=aux->next;
            aux->next->prev=aux->prev;
            delete(remove);
        }
    }
}
void deletePosition(node *&list, int pos){
    if(list == list->next){
        delete(list);
        list = NULL;
        return;
    }

    node *aux = list;
    for (int i = 0; i<pos; i++){
        aux = aux->next;
    }
    if (pos == 0){
        list = list->next;
    }
    aux->prev->next=aux->next;
    aux->next->prev=aux->prev;
    delete(aux);
}
void deleteRecursive(node *&list, node *&aux, float delete_data){
    if(list == NULL){
        cout<<"La lista esta vacia."<<endl;
        return;
    }

    if(aux->next != list){
        deleteRecursive(list, aux->next, delete_data);
    }
    if(aux->data == delete_data){
        deletePosition(aux, 0);
    }
}
void emptyList(node *&list){
    node *aux = list;
    node *remove;

    if(list->next == list){
        delete(list);
        return;
    }

    do{
        remove=aux;
        aux->prev->next=aux->next;
        aux->next->prev=aux->prev;
        if(aux == list){
            list=aux->next;
        }
        aux=aux->prev;
        delete(remove);
    }while(aux != list);
}
void reverseList(node *&list) {
    node *novel = NULL;

    if (list == NULL) {
        cout << "La lista esta vacia." << endl;
        return;
    }

    node *aux = list;

    do {
        insertStart(novel, aux->data);
        aux = aux->next;
    } while (aux != list);

    emptyList(list);
    list = novel;
    printList(novel);
}
void swapElements(node *&list, int first, int second){
    int lookFirst = 1;
    int lookSecond = 1;

    if(list == NULL){
        cout << "La lista esta vacia." << endl;
        return;
    }

    node *current1 = list;
    node *current2 = list;

    //buscamos el primer dato
    if (first == 1){
        cout<<"En la posicion 1 esta el dato: "<<current1->data<<endl;
    }else{
        do{
            lookFirst++;
            current1=current1->next;
        }while(current1 != list && lookFirst != first);
        if (lookFirst != first){
            cout<<"La posicion "<<first<< " no tiene ningun dato."<<endl;
            cout<<"Repita la funcion con otros datos."<<endl;
            return;
        }else{
            cout<<"En la posicion "<<first<<" esta el dato: "<<current1->data<<endl;
        }
    }

    //buscamos el segundo dato
    if (second == 1){
        cout<<"En la posicion 1 esta el dato: "<<current2->data<<endl;
    }else{
        do{
            lookSecond++;
            current2=current2->next;
        }while(current2 != list && lookSecond != second);
        if (lookSecond != second){
            cout<<"La posicion "<<second<< " no tiene ningun dato."<<endl;
            cout<<"Repita la funcion con otros datos."<<endl;
            return;
        }else{
            cout<<"En la posicion "<<second<<" esta el dato: "<<current2->data<<endl;
        }
    }

    node *aux = new node();
    //paso para intercambiar los datos
    if(lookFirst != first && lookSecond != second){
        cout<<"Imposible intercambiar datos."<<endl;
        return;
    }

    aux->data=current1->data;
    current1->data=current2->data;
    current2->data=aux->data;
    cout<<" "<<endl;
    cout<<"Los nuevos valores seran: "<<endl;
    cout<<"en la posicion "<<first<<" esta "<<current2->data<<endl;
    cout<<"en la posicion "<<second<<" esta "<<current1->data<<endl;

}


int main() {

    int op, pos, option, first, second;
    float new_data, delete_data;
    node *header = NULL;

    cout<<"------------------------------------------------------------------------------"<<endl;
    cout<<"UNIVERSIDAD EUROPEA DE MADRID      Victor Perez            profesor: Christian"<<endl;
    cout<<"------------------------------------------------------------------------------"<<endl;
    cout<<"";
    cout<<"****************************    Menu principal    ****************************"<<endl;
    cout<<"";
    cout<<"Selccione una de las opciones del menu"<<endl;
    cout<<"   1/ Mostrar la lista"<<endl;
    cout<<"   2/ Insertar un elemento al INICIO de la lista"<<endl;
    cout<<"   3/ Insertar un elemento al FINAL de la lista"<<endl;
    cout<<"   4/ Insertar un elemento en una POSICION elegida por el usuario"<<endl;
    cout<<"   5/ Calculo del MAYOR de los elementos y cuantas veces se repite"<<endl;
    cout<<"   6/ SUMA de todos los datos de la lista"<<endl;
    cout<<"   7/ Comprobar si la lista esta ORDENADA"<<endl;
    cout<<"   8/ ELIMINAR todas las OCURRENCIAS de un elemento dado en la lista"<<endl;
    cout<<"   9/ INVERTIR la lista"<<endl;
    cout<<"  10/ INTERCAMBIAR dos nodos DADOS en la lista"<<endl;
    cout<<"   0/ SALIR"<<endl;
    cout<<" "<<endl;

    do{
        cout<<"Ingrese su opcion: ";cin>>op;

        switch (op) {
            case 1:
                cout << "Monstrando elementos de la lista..." << endl;
                printList(header);
                cout << " " << endl;
                break;

            case 2:
                cout<<"Ingrese el data de tipo float que quiere introducir: ";
                cin>>new_data;
                cout << "Anadiendo elemento al inicio de la lista..." << endl;
                insertStart(header, new_data);
                cout<<"El dato " << new_data << " ha sido insertado al inicio de la lista." << endl;
                cout << " " << endl;
                break;

            case 3:
                cout<<"Ingrese el data de tipo float que quiere introducir: ";
                cin>>new_data;
                cout << "Anadiendo elemento al final de la lista..." << endl;
                insertEnd(header, new_data);
                cout<<"El dato " << new_data << " ha sido insertado al final de la lista." << endl;
                cout << " "<< endl;
                break;

            case 4:
                cout<<"Ingrese la posicion en la que quiere insertar el nodo: ";
                cin>>pos;
                cout<<"Ingrese el dato de tipo float que quiere introducir: ";
                cin>>new_data;
                cout << "Anadiendo elemento en la posicion indicada de la lista..." << endl;
                insertPosition(header, new_data, pos);
                cout << " "<< endl;
                break;

            case 5:
                cout << "Calculando cual es el mayor elemento de la lista y cuantas veces se repite..." << endl;
                higherRepeated(header);
                cout << " "<< endl;
                break;

            case 6:
                cout << "Sumando todos los elementos de lista..." << endl;
                addElements(header);
                cout << " "<< endl;
                break;

            case 7:
                cout << "Comprobando si la lista esta ordenada o no" << endl;
                orderList(header);
                cout << " "<< endl;
                break;

            case 8:
                cout<<"Elija como quiere eliminar: de forma iterativa pulse '1' o de forma recursiva pulse '2'."<<endl;
                cin>>option;
                while (option != 1 && option != 2){
                    cout<<"Datos erroneos."<<endl;
                    cout<<"Pulse 1 para eliminar de forma iterativa."<<endl;
                    cout<<"Pulse 2 para eliminar de forma iterativa."<<endl;
                    cin>>option;
                }

                cout<<"Ingrese el data que quiere eliminar de la lista: ";
                cin>>delete_data;

                if (option == 1){
                    cout << "Eliminando elementos de la lista de forma iterativa..." << endl;
                    deleteIterative (header,delete_data);
                }
                if (option == 2){
                    cout << "Eliminando elementos de la lista de forma recursiva..." << endl;
                    deleteRecursive(header, header, delete_data);
                }

                cout<<"El dato "<<delete_data<<" se ha borrado de la lista correctamente."<<endl;
                cout << " "<< endl;
                break;

            case 9:
                cout << "Invirtiendo los datos de la lista..." << endl;
                reverseList(header);
                cout<<"Ahora trabajaremos sobre la lista invertida."<<endl;
                cout << " "<< endl;
                break;

            case 10:
                cout<<"Eliga posicion del primer elemento: ";cin>>first;
                cout<<"Eliga posicion del segundo elemento: "; cin>>second;
                cout<<"Intercambiando datos de la lista..."<<endl;
                swapElements(header, first, second);
                cout << " "<< endl;
                break;

            case 0:
                cout << "Ha salido del programa. Hasta pronto.";
                emptyList(header);
                break;
        }
    }while(op!=0);
}
