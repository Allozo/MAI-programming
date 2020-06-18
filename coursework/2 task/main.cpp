#include <iostream>
#include <sstream>

using namespace std;

template<typename T>
struct Vector {
    Vector() = default;

    Vector(T new_x, T new_y) {
        x = new_x;
        y = new_y;
    }

    friend ostream &operator<<(ostream &str, const Vector<T> &a) {
        string res;
        ostringstream s;
        s << a.x << " " << a.y;
        res = s.str();
        str << res;
        return str;
    }

    T x;
    T y;
};

template<typename T>
class DynamicArray {
protected:
    T *array;
    int max_size;
    int real_size;

public:
    DynamicArray() {
        array = new T[8];
        real_size = 0;
        max_size = 8;
    }

    DynamicArray(DynamicArray<T> const &arr) {
        real_size = arr.real_size;
        max_size = arr.real_size;
        array = arr.array;
    }

    explicit DynamicArray(int value) {
        array = new T[2 * value];
        max_size = 2 * value;
        real_size = value;
    }

    virtual ~DynamicArray() {
        delete[] array;
    };

    void add(T value) {
        if (real_size + 1 >= max_size) {
            T *new_array = new T[max_size * 2 + 1];
            for (int i = 0; i < max_size; i++) {
                new_array[i] = array[i];
            }
            delete[] array;
            array = new_array;
            max_size *= 2;
            max_size++;
        }

        array[real_size] = value;
        real_size++;
    }

    void pop() {
        real_size--;
    }

    int size() const {
        return real_size;
    }

    void resize(int n) {
        if (real_size < n and n < max_size) {
            for (int i = real_size; i < n; i++) {
                array[i] = 0;
            }
            real_size = n;
        } else if (max_size <= n) {
            T *new_array = new T[n * 2];
            for (int i = 0; i < real_size; i++) {
                new_array[i] = array[i];
            }
            delete[] array;
            array = new_array;
            real_size = n;
            max_size = 2 * n;

        } else if (n < real_size) {
            real_size = n;
        } else {
            cerr << "Проверь resize" << endl;
            exit(321);
        }
    }

    void deleted(int i) {
        try {
            if (i >= real_size) {
                throw "Значение вне массива";
            }
        }
        catch (const char *exception) {
            cerr << "Error: " << exception << endl;
            exit(1);
        }
        // хотим удалить 5 при нумерации с 1-цы
        for (int j = i - 1; j < real_size; j++) {
            array[j] = array[j + 1];
        }
        real_size--;
    }

    T &operator[](int i) {
        try {
            if (i >= real_size or i < 0) {
                throw "Значение вне массива";
            }
        }
        catch (const char *exception) {
            cerr << "Error: " << exception << endl;
            exit(1);
        }
        return array[i];
    }

    DynamicArray &operator=(const DynamicArray &other){
        this->array = other.array;
        this->real_size = other.real_size;
        this->max_size = other.max_size;
        return *this;
    }

    friend ostream &operator<<(ostream &str, const DynamicArray &dynamicArray) {
        string res;
        for (int i = 0; i < dynamicArray.real_size; i++) {
            ostringstream stream;
            auto a = dynamicArray.array[i];
            stream << a;
            res += stream.str() + " ";
        }
        res += '\n';
        str << res;
        return str;
    }
};

template<typename Tvec>
class DynamicVector : public DynamicArray<Vector <Tvec>> {
public:

    friend ostream &operator<<(ostream &str, const DynamicVector<Vector<Tvec>> &dynamicArray) {
        string res;
        for (int i = 0; i < dynamicArray.real_size; i++) {
            ostringstream stream;
            stream << dynamicArray.array[i].x;
            stream << " ";
            stream << dynamicArray.array[i].y;
            res += stream.str() + '\n';
        }
        str << res;
        return str;
    }

    void resize(size_t n) {
        if (this->real_size < n and n < this->max_size) {
            for (int i = this->real_size; i < n; i++) {
                Vector<Tvec> a(0, 0);
                this->array[i] = a;
            }
            this->real_size = n;
        } else if (this->max_size <= n) {
            auto *new_array = new Vector<Tvec>[n * 2];
            for (int i = 0; i < this->real_size; i++) {
                new_array[i] = this->array[i];
            }
            delete[] this->array;
            this->array = new_array;
            this->real_size = n;
            this->max_size = 2 * n;

        } else if (n < this->real_size) {
            this->real_size = n;
        } else {
            cerr << "Проверь resize" << endl;
            exit(123);
        }
    }

    DynamicVector &operator=(const DynamicVector &other){
        this->array = other.array;
        this->real_size = other.real_size;
        this->max_size = other.max_size;
        return *this;
    }

