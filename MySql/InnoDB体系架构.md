### 一、内存

#### 1.1 缓冲池

​	InnoDB是基于磁盘存储的，磁盘IO效率比较低，因此使用缓冲池来提高性能。在数据库中进行页的读取操作时，首先将磁盘读取到的页放在缓冲池中，下一次再读取相同的页时，首先判断该页是否位于缓冲池中，若在则直接读取，否则读取磁盘上的页。对于页的写操作，则首先修改缓冲池中的页，然后以一定的频率刷新到磁盘上。
​	缓冲池的大小直接影响着数据库的性能，通过配置参数 innodb_buffer_pool_size可以设置大小。缓冲池中不仅存放索引页和数据页，还有undo页、插入缓冲、自适应哈希索引和数据字典信息等。
​	Mysql5.6后允许有多个缓冲池实例，每个页根据哈希值分配到不同的缓冲池中。

#### 1.2 LRU list、Free List、Flush list

​	缓冲池中的页大小为16KB，通过LRU列表进行管理，频繁被使用的页位于LRU前端，最少使用的位于LRU尾部。但InnoDB所使用的LRU是经过优化的。首先是midpoint位置，读取到新的页时，虽然它目前是最新被访问的，但并不直接放在LRU列表头部，而是放在LRU列表的midpoint位置。这样做的原因是，如果将新页直接放到头部，某些索引或数据扫描的SQL操作可能会污染LRU列表，将真正的热点数据移除，因为这些操作往往涉及访问非常多个页。midpoint之前的列表称为new列表，之后的为old列表。midpoint位置可以由配置参数innodb_old_blocks_pct决定，默认为37，也就是列表长度的63%的位置。 第二个比较不一样的地方是innodb_old_blocks_time，用于表示页被读取到mid位置后要过多少时间才会被加入LRU列表的热端。

​	LRU列表用于管理被读取的页，而Free list用于存放空闲页，数据库刚启动时LRU列表为空，所有页都是空闲页。当需要从缓冲池中分页时，首先在Free list中查找有无可用的空闲页，有的话把它删除然后加入LRU列表中，否则淘汰LRU尾部的页。

​	LRU列表中的页被修改后称为脏页，脏页既存在于LRU列表中，也存在于Flush list中，Flush列表用于管理将脏页刷回磁盘，二者互不影响。

​	通过命令SHOW ENGINE INNODB STATUS可以看到buffer pool的状态信息，其中有一个重要的观察量：Buffer pool hit rate：表示缓冲池的命中率，通常该值不能低于95%，如果低于95则要观察是否由于全表扫描导致LRU污染。

#### 1.3 redo log缓冲

​	内存区除了缓冲池外，还有一部分空间用于redo log缓冲，这部分空间一般不会很大，默认为8MB。redo log缓冲按照一定频率刷新到磁盘：

*   Master Thread 每一秒将redo log缓冲刷新到磁盘
*   每个事物提交时都会将redo log缓冲刷新到磁盘
*   当redo log缓冲区剩余空间小于一半时将缓冲区中内容刷新到磁盘

### 二、CheckPoint技术

​	为了防止缓冲池中数据页丢失，事物数据库系统普遍采用Write Ahead Log策略，当事物提交时，先写redo log再修改页。CheckPoint技术是一种决定脏页刷新频率的算法。当数据库宕机时，不需要重做所有日志，因为check point之前的已经刷回磁盘。当缓冲池不够用时，根据LRU算法溢出末尾的页，若此页为脏页则强制执行check point，将其刷回磁盘。
​	InnoDB引擎采用LSN，一个8字节的数字来表示从开始到现在产生了多少字节的redo log。每个页有LSN、redo log中也有LSN、Check Point也有LSN。

​	check point分为 sharp check point和 fuzzy check point，前者在数据库关闭时将所有脏页刷回磁盘，可用性比较低，因此在innodb内部使用fuzzy check point进行部分脏页刷新。有以下几种情况的fuzzy check point：

