### 一、 UReplicationGraphNode_GridSpatialization2D

​	这个函数将世界分割为若干个CELL，每个CELL对应一个UReplicationGraphNode_GridCell节点。决定Cell划分方式的是这三个成员变量
![image-20250101022945377](D:\WPS\MyNote-main\noteImage\image-20250101022945377.png)

![image-20250101023932146](D:\WPS\MyNote-main\noteImage\image-20250101023932146.png)	

​	对一个Actor而言，它的WorldLocation+CullDistance可以组成一个正方形，这个正方形内所覆盖的Cell，都会添加这个Actor，StaticActor和DynamicActor的处理方式略有不同，但总的来说都是根据空间划分添加到对应格子里。同步时会根据Viewer所在的Cell来得到需要同步的Actor。
​	添加Actor时，首先会检查这个Actor的位置是不是在划分范围内，实际上是和空间划分的坐标最小值比较，也就是SpatialBias。当坐标X或Y小于SpatialBias的X或Y时，检查这个Actor对应的Class在不在空间rebuild黑名单RebuildSpatialBlacklistMap内，如果是则忽略，否则将重新划分cell。

![image-20250101023322165](D:\WPS\MyNote-main\noteImage\image-20250101023322165.png)

#### 1.1 AddStatic

​	首先会检查Actor是否初始化完毕，如果还没初始化完成就先添加到PendingStaticSpatializedActors，这个数据结构将在后续RG发起同步Actor时再遍历一次并将初始化好的Actor添加进来。对于正常的Actor，假如它位置在范围内(也就是rebuild为false)，那么首先根据它的Location和CullDistance得到它总共跨越了哪些Cell（也就是GetCellInfoForActor函数完成的工作，这里得到的是Cell的Index的StartX  EndX StartY EndY），然后根据这四个Index去遍历Grid数组获取对应Cell的UReplicationGraphNode_GridCell节点，需要注意的是Grid数组一开始是空的，它只在需要的时候才去扩充自己并构造UReplicationGraphNode_GridCell
![image-20250101024714122](D:\WPS\MyNote-main\noteImage\image-20250101024714122.png)

![image-20250101024720966](D:\WPS\MyNote-main\noteImage\image-20250101024720966.png)

#### 1.2 AddDynamic

​	AddDynamic比较简单，直接将Actor的数据存到DynamicSpatializedActors，因为是动态Actor，在这个地方获取到的Cell可能到了进行Actor同步的时候又会发生变化，因此动态Actor都是等到PrepareForReplication才去更新Cell并把自己放到对应节点里(这个放到Cell里的过程跟Static是一样的)

#### 1.3 PrepareForReplication

​	直接遍历DynamicSpatializedActors，更新动态Actor到对应的Cell中，具体做法是：先获取PreviousCellInfo，然后根据当前位置获取到的CellInfo，对比它们覆盖的Cell进行增删。需要注意的是执行这些操作的前提是rebuild == false

#### 1.4 GatherActorListsForConnection

​	1. 遍历Connection的Viewers，根据VIewer位置获取对应格子，再将对应格子的Actor进行同步。需要注意的是这里实际上调用的是UReplicationGraphNode_GridCell的GatherActorListsForConnection函数。这个过程中还会记录Viewer当前Cell信息和上一次同步时的Cell信息，并将当前Cell记录进ActiveGridCells

![image-20250101203422049](D:\WPS\MyNote-main\noteImage\image-20250101203422049.png)

2. 如果bDestroyDormantDynamicActors为true，则将尝试把上一次同步时所处的Cell中冬眠的Actor销毁，如果上一次所处的Cell位于ActiveGridCells则不处理。销毁的同时还会将这个Actor添加到它所属的Cell中的冬眠节点
   ![image-20250101231241928](D:\WPS\MyNote-main\noteImage\image-20250101231241928.png)

![image-20250101231500287](D:\WPS\MyNote-main\noteImage\image-20250101231500287.png)

### 二、UReplicationGraphNode_GridCell

​	一个继承自UReplicationGraphNode_ActorList的节点，它包含一个冬眠Actor节点UReplicationGraphNode_DormancyNode和动态Actor节点UReplicationGraphNode_ActorListFrequencyBuckets。对于静态Actor的添加，先判断是否为冬眠状态，如果是放到冬眠节点，否则调用Super的NotifyAddNetworkActor。动态Actor则直接转发到UReplicationGraphNode_ActorListFrequencyBuckets

### 三、 UReplicationGraphNode_ActorListFrequencyBuckets

​	这是一个自带负载均衡的节点，如果没有特殊设置，那么每次进行Actor同步时会在NumBuckets个队列中轮流选一个进行复制。添加新Actor的时候也是选择当前Actor数量最少的队列进行添加。FSetting中包含数组BucketThresholds，用于外部灵活指定多少数量的Actor对应多少数量的Bucket。增删完Actor时会触发均衡检查，这一步会遍历BucketThresholds，如果Actor数量少于MaxActor就用对应的NumBuckets重新分配，这也意味着这个数组如果有使用必须保证是有序的。
![image-20250102001940994](D:\WPS\MyNote-main\noteImage\image-20250102001940994.png)

![image-20250102003544413](D:\WPS\MyNote-main\noteImage\image-20250102003544413.png)

​	再来看收集Actor时的行为：如果没有配置EnableFastPath，则每次只会收集一个队列的Actor，配置了EnableFastPath则其余队列中的Actor会以ReplicateActorListsForConnections_FastShared进行同步。至于那些流式关卡的Actor，则会检查在这个Connection中对应的关卡是否可见，只要可见的就同步
![image-20250102003839020](D:\WPS\MyNote-main\noteImage\image-20250102003839020.png)