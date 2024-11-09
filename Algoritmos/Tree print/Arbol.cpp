#include <iostream>
#include <queue>
#include <list>
#include <math.h>
#include <string>
#include <fstream>

int cifras_necesarias(int num) {
    std::string aux;
    aux = std::to_string(num);
    return 4 - aux.size();
}

template <class T>
struct CBinTreeNode
{
    CBinTreeNode(T v)
    {
        value = v;
        nodes[0] = nodes[1] = 0;
    }
    T value;
    CBinTreeNode<T>* nodes[2]; //0 left, 1 right
};

template <class T>
class CBinTree
{
public:
    CBinTree();
    ~CBinTree();
    std::ofstream r;
    CBinTreeNode<T>* Root();
    bool Find(T x, CBinTreeNode<T>**& p);
    bool Ins(T x);
    bool Rem(T x);
    CBinTreeNode<T>** Rep(CBinTreeNode<T>** p);
    void printLevelOrderV(CBinTreeNode<T>* n);
    void printLevelOrderVInv(CBinTreeNode<T>* n);
    void printLevelOrderH(CBinTreeNode<T>* n, int level);
    void printLevelOrderHInv(CBinTreeNode<T>* n, int level);
    int MaxDepth(CBinTreeNode<T>* n);
    void Print();
    void pspace(int n) {
        for (int i = 0; i < n; i++) r << "    ";
    }

    void pline(int n) {
        for (int i = 0; i < n; i++) r << "____";
    }


private:
    CBinTreeNode<T>* root;
    bool brep;
};

template <class T>
CBinTree<T>::CBinTree()
{
    root = 0;
    brep = 0;
    r.open("resultados.txt");
}

template <class T>
CBinTree<T>::~CBinTree()
{
    //...
}

template <class T>
CBinTreeNode<T>* CBinTree<T>::Root()
{
    return root;
}

template <class T>
bool CBinTree<T>::Find(T x, CBinTreeNode<T>**& p)
{
    for (p = &root;
        *p && (*p)->value != x;
        p = &((*p)->nodes[(*p)->value < x])
        );
    return *p != 0;
}

template <class T>
bool CBinTree<T>::Ins(T x)
{
    CBinTreeNode<T>** p;
    if (Find(x, p)) return 0;
    *p = new CBinTreeNode<T>(x);
    return 1;
}

template <class T>
bool CBinTree<T>::Rem(T x)
{
    CBinTreeNode<T>** p;
    if (!Find(x, p)) return 0;
    if ((*p)->nodes[0] && (*p)->nodes[1])
    {
        CBinTreeNode<T>** q = Rep(p);
        (*p)->value = (*q)->value;
        p = q;
    }
    CBinTreeNode<T>* t = *p;
    *p = (*p)->nodes[(*p)->nodes[1] != 0];
    delete t;
    return 1;
}

template <class T>
CBinTreeNode<T>** CBinTree<T>::Rep(CBinTreeNode<T>** p)
{
    CBinTreeNode<T>** q;
    for (q = &(*p)->nodes[!brep];
        (*q)->nodes[brep];
        q = &(*q)->nodes[brep]);
    brep = !brep;
    return q;
}

template <class T>
void CBinTree<T>::printLevelOrderV(CBinTreeNode<T>* n) {
    if (!root) return;
    int profundidad = MaxDepth(root), cantidad = pow(2, profundidad);
    CBinTreeNode<T>* vacio = new CBinTreeNode<T>(-1);
    std::queue< CBinTreeNode<T>* > q;
    std::queue<T> aux, prev;
    q.push(root);

    for (int x = 0; x < cantidad; x++) {
        aux.push(q.front()->value);
        if (q.front()->nodes[0] && q.front()->value != -1) q.push(q.front()->nodes[0]);
        else q.push(vacio);
        if (q.front()->nodes[1] && q.front()->value != -1) q.push(q.front()->nodes[1]);
        else  q.push(vacio);
        q.pop();
    }

    int x = 0, level = 1;
    prev = aux;
    prev.pop();

    while (x < profundidad) {
        for (int y = 0; y < level; y++) {
            if (level > 1) {
                pspace(cantidad);
                if (y % 2 == 0 && prev.front() != -1) r << " || ";
                else if (prev.front() != -1) r << " || ";
                else r << "    ";
                prev.pop();
                pspace(cantidad - 1);;
            }
        }
        r << std::endl;
        for (int y = 0; y < level; y++) {
            if (level == 1) {
                pspace(cantidad / 2);
                pline(cantidad / 2);
                for (int cifras = 0; cifras < cifras_necesarias(aux.front()); cifras++) r << 0;
                r << aux.front();
                pline(cantidad / 2);
                pspace(cantidad / 2);
            }
            else if (aux.front() != -1)
            {
                pspace(cantidad / 2);
                pline(cantidad / 2);
                for (int cifras = 0; cifras < cifras_necesarias(aux.front()); cifras++)r << 0;
                r << aux.front();
                pline(cantidad / 2);
                pspace(cantidad / 2 - 1);
            }
            else
            {
                pspace(cantidad);
                r << "    ";
                pspace(cantidad - 1);
            }
            aux.pop();
        }
        r << std::endl;
        level = level * 2;
        x++;
        cantidad = cantidad / 2;
    }
    r << std::endl;
}

