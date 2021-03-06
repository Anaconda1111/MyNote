## 一、open函数

​	![1644653498629](D:\DaSan\note\noteImage\1644653498629.png)

 ### 1.1 参数说明

1.  pathname：文件路径

 	2. flags：文件打开标志，有三个是必须且互斥的：O_RDONLY   O_WRONLY   O_RDWR，分别代表只读、只写和读写，其它一些例如：O_EXCL()   O_TRUNX(截断文件为0)   O_CREAT(要创建新文件)是可有可无。当要创建新文件时，必须使用具有第三个参数的函数，也即必须用mode参数。
 	3. mode：文件权限，用八进制数字表示，例如777即可

### 1.2 返回值

​	返回在PCB中该文件的文件描述符，如果文件不存在或执行失败则返回-1，可以利用该返回值做条件判断。

### 1.3 perror函数

​	perror函数用于在发生错误时在输出的错误信息前进行补充，例如perror("open file:")。那么打开文件失败时就会显示open file：.....

## 二、read函数和write函数

### 2.1 read函数

![1644655303162](D:\DaSan\note\noteImage/1644655303162.png?lastModify=1644678609)

参数说明：fd -- 文件描述符     buf -- 将数据读入缓冲区    count --  缓冲区大小 返回值说明：返回值是个有符号整型， -1 -- 读文件失败   0 -- 文件读完了   >0 -- 读取的字节数

### 2.2 write函数

![1644655583946](D:\DaSan\note\noteImage/1644655583946.png?lastModify=1644678609)

参数说明： fd -- 文件描述符     buf -- 要写入的数据存放的缓冲区    count --  缓冲区大小 返回值说明：

## 三、stat函数

​	![1644678812952](D:\DaSan\note\noteImage\1644678812952.png)

### 3.1函数功能

​	获取文件的详细信息，包括inode、硬链接数、大小、修改时间等，将这些信息储存在结构体中。lstata与stat的区别就在于针对软连接文件上的行为不同，stat会追踪软连接找到原本的文件，而lstat不会追踪，只会提取软连接文件的信息。

### 3.2 参数、返回值

1. 参数：文件路径或文件描述符、用于存储信息的结构体。

 	2. 返回值：int类型，-1时表示执行失败，其它表示执行成功。

### 3.3 结构体成员

![1644679010664](D:\DaSan\note\noteImage\1644679010664.png)

## 四、unlink函数

​	![1644680668073](D:\DaSan\note\noteImage\1644680668073.png)

### 4.1 函数功能

​	删除文件的硬连接或软连接，如果文件硬链接数为1，则直接删除文件。它的作用是用于删除创建的临时文件，例如缓存文件，需要在程序执行结束后被删除的，可以先open函数创建一个，然后unlink，在close那个文件之前，它不会被删除，在使用完并close后才会。

### 4.2 参数与返回值

​	1. 参数：文件名   2. 返回值：-1失败，其他值表示成功

## 五、dup和dup2函数

![1644685311867](D:\DaSan\note\noteImage\1644685311867.png)

### 5.1 函数功能

​	dup和dup2函数都用于将文件描述符数组中的一个描述符指向指定的文件，有点像复制过去，并将新的文件描述符返回。dup函数接受一个oldfd，并将数组中下标值最小的那个指向该文件，而dup2可以指定一个newfd，如果这个newfd已经被占用了，就关闭它对应的文件，然后再指向该文件，并返回新的fd值。当然，如果old==new，就不关闭，直接返回

## 六、fcntl函数

![1644685662655](D:\DaSan\note\noteImage\1644685662655.png)

### 6.1 函数功能

​	fcntl函数可用于查看与修改文件的属性，例如将一个原本为只读属性的文件添加一个可追加属性，但没办法改为只写属性！

### 6.2 函数参数

​	1. fd：文件描述符    2. cmd：F_GETFL或F_SETFL，前者表示读属性，后者表示要设置属性  3. 可变参数：如果是要读属性，那么这里写0就好，如果是要设置属性，首先读取属性，然后按位或上要增加的属性，再将新的属性作为第三个参数。

![1644686004753](D:\DaSan\note\noteImage\1644686004753.png)

### 6.3 返回值

​		如果是-1表示函数执行失败，否则函数执行成功。

## 七、环境变量控制函数

### 7.1 getenv

<img src="D:\DaSan\note\noteImage\1644768524137.png" alt="1644768524137" style="zoom:150%;" />	

查看环境变量值的函数，输入为环境变量的键，如果存在则返回对应的值，否则返回NULL

### 7.2 setenv / unsetenv

![1644768672259](D:\DaSan\note\noteImage\1644768672259.png)

1.  setenv：左右是新增或覆盖一个环境变量，参数overwrite必须不为0才可以覆盖，执行成功返回0，否则返回-1
2.  unsetenv：删除对应的环境变量，成功返回0，否则返回-1，值得注意的是，如果环境变量不存在不会返回-1，只有当输入是”ABD=“之类的才会返回-1。

## 八、pause函数

​	<img src="D:\DaSan\note\noteImage\1645019375782.png" alt="1645019375782" style="zoom:200%;" />

​	功能是暂停进程直到有信号发送到该进程，只有当信号被捕捉且信号捕捉函数执行完成后pause函数才会返回，其返回值为-1.