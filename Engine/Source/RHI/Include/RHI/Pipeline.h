//
// Created by johnk on 19/2/2022.
//

#pragma once

#include <string>
#include <variant>

#include <Common/Utility.h>
#include <RHI/Common.h>

namespace RHI {
    class BindGroupLayout;
    class PipelineLayout;
    class ShaderModule;

    struct HlslVertexBinding {
        std::string semanticName;
        uint8_t semanticIndex;

        HlslVertexBinding();
        HlslVertexBinding(std::string inSemanticName, uint8_t inSemanticIndex);
    };

    struct GlslVertexBinding {
        uint8_t location;

        GlslVertexBinding();
        GlslVertexBinding(uint8_t inLocation);
    };

    struct VertexAttribute {
        std::variant<HlslVertexBinding, GlslVertexBinding> platformBinding;
        VertexFormat format;
        size_t offset;

        explicit VertexAttribute(
            const std::variant<HlslVertexBinding, GlslVertexBinding>& inPlatformBinding = {},
            VertexFormat inFormat = VertexFormat::max,
            size_t inOffset = 0);

        VertexAttribute& SetPlatformBinding(std::variant<HlslVertexBinding, GlslVertexBinding> inPlatformBinding);
        VertexAttribute& SetFormat(VertexFormat inFormat);
        VertexAttribute& SetOffset(size_t inOffset);
    };

    struct VertexBufferLayout {
        VertexStepMode stepMode;
        size_t stride;
        std::vector<VertexAttribute> attributes;

        explicit VertexBufferLayout(
            VertexStepMode inStepMode = VertexStepMode::perVertex,
            size_t inStride = 0);

        VertexBufferLayout& SetStride(size_t inStride);
        VertexBufferLayout& SetStepMode(VertexStepMode inStepMode);
        VertexBufferLayout& AddAttribute(const VertexAttribute& inAttribute);
    };

    struct VertexState {
        std::vector<VertexBufferLayout> bufferLayouts;

        VertexState();
        VertexState& AddVertexBufferLayout(const VertexBufferLayout& inLayout);
    };

    struct PrimitiveState {
        PrimitiveTopologyType topologyType;
        FillMode fillMode;
        IndexFormat stripIndexFormat;
        FrontFace frontFace;
        CullMode cullMode;
        bool depthClip = false;

        explicit PrimitiveState(
            PrimitiveTopologyType inTopologyType = PrimitiveTopologyType::triangle,
            FillMode inFillMode = FillMode::solid,
            IndexFormat inStripIndexFormat = IndexFormat::uint16,
            FrontFace inFrontFace = FrontFace::ccw,
            CullMode inCullMode = CullMode::back,
            bool inDepthClip = false);

        PrimitiveState& SetTopologyType(PrimitiveTopologyType inTopologyType);
        PrimitiveState& SetFillMode(FillMode inFillMode);
        PrimitiveState& SetStripIndexFormat(IndexFormat inFormat);
        PrimitiveState& SetFrontFace(FrontFace inFrontFace);
        PrimitiveState& SetCullMode(CullMode inCullMode);
        PrimitiveState& SetDepthClip(bool inDepthClip);
    };

    struct StencilFaceState {
        CompareFunc compareFunc;
        StencilOp failOp;
        StencilOp depthFailOp;
        StencilOp passOp;

        explicit StencilFaceState(
            CompareFunc inCompareFunc = CompareFunc::always,
            StencilOp inFailOp = StencilOp::keep,
            StencilOp inDepthFailOp = StencilOp::keep,
            StencilOp inPassOp = StencilOp::keep);
    };

    struct DepthStencilState {
        bool depthEnabled;
        bool stencilEnabled;
        PixelFormat format;
        CompareFunc depthCompareFunc;
        int32_t depthBias;
        float depthBiasSlopeScale;
        float depthBiasClamp;
        StencilFaceState stencilFront;
        StencilFaceState stencilBack;
        uint8_t stencilReadMask;
        uint8_t stencilWriteMask;

        explicit DepthStencilState(
            bool inDepthEnabled = false,
            bool inStencilEnabled = false,
            PixelFormat inFormat = PixelFormat::max,
            CompareFunc inDepthCompareFunc = CompareFunc::always,
            int32_t inDepthBias = 0,
            float inDepthBiasSlopeScale = 0.0f,
            float inDepthBiasClamp = 0.0f,
            const StencilFaceState& inStencilFront = StencilFaceState(),
            const StencilFaceState& inStencilBack = StencilFaceState(),
            uint8_t inStencilReadMask = 0,
            uint8_t inStencilWriteMask = 0);

        DepthStencilState& SetDepthEnabled(bool inDepthEnabled);
        DepthStencilState& SetStencilEnabled(bool inStencilEnabled);
        DepthStencilState& SetFormat(PixelFormat inFormat);
        DepthStencilState& SetDepthCompareFunc(CompareFunc inFunc);
        DepthStencilState& SetStencilFront(StencilFaceState inState);
        DepthStencilState& SetStencilBack(StencilFaceState inState);
        DepthStencilState& SetStencilReadMask(uint8_t inStencilReadMask);
        DepthStencilState& SetStencilWriteMask(uint8_t inStencilWriteMask);
        DepthStencilState& SetDepthBias(int32_t inDepthBias);
        DepthStencilState& SetDepthBiasSlopeScale(float inDepthBiasSlopeScale);
        DepthStencilState& SetDepthBiasClamp(float inDepthBiasClamp);
    };

