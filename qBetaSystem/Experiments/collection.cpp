#include <iostream>
#include <vector>
#include <memory>  // for smart pointers

// Generic collection
template <typename T>
class Collection {
private:
    std::vector<T> items;  // store values or pointers

public:
    // Insert a value
    void insert(T value) {
        items.push_back(value);
    }

    // Insert a pointer
    void insert(T* ptr) {
        items.push_back(ptr);
    }

    // Access item by index
    T& get(size_t index) {
        return items.at(index);
    }

    size_t size() const {
        return items.size();
    }

    // Print all items (for demonstration)
    void print() const {
        for (const auto& item : items) {
            if constexpr (std::is_pointer<T>::value) {
                std::cout << *item << " ";
            } else {
                std::cout << item << " ";
            }
        }
        std::cout << "\n";
    }
};

// Example usage
int main() {
    // Collection of integers (by value)
    Collection<int> values;
    int a = 10, b = 20;
    values.insert(a);
    values.insert(b);
    values.print();  // Output: 10 20
    a = 111; // no effect on value a=10 in values
    values.print();
    // Collection of integer pointers
    Collection<int*> pointers;
    a = 5;
    b = 15;
    pointers.insert(&a);
    pointers.insert(&b);
    pointers.print(); // Output: 5 15
    a = 222;  // effect on pointer to a in pointers
    pointers.print();

    return 0;
}