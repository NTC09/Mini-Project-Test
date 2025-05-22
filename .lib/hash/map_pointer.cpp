#define MAP_SIZE 100007
#define ARR_SIZE 100000
#define f(i, m, n) for (int i = (m); i < (n); i++)


/**
 * @brief Hash function: h <<= 6 for upper and lower key words
 *
 * @param a is the key
 * @return long long
 */
unsigned long long Hash(const char* a) {
    unsigned long long h = 0;
    while (*a) 
        h = (h <<= 6) | (*a++ & 0x2F);
    return h;
}

/**
 * @brief Hash function: h <<= 5 for lower key words only
 *
 * @param a is the key
 * @return long long
 */
unsigned long long hash(const char* a) {
    unsigned long long h = 0;
    while (*a)
        h |= (h <<= 5) | (*a++ & 0x1F);
    return h;
}

/**
 * @brief Node:
 * this a linked list.
 */
struct NODE {
    unsigned long long name; // can save the hash value instead of name
    char* trueName;          // optional
    NODE* next;              // use as a link list
} nodes[ARR_SIZE];           // base array
NODE *hashNode[MAP_SIZE];    // use for hash table
int nodeNums = 0;            // number of nodes added

/**
 * @brief Find node in the map.
 * 
 * @param name - key to find
 * @return NODE* pointer of the node searched. NULL if not found.
 */
NODE* findNode(char* name) {
    unsigned long long hName = Hash(name);
    NODE* temp = hashNode[hName % MAP_SIZE];    // get first node in hash table
    while (temp != 0 && temp->name != hName)    // find the name in all row
        temp = temp->next;
    return temp;
}

/**
 * @brief Add a node to the map.
 *
 * @param name - key to add.
 * @return NODE* pointer of the added node.
 */
NODE* addNode(char* name) {
    unsigned long long hName = Hash(name);
    int hid = hName % MAP_SIZE;     // get index in hash table
    nodes[nodeNums].name = hName;
    nodes[nodeNums].trueName = name;
    nodes[nodeNums].next = hashNode[hid]; // first node in hash table become next node
    hashNode[hid] = &nodes[nodeNums++];   // this node become the first node
    return hashNode[hid];
}