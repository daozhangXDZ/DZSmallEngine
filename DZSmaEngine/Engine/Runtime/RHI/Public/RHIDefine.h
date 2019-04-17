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