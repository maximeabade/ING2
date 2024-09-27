/*
Vous allez mettre en œuvre une classe Template Stack (pile en français) avec les méthodes suivantes :

size() qui retourne la taille de la pile.
empty() qui indique si la pile est vide.
peek() qui retourne la tête de la pile.
push() qui permet d'empiler un élément.
pop() qui permet de dépiler.
Chaque fonction doit être testée dans le programme principal.


*/


#include <iostream>
#include <stack>

template <typename T>
class Stack {
private:
    std::stack<T> data;

public:
    int size() const {
        return data.size();
    }

    bool empty() const {
        return data.empty();
    }

    T peek() const {
        return data.top();
    }

    void push(const T& element) {
        data.push(element);
    }

    void pop() {
        data.pop();
    }
};

int main() {
    Stack<int> stack;
    
    stack.push(5);
    stack.push(10);
    stack.push(15);
    
    std::cout << "Taille de la stack :  " << stack.size() << std::endl;
    std::cout << "La stack est vide :  " << (stack.empty() ? "Yes" : "No") << std::endl;
    std::cout << "Tête de la stack : : " << stack.peek() << std::endl;
    
    stack.pop();
    
    std::cout << "Taille de la stack après le pop: " << stack.size() << std::endl;
    
    return 0;
}