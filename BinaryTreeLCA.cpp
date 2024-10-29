#include <iostream>
#include <queue>
#include <string>

using namespace std;

struct TreeNode {
    TreeNode* Nodes[2];
    int id_node, depth;
    int val;

    TreeNode() {
        val = 0;
        depth = 0;
        id_node = 0;
        Nodes[0] = nullptr;
        Nodes[1] = nullptr;
    }
    TreeNode(int val) {
        this->val = val;
        depth = 0;
        id_node = 0;
        Nodes[0] = nullptr;
        Nodes[1] = nullptr;
    }
    TreeNode(int val, int id_node, int depth) {
        this->val = val;
        this->id_node = id_node;
        this->depth = depth;
        Nodes[0] = nullptr;
        Nodes[1] = nullptr;
    }
};

//BINARYTREE CON ALGORITMO LCA----------------------------------
struct BinaryTree {
    int depth, nelements;
    TreeNode* root;
    //eulerian[0]=altura del nodo
    //eulerian[1]=id del nodo
    int depth_node, iterator;
    int* eulerian[2];

    BinaryTree() {
        depth = 0;
        nelements = 0;
        root = nullptr;
        depth_node=0;
        iterator = 0;
        eulerian[0] = new int[0];
        eulerian[1] = new int[0];
    }
    void insert(int val){
        int depth = 0;
        if (root == nullptr) {
            root = new TreeNode(val,nelements,depth);
            return;
        }
        depth++;
        TreeNode* Temp = root;
        bool son = (Temp->val > val) ? son = 0:son=1;
        while (Temp->Nodes[son] != nullptr) {
            depth++;
            Temp = Temp->Nodes[son];
            if (Temp->val > val)
                son = 0;
            else
                son = 1;
        }
        nelements++;
        Temp->Nodes[son] = new TreeNode(val,nelements,depth);
    }

    //llenando nuestro array de 2 filas "eulerian"
    void PreP1() {
        depth_node = 0;
        delete[] eulerian[0];
        delete[] eulerian[1];
        iterator = 0;
        eulerian[0] = new int[1+nelements * 2];
        eulerian[1] = new int[1+nelements * 2];
        PreP2(root);
    }
    void PreP2(TreeNode* n) {
        eulerian[0][iterator] = n->depth;
        eulerian[1][iterator] = n->id_node;
        iterator++;
        
        if (n->Nodes[0] != nullptr) {
            PreP2(n->Nodes[0]);
            eulerian[0][iterator] = n->depth;
            eulerian[1][iterator] = n->id_node;
            iterator++;
        }

        if (n->Nodes[1] != nullptr) {
            PreP2(n->Nodes[1]);
            eulerian[0][iterator] = n->depth;
            eulerian[1][iterator] = n->id_node;
        }
        if (n->Nodes[0] == nullptr && n->Nodes[1] == nullptr) 
            iterator--;
        
        iterator++;
        return;
    }

    TreeNode* find(int a) {
        if (root == nullptr) {
            return nullptr;
        }
        queue<TreeNode*>Q;
        Q.push(root);
        while (!Q.empty()) {
            if (Q.front()->Nodes[0] != nullptr) { Q.push(Q.front()->Nodes[0]); }
            if (Q.front()->Nodes[1] != nullptr) { Q.push(Q.front()->Nodes[1]); }

            if (Q.front()->id_node == a) {
                return Q.front();
            }
            Q.pop();
        }
    }

    TreeNode* LCA(int a, int b) {
        int min = 1000000000,min_i, minr, maxr, ai, bi;

        for (int i = 0; i < 2 * nelements + 1; i++) {
            if (a == eulerian[1][i]) {
                ai = i;
            }
            if (b == eulerian[1][i]) {
                bi = i;
            }
        }

        if (ai > bi) {
            maxr = ai;
            minr = bi;
        }
        else {
            maxr = bi;
            minr = ai;
        }

        for (int i = minr; i < maxr; i++) {
            if (min > eulerian[0][i]) {
                min_i = i;
                min = eulerian[0][i];
            }
        }
        TreeNode* Temp = find(eulerian[1][min_i]);
        cout << "\n El minimo ancestro de los nodos [" << a << "] y [";
        cout << b << "], es el nodo: [" << Temp->id_node;
        cout << "], con el valor: " << Temp->val << "\n";
        return Temp;
    }

