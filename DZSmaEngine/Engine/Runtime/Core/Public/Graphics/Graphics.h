//#pragma once
//#include "d3d11.h"
//#include "wrl/Client.h"
//#include "VertexShaders.h"
//#include "PixelShaders.h"
//#include <SpriteBatch.h>
//#include <SpriteFont.h>
//#include "Graphics/Buffer/ConstantBuffer.h"
//#include "Graphics/Define/ConstantBufferTypes.h"
//#include "Graphics/Camera.h"
//#include "Graphics/RenderProxy/PrimitiveSceneProxy.h"
//#include "Graphics/RT/RTMan.h"
//#pragma comment(lib,"d3d11.lib")
//#pragma comment(lib,"DirectXTK.lib")
//
///// <summary>
///// DX渲染
///// </summary>
//class DXGraphics
//{
//
//public:	
//	/// <summary>
//	/// Initializes the specified HWND.
//	/// </summary>
//	/// <param name="hwnd">The HWND.</param>
//	/// <param name="width">The width.</param>
//	/// <param name="height">The height.</param>
//	/// <returns></returns>
//	bool Initialize(HWND hwnd, int width, int height);
//	
//	/// <summary>
//	/// Initializes the specified HWND.
//	/// </summary>
//	/// <param name="hwnd">The HWND.</param>
//	/// <param name="width">The width.</param>
//	/// <param name="height">The height.</param>
//	/// <param name="backColor">Color of the back.</param>
//	/// <returns></returns>
//	bool Initialize(HWND hwnd, int width, int height, const FLOAT backColor[]);
//	
//	void updateFrame(float dt);
//	/// <summary>
//	/// Renders the frame.
//	/// </summary>
//	void RenderFrame(float dt);
//
//
//
//	void SetupPrimitiveSceneProxy(PrimitiveSceneProxy* pProxy);
//private:	
//
//	float AspectRatio()const;
//
//	void UpdateConstant();
//	/// <summary>
//	/// Initializes the direct x.
//	/// </summary>
//	/// <param name="hwnd">The HWND.</param>
//	/// <param name="width">The width.</param>
//	/// <param name="height">The height.</param>
//	/// <returns></returns>
//	bool InitializeDirectX();
//
//	bool InitializeConstantBuffer();
//	
//	/// <summary>
//	/// Initializes the shaders.
//	/// </summary>
//	/// <returns></returns>
//	bool InitializeShaders();
//	
//	///// <summary>
//	///// Initializes the scene.
//	///// </summary>
//	///// <returns></returns>
//	//bool InitializeScene();
//
//	/// <summary>
//	/// InitializeUI
//	/// </summary>
//	/// <returns></returns>
//	bool InitializeUI();
//
//	bool InitializeViewPort();
//
//	bool InitEveri();
//	
//	/// <summary>
//	/// 更新UI
//	/// </summary>
//	void RenderFrameUI();
//	
//	/// <summary>
//	/// Handles the render rt.
//	/// </summary>
//	void HandleRenderRT();
//
////private:
////	void InitExtendMode(CombineMesh* pMeshMode, XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 sca, std::string modelPath, std::wstring mainTexturePath, float pAlpha);
////	void InitEngineMode(CubeMesh* pMeshMode, XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 sca, std::wstring mainTexturePath, float pAlpha);
//
//public:
//	/// <summary>
//	/// 当前摄像机
//	/// </summary>
//	Camera mCamera;				
//
//private:
//	Microsoft::WRL::ComPtr< ID3D11Device >				md3d11Device;
//	Microsoft::WRL::ComPtr< ID3D11DeviceContext >		md3d11DeviceContext;
//	Microsoft::WRL::ComPtr< ID3D11RenderTargetView	>	md3d11RenderTargetView;
//
//	Microsoft::WRL::ComPtr < IDXGISwapChain	>			mdxgiSwapChain;
//
//	
//	//Depth
//	Microsoft::WRL::ComPtr<ID3D11DepthStencilView>	mDepthStencilView;
//	Microsoft::WRL::ComPtr<ID3D11Texture2D>			mDepthStencilBuffer;
//	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> mDdepthStencilState;
//	Microsoft::WRL::ComPtr<ID3D11RasterizerState>	mRasterizerState;
//	Microsoft::WRL::ComPtr<ID3D11RasterizerState>	mRasterizerState_CullFront;
//
//	//Blend
//	Microsoft::WRL::ComPtr<ID3D11BlendState>		mBlendState;
//
//	/// <summary>
//	/// 当前常量区
//	/// </summary>
//	ConstantBuffer<CBDrawingStates>			mCBStates;
//	ConstantBuffer<CBChangesEveryFrame>		mCBFrame;
//	ConstantBuffer<CBChangesOnResize>		mCBOnResize;
//	ConstantBuffer<CBChangesRarely>			mCBRarely;
//	ConstantBuffer<CBChangesEveryDrawing>	mCBDraw;
//
//	//Shader
//	VertexShaders							mVertexShader;
//	PixelShaders							mPixelShader;
//
//	std::unique_ptr<DirectX::SpriteBatch>	spriteBatch;
//	std::unique_ptr<DirectX::SpriteFont>	spriteFont;
//
//	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState;
//	
//	std::vector<PrimitiveSceneProxy*> mCurrRenderList;
//	
//	/// <summary>
//	/// The m rt man
//	/// </summary>
//	RTMan mRTMan;
//private:
//	FLOAT* mbackColor;
//	bool isInit = false;
//
//private:
//
//	float cPosXOffset = 0.0f;
//	float mSpeedX = 0.1f;
//
//	HWND mCurrHwnd;
//	int mCurrWinWidth = 800;
//	int mCurrWinHeight = 600;
//	float* translationOffset;
//
/////DX辅助方法
//
//};
//