    struct MultiSampleState {
        uint8_t count;
        uint32_t mask;
        bool alphaToCoverage = false;

        explicit MultiSampleState(
            uint8_t inCount = 1,
            uint32_t inMask = 0xffffffff,
            bool inAlphaToCoverage = false);

        MultiSampleState& SetCount(uint8_t inCount);
        MultiSampleState& SetMask(uint32_t inMask);
        MultiSampleState& SetAlphaToCoverage(bool inAlphaToCoverage);
    };

    struct BlendComponent {
        BlendOp op;
        BlendFactor srcFactor;
        BlendFactor dstFactor;

        explicit BlendComponent(
            BlendOp inOp = BlendOp::opAdd,
            BlendFactor inSrcFactor = BlendFactor::one,
            BlendFactor inDstFactor = BlendFactor::zero);
    };

    struct ColorTargetState {
        PixelFormat format;
        ColorWriteFlags writeFlags;
        bool blendEnabled;
        BlendComponent colorBlend;
        BlendComponent alphaBlend;

        explicit ColorTargetState(
            PixelFormat inFormat = PixelFormat::max,
            ColorWriteFlags inWriteFlags = ColorWriteFlags::null,
            bool inBlendEnabled = false,
            const BlendComponent& inColorBlend = BlendComponent(),
            const BlendComponent& inAlphaBlend = BlendComponent());

        ColorTargetState& SetFormat(PixelFormat inFormat);
        ColorTargetState& SetWriteFlags(ColorWriteFlags inFlags);
        ColorTargetState& SetBlendEnabled(bool inBlendEnabled);
        ColorTargetState& SetColorBlend(const BlendComponent& inColorBlend);
        ColorTargetState& SetAlphaBlend(const BlendComponent& inAlphaBlend);
    };

    struct FragmentState {
        std::vector<ColorTargetState> colorTargets;

        FragmentState();
        FragmentState& AddColorTarget(const ColorTargetState& inState);
    };

    struct ComputePipelineCreateInfo {
        PipelineLayout* layout;
        ShaderModule* computeShader;

        ComputePipelineCreateInfo();
        ComputePipelineCreateInfo& SetLayout(PipelineLayout* inLayout);
        ComputePipelineCreateInfo& SetComputeShader(ShaderModule* inComputeShader);
    };

    struct RasterPipelineCreateInfo {
        PipelineLayout* layout;

        ShaderModule* vertexShader;
        ShaderModule* pixelShader;
        ShaderModule* geometryShader;
        ShaderModule* domainShader;
        ShaderModule* hullShader;

        VertexState vertexState;
        PrimitiveState primitiveState;
        DepthStencilState depthStencilState;
        MultiSampleState multiSampleState;
        FragmentState fragmentState;

        std::string debugName;

        RasterPipelineCreateInfo(PipelineLayout* inLayout = nullptr);
        RasterPipelineCreateInfo& SetLayout(PipelineLayout* inLayout);
        RasterPipelineCreateInfo& SetVertexShader(ShaderModule* inVertexShader);
        RasterPipelineCreateInfo& SetPixelShader(ShaderModule* inPixelShader);
        RasterPipelineCreateInfo& SetGeometryShader(ShaderModule* inGeometryShader);
        RasterPipelineCreateInfo& SetDomainShader(ShaderModule* inDomainShader);
        RasterPipelineCreateInfo& SetHullShader(ShaderModule* inHullShader);
        RasterPipelineCreateInfo& SetVertexState(const VertexState& inVertexState);
        RasterPipelineCreateInfo& SetPrimitiveState(const PrimitiveState& inPrimitiveState);
        RasterPipelineCreateInfo& SetDepthStencilState(const DepthStencilState& inDepthStencilState);
        RasterPipelineCreateInfo& SetMultiSampleState(const MultiSampleState& inMultiSampleState);
        RasterPipelineCreateInfo& SetFragmentState(const FragmentState& inFragmentState);
        RasterPipelineCreateInfo& SetDebugName(std::string inDebugName);
    };

    class Pipeline {
    public:
        NonCopyable(Pipeline)
        virtual ~Pipeline();

        virtual void Destroy() = 0;

    protected:
        Pipeline();
    };

    class ComputePipeline : public Pipeline {
    public:
        NonCopyable(ComputePipeline)
        ~ComputePipeline() override;

        void Destroy() override = 0;

    protected:
        explicit ComputePipeline(const ComputePipelineCreateInfo& createInfo);
    };

    class RasterPipeline : public Pipeline {
    public:
        NonCopyable(RasterPipeline)
        ~RasterPipeline() override;

        void Destroy() override = 0;

    protected:
        explicit RasterPipeline(const RasterPipelineCreateInfo& createInfo);
    };
}