    void print_eulerian() {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 1+nelements * 2; j++) {
                cout <<" | " << eulerian[i][j];
            }
            cout << " |\n";
        }
    }
    

    // ESTO SOLO ES EL PRINT-----------------------------------------------------------------------------------------------------
    // ESTO SOLO ES EL PRINT-----------------------------------------------------------------------------------------------------
    // ESTO SOLO ES EL PRINT-----------------------------------------------------------------------------------------------------

    int cifras_necesarias(int num) {
        std::string aux;
        aux = std::to_string(num);
        return 4 - aux.size();
    }

    void pspace(int n) {
        for (int i = 0; i < n; i++)
            cout << "    ";
    }

    void pline(int n) {
        for (int i = 0; i < n; i++)
            cout << "____";
    }

    int MaxDepth(TreeNode* n) {
        if (!n)
            return 0;
        return std::max(MaxDepth(n->Nodes[0]), MaxDepth(n->Nodes[1])) + 1;
    }

    void print() {
        if (!root)
            return;
        int profundidad = MaxDepth(root), cantidad = pow(2, profundidad);
        TreeNode* vacio = new TreeNode(-1);
        std::queue<TreeNode*> q;
        std::queue<int> aux, prev;
        q.push(root);

        for (int x = 0; x < cantidad; x++) {
            aux.push(q.front()->val);
            if (q.front()->Nodes[0] && q.front()->val != -1)
                q.push(q.front()->Nodes[0]);
            else
                q.push(vacio);
            if (q.front()->Nodes[1] && q.front()->val != -1)
                q.push(q.front()->Nodes[1]);
            else
                q.push(vacio);
            q.pop();
        }

        int x = 0, level = 1;
        prev = aux;
        prev.pop();

        while (x < profundidad) {
            for (int y = 0; y < level; y++) {
                if (level > 1) {
                    pspace(cantidad);
                    if (y % 2 == 0 && prev.front() != -1)
                        cout << " || ";
                    else if (prev.front() != -1)
                        cout << " || ";
                    else
                        cout << "    ";
                    prev.pop();
                    pspace(cantidad - 1);
                    ;
                }
            }
            cout << std::endl;
            for (int y = 0; y < level; y++) {
                if (level == 1) {
                    pspace(cantidad / 2);
                    pline(cantidad / 2);
                    for (int cifras = 0; cifras < cifras_necesarias(aux.front()); cifras++)
                        cout << 0;
                    cout << aux.front();
                    pline(cantidad / 2);
                    pspace(cantidad / 2);
                }
                else if (aux.front() != -1) {
                    pspace(cantidad / 2);
                    pline(cantidad / 2);
                    for (int cifras = 0; cifras < cifras_necesarias(aux.front()); cifras++)
                        cout << 0;
                    cout << aux.front();
                    pline(cantidad / 2);
                    pspace(cantidad / 2 - 1);
                }
                else {
                    pspace(cantidad);
                    cout << "    ";
                    pspace(cantidad - 1);
                }
                aux.pop();
            }
            cout << std::endl;
            level = level * 2;
            x++;
            cantidad = cantidad / 2;
        }
        cout << std::endl;
    }
    // ESTO SOLO ES EL PRINT-----------------------------------------------------------------------------------------------------
    // ESTO SOLO ES EL PRINT-----------------------------------------------------------------------------------------------------
    // ESTO SOLO ES EL PRINT-----------------------------------------------------------------------------------------------------
    
    ~BinaryTree() {
        delete[] eulerian[0];
        delete[] eulerian[1];
    }
};
//BINARYTREE CON ALGORITMO LCA----------------------------------

int main()
{
    BinaryTree Tree;
    Tree.insert(10);
    Tree.insert(4);
    Tree.insert(6);
    Tree.insert(20);
    Tree.insert(11);
    Tree.insert(23);
    Tree.insert(24);
    Tree.insert(22);
    Tree.print();
    Tree.PreP1();
    Tree.print_eulerian();
    Tree.LCA(4, 6);
}