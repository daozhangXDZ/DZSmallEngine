//#include "Graphics/AdapterReader.h"
//#include "Graphics/Graphics.h"
//#include "LogUtil/ErrorLogger.h"
//#include "LogUtil/COMException.h"
//#include <WICTextureLoader.h>
//#include "Graphics/Define/ConstantBufferTypes.h"
//#include "EngineWorldUtil.h"
//#include "Engine/Engine.h"
//
//
//bool DXGraphics::Initialize(HWND hwnd, int width, int height)
//{
//	FLOAT vBC[] = { 0.0f,0.0f,0.0f,1.0f };
//	return Initialize(hwnd, width, height, vBC);
//}
//
//bool DXGraphics::Initialize(HWND hwnd, int width, int height, const FLOAT backColor[])
//{
//	if (isInit)
//	{
//		return true;
//	}
//	translationOffset = new float[3]{ 0, 0, 0 };
//	this->mCurrWinWidth = width;
//	this->mCurrWinHeight = height;
//	this->mCurrHwnd = hwnd;
//	float vRedChannel = backColor[0];
//	float vGreenChannel = backColor[1];
//	float vBlueChannel = backColor[2];
//	float vAlphaChannel = backColor[3];
//	mbackColor = new FLOAT[4]{ vRedChannel ,vGreenChannel ,vBlueChannel ,vAlphaChannel };
//	if (!InitializeDirectX())
//	{
//		return false;
//	}
//	if (!InitializeShaders())
//	{
//		return false;
//	}
//	if (!InitializeConstantBuffer())
//	{
//		return false;
//	}
//	if (!InitializeUI())
//	{
//		return false;
//	}
//	if (!InitializeViewPort())
//	{
//		return false;
//	}
//
//	//RenderCommand->SetupD3D(md3d11Device.Get(), md3d11DeviceContext.Get());
//	if (!mCurrRenderList.empty())
//	{
//		for (int i = 0; i < mCurrRenderList.size(); i++)
//		{
//			mCurrRenderList[i]->SetupRender(md3d11Device.Get(), md3d11DeviceContext.Get(), &mCBDraw);
//		}
//	}
//	isInit = true;
//	return true;
//}
//
//
//bool DXGraphics::InitializeDirectX()
//{
//	try
//	{
//		std::vector<AdapterReaderData> adapters = AdapterReader::getAdapters();
//
//		if (adapters.size() < 1)
//		{
//			ErrorLogger::Log("No IDXGI Adapters found.");
//			return false;
//		}
//
//		///////////////////////////////------------SwapChian------------///////////////////////////////////////////
//		DXGI_SWAP_CHAIN_DESC scd = { 0 };
//
//		scd.BufferDesc.Width = this->mCurrWinWidth;
//		scd.BufferDesc.Height = this->mCurrWinHeight;
//		scd.BufferDesc.RefreshRate.Numerator = 60;
//		scd.BufferDesc.RefreshRate.Denominator = 1;
//		scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
//		scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
//		scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
//
//		scd.SampleDesc.Count = 1;
//		scd.SampleDesc.Quality = 0;
//
//		scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
//		scd.BufferCount = 1;
//		scd.OutputWindow = mCurrHwnd;
//		scd.Windowed = TRUE;
//		scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
//		scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
//
//		HRESULT hr;
//		hr = D3D11CreateDeviceAndSwapChain(
//			adapters[0].getAdapter(),				//IDXGI Adapter
//			D3D_DRIVER_TYPE_UNKNOWN,
//			NULL,									//FOR SOFTWARE DRIVER TYPE
//			NULL,									//FLAGS FOR RUNTIME LAYERS
//			NULL,									//FEATURE LEVELS ARRAY
//			0,										//# OF FEATURE LEVELS IN ARRAY
//			D3D11_SDK_VERSION,
//			&scd,									//Swapchain description
//			this->mdxgiSwapChain.GetAddressOf(),	//Swapchain Address
//			this->md3d11Device.GetAddressOf(),		//Device Address
//			NULL,									//Supported feature level
//			this->md3d11DeviceContext.GetAddressOf()//Device Context Address
//		); 
//
//		COM_ERROR_IF_FAILED(hr, "Failed to create device and swapchain.");
//
//		Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
//		hr = this->mdxgiSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backBuffer.GetAddressOf()));
//		COM_ERROR_IF_FAILED(hr, "GetBuffer Failed.");
//
//
//
//		///////////////////////////////------------CreateRenderTargetView------------///////////////////////////////////////////
//		hr = this->md3d11Device->CreateRenderTargetView(backBuffer.Get(), NULL, this->md3d11RenderTargetView.GetAddressOf());
//		COM_ERROR_IF_FAILED(hr, "Failed to create render target view.");
//
//
//
//
//		///////////////////////////////------------Depth/Stencil Buffer------------///////////////////////////////////////////
//		CD3D11_TEXTURE2D_DESC depthStencilTextureDesc(DXGI_FORMAT_D24_UNORM_S8_UINT, this->mCurrWinWidth, this->mCurrWinHeight);
//		depthStencilTextureDesc.MipLevels = 1;
//		depthStencilTextureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
//
//		hr = this->md3d11Device->CreateTexture2D(&depthStencilTextureDesc, NULL, this->mDepthStencilBuffer.GetAddressOf());
//		COM_ERROR_IF_FAILED(hr, "Failed to create depth stencil buffer.");
//
//		hr = this->md3d11Device->CreateDepthStencilView(this->mDepthStencilBuffer.Get(), NULL, this->mDepthStencilView.GetAddressOf());
//		COM_ERROR_IF_FAILED(hr, "Failed to create depth stencil view.");
//
//
//
//		///////////////////////////////------------OMSetRenderTargets------------///////////////////////////////////////////
//		this->md3d11DeviceContext->OMSetRenderTargets(1, this->md3d11RenderTargetView.GetAddressOf(), this->mDepthStencilView.Get());
//
//
//
//		///////////////////////////////------------Create Rasterizer State------------///////////////////////////////////////////
//
//		CD3D11_RASTERIZER_DESC rasterizerDesc(D3D11_DEFAULT);
//		hr = this->md3d11Device->CreateRasterizerState(&rasterizerDesc, this->mRasterizerState.GetAddressOf());
//		COM_ERROR_IF_FAILED(hr, "Failed to create rasterizer state.");
//
//		CD3D11_RASTERIZER_DESC rasterizerDesc_CullFront(D3D11_DEFAULT);
//		rasterizerDesc_CullFront.CullMode = D3D11_CULL_MODE::D3D11_CULL_FRONT;
//		hr = this->md3d11Device->CreateRasterizerState(&rasterizerDesc_CullFront, this->mRasterizerState_CullFront.GetAddressOf());
//		COM_ERROR_IF_FAILED(hr, "Failed to create rasterizer state.");
//
//
//
//
//		///////////////////////////////------------Create depth stencil state------------///////////////////////////////////////////
//		CD3D11_DEPTH_STENCIL_DESC depthstencildesc(D3D11_DEFAULT);
//		depthstencildesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;
//
//		hr = this->md3d11Device->CreateDepthStencilState(&depthstencildesc, this->mDdepthStencilState.GetAddressOf());
//		COM_ERROR_IF_FAILED(hr, "Failed to create depth stencil state.");
//
//
//
//
//
//		///////////////////////////////------------Create Blend State------------///////////////////////////////////////////
//		D3D11_RENDER_TARGET_BLEND_DESC rtbd = { 0 };
//		rtbd.BlendEnable = true;
//		rtbd.SrcBlend = D3D11_BLEND::D3D11_BLEND_SRC_ALPHA;
//		rtbd.DestBlend = D3D11_BLEND::D3D11_BLEND_INV_SRC_ALPHA;
//		rtbd.BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
//		rtbd.SrcBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;
//		rtbd.DestBlendAlpha = D3D11_BLEND::D3D11_BLEND_ZERO;
//		rtbd.BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
//		rtbd.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE::D3D11_COLOR_WRITE_ENABLE_ALL;
//
//		D3D11_BLEND_DESC blendDesc = { 0 };
//		blendDesc.RenderTarget[0] = rtbd;
//
//		hr = this->md3d11Device->CreateBlendState(&blendDesc, this->mBlendState.GetAddressOf());
//		COM_ERROR_IF_FAILED(hr, "Failed to create blend state.");
//
//		spriteBatch = std::make_unique<DirectX::SpriteBatch>(this->md3d11DeviceContext.Get());
//		spriteFont = std::make_unique<DirectX::SpriteFont>(this->md3d11Device.Get(), L"Data\\Fonts\\comic_sans_ms_16.spritefont");
//
//
//
//		///////////////////////////////------------Create & set the Viewport------------///////////////////////////////////////////
//		CD3D11_VIEWPORT viewport(0.0f, 0.0f, static_cast<float>(this->mCurrWinWidth), static_cast<float>(this->mCurrWinHeight));;
//		this->md3d11DeviceContext->RSSetViewports(1, &viewport);
//
//
//
//		///////////////////////////////------------Create sampler description for sampler state------------///////////////////////////////////////////
//		CD3D11_SAMPLER_DESC sampDesc(D3D11_DEFAULT);
//		sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
//		sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
//		sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
//		hr = this->md3d11Device->CreateSamplerState(&sampDesc, this->samplerState.GetAddressOf()); //Create sampler state
//		COM_ERROR_IF_FAILED(hr, "Failed to create sampler state.");
//	}
//	catch (COMException & exception)
//	{
//		ErrorLogger::Log(exception);
//		return false;
//	}
//	return true;
//}
//
//bool DXGraphics::InitializeConstantBuffer()
//{
//	mCBDraw.Initialize(md3d11Device.Get(), md3d11DeviceContext.Get());
//	mCBDraw.BindVSConstant(0);
//	mCBDraw.BindPSConstant(0);
//
//	mCBStates.Initialize(md3d11Device.Get(), md3d11DeviceContext.Get());
//	mCBStates.BindVSConstant(1);
//	mCBStates.BindPSConstant(1);
//
//	mCBFrame.Initialize(md3d11Device.Get(), md3d11DeviceContext.Get());
//	mCBFrame.BindVSConstant(2);
//	mCBFrame.BindPSConstant(2);
//
//	mCBOnResize.Initialize(md3d11Device.Get(), md3d11DeviceContext.Get());
//	mCBOnResize.BindVSConstant(3);
//	//mCBOnResize.BindPSConstant(3);
//
//	mCBRarely.Initialize(md3d11Device.Get(), md3d11DeviceContext.Get());
//	mCBRarely.BindVSConstant(4);
//	mCBRarely.BindPSConstant(4);
//	return true;
//}
//
//
//bool DXGraphics::InitializeShaders()
//{
//	std::wstring shaderfolder = L"";
//#pragma region DetermineShaderPath
//	if (IsDebuggerPresent() == TRUE)
//	{
//#ifdef _DEBUG //Debug Mode
//#ifdef _WIN64 //x64
//		shaderfolder = L"..\\x64\\Debug\\Shaders\\";
//#else  //x86 (Win32)
//		shaderfolder = L"..\\Debug\\Shaders\\";
//#endif
//#else //Release Mode
//#ifdef _WIN64 //x64
//		shaderfolder = L"..\\x64\\Release\\Shaders\\";
//#else  //x86 (Win32)
//		shaderfolder = L"..\\Release\\Shaders\\";
//#endif
//#endif
//	}
//
//	//D3D11_INPUT_ELEMENT_DESC element_desc[] =
//	//{
//	//	{"POSITION",	0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT,		0,		0,								D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA,	0  },
//	//	{"TEXCOORD",	0, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT,			0,		D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0  },
//	//};
//	//UINT elementsNumber = ARRAYSIZE(element_desc);
//	if (!mVertexShader.Initialize(md3d11Device, shaderfolder + L"Basic_VS_3D.cso", 
//		const_cast<D3D11_INPUT_ELEMENT_DESC*>(VertexPosNormalTex::inputLayout), ARRAYSIZE(VertexPosNormalTex::inputLayout)))
//	{
//		return false;
//	}
//	if (!mPixelShader.Initialize(md3d11Device, shaderfolder + L"Basic_PS_3D.cso"))
//	{
//		return false;
//	}
//
//	//HRESULT hr;
//	//hr = this->mVS_ConstantBuffer.Initialize(this->md3d11Device.Get(), this->md3d11DeviceContext.Get());
//	//COM_ERROR_IF_FAILED(hr, "Faiure Initialize VSConstantBuffer");
//	//hr = this->mPS_ConstantBuffer.Initialize(this->md3d11Device.Get(), this->md3d11DeviceContext.Get());
//	//COM_ERROR_IF_FAILED(hr, "Faiure Initialize PSConstantBuffer");
//
//	return true;
//}
//
//bool DXGraphics::InitializeUI()
//{
//	//Setup ImGui
//	return true;
//}
//
//bool DXGraphics::InitializeViewPort()
//{
//	{
//	
//		/*pos.y += 3;*/
//		mCamera.SetPosition(0.0f, 0.0f, -2.0f);
//		mCamera.SetLookAtPos(XMFLOAT3(0.0, 0.0, 1.0f));
//		mCamera.SetProjectionValues(90.0f, AspectRatio(), 0.1f, 1000.0f);
//
//		mCBOnResize.data.proj = XMMatrixTranspose(mCamera.GetProjectionMatrix());
//		if (mCBOnResize.ApplyChanges())
//		{
//			mCBOnResize.RefreshBind();
//		}
//
//		XMStoreFloat4(&mCBFrame.data.eyePos, mCamera.GetPositionVector());
//		mCBFrame.data.view = XMMatrixTranspose(mCamera.GetViewMatrix());
//		if (mCBFrame.ApplyChanges())
//		{
//			mCBFrame.RefreshBind();
//		}
//		UpdateConstant();
//	}
//	return true;
//}
//
//float DXGraphics::AspectRatio()const
//{
//	return static_cast<float>(this->mCurrWinWidth) / static_cast<float>(mCurrWinHeight);
//}
//
//bool DXGraphics::InitEveri()
//{
//	XMStoreFloat4x4(
//		&mCBRarely.data.reflection, 
//		XMMatrixTranspose(XMMatrixReflect(XMVectorSet(0.0f, 0.0f, -1.0f, 10.0f)))
//	);
//	// 环境光
//	mCBRarely.data.dirLight[0].Ambient = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
//	mCBRarely.data.dirLight[0].Diffuse = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
//	mCBRarely.data.dirLight[0].Specular = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
//	mCBRarely.data.dirLight[0].Direction = XMFLOAT3(0.0f, -1.0f, 0.0f);
//	// 灯光
//	mCBRarely.data.pointLight[0].Position = XMFLOAT3(0.0f, 15.0f, 0.0f);
//	mCBRarely.data.pointLight[0].Ambient = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
//	mCBRarely.data.pointLight[0].Diffuse = XMFLOAT4(0.6f, 0.6f, 0.6f, 1.0f);
//	mCBRarely.data.pointLight[0].Specular = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
//	mCBRarely.data.pointLight[0].Att = XMFLOAT3(0.0f, 0.1f, 0.0f);
//	mCBRarely.data.pointLight[0].Range = 25.0f;
//	mCBRarely.data.numDirLight = 1;
//	mCBRarely.data.numPointLight = 1;
//	mCBRarely.data.numSpotLight = 0;
//	if (mCBRarely.ApplyChanges())
//	{
//		mCBFrame.RefreshBind();
//	}
//	return true;
//}
//
//
//
//void DXGraphics::RenderFrame(float dt)
//{
//	float bgcolor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
//	this->md3d11DeviceContext->ClearRenderTargetView(this->md3d11RenderTargetView.Get(), bgcolor);
//	this->md3d11DeviceContext->ClearDepthStencilView(this->mDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
//
//	this->md3d11DeviceContext->IASetInputLayout(this->mVertexShader.GetInputLayout());
//	this->md3d11DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
//	this->md3d11DeviceContext->RSSetState(this->mRasterizerState.Get());
//	this->md3d11DeviceContext->OMSetDepthStencilState(this->mDdepthStencilState.Get(), 0);
//	this->md3d11DeviceContext->OMSetBlendState(this->mBlendState.Get(), NULL, 0xFFFFFFFF);
//	this->md3d11DeviceContext->PSSetSamplers(0, 1, this->samplerState.GetAddressOf());
//	this->md3d11DeviceContext->VSSetShader(mVertexShader.GetShader(), NULL, 0);
//	this->md3d11DeviceContext->PSSetShader(mPixelShader.GetShader(), NULL, 0);
//	{
//		if (!mCurrRenderList.empty())
//		{
//			for (int i =0; i< mCurrRenderList.size(); i++)
//			{
////				mCurrRenderList[i].SetupRender(md3d11Device.Get(), md3d11DeviceContext.Get(), mVS_ConstantBuffer, mPS_ConstantBuffer);
//				mCurrRenderList[i]->Draw(mCamera.GetViewMatrix() * mCamera.GetProjectionMatrix());
//			}	
//		}
//	}
//	//Begin UI Render Will Handle the RT
//	this->HandleRenderRT();
//	//RenderUI
//	this->RenderFrameUI();
//	this->mdxgiSwapChain->Present(0, NULL);
//}
//
//
//void DXGraphics::RenderFrameUI()
//{
//	////Draw Text
//	//spriteBatch->Begin();
//	//spriteFont->DrawString(spriteBatch.get(), L"This DZEngine Base", DirectX::XMFLOAT2(0, 0), DirectX::Colors::White, 0.0f, DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::XMFLOAT2(1.0f, 1.0f));
//	//spriteBatch->End();
//
//	////Draw FPS
//	//std::string fpsString = "FPS: " + std::to_string(Engine::GetCurrFPS());
//	//spriteBatch->Begin();
//	//spriteFont->DrawString(spriteBatch.get(), StringConverter::StringToWide(fpsString).c_str(), DirectX::XMFLOAT2(200, 0), DirectX::Colors::White, 0.0f, DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::XMFLOAT2(1.0f, 1.0f));
//	//spriteBatch->End();
//
//	static int counter = 0;
//}
//
//void DXGraphics::HandleRenderRT()
//{
//	mRTMan.DriverDrawRT(this->md3d11Device.Get(),this->md3d11DeviceContext.Get());
//}
//
//void DXGraphics::SetupPrimitiveSceneProxy(PrimitiveSceneProxy* pProxy)
//{
//	mCurrRenderList.push_back(pProxy);
//}
//
//void DXGraphics::updateFrame(float dt)
//{
//	UpdateConstant();
//}
//
//
//void DXGraphics::UpdateConstant()
//{
//	XMStoreFloat4(&mCBFrame.data.eyePos, mCamera.GetPositionVector());
//	mCBFrame.data.view = XMMatrixTranspose(mCamera.GetViewMatrix());
//	if (mCBFrame.ApplyChanges())
//	{
//		mCBFrame.RefreshBind();
//	}
//}
//
//
