#include <array>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <vector>

using std::array;
using std::cout;
using std::endl;
using std::map;
using std::string;
using std::vector;

template <typename T>
vector<string> getStringMapKeys(map<string, T> &referenceMap) {
    vector<string> keys;
    for (auto &mapPair : referenceMap) {
        keys.push_back(mapPair.first);
    }
    return keys;
}

template <typename T> class IIterator {
  public:
    virtual void Next() = 0;
    virtual T Current() = 0;
    virtual bool IsDone() = 0;
};

template <typename T, std::size_t N> class ArrayIterator : public IIterator<T> {
  private:
    array<T, N> *arr;
    int current = 0;

  public:
    ArrayIterator<T, N>(array<T, N> *referenceArr) : arr(referenceArr) {}
    void Next() override { current++; }
    T Current() override { return arr->at(current); }
    bool IsDone() override { return arr->size() > current; }
};

template <typename T> class MapIterator : public IIterator<T> {
  private:
    vector<string> validKeys;
    map<string, T> *mapPtr;
    int current = 0;

  public:
    MapIterator<T>(map<string, T> *referenceMap, string substring)
        : mapPtr(referenceMap) {
        auto keys = getStringMapKeys(*referenceMap);
        for (auto &key : keys) {
            // Check if substring is a part of key
            if (key.find(substring) != string::npos) {
                validKeys.push_back(key);
            }
        }
    }
    bool IsDone() override { return validKeys.size() > current; }
    void Next() override { current++; }
    T Current() override { return mapPtr->at(validKeys[current]); }
};

template <typename T, std::size_t N> class BetterArray : public array<T, N> {
  public:
    ArrayIterator<T, N> CreateIterator() { return ArrayIterator<T, N>(this); };
};

template <typename T> class BetterMap : public map<string, T> {
  public:
    MapIterator<T> CreateIterator(string substring) {
        return MapIterator<T>(this, substring);
    };
};

int main() {
    BetterMap<int> foo;
    BetterArray<int, 4> bar{1001, 230, 31, 31};
    foo["lina"] = 1;
    foo["raslina"] = 2;
    foo["linaras"] = 3;
    foo["amogus"] = 17;
    int i = 0;
    for (auto it = foo.CreateIterator("lina"); it.IsDone(); it.Next()) {
        cout << it.Current() << endl;
    }
    for (auto it = bar.CreateIterator(); it.IsDone(); it.Next()) {
        cout << it.Current() << endl;
    }
    return 0;
}