// dllmain.cpp : Defines the entry point for the DLL application.
#include "include/platform.h"

namespace {
    std::ofstream g_log{};
    template<class ...Args>
    void log(std::string_view format, Args && ...args)
    {
        g_log << std::vformat(format, std::make_format_args(args...)) << "\n";
        g_log.flush();
    }
}

FX_ENTRY BOOL FX_CALL DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        g_log = std::ofstream{ "glide3x.log", std::ios::app };
        log("##### logging started #####");
    }
    // DLL_PROCESS_DETACH should probably destroy the log but whatever
    return TRUE;
}

FX_ENTRY void FX_CALL grDrawPoint(const void* pt)
{
    log("grDrawPoint");
}

FX_ENTRY void FX_CALL grDrawLine(const void* v1, const void* v2)
{
    log("grDrawLine");
}

FX_ENTRY void FX_CALL grDrawTriangle(const void* a, const void* b, const void* c)
{
    log("grDrawTriangle");
}

FX_ENTRY void FX_CALL grVertexLayout(FxU32 param, FxI32 offset, FxU32 mode)
{
    log("grVertexLayout");
}

FX_ENTRY void FX_CALL grDrawVertexArray(FxU32 mode, FxU32 Count, void* pointers)
{
    log("grDrawVertexArray");
}

FX_ENTRY void FX_CALL grDrawVertexArrayContiguous(FxU32 mode, FxU32 Count, void* pointers, FxU32 stride)
{
    log("grDrawVertexArrayContiguous");
}

FX_ENTRY void FX_CALL grAADrawTriangle(const void* a, const void* b, const void* c, FxBool ab_antialias, FxBool bc_antialias, FxBool ca_antialias)
{
    log("grAADrawTriangle");
}

FX_ENTRY void FX_CALL grBufferClear(GrColor_t color, GrAlpha_t alpha, FxU32 depth)
{
    log("grBufferClear");
}

FX_ENTRY void FX_CALL grBufferSwap(FxU32 swap_interval)
{
    log("grBufferSwap");
}

FX_ENTRY void FX_CALL grRenderBuffer(GrBuffer_t buffer)
{
    log("grRenderBuffer");
}

typedef void (*GrErrorCallbackFnc_t)(const char* string, FxBool fatal);

FX_ENTRY void FX_CALL grErrorSetCallback(GrErrorCallbackFnc_t fnc)
{
    log("grErrorSetCallback");
}

FX_ENTRY void FX_CALL grFinish(void)
{
    log("grFinish");
}

FX_ENTRY void FX_CALL grFlush(void)
{
    log("grFlush");
}

FX_ENTRY GrContext_t FX_CALL grSstWinOpen(FxU32 hWnd, GrScreenResolution_t screen_resolution, GrScreenRefresh_t refresh_rate, GrColorFormat_t color_format, GrOriginLocation_t origin_location, int nColBuffers, int nAuxBuffers)
{
    log("grSstWinOpen hwnd: {}, res: {}, rf: {}, cf: {}, org: {}, ncol: {}, naux: {}", hWnd, screen_resolution, refresh_rate, color_format, origin_location, nColBuffers, nAuxBuffers);
    return GrContext_t{ 1 }; /* so we dont crash the app */
}

FX_ENTRY FxBool FX_CALL grSstWinClose(GrContext_t context)
{
    log("grSstWinClose");
    return FXTRUE;
}

FX_ENTRY void FX_CALL grSetNumPendingBuffers(FxI32 NumPendingBuffers)
{
    log("grSetNumPendingBuffers");
}

FX_ENTRY FxBool FX_CALL grSelectContext(GrContext_t context)
{
    log("grSelectContext");
    return {};
}

FX_ENTRY void FX_CALL grSstOrigin(GrOriginLocation_t  origin)
{
    log("grSstOrigin");
}

FX_ENTRY void FX_CALL grSstSelect(int which_sst)
{
    log("grSstSelect");
}

FX_ENTRY void FX_CALL grAlphaBlendFunction(GrAlphaBlendFnc_t rgb_sf, GrAlphaBlendFnc_t rgb_df, GrAlphaBlendFnc_t alpha_sf, GrAlphaBlendFnc_t alpha_df)
{
    log("grAlphaBlendFunction");
}

FX_ENTRY void FX_CALL grAlphaCombine(GrCombineFunction_t function, GrCombineFactor_t factor, GrCombineLocal_t local, GrCombineOther_t other, FxBool invert)
{
    log("grAlphaCombine");
}

FX_ENTRY void FX_CALL grAlphaControlsITRGBLighting(FxBool enable)
{
    log("grAlphaControlsITRGBLighting");
}

