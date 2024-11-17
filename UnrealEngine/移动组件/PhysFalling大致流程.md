首先是计算速度，从蒙太奇或者输入的加速度/寻路组件中获取当帧速度，再单独的将重力叠加在速度上。

![image-20241113221802645](D:\WPS\MyNote-main\noteImage\image-20241113221802645.png)

![image-20241113221847414](D:\WPS\MyNote-main\noteImage\image-20241113221847414.png)

![image-20241113221856159](D:\WPS\MyNote-main\noteImage\image-20241113221856159.png)

​	然后是根据速度算出delta，这里使用中点积分法来算距离，估计是为了减少误差，然后调用SafeMoveUpdatedComponent执行位移，根据位移结果是否有碰撞产生可以分为两种情况，最简单的是有碰撞，调用IsValidLandingSpot检查当前落点是否合法，如果是则调用ProcessLanded将移动模式变为Walking或者NavWalking并调用StartNewPhysics进行新一轮移动(注：如果是NavWalking，还会做一次导航投影，投影失败时设置为Walking)，如果没有碰撞那就什么都不做。
​	IsValidLandingSpot主要是移动的HIt和FindFloor的结果判断当前落到的位置可不可走，比较特殊的是根据Hit结果的判断：如果胶囊体没有和其他东西渗透，就调用IsWithinEdgeTolerance，这个函数用来检查碰撞点到胶囊体中心点的**平面距离**是否小于一定值，如果是则认为可以落地。这个流程的作用应该是让胶囊体落到一些过度倾斜的斜面时可以继续下滑，当然，胶囊体本身如果倾斜了也会导致判断不通过。上面提到的根据Hit和FindFloor两个条件是都必须满足，FindFloor找到的必须是WalkableFloor。
​	IsValidLandingSpot判断不通过的情况比较复杂，UE分了几种情况处理。

1. Hit不可走：如果落在比较倾斜的斜面上，Hit会被判断为不可走，此时调用ShouldCheckForValidLandingSpot，这个函数主要是判断了下Hit的Normal和ImpatNormal是否一致，不一致说明落在倾斜面上，然后再调用下IsWithinEdgeTolerance，检查碰撞点到胶囊体中心的平面距离是否足够小，如果是则执行一下FindFloor（FindFloor找到的屏幕或许是可走的，这可能发生在梯形盆地），然后用Floor的Hit再去做一次IsValidLandingSpot检测，通过的话也认为已经落地
   ![image-20241113232159479](D:\WPS\MyNote-main\noteImage\image-20241113232159479.png)

2. 在1不成立的情况下，重新计算没有AirControl的速度并计算出新的Adjust，新的Adjust依然是有加速度并且受到AirControl的Ajdust
   ![image-20241114234348806](D:\WPS\MyNote-main\noteImage\image-20241114234348806.png)

3. 利用2计算出的Adjust，调用ComputeSlideVector计算滑墙的向量，并利用这个新的向量再次进行位移，如果位移的Hit满足IsValidLandingSpot的判断，则执行落地流程并返回![image-20241114234703116](D:\WPS\MyNote-main\noteImage\image-20241114234703116.png)

4. 如果第三步的滑墙逻辑依然无法移动到一个可站立的平台，则判断，如果前面的移动逻辑有AirControl，则用不带AirControl的速度再算一个Adjust，然后再调用一次ComputeSlideVector，并且这次的Time是1.0。然后再调用一次TwoWallAdjust计算出最终的Delta![image-20241118003922153](D:\WPS\MyNote-main\noteImage\image-20241118003922153.png)

   ​	在用Delta做最终移动前还会先求一个布尔值bDitch，这个值的含义是当前是否卡在两个无法站立的斜坡上(V字地形)。然后调用SafeMoveUpdatedComp进行位移，如果本次位移完全没有移动(Time==0)，则用第一次移动Hit.Normal和本次移动的Normal相加并处理为平面单位向量进行小幅度位移。尝试离开当前位置![image-20241118004759910](D:\WPS\MyNote-main\noteImage\image-20241118004759910.png)

5. 后续的处理，加入bDitch为ture或者最后一次碰撞的地方可以站立(通常情况下应该是不行的， 想象不出来这里有什么地形会符合这个条件，感觉像碰运气)或者最后一次移动依然完全没有位移产生，那么也执行ProcessLanded退出falling，这里应该是期待后续靠walking的逻辑走出这块区域。

   ![image-20241118005028264](D:\WPS\MyNote-main\noteImage\image-20241118005028264.png)
   而如果这三个条件都不满足，最后一步：看着像是往上地、xy方向随机的一个速度进行位移，尝试走出当前被卡住的地方

![image-20241118005428687](D:\WPS\MyNote-main\noteImage\image-20241118005428687.png)

