//
// Created by johnk on 10/1/2022.
//

#pragma once

#include <stdexcept>
#include <utility>
#include <unordered_map>
#include <format>
#include <functional>

#include <dxgi1_4.h>
#include <d3d12.h>

#include <Common/Debug.h>
#include <RHI/Common.h>

namespace RHI::DirectX12 {
    DECLARE_EC_FUNC()
    DECLARE_FC_FUNC()

    ECIMPL_BEGIN(QueueType, D3D12_COMMAND_LIST_TYPE)
        ECIMPL_ITEM(QueueType::graphics, D3D12_COMMAND_LIST_TYPE_DIRECT)
        ECIMPL_ITEM(QueueType::compute, D3D12_COMMAND_LIST_TYPE_COMPUTE)
        ECIMPL_ITEM(QueueType::transfer, D3D12_COMMAND_LIST_TYPE_COPY)
    ECIMPL_END(D3D12_COMMAND_LIST_TYPE)

    ECIMPL_BEGIN(PixelFormat, DXGI_FORMAT)
        // 8-Bits
        ECIMPL_ITEM(PixelFormat::r8Unorm, DXGI_FORMAT_R8_UNORM)
        ECIMPL_ITEM(PixelFormat::r8Snorm, DXGI_FORMAT_R8_SNORM)
        ECIMPL_ITEM(PixelFormat::r8Uint, DXGI_FORMAT_R8_UINT)
        ECIMPL_ITEM(PixelFormat::r8Sint, DXGI_FORMAT_R8_SINT)
        // 16-Bits
        ECIMPL_ITEM(PixelFormat::r16Uint, DXGI_FORMAT_R16_UINT)
        ECIMPL_ITEM(PixelFormat::r16Sint, DXGI_FORMAT_R16_SINT)
        ECIMPL_ITEM(PixelFormat::r16Float, DXGI_FORMAT_R16_FLOAT)
        ECIMPL_ITEM(PixelFormat::rg8Unorm, DXGI_FORMAT_R8G8_UNORM)
        ECIMPL_ITEM(PixelFormat::rg8Snorm, DXGI_FORMAT_R8G8_SNORM)
        ECIMPL_ITEM(PixelFormat::rg8Uint, DXGI_FORMAT_R8G8_UINT)
        ECIMPL_ITEM(PixelFormat::rg8Sint, DXGI_FORMAT_R8G8_SINT)
        // 32-Bits
        ECIMPL_ITEM(PixelFormat::r32Uint, DXGI_FORMAT_R32_UINT)
        ECIMPL_ITEM(PixelFormat::r32Sint, DXGI_FORMAT_R32_SINT)
        ECIMPL_ITEM(PixelFormat::r32Float, DXGI_FORMAT_R32_FLOAT)
        ECIMPL_ITEM(PixelFormat::rg16Uint, DXGI_FORMAT_R16G16_UINT)
        ECIMPL_ITEM(PixelFormat::rg16Sint, DXGI_FORMAT_R16G16_SINT)
        ECIMPL_ITEM(PixelFormat::rg16Float, DXGI_FORMAT_R16G16_FLOAT)
        ECIMPL_ITEM(PixelFormat::rgba8Unorm, DXGI_FORMAT_R8G8B8A8_UNORM)
        ECIMPL_ITEM(PixelFormat::rgba8UnormSrgb, DXGI_FORMAT_R8G8B8A8_UNORM_SRGB)
        ECIMPL_ITEM(PixelFormat::rgba8Snorm, DXGI_FORMAT_R8G8B8A8_SNORM)
        ECIMPL_ITEM(PixelFormat::rgba8Uint, DXGI_FORMAT_R8G8B8A8_UINT)
        ECIMPL_ITEM(PixelFormat::rgba8Sint, DXGI_FORMAT_R8G8B8A8_SINT)
        ECIMPL_ITEM(PixelFormat::bgra8Unorm, DXGI_FORMAT_B8G8R8A8_UNORM)
        ECIMPL_ITEM(PixelFormat::bgra8UnormSrgb, DXGI_FORMAT_B8G8R8A8_UNORM_SRGB)
        ECIMPL_ITEM(PixelFormat::rgb9E5Float, DXGI_FORMAT_R9G9B9E5_SHAREDEXP)
        ECIMPL_ITEM(PixelFormat::rgb10A2Unorm, DXGI_FORMAT_R10G10B10A2_UNORM)
        ECIMPL_ITEM(PixelFormat::rg11B10Float, DXGI_FORMAT_R11G11B10_FLOAT)
        // 64-Bits
        ECIMPL_ITEM(PixelFormat::rg32Uint, DXGI_FORMAT_R32G32_UINT)
        ECIMPL_ITEM(PixelFormat::rg32Sint, DXGI_FORMAT_R32G32_SINT)
        ECIMPL_ITEM(PixelFormat::rg32Float, DXGI_FORMAT_R32G32_FLOAT)
        ECIMPL_ITEM(PixelFormat::rgba16Uint, DXGI_FORMAT_R16G16B16A16_UINT)
        ECIMPL_ITEM(PixelFormat::rgba16Sint, DXGI_FORMAT_R16G16B16A16_SINT)
        ECIMPL_ITEM(PixelFormat::rgba16Float, DXGI_FORMAT_R16G16B16A16_FLOAT)
        // 128-Bits
        ECIMPL_ITEM(PixelFormat::rgba32Uint, DXGI_FORMAT_R32G32B32A32_UINT)
        ECIMPL_ITEM(PixelFormat::rgba32Sint, DXGI_FORMAT_R32G32B32A32_SINT)
        ECIMPL_ITEM(PixelFormat::rgba32Float, DXGI_FORMAT_R32G32B32A32_FLOAT)
        // Depth-Stencil
        ECIMPL_ITEM(PixelFormat::d16Unorm, DXGI_FORMAT_D16_UNORM)
        ECIMPL_ITEM(PixelFormat::d24UnormS8Uint, DXGI_FORMAT_D24_UNORM_S8_UINT)
        ECIMPL_ITEM(PixelFormat::d32Float, DXGI_FORMAT_D32_FLOAT)
        ECIMPL_ITEM(PixelFormat::d32FloatS8Uint, DXGI_FORMAT_D32_FLOAT_S8X24_UINT)
    ECIMPL_END(DXGI_FORMAT)

