// Итератор
// - итератор по массиву
// - итератор по map<string, ...>
// возвращающий ключ-значение с определённой
// подстрокой в ключе
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

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
    void Next();
    T Current();
    bool IsDone();
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
    bool isDone() { return validKeys.size() > current; }
    void Next() { current++; }
    T Current() { return mapPtr->at(validKeys[current]); }
};

template <typename T> class BetterMap : public map<string, T> {
  public:
    MapIterator<T> CreateIterator(string substring) {
        return MapIterator<T>(this, substring);
    };
};

int main() {
    BetterMap<int> foo;
    foo["lina"] = 1;
    foo["raslina"] = 2;
    foo["linaras"] = 3;
    foo["amogus"] = 17;
    int i = 0;
    for (auto it = foo.CreateIterator("lina"); it.isDone(); it.Next()) {
        cout << it.Current() << endl;
    }
    return 0;
}