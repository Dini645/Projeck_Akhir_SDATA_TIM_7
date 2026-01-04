// drivethru.cpp
#include "drive_thru.h"

using namespace std;


void copyString(char* dest, const char* src, int maxLen) {
    int i = 0;
    while (src[i] != '\0' && i < maxLen - 1) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

bool stringsEqual(const char* str1, const char* str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) return false;
        i++;
    }
    return str1[i] == str2[i];
}

int stringLength(const char* str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

void clearScreen() {
    // Membersihkan layar dengan mencetak banyak newline
    for (int i = 0; i < 50; i++) {
        cout << "\n";
    }
}

bool isValidNIK(const char* nik) {
    
    int len = stringLength(nik);
    if (len < 4 || len > 20) return false;
    
    
    for (int i = 0; i < len; i++) {
        if (!((nik[i] >= 'A' && nik[i] <= 'Z') ||
              (nik[i] >= 'a' && nik[i] <= 'z') ||
              (nik[i] >= '0' && nik[i] <= '9'))) {
            return false;
        }
    }
    return true;
}


TreeNode::TreeNode(const char* n, const char* nik, int a) : amount(a), height(1), freq(0), ch('\0'), left(NULL), right(NULL) {
    copyString(name, n, 50);
    copyString(this->nik, nik, 20);
}

TreeNode::TreeNode(char c, int f) : amount(0), height(0), freq(f), ch(c), left(NULL), right(NULL) {
    name[0] = '\0';
    nik[0] = '\0';
}

QueueNode::QueueNode(Transaction* t) : transaction(t), next(NULL) {}

Item::Item() : price(0), quantity(0), next(NULL), id(0), cost(0) {
    name[0] = '\0';
    category[0] = '\0';
}

Item::Item(const char* n, int p, const char* c, int q) : 
    price(p), quantity(q), next(NULL), id(0), cost(0) {
    copyString(name, n, 50);
    copyString(category, c, 20);
}

Transaction::Transaction() : orderNumber(0), totalAmount(0), foodCount(0), 
                           drinkCount(0), next(NULL) {
    customerName[0] = '\0';
    customerNIK[0] = '\0';
    date[0] = '\0';
}

Transaction::Transaction(int num, const char* name, const char* nik, int total, int food, 
                       int drink, const char* dt) :
    orderNumber(num), totalAmount(total), foodCount(food), 
    drinkCount(drink), next(NULL) {
    copyString(customerName, name, 50);
    copyString(customerNIK, nik, 20);
    copyString(date, dt, 20);
}

Customer::Customer() : totalSpent(0), visitCount(0), next(NULL) {
    name[0] = '\0';
    nik[0] = '\0';
}

Customer::Customer(const char* n, const char* nik, int t) : totalSpent(t), visitCount(1), next(NULL) {
    copyString(name, n, 50);
    copyString(this->nik, nik, 20);
}

ShoppingCart::Node::Node() : data(NULL), next(NULL) {}

ShoppingCart::Node::Node(Item* d) : data(d), next(NULL) {}

HuffmanCoding::MinHeapNode::MinHeapNode(TreeNode* n) : node(n), next(NULL) {}


ShoppingCart::ShoppingCart() : top(NULL), itemCount(0) {
    customerName[0] = '\0';
    customerNIK[0] = '\0';
}

ShoppingCart::~ShoppingCart() {
    clearCart();
}

void ShoppingCart::push(Item* item) {
    Node* newNode = new Node(item);
    newNode->next = top;
    top = newNode;
    itemCount += item->quantity;
    cout << ">> " << item->name << " ditambahkan ke keranjang\n";
}

Item* ShoppingCart::pop() {
    if (top == NULL) return NULL;
    Node* temp = top;
    Item* item = top->data;
    top = top->next;
    itemCount -= item->quantity;
    delete temp;
    return item;
}

bool ShoppingCart::isEmpty() { 
    return top == NULL; 
}

void ShoppingCart::display() {
    if (isEmpty()) {
        cout << "\nKeranjang kosong.\n";
        return;
    }
    
    cout << "\n==================================================\n";
    cout << "               KERANJANG BELANJA\n";
    cout << "==================================================\n";
    
    if (stringLength(customerName) > 0) {
        cout << "Nama Pelanggan : " << customerName << "\n";
    }
    
    if (stringLength(customerNIK) > 0) {
        cout << "NIK Pelanggan  : " << customerNIK << "\n";
    }
    
    Node* temp = top;
    int itemNum = 1;
    int totalPrice = 0;
    int totalItems = 0;
    int foodItems = 0;
    int drinkItems = 0;
    
    cout << "\n--------------------------------------------------\n";
    cout << "No  Item                   Qty  Harga\n";
    cout << "--------------------------------------------------\n";
    
    while (temp != NULL) {
        int itemTotal = temp->data->price * temp->data->quantity;
        totalPrice += itemTotal;
        totalItems += temp->data->quantity;
        
        if (stringsEqual(temp->data->category, "makanan")) {
            foodItems += temp->data->quantity;
        } else {
            drinkItems += temp->data->quantity;
        }
        
        cout << itemNum << ".  " << temp->data->name;
        int nameLen = stringLength(temp->data->name);
        for(int i = nameLen; i < 23; i++) cout << " ";
        cout << temp->data->quantity << "   Rp " << itemTotal << "\n";
        
        temp = temp->next;
        itemNum++;
    }
    
    cout << "--------------------------------------------------\n";
    cout << "\nSTATISTIK KERANJANG:\n";
    cout << "Total Item    : " << totalItems << " buah\n";
    cout << "Makanan       : " << foodItems << " buah\n";
    cout << "Minuman       : " << drinkItems << " buah\n";
    cout << "Total Harga   : Rp " << totalPrice << "\n";
    cout << "==================================================\n";
}

int ShoppingCart::getTotalPrice() {
    int total = 0;
    Node* temp = top;
    while (temp != NULL) {
        total += temp->data->price * temp->data->quantity;
        temp = temp->next;
    }
    return total;
}

int ShoppingCart::getFoodCount() {
    int count = 0;
    Node* temp = top;
    while (temp != NULL) {
        if (stringsEqual(temp->data->category, "makanan")) {
            count += temp->data->quantity;
        }
        temp = temp->next;
    }
    return count;
}

int ShoppingCart::getDrinkCount() {
    int count = 0;
    Node* temp = top;
    while (temp != NULL) {
        if (stringsEqual(temp->data->category, "minuman")) {
            count += temp->data->quantity;
        }
        temp = temp->next;
    }
    return count;
}

int ShoppingCart::getTotalItems() {
    return itemCount;
}

bool ShoppingCart::cancelLastItem() {
    if (isEmpty()) {
        cout << "Keranjang kosong, tidak ada yang bisa dibatalkan.\n";
        return false;
    }
    Item* cancelled = pop();
    cout << "Item \"" << cancelled->name << "\" berhasil dibatalkan.\n";
    delete cancelled;
    return true;
}

void ShoppingCart::setCustomerName(const char* name) {
    copyString(customerName, name, 50);
    cout << ">> Nama pelanggan diset menjadi: " << name << "\n";
}

void ShoppingCart::getCustomerName(char* name) {
    copyString(name, customerName, 50);
}

void ShoppingCart::setCustomerNIK(const char* nik) {
    copyString(customerNIK, nik, 20);
    cout << ">> NIK pelanggan diset menjadi: " << nik << "\n";
}

void ShoppingCart::getCustomerNIK(char* nik) {
    copyString(nik, customerNIK, 20);
}

void ShoppingCart::clearCart() {
    while (!isEmpty()) {
        Item* item = pop();
        delete item;
    }
    itemCount = 0;
}

Queue Implementation
TransactionQueue::TransactionQueue() : front(NULL), rear(NULL), size(0) {}

TransactionQueue::~TransactionQueue() {
    while (!isEmpty()) {
        dequeue();
    }
}

void TransactionQueue::enqueue(Transaction* transaction) {
    QueueNode* newNode = new QueueNode(transaction);
    if (rear == NULL) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
    size++;
}

Transaction* TransactionQueue::dequeue() {
    if (isEmpty()) return NULL;
    
    QueueNode* temp = front;
    Transaction* transaction = front->transaction;
    front = front->next;
    
    if (front == NULL) rear = NULL;
    
    delete temp;
    size--;
    return transaction;
}

bool TransactionQueue::isEmpty() {
    return front == NULL;
}

int TransactionQueue::getSize() {
    return size;
}

void TransactionQueue::displayQueue() {
    if (isEmpty()) {
        cout << "\n>> Antrian transaksi kosong.\n";
        return;
    }
    
    cout << "\n==================================================\n";
    cout << "           ANTRIAN TRANSAKSI PENDING\n";
    cout << "==================================================\n";
    
    QueueNode* temp = front;
    int count = 1;
    
    cout << "\nNo  No.Pes  Nama Pelanggan        Total       NIK\n";
    cout << "--------------------------------------------------\n";
    
    while (temp != NULL) {
        cout << count << ".  ";
        cout << temp->transaction->orderNumber << "   ";
        
        if (stringLength(temp->transaction->customerName) > 0) {
            cout << temp->transaction->customerName;
            int nameLen = stringLength(temp->transaction->customerName);
            for(int i = nameLen; i < 22; i++) cout << " ";
        } else {
            cout << "Tanpa Nama            ";
        }
        
        cout << "Rp " << temp->transaction->totalAmount << "   ";
        if (stringLength(temp->transaction->customerNIK) > 0) {
            cout << temp->transaction->customerNIK;
        } else {
            cout << "Tanpa NIK";
        }
        cout << "\n";
        
        temp = temp->next;
        count++;
    }
    
    cout << "==================================================\n";
    cout << "Total dalam antrian: " << size << " transaksi\n";
}

Transaction* TransactionQueue::peek() {
    if (isEmpty()) return NULL;
    return front->transaction;
}

//BinaryTree 
CustomerBinaryTree::CustomerBinaryTree() : root(NULL) {}

CustomerBinaryTree::~CustomerBinaryTree() {
    destroyTree(root);
}

void CustomerBinaryTree::insertRecursive(TreeNode* &node, const char* name, const char* nik, int amount) {
    if (node == NULL) {
        node = new TreeNode(name, nik, amount);
        return;
    }
    
   
    int i = 0;
    while (nik[i] != '\0' && node->nik[i] != '\0') {
        if (nik[i] < node->nik[i]) {
            insertRecursive(node->left, name, nik, amount);
            return;
        } else if (nik[i] > node->nik[i]) {
            insertRecursive(node->right, name, nik, amount);
            return;
        }
        i++;
    }
    
   
    if (nik[i] == '\0' && node->nik[i] == '\0') {
        
        copyString(node->name, name, 50);
        node->amount += amount;
    } else if (nik[i] == '\0') {
        insertRecursive(node->left, name, nik, amount);
    } else {
        insertRecursive(node->right, name, nik, amount);
    }
}

void CustomerBinaryTree::insert(const char* name, const char* nik, int amount) {
    insertRecursive(root, name, nik, amount);
}

void CustomerBinaryTree::displayInOrder(TreeNode* node) {
    if (node == NULL) return;
    
    displayInOrder(node->left);
    cout << "Nama: " << node->name << ", NIK: " << node->nik 
         << ", Total: Rp " << node->amount << "\n";
    displayInOrder(node->right);
}

void CustomerBinaryTree::display() {
    if (root == NULL) {
        cout << "\n>> Binary Tree kosong.\n";
        return;
    }
    
    cout << "\n==================================================\n";
    cout << "       CUSTOMER BINARY TREE (In-Order)\n";
    cout << "==================================================\n";
    displayInOrder(root);
    cout << "==================================================\n";
}

TreeNode* CustomerBinaryTree::searchRecursive(TreeNode* node, const char* nik) {
    if (node == NULL) return NULL;
    
    if (stringsEqual(node->nik, nik)) return node;
    
    TreeNode* leftResult = searchRecursive(node->left, nik);
    if (leftResult != NULL) return leftResult;
    
    return searchRecursive(node->right, nik);
}

TreeNode* CustomerBinaryTree::search(const char* nik) {
    return searchRecursive(root, nik);
}

int CustomerBinaryTree::getHeight(TreeNode* node) {
    if (node == NULL) return 0;
    return 1 + max(getHeight(node->left), getHeight(node->right));
}

void CustomerBinaryTree::destroyTree(TreeNode* node) {
    if (node == NULL) return;
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

//AVLTree 
CustomerAVLTree::CustomerAVLTree() : root(NULL) {}

CustomerAVLTree::~CustomerAVLTree() {
    destroyTree(root);
}

int CustomerAVLTree::getHeight(TreeNode* node) {
    return node ? node->height : 0;
}

int CustomerAVLTree::getBalance(TreeNode* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

TreeNode* CustomerAVLTree::rightRotate(TreeNode* y) {
    TreeNode* x = y->left;
    TreeNode* T2 = x->right;
    
    x->right = y;
    y->left = T2;
    
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    
    return x;
}

TreeNode* CustomerAVLTree::leftRotate(TreeNode* x) {
    TreeNode* y = x->right;
    TreeNode* T2 = y->left;
    
    y->left = x;
    x->right = T2;
    
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    
    return y;
}

TreeNode* CustomerAVLTree::insertRecursive(TreeNode* node, const char* name, const char* nik, int amount) {
    if (node == NULL) return new TreeNode(name, nik, amount);
    
    
    int compare = 0;
    int i = 0;
    while (nik[i] != '\0' && node->nik[i] != '\0') {
        if (nik[i] < node->nik[i]) {
            compare = -1;
            break;
        } else if (nik[i] > node->nik[i]) {
            compare = 1;
            break;
        }
        i++;
    }
    
    if (compare == 0) {
        
        if (nik[i] == '\0' && node->nik[i] == '\0') {
            
            copyString(node->name, name, 50);
            node->amount += amount;
            return node;
        } else if (nik[i] == '\0') {
            compare = -1;
        } else {
            compare = 1;
        }
    }
    
    if (compare < 0)
        node->left = insertRecursive(node->left, name, nik, amount);
    else
        node->right = insertRecursive(node->right, name, nik, amount);
    
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    
    int balance = getBalance(node);
    
    if (balance > 1 && compare < 0)
        return rightRotate(node);
    
    if (balance < -1 && compare > 0)
        return leftRotate(node);
    
    if (balance > 1 && compare > 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    
    if (balance < -1 && compare < 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    
    return node;
}

void CustomerAVLTree::insert(const char* name, const char* nik, int amount) {
    root = insertRecursive(root, name, nik, amount);
}

void CustomerAVLTree::displayInOrder(TreeNode* node) {
    if (node == NULL) return;
    
    displayInOrder(node->left);
    cout << "Nama: " << node->name << ", NIK: " << node->nik 
         << ", Total: Rp " << node->amount 
         << ", Height: " << node->height << "\n";
    displayInOrder(node->right);
}

void CustomerAVLTree::display() {
    if (root == NULL) {
        cout << "\n>> AVL Tree kosong.\n";
        return;
    }
    
    cout << "\n==================================================\n";
    cout << "         CUSTOMER AVL TREE (In-Order)\n";
    cout << "==================================================\n";
    displayInOrder(root);
    cout << "==================================================\n";
    cout << "Tinggi tree: " << getHeight(root) << "\n";
}

TreeNode* CustomerAVLTree::searchRecursive(TreeNode* node, const char* nik) {
    if (node == NULL) return NULL;
    
    if (stringsEqual(node->nik, nik)) return node;
    
    TreeNode* leftResult = searchRecursive(node->left, nik);
    if (leftResult != NULL) return leftResult;
    
    return searchRecursive(node->right, nik);
}

TreeNode* CustomerAVLTree::search(const char* nik) {
    return searchRecursive(root, nik);
}

void CustomerAVLTree::destroyTree(TreeNode* node) {
    if (node == NULL) return;
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

// Huffman
HuffmanCoding::HuffmanCoding() : root(NULL), minHeapHead(NULL) {}

HuffmanCoding::~HuffmanCoding() {
    destroyHuffmanTree(root);
    
    while (minHeapHead) {
        MinHeapNode* temp = minHeapHead;
        minHeapHead = minHeapHead->next;
        delete temp;
    }
}

void HuffmanCoding::insertToMinHeap(TreeNode* node) {
    MinHeapNode* newNode = new MinHeapNode(node);
    
    if (!minHeapHead || node->freq < minHeapHead->node->freq) {
        newNode->next = minHeapHead;
        minHeapHead = newNode;
    } else {
        MinHeapNode* current = minHeapHead;
        while (current->next && current->next->node->freq < node->freq) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

TreeNode* HuffmanCoding::extractMin() {
    if (!minHeapHead) return NULL;
    
    MinHeapNode* temp = minHeapHead;
    TreeNode* node = temp->node;
    minHeapHead = minHeapHead->next;
    delete temp;
    return node;
}

void HuffmanCoding::buildTree(char data[], int freq[], int size) {
    destroyHuffmanTree(root);
    root = NULL;
    
    for (int i = 0; i < size; i++) {
        TreeNode* newNode = new TreeNode(data[i], freq[i]);
        insertToMinHeap(newNode);
    }
    
    while (minHeapHead && minHeapHead->next) {
        TreeNode* left = extractMin();
        TreeNode* right = extractMin();
        
        TreeNode* top = new TreeNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        
        insertToMinHeap(top);
    }
    
    if (minHeapHead) {
        root = extractMin();
    }
}

void HuffmanCoding::generateCodes(TreeNode* node, char* code, int depth, char huffmanCodes[][100]) {
    if (!node) return;
    
    if (!node->left && !node->right) {
        code[depth] = '\0';
        int idx = (unsigned char)node->ch;
        int i = 0;
        while (code[i] != '\0') {
            huffmanCodes[idx][i] = code[i];
            i++;
        }
        huffmanCodes[idx][i] = '\0';
    }
    
    if (node->left) {
        code[depth] = '0';
        generateCodes(node->left, code, depth + 1, huffmanCodes);
    }
    
    if (node->right) {
        code[depth] = '1';
        generateCodes(node->right, code, depth + 1, huffmanCodes);
    }
}

void HuffmanCoding::printCodes() {
    if (!root) {
        cout << "\n>> Huffman Tree belum dibangun.\n";
        return;
    }
    
    char huffmanCodes[256][100];
    for (int i = 0; i < 256; i++) {
        huffmanCodes[i][0] = '\0';
    }
    
    char code[100];
    generateCodes(root, code, 0, huffmanCodes);
    
    cout << "\n==================================================\n";
    cout << "             HUFFMAN CODES\n";
    cout << "==================================================\n";
    
    for (int i = 0; i < 256; i++) {
        if (huffmanCodes[i][0] != '\0') {
            if (i == ' ') {
                cout << "[SPACE]: " << huffmanCodes[i] << "\n";
            } else if (i == '\n') {
                cout << "[NEWLINE]: " << huffmanCodes[i] << "\n";
            } else {
                cout << (char)i << ": " << huffmanCodes[i] << "\n";
            }
        }
    }
    cout << "==================================================\n";
}

void HuffmanCoding::encode(const char* text, char* encoded) {
    if (!root) {
        encoded[0] = '\0';
        return;
    }
    
    char huffmanCodes[256][100];
    for (int i = 0; i < 256; i++) {
        huffmanCodes[i][0] = '\0';
    }
    
    char code[100];
    generateCodes(root, code, 0, huffmanCodes);
    
    int encodedPos = 0;
    int i = 0;
    while (text[i] != '\0') {
        int idx = (unsigned char)text[i];
        int j = 0;
        while (huffmanCodes[idx][j] != '\0') {
            encoded[encodedPos++] = huffmanCodes[idx][j++];
        }
        i++;
    }
    encoded[encodedPos] = '\0';
}

void HuffmanCoding::decode(const char* encodedText, char* decoded) {
    if (!root) {
        decoded[0] = '\0';
        return;
    }
    
    int decodedPos = 0;
    TreeNode* current = root;
    int i = 0;
    
    while (encodedText[i] != '\0') {
        if (encodedText[i] == '0') {
            current = current->left;
        } else {
            current = current->right;
        }
        
        if (!current->left && !current->right) {
            decoded[decodedPos++] = current->ch;
            current = root;
        }
        i++;
    }
    decoded[decodedPos] = '\0';
}

void HuffmanCoding::destroyHuffmanTree(TreeNode* node) {
    if (node == NULL) return;
    destroyHuffmanTree(node->left);
    destroyHuffmanTree(node->right);
    delete node;
}

TransactionHistory::TransactionHistory() : head(NULL), count(0), totalRevenue(0), 
                                         totalProfit(0), totalFoodSold(0), totalDrinkSold(0) {}

TransactionHistory::~TransactionHistory() {
    Transaction* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        delete temp;
    }
}

void TransactionHistory::addTransaction(int orderNum, const char* customerName, const char* nik, int total, 
                                       int food, int drink, const char* date) {
    Transaction* newTrans = new Transaction(orderNum, customerName, nik, total, food, drink, date);
    newTrans->next = head;
    head = newTrans;
    
    count++;
    totalRevenue += total;
    totalFoodSold += food;
    totalDrinkSold += drink;
    
    int cost = total * 60 / 100;
    totalProfit += (total - cost);
    
    if (stringLength(customerName) > 0 && stringLength(nik) > 0) {
        addToCustomerTree(customerName, nik, total);
        addToCustomerAVL(customerName, nik, total);
    }
}

void TransactionHistory::displayAllTransactions() {
    if (head == NULL) {
        cout << "\n>> Belum ada transaksi.\n";
        return;
    }
    
    cout << "\n================================================================================\n";
    cout << "                            RIWAYAT TRANSAKSI\n";
    cout << "================================================================================\n";
    
    Transaction* temp = head;
    int transNum = 1;
    
    cout << "\n--------------------------------------------------------------------------------\n";
    cout << "No  No.Pes  Nama Pelanggan        NIK              Total    Makan Minum Tanggal\n";
    cout << "--------------------------------------------------------------------------------\n";
    
    while (temp != NULL) {
        cout << transNum << ".  ";
        cout << temp->orderNumber << "   ";
        
        if (stringLength(temp->customerName) > 0) {
            cout << temp->customerName;
            int nameLen = stringLength(temp->customerName);
            for(int i = nameLen; i < 22; i++) cout << " ";
        } else {
            cout << "Tanpa Nama            ";
        }
        
        if (stringLength(temp->customerNIK) > 0) {
            cout << temp->customerNIK;
            int nikLen = stringLength(temp->customerNIK);
            for(int i = nikLen; i < 18; i++) cout << " ";
        } else {
            cout << "Tanpa NIK           ";
        }
        
        cout << "Rp " << temp->totalAmount << "   ";
        cout << temp->foodCount << "     ";
        cout << temp->drinkCount << "    ";
        cout << temp->date << "\n";
        
        temp = temp->next;
        transNum++;
    }
    
    cout << "--------------------------------------------------------------------------------\n";
    
    cout << "\nSUMMARY:\n";
    cout << "Total Transaksi : " << count << "\n";
    cout << "Total Pemasukan : Rp " << totalRevenue << "\n";
    cout << "Total Makanan   : " << totalFoodSold << " item\n";
    cout << "Total Minuman   : " << totalDrinkSold << " item\n";
    cout << "Total Item      : " << (totalFoodSold + totalDrinkSold) << " item\n";
    cout << "Rata-rata/Trans : Rp " << (count > 0 ? totalRevenue / count : 0) << "\n";
    cout << "================================================================================\n";
}

void TransactionHistory::displayStatistics() {
    if (head == NULL) {
        cout << "\n>> Belum ada data statistik.\n";
        return;
    }
    
    cout << "\n==================================================\n";
    cout << "           STATISTIK PENJUALAN & KEUNTUNGAN\n";
    cout << "==================================================\n";
    
    cout << "\nOVERVIEW PENJUALAN:\n";
    cout << "----------------------------------------------\n";
    cout << "Metric                    Value\n";
    cout << "----------------------------------------------\n";
    cout << "Total Transaksi           " << count << "\n";
    cout << "Total Pemasukan           Rp " << totalRevenue << "\n";
    cout << "Total Keuntungan          Rp " << totalProfit << "\n";
    cout << "Total Makanan Terjual     " << totalFoodSold << "\n";
    cout << "Total Minuman Terjual     " << totalDrinkSold << "\n";
    cout << "Total Item Terjual        " << (totalFoodSold + totalDrinkSold) << "\n";
    cout << "----------------------------------------------\n";
    
    if (count > 0) {
        float avgTransaction = (float)totalRevenue / count;
        float profitMargin = (float)totalProfit / totalRevenue * 100;
        float foodPercentage = (float)totalFoodSold / (totalFoodSold + totalDrinkSold) * 100;
        float drinkPercentage = (float)totalDrinkSold / (totalFoodSold + totalDrinkSold) * 100;
        
        cout << "\nANALISIS:\n";
        cout << "Rata-rata Transaksi   : Rp " << avgTransaction << "\n";
        cout << "Margin Keuntungan     : " << profitMargin << "%\n";
        cout << "Persentase Makanan    : " << foodPercentage << "%\n";
        cout << "Persentase Minuman    : " << drinkPercentage << "%\n";
        cout << "Rata-rata Item/Trans  : " << (float)(totalFoodSold + totalDrinkSold) / count << "\n";
    }
    
    cout << "==================================================\n";
}

void TransactionHistory::displayDailyReport() {
    cout << "\n==================================================\n";
    cout << "          LAPORAN HARIAN PENJUALAN\n";
    cout << "==================================================\n";
    
    cout << "\nTanggal: " << "Sistem Drive-Thru" << "\n\n";
    
    cout << "PERFORMA PENJUALAN:\n";
    cout << "------------------------------------\n";
    cout << "Metric                 Value\n";
    cout << "------------------------------------\n";
    cout << "Total Transaksi        " << count << "\n";
    cout << "Total Pemasukan        Rp " << totalRevenue << "\n";
    cout << "Total Keuntungan       Rp " << totalProfit << "\n";
    cout << "Total Makanan Terjual  " << totalFoodSold << "\n";
    cout << "Total Minuman Terjual  " << totalDrinkSold << "\n";
    cout << "------------------------------------\n";
    
    if (count > 0) {
        cout << "\nANALISIS HARIAN:\n";
        cout << "Rata-rata Transaksi : Rp " << totalRevenue / count << "\n";
        cout << "Estimasi Pendapatan Bulanan : Rp " << totalRevenue * 30 << "\n";
    }
    
    cout << "==================================================\n";
}

void TransactionHistory::saveTransactionsToFile() {
    ofstream file("transaksi_history.txt");
    if (file.is_open()) {
        file << "=== RIWAYAT TRANSAKSI DRIVE-THRU ===\n";
        file << "Tanggal Export: Sistem Drive-Thru\n\n";
        
        Transaction* temp = head;
        int transNum = 1;
        
        while (temp != NULL) {
            file << "Transaksi #" << transNum << "\n";
            file << "No. Pesanan  : " << temp->orderNumber << "\n";
            file << "Pelanggan    : " << (stringLength(temp->customerName) > 0 ? temp->customerName : "Tanpa Nama") << "\n";
            file << "NIK          : " << (stringLength(temp->customerNIK) > 0 ? temp->customerNIK : "Tanpa NIK") << "\n";
            file << "Total        : Rp " << temp->totalAmount << "\n";
            file << "Makanan      : " << temp->foodCount << " item\n";
            file << "Minuman      : " << temp->drinkCount << " item\n";
            file << "Waktu        : " << temp->date << "\n";
            file << "----------------------------------------\n";
            
            temp = temp->next;
            transNum++;
        }
        
        file << "\nSUMMARY:\n";
        file << "Total Transaksi: " << count << "\n";
        file << "Total Pemasukan: Rp " << totalRevenue << "\n";
        file << "Total Keuntungan: Rp " << totalProfit << "\n";
        file << "Total Makanan: " << totalFoodSold << "\n";
        file << "Total Minuman: " << totalDrinkSold << "\n";
        
        file.close();
        cout << ">> Riwayat transaksi disimpan ke 'transaksi_history.txt'\n";
    } else {
        cout << ">> Gagal menyimpan riwayat transaksi.\n";
    }
}

int TransactionHistory::getTotalTransactions() {
    return count;
}

int TransactionHistory::getTotalRevenue() {
    return totalRevenue;
}

int TransactionHistory::getTotalProfit() {
    return totalProfit;
}

Transaction* TransactionHistory::findTransaction(int orderNum) {
    Transaction* temp = head;
    while (temp != NULL) {
        if (temp->orderNumber == orderNum) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

Transaction* TransactionHistory::searchTransactionByCustomer(const char* customerName) {
    Transaction* temp = head;
    while (temp != NULL) {
        if (stringsEqual(temp->customerName, customerName)) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

Transaction* TransactionHistory::searchTransactionByNIK(const char* nik) {
    Transaction* temp = head;
    while (temp != NULL) {
        if (stringsEqual(temp->customerNIK, nik)) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void TransactionHistory::searchTransactionByDate(const char* date) {
    if (head == NULL) {
        cout << "\n>> Belum ada transaksi.\n";
        return;
    }
    
    Transaction* temp = head;
    int foundCount = 0;
    
    cout << "\n==================================================\n";
    cout << "       HASIL PENCARIAN BERDASARKAN TANGGAL: " << date << "\n";
    cout << "==================================================\n";
    
    cout << "\nNo.Pes  Nama Pelanggan        NIK              Total    Makan Minum\n";
    cout << "--------------------------------------------------------------------\n";
    
    while (temp != NULL) {
        if (stringsEqual(temp->date, date)) {
            cout << temp->orderNumber << "   ";
            
            if (stringLength(temp->customerName) > 0) {
                cout << temp->customerName;
                int nameLen = stringLength(temp->customerName);
                for(int i = nameLen; i < 22; i++) cout << " ";
            } else {
                cout << "Tanpa Nama            ";
            }
            
            if (stringLength(temp->customerNIK) > 0) {
                cout << temp->customerNIK;
                int nikLen = stringLength(temp->customerNIK);
                for(int i = nikLen; i < 18; i++) cout << " ";
            } else {
                cout << "Tanpa NIK           ";
            }
            
            cout << "Rp " << temp->totalAmount << "   ";
            cout << temp->foodCount << "     ";
            cout << temp->drinkCount << "\n";
            
            foundCount++;
        }
        temp = temp->next;
    }
    
    if (foundCount == 0) {
        cout << ">> Tidak ditemukan transaksi pada tanggal " << date << "\n";
    } else {
        cout << "\n>> Ditemukan " << foundCount << " transaksi pada tanggal " << date << "\n";
    }
    cout << "==================================================\n";
}

void TransactionHistory::searchTransactionByAmountRange(int minAmount, int maxAmount) {
    if (head == NULL) {
        cout << "\n>> Belum ada transaksi.\n";
        return;
    }
    
    Transaction* temp = head;
    int foundCount = 0;
    
    cout << "\n==================================================\n";
    cout << "  HASIL PENCARIAN BERDASARKAN RANGE HARGA: Rp " 
         << minAmount << " - Rp " << maxAmount << "\n";
    cout << "==================================================\n";
    
    cout << "\nNo.Pes  Nama Pelanggan        NIK              Total    Makan Minum Tanggal\n";
    cout << "------------------------------------------------------------------------------\n";
    
    while (temp != NULL) {
        if (temp->totalAmount >= minAmount && temp->totalAmount <= maxAmount) {
            cout << temp->orderNumber << "   ";
            
            if (stringLength(temp->customerName) > 0) {
                cout << temp->customerName;
                int nameLen = stringLength(temp->customerName);
                for(int i = nameLen; i < 22; i++) cout << " ";
            } else {
                cout << "Tanpa Nama            ";
            }
            
            if (stringLength(temp->customerNIK) > 0) {
                cout << temp->customerNIK;
                int nikLen = stringLength(temp->customerNIK);
                for(int i = nikLen; i < 18; i++) cout << " ";
            } else {
                cout << "Tanpa NIK           ";
            }
            
            cout << "Rp " << temp->totalAmount << "   ";
            cout << temp->foodCount << "     ";
            cout << temp->drinkCount << "    ";
            cout << temp->date << "\n";
            
            foundCount++;
        }
        temp = temp->next;
    }
    
    if (foundCount == 0) {
        cout << ">> Tidak ditemukan transaksi dalam range harga tersebut\n";
    } else {
        cout << "\n>> Ditemukan " << foundCount << " transaksi\n";
    }
    cout << "==================================================\n";
}

void TransactionHistory::displayTransactionDetails(Transaction* trans) {
    if (trans == NULL) {
        cout << "\n>> Transaksi tidak ditemukan.\n";
        return;
    }
    
    cout << "\n==================================================\n";
    cout << "           DETAIL TRANSAKSI #" << trans->orderNumber << "\n";
    cout << "==================================================\n";
    cout << "No. Pesanan    : " << trans->orderNumber << "\n";
    cout << "Nama Pelanggan : " << (stringLength(trans->customerName) > 0 ? trans->customerName : "Tanpa Nama") << "\n";
    cout << "NIK Pelanggan  : " << (stringLength(trans->customerNIK) > 0 ? trans->customerNIK : "Tanpa NIK") << "\n";
    cout << "Total Harga    : Rp " << trans->totalAmount << "\n";
    cout << "Jumlah Makanan : " << trans->foodCount << " item\n";
    cout << "Jumlah Minuman : " << trans->drinkCount << " item\n";
    cout << "Total Item     : " << (trans->foodCount + trans->drinkCount) << " item\n";
    cout << "Tanggal        : " << trans->date << "\n";
    
    int cost = trans->totalAmount * 60 / 100;
    int profit = trans->totalAmount - cost;
    float profitMargin = (float)profit / trans->totalAmount * 100;
    
    cout << "Perkiraan Biaya: Rp " << cost << "\n";
    cout << "Perkiraan Untung: Rp " << profit << " (" << profitMargin << "%)\n";
    cout << "==================================================\n";
}

void TransactionHistory::searchTransactionMenu() {
    int searchChoice;
    
    do {
        clearScreen();
        cout << "\n==================================================\n";
        cout << "           MENU PENCARIAN TRANSAKSI\n";
        cout << "==================================================\n";
        cout << "1. Cari Berdasarkan Nomor Pesanan\n";
        cout << "2. Cari Berdasarkan Nama Pelanggan\n";
        cout << "3. Cari Berdasarkan NIK Pelanggan\n";
        cout << "4. Cari Berdasarkan Tanggal\n";
        cout << "5. Cari Berdasarkan Range Harga\n";
        cout << "0. Kembali ke Menu Admin\n";
        cout << "\nPilihan: ";
        cin >> searchChoice;
        
        switch (searchChoice) {
            case 1: {
                int orderNum;
                cout << "\nMasukkan nomor pesanan: ";
                cin >> orderNum;
                
                Transaction* found = findTransaction(orderNum);
                if (found != NULL) {
                    displayTransactionDetails(found);
                } else {
                    cout << "\n>> Transaksi dengan nomor " << orderNum << " tidak ditemukan.\n";
                }
                break;
            }
                
            case 2: {
                char customerName[50];
                cout << "\nMasukkan nama pelanggan: ";
                cin.ignore();
                cin.getline(customerName, 50);
                
                Transaction* found = searchTransactionByCustomer(customerName);
                if (found != NULL) {
                    cout << "\n>> Transaksi ditemukan untuk pelanggan " << customerName << ":\n";
                    displayTransactionDetails(found);
                    
                    cout << "\n>> Semua transaksi dari " << customerName << ":\n";
                    cout << "--------------------------------------------------\n";
                    Transaction* temp = head;
                    int transCount = 0;
                    int totalSpent = 0;
                    
                    while (temp != NULL) {
                        if (stringsEqual(temp->customerName, customerName)) {
                            cout << "Pesanan #" << temp->orderNumber << ": Rp " 
                                 << temp->totalAmount << " (" << temp->date << ")\n";
                            totalSpent += temp->totalAmount;
                            transCount++;
                        }
                        temp = temp->next;
                    }
                    
                    cout << "--------------------------------------------------\n";
                    cout << "Total transaksi: " << transCount << "\n";
                    cout << "Total pengeluaran: Rp " << totalSpent << "\n";
                    if (transCount > 0) {
                        cout << "Rata-rata per transaksi: Rp " << totalSpent / transCount << "\n";
                    }
                } else {
                    cout << "\n>> Tidak ditemukan transaksi untuk pelanggan " << customerName << "\n";
                }
                break;
            }
                
            case 3: {
                char nik[20];
                cout << "\nMasukkan NIK pelanggan: ";
                cin.ignore();
                cin.getline(nik, 20);
                
                if (!isValidNIK(nik)) {
                    cout << "\n>> Format NIK tidak valid! NIK harus 4-20 karakter (huruf/angka).\n";
                    break;
                }
                
                Transaction* found = searchTransactionByNIK(nik);
                if (found != NULL) {
                    cout << "\n>> Transaksi ditemukan untuk NIK " << nik << ":\n";
                    displayTransactionDetails(found);
                    
                    cout << "\n>> Semua transaksi dari NIK " << nik << ":\n";
                    cout << "--------------------------------------------------\n";
                    Transaction* temp = head;
                    int transCount = 0;
                    int totalSpent = 0;
                    
                    while (temp != NULL) {
                        if (stringsEqual(temp->customerNIK, nik)) {
                            cout << "Pesanan #" << temp->orderNumber << ": Rp " 
                                 << temp->totalAmount << " (" << temp->date << ")\n";
                            totalSpent += temp->totalAmount;
                            transCount++;
                        }
                        temp = temp->next;
                    }
                    
                    cout << "--------------------------------------------------\n";
                    cout << "Total transaksi: " << transCount << "\n";
                    cout << "Total pengeluaran: Rp " << totalSpent << "\n";
                    if (transCount > 0) {
                        cout << "Rata-rata per transaksi: Rp " << totalSpent / transCount << "\n";
                    }
                    
                    cout << "\n>> Data pelanggan dengan NIK " << nik << ":\n";
                    cout << "Nama: " << found->customerName << "\n";
                    cout << "Total pengeluaran: Rp " << totalSpent << "\n";
                    cout << "Frekuensi pesanan: " << transCount << "\n";
                } else {
                    cout << "\n>> Tidak ditemukan transaksi untuk NIK " << nik << "\n";
                }
                break;
            }
                
            case 4: {
                char date[20];
                cout << "\nMasukkan tanggal (format: DD-MM-YYYY): ";
                cin.ignore();
                cin.getline(date, 20);
                
                searchTransactionByDate(date);
                break;
            }
                
            case 5: {
                int minAmount, maxAmount;
                cout << "\nMasukkan harga minimum: Rp ";
                cin >> minAmount;
                cout << "Masukkan harga maksimum: Rp ";
                cin >> maxAmount;
                
                if (minAmount <= maxAmount) {
                    searchTransactionByAmountRange(minAmount, maxAmount);
                } else {
                    cout << "\n>> Harga minimum tidak boleh lebih besar dari harga maksimum.\n";
                }
                break;
            }
                
            case 0:
                cout << "\nKembali ke menu admin...\n";
                break;
                
            default:
                cout << "\nPilihan tidak valid!\n";
        }
        
        if (searchChoice != 0) {
            cout << "\nTekan Enter untuk melanjutkan...";
            cin.ignore();
            cin.get();
        }
        
    } while (searchChoice != 0);
}

int TransactionHistory::getFoodSold() {
    return totalFoodSold;
}

int TransactionHistory::getDrinkSold() {
    return totalDrinkSold;
}

void TransactionHistory::addToPendingQueue(Transaction* transaction) {
    pendingQueue.enqueue(transaction);
    cout << ">> Transaksi ditambahkan ke antrian pending\n";
}

void TransactionHistory::processPendingQueue() {
    if (pendingQueue.isEmpty()) {
        cout << "\n>> Tidak ada transaksi dalam antrian pending\n";
        return;
    }
    
    int processed = 0;
    while (!pendingQueue.isEmpty()) {
        Transaction* trans = pendingQueue.dequeue();
        cout << ">> Memproses transaksi #" << trans->orderNumber 
             << " - " << trans->customerName << " (" << trans->customerNIK 
             << ") - Rp " << trans->totalAmount << "\n";
        delete trans;
        processed++;
    }
    
    cout << ">> " << processed << " transaksi berhasil diproses\n";
}

void TransactionHistory::displayPendingQueue() {
    pendingQueue.displayQueue();
}

void TransactionHistory::addToCustomerTree(const char* name, const char* nik, int amount) {
    customerTree.insert(name, nik, amount);
}

void TransactionHistory::addToCustomerAVL(const char* name, const char* nik, int amount) {
    customerAVL.insert(name, nik, amount);
}

void TransactionHistory::displayCustomerTree() {
    customerTree.display();
}

void TransactionHistory::displayCustomerAVL() {
    customerAVL.display();
}

void TransactionHistory::processHuffmanDemo() {
    cout << "\n==================================================\n";
    cout << "           DEMO HUFFMAN CODING\n";
    cout << "==================================================\n";
    
    char data[] = {'F', 'A', 'S', 'T', 'F', 'O', 'O', 'D'};
    int freq[] = {5, 9, 12, 13, 5, 15, 15, 1};
    
    huffman.buildTree(data, freq, 8);
    
    cout << "\n1. Huffman Codes:\n";
    huffman.printCodes();
    
    char text[] = "FASTFOOD";
    char encoded[1000];
    char decoded[100];
    
    huffman.encode(text, encoded);
    huffman.decode(encoded, decoded);
    
    cout << "\n2. Encode teks \"" << text << "\":\n";
    cout << "Encoded: " << encoded << "\n";
    cout << "Decoded: " << decoded << "\n";
    
    cout << "\n3. Kompresi data menu makanan:\n";
    char menuText[] = "BURGERFRENCHFRIESCHICKENNUGGETSPIZZA";
    cout << "Teks asli: " << menuText << "\n";
    
    char menuData[] = {'B', 'U', 'R', 'G', 'E', 'F', 'N', 'C', 'H', 'I', 'K', 'P', 'Z', 'A', 'S'};
    int menuFreq[] = {2, 2, 4, 2, 4, 3, 2, 1, 1, 2, 1, 1, 1, 1, 1};
    
    HuffmanCoding menuHuffman;
    menuHuffman.buildTree(menuData, menuFreq, 15);
    
    char menuEncoded[1000];
    menuHuffman.encode(menuText, menuEncoded);
    cout << "Encoded: " << menuEncoded << "\n";
    
    int originalBits = stringLength(menuText) * 8;
    int encodedBits = stringLength(menuEncoded);
    float compressionRatio = (float)encodedBits / originalBits * 100;
    cout << "Rasio kompresi: " << compressionRatio << "%\n";
    
    cout << "==================================================\n";
}


CustomerManager::CustomerManager() : head(NULL), count(0) {}

CustomerManager::~CustomerManager() {
    Customer* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        delete temp;
    }
}

void CustomerManager::addCustomer(const char* name, const char* nik, int total) {
    Customer* existing = findCustomerByNIK(nik);
    if (existing != NULL) {
        existing->totalSpent += total;
        existing->visitCount++;
        
        if (!stringsEqual(existing->name, name)) {
            cout << ">> Info: Nama pelanggan diupdate dari '" << existing->name 
                 << "' ke '" << name << "' untuk NIK " << nik << "\n";
            copyString(existing->name, name, 50);
        }
    } else {
        Customer* newCustomer = new Customer(name, nik, total);
        newCustomer->next = head;
        head = newCustomer;
        count++;
    }
}

void CustomerManager::displayAllCustomers() {
    if (head == NULL) {
        cout << "\n>> Belum ada data pelanggan.\n";
        return;
    }
    
    cout << "\n==================================================\n";
    cout << "               DAFTAR PELANGGAN\n";
    cout << "==================================================\n";
    
    Customer* temp = head;
    int custNum = 1;
    int totalRevenue = 0;
    
    cout << "\n--------------------------------------------------------------------------------\n";
    cout << "No  Nama Pelanggan           NIK                Total Belanja Kunjungan\n";
    cout << "--------------------------------------------------------------------------------\n";
    
    while (temp != NULL) {
        cout << custNum << ".  " << temp->name;
        int nameLen = stringLength(temp->name);
        for(int i = nameLen; i < 25; i++) cout << " ";
        
        cout << temp->nik;
        int nikLen = stringLength(temp->nik);
        for(int i = nikLen; i < 20; i++) cout << " ";
        
        cout << "Rp " << temp->totalSpent << "       ";
        cout << temp->visitCount << "\n";
        
        totalRevenue += temp->totalSpent;
        temp = temp->next;
        custNum++;
    }
    
    cout << "--------------------------------------------------------------------------------\n";
    
    cout << "\nSTATISTIK PELANGGAN:\n";
    cout << "Total Pelanggan    : " << count << " orang\n";
    cout << "Total Transaksi    : Rp " << totalRevenue << "\n";
    cout << "Rata-rata Belanja  : Rp " << (count > 0 ? totalRevenue / count : 0) << "\n";
    
    Customer* topSpender = getTopSpender();
    if (topSpender) {
        cout << "Top Spender        : " << topSpender->name 
             << " (" << topSpender->nik << ") - Rp " << topSpender->totalSpent << "\n";
    }
    
    cout << "==================================================\n";
}

Customer* CustomerManager::findCustomer(const char* name) {
    Customer* temp = head;
    while (temp != NULL) {
        if (stringsEqual(temp->name, name)) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

Customer* CustomerManager::findCustomerByNIK(const char* nik) {
    Customer* temp = head;
    while (temp != NULL) {
        if (stringsEqual(temp->nik, nik)) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void CustomerManager::searchCustomerByName(const char* name) {
    Customer* found = findCustomer(name);
    if (found != NULL) {
        cout << "\n==================================================\n";
        cout << "           DATA PELANGGAN DITEMUKAN\n";
        cout << "==================================================\n";
        cout << "Nama Pelanggan : " << found->name << "\n";
        cout << "NIK Pelanggan  : " << found->nik << "\n";
        cout << "Total Belanja  : Rp " << found->totalSpent << "\n";
        cout << "Jumlah Kunjungan: " << found->visitCount << "\n";
        cout << "Rata-rata Belanja: Rp " << (found->visitCount > 0 ? found->totalSpent / found->visitCount : 0) << "\n";
        
        cout << "Kategori       : ";
        if (found->totalSpent > 100000) {
            cout << "Pelanggan Premium (Rp 100.000+)\n";
        } else if (found->totalSpent > 50000) {
            cout << "Pelanggan Reguler (Rp 50.000 - 100.000)\n";
        } else {
            cout << "Pelanggan Baru (< Rp 50.000)\n";
        }
        cout << "==================================================\n";
    } else {
        cout << "\n>> Pelanggan dengan nama '" << name << "' tidak ditemukan.\n";
    }
}

void CustomerManager::searchCustomerByNIK(const char* nik) {
    Customer* found = findCustomerByNIK(nik);
    if (found != NULL) {
        cout << "\n==================================================\n";
        cout << "           DATA PELANGGAN DITEMUKAN (BERDASARKAN NIK)\n";
        cout << "==================================================\n";
        cout << "NIK Pelanggan  : " << found->nik << "\n";
        cout << "Nama Pelanggan : " << found->name << "\n";
        cout << "Total Belanja  : Rp " << found->totalSpent << "\n";
        cout << "Jumlah Kunjungan: " << found->visitCount << "\n";
        cout << "Rata-rata Belanja: Rp " << (found->visitCount > 0 ? found->totalSpent / found->visitCount : 0) << "\n";
        
        cout << "Kategori       : ";
        if (found->totalSpent > 100000) {
            cout << "Pelanggan Premium (Rp 100.000+)\n";
        } else if (found->totalSpent > 50000) {
            cout << "Pelanggan Reguler (Rp 50.000 - 100.000)\n";
        } else {
            cout << "Pelanggan Baru (< Rp 50.000)\n";
        }
        cout << "==================================================\n";
    } else {
        cout << "\n>> Pelanggan dengan NIK '" << nik << "' tidak ditemukan.\n";
    }
}

int CustomerManager::getCustomerCount() {
    return count;
}

void CustomerManager::saveCustomersToFile() {
    ofstream file("pelanggan_data.txt");
    if (file.is_open()) {
        file << "=== DATA PELANGGAN DRIVE-THRU ===\n";
        file << "Tanggal Export: Sistem Drive-Thru\n\n";
        
        Customer* temp = head;
        while (temp != NULL) {
            file << "Nama: " << temp->name << "\n";
            file << "NIK: " << temp->nik << "\n";
            file << "Total Belanja: Rp " << temp->totalSpent << "\n";
            file << "Kunjungan: " << temp->visitCount << "\n";
            file << "------------------------------\n";
            temp = temp->next;
        }
        
        file.close();
        cout << ">> Data pelanggan disimpan ke 'pelanggan_data.txt'\n";
    }
}

Customer* CustomerManager::getTopSpender() {
    if (head == NULL) return NULL;
    
    Customer* top = head;
    Customer* temp = head->next;
    
    while (temp != NULL) {
        if (temp->totalSpent > top->totalSpent) {
            top = temp;
        }
        temp = temp->next;
    }
    return top;
}


DriveThruSystem::DriveThruSystem() : orderCounter(1001) {
    copyString(adminPassword, "admin123", 20);
    initializeMenu();
}

void DriveThruSystem::initializeMenu() {
    
    copyString(menuItems[0].name, "Burger Special", 50);
    menuItems[0].id = 1;
    menuItems[0].price = 35000;
    copyString(menuItems[0].category, "makanan", 20);
    menuItems[0].cost = 15000;
    
    copyString(menuItems[1].name, "French Fries", 50);
    menuItems[1].id = 2;
    menuItems[1].price = 20000;
    copyString(menuItems[1].category, "makanan", 20);
    menuItems[1].cost = 8000;
    
    copyString(menuItems[2].name, "Chicken Nuggets", 50);
    menuItems[2].id = 3;
    menuItems[2].price = 25000;
    copyString(menuItems[2].category, "makanan", 20);
    menuItems[2].cost = 12000;
    
    copyString(menuItems[3].name, "Pizza Slice", 50);
    menuItems[3].id = 4;
    menuItems[3].price = 30000;
    copyString(menuItems[3].category, "makanan", 20);
    menuItems[3].cost = 18000;
    
    copyString(menuItems[4].name, "Hot Dog", 50);
    menuItems[4].id = 5;
    menuItems[4].price = 22000;
    copyString(menuItems[4].category, "makanan", 20);
    menuItems[4].cost = 10000;
    
    
    copyString(menuItems[5].name, "Soft Drink", 50);
    menuItems[5].id = 6;
    menuItems[5].price = 12000;
    copyString(menuItems[5].category, "minuman", 20);
    menuItems[5].cost = 3000;
    
    copyString(menuItems[6].name, "Ice Cream Sundae", 50);
    menuItems[6].id = 7;
    menuItems[6].price = 15000;
    copyString(menuItems[6].category, "minuman", 20);
    menuItems[6].cost = 5000;
    
    copyString(menuItems[7].name, "Chocolate Milkshake", 50);
    menuItems[7].id = 8;
    menuItems[7].price = 22000;
    copyString(menuItems[7].category, "minuman", 20);
    menuItems[7].cost = 8000;
    
    copyString(menuItems[8].name, "Vanilla Milkshake", 50);
    menuItems[8].id = 9;
    menuItems[8].price = 22000;
    copyString(menuItems[8].category, "minuman", 20);
    menuItems[8].cost = 8000;
    
    copyString(menuItems[9].name, "Iced Tea", 50);
    menuItems[9].id = 10;
    menuItems[9].price = 10000;
    copyString(menuItems[9].category, "minuman", 20);
    menuItems[9].cost = 2000;
}

Item* DriveThruSystem::createItem(const char* name, int price, const char* category, int quantity) {
    return new Item(name, price, category, quantity);
}

void DriveThruSystem::displayMainMenu() {
    cout << "\nMENU UTAMA:\n";
    cout << "1. Mode Pelanggan\n";
    cout << "2. Mode Admin\n";
    cout << "3. Keluar\n";
    cout << "\nPilihan: ";
}

void DriveThruSystem::displayAdminMenu() {
    cout << "\n==================================================\n";
    cout << "           MENU ADMIN - STATISTIK\n";
    cout << "==================================================\n";
    
    cout << "\nOPSI ADMIN:\n";
    cout << "1. Lihat Riwayat Transaksi\n";
    cout << "2. Cari Transaksi\n";
    cout << "3. Lihat Statistik Penjualan & Keuntungan\n";
    cout << "4. Lihat Data Pelanggan\n";
    cout << "5. Cari Pelanggan\n";
    cout << "6. Laporan Harian\n";
    cout << "7. Simpan Data ke File\n";
    cout << "8. Data Struktur Lanjut (Queue, Tree, Huffman)\n";
    cout << "0. Kembali ke Menu Utama\n";
    cout << "\nPilihan: ";
}

void DriveThruSystem::displayCustomerMenu() {
    cout << "\n==================================================\n";
    cout << "          MENU PELANGGAN\n";
    cout << "==================================================\n";
    
    cout << "\nOPSI PELANGGAN:\n";
    cout << "1. Lihat Menu\n";
    cout << "2. Masukkan Data Diri (Nama & NIK)\n";
    cout << "3. Tambah Makanan\n";
    cout << "4. Tambah Minuman\n";
    cout << "5. Lihat Keranjang\n";
    cout << "6. Batalkan Item\n";
    cout << "7. Checkout & Bayar\n";
    cout << "8. Kembali ke Menu Utama\n";
    cout << "\nPilihan: ";
}

bool DriveThruSystem::verifyAdmin() {
    char password[20];
    cout << "\nMasukkan password admin: ";
    cin >> password;
    
    if (stringsEqual(password, adminPassword)) {
        cout << ">> Akses admin diberikan!\n";
        return true;
    } else {
        cout << ">> Password salah!\n";
        return false;
    }
}

void DriveThruSystem::printReceipt(int orderNum, const char* customerName, const char* nik, int total, 
                                 int food, int drink) {
    cout << "\n==================================================\n";
    cout << "         STRUK PESANAN #" << orderNum << "\n";
    cout << "==================================================\n";
    
    if (stringLength(customerName) > 0) {
        cout << "Atas nama: " << customerName << "\n";
    }
    
    if (stringLength(nik) > 0) {
        cout << "NIK       : " << nik << "\n";
    }
    
    cout << "\nDetail Pesanan:\n";
    cout << "----------------------------------------------\n";
    cout << "Total Item: " << (food + drink) << "\n";
    cout << "Makanan   : " << food << "\n";
    cout << "Minuman   : " << drink << "\n";
    cout << "Total     : Rp " << total << "\n";
    cout << "==================================================\n";
    cout << " Terima kasih atas pesanan Anda!\n";
    cout << "==================================================\n";
    
    ofstream file("struk.txt", ios::app);
    if (file.is_open()) {
        file << "\n==================================================\n";
        file << "         STRUK PESANAN #" << orderNum << "\n";
        file << "==================================================\n";
        if (stringLength(customerName) > 0) {
            file << "Atas nama: " << customerName << "\n";
        }
        if (stringLength(nik) > 0) {
            file << "NIK      : " << nik << "\n";
        }
        file << "Total: Rp " << total << "\n";
        file << "Tanggal: Sistem Drive-Thru\n";
        file << "==================================================\n\n";
        file.close();
    }
}

void DriveThruSystem::runAdminMode() {
    int choice;
    
    do {
        clearScreen();
        displayAdminMenu();
        cin >> choice;
        
        switch (choice) {
            case 1:
                clearScreen();
                transactions.displayAllTransactions();
                break;
                
            case 2:
                clearScreen();
                transactions.searchTransactionMenu();
                break;
                
            case 3:
                clearScreen();
                transactions.displayStatistics();
                break;
                
            case 4:
                clearScreen();
                customers.displayAllCustomers();
                break;
                
            case 5:
                clearScreen();
                {
                    int searchChoice;
                    cout << "\n==================================================\n";
                    cout << "           PENCARIAN PELANGGAN\n";
                    cout << "==================================================\n";
                    cout << "1. Cari berdasarkan Nama\n";
                    cout << "2. Cari berdasarkan NIK\n";
                    cout << "0. Kembali\n";
                    cout << "\nPilihan: ";
                    cin >> searchChoice;
                    
                    if (searchChoice == 1) {
                        char searchName[50];
                        cout << "\nMasukkan nama pelanggan yang dicari: ";
                        cin.ignore();
                        cin.getline(searchName, 50);
                        customers.searchCustomerByName(searchName);
                    } else if (searchChoice == 2) {
                        char searchNIK[20];
                        cout << "\nMasukkan NIK pelanggan yang dicari: ";
                        cin.ignore();
                        cin.getline(searchNIK, 20);
                        customers.searchCustomerByNIK(searchNIK);
                    }
                }
                break;
                
            case 6:
                clearScreen();
                transactions.displayDailyReport();
                break;
                
            case 7:
                clearScreen();
                transactions.saveTransactionsToFile();
                customers.saveCustomersToFile();
                cout << ">> Struk tersimpan di file 'struk.txt'\n";
                break;
                
            case 8: {
                clearScreen();
                int subChoice;
                do {
                    cout << "\n==================================================\n";
                    cout << "       DATA STRUKTUR LANJUT\n";
                    cout << "==================================================\n";
                    cout << "1. Lihat Antrian Transaksi Pending\n";
                    cout << "2. Proses Antrian Transaksi\n";
                    cout << "3. Lihat Customer Binary Tree\n";
                    cout << "4. Lihat Customer AVL Tree\n";
                    cout << "5. Demo Huffman Coding\n";
                    cout << "0. Kembali ke Menu Admin\n";
                    cout << "\nPilihan: ";
                    cin >> subChoice;
                    
                    clearScreen();
                    switch (subChoice) {
                        case 1:
                            transactions.displayPendingQueue();
                            break;
                        case 2:
                            transactions.processPendingQueue();
                            break;
                        case 3:
                            transactions.displayCustomerTree();
                            break;
                        case 4:
                            transactions.displayCustomerAVL();
                            break;
                        case 5:
                            transactions.processHuffmanDemo();
                            break;
                        case 0:
                            cout << "\nKembali ke menu admin...\n";
                            break;
                        default:
                            cout << "\nPilihan tidak valid!\n";
                    }
                    
                    if (subChoice != 0) {
                        cout << "\nTekan Enter untuk melanjutkan...";
                        cin.ignore();
                        cin.get();
                        clearScreen();
                    }
                    
                } while (subChoice != 0);
                break;
            }
                
            case 0:
                cout << "\nKembali ke menu utama...\n";
                break;
                
            default:
                cout << "\nPilihan tidak valid!\n";
        }
        
        if (choice != 0) {
            cout << "\nTekan Enter untuk melanjutkan...";
            cin.ignore();
            cin.get();
        }
        
    } while (choice != 0);
}

void DriveThruSystem::runCustomerMode() {
    int choice;
    char name[50];
    char nik[20];
    
    do {
        clearScreen();
        displayCustomerMenu();
        cin >> choice;
        
        switch (choice) {
            case 1:
                clearScreen();
                cout << "\n==================================================\n";
                cout << "                   MENU MAKANAN\n";
                cout << "==================================================\n";
                for (int i = 0; i < 5; i++) {
                    cout << menuItems[i].id << ". " << menuItems[i].name 
                         << " - Rp " << menuItems[i].price << "\n";
                }
                cout << "\n                   MENU MINUMAN\n";
                cout << "==================================================\n";
                for (int i = 5; i < 10; i++) {
                    cout << menuItems[i].id << ". " << menuItems[i].name 
                         << " - Rp " << menuItems[i].price << "\n";
                }
                cout << "==================================================\n";
                break;
                
            case 2:
                clearScreen();
                cout << "\nMasukkan data diri:\n";
                cout << "Nama pelanggan: ";
                cin.ignore();
                cin.getline(name, 50);
                cart.setCustomerName(name);
                
                cout << "NIK (minimal 4 karakter, huruf/angka): ";
                cin.getline(nik, 20);
                
                if (isValidNIK(nik)) {
                    cart.setCustomerNIK(nik);
                    cout << ">> NIK valid dan berhasil disimpan.\n";
                } else {
                    cout << ">> Format NIK tidak valid! Harus 4-20 karakter (huruf/angka).\n";
                    cout << ">> Contoh NIK yang valid: ABCD123, USER001, CUST2024\n";
                    cout << ">> Anda masih bisa memesan, tetapi data tidak akan tersimpan lengkap.\n";
                }
                break;
                
            case 3:
                clearScreen();
                int foodChoice, qty;
                cout << "\nPilih makanan (1-5): ";
                cin >> foodChoice;
                if (foodChoice >= 1 && foodChoice <= 5) {
                    cout << "Jumlah: ";
                    cin >> qty;
                    if (qty > 0 && qty <= 10) {
                        Item* newItem = createItem(menuItems[foodChoice-1].name, 
                                                 menuItems[foodChoice-1].price, 
                                                 "makanan", qty);
                        cart.push(newItem);
                    } else {
                        cout << "Jumlah harus 1-10.\n";
                    }
                } else {
                    cout << "Pilihan tidak valid.\n";
                }
                break;
                
            case 4:
                clearScreen();
                int drinkChoice;
                cout << "\nPilih minuman (6-10): ";
                cin >> drinkChoice;
                if (drinkChoice >= 6 && drinkChoice <= 10) {
                    cout << "Jumlah: ";
                    cin >> qty;
                    if (qty > 0 && qty <= 10) {
                        Item* newItem = createItem(menuItems[drinkChoice-1].name, 
                                                 menuItems[drinkChoice-1].price, 
                                                 "minuman", qty);
                        cart.push(newItem);
                    } else {
                        cout << "Jumlah harus 1-10.\n";
                    }
                } else {
                    cout << "Pilihan tidak valid.\n";
                }
                break;
                
            case 5:
                clearScreen();
                cart.display();
                break;
                
            case 6:
                clearScreen();
                cart.cancelLastItem();
                break;
                
            case 7:
                clearScreen();
                if (cart.isEmpty()) {
                    cout << "\n>> Keranjang kosong!\n";
                } else {
                    cart.display();
                    char confirm;
                    cout << "\nKonfirmasi checkout & pembayaran? (y/n): ";
                    cin >> confirm;
                    
                    if (confirm == 'y' || confirm == 'Y') {
                        int total = cart.getTotalPrice();
                        int food = cart.getFoodCount();
                        int drink = cart.getDrinkCount();
                        char customerName[50];
                        char customerNIK[20];
                        cart.getCustomerName(customerName);
                        cart.getCustomerNIK(customerNIK);
                        
                        char date[20];
                        copyString(date, "Sistem Drive-Thru", 20);
                        
                        transactions.addTransaction(orderCounter, customerName, customerNIK, total, food, drink, date);
                        
                        if (stringLength(customerName) > 0 && stringLength(customerNIK) > 0) {
                            customers.addCustomer(customerName, customerNIK, total);
                        } else {
                            cout << "\n>> Catatan: Data pelanggan tidak lengkap, hanya transaksi yang disimpan.\n";
                        }
                        
                        printReceipt(orderCounter, customerName, customerNIK, total, food, drink);
                        
                        cout << "\n>> Pembayaran berhasil! Pesanan #" << orderCounter << "\n";
                        cout << ">> Total yang dibayar: Rp " << total << "\n";
                        cout << ">> Catatan: Anda dapat mencari pesanan ini di menu admin\n";
                        
                        orderCounter++;
                        cart.clearCart();
                    }
                }
                break;
                
            case 8:
                cout << "\nKembali ke menu utama...\n";
                break;
                
            default:
                cout << "\nPilihan tidak valid!\n";
        }
        
        if (choice != 8) {
            cout << "\nTekan Enter untuk melanjutkan...";
            cin.ignore();
            cin.get();
        }
        
    } while (choice != 8);
}

void DriveThruSystem::run() {
    int mainChoice;
    
    do {
        clearScreen();
        displayMainMenu();
        cin >> mainChoice;
        
        switch (mainChoice) {
            case 1:
                runCustomerMode();
                break;
                
            case 2:
                if (verifyAdmin()) {
                    runAdminMode();
                } else {
                    cout << "\nTekan Enter untuk melanjutkan...";
                    cin.ignore();
                    cin.get();
                }
                break;
                
            case 3:
                clearScreen();
                cout << "\n==================================================\n";
                cout << "   TERIMA KASIH TELAH MENGGUNAKAN\n";
                cout << "   SISTEM DRIVE-THRU FAST FOOD\n";
                cout << "==================================================\n";
                cout << "   Total Transaksi: " << transactions.getTotalTransactions() << "\n";
                cout << "   Total Pelanggan: " << customers.getCustomerCount() << "\n";
                cout << "   Total Pemasukan: Rp " << transactions.getTotalRevenue() << "\n";
                cout << "   Total Keuntungan: Rp " << transactions.getTotalProfit() << "\n";
                cout << "   Total Makanan Terjual: " << transactions.getFoodSold() << "\n";
                cout << "   Total Minuman Terjual: " << transactions.getDrinkSold() << "\n";
                cout << "   Struk disimpan di file 'struk.txt'\n";
                cout << "   Riwayat transaksi: 'transaksi_history.txt'\n";
                cout << "   Data pelanggan: 'pelanggan_data.txt'\n";
                cout << "==================================================\n";
                break;
                
            default:
                cout << "\nPilihan tidak valid!\n";
                cout << "\nTekan Enter untuk melanjutkan...";
                cin.ignore();
                cin.get();
        }
        
    } while (mainChoice != 3);
}

int main() {
    clearScreen();
    cout << "==================================================\n";
    cout << "       SISTEM DRIVE-THRU FAST FOOD\n";
    cout << "       DENGAN FITUR PENCARIAN PESANAN & NIK\n";
    cout << "==================================================\n";
    cout << "Fitur Utama:\n";
    cout << "1. Sistem Pemesanan Drive-Thru dengan NIK (minimal 4 karakter)\n";
    cout << "2. Pencarian Pesanan berdasarkan Nama/NIK\n";
    cout << "3. Statistik dan Laporan\n";
    cout << "4. Struktur Data: Stack, Queue, Tree, Huffman\n";
    cout << "==================================================\n";
    
    DriveThruSystem system;
    system.run();
    
    return 0;
}
