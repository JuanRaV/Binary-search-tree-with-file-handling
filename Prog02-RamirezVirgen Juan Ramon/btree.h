#ifndef BTREE_H_INCLUDED
#define BTREE_H_INCLUDED

#include <exception>
#include <iomanip>
#include <iostream>
#include<fstream>
#include<cstring>

#include "student.h"

template <class T>
class BTree {
    private:
        class Node {
            public:
                Node();
                Node( T&);
                ~Node();

                Node* left;
                Node* right;


                T* dataPtr;

                T& getData();

                void setData(T& e);

                class Exception : public std::exception {
                    private:
                        std::string msg;
                    public:
                        explicit Exception (const char* message) : msg(message) { }
                        explicit Exception (const std::string& message) : msg(message) { }
                        virtual ~Exception () throw () { }
                        virtual const char* what () const throw() {
                            return msg.c_str();
                            }
                    };


            };


    public:
        typedef Node* Position;
    private:
        Position root;

        void copyAll(Position& r, Position& cr);
        void deleteAll();

        void insertData(Position&, T&);
        void deleteData(Position&, T& e);

        Position& findData(Position&,  T&);
        bool searchNode(Position&, int);

        Position& getLowest(Position&);
        Position& getHighest(Position&);

        void parsePreOrder(Position&);
        void parseInOrder(Position&);
        void parsePostOrder(Position&);



    public:
        class Exception : public std::exception {
            private:
                std::string msg;
            public:
                explicit Exception (const char* message) : msg(message) { }
                explicit Exception (const std::string& message) : msg(message) { }
                virtual ~Exception () throw () { }
                virtual const char* what () const throw() {
                    return msg.c_str();
                    }
            };

        BTree();
        BTree(const BTree&);

        ~BTree();

        bool isEmpty();

        void insertData( T&);
        void deleteData(T& e);
        void deleteNode(Position&);
        T retrieve(Position&);
        bool searchNode(int);

        int getHeight(Position&);

        Position& findData(T&);

        Position& getLowest();
        Position& getHighest();

        bool isLeaf(Position&);

        int getHeight();

        void save(Student);
        void save2(Student);
        void cargar();

        void parsePreOrder();
        void parseInOrder();
        void parsePostOrder();

        int getHeightLeft();
        int getHeightRight();

        void deleteAll(Position&);

        BTree& operator = (const BTree&);

    };

///Implementacion

///Nodo
template <class T>
BTree<T>::Node::Node() : dataPtr(nullptr), left(nullptr), right(nullptr) {
    }

template <class T>
BTree<T>::Node::Node( T& e) : dataPtr(new T(e)), left(nullptr), right(nullptr) {
    if(dataPtr == nullptr)
        throw Exception("Memoria no disponible, inicializar Nodo");
    }

template <class T>
BTree<T>::Node::~Node() {
    delete dataPtr;
    }

    template <class T>
T& BTree<T>::Node::getData() {
    if(dataPtr == nullptr)
        throw Exception("Dato inexistente, getData");

    return *dataPtr;
    }

template <class T>
void BTree<T>::Node::setData(T& e) {
    if(dataPtr == nullptr){
        if((dataPtr= new T(e)) == nullptr)
            throw Exception("Dato inexistente, getData");
    }else
         *dataPtr=e;
    }

template <class T>
void BTree<T>::save(Student s){
    fstream File;

    File.open("file01.txt",ios::app);
    File<<s.getCode();
    File<<"|";
    File<<s.getName();
    File<<"|";
    File<<s.getDegree();

    File<<"*";
    File.close();
}

