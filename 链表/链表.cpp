#include <iostream>
#include <stdlib.h>
using namespace std;

class Node {
public:
    int data; // 节点中存储的数据
    Node* next; // 指向下一个节点的指针

    // 构造函数
    Node(int val = 0, Node* next = nullptr) {
        this->data = val;
        this->next = next;
    }

    // 拷贝构造函数
    Node(const Node& other) {
        this->data = other.data;
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
    void addNode(int value) {
        Node* newNode = new Node;   // 新建节点
        newNode->data = value;      // 设置节点数据
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
            cout << temp->data << " ";  // 输出节点数据
            temp = temp->next;      // 指针指向下一个节点
        }
        cout << endl;
    }

    // 根据值删除节点
    void deleteNodeByValue(int value) {
        Node* temp = head;          // 从链表头开始遍历
        Node* prev = NULL;          // 保存当前节点的前一个节点指针
        while (temp != NULL) {
            if (temp->data == value) {  // 如果找到了需要删除的节点
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


    void reverseList() {
        Node* prev = nullptr;
        Node* current = head;
        Node* next = nullptr;

        while (current != nullptr) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        head = prev;
    }
    // 反转链表
    //void reverseList() {
    //    Node* prev = nullptr;
    //    Node* current = head;
    //    Node* next = nullptr;
    //    while (current != nullptr) {
    //        next = current->next;
    //        current->next = prev;
    //        prev = current;
    //        current = next;
    //    }
    //    head = prev; // 更新链表头部
    //}

    // 查找节点
    int searchNode(int val) {
        Node* current = head;
        int pos = 0;
        while (current != nullptr) {
            if (current->data == val) { // 找到目标节点
                return pos;
            }
            current = current->next;
            pos++;
        }
        return -1; // 没有找到目标节点
    }

    // 删除重复节点
    void deleteDuplicates() {
        Node* current = head;
        while (current != nullptr) {
            Node* runner = current;
            while (runner->next != nullptr) {
                if (runner->next->data == current->data) { // 找到重复节点
                    Node* duplicate = runner->next;
                    runner->next = runner->next->next;
                    delete duplicate;
                }
                else {
                    runner = runner->next;
                }
            }
            current = current->next;
        }
    }

    // 合并链表
    LinkedList mergeList(LinkedList& list) {
        LinkedList mergedList;
        Node* current1 = head;
        Node* current2 = list.head;
        while (current1 != nullptr && current2 != nullptr) {
            if (current1->data < current2->data) { // 当前节点1的值小于节点2
                mergedList.addNode(current1->data);
                current1 = current1->next;
            }
            else { // 当前节点2的值小于等于节点1
                mergedList.addNode(current2->data);
                current2 = current2->next;
            }
        }
        // 将剩余节点添加到合并链表末尾
        while (current1 != nullptr) {
            mergedList.addNode(current1->data);
            current1 = current1->next;
        }
        while (current2 != nullptr) {
            mergedList.addNode(current2->data);
            current2 = current2->next;
        }
        return mergedList;
    }

    // 将链表分离为两个链表，其中一个包含原链表的前一半节点，另一个包含后一半节点
    void splitList(Node* head, Node** head1, Node** head2) {
        if (head == nullptr || head->next == nullptr) { // 如果链表为空或只有一个节点
            *head1 = head; // 直接将head1指向该节点
            *head2 = nullptr; // head2指向nullptr
            return;
        }
        Node* slow = head; // 慢指针每次移动一步
        Node* fast = head->next; // 快指针每次移动两步
        while (fast != nullptr) { // 快指针移动到链表末尾时停止
            fast = fast->next; // 快指针先移动一步
            if (fast != nullptr) { // 如果快指针还没到末尾
                slow = slow->next; // 慢指针再移动一步
                fast = fast->next; // 快指针再移动一步
            }
        }
        *head1 = head; // head1指向原链表的头节点
        *head2 = slow->next; // head2指向后一半链表的头节点
        slow->next = nullptr; // 将原链表的前一半节点的最后一个节点的next设为nullptr，即分离出后一半链表
    }
    // 交换链表中的两个节点
    void swapNodes(int posX, int posY) {
        Node* prevX = nullptr;
        Node* currentX = head;
        while (currentX != nullptr && currentX->data != posX) {
            prevX = currentX;
            currentX = currentX->next;
        }
        Node* prevY = nullptr;
        Node* currentY = head;
        while (currentY != nullptr && currentY->data != posY) {
            prevY = currentY;
            currentY = currentY->next;
        }
        /*
        if (x == y) { // 节点相同
            return;
        }
        Node* prevX = nullptr;
        Node* currentX = head;
        while (currentX != nullptr && currentX->data != x) {
            prevX = currentX;
            currentX = currentX->next;
        }
        Node* prevY = nullptr;
        Node* currentY = head;
        while (currentY != nullptr && currentY->data != y) {
            prevY = currentY;
            currentY = currentY->next;
        }
        if (currentX == nullptr || currentY == nullptr) { // 节点不存在
            return;
        }
        if (prevX != nullptr) {
            prevX->next = currentY;
        }
        else {
            head = currentY;
        }
        if (prevY != nullptr) {
            prevY->next = currentX;
        }
        else {
            head = currentX;
        }
        Node* temp = currentX->next;
        currentX->next = currentY->next;
        currentY->next = temp;
        */
    }
    // 交换链表中的两个节点的值
    void swapValue(Node* x, Node* y) {
        int currentX = x->data;
        x->data = y->data;
        y->data = currentX;
        
    }


    // 合并两个有序链表
    Node* mergeLists(Node* l1, Node* l2) {
        if (l1 == nullptr) { // l1为空，返回l2
            return l2;
        }
        if (l2 == nullptr) { // l2为空，返回l1
            return l1;
        }
        Node* newHead = nullptr;
        if (l1->data <= l2->data) { // l1头节点小于等于l2头节点
            newHead = l1;
            newHead->next = mergeLists(l1->next, l2);
        }
        else { // l1头节点大于l2头节点
            newHead = l2;
            newHead->next = mergeLists(l1, l2->next);
        }
        return newHead;
    }

    // 链表的冒泡排序(递归)
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
                if (prev->data > temp->data) {  //升序排序
                    swapValue(prev, temp);  //交换节点的值
                    flag = 1;  // 存在交换
                }
                prev = temp;            // 前节点后移
                temp = temp->next;      // 后节点后移
            }
        }
    }

