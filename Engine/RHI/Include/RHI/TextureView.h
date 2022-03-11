//
// Created by johnk on 2022/1/23.
//

#ifndef EXPLOSION_RHI_TEXTURE_VIEW_H
#define EXPLOSION_RHI_TEXTURE_VIEW_H

#include <Common/Utility.h>
#include <RHI/Enum.h>

namespace RHI {
    struct TextureViewCreateInfo {
        PixelFormat format;
        TextureViewDimension dimension;
        TextureAspect aspect;
        uint8_t baseMipLevel;
        uint8_t mipLevelNum;
        uint8_t baseArrayLayer;
        uint8_t arrayLayerNum;
    };

    class TextureView {
    public:
        NON_COPYABLE(TextureView)
        virtual ~TextureView();

        virtual void Destroy() = 0;

    protected:
        explicit TextureView(const TextureViewCreateInfo* createInfo);
    };
}

#endif //EXPLOSION_RHI_TEXTURE_VIEW_H
