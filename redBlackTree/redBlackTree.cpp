#include <iostream>
#include <string>

enum color{ BLACK, RED };

template <typename T>
struct Node {
    Node<T>* parent = nullptr;
    Node<T>* left_child = nullptr;
    Node<T>* right_child = nullptr;

    T data;
    bool color;
};

template <typename T>
struct RBT {
    Node<T>* root = nullptr;
    int size = 0;

    bool insert(T data, int (*func)(T*, T*)) {

        // Gdy RBT jest puste
        if (root == nullptr) {
            Node<T>* newNode = new Node<T>();
            newNode->data = data;
            newNode->color = BLACK;
            root = newNode;
            size++;
            return 1;
        }

        // Gdy RBT nie jest puste
        Node<T>* tmp_root = root;
        Node<T>* last_leaf = nullptr;
        while (tmp_root != nullptr) {
            last_leaf = tmp_root;

            int cmp_result = func(&data, &tmp_root->data);
            if (cmp_result == 0) {
                // Gdy istnieje już element o takim samym kluczu
                return 0;
            }
            else if (cmp_result == -1) {
                tmp_root = tmp_root->left_child;
            }
            else {
                tmp_root = tmp_root->right_child;
            }
        }

        Node<T>* newNode = new Node<T>();
        newNode->data = data;
        newNode->color = RED;

        if (func(&data, &last_leaf->data) == -1) {
            last_leaf->left_child = newNode;
        }
        else {
            last_leaf->right_child = newNode;
        }
        newNode->parent = last_leaf;

        size++;

        // Przywrócenie balansu
        Node<T>* node = newNode;
        Node<T>* uncle = nullptr;
        while (node->parent != nullptr && node->parent->color == RED) {
            if (node->parent->parent->left_child == node->parent) {
                uncle = node->parent->parent->right_child;

                if (uncle != nullptr && uncle->color == RED) {
                    uncle->color = BLACK;
                    uncle->parent->color = RED;
                    node->parent->color = BLACK;
                    node = node->parent->parent;
                }
                else {
                    if (node->parent->right_child == node) {
                        //dla rotateLeft
                        //node = node->parent;
                        //rotateLeft(node);

                        //dla rotateLeft2
                        node = node->parent;
                        rotateLeft2(node->right_child, node);
                    }

                    node->parent->parent->color = RED;
                    node->parent->color = BLACK;
                    //rotateRight(node->parent->parent);

                    rotateRight2(node->parent, node->parent->parent);

                }
            }
            else if (node->parent->parent->right_child == node->parent) {
                uncle = node->parent->parent->left_child;

                if (uncle != nullptr && uncle->color == RED) {
                    uncle->color = BLACK;
                    uncle->parent->color = RED;
                    node->parent->color = BLACK;
                    node = node->parent->parent;
                }
                else {
                    if (node->parent->left_child == node) {
                        //dla rotateRight
                        //node = node->parent;
                        //rotateRight(node);

                        //dla rotateRight2
                        node = node->parent;
                        rotateRight2(node->left_child, node);
                    }

                    node->parent->parent->color = RED;
                    node->parent->color = BLACK;

                    //rotateLeft(node->parent->parent); w zadaniu miał byc rotate z dwoma argumentami :(
                    rotateLeft2(node->parent, node->parent->parent);

                }
            }
        }


        root->color = BLACK;
        return 1;
    }

    //void rotateLeft(Node<T>* n) {
    //    Node<T>* new_parent = n->right_child;

    //    n->right_child = new_parent->left_child;

    //    if (new_parent->left_child != nullptr)
    //        new_parent->left_child->parent = n;

    //    new_parent->parent = n->parent;

    //    // Ustawienie rodzica dla węzła z którym następuje zamiana
    //    if (root == n)
    //        root = new_parent;
    //    else if (n->parent->left_child == n)
    //        n->parent->left_child = new_parent;
    //    else if (n->parent->right_child == n)
    //        n->parent->right_child = new_parent;

    //    n->parent = new_parent;
    //    new_parent->left_child = n;

    //}

    void rotateLeft2(Node<T>* child, Node<T>* par) {

        par->right_child = child->left_child;

        if (child->left_child != nullptr)
            child->left_child->parent = par;

        child->parent = par->parent;


        if (root == par)
            root = child;
        else if (par->parent->left_child == par)
            par->parent->left_child = child;
        else if (par->parent->right_child == par)
            par->parent->right_child = child;

        par->parent = child;
        child->left_child = par;

    }

    //void rotateRight(Node<T>* n) {
    //    Node<T>* new_parent = n->left_child;

    //    n->left_child = new_parent->right_child;

    //    if (new_parent->right_child != nullptr)
    //        new_parent->right_child->parent = n;

    //    new_parent->parent = n->parent;