    /*
    // 链表的快速排序
    void quickSort() {
        if (head == nullptr || head->next == nullptr) { // 链表为空或只有一个节点，直接返回
            return;
        }
        Node* pivot = head; // 以头节点为基准
        Node* p = pivot->next; // 指向下一个节点
        Node* small = nullptr; // 指向小于基准的节点
        Node* big = nullptr; // 指向大于等于基准的节点
        while (p != nullptr) {
            if (p->data < pivot->data) { // 当前节点小于基准
                if (small == nullptr) {
                    small = p;
                    head = small;
                }
                else {
                    small->next = p;
                    small = small->next;
                }
            }
            else { // 当前节点大于等于基准
                if (big == nullptr) {
                    big = p;
                    pivot->next = big;
                }
                else {
                    big->next = p;
                    big = big->next;
                }
            }
            p = p->next;
        }
        if (small != nullptr) { // 存在小于基准的节点
            small->next = nullptr;
            head = quickSort();
            Node* tail = getTail(head);
            tail->next = pivot;
        }
        else { // 不存在小于基准的节点
            head = pivot;
        }
        if (big != nullptr) { // 存在大于等于基准的节点
            big->next = nullptr;
            pivot->next = quickSort(pivot->next);
        }
        else { // 不存在大于等于基准的节点
            pivot->next = nullptr;
        }
        return;
    }*/

    // 获取链表的尾节点
    Node* getTail(Node* head) {
        while (head->next != nullptr) {
            head = head->next;
        }
        return head;
    }

};

// 主函数
int main() {
    int t;
    int r;
    int d = 0;
    int pos = 0;

    LinkedList list;            // 创建链表对象
    while (d == 0 || d == 1 || d == 2) {
        if (d == 0) {
            cout << "输入节点个数：";
            cin >> t;

            for (int i = 0; i < t; i++) {
                r = 0;
                cout << "请输入数据：";
                cin >> r;
                list.addNode(r);
            }

            cout << "链表为：";
            list.printList();
        }
        if (d == 1) {
            cout << "输入删除的位置：";
            cin >> pos;

            list.deleteNoteByPosition(pos);

            cout << "删除后的链表：";
            list.printList();
        }
        if (d == 2) {
            list.bubbleSort();
            cout << "排序后的链表：";
            list.printList();
        }

        cout << "请选择对链表的操作，“0”（继续添加元素）、“1”（删除指定位置的元素,下标从0开始）、“2”（对链表排序）、其他（结束程序）：";
        cin >> d;
    }

    cout << "储存的链表为：";
    list.printList();
    cout << "程序已退出！";
    list.reverseList();
    list.printList();
    return 0;
}
