struct Node {
    int life;
    int hIndex;
    bool operator<(Node& n) {
        return life < n.life;
    }
} pool[30000];
int poolNum = 0;

/*=================================Min Heap/*=================================*/
int hList[30000];
int hSize;
#define hswap(i1, i2)                \
    {                                \
        temp = hList[i1];            \
        hList[i1] = hList[i2];       \
        hList[i2] = temp;            \
        pool[hList[i1]].hIndex = i1; \
        pool[hList[i2]].hIndex = i2; \
    }
void push(int nodeId) {
    hList[hSize] = nodeId;
    pool[hList[hSize]].hIndex = hSize;
    register int i = hSize++, p, m, temp;
    while (i > 0) {
        m = i;
        p = (i - 1) / 2;
        if (pool[hList[i]] < pool[hList[p]])
            m = p;
        if (m != i) {
            hswap(i, m);
            i = m;
        } else
            break;
    }
}
void pop(int indx) {
    register int i = indx, n, m, temp;
    --hSize;
    hswap(i, hSize);
    while (i < hSize) {
        m = i;
        n = i * 2 + 1;
        if (n < hSize && pool[hList[n]] < pool[hList[m]])
            m = n;
        ++n;
        if (n < hSize && pool[hList[n]] < pool[hList[m]])
            m = n;
        if (m != i) {
            hswap(i, m);
            i = m;
        } else
            break;
    }
}