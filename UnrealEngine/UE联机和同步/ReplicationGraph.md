#### 一、简介

​	在UE4常规的Actor同步流程中，UNetDriver的TickFlush函数会调用ServerReplicateActors来完成一次O(M*N)的遍历，其中M是需要同步的Actor数量，N是客户端连接数，这种方式不仅在DS端消耗高，客户端也会收到一些可能它并不需要关心的Actor的同步数据(比如有只怪物离得非常远)。ReplicationGraph是一种优化上述同步算法的方式，通过提供一些节点，针对不同的Connection去收集它需要同步的Actor，这些节点可以是全局节点(也就是每个Connection都会跑到)，也可以是Connection自己拥有的节点。
​	UNetDriver::ServerReplicateActors中会先检查是否存在ReplicationDriver，如果是那么同步Actor的操作便交给ReplicationDriver。只要将项目的ReplicationGraph类作为ReplicationDriver即可修改同步Actor的流程![image-20241229203005939](D:\WPS\MyNote-main\noteImage\image-20241229203005939.png)

​	替换ReplicationDriver的方式有两种，一种是在DefaultEngine文件中：

![image-20241229203606913](D:\WPS\MyNote-main\noteImage\image-20241229203606913.png)

另一种是直接在代码里写死：

![image-20241229203620008](D:\WPS\MyNote-main\noteImage\image-20241229203620008.png)

#### 二、UReplicationGraph::ServerReplicateActors

1. 先检查同步的时间间隔，自增NetDriver上的ReplicationFrame变量、然后通过ON_SCOPE_EXIT注册了一个lamba用于在函数执行完毕时自增ReplicationGraphFrame和关闭这一帧中需要判断出需要被关闭的Connection
2. 为每个节点执行PrepareForReplication，节点中有变量标准自己是否需要执行这个函数，如果为true那么在初始化时会被添加到RG的PrepareForReplicationNodes数组中
   ![image-20241229204458498](D:\WPS\MyNote-main\noteImage\image-20241229204458498.png)

3. 遍历所有的Connection：

   1. 先检查Connection是否已经准备好连接，并构造一个ConnectionViwer数组，收集这个Connection的Viwer信息，由于可能存在分屏游戏，Connection结构中有Children数组，它们也同样需要被放到ConnectionViwer数组中，并且为PlayerController调用SendClientAdjustment![image-20241229210646867](D:\WPS\MyNote-main\noteImage\image-20241229210646867.png)

   2. 注册一个匿名函数在这一轮循环的末尾执行：TODO 暂时不知道是干嘛的![image-20241229210856081](D:\WPS\MyNote-main\noteImage\image-20241229210856081.png)

   3. 接着是最关键的一步：为这个Connection收集需要同步的Actor列表。首先构造FConnectionGatherActorListParameters。这个结构包含当前Connection所有的Viewer信息、ConnectionManager本身(RG对Connection的一种封装)，客户端可视的流式关卡名称(有些节点需要它去同步对应关卡里那些永远需要同步的Actor)，和一个传出参数GatheredReplicationListsForConnection
      ![image-20241229211640047](D:\WPS\MyNote-main\noteImage\image-20241229211640047.png)

      然后是调用所有的Node，包括Global和连接自身持有的，调用它们的GatherActorListsForConnection函数收集Actor列表![image-20241229211911088](D:\WPS\MyNote-main\noteImage\image-20241229211911088.png)

      最后是更新Viewers的Location，这一步还会将之前原本应该销毁但因为距离太远没销毁的Actor给拿出来，稍后会遍历并通知客户端销毁
      ![image-20241229212817386](D:\WPS\MyNote-main\noteImage\image-20241229212817386.png)

      ![image-20241229212904210](D:\WPS\MyNote-main\noteImage\image-20241229212904210.png)

      ![image-20241229212928237](D:\WPS\MyNote-main\noteImage\image-20241229212928237.png)

   4.  收集完毕后开始进行Actor的同步，这一步跟原生的逻辑没有什么不同 TODO (需要更详细的流程)
      ![image-20241229213150260](D:\WPS\MyNote-main\noteImage\image-20241229213150260.png)
   5. 遍历该Connection所持有的ActorChannel，并关闭那些不再相关的ActorChannel
      ![image-20241230090836822](D:\WPS\MyNote-main\noteImage\image-20241230090836822.png)
   6. 处理需要被销毁的Actor，第一个函数中只会先销毁离Viewer足够近的Actor![image-20241230091427833](D:\WPS\MyNote-main\noteImage\image-20241230091427833.png)
   7. 最后，判断Connection是否发生复制错误，是的话关闭这个连接
      ![image-20241230091931244](D:\WPS\MyNote-main\noteImage\image-20241230091931244.png)

