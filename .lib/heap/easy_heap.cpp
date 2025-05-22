#define MAX_N 10000

class mStruct {
   public:
    unsigned int id;
    int point;
    unsigned int minId, maxId;
    bool operator<(mStruct& mP) const {
        if (this->point != mP.point)
            return this->point < mP.point;
        else
            return this->id > mP.id;
    }
} mElements[MAX_N];

class Heap {
private:
    int idList[14286];
    bool isMaxHeap;
    unsigned int size;
    void heapifyUp(int index) {
        int indx = index;
        int parent = (indx - 1) / 2;
        if (parent >= 0) {
            if (comp(parent, indx))
                indx = parent;
        }
        if (indx != index) {
            Swap(indx, index);
            heapifyUp(indx);
        }
    }
    void heapifyDown(int index) {
        int indx = index,
        left = 2 * indx + 1,
        right = 2 * indx + 2;
        if (left < size) {
            if (comp(indx, left))
                indx = left;
        }
        if (right < size) {
            if (comp(indx, right))
                indx = right;
        }
        if (indx != index) {
            Swap(indx, index);
            heapifyDown(indx);
        }
    }
    void Swap(int a, int b) {
        int t = idList[a];
        idList[a] = idList[b];
        idList[b] = t;
        if (isMaxHeap) {
            mElements[idList[a]].maxId = a;
            mElements[idList[b]].maxId = b;
        }
        else {
            mElements[idList[a]].minId = a;
            mElements[idList[b]].minId = b;
        }
    }
    bool comp(int id1, int id2) {
        return (mElements[idList[id1]] < mElements[idList[id2]]) == isMaxHeap;
    }
public:
    void initMaxHeap() {
        this->isMaxHeap = true;
        this->size = 0;
    }
    void initMinHeap() {
        this->isMaxHeap = false;
        this->size = 0;
    }
    void insert(int index) {
        this->idList[this->size] = index;
        if (isMaxHeap)
            mElements[index].maxId = size;
        else
            mElements[index].minId = size;
        heapifyUp(this->size++);
    }

    void erase(int index) {
        Swap(index, --this->size);
        heapifyDown(index);
        heapifyUp(index);
    }
    void update(int index) {
        heapifyUp(index);
        heapifyDown(index);
    }
    int pop() {
        Swap(0, --this->size);
        heapifyDown(0);
        return this->idList[this->size];
    }
}heap;

int main() {
    
    return 0;
        }