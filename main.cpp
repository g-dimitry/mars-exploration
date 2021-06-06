#include <iostream>
#include <functional>
using namespace std;

template <typename Type>
class Array
{
private:
  Type *data;
  int count;
  int partition(int start, int end, function<int(Type, Type)> f)
  {
    int i = (start - 1);

    for (int j = start; j <= end - 1; j++)
    {
      if (f(this->data[j], this->data[end]) < 0)
      {
        i++;
        this->swap(i, j);
      }
    }
    this->swap(i + 1, end);
    return (i + 1);
  }
  void quickSort(int start, int end, function<int(Type, Type)> f)
  {
    if (start < end)
    {
      int pivotIndex = this->partition(start, end, f);

      this->quickSort(start, pivotIndex - 1, f);
      this->quickSort(pivotIndex + 1, end, f);
    }
  }

public:
  ~Array()
  {
    delete[] this->data;
  }
  Array<Type>()
  {
    this->data = new Type[0];
    this->count = 0;
  }
  Array<Type>(const Array<Type> &obj)
  {
    this->count = obj.count;
    this->data = new Type[count];
    for (int i = 0; i < count; i++)
    {
      this->data[i] = obj.data[i];
    }
  }
  Array<Type>(Type *data, int count)
  {
    this->data = new Type[count];
    for (int i = 0; i < count; i++)
    {
      this->data[i] = data[i];
    }
    this->count = count;
  }
  Type *getData()
  {
    return this->data;
  }
  int getCount()
  {
    return this->count;
  }
  void copy(Type *dest)
  {
    for (int i = 0; i < count; i++)
    {
      dest[i] = this->data[i];
    }
  }
  Array<Type> clone()
  {
    Type *outArr = new Type[count];
    this->copy(outArr);
    return Array<Type>(outArr, count);
  }
  Array<Type> *push(Type element)
  {
    int newCount = count + 1;
    Type *outArr = new Type[newCount];
    if (!this->count || this->count != 0)
    {
      this->copy(outArr);
      delete[] this->data;
    }
    outArr[count] = element;
    this->data = outArr;
    this->count++;
    return this;
  }
  Array<Type> *pop()
  {
    if (count <= 0)
    {
      return this;
    }
    int newCount = count - 1;
    Type *outArr = new Type[newCount];
    for (int i = 0; i < newCount; i++)
    {
      outArr[i] = this->data[i];
    }
    delete[] this->data;
    this->count = newCount;
    this->data = outArr;
    return this;
  }
  Array<Type> *filter(function<bool(Type)> f)
  {
    Array<Type> *out = new Array<Type>();
    for (int i = 0; i < count; i++)
    {
      if (f(this->data[i]))
      {
        out->push(this->data[i]);
      }
    }
    delete[] this->data;
    this->count = out->count;
    this->data = new Type[out->getCount()];
    out->copy(this->data);
    delete out;
    return this;
  }
  void forEach(function<void(Type)> f)
  {
    if (!this->count || this->count == 0)
      return;
    for (int i = 0; i < this->count; i++)
    {
      f(this->data[i]);
    }
  }
  void swap(int indexA, int indexB)
  {
    Type *a = &this->data[indexA];
    Type *b = &this->data[indexB];
    Type t = *a;
    *a = *b;
    *b = t;
  }
  void sort(function<int(Type, Type)> f)
  {
    if (!this->count || this->count == 0)
      return;
    this->quickSort(0, this->getCount() - 1, f);
  }
  template <typename MapType>
  Array<MapType> *map(function<MapType(Type)> f)
  {
    MapType *outArr = new MapType[this->count];
    Array<MapType> *out = new Array<MapType>(outArr, this->count);
    for (int i = 0; i < this->count; i++)
    {
      out->getData()[i] = f(this->data[i]);
    }
    return out;
  }
  template <typename ReduceType>
  ReduceType reduce(function<ReduceType(ReduceType accumulator, Type currentValue, int currentIndex, Type *srcArray)> f, ReduceType initValue)
  {
    ReduceType value = initValue;
    for (int i = 0; i < this->count; i++)
    {
      value = f(value, this->data[i], i, this->data);
    }
    return value;
  }
  Array<Type> concat(Array<Type> array)
  {
    Array<Type> temp = this->clone();
    array.forEach([=](Type element) {
      temp.push(element);
    });
    return temp;
  }
  Array<Type> reverse()
  {
    Array<Type> temp = this->clone();
    for (int i = 0; i < temp.getCount() / 2; i++)
    {
      temp.swap(i, temp.getCount() - i - 1);
    }
    return temp;
  }
};

class Test
{
public:
  int value;
  Test(int value)
  {
    this->value = value;
  }
};

int main()
{
  Array<int> arr;
  for (int i = 10; i >= 0; i--)
  {
    arr.push(i);
  }
  // arr.sort([](int a, int b) {
  //   if (a > b)
  //     return 1;
  //   if (a < b)
  //     return -1;
  //   return 0;
  // });
  Array<int> arr2 = arr.clone();
  arr2.forEach([](int t) {
    cout << t << endl;
  });
  // for (int i = 0; i < arr.getCount(); i++)
  // {
  //   cout << arr.getData() << endl;
  // }
  cout << "DDDDD" << endl;
}