    ECIMPL_BEGIN(VertexFormat, DXGI_FORMAT)
        // 8-Bits Channel
        ECIMPL_ITEM(VertexFormat::uint8X2, DXGI_FORMAT_R8G8_UINT)
        ECIMPL_ITEM(VertexFormat::uint8X4, DXGI_FORMAT_R8G8B8A8_UINT)
        ECIMPL_ITEM(VertexFormat::sint8X2, DXGI_FORMAT_R8G8_SINT)
        ECIMPL_ITEM(VertexFormat::sint8X4, DXGI_FORMAT_R8G8B8A8_SINT)
        ECIMPL_ITEM(VertexFormat::unorm8X2, DXGI_FORMAT_R8G8_UNORM)
        ECIMPL_ITEM(VertexFormat::unorm8X4, DXGI_FORMAT_R8G8B8A8_UNORM)
        ECIMPL_ITEM(VertexFormat::snorm8X2, DXGI_FORMAT_R8G8_SNORM)
        ECIMPL_ITEM(VertexFormat::snorm8X4, DXGI_FORMAT_R8G8B8A8_SNORM)
        // 16-Bits Channel
        ECIMPL_ITEM(VertexFormat::uint16X2, DXGI_FORMAT_R16G16_UINT)
        ECIMPL_ITEM(VertexFormat::uint16X4, DXGI_FORMAT_R16G16B16A16_UINT)
        ECIMPL_ITEM(VertexFormat::sint16X2, DXGI_FORMAT_R16G16_SINT)
        ECIMPL_ITEM(VertexFormat::sint16X4, DXGI_FORMAT_R16G16B16A16_SINT)
        ECIMPL_ITEM(VertexFormat::unorm16X2, DXGI_FORMAT_R16G16_UNORM)
        ECIMPL_ITEM(VertexFormat::unorm16X4, DXGI_FORMAT_R16G16B16A16_UNORM)
        ECIMPL_ITEM(VertexFormat::snorm16X2, DXGI_FORMAT_R16G16_SNORM)
        ECIMPL_ITEM(VertexFormat::snorm16X4, DXGI_FORMAT_R16G16B16A16_SNORM)
        ECIMPL_ITEM(VertexFormat::float16X2, DXGI_FORMAT_R16G16_FLOAT)
        ECIMPL_ITEM(VertexFormat::float16X4, DXGI_FORMAT_R16G16B16A16_FLOAT)
        // 32-Bits Channel
        ECIMPL_ITEM(VertexFormat::float32X1, DXGI_FORMAT_R32_FLOAT)
        ECIMPL_ITEM(VertexFormat::float32X2, DXGI_FORMAT_R32G32_FLOAT)
        ECIMPL_ITEM(VertexFormat::float32X3, DXGI_FORMAT_R32G32B32_FLOAT)
        ECIMPL_ITEM(VertexFormat::float32X4, DXGI_FORMAT_R32G32B32A32_FLOAT)
        ECIMPL_ITEM(VertexFormat::uint32X1, DXGI_FORMAT_R32_UINT)
        ECIMPL_ITEM(VertexFormat::uint32X2, DXGI_FORMAT_R32G32_UINT)
        ECIMPL_ITEM(VertexFormat::uint32X3, DXGI_FORMAT_R32G32B32_FLOAT)
        ECIMPL_ITEM(VertexFormat::uint32X4, DXGI_FORMAT_R32G32B32A32_UINT)
        ECIMPL_ITEM(VertexFormat::sint32X1, DXGI_FORMAT_R32_SINT)
        ECIMPL_ITEM(VertexFormat::sint32X2, DXGI_FORMAT_R32G32_SINT)
        ECIMPL_ITEM(VertexFormat::sint32X3, DXGI_FORMAT_R32G32B32_SINT)
        ECIMPL_ITEM(VertexFormat::sint32X4, DXGI_FORMAT_R32G32B32A32_SINT)
    ECIMPL_END(DXGI_FORMAT)