4. 更新Actor完毕，调用 PostServerReplicateStats(原生的RG中这是个空函数)进行一些需要放在Actor同步完成后的逻辑
   ![image-20241230092116145](D:\WPS\MyNote-main\noteImage\image-20241230092116145.png)

#### 三、 初始化

​	ReplicationDriver的初始化由下面三个函数完成。其中比较重要的是InitForNetDriver和InitializeActorsInWorld，在RG的实现中这两个函数完成了对不同类型复制策略的标记和将当前World中所有Actor添加到RG。UE4官方示例ShooterGame中的ShooterReplication还对以上行为进行了扩展，包括创建全局节点、实现RouteAddNetworkActorToNodes函数等。
![image-20241230235559906](D:\WPS\MyNote-main\noteImage\image-20241230235559906.png)

##### 3.1 InitForNetDriver

![image-20241230235942337](D:\WPS\MyNote-main\noteImage\image-20241230235942337.png)

​	可以看到，InitForNetDriver的主要工作是将一些类提前注册到GlobalActorReplicationInfoMap，以及初始化全局节点。GlobalActorReplicationInfoMap是一个比较重要的数据结构，它包含两个主要成员：ActorMap (Actor*映射TUniquePtr\<FGlobalActorReplicationInfo\>,也就是说这个世界中的每个需要复制的Actor都会在这里注册一份对应的复制信息，里面包含着上次同步时间、WorldLocation等)    ClassMap(UClass\*映射FClassReplicationInfo 也就是对于每一类需要复制的Actor都对应一份配置，例如优先级、同步裁剪距离等)。
​	另外一个数据结构RPC_Multicast_OpenChannelForClass同样是以UClass为key，意思是这一类Actor如果需要发送MulticastRPC但是他的ActorChannel不存在，那么考虑为他先把ActorChannel创建出来。考虑的条件是要么这个Actor的同步不受距离限制，要么在Connection对应的Viewer的裁剪距离之内，这样做的原因是，对于这个Connetion虽然这个Actor暂时还没有ActorChannel，但是按照规则它很可能马上就会创建一个ActorChannel，那么这里就不把它的多播RPC抛弃而是提前创建出来。
​	至于InitGlobalGraphNodes，原生的RG里这是个空函数，留给子类实现，例如ShooterReplicationGraph：![image-20241231001130013](D:\WPS\MyNote-main\noteImage\image-20241231001130013.png)

##### 3.2 InitializeActorsInWorld

​	这一步主要是遍历World中的Actor并把它们添加到GlobalActorReplicationInfoMap，这里的Get方法实现中如果Actor对应的数据不存在还会根据ClassMap中存储的信息为他构造一份
![image-20241231002234684](D:\WPS\MyNote-main\noteImage\image-20241231002234684.png)

##### 3.3  UShooterReplicationGraph::InitGlobalActorClassSettings

#### 四、新增的Actor和连接如何被添加到RG

​	![image-20241231012945616](D:\WPS\MyNote-main\noteImage\image-20241231012945616.png)

UE的网络同步流程中，新增Actor和ClientConnection时都会先检查是否存在ReplicationDriver，如果是就调用ReplicationDriver上对应的Add\Remove函数