//
// Created by johnk on 13/1/2022.
//

#include <RHI/DirectX12/Gpu.h>

namespace RHI::DirectX12 {
    DX12Gpu::DX12Gpu(ComPtr<IDXGIAdapter1>&& a) : Gpu(), dx12Adapter(a) {}

    DX12Gpu::~DX12Gpu() = default;

    GpuProperty DX12Gpu::GetProperty()
    {
        DXGI_ADAPTER_DESC1 desc;
        dx12Adapter->GetDesc1(&desc);

        GpuProperty property {};
        property.vendorId = desc.VendorId;
        property.deviceId = desc.DeviceId;
        // TODO
        return property;
    }
}
