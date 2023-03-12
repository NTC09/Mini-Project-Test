#define opt __attribute((optimize("Ofast")))
#define abs(x) ((x < 0) ? -(x) : (x))
#define distance(x1, y1, x2, y2) (abs((x1) - (x2)) + abs((y1) - (y2)))

class Base {
public:
    int ID;
    int x;
    int y;
    int heapid;
};// typedef Type;

template <typename Type>
class Heap {
private:
    void* List[1000];
    bool needErase;
    bool isMaxHeap;
    void heapifyUp(int index) {
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
    void heapifyDown(int index) {
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
    void erase(int index) {
        Swap(index, --this->size);
        heapifyDown(index);
        heapifyUp(index);
    }
    void Swap(int a, int b) {
        register void* t = List[a];
        List[a] = List[b];
        List[b] = t;
        if (needErase) {
            ((Type*)List[a])->heapid = a;
            ((Type*)List[b])->heapid = b;
        }
    }
    bool comp(int id1, int id2) {
        return (*(Type*)List[id1] < *(Type*)List[id2]) == isMaxHeap;
    }
public:
    unsigned int size;
    Heap() {
        this->init(false);
    }
    void init(bool need) {
        this->size = 0;
        needErase = need;
        isMaxHeap = true;
    }
    void init() {
        this->size = 0;
        needErase = false;
        isMaxHeap = false;
    }
    void insert(void* newValue) {
        if (size == 1000) {
            if (*(Type*)newValue < *(Type*)List[this->size - 1])
                erase(this->size - 1);
            else
                return;
        }
        this->List[this->size] = newValue;
        if (needErase)
            ((Type*)newValue)->heapid = this->size;
        heapifyUp(this->size++);
    }
    
    void erase(void* type) {
        if (needErase)
            erase(((Type*)type)->heapid);
    }
    void update(int index) {
        heapifyUp(index);
        heapifyDown(index);
    }
    Type* pop() {
        Swap(0, --this->size);
        heapifyDown(0);
        return (Type*)this->List[this->size];
    }
    Type* top() {
        if (size == 0)
            return 0;
        return (Type*)this->List[0];
    }
};

class School: public Base {
public:
    int distance;
    void* assigned;
    void* wishlist;
    static int number;
    static int capacity;
    bool operator<(School& st) const {
        if (this->distance != st.distance)
            return this->distance > st.distance;
        return this->ID > st.ID;
    }
    void calculatedistance(int sx, int sy) {
        distance = distance(x, y, sx, sy);
    }
    void* insert(void* student);
    
} school[10];
int School::number;
int School::capacity;

class Student: public Base {
public:
    int maxDistance;
    Student* next;
    School* schoola;
    static int numbers;
    bool operator<(Student& st) const {  // higher priority
        if (this->maxDistance != st.maxDistance)
            return this->maxDistance > st.maxDistance;
        return this->ID < st.ID;
    }
    void calculatedistance() {
        maxDistance = 0;
        register int t;
        for (register int i = 0; i < School::number; i++) {
            t = distance(x, y, school[i].x, school[i].y);
            if (maxDistance < t)
                maxDistance = t;
        }
    }
} student[10000];
Student* mapStudent[10007];
Heap<Student> assgined[10];
Heap<Student> wantAssign[10];
int Student::numbers = 0;

Student* findStudent(int mID) {
    register int hash = mID % 10007;
    register Student* st = mapStudent[hash];
    while (st != 0 && st->ID != mID)
        st = st->next;
    return st;
}

Student* addNewStudent(int mID, int mX, int mY) {
    register int hash = mID % 10007;
    student[Student::numbers].ID = mID;
    student[Student::numbers].x = mX;
    student[Student::numbers].y = mY;
    student[Student::numbers].next = mapStudent[hash];
    mapStudent[hash] = &student[Student::numbers++];
    return mapStudent[hash];
}

void assign(Student* studentIn) {
    Heap<School> pschool;
    for (register int i = 0; i < School::number; i++) {
        school[i].calculatedistance(studentIn->x, studentIn->y);
        pschool.insert(&school[i]);
    }
    while (pschool.size != 0) {
        register School* t = pschool.pop();
        if (((Heap<Student>*)t->assigned)->size < School::capacity) {
            t->insert(studentIn);
            studentIn->schoola = t;
            return;
        }
        else if (*studentIn < *assgined[t->ID].top()) {
            register Student* studentOut = assgined[t->ID].pop();
            assgined[t->ID].insert(studentIn);
            studentIn->schoola = t;
            assign(studentOut);
            return;
        }
        else {
            wantAssign[t->ID].insert(studentIn);
        }
    }
}

void kickout(Student* studentOut) {
    School* curSchool = (School*)studentOut->schoola;
    Heap<Student>* curAsigned = (Heap<Student>*)curSchool->assigned;
    Heap<Student>* wishList = (Heap<Student>*)curSchool->wishlist;
    curAsigned->erase(studentOut);
    if (curAsigned->size == School::capacity - 1) {
        if (wishList->size == 0)
            return;
        register Student* studentIn = wishList->pop();
        while (studentIn->schoola == 0 && wishList->size != 0) {
            studentIn = wishList->pop();
        }
        if (studentIn->schoola != 0) {
            kickout(studentIn);
            curAsigned->insert(studentIn);
            studentIn->schoola = studentOut->schoola;
        }
    }
    studentOut->schoola = 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void init(int C, int N, int mX[], int mY[]) {
    School::number = N;
    School::capacity = C;
    Student::numbers = 0;
    for (register int i = 0; i < 10007; i++)
        mapStudent[i] = 0;
    for (register int i = 0; i < N; i++) {
        assgined[i].init(true);
        wantAssign[i].init();
        school[i].x = mX[i];
        school[i].y = mY[i];
        school[i].ID = i;
        school[i].assigned = &assgined[i];
        school[i].wishlist = &wantAssign[i];
    }
    return;
}

int add(int mStudent, int mX, int mY) {  // 7.500
    register Student* st = findStudent(mStudent);
    if (st == 0)
        st = addNewStudent(mStudent, mX, mY);
    else {
        st->x = mX;
        st->y = mY;
    }
    st->calculatedistance();
    assign(st);
    return st->schoola->ID;
}

int remove(int mStudent) {  // 1.500
    register Student* st = findStudent(mStudent);
    register int ret = st->schoola->ID;
    kickout(st);
    return ret;
}

int status(int mSchool) {  // 10.000
    return assgined[mSchool].size;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
