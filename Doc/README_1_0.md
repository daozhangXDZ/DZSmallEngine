# SmallEngine

一个特别小的研究引擎【用于各种实验】

0. 5:   Complety

   ![](.\DOCContent\Capt_RenderFrameWork_1-1_Com.PNG)

加入：材质，灯光，Shader模块

更新：

1、框架上分离出材质和Shader模块，

2、Shader中 抽象出ShaderResource.和全局ShaderType

3、RHI层 更新

4、D3D11层加入ComputerShader, 准备加入GeoShader

5、部分逻辑抽象到逻辑层，如材质赋予，纹理【后期扩展】，etc 

6、Engine业务层 加入 World  [World 包含出 WorldSetting]

