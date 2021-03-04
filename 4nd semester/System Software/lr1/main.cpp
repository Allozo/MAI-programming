#include <iostream>
#include <memory>
#include <cassert>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

// Абстрактный класс для таблицы идентификаторов
template<typename T>
class IdTable {
public:
    // добавим идентификатор в таблицу
    virtual void add_id(const T &key) = 0;

    // найдем идентификатор в таблице
    virtual bool search_id(const T &key) = 0;

    // вывести идентификаторы
    virtual void print_table() = 0;

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

// Реализация списка для хранения идентификаторов
template<typename T>
class IdTableList : public IdTable<T> {
public:
    void add_id(const T &key) override {
        shared_ptr<Node<T>> new_node = make_shared<Node<T>> (key, nullptr);

        // если таблица пустая
        if (root == nullptr) {
            this->increase_count_operation();
            root = new_node;
            end = new_node;
            return;
        }

        if (!search_id(key)) {
            // дописали новое значение в конец
            end->next = new_node;

            // обновили конец
            end = new_node;
        }
    }

    bool search_id(const T &key) override {
        shared_ptr<Node<T>> now_node = root;

        // обойдем весь список с самого начала
        while (now_node != nullptr) {
            this->increase_count_operation();
            if (now_node->key == key) {
                return true;
            }
            now_node = now_node->next;
        }

        // если оказались тут, то значение не нашли
        return false;
    }

    void print_table() override {
        shared_ptr<Node<T>> now_node = root;

        while (now_node != nullptr) {
            cout << now_node->key << endl;
            now_node = now_node->next;
        }
    }


private:
    // Структура для хранения вершины списка
    template<typename P>
    struct Node {
        P key;
        shared_ptr<Node<P>> next;

        // Конструктор для вершины
        Node(const P &_key, shared_ptr<Node<P>> _next) {
            key = _key;
            next = _next;
        }
    };

    // Корень списка
    shared_ptr<Node<T>> root = nullptr;

    // Корень списка
    shared_ptr<Node<T>> end = nullptr;

};

// Реализация бинарного дерева для хранения идентификаторов
template<typename T>
class IdTableBinaryTree : public IdTable<T> {
public:
    void add_id(const T &key) override {
        shared_ptr<Node<T>> new_node = make_shared<Node<T>> (key, nullptr, nullptr);

        if (root == nullptr) {
            this->increase_count_operation();
            root = new_node;
            return;
        }

        // вершина по которой будем итерироваться
        shared_ptr<Node<T>> now_node = root;

        // закончим только тогда, когда найдем пустого потомка
        while (true) {

            // сравниваем новое значение с текущим ключом 
            this->increase_count_operation();
            if (now_node->key == new_node->key) {
                return;
            }

            if (new_node->key > now_node->key) {
                // проверяем потомка на nullptr
                this->increase_count_operation();

                if (now_node->right != nullptr) {
                    now_node = now_node->right;
                } else {
                    now_node->right = new_node;
                    return;
                }
            } else {
                // проверяем потомка на nullptr
                this->increase_count_operation();

                if (now_node->left != nullptr) {
                    now_node = now_node->left;
                } else {
                    now_node->left = new_node;
                    return;
                }
            }
        }
    }

    bool search_id(const T &key) override {

        shared_ptr<Node < T>> now_node = root;

        while (true) {
            this->increase_count_operation();
            if (now_node == nullptr) {
                return false;
            }
            if (now_node->key == key) {
                return true;
            }
            if (now_node->key > key) {
                now_node = now_node->left;
            } else {
                now_node = now_node->right;
            }
        }
    }

    ~IdTableBinaryTree() override = default;

    void print_table() override {
        inorder(root);
    }

private:
    // Структура для хранения вершины бинарного дерева
    template<typename P>
    struct Node {
        P key;
        shared_ptr<Node<P>> right;
        shared_ptr<Node<P>> left;

        // Конструктор для вершины
        Node(const P &_key, shared_ptr<Node<P>> _right, shared_ptr<Node<P>> _left) {
            key = _key;
            right = _right;
            left = _left;
        }
    };

    // Корень дерева
    shared_ptr<Node<T>> root = nullptr;