    ECIMPL_BEGIN(TextureViewDimension, D3D12_SRV_DIMENSION)
        ECIMPL_ITEM(TextureViewDimension::tv1D, D3D12_SRV_DIMENSION_TEXTURE1D)
        ECIMPL_ITEM(TextureViewDimension::tv2D, D3D12_SRV_DIMENSION_TEXTURE2D)
        ECIMPL_ITEM(TextureViewDimension::tv2DArray, D3D12_SRV_DIMENSION_TEXTURE2DARRAY)
        ECIMPL_ITEM(TextureViewDimension::tvCube, D3D12_SRV_DIMENSION_TEXTURECUBE)
        ECIMPL_ITEM(TextureViewDimension::tvCubeArray, D3D12_SRV_DIMENSION_TEXTURECUBEARRAY)
        ECIMPL_ITEM(TextureViewDimension::tv3D, D3D12_SRV_DIMENSION_TEXTURE3D)
    ECIMPL_END(D3D12_SRV_DIMENSION)

    ECIMPL_BEGIN(TextureViewDimension, D3D12_UAV_DIMENSION)
        ECIMPL_ITEM(TextureViewDimension::tv1D, D3D12_UAV_DIMENSION_TEXTURE1D)
        ECIMPL_ITEM(TextureViewDimension::tv2D, D3D12_UAV_DIMENSION_TEXTURE2D)
        ECIMPL_ITEM(TextureViewDimension::tv2DArray, D3D12_UAV_DIMENSION_TEXTURE2DARRAY)
        ECIMPL_ITEM(TextureViewDimension::tv3D, D3D12_UAV_DIMENSION_TEXTURE3D)
        // not support cube and cube array when texture is used as a UAV
    ECIMPL_END(D3D12_UAV_DIMENSION)

