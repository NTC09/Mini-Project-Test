#include <iostream>
using namespace std;

#define Key long long



class keyClass {
public:
    Key key;
    void init(Key key) {
        this->key = key;
    }
};

class Type: public keyClass {
    int value;
};

//template <typename Key, typename Type>
class List {
    Type* node;
    int size;
public:
    void reset() {
        size = 0;
        node = new Type;
    }
    void add(Type& t) {
        this->node[size++] = t;
    }
    Type& operator[](Key& key) {
        register int i = 0;
        while (i < size) {
            if (key == node[i].key) {
                return this->node[i];
            }
            i++;
        }
        this->node[size].init(key);
        return this->node[size++];
    }
};

//template <typename Type>
struct Map {
    //List<Type> index[10007];
    List index[10007];
public:
    Type& operator[](Key key) {
        return this->index[key % 10007][key];
    }
    void reset() {
        for (register int i = 0; i < 10007; i++)
            index[i].reset();
    }
};

int main() {

    return 0;
}