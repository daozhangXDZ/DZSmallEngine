#pragma once
enum EShaderFrequency
{
	SF_Vertex = 0,
	SF_Hull = 1,
	SF_Domain = 2,
	SF_Pixel = 3,
	SF_Geometry = 4,
	SF_Compute = 5,

	SF_NumFrequencies = 6,

	SF_NumBits = 3,
};


/** @warning: update *LegacyShaderPlatform* when the below changes */
enum EShaderPlatform
{
	SP_PCD3D_SM5 = 0,
	SP_OPENGL_SM4 = 1,
	SP_PS4 = 2,
	/** Used when running in Feature Level ES2 in OpenGL. */
	SP_OPENGL_PCES2 = 3,
	SP_XBOXONE_D3D12 = 4,
	SP_PCD3D_SM4 = 5,
	SP_OPENGL_SM5 = 6,
	/** Used when running in Feature Level ES2 in D3D11. */
	SP_PCD3D_ES2 = 7,
	SP_OPENGL_ES2_ANDROID = 8,
	SP_OPENGL_ES2_WEBGL = 9,
	SP_OPENGL_ES2_IOS = 10,
	SP_METAL = 11,
	SP_METAL_MRT = 12,
	SP_OPENGL_ES31_EXT = 13,
	/** Used when running in Feature Level ES3_1 in D3D11. */
	SP_PCD3D_ES3_1 = 14,
	/** Used when running in Feature Level ES3_1 in OpenGL. */
	SP_OPENGL_PCES3_1 = 15,
	SP_METAL_SM5 = 16,
	SP_VULKAN_PCES3_1 = 17,
	SP_METAL_SM4 = 18,
	SP_VULKAN_SM4 = 19,
	SP_VULKAN_SM5 = 20,
	SP_VULKAN_ES3_1_ANDROID = 21,
	SP_METAL_MACES3_1 = 22,
	SP_METAL_MACES2 = 23,
	SP_OPENGL_ES3_1_ANDROID = 24,
	SP_SWITCH = 25,
	SP_SWITCH_FORWARD = 26,
	SP_METAL_MRT_MAC = 27,

	SP_NumPlatforms = 28,
	SP_NumBits = 5,
};

enum ETextureSrcFormat
{
	PNG = 0,
	DDS = 1,
};


/**
 * 一些RHI层的纹理创建标致
 * 支持按位或和按位与，方便选择多个Flag
 */
enum ETextureCreateFlags
{
	TexCreate_None = 0,
	// 可以作为渲染目标
	TexCreate_RenderTargetable = 1 << 0,
	// 可以作为覆盖
	TexCreate_ResolveTargetable = 1 << 1,
	// 可以作为深度模板目标
	TexCreate_DepthStencilTargetable = 1 << 2,
	// 作为Shader的采样资源
	TexCreate_ShaderResource = 1 << 3,

	// Texture is encoded in sRGB gamma space
	TexCreate_SRGB = 1 << 4,
	// Texture will be created without a packed miptail
	TexCreate_NoMipTail = 1 << 5,
	// Texture will be created with an un-tiled format
	TexCreate_NoTiling = 1 << 6,
	// Texture that may be updated every frame
	TexCreate_Dynamic = 1 << 8,
	// Allow silent texture creation failure
	TexCreate_AllowFailure = 1 << 9,
	// Disable automatic defragmentation if the initial texture memory allocation fails.
	TexCreate_DisableAutoDefrag = 1 << 10,
	// Create the texture with automatic -1..1 biasing
	TexCreate_BiasNormalMap = 1 << 11,
	// Create the texture with the flag that allows mip generation later, only applicable to D3D11
	TexCreate_GenerateMipCapable = 1 << 12,
	// UnorderedAccessView (DX11 only)
	// Warning: Causes additional synchronization between draw calls when using a render target allocated with this flag, use sparingly
	// See: GCNPerformanceTweets.pdf Tip 37
	TexCreate_UAV = 1 << 16,
	// Render target texture that will be displayed on screen (back buffer)
	TexCreate_Presentable = 1 << 17,
	// Texture data is accessible by the CPU
	TexCreate_CPUReadback = 1 << 18,
	// Texture was processed offline (via a texture conversion process for the current platform)
	TexCreate_OfflineProcessed = 1 << 19,
	// Texture needs to go in fast VRAM if available (HINT only)
	TexCreate_FastVRAM = 1 << 20,
	// by default the texture is not showing up in the list - this is to reduce clutter, using the FULL option this can be ignored
	TexCreate_HideInVisualizeTexture = 1 << 21,
	// Texture should be created in virtual memory, with no physical memory allocation made
	// You must make further calls to RHIVirtualTextureSetFirstMipInMemory to allocate physical memory
	// and RHIVirtualTextureSetFirstMipVisible to map the first mip visible to the GPU
	TexCreate_Virtual = 1 << 22,
	// Creates a RenderTargetView for each array slice of the texture
	// Warning: if this was specified when the resource was created, you can't use SV_RenderTargetArrayIndex to route to other slices!
	TexCreate_TargetArraySlicesIndependently = 1 << 23,
	// Texture that may be shared with DX9 or other devices
	TexCreate_Shared = 1 << 24,
	// RenderTarget will not use full-texture fast clear functionality.
	TexCreate_NoFastClear = 1 << 25,
	// Texture is a depth stencil resolve target
	TexCreate_DepthStencilResolveTarget = 1 << 26,
	// Flag used to indicted this texture is a streamable 2D texture, and should be counted towards the texture streaming pool budget.
	TexCreate_Streamable = 1 << 27,
	// Render target will not FinalizeFastClear; Caches and meta data will be flushed, but clearing will be skipped (avoids potentially trashing metadata)
	TexCreate_NoFastClearFinalize = 1 << 28,
	// Hint to the driver that this resource is managed properly by the engine for Alternate-Frame-Rendering in mGPU usage.
	TexCreate_AFRManual = 1 << 29,
	// Workaround for 128^3 volume textures getting bloated 4x due to tiling mode on PS4
	TexCreate_ReduceMemoryWithTilingMode = 1 << 30,
	/** Texture should be allocated from transient memory. */
	TexCreate_Transient = 1 << 31
};



/**
 * 绘制方式
 */
enum PrimitiveTopology
{
	TRIANGLELIST = 0,
};


struct FPixelFormatInfo
{
	const TCHAR*	Name;
	int32				BlockSizeX,
		BlockSizeY,
		BlockSizeZ,
		BlockBytes,
		NumComponents;
	/** Platform specific token, e.g. D3DFORMAT with D3DDrv										*/
	uint32			PlatformFormat;
	/** Whether the texture format is supported on the current platform/ rendering combination	*/
	bool			Supported;
	EPixelFormat	UnrealFormat;
};

extern FPixelFormatInfo GPixelFormats[PF_MAX];