    ECIMPL_BEGIN(TextureViewDimension, D3D12_RTV_DIMENSION)
        ECIMPL_ITEM(TextureViewDimension::tv1D, D3D12_RTV_DIMENSION_TEXTURE1D)
        ECIMPL_ITEM(TextureViewDimension::tv2D, D3D12_RTV_DIMENSION_TEXTURE2D)
        ECIMPL_ITEM(TextureViewDimension::tv2DArray, D3D12_RTV_DIMENSION_TEXTURE2DARRAY)
        ECIMPL_ITEM(TextureViewDimension::tv3D, D3D12_RTV_DIMENSION_TEXTURE3D)
    ECIMPL_END(D3D12_RTV_DIMENSION)

    ECIMPL_BEGIN(TextureViewDimension, D3D12_DSV_DIMENSION)
        ECIMPL_ITEM(TextureViewDimension::tv1D, D3D12_DSV_DIMENSION_TEXTURE1D)
        ECIMPL_ITEM(TextureViewDimension::tv2D, D3D12_DSV_DIMENSION_TEXTURE2D)
        ECIMPL_ITEM(TextureViewDimension::tv2DArray, D3D12_DSV_DIMENSION_TEXTURE2DARRAY)
    ECIMPL_END(D3D12_DSV_DIMENSION)

    ECIMPL_BEGIN(AddressMode, D3D12_TEXTURE_ADDRESS_MODE)
        ECIMPL_ITEM(AddressMode::clampToEdge, D3D12_TEXTURE_ADDRESS_MODE_CLAMP)
        ECIMPL_ITEM(AddressMode::repeat, D3D12_TEXTURE_ADDRESS_MODE_WRAP)
        ECIMPL_ITEM(AddressMode::mirrorRepeat, D3D12_TEXTURE_ADDRESS_MODE_MIRROR)
    ECIMPL_END(D3D12_TEXTURE_ADDRESS_MODE)

    ECIMPL_BEGIN(CompareFunc, D3D12_COMPARISON_FUNC)
        ECIMPL_ITEM(CompareFunc::never, D3D12_COMPARISON_FUNC_NEVER)
        ECIMPL_ITEM(CompareFunc::less, D3D12_COMPARISON_FUNC_LESS)
        ECIMPL_ITEM(CompareFunc::equal, D3D12_COMPARISON_FUNC_EQUAL)
        ECIMPL_ITEM(CompareFunc::lessEqual, D3D12_COMPARISON_FUNC_LESS_EQUAL)
        ECIMPL_ITEM(CompareFunc::greater, D3D12_COMPARISON_FUNC_GREATER)
        ECIMPL_ITEM(CompareFunc::notEqual, D3D12_COMPARISON_FUNC_NOT_EQUAL)
        ECIMPL_ITEM(CompareFunc::greaterEqual, D3D12_COMPARISON_FUNC_GREATER_EQUAL)
        ECIMPL_ITEM(CompareFunc::always, D3D12_COMPARISON_FUNC_ALWAYS)
    ECIMPL_END(D3D12_COMPARISON_FUNC)

    ECIMPL_BEGIN(HlslBindingRangeType, D3D12_DESCRIPTOR_RANGE_TYPE)
        ECIMPL_ITEM(HlslBindingRangeType::constantBuffer, D3D12_DESCRIPTOR_RANGE_TYPE_CBV)
        ECIMPL_ITEM(HlslBindingRangeType::texture, D3D12_DESCRIPTOR_RANGE_TYPE_SRV)
        ECIMPL_ITEM(HlslBindingRangeType::sampler, D3D12_DESCRIPTOR_RANGE_TYPE_SAMPLER)
        ECIMPL_ITEM(HlslBindingRangeType::unorderedAccess, D3D12_DESCRIPTOR_RANGE_TYPE_UAV)
    ECIMPL_END(D3D12_DESCRIPTOR_RANGE_TYPE)