    //    if (root == n)
    //        root = new_parent;
    //    else if (n->parent->left_child == n)
    //        n->parent->left_child = new_parent;
    //    else if (n->parent->right_child == n)
    //        n->parent->right_child = new_parent;

    //    n->parent = new_parent;
    //    new_parent->right_child = n;

    //}

    void rotateRight2(Node<T>* child, Node<T>* par) {

        par->left_child = child->right_child;

        if (child->right_child != nullptr)
            child->right_child->parent = par;

        child->parent = par->parent;

        if (root == par)
            root = child;
        else if (par->parent->left_child == par)
            par->parent->left_child = child;
        else if (par->parent->right_child == par)
            par->parent->right_child = child;

        par->parent = child;
        child->right_child = par;

    }

    Node<T>* search(T data, int (*func)(T*, T*)) {
        Node<T>* tmp = root;
        int cmp_result;
        while (tmp != nullptr && (cmp_result = func(&data, &tmp->data)) != 0) {
            if (cmp_result == -1) {
                tmp = tmp->left_child;
            }
            else {
                tmp = tmp->right_child;
            }
        }

        return tmp;
    }


    void inorderTraversal_h(Node<T>* n, Node<T>** arr) {
        if (n != nullptr) {
            inorderTraversal_h(n->left_child, arr);
            arr[traversal_index++] = n;
            inorderTraversal_h(n->right_child, arr);
        }

    }

    std::string inorderTraversal(std::string(*func)(T*)) {
        traversal_index = 0;
        Node<T>** arr = new Node<T>*[size];
        std::string s = "";

        if (root == nullptr)
            return "rbt is empty.";

        inorderTraversal_h(root, arr);

        for (int i = 0; i < size; i++) {
            s += '(' + func(&arr[i]->data) + ") ";
        }

        delete[] arr;
        return s;
    }

    void preorderTraversal_h(Node<T>* n, Node<T>** arr) {
        if (n != nullptr) {
            arr[traversal_index++] = n;
            preorderTraversal_h(n->left_child, arr);
            preorderTraversal_h(n->right_child, arr);
        }
    }

    std::string preorderTraversal(std::string(*func)(T*)) {
        traversal_index = 0;
        Node<T>** arr = new Node<T>*[size];
        std::string s = "";

        if (root == nullptr)
            return "rbt is empty.";

        preorderTraversal_h(root, arr);

        for (int i = 0; i < size; i++) {
            s += '(' + func(&arr[i]->data) + ") ";
        }

        delete[] arr;
        return s;
    }

    static int traversal_index;
    void clear() {
        traversal_index = 0;
        Node<T>** arr = new Node<T>*[size];
        preorderTraversal_h(root, arr);

        for (int i = 0; i < size; i++) {
            Node<T>* p = arr[i];
            delete p;
        }

        size = 0;
        delete[] arr;
        root = nullptr;
    }

    std::string str(std::string(*func)(T*), int n = -1) {
        traversal_index = 0;
        Node<T>** arr = new Node<T>*[size];
        std::string s = "Size: " + std::to_string(size) + "\nHeight: " + std::to_string(height_h(root)) + "\n{\n";
        preorderTraversal_h(root, arr);

        if (root == nullptr) {
            s += "\n\trbt is empty\n\n}";
            return s;
        }

        if (n == -1 || n > size) {
            n = size;
        }

        for (int i = 0; i < n; i++) {
            if (arr[i]->color == RED)
                s += "\t[ \033[31m  RED  \033[0m";
            else {
                s += "\t[ \033[30;45m BLACK \033[0m \033[0m";
            }
            //std::cout << "(" << arr[i].f1 << ' ' << arr[i].f2 << ")\n";
            s += " Node: (" + func(&arr[i]->data) + ')';
            //std::cout << &arr[i]->parent << '\n';
            if (arr[i]->parent == nullptr)
                s += " Parent: ()";
            else
                s += " Parent: (" + func(&arr[i]->parent->data) + ')';

            if (arr[i]->left_child == nullptr)
                s += " L_child: ()";
            else
                s += " L_child: (" + func(&arr[i]->left_child->data) + ')';

            if (arr[i]->right_child == nullptr)
                s += " R_child: ()";
            else
                s += " R_child: (" + func(&arr[i]->right_child->data) + ')';

            s += " ]\n";
        }

        s += '}';

        delete[] arr;
        return s;
    }

    int height_h(Node<T>* n) {
        if (n == nullptr)
            return 0;

        int lb_height = height_h(n->left_child);
        int rb_height = height_h(n->right_child);

        if (lb_height < rb_height)
            return 1 + rb_height;
        else
            return 1 + lb_height;
    }

    int height() {
        return height_h(root);
    }

};