template <class T>
void BTree<T>::cargar(){
ifstream file( "file01.txt", ios::in | ios::binary);

 /// sale del programa si ifstream no pudo abrir el archivo
 /// Verifica que se haya abierto bien el archivo
 if ( !file.is_open() )
 {
 cerr << "No se pudo abrir el archivo" << endl;
 exit( EXIT_FAILURE );
 } // fin de if

 int code;
 string name;
 string degree;

 cout << left << setw( 10 ) << "Code" << setw( 13 )
 << "Name" << "   Degree" << endl << fixed << showpoint;
 cout<<"------------------------------------"<<endl;
/// seekg desplazamiento en el archivo "handle"   end, beg(inning) cur(rent)
 file.seekg(0,file.end);
 int length=file.tellg();
 //cout<<length;  /// despliga en tamaño de lectura
 file.seekg(0,file.beg);

 /// crea un buffer para recupera todo la informacion en formato binario
 char *buffer = new char [length];
 file.read (buffer,length);

 /// convertimos nuestro buffer en formato flujo de cadena stringstream

 string registro;
 string campo;
 bool flag=true;

 stringstream ss(buffer);
  /// recupera registro a registro de nuestro SS
  /// se puede usar una bandera o verificamos que los caracteres extraidos no sin imprimibles
Student s;
while(getline(ss,registro,'*') and  ss.eofbit and flag)//and flag)
  {
       stringstream ss_reg(registro);
       /// en caso de no conocer cuantos registro se usa este ciclo y se puede hacer un try catch para
       ///  cuidar las conversiones en caso de ser necesarias
      /* while( getline(ss_reg,campo,'|'))
       {
         cout<<campo<<" ";
       }*/

        try{
            getline(ss_reg,campo,'|');
            code=stoi(campo);
            s.setCode(code);
            getline(ss_reg,campo,'|');
            name=campo;
            s.setName(name);
            getline(ss_reg,campo,'|');
            degree=campo;
             s.setDegree(degree);
             insertData(s);
        cout << left << setw( 10 ) << code << setw( 13 ) << name
        << setw( 7 ) << setprecision( 2 ) << right << degree << endl;
            /*
            Se puede evitar con ss.eofbit
            Cuando da lectura a los utimos caracteres no imprimibles como un registro, arroja un error
            el cual tiene que estar cuidado con un try catch  y activar la bandera para que no leea mas
            caracteres de nuestro ss o ss_reg
            */
         } catch (invalid_argument const &e) {
                  //cout << "Bad input: std::invalid_argument thrown" << endl;
                  flag=false;
                  }
           catch (out_of_range const &e) {
                  //cout << "Integer overflow: std::out_of_range thrown" <<endl;
                  flag=false;
                  }
        fflush(stdin);
     }
      system("pause");
    fflush(stdin);
}
///Arból
template <class T>
BTree<T>::BTree() : root(nullptr) {}

template <class T>
BTree<T>::BTree(const BTree& t) : root(nullptr) {
    copyAll(t);
    }
template <class T>
BTree<T>::~BTree() {
    deleteAll(root);
    }


template <class T>
void BTree<T>::deleteAll(Position& r) {
    if(r==nullptr)
        return;
    deleteAll(r->left);
    deleteAll(r->right);
    delete r;
    }

template <class T>
void BTree<T>::copyAll(Position& r, Position& cr) {
    if(cr != nullptr){
        r= new Node(cr->getData());
        copyAll(r->left,cr->left);
        copyAll(r->right,cr->right);
    }
}

template <class T>
bool BTree<T>::isEmpty() {
    return root == nullptr;
    }

template <class T>
void BTree<T>::insertData(T& e) {
    insertData(root,e);
    }

template <class T>
void BTree<T>::insertData(Position& r,  T& e) {
    if(r==nullptr) {
        try {
            if((r=new Node(e))==nullptr)
                throw Exception("Memoria no disponilbe, insertData");
            }
        catch(typename Node::Exception ex) {
            throw Exception(ex.what());
            }
        }
    else {
        if(e < r->getData())
            insertData(r->left,e);
        else
            insertData(r->right,e);
        }
    }
template <class T>
void BTree<T>::deleteData(T& e) {
    deleteData(root,e);
    }