    ECIMPL_BEGIN(ShaderStageBits, D3D12_SHADER_VISIBILITY)
        ECIMPL_ITEM(ShaderStageBits::sVertex, D3D12_SHADER_VISIBILITY_VERTEX)
        ECIMPL_ITEM(ShaderStageBits::sPixel, D3D12_SHADER_VISIBILITY_PIXEL)
        ECIMPL_ITEM(ShaderStageBits::sCompute, D3D12_SHADER_VISIBILITY_ALL)
        ECIMPL_ITEM(ShaderStageBits::sGeometry, D3D12_SHADER_VISIBILITY_GEOMETRY)
        ECIMPL_ITEM(ShaderStageBits::sDomain, D3D12_SHADER_VISIBILITY_DOMAIN)
        ECIMPL_ITEM(ShaderStageBits::sHull, D3D12_SHADER_VISIBILITY_HULL)
    ECIMPL_END(D3D12_SHADER_VISIBILITY)

    ECIMPL_BEGIN(PrimitiveTopologyType, D3D12_PRIMITIVE_TOPOLOGY_TYPE)
        ECIMPL_ITEM(PrimitiveTopologyType::point, D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT)
        ECIMPL_ITEM(PrimitiveTopologyType::line, D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE)
        ECIMPL_ITEM(PrimitiveTopologyType::triangle, D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE)
    ECIMPL_END(D3D12_PRIMITIVE_TOPOLOGY_TYPE)

    ECIMPL_BEGIN(FillMode, D3D12_FILL_MODE)
        ECIMPL_ITEM(FillMode::wireframe, D3D12_FILL_MODE_WIREFRAME)
        ECIMPL_ITEM(FillMode::solid, D3D12_FILL_MODE_SOLID)
    ECIMPL_END(D3D12_FILL_MODE)