FX_ENTRY void FX_CALL grAlphaTestFunction(GrCmpFnc_t function)
{
    log("grAlphaTestFunction");
}

FX_ENTRY void FX_CALL grAlphaTestReferenceValue(GrAlpha_t value)
{
    log("grAlphaTestReferenceValue");
}

FX_ENTRY void FX_CALL grChromakeyMode(GrChromakeyMode_t mode)
{
    log("grChromakeyMode");
}

FX_ENTRY void FX_CALL grChromakeyValue(GrColor_t value)
{
    log("grChromakeyValue");
}

FX_ENTRY void FX_CALL grClipWindow(FxU32 minx, FxU32 miny, FxU32 maxx, FxU32 maxy)
{
    log("grClipWindow");
}

FX_ENTRY void FX_CALL grColorCombine(GrCombineFunction_t function, GrCombineFactor_t factor, GrCombineLocal_t local, GrCombineOther_t other, FxBool invert)
{
    log("grColorCombine");
}

FX_ENTRY void FX_CALL grColorMask(FxBool rgb, FxBool a)
{
    log("grColorMask");
}

FX_ENTRY void FX_CALL grCullMode(GrCullMode_t mode)
{
    log("grCullMode");
}

FX_ENTRY void FX_CALL grConstantColorValue(GrColor_t value)
{
    log("grConstantColorValue");
}

FX_ENTRY void FX_CALL grDepthBiasLevel(FxI32 level)
{
    log("grDepthBiasLevel");
}

FX_ENTRY void FX_CALL grDepthBufferFunction(GrCmpFnc_t function)
{
    log("grDepthBufferFunction");
}

FX_ENTRY void FX_CALL grDepthBufferMode(GrDepthBufferMode_t mode)
{
    log("grDepthBufferMode");
}

FX_ENTRY void FX_CALL grDepthMask(FxBool mask)
{
    log("grDepthMask");
}

FX_ENTRY void FX_CALL grDisableAllEffects(void)
{
    log("grDisableAllEffects");
}

FX_ENTRY void FX_CALL grDitherMode(GrDitherMode_t mode)
{
    log("grDitherMode");
}

FX_ENTRY void FX_CALL grFogColorValue(GrColor_t fogcolor)
{
    log("grFogColorValue");
}

FX_ENTRY void FX_CALL grFogMode(GrFogMode_t mode)
{
    log("grFogMode");
}

FX_ENTRY void FX_CALL grFogTable(const GrFog_t ft[])
{
    log("grFogTable");
}

FX_ENTRY void FX_CALL grLoadGammaTable(FxU32 nentries, FxU32* red, FxU32* green, FxU32* blue)
{
    //MessageBox(0, TEXT("grLoadGammaTable"), TEXT("grGet"), MB_OK);

    log("grLoadGammaTable");
}

FX_ENTRY void FX_CALL grSplash(float x, float y, float width, float height, FxU32 frame)
{
    log("grSplash");
}

FX_ENTRY FxU32 FX_CALL grGet(FxU32 pname, FxU32 plength, FxI32* params)
{
    log("grGet {:x} {} {}", pname, plength, static_cast<void*>(params));
    *params = plength;

    //MessageBox(0, TEXT("grGet"), TEXT("grGet"), MB_OK);
    switch (pname) {
    case GR_NUM_BOARDS: {
        //*params = plength;
        return plength;
    }
    case GR_GAMMA_TABLE_ENTRIES: {
        return 32;
    }
    case GR_BITS_GAMMA: {
        return 8;
    }
    case GR_MAX_TEXTURE_SIZE: {
        return 256;
    }
    case GR_MAX_TEXTURE_ASPECT_RATIO: {
        return 3;
    }
    case GR_NUM_FB: {
        return 2;
    }
    case GR_NUM_TMU: {
        return 1;
    }
    case GR_TEXTURE_ALIGN: {
        return 8;
    }
    case GR_MEMORY_UMA: {
        return 1;
    }
    default: { break; }
    }

    return {};
}

FX_ENTRY const char* FX_CALL grGetString(FxU32 pname)
{
    log("grGetString");
    return {};
}

FX_ENTRY FxI32 FX_CALL grQueryResolutions(const GrResolution* resTemplate, GrResolution* output)
{
    log("grQueryResolutions");
    return {};
}

FX_ENTRY FxBool FX_CALL grReset(FxU32 what)
{
    log("grReset");
    return {};
}

FX_ENTRY GrProc FX_CALL grGetProcAddress(char* procName)
{
    log("grGetProcAddress");
    return {};
}

