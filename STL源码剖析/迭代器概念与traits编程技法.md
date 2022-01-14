## 一、迭代器

​	迭代器是STL实现泛型思维的重要角色，它扮演着数据容器和算法之间的胶着剂，例如下面这个算法find():

```c++
template<class InputIterator,class T>
InputIterator find(InputIterator first,InputIterator last,const T& value){
    while(first!=last&&*first!=value)
        ++first;
    return first;
}
```

​	可见，有了迭代器之后，执行容器内的find算法就只需要传入容器对应的迭代器，而不需要为每个容器都设计一个find算法，这样就实现了容器算法的分离。
​	从代码中可以看出，迭代器的行为类似指针，实际上，迭代器就是一种广义指针，因此迭代器最重要的工作就是对operator*和operator->进行重载工作。针对某个容器设计的迭代器，将会暴露容器的许多细节，换句话说，要设计出某个容器的迭代器，首先必须对容器本身有足够丰富的了解，因此干脆将迭代器的设计工作交给容器设计者完成，如此一来所有实现细节都能得到封装，这也就是为什么STL每一种容器都有自己的专属迭代器。
​	迭代器也会带来一个问题：假设算法中需要声明一个变量，类型为“迭代器所指向的对象的类型”时，该怎么办？参数推导机制可以作为一种不太完美的解决方法：

```c++
template <class I,class T>
void fun_impl(I iter,T t){
    T tmp;
    ...;
}
template <class I>
inline void func(I iter){
    func_impl(iter,*iter);//分别为指针和指针解引用，*iter就代表迭代器所指向的对象
}						  //再由函数func_impl推导出其类型，函数func_impl也完成了算法的所有工作

int main(){
    int i;
    func(&i);
}
```

​	迭代器所指向的类型称为该迭代器的value_type，参数类型推导技巧并非全面可用，例如当value type必须用于函数的返回值时，就束手无策了，因此需要一种更高明的方法来推导类型，即Traits编程技法。

## 二、Traits编程技法

```c++
template<class T>
struct MyIter{
    typedef T value_type;
    ...
}
//通过内嵌型别声明来解决问题，注意，返回值必须加上关键字typename，因为T是一个模板参数，
//在它被编译器具现化之前，编译器对T一无所知，所以要通过关键字typename告诉编译器这是一个类型
//不然通不过编译。这种方法也有风险：并不是所有类型都是class type，原生类型无法内嵌型别
template<class I>
typename I::value_type func(I ite){
    return *ite;
}

//下面来看traits：
template<class I>
struct iterator_traits{
    typedef typename I::value_type value_type;
}
//上述代码中，假设I是某个类，且类内有内嵌型别声明，则通过这行代码可用把其型别萃取出来
//这也要求传进来的型别参数对应的类内要声明内嵌型别
//这么一看似乎只是多了一层封装，但好处就是，这样子traits可拥有为原生类型服务的偏特化版本：
template<class T>
struct iterator_traits<T*>{
    typedef T value_type;
}

template<class T>
struct iterator_traits<const T*>{
    typedef T value_type;
}
//这样一来，一个int*型的迭代器也可通过traits取出其value_type!
```

​	traits扮演的“类型萃取机”能够萃取出各个迭代器的特性，当然，若要它生效，每一个迭代器都必须遵守约定，自行以内嵌型别定义的方式定义出相应型别。根据经验，最常用到的迭代器相应型别有五种：value_type   difference type, pointer, reference, iterator catagoly：

```c++
template<class I>
struct iterator_traits{
    typedef typename I::iterator_categoly  iterator_categoly;//迭代器类型
    typedef typename I::value_type		   value_type;       //迭代器所指对象的类型
    typedef typename I::difference_type    difference_type;  //两个迭代器中间距离
    typedef typename I::pointer			   pointer;          //迭代器所指向的对象的地址
    typedef typename I::reference          reference;        //迭代器所指对象的引用
}
```

### 2.1 迭代器的类型

​	根据移动特性与施行操作，迭代器被分为五类：

```c++
Input Iterator:这种迭代器指向的对象，不允许外界改变。只读
OutPut Iterator：只写
Forward Iterator：允许在此种迭代器形成的区间上执行读写操作
Bidirectional Iterator：可双向移动，某些算法需要逆向访问某个迭代器区间
Random Access Iterator：前四种迭代器只供应一部分指针算数能力，第五种则覆盖所有指针算数能力
```

​	选择适当的迭代器有助于提高效率，例如当类型是原生类型时，选用第五种类型的迭代器可以实现跳跃前进(即i+n，因为它支持指针的这一算数操作)

```c++
template<class InputerIterator,class Distance>
void advance_II(InputerIterator& i,Distance n){
    while(n--)++i;
}

template <class BidirectionalIterator,class Distance>
void advance_BI(BidirectionalIterator& i,Distance n){
    if(n>0)
        while(n--)++i;
    else
        while(n++)--i;
}

template<class RandomAccessIterator, class Distance>
void advance_RAI(RandomAccessIterator& i,Distance n){
    i+=n;
}
//可见，对于同一算法，不同类型的迭代器效率是完全不同的，因此用traits萃取出迭代器类型作为该算法
//的第三参数，然后根据第三参数决定适用哪种方法实现可以提高效率

//下面是五个作为标记用的型别：
struct input_iterator_tag();
struct output_iterator_tag();
struct forward_iterator_tag():public input_iterator_tag();
struct bidirectional_iterator_tag:public forward_iterator_tag();
struct random_access_iterator_tag:public bidirectional_iterator_tag();
//这些class只是作为标记使用，所以不需要任何成员
//于是现在我们可以重新设计advance！
template<class InputerIterator,class Distance>
void __advance(InputerIterator& i,Distance n,input_iterator_tag){
    while(n--)++i;
}

template <class BidirectionalIterator,class Distance>
void __advance(BidirectionalIterator& i,Distance n,bidirectional_iterator_tag){
    if(n>0)
        while(n--)++i;
    else
        while(n++)--i;
}

template<class RandomAccessIterator, class Distance>
void __advance(RandomAccessIterator& i,Distance n,random_access_iterator_tag){
    i+=n;
}
//上述函数的第三个参数仅用来形成函数重载
template<class InputIterator,class Distance>
void advance(InputIterator& i,Distance n){
    //萃取出迭代器的类型：
    __advance(i,n,iterator_traits<InputIteratir>::iterator_category());
}
```

### 2.2 std::iterator的保证

​	STL提供了一个iterator class，如果每个新设计的迭代器都继承它，就可保证都符合STL所需的规范：

```c++
template<class Categroy,class T,class Distance=ptrdiff_t,class pointer=T*,class 						Reference=T&>
struct iterator{
    typedef Category    iterator_Category;
    typedef T		    value_type;
    typedef Distance    difference_type;
    typedef Pointer     pointer;
    typedef Reference   reference;
}
//由于最后三个型别参数都有默认值，所以可以这么写：
template<class Item>
struct ListIter:public std::iterator<std::forward_iterator_tag,Item>{
    ...;
}
```

