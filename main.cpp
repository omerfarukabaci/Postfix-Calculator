#include <iostream>
#include <string>
#include <math.h>
#include <string.h>

using namespace std;

struct Node {
	char data;
	int d;
	Node *next;
};

struct thestack {
	Node *head;
	void create();
	void close();
	void push(char);
	void pushint(int);
	char pop();
	int popint();
	bool isempty();
};

void thestack::create() {
	head = NULL;
}
void thestack::close() {
	Node *p;
	while (head) {
		p = head;
		head = head->next;
		delete p;
	}
}

void thestack::push(char newdata) {
	Node *newnode = new Node;
	newnode->data = newdata;
	newnode->next = head;
	head = newnode;
}
void thestack::pushint(int newdata) {
	Node *newnode = new Node;
	newnode->d = newdata;
	newnode->next = head;
	head = newnode;
}
bool thestack::isempty() {
	return head == NULL;
}

char thestack::pop() {
	Node *topnode;
	char temp;
	topnode = head;
	head = head->next;
	temp = topnode->data;
	delete topnode;
	return temp;
}

int thestack::popint() {
	Node *topnode;
	char temp;
	topnode = head;
	head = head->next;
	temp = topnode->d;
	delete topnode;
	return temp;
}

int precedence(char c)
{
	if (c == '^')
		return 3;
	else if (c == '*' || c == '/')
		return 2;
	else if (c == '+' || c == '-')
		return 1;
	else
		return -1;
}

int calculate(int a, int b , char op) {
	switch (op) {
		case '+':
			return a+b;
		case '-':
			return a - b;
		case '*':
			return a* b;
		case '/':
			if( b == 0) return 1;
			return a / b;
		case '^':
			return pow(a,b);
		default:
			return 1;
	}
}

int main() {
	thestack s;
	s.create();
	char c[99];
	char output[99] = "0";
	cin >> c;
	int i = 0, k=0 ,x1, x2;
	cout << "Postfix expression: ";
	while (i < strlen(c)) {
		if (c[i] >= '0' && c[i] <= '9') {
			output[k] = c[i];
			cout << c[i] << " ";
			k++;
		}
		else {
			if (c[i] == '(') s.push(c[i]);
			else if (c[i] == ')') {
				while (!s.isempty() && s.head->data != '(') {
					output[k] = s.pop();
					cout << output[k] << " ";
					k++;
				}
				if (s.head->data == '(') s.pop();
			} //end of elseif
			else {
				while (!s.isempty() && precedence(c[i]) <= precedence(s.head->data)){
						output[k] = s.pop();
						cout << output[k] << " ";
						k++;
				}
				s.push(c[i]);
			}
		}
		i++;
	}
	while (!s.isempty()){
		output[k] = s.pop();
		cout << output[k] << " ";
		k++;
	}
	s.close();
	s.create();
	i = 0;
	while (i < strlen(output)) {
		if (output[i] >= '0' && output[i] <= '9') s.pushint(output[i] - '0');
		else {
			x2 = s.popint();
			x1 = s.popint();
			s.pushint(calculate(x1, x2, output[i]));
		}
		i++;
	}
	cout << "\t Value: ";
	cout << s.popint() << endl;
	return 0;
}

