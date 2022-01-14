## 一、RTTI

​	RTTI是运行阶段类型识别，用于确定对象的类型。C++有3个支持RTTI的元素：

1.  dynamic_cast：如果可能的话，该运算符将使用一个指向基类的指针来生成一个指向派生类的指针，否则返回空指针

     		2. typeid运算符返回一个指出对象类型的值
     		3. type_info结构存储了有关特定类型的信息。

注意：只能将RTTI用于包含虚函数的层次类型结构，原因在于只有对于这种类层次结构，才应该将派生类对象的地址赋给基类指针。

### 1.1 dynamic_cast运算符：

​	dynamic_cast运算符是最常用的RTTI组件，它主要用于解决"是否可以安全地将对象的地址赋给特定类型的指针"这样的问题，语法如下：

```c++
class Grand{};
class Superb:public Grand{};
class Magnificent:public Superb{};

Superb *pm=dynamic_cast<Superb *>(pg);
//即进行判断：指针pg的类型是否可以安全的转换为Superb*，如果可以则运算符将返回对象地址，否则返回空指针
//也可以将这个运算符用于引用，但没有与空指针对应的引用值，因此当请求不正确时，将引发bad_cast异常
```

### 1.2 typeid运算符和typeiofo类

​	typeid运算符能用于确定两个对象是否为同种类型，与sizeof有点像，可接受两种参数：类名以及结果为对象的表达式，typeid运算符返回一个对type_info的引用，type_info是在头文件typeinfo中定义的一个类，重载了==和!=运算符，以便使用它们进行类型比较：

```c++
typeid(Magnificent)==typeid(*pg);
//如果pg指向的是一个Magnificent对象则返回true，否则返回false
//如果pg是一个空指针，则引发bad_typeid异常
//type_info的实现随厂商而异，但包含一个name成员，通常是类的名称
```

### 1.3 误用RTTI的例子

```c++
for(int i=0;i<5;i++){
    pg=Getone();
    pg->speak();
    if(ps=dynamic_cast(Superb *)(pg))
        ps->say()
}

//这是误用的情况：
for(int i=0;i<5;i++){
    pg=Getone();
    if(typeid(Magnifcent)==typeid(*pg)){
        ...
    }
    else if(typeid(Superb)==typeid(*pg)){
        ...
    }
}

//当if else语句中使用了typeid，则应考虑是否应该使用虚函数和dynamic_cast
```