FX_ENTRY void FX_CALL grEnable(GrEnableMode_t mode)
{
    log("grEnable");
}

FX_ENTRY void FX_CALL grDisable(GrEnableMode_t mode)
{
    log("grDisable");
}

FX_ENTRY void FX_CALL grCoordinateSpace(GrCoordinateSpaceMode_t mode)
{
    log("grCoordinateSpace");
}

FX_ENTRY void FX_CALL grDepthRange(FxFloat n, FxFloat f)
{
    log("grDepthRange");
}

FX_ENTRY void FX_CALL grStippleMode(GrStippleMode_t mode)
{
    log("grStippleMode");
}

FX_ENTRY void FX_CALL grStipplePattern(GrStipplePattern_t mode)
{
    log("grStipplePattern");
}

FX_ENTRY void FX_CALL grViewport(FxI32 x, FxI32 y, FxI32 width, FxI32 height)
{
    log("grViewport");
}

FX_ENTRY FxU32 FX_CALL grTexCalcMemRequired(GrLOD_t lodmin, GrLOD_t lodmax, GrAspectRatio_t aspect, GrTextureFormat_t fmt)
{
    log("grTexCalcMemRequired");
    return {};
}

FX_ENTRY FxU32 FX_CALL grTexTextureMemRequired(FxU32 evenOdd, GrTexInfo* info)
{
    log("grTexTextureMemRequired");
    return {};
}

FX_ENTRY FxU32 FX_CALL grTexMinAddress(GrChipID_t tmu)
{
    log("grTexMinAddress {}", tmu);
    return {};
}

FX_ENTRY FxU32 FX_CALL grTexMaxAddress(GrChipID_t tmu)
{
    log("grTexMaxAddress {}", tmu);
    return std::numeric_limits<FxU32>::max();
}

FX_ENTRY void FX_CALL grTexNCCTable(GrNCCTable_t table)
{
    log("grTexNCCTable");
}

FX_ENTRY void FX_CALL grTexSource(GrChipID_t tmu, FxU32 startAddress, FxU32 evenOdd, GrTexInfo* info)
{
    log("grTexSource");
}

FX_ENTRY void FX_CALL grTexClampMode(GrChipID_t tmu, GrTextureClampMode_t s_clampmode, GrTextureClampMode_t t_clampmode)
{
    log("grTexClampMode");
}

FX_ENTRY void FX_CALL grTexCombine(GrChipID_t tmu, GrCombineFunction_t rgb_function, GrCombineFactor_t rgb_factor, GrCombineFunction_t alpha_function, GrCombineFactor_t alpha_factor, FxBool rgb_invert, FxBool alpha_invert)
{
    log("grTexCombine");
}

FX_ENTRY void FX_CALL grTexDetailControl(GrChipID_t tmu, int lod_bias, FxU8 detail_scale, float detail_max)
{
    log("grTexDetailControl");
}

FX_ENTRY void FX_CALL grTexFilterMode(GrChipID_t tmu, GrTextureFilterMode_t minfilter_mode, GrTextureFilterMode_t magfilter_mode)
{
    log("grTexFilterMode");
}

FX_ENTRY void FX_CALL grTexLodBiasValue(GrChipID_t tmu, float bias)
{
    log("grTexLodBiasValue");
}

FX_ENTRY void FX_CALL grTexDownloadMipMap(GrChipID_t tmu, FxU32 startAddress, FxU32 evenOdd, GrTexInfo* info)
{
    log("grTexDownloadMipMap tmu: {}, sa: {}, eo: {}, inf: {}", tmu, startAddress, evenOdd, static_cast<void*>(info));
}

FX_ENTRY void FX_CALL grTexDownloadMipMapLevel(GrChipID_t tmu, FxU32 startAddress, GrLOD_t thisLod, GrLOD_t largeLod, GrAspectRatio_t aspectRatio, GrTextureFormat_t format, FxU32 evenOdd, void* data)
{
    log("grTexDownloadMipMapLevel");
}

FX_ENTRY FxBool FX_CALL grTexDownloadMipMapLevelPartial(GrChipID_t tmu, FxU32 startAddress, GrLOD_t thisLod, GrLOD_t largeLod, GrAspectRatio_t aspectRatio, GrTextureFormat_t format, FxU32 evenOdd, void* data, int start, int end)
{
    log("grTexDownloadMipMapLevelPartial");
    return {};
}

FX_ENTRY void FX_CALL grTexDownloadTable(GrTexTable_t type, void* data)
{
    log("grTexDownloadTable");
}

FX_ENTRY void FX_CALL grTexDownloadTablePartial(GrTexTable_t type, void* data, int start, int end)
{
    log("grTexDownloadTablePartial");
}

