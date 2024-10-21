#include <iostream>
#include <algorithm>
#include <cmath>
#include <utility>

struct Node {
    int coefficient;
    int exponent;
    Node* next;
};

double evaluate(Node* head, double x) {
    double result = 0.0;
    Node* current = head;
    while (current != nullptr) {
        result += current->coefficient * pow(x, current->exponent);
        current = current->next;
    }
    return result;
}

void sortAscendingByCoefficient(Node*& head) {
    if (!head || !head->next) return;
    Node* i = head;
    while (i) {
        Node* j = i->next;
        while (j) {
            if (i->coefficient > j->coefficient) {
                std::swap(i->coefficient, j->coefficient);
                std::swap(i->exponent, j->exponent);
            }
            j = j->next;
        }
        i = i->next;
    }
}

void sortDescendingByExponent(Node*& head) {
    if (!head || !head->next) return;
    Node* i = head;
    while (i) {
        Node* j = i->next;
        while (j) {
            if (i->exponent < j->exponent) {
                std::swap(i->coefficient, j->coefficient);
                std::swap(i->exponent, j->exponent);
            }
            j = j->next;
        }
        i = i->next;
    }
}

Node* findMinTerm(Node* head) {
    if (!head) return nullptr;
    Node* minTerm = head;
    Node* current = head->next;
    while (current) {
        if (current->coefficient < minTerm->coefficient) {
            minTerm = current;
        }
        current = current->next;
    }
    return minTerm;
}

Node* findFirstEvenExponentTerm(Node* head) {
    Node* current = head;
    while (current) {
        if (current->exponent % 2 == 0) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void listPositiveCoefficients(Node* head) {
    Node* current = head;
    while (current) {
        if (current->coefficient > 0) {
            std::cout << "Coefficient: " << current->coefficient << ", Exponent: " << current->exponent << std::endl;
        }
        current = current->next;
    }
}

int countEvenExponentTerms(Node* head) {
    int count = 0;
    Node* current = head;
    while (current) {
        if (current->exponent % 2 == 0) {
            count++;
        }
        current = current->next;
    }
    return count;
}

void insertTermSorted(Node*& head, int coefficient, int exponent) {
    Node* newNode = new Node{coefficient, exponent, nullptr};
    if (!head || head->coefficient > coefficient) {
        newNode->next = head;
        head = newNode;
        return;
    }
    Node* current = head;
    while (current->next && current->next->coefficient <= coefficient) {
        current = current->next;
    }
    if (current->exponent == exponent) {
        current->coefficient += coefficient;
        delete newNode;
    } else {
        newNode->next = current->next;
        current->next = newNode;
    }
}

void deleteFirstNegativeCoefficient(Node*& head) {
    if (!head) return;
    if (head->coefficient < 0) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return;
    }
    Node* current = head;
    while (current->next && current->next->coefficient >= 0) {
        current = current->next;
    }
    if (current->next) {
        Node* temp = current->next;
        current->next = current->next->next;
        delete temp;
    }
}

struct LargeNumber {
    Node* head;
    bool isNegative;
    LargeNumber() : head(nullptr), isNegative(false) {}
};

void addDigitFront(LargeNumber& num, int digit) {
    Node* newNode = new Node{digit, 0, num.head};
    num.head = newNode;
}

LargeNumber add(LargeNumber num1, LargeNumber num2) {
    LargeNumber result;
    int carry = 0;
    Node* p1 = num1.head;
    Node* p2 = num2.head;
    while (p1 || p2 || carry) {
        int sum = carry;
        if (p1) {
            sum += p1->coefficient;
            p1 = p1->next;
        }
        if (p2) {
            sum += p2->coefficient;
            p2 = p2->next;
        }
        addDigitFront(result, sum % 10);
        carry = sum / 10;
    }
    return result;
}

LargeNumber subtract(LargeNumber num1, LargeNumber num2) {
    LargeNumber result;
    int borrow = 0;
    Node* p1 = num1.head;
    Node* p2 = num2.head;
    while (p1) {
        int diff = p1->coefficient - (p2 ? p2->coefficient : 0) - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        addDigitFront(result, diff);
        p1 = p1->next;
        if (p2) p2 = p2->next;
    }
    return result;
}

LargeNumber multiply(LargeNumber num1, LargeNumber num2) {
    LargeNumber result;
    result.isNegative = num1.isNegative != num2.isNegative;
    int shift = 0;
    for (Node* p2 = num2.head; p2; p2 = p2->next) {
        LargeNumber temp;
        int carry = 0;
        for (int i = 0; i < shift; ++i) addDigitFront(temp, 0);
        for (Node* p1 = num1.head; p1; p1 = p1->next) {
            int product = p1->coefficient * p2->coefficient + carry;
            addDigitFront(temp, product % 10);
            carry = product / 10;
        }
        if (carry) addDigitFront(temp, carry);
        result = add(result, temp);
        shift++;
    }
    return result;
}

int compare(LargeNumber num1, LargeNumber num2) {
    Node* p1 = num1.head;
    Node* p2 = num2.head;
    while (p1 && p2) {
        if (p1->coefficient != p2->coefficient) return p1->coefficient - p2->coefficient;
        p1 = p1->next;
        p2 = p2->next;
    }
    if (p1) return 1;
    if (p2) return -1;
    return 0;
}

LargeNumber divide(LargeNumber num1, LargeNumber num2) {
    LargeNumber result;
    if (compare(num1, num2) < 0) return result;
    LargeNumber divisor = num2;
    LargeNumber current;
    Node* head1 = num1.head;
    while (head1) {
        addDigitFront(current, head1->coefficient);
        int count = 0;
        while (compare(current, divisor) >= 0) {
            current = subtract(current, divisor);
            count++;
        }
        addDigitFront(result, count);
        head1 = head1->next;
    }
    return result;
}

int main() {
    Node* polynomial = nullptr;
    insertTermSorted(polynomial, 3, 2);
    insertTermSorted(polynomial, 5, 1);
    insertTermSorted(polynomial, -2, 0);

    std::cout << "Polynomial evaluated at x=2: " << evaluate(polynomial, 2.0) << std::endl;

    std::cout << "Positive coefficients: " << std::endl;
    listPositiveCoefficients(polynomial);

    std::cout << "First term with even exponent: ";
    Node* evenTerm = findFirstEvenExponentTerm(polynomial);
    if (evenTerm) {
        std::cout << "Coefficient: " << evenTerm->coefficient << ", Exponent: " << evenTerm->exponent << std::endl;
    } else {
        std::cout << "None found" << std::endl;
    }

    return 0;
}
