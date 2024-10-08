#define _CRT_SECURE_NO_WARNINGS
// dllmain.cpp : Defines the entry point for the DLL application.
#include "include/platform.h"
#include <cassert>
#include <cmath>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "include/ThirdParty/stb_image_write.h"

namespace {
    std::ofstream g_log{};
    template<class ...Args>
    void log(std::string_view format, Args && ...args)
    {
        g_log << std::vformat(format, std::make_format_args(args...)) << "\n";
        g_log.flush();
    }
    template<std::integral T>
    T pow2(T value)
    {
        T result{ 1 };
        for (auto i = 0; i < value; i++)
        {
            result *= 2;
        }
        return result;
    }

    // the actual palette var 
    //    static GuTexPalette g_pal{}; 
    
    std::vector<FxU32> g_pal(256u);

#pragma region "HEX DUMP (needs to be internal at some point)"
    void HexDump(const uint8_t* buf, size_t len, std::string& outdata, bool HexOnly = false) {
        //#ifdef _DEBUG
        if (len <= 0) { return; }		//length not provided
        if (buf == nullptr) { return; } //invalid pointer

        constexpr char hex_character[] = "0123456789ABCDEF";

        constexpr int BYTES_PER_LINE = 16;					//16 is standard to most hex dumps
#define SPACE_BETWEEN_BYTES (1)
#define SPACE_AFTER_BYTES	(4)

        constexpr char padding_character = ' ';
        constexpr size_t CHARACTERS_PER_LINE = BYTES_PER_LINE;

        constexpr size_t HEX_BLOCK_SIZE = ((BYTES_PER_LINE * 2) + (BYTES_PER_LINE * SPACE_BETWEEN_BYTES) - SPACE_BETWEEN_BYTES);
        constexpr size_t TOTAL_CHARS_PER_LINE = (BYTES_PER_LINE * 2) + ((BYTES_PER_LINE * SPACE_BETWEEN_BYTES) - SPACE_BETWEEN_BYTES) + SPACE_AFTER_BYTES + CHARACTERS_PER_LINE;

        size_t TOTAL_LINES = len / BYTES_PER_LINE;
        size_t steper = BYTES_PER_LINE;
        for (size_t i = 0; i <= len; i += steper) {
            {
                //Whats our total line size going to be?
                char BufferOutput[TOTAL_CHARS_PER_LINE + 1];
                size_t position = 0;

                size_t current_addr = i;
                size_t current_endl = current_addr + steper;
                for (size_t addr = current_addr; addr < current_endl; addr++) {
                    //build our hex block line
                    if (addr < len) {
                        BufferOutput[position] = hex_character[(buf[addr] >> 4) & 0xf]; position++; //high byte problem
                        BufferOutput[position] = hex_character[(buf[addr] & 0xf) & 0xf]; position++;
                    }
                    else {
                        BufferOutput[position] = padding_character; position++;
                        BufferOutput[position] = padding_character; position++;
                    }

#if (SPACE_BETWEEN_BYTES >= 1)
                    //is it between another byte
                    if (addr < (current_endl - 1)) {
                        for (size_t padd_count = 0; padd_count < SPACE_BETWEEN_BYTES; padd_count++) {
                            BufferOutput[position] = padding_character; position++;
                        }
                    }
#endif

                }

#if (SPACE_AFTER_BYTES >= 1)
                //padding between hex and the string
                for (size_t pad_int = 0; pad_int < SPACE_AFTER_BYTES; pad_int++) {
                    BufferOutput[position] = padding_character; position++;
                }
#endif

                if (!HexOnly) {
                    //the string itself
                    for (size_t str_int = current_addr; str_int < current_endl; str_int++) {
                        if (str_int < len) {
                            BufferOutput[position] = isgraph(buf[str_int]) ? buf[str_int] : buf[str_int] == ' ' ? ' ' : '.'; position++;
                        }
                        else {
                            break;
                        }
                    }
                }

                //final null on the line
                BufferOutput[position] = '\0';

                //Calculate the steper
                if (!((len - i) > BYTES_PER_LINE) && ((len - i) >= 1)) {
                    steper = (len - i);
                }

                outdata += (((i + steper) <= len) ? std::format(" [{:08X}] ", i) : "") + BufferOutput;
                if ((i + steper) < len)
                    outdata += "\n";
            }
        }
#pragma endregion
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

    //MessageBox(0, TEXT("grGet"), TEXT("grGet"), MB_OK);
    switch (pname) {
    case GR_MAX_TEXTURE_SIZE: {
        *params = 256;
        break;
    }
    case GR_MAX_TEXTURE_ASPECT_RATIO: {
        *params = 3;
        break;
    }
    case GR_NUM_BOARDS: {
        *params = 1;
        break;
    }
    case GR_NUM_FB: {
        *params = 1;
        break;
    }
    case GR_NUM_TMU: {
        *params = 1;
        break;
    }
    case GR_TEXTURE_ALIGN: {
        *params = 256;// D2DX_TMU_ADDRESS_ALIGNMENT;
        break;
    }
    case GR_MEMORY_UMA: {
        *params = 0;
        break;
    }
    case GR_GAMMA_TABLE_ENTRIES: {
        *params = 256;
        break;
    }
    case GR_BITS_GAMMA: {
        *params = 8;
        break;
    }
    default: { return 0; }
    }
    return 4;
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

#ifdef DUMP_RAW_IMAGES
#pragma pack(push, 1)  // Ensure no padding
struct BMPHeader {
    uint16_t file_type{ 0x4D42 }; // "BM"
    uint32_t file_size{ 0 };      // Size of the file (will be set later)
    uint16_t reserved1{ 0 };
    uint16_t reserved2{ 0 };
    uint32_t offset_data{ 54 };   // Data offset from start of the file (header size)
};
struct DIBHeader {
    uint32_t dib_header_size{ 40 };   // DIB header size
    int32_t width{ 0 };               // Image width
    int32_t height{ 0 };              // Image height (positive = bottom-to-top)
    uint16_t planes{ 1 };             // Number of color planes
    uint16_t bpp{ 32 };               // Bits per pixel
    uint32_t compression{ 0 };        // No compression
    uint32_t image_size{ 0 };         // Size of raw bitmap data (can be 0 for uncompressed)
    int32_t x_ppm{ 2835 };            // Pixels per meter (X axis)
    int32_t y_ppm{ 2835 };            // Pixels per meter (Y axis)
    uint32_t colors_in_palette{ 0 };  // No palette
    uint32_t important_colors{ 0 };   // All colors are important
};
#pragma pack(pop)
void saveBMP(const std::string& filename, int32_t width, int32_t height, const std::vector<uint8_t>& argb_data) {
    BMPHeader bmp_header;
    DIBHeader dib_header;

    dib_header.width = width;
    dib_header.height = -height;  // Negative so image is stored top-to-bottom

    // BMP row size (must be a multiple of 4 bytes)
    const int row_size = (width * 4);// +3) & ~3;

    dib_header.image_size = row_size * height;
    bmp_header.file_size = sizeof(BMPHeader) + sizeof(DIBHeader) + dib_header.image_size;

    std::ofstream file(filename, std::ios::binary);

    if (!file) {
        //std::cerr << "Error: Could not open file for writing.\n";
        return;
    }

    // Write headers
    file.write(reinterpret_cast<const char*>(&bmp_header), sizeof(bmp_header));
    file.write(reinterpret_cast<const char*>(&dib_header), sizeof(dib_header));

    // Convert ARGB to BMP format (BGRA)
    std::vector<uint8_t> bmp_data(row_size * height);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            size_t argb_index = (y * width + x) * 4;
            size_t bmp_index = (y * row_size + x * 4);

            //bmp_data[bmp_index + 0] = argb_data[argb_index + 2]; // B
            //bmp_data[bmp_index + 1] = argb_data[argb_index + 1]; // G
            //bmp_data[bmp_index + 2] = argb_data[argb_index + 0]; // R
            //bmp_data[bmp_index + 3] = argb_data[argb_index + 3]; // A
            bmp_data[bmp_index + 0] = argb_data[argb_index + 0]; // B
            bmp_data[bmp_index + 1] = argb_data[argb_index + 1]; // G
            bmp_data[bmp_index + 2] = argb_data[argb_index + 2]; // R
            bmp_data[bmp_index + 3] = argb_data[argb_index + 3]; // A
        }
    }

