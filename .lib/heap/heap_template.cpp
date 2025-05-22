
struct Sss{
	int value;
	int heapid;
} sss[100000];

bool comp(int a, int b){
	return sss[a].value > sss[b].value;
}

struct Heap{
	int index[100007];
	int size;
	void Swap(int i, int j){
		sss[index[i]].heapid = j;
		sss[index[j]].heapid = i;
		register int t = index[i];
		index[i] = index[j];
		index[j] = t;
	}
	void insert(int id){
		sss[id].heapid = size;
		index[size] = id;
		up(size++);
	}
	void up(int i){
		register int j = i, t = i;
		while (t){
			j = t;
			t = (j-1)/2;
			if (comp(t,j)) break;
			Swap(j,t);
		}
	}
	void down(int i){
		register int j = i, t = i;
		while (t < size){
			j = t;
			t = 2*j+1;
			if (t<size && comp(j,t)) t++;
			if (t<size && comp(t,j)) break;
			Swap(j,t);
		}
	}
	int pop(){
		Swap(0,	--size);
		down(0);
		return index[size];
	}
} heap;

#define MAX_N 10000

struct mStruct {
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

struct Heap {
   public:
    int idList[14286];
    bool isMaxHeap;
    unsigned int size;
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
    void heapifyUp(int index) {
        int indx = index;
        int parent = (indx - 1) / 2 ;
        if (parent>= 0) {
            if (comp(parent, indx) == isMaxHeap)
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
            if (comp(indx, left) == isMaxHeap)
                indx = left;
        }
        if (right < size) {
            if (comp(indx, right) == isMaxHeap)
                indx = right;
        }
        if (indx != index) {
            Swap(indx, index);
            heapifyDown(indx);
        }
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
    void Swap(int a, int b) {
        int t = idList[a];
        idList[a] = idList[b];
        idList[b] = t;
        if (isMaxHeap) {
            mElements[idList[a]].maxId = a;
            mElements[idList[b]].maxId = b;
        } else {
            mElements[idList[a]].minId = a;
            mElements[idList[b]].minId = b;
        }
    }
    bool comp(int id1, int id2) {
        return mElements[idList[id1]] < mElements[idList[id2]];
    }
};