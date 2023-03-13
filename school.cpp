#define op __attribute((optimize("Ofast")))
#define abs(x) ((x < 0) ? -(x) : (x))
#define distance(x1, y1, x2, y2) (abs((x1) - (x2)) + abs((y1) - (y2)))

class Base {
   public:
    int ID;
    int x;
    int y;
    int heapId;
} typedef Type;

template <typename Type>
class Heap {
   private:
    Type* List[1000];
    bool needErase;
    bool isMaxHeap;
    op void heapifyUp(int index) {
        register int indx = index,
                     parent = (indx - 1) / 2;
        if (parent >= 0) {
            if (comp(parent, indx))
                indx = parent;
        }
        if (indx != index) {
            Swap(indx, index);
            heapifyUp(indx);
        }
    }
    op void heapifyDown(int index) {
        register int indx = index,
                     left = 2 * indx + 1,
                     right = 2 * indx + 2;
        if (left < size)
            if (comp(indx, left))
                indx = left;
        if (right < size)
            if (comp(indx, right))
                indx = right;
        if (indx != index) {
            Swap(indx, index);
            heapifyDown(indx);
        }
    }
    op void erase(int index) {
        Swap(index, --this->size);
        heapifyDown(index);
        heapifyUp(index);
    }
    op void Swap(int a, int b) {
        register Type* t = List[a];
        List[a] = List[b];
        List[b] = t;
        if (needErase) {
            List[a]->heapId = a;
            List[b]->heapId = b;
        }
    }
    op bool comp(int id1, int id2) {
        return (*List[id1] < *List[id2]) == isMaxHeap;
    }
   public:
    unsigned int size;
    op Heap() {
        this->init(false);
    }
    op void init(bool need) {
        this->size = 0;
        needErase = need;
        isMaxHeap = true;
    }
    op void init() {
        this->size = 0;
        needErase = false;
        isMaxHeap = false;
    }
    op void insert(Type* newValue) {
        if (size == 1000) {
            if (*newValue < *List[this->size - 1])
                erase(this->size - 1);
            else
                return;
        }
        this->List[this->size] = newValue;
        if (needErase)
            newValue->heapId = this->size;
        heapifyUp(this->size++);
    }
    
    op void erase(Type* type) {
        if (needErase)
            erase(type->heapId);
    }
    op Type* pop() {
        Swap(0, --this->size);
        heapifyDown(0);
        return this->List[this->size];
    }
    op Type* top() {
        if (size == 0)
            return 0;
        return this->List[0];
    }
};

class Student : public Base {
   public:
    int maxDistance;
    int next;
    class School* schoolIn;
    op bool operator<(Student& st) const {  // higher priority
        if (this->maxDistance != st.maxDistance)
            return this->maxDistance > st.maxDistance;
        return this->ID < st.ID;
    }
    op void calculateDistance();
};

class School : public Base {
   public:
    int distance;
    class Heap<Student>* assigned;
    class Heap<Student>* wishlist;
    School() {
        assigned = new Heap<Student>;
        wishlist = new Heap<Student>;
    }
    op bool operator<(School& st) const {
        if (this->distance != st.distance)
            return this->distance > st.distance;
        return this->ID > st.ID;
    }
    op void calculateDistance(int sx, int sy) {
        distance = distance(x, y, sx, sy);
    }
};

// Finish class define

Student student[10000];
int mapStudent[10007];
int studentNumber;
School school[10];
int schoolNumber;
int capacity;

op void Student::calculateDistance() {
    maxDistance = 0;
    register int t;
    for (register int i = 0; i < schoolNumber; i++) {
        t = distance(x, y, school[i].x, school[i].y);
        if (maxDistance < t)
            maxDistance = t;
    }
}

op int findStudent(int mID) {
    register int hash = mID % 10007;
    register int st = mapStudent[hash];
    while (st != -1 && student[st].ID != mID)
        st = student[st].next;
    return st;
}

op int addNewStudent(int mID, int mX, int mY) {
    register int hash = mID % 10007;
    student[studentNumber].ID = mID;
    student[studentNumber].x = mX;
    student[studentNumber].y = mY;
    student[studentNumber].next = mapStudent[hash];
    mapStudent[hash] = studentNumber++;
    return mapStudent[hash];
}

op void assign(Student* studentIn) {
    Heap<School> qSchool;
    for (register int i = 0; i < schoolNumber; i++) {
        school[i].calculateDistance(studentIn->x, studentIn->y);
        qSchool.insert(&school[i]);
    }
    register School* t;
    while (qSchool.size != 0) {
        t = qSchool.pop();
        if (t->assigned->size < capacity) {
            t->assigned->insert(studentIn);
            studentIn->schoolIn = t;
            return;
        } else if (*studentIn < *t->assigned->top()) {
            register Student* studentOut = t->assigned->pop();
            t->assigned->insert(studentIn);
            studentIn->schoolIn = t;
            assign(studentOut);
            return;
        } else {
            t->wishlist->insert(studentIn);
        }
    }
}

op void kickOut(Student* studentOut) {
    studentOut->schoolIn->assigned->erase(studentOut);
    if (studentOut->schoolIn->assigned->size == capacity - 1) {
        if (studentOut->schoolIn->wishlist->size == 0)
            return;
        register Student* studentIn = studentOut->schoolIn->wishlist->pop();
        while (studentIn->schoolIn == 0 && studentOut->schoolIn->wishlist->size != 0) {
            studentIn = studentOut->schoolIn->wishlist->pop();
        }
        if (studentIn->schoolIn != 0) {
            kickOut(studentIn);
            studentOut->schoolIn->assigned->insert(studentIn);
            studentIn->schoolIn = studentOut->schoolIn;
        }
    }
    studentOut->schoolIn = 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
op void init(int C, int N, int mX[], int mY[]) {
    schoolNumber = N;
    capacity = C;
    studentNumber = 0;
    for (register int i = 0; i < 10007; i++)
        mapStudent[i] = -1;
    for (register int i = 0; i < N; i++) {
        school[i].x = mX[i];
        school[i].y = mY[i];
        school[i].ID = i;
        school[i].assigned->init(true);
        school[i].wishlist->init();
    }
}

op int add(int mStudent, int mX, int mY) {  // 7.500
    register int id = findStudent(mStudent);
    if (id == -1)
        id = addNewStudent(mStudent, mX, mY);
    else {
        student[id].x = mX;
        student[id].y = mY;
    }
    student[id].calculateDistance();
    assign(&student[id]);
    return student[id].schoolIn->ID;
}

op int remove(int mStudent) {  // 1.500
    register int st = findStudent(mStudent),
                 ret = student[st].schoolIn->ID;
    kickOut(&student[st]);
    return ret;
}

op int status(int mSchool) {  // 10.000
    return school[mSchool].assigned->size;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