FX_ENTRY void FX_CALL grTexMipMapMode(GrChipID_t tmu, GrMipMapMode_t mode, FxBool lodBlend)
{
    log("grTexMipMapMode");
}

FX_ENTRY void FX_CALL grTexMultibase(GrChipID_t tmu, FxBool enable)
{
    log("grTexMultibase");
}

FX_ENTRY void FX_CALL grTexMultibaseAddress(GrChipID_t tmu, GrTexBaseRange_t range, FxU32 startAddress, FxU32 evenOdd, GrTexInfo* info)
{
    log("grTexMultibaseAddress");
}

FX_ENTRY FxBool FX_CALL grLfbLock(GrLock_t type, GrBuffer_t buffer, GrLfbWriteMode_t writeMode, GrOriginLocation_t origin, FxBool pixelPipeline, GrLfbInfo_t* info)
{
    log("grLfbLock");
    return {};
}

FX_ENTRY FxBool FX_CALL grLfbUnlock(GrLock_t type, GrBuffer_t buffer)
{
    log("grLfbUnlock");
    return {};
}

FX_ENTRY void FX_CALL grLfbConstantAlpha(GrAlpha_t alpha)
{
    log("grLfbConstantAlpha");
}

FX_ENTRY void FX_CALL grLfbConstantDepth(FxU32 depth)
{
    log("grLfbConstantDepth");
}

FX_ENTRY void FX_CALL grLfbWriteColorSwizzle(FxBool swizzleBytes, FxBool swapWords)
{
    log("grLfbWriteColorSwizzle");
}

FX_ENTRY void FX_CALL grLfbWriteColorFormat(GrColorFormat_t colorFormat)
{
    log("grLfbWriteColorFormat");
}

FX_ENTRY FxBool FX_CALL grLfbWriteRegion(GrBuffer_t dst_buffer, FxU32 dst_x, FxU32 dst_y, GrLfbSrcFmt_t src_format, FxU32 src_width, FxU32 src_height, FxBool pixelPipeline, FxI32 src_stride, void* src_data)
{
    log("grLfbWriteRegion");
    return {};
}

FX_ENTRY FxBool FX_CALL grLfbReadRegion(GrBuffer_t src_buffer, FxU32 src_x, FxU32 src_y, FxU32 src_width, FxU32 src_height, FxU32 dst_stride, void* dst_data)
{
    log("grLfbReadRegion");
    return {};
}

FX_ENTRY void FX_CALL grGlideInit(void)
{
    log("grGlideInit");
}

FX_ENTRY void FX_CALL grGlideShutdown(void)
{
    log("grGlideShutdown");
}

FX_ENTRY void FX_CALL grGlideGetState(void* state)
{
    log("grGlideGetState");
}

FX_ENTRY void FX_CALL grGlideSetState(const void* state)
{
    log("grGlideSetState");
}

FX_ENTRY void FX_CALL grGlideGetVertexLayout(void* layout)
{
    log("grGlideGetVertexLayout");
}

FX_ENTRY void FX_CALL grGlideSetVertexLayout(const void* layout)
{
    log("grGlideSetVertexLayout");
}

#pragma region "gu*"
FX_ENTRY FxBool FX_CALL gu3dfGetInfo(const char* filename, Gu3dfInfo* info)
{
    log("gu3dfGetInfo");
    return {};
}

FX_ENTRY FxBool FX_CALL gu3dfLoad(const char* filename, Gu3dfInfo* data)
{
    log("gu3dfLoad");
    return {};
}

FX_ENTRY void FX_CALL guGammaCorrectionRGB(FxFloat red, FxFloat green, FxFloat blue)
{
    log("guGammaCorrectionRGB");
}

FX_ENTRY float FX_CALL guFogTableIndexToW(int i)
{
    log("guFogTableIndexToW");
    return {};
}

FX_ENTRY void FX_CALL guFogGenerateExp(GrFog_t* fogtable, float density)
{
    log("guFogGenerateExp");
}

FX_ENTRY void FX_CALL guFogGenerateExp2(GrFog_t* fogtable, float density)
{
    log("guFogGenerateExp2");
}

FX_ENTRY void FX_CALL guFogGenerateLinear(GrFog_t* fogtable, float nearZ, float farZ)
{
    log("guFogGenerateLinear");
}

FX_ENTRY int FX_CALL
guEncodeRLE16(void* dst,
    void* src,
    FxU32 width,
    FxU32 height)
{
    //assert(false && "guEncodeRLE16: Unsupported");
    log("guEncodeRLE16");
    return 0;
}
#pragma endregion