    // inorder обход
    void inorder(shared_ptr<Node<T>> x) {
        if (x != nullptr) {
            inorder(x->left);
            std::cout << x->key << std::endl;
            inorder(x->right);
        }
    }
};

template<typename T>
long my_test_id_table(IdTable<T> &id_table) {
    vector<string> vec_id = {"jYYOnnRMnROpZKMJLvPHEwjhpsuQbyobjkBgcDaVhUAgKeZQDYNtWeyqyQanGNMXgHtikq",
                             "hypiSxwrZRwjLHJNkCAWFSmWGoCrnIbSmnOTVBTXpgXNYuCRWRnXkuRXysnMABRafzjIgH",
                             "hypiSxwrZRwjLHJNkCAWFSmWGoCrnIbSmnOTVBTXpgXNYuCRWRnXkuRXysnMABRafzjIgH",
                             "IfzEaoUGTUGWOHVpPOMkbiXhEmurLfxprUOEuDAKxpCmpnbCcoenShLxgIDaizDJCAcqOa",
                             "GVBEEJvetqrIFcoctsHbpULkfuZzyqSjTfFifIOsgArGNuSaMmJNxUxRLgXMYYEwDYeZhq",
                             "GsDBQzXeZvyHZlhBokAYnMEvXkOmzWnhPayvdsdmECRygCxcncpWbglsxqfYFCFfBmTepy",
                             "fDZTNDFUwcBJBlIJkDisAtuSljoQUJVfEiotCvwfXnriKeKzZaGEYkEjextAwqwihAXXpG",
                             "kTGAHdkXvZHsZDSWEnTrPiXTWYDaCuBxjcEcqNpOIlUEpLXAaMKsqPVNQfUcTLiDAbjgVO",
                             "qOElohdNDiHgAIzueIplndDSrztwjBINPIeWVGjPnLThPscCgGoaINphvgcgIeWOvyaedX",
                             "qffXmntyadqHQFcIGZLKVaZlxlfKCDqxGbEbMTdPtAqyJWVhuJIGoyoDbiLAEgMazCSjDk",
                             "LVNcGHDtntdlaGtNHftxRVwMvDbWWSPPueCJaYULwRMkIPFoDANocjNbkxwfGVLwlpCEyA",
                             "TJcyiJmxeEvaBZpJKtbCdGIBBDRnzfmQgEIeSAMwrDNZCzWunuwenryibJFLJJvdfZxHub",
                             "qffXmntyadqHQFcIGZLKVaZlxlfKCDqxGbEbMTdPtAqyJWVhuJIGoyoDbiLAEgMazCSjDk",
                             "LiETEqxIyEDLmPiNdaxtEovvmWJAKwpCrpOuzOabEYzOEfqdBgVhHjWUMhRZCFBYIRbaFr"};

    for (auto &id: vec_id) {
        cout << "Add id: " << id << endl;
        id_table.add_id(id);
    }

    assert(id_table.search_id("jYYOnnRMnROpZKMJLvPHEwjhpsuQbyobjkBgcDaVhUAgKeZQDYNtWeyqyQanGNMXgHtikq") == true);
    cout << "Id 'jYYOnnRMnROpZKMJLvPHEwjhpsuQbyobjkBgcDaVhUAgKeZQDYNtWeyqyQanGNMXgHtikq' detected in table" << endl;

    assert(id_table.search_id("hypiSxwrZRwjLHJNkCAWFSmWGoCrnIbSmnOTVBTXpgXNYuCRWRnXkuRXysnMABRafzjIgH") == true);
    cout << "Id 'hypiSxwrZRwjLHJNkCAWFSmWGoCrnIbSmnOTVBTXpgXNYuCRWRnXkuRXysnMABRafzjIgH' detected in table" << endl;

    assert(id_table.search_id("LiETEqxIyEDLmPiNdaxtEovvmWJAKwpCrpOuzOabEYzOEfqdBgVhHjWUMhRZCFBYIRbaFr") == true);
    cout << "Id 'LiETEqxIyEDLmPiNdaxtEovvmWJAKwpCrpOuzOabEYzOEfqdBgVhHjWUMhRZCFBYIRbaFr' detected in table" << endl;

    assert(id_table.search_id("ikxBIPTTlRFCEAwIoAUIovbaGPmsrDTHvkNbRCFSyBdWcUbzcQNOReiYKJGOcrCHMdPnuE") == false);
    cout << "Id 'ikxBIPTTlRFCEAwIoAUIovbaGPmsrDTHvkNbRCFSyBdWcUbzcQNOReiYKJGOcrCHMdPnuE' not detected in table" << endl;

    assert(id_table.search_id("GTWbcIQTcHrQpjlHmRdFxMeUoSTXyFnSytAQPrIbIFdqjqXDKejPQLKWubBBwWZssrhWli") == false);
    cout << "Id 'GTWbcIQTcHrQpjlHmRdFxMeUoSTXyFnSytAQPrIbIFdqjqXDKejPQLKWubBBwWZssrhWli' not detected in table" << endl;

    assert(id_table.search_id("MmBTTzHpzZIQnzBElklQLKVxbaULpFMJzFBgsEqixQzPnGgvMdEWunWPOfaaAVWjOagqzh") == false);
    cout << "Id 'MmBTTzHpzZIQnzBElklQLKVxbaULpFMJzFBgsEqixQzPnGgvMdEWunWPOfaaAVWjOagqzh' not detected in table" << endl;

    assert(id_table.search_id("qffXmntyadqHQFcIGZLKVaZlxlfKCDqxGbEbMTdPtAqyJWVhuJIGoyoDbiLAEgMazCSjDk") == true);
    cout << "Id 'qffXmntyadqHQFcIGZLKVaZlxlfKCDqxGbEbMTdPtAqyJWVhuJIGoyoDbiLAEgMazCSjDk' detected in table" << endl;

    assert(id_table.search_id("LiETEqxIyEDLmPiNdaxtEovvmWJAKwpCrpOuzOabEYzOEfqdBgVhHjWUMhRZCFBYIRbaFr") == true);
    cout << "Id 'LiETEqxIyEDLmPiNdaxtEovvmWJAKwpCrpOuzOabEYzOEfqdBgVhHjWUMhRZCFBYIRbaFr' detected in table" << endl;

    return id_table.get_count_operation();
}

// простой тест для сравнения
void test_easy() {
    IdTableBinaryTree<string> idTableBinaryTree;
    long count_operation_for_binary_tree = my_test_id_table(idTableBinaryTree);
    cout << "The number of comparison operations for the binary tree: " << count_operation_for_binary_tree << endl;

    IdTableList<string> idTableList;
    long count_operation_for_list = my_test_id_table(idTableList);
    cout << "The number of comparison operations for the list:        " << count_operation_for_list << endl;
}

template <typename T>
long test_for_file(IdTable<T> &id_table, string &name_file) {
    ifstream file(name_file);

    string str;

    if (!file) {
        cout << "Error opening the file: " << name_file << endl;
        return -1;
    }

    while (file >> str) {
        id_table.add_id(str);
    }

    file.close();


    return id_table.get_count_operation();
}

// запустит несколько тестов, а потом выведет отношения колличества операций
void speed_comparison_test() {
    IdTableBinaryTree<string> idTableBinaryTree;
    IdTableList<string> idTableList;
    vector<string> files = {"test_id/list_id_10.txt", "test_id/list_id_50.txt",
                            "test_id/list_id_100.txt", "test_id/list_id_500.txt",
                            "test_id/list_id_1000.txt", "test_id/list_id_1500.txt",
                            "test_id/list_id_2000.txt"};
    vector<int> num = {10, 50, 100, 500, 1000, 1500, 2000};

    vector<pair<long, long>> res;

    for (int i = 0; i < files.size(); i++) {
        string name_file = files[i];

        long res_1 = test_for_file(idTableList, name_file);
        long res_2 = test_for_file(idTableBinaryTree, name_file);

        if (res_1 == -1 or res_2 == -1) {
            continue;
        }
        res.emplace_back(make_pair(res_1, res_2));

        cout << "Struct: List.        Number of tests: " << setw(5) << num[i] << ". Number of comparison operations: " << res_1 << endl;
        cout << "Struct: Binary tree. Number of tests: " << setw(5) << num[i] << ". Number of comparison operations: " << res_2 << endl;
    }

    cout << endl;

    for (auto & re : res) {
        cout << "(List)/(Binary tree) == " << static_cast<double>(re.first)/re.second << endl;
    }
}

int main() {
    // этот тест можно запустить, если нужно посмотреть, как оно может работать
    test_easy();

    // этот тест выведет сравнение Списка и Бинарного дерева
//    speed_comparison_test();

    return 0;
}