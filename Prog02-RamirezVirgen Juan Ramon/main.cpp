

#include <iostream>
#include "btree.h"
#include "student.h"
using namespace std;



int main() {
    BTree<Student> myTree;
    Student s ;
    int opc,id;
    string name,degree;

    do{
        system("cls");
        cout<<"==MENU ABB==\n1.-Insert\n2.-Delete by price\n3.-Search Node"<<endl;
        cout<<"4.-InOrder\n5.-PreOrder\n6.-PostOrden\n7.-Recuperar\n8.-Extit"<<endl;cin>>opc;
        system("cls");

        switch(opc){
        case 1:
            cout<<"--INSERT--"<<endl;
            cout<<"Write a code: ";cin>>id;
            s.setCode(id);
            cout<<"Write a name: ";cin>>name;
            s.setName(name);
            cout<<"Write a degree: ";cin>>degree;
            s.setDegree(degree);
            myTree.insertData(s);
            myTree.save(s);
            break;
        case 2:
            cout<<"--DELETE BY CODE--"<<endl;
            cout<<"Write a code: ";cin>>id;
            s.setCode(id);
            myTree.deleteData(s);
            break;
        case 3:
            cout<<"--SEARCH--"<<endl;
            cout<<"Write a code: ";cin>>id;
            cout <<boolalpha<<myTree.searchNode(id)<<endl;
            system("pause");
            break;
        case 4:
            cout<<"--InOrder--"<<endl;
            myTree.parseInOrder();
            cout<<endl;
            system("pause");
            break;
        case 5:
            cout<<"--PreOrder--"<<endl;
            myTree.parsePreOrder();
            cout<<endl;
            system("pause");
            break;
        case 6:
            cout<<"--PostOrder--"<<endl;
            myTree.parsePostOrder();
            cout<<endl;
            system("pause");
            break;
        case 7:
            myTree.cargar();
            break;
        }
    }while(opc!=8);

    return 0;

    }