template <class T>
void CBinTree<T>::printLevelOrderVInv(CBinTreeNode<T>* n) {
    if (!root) return;
    int profundidad = MaxDepth(root), cantidad = pow(2, profundidad);
    CBinTreeNode<T>* vacio = new CBinTreeNode<T>(-1);
    std::queue< CBinTreeNode<T>* > q;
    std::list< T > aux, prev;
    q.push(root);

    for (int x = 0; x < cantidad; x++) {
        aux.push_back(q.front()->value);
        if (q.front()->nodes[0] && q.front()->value != -1) q.push(q.front()->nodes[0]);
        else q.push(vacio);
        if (q.front()->nodes[1] && q.front()->value != -1) q.push(q.front()->nodes[1]);
        else  q.push(vacio);
        q.pop();
    }

    int x = 0, espacio = 2, level = pow(2, profundidad - 1);
    aux.pop_back();
    prev = aux;

    while (x < profundidad) {
        for (int i = 0; i < level; i++) {
            if (level == 1) {
                pspace(espacio / 2);
                pline(espacio / 2);
                for (int j = 0; j < cifras_necesarias(aux.back()); j++) r << 0;
                r << aux.back();
                pline(espacio / 2);
                pspace(espacio / 2);
            }
            else if (aux.back() != -1)
            {
                pspace(espacio / 2);
                pline(espacio / 2);
                for (int j = 0; j < cifras_necesarias(aux.back()); j++) r << 0;
                r << aux.back();
                pline(espacio / 2);
                pspace(espacio / 2 - 1);

            }
            else
            {
                pspace(espacio);
                pspace(espacio);
            }
            aux.pop_back();
        }
        r << std::endl;
        for (int i = 0; i < level; i++)
        {
            if (level > 1)
            {
                pspace(espacio);
                if (i % 2 == 0 && prev.back() != -1) r << " || ";
                else if (prev.back() != -1) r << " || ";
                else r << "    ";
                pspace(espacio - 1);
                prev.pop_back();
            }
        }
        r << std::endl;
        level = level / 2;
        x++;
        espacio = espacio * 2;
    }
    r << std::endl;
}

template <class T>
void CBinTree<T>::printLevelOrderH(CBinTreeNode<T>* n, int level) {
    if (!n) return;
    printLevelOrderH(n->nodes[1], level + 1);
    for (int i = 0; i < level; i++) {
        if (level - i == 1 && level != 0) {
            r << " |-";
        }
        else {
            r << "  ";
        }
    }
    for (int i = 0; i < cifras_necesarias(n->value); i++) r << 0;
    r << n->value << std::endl;
    printLevelOrderH(n->nodes[0], level + 1);

}
template <class T>
void CBinTree<T>::printLevelOrderHInv(CBinTreeNode<T>* n, int level) {
    if (!n) return;
    printLevelOrderHInv(n->nodes[1], level - 1);
    for (int i = 0; i < level; i++) r << "  ";
    for (int i = 0; i < cifras_necesarias(n->value); i++) r << 0;
    r << n->value;
    if (level != MaxDepth(root))r << "-|";
    r << std::endl;
    printLevelOrderHInv(n->nodes[0], level - 1);
}

template <class T>
int CBinTree<T>::MaxDepth(CBinTreeNode<T>* n)
{
    if (!n) return 0;
    return std::max(MaxDepth(n->nodes[0]), MaxDepth(n->nodes[1])) + 1;
}

template <class T>
void CBinTree<T>::Print()
{
    InOrder(root);
    r << "\n";
}



int main()
{
    CBinTree<int> t;
    t.Ins(51);
    t.Ins(40);
    t.Ins(80);
    t.Ins(30);
    t.Ins(40);
    t.Ins(60);
    t.Ins(59);
    t.Ins(90);
    t.Ins(20);
    t.Ins(30);
    t.Ins(70);
    t.Ins(90);
    t.Ins(900);

    t.r << "Impresion por niveles en horizontal" << "\n";
    t.printLevelOrderH(t.Root(), 0);
    t.r << "Impresion por niveles en horizontal invertido" << "\n";
    t.printLevelOrderHInv(t.Root(), t.MaxDepth(t.Root()));
    t.r << "Impresion por niveles en vertical invertido" << "\n";
    t.printLevelOrderV(t.Root());
    t.r << "Impresion por niveles en vertical invertido" << "\n";
    t.printLevelOrderVInv(t.Root());

}
