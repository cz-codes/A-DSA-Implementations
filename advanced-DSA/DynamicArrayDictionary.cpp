#include <cstddef>
#include <iostream>
#include <forward_list>
using namespace std;

template <typename T>
class DynamicArray
{
private:
    T *innerArray;
    size_t size;
    size_t capacity;

public:
    DynamicArray(size_t cap = 2) : size(0), capacity(cap)
    {
        innerArray = new T[capacity];
    }

    ~DynamicArray() { delete[] innerArray; }

    size_t getSize()
    {
        return size;
    }

     size_t getCapacity()
    {
        return capacity;
    }


    /// use unique pointer??
    //formerly capacityChange_handler
    void reserve(size_t cap)
    {
        capacity = cap;
        int *newInnerArray = new T[capacity];
        for (int i = 0; i < size; i++)
        {
            newInnerArray[i] = innerArray[i];
        }
        delete[] innerArray;
        innerArray = newInnerArray;
    }

    void push_back(T x)
    {
        if (size < capacity)
        {
            innerArray[size++] = x;
        }
        else if (size == capacity)
        {
            reserve(2 * capacity);
            innerArray[size++] = x;
        }

        if (size < capacity / 4)
        {
            reserve(capacity / 2);
        }
    }
    // Implementing eraze(index) as in vector would compromise index-data integrity ,
    //  Therefore that is left for future addition if/when required.
    T pop_back()
    {
        return innerArray[size--];
    }

        T &at(size_t index)
    {
        if (index >= size)
        {
            throw out_of_range("Index not Initliased");
        }
        return innerArray[index];
    }

    const T &at(size_t index) const
    {
        if (index >= size)
        {
            throw out_of_range("Uninitialised index reference");
        }
        return innerArray[index];
    }

    T &operator[](size_t index)
    {
        return innerArray[index];
    }

    const T &operator[](size_t index) const
    {
        return innerArray[index];
    }
};

struct keyValue{
    string key;
    string value;
};

class Dictionary{
    private:
        const int P;
        DynamicArray<forward_list<keyValue>> dArray;
    public:


        uint32_t hash(const string key){
            uint32_t hash = 0;
            for( const c: key){
                hash = hash + P * (uint32_t) c;
            }
            return hash;
        }

        void insert(string key, string value){
            size_t index = hash(key) % dArray.getCapacity();
            

        }



        Dictionary():P(31){}
};

int main()
{
    DynamicArray<int> a;
    a.push_back(1);
    cout << "size: " << a.getSize() << endl;
    a.push_back(2);
    cout << "size: " << a.getSize() << endl;
    a.push_back(3);
    a[0] = 7;
    a.at(0) = 9;
    cout << "at 0: " << a.at(0) << endl;

    for (size_t i = 0; i < a.getSize(); i++)
    {
        cout << a.at(i) << endl;
    }
    return 0;
}