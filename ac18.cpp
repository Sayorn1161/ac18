#include <iostream>
#include <string>

class Queue {
private:
    struct Node {
        char data;
        Node* next;
    };
    Node* front;
    Node* rear;

public:
    Queue() : front(nullptr), rear(nullptr) {}

    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    bool isEmpty() const {
        return front == nullptr;
    }

    void enqueue(char item) {
        Node* newNode = new Node{item, nullptr};
        if (isEmpty()) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    char dequeue() {
        if (isEmpty()) {
            throw std::runtime_error("Queue is empty");
        }
        Node* temp = front;
        char item = front->data;
        front = front->next;
        delete temp;
        return item;
    }
};

class Stack {
private:
    struct Node {
        char data;
        Node* next;
    };
    Node* top;

public:
    Stack() : top(nullptr) {}

    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    bool isEmpty() const {
        return top == nullptr;
    }

    void push(char item) {
        Node* newNode = new Node{item, top};
        top = newNode;
    }

    char pop() {
        if (isEmpty()) {
            throw std::runtime_error("Stack is empty");
        }
        Node* temp = top;
        char item = top->data;
        top = top->next;
        delete temp;
        return item;
    }

    char peek() const {
        if (isEmpty()) {
            throw std::runtime_error("Stack is empty");
        }
        return top->data;
    }
};

bool areParenthesesBalanced(const std::string& expression) {
    Stack stack;
    for (size_t i = 0; i < expression.length(); i++) {
        char current = expression[i];

        if (current == '(' || current == '{' || current == '[') {
            stack.push(current);
        } else if (current == ')' || current == '}' || current == ']') {
            if (stack.isEmpty()) {
                std::cout << "Error at: " << expression.substr(0, i + 1) << std::endl;
                return false;
            }
            char top = stack.pop();
            if ((current == ')' && top != '(') ||
                (current == '}' && top != '{') ||
                (current == ']' && top != '[')) {
                std::cout << "Error at: " << expression.substr(0, i + 1) << std::endl;
                return false;
            }
        }
    }

    if (!stack.isEmpty()) {
        std::cout << "Error: Unmatched opening brackets." << std::endl;
        return false;
    }
    return true;
}

int main() {
    std::string input;
    std::cout << "Enter the expression ending with ';': ";
    std::getline(std::cin, input);

    // Remove the trailing semicolon
    if (!input.empty() && input.back() == ';') {
        input.pop_back();
    }

    if (areParenthesesBalanced(input)) {
        std::cout << "The expression is correctly balanced." << std::endl;
    } else {
        std::cout << "The expression is incorrectly balanced." << std::endl;
    }

    return 0;
}
