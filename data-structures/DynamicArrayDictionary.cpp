//TODO:
//UNDERSTAND AND IMPLEMENT = OVERLOADING(MOVE) IN DYNAMIC ARRAY
//COMPLETE rehash() by binding reference to new Array (correct ??)
//...


#include <cstddef>
#include <iostream>
#include <forward_list>
#include <cstdint>
using namespace std;

//Dynamic Array
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

    size_t getSize(){ return size; }

    size_t getCapacity(){ return capacity;}

    size_t incrementSize(){ return size++; }


    // use unique pointer??
    void reserve(size_t cap)
    {
        capacity = cap;
        T *newInnerArray = new T[capacity];
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
        //Shrink Array
        if (size < capacity / 4)
        {
            reserve(capacity / 2);
        }
    }
    // Implementing eraze(index) as in vector would compromise index-data integrity ,
    //  Therefore that is left for future addition if/when required.
    T pop_back(){ return innerArray[size--]; }

    T &at(size_t index)
    {
        if (index >= size)
        {
            throw out_of_range("Index not Initliased");
        }
        return innerArray[index];
    }
    //Array Access functions
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
        float threshold;
        float loadfactor;
    public:

        
        void inserIntoArray_handler(size_t index, string key, string value, DynamicArray<forward_list<keyValue>> &dArray){
            dArray.at(index).push_front({key,value});
        }

        void hashCopyArray_handler(DynamicArray<forward_list<keyValue>> &newdArray, DynamicArray<forward_list<keyValue>> &currdArray){
            for( size_t i = 0; i<currdArray.getCapacity();i++){
                if(!currdArray[i].empty()){
                    for(auto e: currdArray[i]){
                        string key = e.key;
                        string value = e.value;
                        size_t index = hash(key)%newdArray.getCapacity();
                        inserIntoArray_handler(index, key, value, newdArray);
                        //  COPYING REFERENCE REQURIES = OVERLOADED IN DYNAMIC ARRAY
                    }
                    
                }
            }
        }

        float calcLoadfactor(){
            loadfactor = dArray.getSize()/dArray.getCapacity();
            return loadfactor;
        }

        uint32_t hash(const string key){
            uint32_t hash = 0;
            for( const char c: key){
                hash = hash + P * (uint32_t) c;
            }
            return hash;
        }

        void rehash(){
            DynamicArray<forward_list<keyValue>> newdArray;
            newdArray.reserve(dArray.getCapacity()*2);
            hashCopyArray_handler(newdArray,dArray);

        }

        void insert(string key, string value){
            if( (dArray.getSize()+ 1) / dArray.getCapacity() >= threshold){
                rehash();
            }
            size_t index = hash(key) % dArray.getCapacity();
            inserIntoArray_handler(index, key, value,dArray);

        }



        Dictionary():P(31) ,threshold(0.75){
            calcLoadfactor();
        }
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