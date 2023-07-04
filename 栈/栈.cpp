#include <iostream>
using namespace std;

class Node {
public:
    int val;
    Node* next;

    Node(int v) {
        val = v;
        next = NULL;
    }
};

class Stack {
private:
    Node* head;
    int size;
    int max_size; // 栈的最大大小

public:
    // 构造函数
    Stack(int max_size = 100) {
        head = NULL;
        size = 0;
        this->max_size = max_size;
    }

    // 析构函数
    ~Stack() {
        Node* p = head;
        while (p != NULL) {
            Node* temp = p;
            p = p->next;
            delete temp;
        }
    }

    // 入栈
    void push(int val) {
        if (size > max_size) { // 栈溢出
            expand(100);
        }
        Node* p = new Node(val);
        p->next = head;
        head = p;
        size++;
    }

    // 出栈
    int pop() {
        if (head == NULL) { // 栈为空
            cout << "Stack is empty!" << endl;
            return 0;
        }
        Node* p = head;
        head = head->next;
        int val = p->val;
        delete p;
        size--;
        return val;
    }

    // 获取栈顶元素
    int peek() {
        if (head == NULL) { // 栈为空
            cout << "Stack is empty!" << endl;
            return 0;
        }
        return head->val;
    }

    // 获取栈的大小
    int getSize() {
        return size;
    }

    // 获取栈的最大大小
    int getMaxSize() {
        return max_size;
    }

    // 拓展栈
    void expand(int expand_size) {
        this->max_size += expand_size;
        return;
    }
};

int main() {
    Stack s(10);
    int d = 1;
    int n = 0;
    cout << "输入要入栈的元素的个数：";
    cin >> n;
    for (int i = 0; i < n; i++) {
        int k = 0;
        cout << "第" << i + 1 << "元素：";
        cin >> k;
        s.push(k);
    }
    while (d == 1 || d == 2 || d == 3 || d == 4)
    {
        cout << "*选择操作，0或其他(结束程序)，1(继续压入元素)，2(弹出元素)，3(获取栈的大小)，4(打印栈)：";
        cin >> d;
        if (d == 1) {
            cout << "**输入要入栈的元素的个数：";
            cin >> n;
            for (int i = 0; i < n; i++) {
                int k = 0;
                cout << "第" << i + 1 << "元素：";
                cin >> k;
                s.push(k);
            }
        }
        else if(d == 2)
        {
            cout << "**输入要弹出的元素的个数：";
            cin >> n;
            for (int i = 0; i < n; i++) {
                cout << "第" << i + 1 << "元素：" << s.pop() << endl;
            }
        }
        else if (d == 3) {
            cout << "栈的大小为：" << s.getSize() << endl;
        }
        else if (d == 4) {
            cout << "当前栈为：" << endl;
            Stack temp_s = s;
            for (int o = 0; o < s.getSize(); o++) {
                cout << temp_s.pop() << endl;    
            }
        }
        else {
            cout << "当前栈为：" << endl;
            int len = s.getSize();
            for (int o = 0; o < len; o++) {
                cout << s.pop() << endl;
            }
            cout << "程序结束！";
        }
    }


   
    return 0;
}