    ECIMPL_BEGIN(PrimitiveTopology, D3D_PRIMITIVE_TOPOLOGY)
        ECIMPL_ITEM(PrimitiveTopology::pointList, D3D_PRIMITIVE_TOPOLOGY_POINTLIST)
        ECIMPL_ITEM(PrimitiveTopology::lineList, D3D_PRIMITIVE_TOPOLOGY_LINELIST)
        ECIMPL_ITEM(PrimitiveTopology::lineStrip, D3D_PRIMITIVE_TOPOLOGY_LINESTRIP)
        ECIMPL_ITEM(PrimitiveTopology::triangleList, D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
        ECIMPL_ITEM(PrimitiveTopology::triangleStrip, D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP)
        ECIMPL_ITEM(PrimitiveTopology::lineListAdj, D3D_PRIMITIVE_TOPOLOGY_LINELIST_ADJ)
        ECIMPL_ITEM(PrimitiveTopology::lineStripAdj, D3D_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ)
        ECIMPL_ITEM(PrimitiveTopology::triangleListAdj, D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ)
        ECIMPL_ITEM(PrimitiveTopology::triangleStripAdj, D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ)
    ECIMPL_END(D3D_PRIMITIVE_TOPOLOGY)

    ECIMPL_BEGIN(BlendOp, D3D12_BLEND_OP)
        ECIMPL_ITEM(BlendOp::opAdd, D3D12_BLEND_OP_ADD)
        ECIMPL_ITEM(BlendOp::opSubstract, D3D12_BLEND_OP_SUBTRACT)
        ECIMPL_ITEM(BlendOp::opReverseSubstract, D3D12_BLEND_OP_REV_SUBTRACT)
        ECIMPL_ITEM(BlendOp::opMin, D3D12_BLEND_OP_MIN)
        ECIMPL_ITEM(BlendOp::opMax, D3D12_BLEND_OP_MAX)
    ECIMPL_END(D3D12_BLEND_OP)

    ECIMPL_BEGIN(BlendFactor, D3D12_BLEND)
        ECIMPL_ITEM(BlendFactor::zero, D3D12_BLEND_ZERO)
        ECIMPL_ITEM(BlendFactor::one, D3D12_BLEND_ONE)
        ECIMPL_ITEM(BlendFactor::src, D3D12_BLEND_SRC_COLOR)
        ECIMPL_ITEM(BlendFactor::oneMinusSrc, D3D12_BLEND_INV_SRC_COLOR)
        ECIMPL_ITEM(BlendFactor::srcAlpha, D3D12_BLEND_SRC_ALPHA)
        ECIMPL_ITEM(BlendFactor::oneMinusSrcAlpha, D3D12_BLEND_INV_SRC_ALPHA)
        ECIMPL_ITEM(BlendFactor::dst, D3D12_BLEND_DEST_COLOR)
        ECIMPL_ITEM(BlendFactor::oneMinusDst, D3D12_BLEND_INV_DEST_COLOR)
        ECIMPL_ITEM(BlendFactor::dstAlpha, D3D12_BLEND_DEST_ALPHA)
        ECIMPL_ITEM(BlendFactor::oneMinusDstAlpha, D3D12_BLEND_INV_DEST_ALPHA)
    ECIMPL_END(D3D12_BLEND)

    ECIMPL_BEGIN(CullMode, D3D12_CULL_MODE)
        ECIMPL_ITEM(CullMode::none, D3D12_CULL_MODE_NONE)
        ECIMPL_ITEM(CullMode::front, D3D12_CULL_MODE_FRONT)
        ECIMPL_ITEM(CullMode::back, D3D12_CULL_MODE_BACK)
    ECIMPL_END(D3D12_CULL_MODE)

    // see https://docs.microsoft.com/en-us/windows/win32/api/d3d12/ne-d3d12-d3d12_stencil_op
    ECIMPL_BEGIN(StencilOp, D3D12_STENCIL_OP)
        ECIMPL_ITEM(StencilOp::keep, D3D12_STENCIL_OP_KEEP)
        ECIMPL_ITEM(StencilOp::zero, D3D12_STENCIL_OP_ZERO)
        ECIMPL_ITEM(StencilOp::replace, D3D12_STENCIL_OP_REPLACE)
        ECIMPL_ITEM(StencilOp::invert, D3D12_STENCIL_OP_INVERT)
        ECIMPL_ITEM(StencilOp::incrementClamp, D3D12_STENCIL_OP_INCR_SAT)
        ECIMPL_ITEM(StencilOp::decrementClamp, D3D12_STENCIL_OP_DECR_SAT)
        ECIMPL_ITEM(StencilOp::incrementWrap, D3D12_STENCIL_OP_INCR)
        ECIMPL_ITEM(StencilOp::decrementWrap, D3D12_STENCIL_OP_DECR)
    ECIMPL_END(D3D12_STENCIL_OP)

    ECIMPL_BEGIN(IndexFormat, DXGI_FORMAT)
        ECIMPL_ITEM(IndexFormat::uint16, DXGI_FORMAT_R16_UINT)
        ECIMPL_ITEM(IndexFormat::uint32, DXGI_FORMAT_R32_UINT)
    ECIMPL_END(DXGI_FORMAT)

    ECIMPL_BEGIN(VertexStepMode, D3D12_INPUT_CLASSIFICATION)
        ECIMPL_ITEM(VertexStepMode::perVertex, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA)
        ECIMPL_ITEM(VertexStepMode::perInstance, D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA)
    ECIMPL_END(D3D12_INPUT_CLASSIFICATION)

    ECIMPL_BEGIN(BufferState, D3D12_RESOURCE_STATES)
        ECIMPL_ITEM(BufferState::undefined, D3D12_RESOURCE_STATE_COMMON)
        ECIMPL_ITEM(BufferState::staging, D3D12_RESOURCE_STATE_GENERIC_READ)
        ECIMPL_ITEM(BufferState::copySrc, D3D12_RESOURCE_STATE_COPY_SOURCE)
        ECIMPL_ITEM(BufferState::copyDst, D3D12_RESOURCE_STATE_COPY_DEST)
        ECIMPL_ITEM(BufferState::shaderReadOnly, D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE | D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE)
        ECIMPL_ITEM(BufferState::storage, D3D12_RESOURCE_STATE_UNORDERED_ACCESS)
    ECIMPL_END(D3D12_RESOURCE_STATES)

    ECIMPL_BEGIN(TextureDimension, D3D12_RESOURCE_DIMENSION)
        ECIMPL_ITEM(TextureDimension::t1D, D3D12_RESOURCE_DIMENSION_TEXTURE1D)
        ECIMPL_ITEM(TextureDimension::t2D, D3D12_RESOURCE_DIMENSION_TEXTURE2D)
        ECIMPL_ITEM(TextureDimension::t3D, D3D12_RESOURCE_DIMENSION_TEXTURE3D)
    ECIMPL_END(D3D12_RESOURCE_DIMENSION)

    ECIMPL_BEGIN(TextureState, D3D12_RESOURCE_STATES)
        ECIMPL_ITEM(TextureState::undefined, D3D12_RESOURCE_STATE_COMMON)
        ECIMPL_ITEM(TextureState::copySrc, D3D12_RESOURCE_STATE_COPY_SOURCE)
        ECIMPL_ITEM(TextureState::copyDst, D3D12_RESOURCE_STATE_COPY_DEST)
        ECIMPL_ITEM(TextureState::shaderReadOnly, D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE | D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE)
        ECIMPL_ITEM(TextureState::renderTarget, D3D12_RESOURCE_STATE_RENDER_TARGET)
        ECIMPL_ITEM(TextureState::storage, D3D12_RESOURCE_STATE_UNORDERED_ACCESS)
        ECIMPL_ITEM(TextureState::depthStencilReadonly, D3D12_RESOURCE_STATE_DEPTH_READ)
        ECIMPL_ITEM(TextureState::depthStencilWrite, D3D12_RESOURCE_STATE_DEPTH_WRITE)
        ECIMPL_ITEM(TextureState::present, D3D12_RESOURCE_STATE_PRESENT)
    ECIMPL_END(D3D12_RESOURCE_STATES)

    FCIMPL_BEGIN(ColorWriteFlags, uint8_t)
        FCIMPL_ITEM(ColorWriteBits::red,   D3D12_COLOR_WRITE_ENABLE_RED)
        FCIMPL_ITEM(ColorWriteBits::green, D3D12_COLOR_WRITE_ENABLE_GREEN)
        FCIMPL_ITEM(ColorWriteBits::blue,  D3D12_COLOR_WRITE_ENABLE_BLUE)
        FCIMPL_ITEM(ColorWriteBits::alpha, D3D12_COLOR_WRITE_ENABLE_ALPHA)
    FCIMPL_END(D3D12_COLOR_WRITE_ENABLE)

    FCIMPL_BEGIN(TextureUsageFlags, D3D12_RESOURCE_FLAGS)
        FCIMPL_ITEM(TextureUsageBits::copySrc,                D3D12_RESOURCE_FLAG_NONE)
        FCIMPL_ITEM(TextureUsageBits::copyDst,                D3D12_RESOURCE_FLAG_NONE)
        FCIMPL_ITEM(TextureUsageBits::textureBinding,         D3D12_RESOURCE_FLAG_NONE)
        FCIMPL_ITEM(TextureUsageBits::storageBinding,         D3D12_RESOURCE_FLAG_NONE)
        FCIMPL_ITEM(TextureUsageBits::renderAttachment,       D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET)
        FCIMPL_ITEM(TextureUsageBits::depthStencilAttachment, D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL)
    FCIMPL_END(D3D12_RESOURCE_FLAGS)

    // constant buffer size must be a multiple of 256
    inline size_t GetConstantBufferSize(size_t size) {
        return (size + (D3D12_CONSTANT_BUFFER_DATA_PLACEMENT_ALIGNMENT - 1)) & ~(D3D12_CONSTANT_BUFFER_DATA_PLACEMENT_ALIGNMENT - 1);
    }

    // TODO use DirectXTex ComputePitch ?
    inline size_t GetBytesPerPixel(PixelFormat format) {
        if (format >= PixelFormat::r8Unorm && format <= PixelFormat::r8Sint) {
            return 1;
        }
        if (format >= PixelFormat::r16Uint && format <= PixelFormat::rg8Sint) {
            return 2;
        }
        if (format >= PixelFormat::r32Uint && format <= PixelFormat::rg11B10Float) {
            return 4;
        }
        if (format >= PixelFormat::rg32Uint && format <= PixelFormat::rgba16Float) {
            return 8;
        }
        if (format >= PixelFormat::rgba32Uint && format <= PixelFormat::rgba32Float) {
            return 16;
        }

        // TODO depth stencil texture format

        return 0;
    }
}
