#include <iostream>
#include <stdlib.h>
using namespace std;

class Node {
public:
    int coe; // 系数
    int power; // 幂
    Node* next; // 指向下一个节点的指针

    // 构造函数
    Node(int coe = 0,int power = 0, Node* next = nullptr) {
        this->coe = coe;
        this->power = power;
        this->next = next;
    }

    // 拷贝构造函数
    Node(const Node& other) {
        this->coe = other.coe;
        this->power = other.power;
        if (other.next == nullptr) {
            this->next = nullptr;
        }
        else {
            this->next = new Node(*(other.next));
        }
    }

    // 析构函数
    ~Node() {
    }
};

// 链表类
class LinkedList {
private:
    Node* head;         // 链表头节点指针
public:
    // 构造函数
    LinkedList() {
        head = NULL;    // 初始化链表头指针为空
    }

    // 添加节点
    void addNode(int coe, int power) {
        Node* newNode = new Node;   // 新建节点
        newNode->coe = coe;         // 设置节点数据
        newNode->power = power;      
        newNode->next = NULL;       // 设置节点的下一个指针为空

        if (head == NULL) {         // 如果链表为空，则将新节点作为链表头
            head = newNode;
        }
        else {                      // 如果链表不为空，则将新节点插入到链表尾部
            Node* temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    // 打印链表
    void printList() {
        Node* temp = head;          // 从链表头开始遍历
        while (temp != NULL) {      // 当遍历到链表末尾时退出循环
            if (temp->next != NULL) {
                cout << " ";
                if (temp->coe != 1) {
                    cout << temp->coe;
                }
                cout <<"X";
                if (temp->power != 1) {
                    cout << "^";
                    cout << temp->power;  // 输出节点数据
                }
                cout << "+";
            }
            else {
                cout << " ";
                if (temp->coe != 1) {
                    cout << temp->coe;
                }
                cout << "X";
                if (temp->power != 1) {
                    cout << "^";
                    cout << temp->power;  // 输出节点数据
                }
            }
            temp = temp->next;      // 指针指向下一个节点
        }
        cout << endl;
    }

    // 根据值删除节点
    void deleteNodeByValue(int value) {
        Node* temp = head;          // 从链表头开始遍历
        Node* prev = NULL;          // 保存当前节点的前一个节点指针
        while (temp != NULL) {
            if (temp->power == value) {  // 如果找到了需要删除的节点
                if (prev == NULL) {     // 如果是链表头节点
                    head = temp->next;
                }
                else {                  // 如果不是链表头节点
                    prev->next = temp->next;
                }
                delete temp;            // 释放节点内存
                return;
            }
            prev = temp;            // 保存当前节点指针
            temp = temp->next;      // 指针指向下一个节点
        }
        cout << "Invalid value" << endl;
    }

    // 根据顺序删除节点
    void deleteNoteByPosition(int pos) {
        Node* temp = head;          // 从链表头开始遍历
        Node* prev = NULL;          // 保存当前节点的前一个节点指针
        for (int i = 0; i < pos && temp != nullptr; i++) {
            prev = temp;
            temp = temp->next;      // 找到删除节点

        }
        if (temp != nullptr) {          // 删除位置有效
            if (prev == NULL) {         // 如果是链表头节点
                head = head->next;
            }
            else {                  // 如果不是链表头节点
                prev->next = temp->next;
            }
            delete temp;
        }
        else {                      // 插入位置无效
            cout << "Invalid position" << endl;
        }

    }

    // 根据指针删除节点
    void deleteNoteByPoint(Node* prev, Node* temp) {
        prev->next = temp->next;
        delete temp;
    }

    // 在指定位置插入节点
    void insertNode(int pos, int val) {
        Node* newNode = new Node(val); // 创建新节点
        if (pos == 0) { // 插入位置为链表头部
            newNode->next = head;
            head = newNode;
        }
        else { // 插入位置不为头部
            Node* current = head;
            for (int i = 0; i < pos - 1 && current != nullptr; i++) {
                current = current->next; // 找到插入位置前一个节点
            }
            if (current != nullptr) { // 插入位置有效
                newNode->next = current->next;
                current->next = newNode;
            }
            else { // 插入位置无效
                cout << "Invalid position" << endl;
                delete newNode;
            }
        }
    }

    // 查找节点
    int searchNode(int val) {
        Node* current = head;
        int pos = 0;
        while (current != nullptr) {
            if (current->power == val) { // 找到目标节点
                return pos;
            }
            current = current->next;
            pos++;
        }
        return -1; // 没有找到目标节点
    }

    // 获取链表的尾节点
    Node* getTail(Node* head) {
        while (head->next != nullptr) {
            head = head->next;
        }
        return head;
    }

    void swapValue(Node* x, Node* y) {
        int currentX1 = x->power;
        int currentX2 = x->coe;
        x->power = y->power;
        x->coe = y->coe;
        y->power = currentX1;
        y->coe = currentX2;

    }

    void bubbleSort() {
        if (head == nullptr || head->next == nullptr) { // 链表为空或只有一个节点，直接返回
            return;
        }
        Node* prev = head;          // 以前节点为基准
        Node* temp = prev->next;    // 后一个节点用来判断
        int flag = 1;      // 排序完成的标志,存在交换时表示排序未完成
        while (flag) {
            flag = 0;
            prev = head;
            temp = prev->next;
            while (temp != nullptr) {
                if (prev->power > temp->power) {  //升序排序
                    swapValue(prev, temp);  //交换节点的值
                    flag = 1;  // 存在交换
                }
                prev = temp;            // 前节点后移
                temp = temp->next;      // 后节点后移
            }
        }
    }

    void mergeSimilar() {
        bubbleSort();
        if (head == nullptr || head->next == nullptr) { // 链表为空或只有一个节点，直接返回
            return;
        }
        Node* prev = head;          // 基准节点
        Node* temp = prev->next;    // 后一个节点用来判断
        Node* prevtemp = prev;      // 储存前一个节点
        Node* deltemp;
        while (prev != NULL) {        // 前指针从头移到尾
            prevtemp = prev;
            temp = prev->next;
            while (temp != NULL) {    // 前指不动，后指针移到表尾
                if (prev->power == temp->power) {       // 幂相同
                    prev->coe = prev->coe + temp->coe;  // 系数合并
                    deltemp = temp;
                    temp = temp->next;                  // 后指针后移
                    deleteNoteByPoint(prevtemp, deltemp);  // 删除已合并节点
                }
                else {                                  // 幂不同
                    prevtemp = prev->next;
                    temp = temp->next;                  // 后指针后移
                }
            }
            prev = prev->next;
        }
    }

};

// 主函数
int main() {
    int t;
    int r1;
    int r2;
    int d = 0;
    int pos = 0;

    LinkedList list;            // 创建链表对象
    while (d == 0 || d == 1 || d == 2 || d == 3) {
        if (d == 0) {
            cout << "输入多项式项数：";
            cin >> t;

            for (int i = 0; i < t; i++) {
                r1 = 0;
                r2 = 0;
                cout << "请顺序输入系数和幂：";
                cin >> r1 >> r2;
                list.addNode(r1, r2);
            }

            cout << "多项式为：";
            list.printList();
        }
        if (d == 1) {
            cout << "输入删除的位置：";
            cin >> pos;

            list.deleteNoteByPosition(pos);

            cout << "删除后的多项式：";
            list.printList();
        }
        if (d == 2) {
            list.bubbleSort();
            cout << "排序后的的多项式：";
            list.printList();
        }
        if (d == 3) {
            list.mergeSimilar();
            cout << "化简后的多项式为：";
            list.printList();
        }

        cout << "请选择对多项式的操作，“0”（继续添加元素）、“1”（删除指定位置的项,下标从0开始）、“2”（对多项式排序）、“3”（合并同类项）、其他（结束程序）：";
        cin >> d;
    }

    cout << "储存的多项式为：";
    list.printList();
    cout << "程序已退出！";

    return 0;
}