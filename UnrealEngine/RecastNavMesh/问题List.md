1. 跳跃点的数据是如何维护的，比如userid和Offmesh
        首先，拖入一个NavLinkProxy到场景中时，NavLinkCustomComponent会调用INavLinkCustomInterface::GetUniqueId()，为自己获取一个唯一的id(如果此时id==0)，然后调用UNavigationSystemV1::RequestCustomLinkRegistering将自己注册到NavigationSystem中的CustomLinksMap。然后就是构建导航，在FRecastTileGenerator::AppendModifier中会传入NavLink数据，并存储在Generator的OffmeshLinks; 随后在FRecastTileGenerator::GenerateNavigationDataLayer这一步中拿出来作为初始化对应Tile参数，由此Tile中的offMeshConCount和offMeshCons得以初始化（dtCreateNavMeshData）
    
2. 漏斗-拉绳算法

3. 导航投影为什么Z轴只作为过滤不作为权重的一部分，是否意味着查询的时候是先根据xy范围拿到所有的高度层的poly

    ​	答： 首先导航投影不考虑Z轴距离是错误的结论，正确的说法是findNearestPoly2D接口如果没有传最后一个参数tolerance，那么在选择的时候就会走到下面这个分支![image-20250323233250258](D:\WPS\MyNote-main\noteImage\image-20250323233250258.png)
    ​	  这个分支里h只做过滤不作为权重的一部分。问题就出在FPImplRecastNavMesh::ProjectPointToNavMesh这个接口中默认是不传最后一个参数的，所以会出现AI投影导航的时候会投影到离center高度差很多的情况。 回到问题本身，查询的过程中首先是根据exten和tile的大小得到起始遍历tile的x和y，然后遍历地获取x y对应的所有tile，从这里可以看出来tile的存储是基于x和y左边进行的哈希，然后存在一个成员是链表的哈希表里，提取tile的时候的确没有用z轴来过滤，但是后续根据tile获取poly的时候是会做dtOverlapQuantBounds判断的，也就是说最后获取到的poly都是在extent范围内的。

4. 部分路径是怎么得到的

5. 如果存在多层导航网格 Pawn要如何选择使用哪一层

    ​	核心函数是UNavigationSystemV1::GetNavDataForProps(const FNavAgentProperties& AgentProperties, const FVector& AgentLocation, const FVector& Extent)，这个函数接受参数AgentProperties，并根据AgentProperties返回对应的NavData，也就是在这里决定了使用那一层导航。那么AgentProperties是从哪来的呢，Pawn中有个接口叫GetNavAgentPropertiesRef，其实现是尝试去拿移动组件上的AgentProperties，这个AgentProperties主要定义了Agent的宽、高和step height，从他的哈希函数中也可以看出。

    ![image-20250324000557784](D:\WPS\MyNote-main\noteImage\image-20250324000557784.png)
    ![image-20250324001044744](D:\WPS\MyNote-main\noteImage\image-20250324001044744.png)

    ​		UNavigationSystemV1存储了不同FNavAgentProperties到不同NavigationData的映射，而这个映射的初始化是在RegisterNavData函数中完成的。我们知道UE4可以配置不同的参数来生成多层导航网格，这个不同参数其实对应的是结构体FNavDataConfig，而FNavDataConfig是FNavAgentProperties的子类，这样就能在初始化NavigationData的时候，也初始化这不同配置到不同数据的映射，Pawn或者说Agent只要定义好自己是哪种FNavAgentProperties，就能在各个需要用到导航的地方使用对应层导航。而如果自定义的FNavAgentProperties跟哪个都匹配不上，则会选择最接近的那一个![image-20250324001122103](D:\WPS\MyNote-main\noteImage\image-20250324001122103.png)

6. 导航网格生成的相关参数有哪些，会对导航网格生成的结果产生哪些影响

7. 导航的area type是什么，他是怎么影响到poly的cost和filter的

    答： area type是一种对地形的定义，包括可不可行走、行走的消耗等，通常用于区分不同区域。 首先是他的注册，每个导航区域类型对应一个UNavArea类，在他的PostLoad中会将自己注册到导航系统中：UNavigationSystemV1::RequestAreaRegistering(GetClass())。然后在注册NavigationData时，UNavigationSystemV1会把存起来的area type传给NavigationData，以初始化他的成员SupportedAreas。在这一步中，还会给每个NavAaea分配一个Id，这个id后面会存储在dtpoly的成员中，同时还会将areaid和cost作为一组数据存放到默认的过滤器中![image-20250324233906566](D:\WPS\MyNote-main\noteImage\image-20250324233906566.png)

    ![image-20250324234453495](D:\WPS\MyNote-main\noteImage\image-20250324234453495.png)

     后续在寻路的过程中，对于每个遍历到的poly，首先会用filter尝试把cost过高的类型过滤，如果没有被过滤那么后续还会用到这个cost来作为代价的系数(这里描述的是默认filter的实现)：

    ![image-20250324234700220](D:\WPS\MyNote-main\noteImage\image-20250324234700220.png)

    ![image-20250324234720357](D:\WPS\MyNote-main\noteImage\image-20250324234720357.png)![image-20250324234755206](D:\WPS\MyNote-main\noteImage\image-20250324234755206.png)

8. 如何实现自己的过滤器，以实现不同AI查询出不同的路径