    friend DynamicVector operator*(const DynamicVector &left_vec, int value) {
        DynamicVector new_vec(left_vec);
        for (int i = 0; i < left_vec.real_size; i++) {
            new_vec[i].x *= value;
            new_vec[i].y *= value;
        }
        return new_vec;
    }

    friend DynamicVector operator*(int value, const DynamicVector &right_vec) {
        DynamicVector new_vec(right_vec);
        for (int i = 0; i < right_vec.real_size; i++) {
            new_vec[i].x *= value;
            new_vec[i].y *= value;
        }
        return new_vec;
    }

    friend DynamicVector operator+(const DynamicVector &vec_left, const DynamicVector &vec_right) {
        int size = max(vec_left.size(), vec_right.size());
        DynamicVector new_vec;
        new_vec.resize(size);
        for (int i = 0; i < min(vec_left.size(), vec_right.size()); i++) {
            new_vec.array[i].x = vec_left.array[i].x + vec_right.array[i].x;
            new_vec.array[i].y = vec_left.array[i].y + vec_right.array[i].y;
        }
        if (vec_left.size() > vec_right.size()) {
            for (int i = min(vec_left.size(), vec_right.size()); i < vec_left.size(); i++) {
                new_vec.array[i] = vec_left.array[i];
            }
        } else {
            for (int i = min(vec_left.size(), vec_right.size()); i < vec_right.size(); i++) {
                new_vec.array[i] = vec_right.array[i];
            }
        }
//        cout << new_vec << "-> " << new_vec.array[0].x << " " << new_vec.array[0].y << endl;
        return new_vec;
    }

};

template <typename Tset>
class DynamicSet : public  DynamicArray<Tset> {
public:
    DynamicSet() {
        this->real_size = 0;
        this->max_size = 0;
    }

    explicit DynamicSet(int value) {
        this->array = new Tset[2 * value];
        this->max_size = 2 * value;
        this->real_size = value;
    }

    DynamicSet unification (const DynamicSet &left_set) {
        DynamicSet new_set;
        for (int i = 0; i < left_set.size(); i++) {
            new_set.add(left_set.array[i]);
        }
        for (int i = 0; i < this->size(); i++) {
            new_set.add(this->array[i]);
        }
        return new_set;
    }

    DynamicSet intersection (const DynamicSet &left_set) {
        DynamicSet new_set;
        for (int i = 0; i < this->size(); i++) {
            bool equal = false;
            for (int j = 0; j < left_set.size(); j++) {
                if (this->array[i] == left_set.array[j]) {
                    equal = true;
                    break;
                }
            }
            if (equal) {
                new_set.add(this->array[i]);
            }
        }
        return new_set;
    }
};

void test_for_dynamic_array() {
    DynamicArray<double> my_array(10);
    cout << my_array;
    for (int i = 0; i < 10; i++) {
        my_array[i] = i+2;
    }
    cout << my_array;
    my_array.deleted(5);
    cout << my_array;
    my_array.resize(7);
    cout << my_array;
    my_array.pop();
    cout << my_array;
    my_array.resize(10);
    cout << my_array;
    my_array.resize(30);
    cout << my_array;
    cout << my_array.size() << endl;
    my_array.add(23);
    cout << my_array << "----" << endl;

    DynamicArray<double> my_array_2(4);
    for (int i = 0; i < 20; i++) {
        my_array_2.add(i+2);
    }
    cout << my_array_2;
}

void test_for_dynamic_vector() {
    DynamicVector<int> t;
    Vector<int> a(5, 6);
    Vector<int> b(4, 7);
    t.add(a);
    t.add(a);
    t.add(a);
    t.add(a);
    t.add(b);
    cout << t << endl;
    t.resize(4);
    cout << t << endl;
    t.resize(9);
    t.add(b);
    cout << t << endl;

    cout << "--------" << endl;

    auto g = t + t;
    cout << g << endl;
    auto h = 2 * t;
    cout << h << endl;
    auto z = t * 2;
    cout << z << endl;
}

void test_for_dynamic_set() {
    DynamicSet<int> a;
    for (int i = 0; i < 5; i++) {
        a.add(i);
    }
    a.add(5);
    a.add(5);
    a[0] = 1;
    cout << "a: " << a;

    cout << "---" << endl;

    DynamicSet<int> g;
    for (int i = 0; i < 7; i++) {
        g.add(i+10);
    }
    cout << "g: " << g;

    cout << "---" << endl;

    auto h = a.unification(g);
    cout << "Объеденение: " << h;

    cout << "---" << endl;


    a[2] = 13;
    cout << "a: " << a;
    cout << "g: " << g;
    auto y = a.intersection(g);
    cout << "Пересечение:" << y;
}

int main() {
    test_for_dynamic_array();
    test_for_dynamic_vector();
    test_for_dynamic_set();
    return 0;
}