// wykorzystywany przy dodawaniu elementu do tablicy, np. w inorder
template <typename T>
int RBT<T>::traversal_index = 0;

// Obiekty dodawane do RBT i potrzebne dla niego funkcje
struct simple_object {
    int f1 = NULL;
    char f2 = NULL;
};

std::string str(simple_object* o) {
    std::string s = std::to_string(o->f1) + ", " + o->f2;
    return s;
}

int simpleObjectComparator(simple_object* o1, simple_object* o2) {
    if (o1->f1 == o2->f1)
        return 0;
    else if (o1->f1 < o2->f1)
        return -1;
    else
        return 1;
}

using namespace std;

int main()
{
    srand(time(NULL));

    RBT<simple_object>* rbt = new RBT<simple_object>();
    // rbt1
    rbt->insert({ 2135, 'j' }, simpleObjectComparator);
    rbt->insert({ 1700, 'd' }, simpleObjectComparator);
    rbt->insert({ 1900, 'd' }, simpleObjectComparator);
    rbt->insert({ 1090, 'd' }, simpleObjectComparator);
    rbt->insert({ 80, 'd' }, simpleObjectComparator);
    rbt->insert({ 3000, 'd' }, simpleObjectComparator);
    rbt->insert({ 4000, 'd' }, simpleObjectComparator);
    rbt->insert({ 3500, 'd' }, simpleObjectComparator);
    rbt->insert({ 1600, 'd' }, simpleObjectComparator);
    rbt->insert({ 10, 'd' }, simpleObjectComparator);
    rbt->insert({ 50, 'd' }, simpleObjectComparator);
    rbt->insert({ 3200, 'd' }, simpleObjectComparator);
    rbt->insert({ 3010, 'd' }, simpleObjectComparator);
    rbt->insert({ 90, 'd' }, simpleObjectComparator);
    rbt->insert({ 85, 'd' }, simpleObjectComparator);
    rbt->insert({ 83, 'd' }, simpleObjectComparator);
    rbt->insert({ 82, 'd' }, simpleObjectComparator);
    rbt->insert({ 1650, 'd' }, simpleObjectComparator);
    rbt->insert({ 81, 'd' }, simpleObjectComparator);
    rbt->insert({ 3011, 'd' }, simpleObjectComparator);
    rbt->insert({ 3012, 'd' }, simpleObjectComparator);

    // rbt 2
    //rbt->insert({ 2391, 'j' }, simpleObjectComparator);
    //rbt->insert({ 6, 'j' }, simpleObjectComparator);
    //rbt->insert({ 1919, 'j' }, simpleObjectComparator);
    //rbt->insert({ 5006, 'j' }, simpleObjectComparator);
    //rbt->insert({ 0, 'j' }, simpleObjectComparator);
    //rbt->insert({ 1, 'j' }, simpleObjectComparator);
    //rbt->insert({ 11, 'j' }, simpleObjectComparator);
    //rbt->insert({ 500, 'j' }, simpleObjectComparator);
    //rbt->insert({ 1000, 'j' }, simpleObjectComparator);
    //rbt->insert({ 9001, 'j' }, simpleObjectComparator);
    //rbt->insert({ 20, 'j' }, simpleObjectComparator);
    //rbt->insert({ 8, 'j' }, simpleObjectComparator);
    //rbt->insert({ 4, 'j' }, simpleObjectComparator);
    //rbt->insert({ 3, 'j' }, simpleObjectComparator);
    //rbt->insert({ 2, 'j' }, simpleObjectComparator);




    cout << rbt->str(str);

    delete rbt;

    const int MAX_ORDER = 7;
    RBT<simple_object>* rbt2 = new RBT<simple_object>();

    //for (int i = 1; i < MAX_ORDER + 1; i++) {
    //    int n = pow(10, i);

    //    clock_t start = clock();

    //    for (int j = 0; j < n; j++) {
    //        rbt2->insert({ rand() % RAND_MAX, 'x'}, simpleObjectComparator);
    //    }

    //    clock_t end = clock();

    //    cout << "\nCzas: " << double(end - start) / CLOCKS_PER_SEC << "s\n" << rbt2->str(str, 10) ;

    //    int m = pow(10, 4);
    //    long match = 0;

    //    start = clock();

    //    for (int j = 0; j < m; j++) {
    //        Node<simple_object> * result = rbt2->search({ rand() % RAND_MAX, 'x' }, simpleObjectComparator);

    //        if (result != nullptr) {
    //            match++;
    //        }
    //    }

    //    end = clock();

    //    cout << "\n\nWyszukiwanie -> czas: " << double(end - start) / CLOCKS_PER_SEC << "s, dopasowan: " << match << "\n\n";
    //    match = 0;
    //    rbt2->clear();
    //}


    delete rbt2;
}

