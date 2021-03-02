#include <iostream>
#include <memory>

using namespace std;

// Абстрактный класс для таблицы идентификаторов
class IdTable {
public:
    // добавим идентификатор в таблицу
    virtual void add_id(const string &key) = 0;

    // найдем идентификатор в таблице
    virtual bool search_id(const string &key) = 0;

    // получим число операций в таблице
    long get_count_operation() const {
        return count_operation;
    }

    virtual ~IdTable() = default;

protected:
    void increase_count_operation() {
        count_operation++;
    }

    long count_operation = 0;
};

template<typename T>
struct Node {
    T key;
    Node *parent;
    Node *right;
    Node *left;

    Node(const T &_key, Node *_parent, Node *_right, Node *_left) {
        key = _key;
        parent = _parent;
        right = _right;
        left = _left;
    }
};

template<typename T>
class IdTableBinaryTree : public IdTable {
public:
    void add_id(const string &key) override {
        Node<T> *new_node = new Node<T>(key, nullptr, nullptr, nullptr);
        cout << "Хотим записать вершину с ключом " + key << endl; 
        if (root == nullptr) {
            cout << "Записали вершину в корень" << endl; 
            root = new_node;
            return;
        }

        Node<T> *now_node = root;

        // закончим только тогда, когда найдем пустого потомка
        while (true) {
            // сравниваем новое значение с текущим ключом 
            increase_count_operation();
            if (now_node->key == new_node->key) {
                return;
            }

            if (new_node->key > now_node->key) {
                // проверяем потомка на nullptr
                increase_count_operation();
                
                if (now_node->right != nullptr) {
                    cout << "Спустились в правое поддерево" << endl;
                    now_node = now_node->right;
                } else {
                    cout << "Записали вершину правым потомком" << endl;
                    new_node->parent = now_node;
                    now_node->right = new_node;
                    return;
                }
            } else {
                // проверяем потомка на nullptr
                increase_count_operation();

                if (now_node->left != nullptr) {
                    cout << "Спустились в левое поддерево" << endl;
                    now_node = now_node->left;
                } else {
                    cout << "Записали вершину левым потомком" << endl;
                    new_node->parent = now_node;
                    now_node->left = new_node;
                    return;
                }
            }
        }
    }

    bool search_id(const string &key) override {

        Node<T> *now_node = root;

        while (true) {
            increase_count_operation();
            if (now_node == nullptr) {
                return false;
            } 
            if (now_node->key == key) {
                return now_node;
            }
            if (now_node->key > key) {
                now_node = now_node->left;
            } else {
                now_node = now_node->right;
            }
        }
    }

    ~IdTableBinaryTree() override = default;

    // получим корень дерева
    Node<T>* get_root() {
        return root;
    }

    void print_binary_tree() {
        preorder(root);
    }


private:
    Node<T> *root = nullptr;

    // preorder обход
    void preorder(Node<T> *x) {
        if (x != nullptr) {
            std::cout << x->key << std::endl;
            preorder(x->left);
            preorder(x->right);
        }
    }
};


int main() {
    setlocale(LC_ALL, "RUS");
    IdTableBinaryTree<string> idTableBinary;
    idTableBinary.add_id("1234");
    idTableBinary.add_id("1235");
    idTableBinary.add_id("1236");
    idTableBinary.add_id("1233");
    idTableBinary.add_id("1233");
    idTableBinary.print_binary_tree();

    cout << idTableBinary.search_id("1233") << endl;
    cout << idTableBinary.search_id("1234") << endl;
    cout << idTableBinary.search_id("1235") << endl;
    cout << idTableBinary.search_id("1236") << endl;
    cout << idTableBinary.get_count_operation() << endl;

    return 0;
}