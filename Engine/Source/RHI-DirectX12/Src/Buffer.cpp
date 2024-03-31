//
// Created by johnk on 2022/1/24.
//

#include <vector>
#include <functional>

#include <directx/d3dx12.h>

#include <RHI/Common.h>
#include <RHI/DirectX12/Buffer.h>
#include <RHI/DirectX12/BufferView.h>
#include <RHI/DirectX12/Common.h>
#include <RHI/DirectX12/Device.h>

namespace RHI::DirectX12 {
    static D3D12_HEAP_TYPE GetDX12HeapType(BufferUsageFlags bufferUsages)
    {
        static std::unordered_map<BufferUsageFlags, D3D12_HEAP_TYPE> rules = {
            { BufferUsageBits::mapWrite | BufferUsageBits::copySrc, D3D12_HEAP_TYPE_UPLOAD },
            { BufferUsageBits::mapRead | BufferUsageBits::copyDst, D3D12_HEAP_TYPE_READBACK }
            // TODO check other conditions ?
        };
        static D3D12_HEAP_TYPE fallback = D3D12_HEAP_TYPE_DEFAULT;

        for (const auto& rule : rules) {
            if (bufferUsages & rule.first) {
                return rule.second;
            }
        }
        return fallback;
    }

    static MapMode GetMapMode(BufferUsageFlags bufferUsages)
    {
        static std::unordered_map<BufferUsageBits, MapMode> rules = {
            { BufferUsageBits::mapRead, MapMode::read },
            { BufferUsageBits::mapWrite, MapMode::write }
        };

        for (const auto& rule : rules) {
            if (bufferUsages & rule.first) {
                return rule.second;
            }
        }
        return MapMode::read;
    }
}

namespace RHI::DirectX12 {
    DX12Buffer::DX12Buffer(DX12Device& device, const BufferCreateInfo& inCreateInfo) : Buffer(inCreateInfo), mapMode(GetMapMode(inCreateInfo.usages)), usages(inCreateInfo.usages), device(device)
    {
        CreateNativeBuffer(device, inCreateInfo);
    }

    DX12Buffer::~DX12Buffer() = default;

    void* DX12Buffer::Map(MapMode inMapMode, size_t inOffset, size_t inLength)
    {
        Assert(mapMode == inMapMode);

        void* data;
        CD3DX12_RANGE range(inOffset, inOffset + inLength);
        bool success = SUCCEEDED(nativeResource->Map(0, &range, &data));
        Assert(success);
        return data;
    }

    void DX12Buffer::UnMap()
    {
        nativeResource->Unmap(0, nullptr);
    }

    Holder<BufferView> DX12Buffer::CreateBufferView(const BufferViewCreateInfo& inCreateInfo)
    {
        return Common::UniqueRef<BufferView>(new DX12BufferView(*this, inCreateInfo));
    }

    void DX12Buffer::Destroy()
    {
        delete this;
    }

    ID3D12Resource* DX12Buffer::GetNative()
    {
        return nativeResource.Get();
    }

    BufferUsageFlags DX12Buffer::GetUsages()
    {
        return usages;
    }

    DX12Device& DX12Buffer::GetDevice()
    {
        return device;
    }

    void DX12Buffer::CreateNativeBuffer(DX12Device& inDevice, const BufferCreateInfo& inCreateInfo)
    {
        CD3DX12_HEAP_PROPERTIES heapProperties(GetDX12HeapType(inCreateInfo.usages));
        CD3DX12_RESOURCE_DESC resourceDesc = CD3DX12_RESOURCE_DESC::Buffer(
            inCreateInfo.usages & BufferUsageBits::uniform ?
            GetConstantBufferSize(inCreateInfo.size) :
            inCreateInfo.size);

        bool success = SUCCEEDED(inDevice.GetNative()->CreateCommittedResource(
            &heapProperties,
            D3D12_HEAP_FLAG_NONE,
            &resourceDesc,
            DX12EnumCast<BufferState, D3D12_RESOURCE_STATES>(inCreateInfo.initialState),
            nullptr,
            IID_PPV_ARGS(&nativeResource)));
        Assert(success);

#if BUILD_CONFIG_DEBUG
        if (!inCreateInfo.debugName.empty()) {
            nativeResource->SetName(Common::StringUtils::ToWideString(inCreateInfo.debugName).c_str());
        }
#endif
    }
}