So this is a test. Let's say i want to design a program. 
It will do a few things. 
```cpp
int main()
{
    cout << "Hello world" << endl;
    countToTen();
    return 0;
}
```

First of all, we'll need some imports. Here, we need the `iostream`. 
```cpp
//0
#include <iostream>
```
This will give us access to cout and endl, but we need to use the `std` namespace.
```cpp 
//1
using namespace std;
```

Finally, we need to define the `countToTen()` function. 
We can do as such :
```cpp
//2 
void countToTen()
{
    for(int i = 1; i < 11; i++)
    {
        cout << i << endl;
    }
}
```

```cpp 
//rignore 
//hello world
```