template <class T>
void BTree<T>::deleteData(Position& r, T& e) {
    if(r== nullptr)
        return;

    if(r->getData() == e){///hoja
        if(isLeaf(r)){
            delete r;
            r=nullptr;
            return;
        }
    if(r->left == nullptr or r->right == nullptr){///1 hijo
        Position aux(r);

        if(r->left == nullptr)
            r=r->right;

        r=r->left;

        delete aux;
        return;
    }///2 hijos

    T sustitution(getHighest(r->left)->getData());

    r->setData(sustitution);

    deleteData(r->left,sustitution);

    }
    else{
        if(e < r->getData())
            deleteData(r->left,e);
        else
            deleteData(r->right,e);
    }

    }

template <class T>
typename BTree<T>::Position& BTree<T>::findData(T& e) {
    return findData(root,e);
    }

template <class T>
typename BTree<T>::Position& BTree<T>::findData(Position& r,  T& e) {
    if(r==nullptr or r->getData() == e)
        return r;

    if(e < r->getData())
        return findData(r->left,e);

    return findData(r->right,e);
    }

template <class T>
typename BTree<T>::Position& BTree<T>::getLowest() {
    return getLowest(root);
    }

template <class T>
typename BTree<T>::Position& BTree<T>::getLowest(Position& r) {
    if(r==nullptr or r->left==nullptr)
        return r;

    return getLowest(r->left);
    }
template <class T>

typename BTree<T>::Position& BTree<T>::getHighest() {
    return getHighest(root);
    }

template <class T>
typename BTree<T>::Position& BTree<T>::getHighest(Position& r) {
    if(r==nullptr or r->right==nullptr)
        return r;

    return getHighest(r->right);

    }

template <class T>
bool BTree<T>::isLeaf(Position& r) {
    return r != nullptr and r->left == r->right;
    }

template <class T>
int BTree<T>::getHeight() {
    return getHeight(root);
    }

template <class T>
int BTree<T>::getHeight(Position& r) {
    if(r==nullptr)
        return 0;

    int lH(getHeight(r->left));
    int rH(getHeight(r->right));

    return(lH > rH ? lH : rH)+1;
    }
/// pre-order
template <class T>
void BTree<T>::parsePreOrder() {
    parsePreOrder(root);
    }

template <class T>
void BTree<T>::parsePreOrder(Position& r) {
    Student s;
    if(r==nullptr)
        return;

    std::cout<<r->getData()<<", ";
    parsePreOrder(r->left);
    parsePreOrder(r->right);
    }
///in-order
template <class T>
void BTree<T>::parseInOrder() {
    parseInOrder(root);
    }

template <class T>
void BTree<T>::parseInOrder(Position& r) {
    if(r==nullptr)
        return;

    parseInOrder(r->left);
    std::cout << r->getData() << ", ";
    parseInOrder(r->right);
    }
/// post-order
template <class T>
void BTree<T>::parsePostOrder() {
    parsePostOrder(root);
    }

template <class T>
void BTree<T>::parsePostOrder(Position& r) {
    if(r==nullptr)
        return;
    parsePostOrder(r->left);
    parsePostOrder(r->right);
    std::cout<<r->getData()<<", ";

}

template <class T>
T BTree<T>::retrieve(Position& r) {


    return  r->getData();;
    }

template <class T>
bool BTree<T>::searchNode(int code)
{
    return searchNode(root,code);
}
template <class T>
bool BTree<T>::searchNode(Position& r,int code)
{

    if(!r)
        return false;
    else if(r->getData().getCode() == code)
        return true;
    else if(r->getData().getCode() < code)
        return searchNode(r->right,code);
    else
        return searchNode(r->left,code);
}





template <class T>
int BTree<T>::getHeightLeft() {
    return getHeight(root->left);
}

template <class T>
int BTree<T>::getHeightRight() {
    return getHeight(root->right);
}


template <class T>
BTree<T>& BTree<T>::operator=(const BTree& t) {
    deleteAll(root);
    copyAll(t);

    return *this;
    }


#endif // BTREE_H_INCLUDED
