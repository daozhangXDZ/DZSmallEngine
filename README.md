# SmallEngine

一个特别小的研究引擎【用于各种实验】

1、框架上设计上采用Unreal、Unity的设计思路【偷懒了】
2、（初步预计包含渲染，物理和动画，声音，GamePlayer)

（2019-04-01 见笑）

地址：

最新小功能截图:

-------------TODO：准备间接Shadow 和Light----------------

--------------"分离出Policy, 走 DepthMap, BaseMap, Light(LD，), "

--------------::加入RT缓存到Texture2D, -------加入DebugPolicy 用于观察结果----------------------------------------------------------

----------"灯光组件 加入，分离LightInfo, 准备ShadowMap和MuiPointShadow"`---------------------------------------------------------

![](./Doc/DOCContent/DrowPolicy_RT.PNG)







-------------------------------------------------------------------2019-04-15--------------------------------------------------------------------------

![](./DOC/DOCContent/C01.jpg)

![](./Doc/DOCContent/Material_Normal_BugE.PNG)

## 大概分类

0、底层模块：包括如弱指针，线程，基础数据结构，容器，通用模版等封装：待另外clp-api(某C++深爱者）加入

制作。

1、内程序模块，平台程序模块（显示和输入输出）如窗口、鼠标、键盘、文件等......etc

2、渲染模块，渲染抽象，DX和OpenES封装（分装基础命令和相关资源)......etc

2、编辑器模块、声音模块，动画、物理模块。......etc

3、数据模块、模块维护器、巴拉吧拉etc.......etc

4、GamePlayer结构......etc

## 更新目录说明：

DOCCont

## 大概目录截图

具体可以留言交流（嘻嘻）

基础：完成了DX封装0.1，Render和命令抽象（待），内部程序，主程序，内部窗口，。。。巴拉拉。

### EngineFrameWork_01



![](./ReadMeRes/EngineFrameWork_01.PNG)



### EngineFrameWork_Core_01

![](./ReadMeRes/EngineFrameWork_Core_01.PNG)



### EngineFrameWork_Engine_01

![](./ReadMeRes/EngineFrameWork_Engine_01.PNG)

### EngineFrameWork_NativeApp_01

![](./ReadMeRes/EngineFrameWork_NativeApp_01.PNG)

### EngineFrameWork_RenderEngine_01

![](./ReadMeRes/EngineFrameWork_RenderEngine_01.PNG)