    // Write pixel data
    file.write(reinterpret_cast<const char*>(bmp_data.data()), bmp_data.size());

    file.close();
    if (file) {
        //std::cout << "BMP image saved successfully to " << filename << "\n";
    }
    else {
        //std::cerr << "Error: Could not write to file.\n";
    }
}
#endif

#ifdef DUMP_RAW_IMAGES
uint32_t icount{};
#endif
FX_ENTRY void FX_CALL grTexDownloadMipMap(GrChipID_t tmu, FxU32 startAddress, FxU32 evenOdd, GrTexInfo* info)
{
    log("grTexDownloadMipMap tmu: {}, sa: {}, eo: {}, inf->smlod: {}, inf->lrglod: {}, inf->aspect: {}, inf->fmt: {}, inf->data: {}", tmu, startAddress, evenOdd, info->smallLodLog2, info->largeLodLog2, info->aspectRatioLog2, info->format, info->data);
//    FxU32 width, height;
//    GetWidthHeightFromTexInfo(info, &width, &height);
//    log("grTexDownloadMipMap::GetWidthHeightFromTexInfo inf: {}, w: {}, h: {}", static_cast<void*>(info), width, height);
//    size_t len_data = ((width * 4) * height);
//    if (len_data) {
//        std::vector<uint8_t> rawbuf(len_data);
//        std::copy((uint8_t*)info->data, (uint8_t*)info->data + len_data, rawbuf.begin());
//
//        std::string out{};
//        HexDump(rawbuf.data(), len_data, out);
//        log("TextureImageData: \n{}", out);
//    }
//#ifdef DUMP_RAW_IMAGES
//    // image data
//    std::vector<uint8_t> imgdata(len_data);
//    std::copy((uint8_t*)info->data, (uint8_t*)info->data + len_data, imgdata.begin());
//    std::string dfout = { std::string("screens/") + std::to_string(icount++) + std::string(".bmp") };
//    saveBMP(dfout, width, height, imgdata);
//    // end image data
//#endif

    assert(info->smallLodLog2 == info->largeLodLog2);

    const FxU32 dimension = (1 << info->smallLodLog2);
    FxU32 width{}, height{};
    switch (info->aspectRatioLog2)
    {
        case GR_ASPECT_LOG2_8x1: { width = dimension; height = dimension / 8; break; }
        case GR_ASPECT_LOG2_4x1: { width = dimension; height = dimension / 4; break; }
        case GR_ASPECT_LOG2_2x1: { width = dimension; height = dimension / 2; break; }
        case GR_ASPECT_LOG2_1x1: { width = dimension; height = dimension; break; }
        case GR_ASPECT_LOG2_1x2: { width = dimension / 2; height = dimension; break; }
        case GR_ASPECT_LOG2_1x4: { width = dimension / 4; height = dimension; break; }
        case GR_ASPECT_LOG2_1x8: { width = dimension / 8; height = dimension; break; }
        default: { width = 0; height = 0; break; }
    }

    log("width: {}, height: {}", width, height);
    /* again when dumping this data the image was BGRA = 4 not 3 */
    size_t dim = (width * height);
    size_t data_len = (dim * 3);
    std::vector<std::uint8_t> image_data(data_len);
    const auto* cursor = reinterpret_cast<std::uint8_t*>(info->data);

    // could have swore it was uint24 values but its not ok...
    //std::vector<uint8_t> rawbuf(data_len);
    //std::copy((uint8_t*)info->data, (uint8_t*)info->data + data_len, rawbuf.begin());
    //std::string out{};
    //HexDump(rawbuf.data(), data_len, out);
    //log("TextureImageData: \n{}", out);
    //return;

    //
    // there is an actual palette variable within the sdk.
    //
    for (size_t i = 0u; i < dim; i++)
    {
        const auto index = *cursor;
        const auto r = g_pal[index * 4u + 0u];
        const auto g = g_pal[index * 4u + 1u];
        const auto b = g_pal[index * 4u + 2u];
        image_data[i * 3u + 0u] = b;
        image_data[i * 3u + 1u] = g;
        image_data[i * 3u + 2u] = r;
        ++cursor;
    }

    static auto counter = 1u;
    const auto filename = std::format("screens/output_{:06}.png", counter++);
    if (::stbi_write_png(filename.c_str(), width, height, 3, image_data.data(), width * 3) != 0)
    {
        // save the image to disk inside folder screens.
    }
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
    log("grTexDownloadTable palette type: {}, addr: {}", type, static_cast<void*>(data));
    /* palette table */
    //GR_TEXTABLE_NCC0;             0
    //GR_TEXTABLE_NCC1;             1
    //GR_TEXTABLE_PALETTE;          2
    //GR_TEXTABLE_PALETTE_6666_EXT; 3
    GuTexPalette x;
    switch (type) {
    case GR_TEXTABLE_PALETTE: {
        /*
            the actual palette variable is an array of FxU32
            as you can see the following ends up copied backwards.
            should actually be:
                FxU32* pal = static_cast<FxU32*>(data);
                std::copy(pal, pal + 256, g_pal.begin());
        */
        uint8_t* pal = static_cast<uint8_t*>(data);
        std::copy(pal, pal + (256 * 4), g_pal.data());

        break;
    }
    }
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
    return FXTRUE;
}

FX_ENTRY FxBool FX_CALL grLfbUnlock(GrLock_t type, GrBuffer_t buffer)
{
    log("grLfbUnlock");
    return FXTRUE;
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