*   Master Thread Check Point：Master Thread差不多以每秒或每十秒的速度从缓冲池的脏页列表中刷新一定比例的页回磁盘，这个过程是异步的，此时用户查询不会被阻塞。
*   FLUSH_LRU_LIST Check Point：innodb引擎会确保LRU list中有至少100个空闲页，倘若没有，那么会将LRU尾部页移除，如果这些页中有脏页，那么进行Check Point
*   Async/Sync Flush Check Point：定义变量 check point age = redo lsn - check point lsn，这个变量的含义就是redo log缓冲区中有多少字节还没被刷新到磁盘。当这个变量的大小大于 75%*redo log file 且 小于 90% redo log file时触发Async Flush，大于90%时触发Sync，大于90的情况很少见。在早期版本，Async Flsh Check Point会阻塞发现问题的用户查询线程，而Sync会阻塞所有用户查询线程，但在Mysql 5.6之后这部分刷新操作放入单独的线程执行，故不会阻塞用户查询线程。
*   Dirty Page Too Much：脏页数量太多，强制进行check point，通过参数 innodb_max_dirty_page_pct控制，默认为75%，意思就是说当缓冲池中脏页数量占据75%时进行check point，刷新一部分到磁盘。

### 三、InnoDB关键特性

#### 3.1 插入缓冲

​	插入缓冲(Insert Buffer)用于提升非聚集索引的插入或更新操作的效率：不是每一次都直接插入到索引页中，而是先判断插入的非聚集索引页是否存在缓冲池中，如果在则直接插入，不在则放到一个Insert Buffer中，然后再以一定的频率和情况进行Insert Buffer和辅助索引页子节点的merge操作。此时通常能将多个插入合并到一个操作中(因为这部分数据都将位于同一个索引页)，于是大大提高对于非聚集索引插入的性能。
​	Insert Buffer的使用需要满足两个条件：1. 索引是非主键索引   2. 索引不是唯一的；在较新的版本中，InnoDB引入change buffer，可将其是为Insert Buffer的升级版，使得InnoDB引擎可以对DML操作(INSERT  DELETE   UPDATE)都进行缓冲。

​	Insert Buffer具体的实现上是一棵B+树，所有的表格的Insert Buffer都存放到同一棵B+树当中。这颗全局B+树的非叶子节点由search key组成，每个search key占九个字节，分别由space、market、offset组成，其中，space表示这个Insert Buffer所在表的表空间id，MySQL中所有的表都有一个唯一的表空间id；market占用一个字节，它用于兼容老版本的Insert Buffer；offset表示页所在的偏移量。叶子节点的组成则是由 search key + metadata + 要插入的数据这三部分组成，metadata占四字节，主要作用是用于排序每个记录进入Insert Buffer的顺序。

#### 3.2 两次写

​	double write机制用于提升数据页的可靠性。在数据库宕机时，有可能InnoDB引擎正在写入某个页，而且只写了一部分，此时重启数据库之后，InnoDB引擎会发现磁盘上的这个页是不完整的(因为上次宕机没写完)，因此redolog也会失效，从而导致部分数据丢失。double write就是在使用redo log之前，用户需要这个页的副本，当写入失效发生时先通过这个页的副本还原页，然后再进行操作。
​	double write分为两部分，一部分是内存中的doublewrite buffer，另一部分是物理磁盘上共享表空间中的连续的128个页，它们大小都为2MB。在对缓冲池中的脏页进行刷新时，并不直接写入磁盘，而是先通过memcpy将脏页复制到doublewrite buffer，然后doublewrite buffer再分两次，顺序地写入共享表空间的物理磁盘上，然后马上调用fsync同步磁盘。完成double write页的写入后，再将double write buffer中的页写入各个表空间文件中，此时写入是离散的。

#### 3.3 自适应哈希索引

​	InnoDB引擎会自动根据访问的频率和模式来自动的为某些热点页建立哈希索引，从而提高数据访问速度。

