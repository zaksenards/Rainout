#include <rainout/assetManager.h>

namespace rainout
{
    Texture::Texture(){}
    Texture::Texture(char* data, uint32_t width, uint32_t height, uint32_t bitCount, bool animated, uint8_t frames, uint32_t frameW, uint32_t frameH)
        :_data(data),_width(width),_height(height),_bitCount(bitCount),_animated(animated),_frames(frames),_frameWidth(frameW),_frameHeight(frameH)
    {
        _index = 0;
        _animationSpeed = 0.4f;
    }

    Texture::~Texture()
    {
        delete _data;
    }

    void Texture::setAnimationSpeed(float speed)
    {
        _animationSpeed = speed;
    }

    float Texture::getAnimationSpeed()
    {
        return _animationSpeed;
    }

    uint8_t Texture::getAnimationIndex()
    {
        return (uint8_t)_index;
    }

    uint8_t Texture::getFrameCount()
    {
        return _frames;
    }

    uint32_t Texture::getFrameWidth()
    {
        return _frameWidth;
    }

    uint32_t Texture::getFrameHeight()
    {
        return _frameHeight;
    }

    uint32_t Texture::getBitCount()
    {
        return _bitCount;
    }

    bool    Texture::isAnimated()
    {
        return _animated;
    }

    uint32_t Texture::getHeight()
    {
        return _height;
    }

    void Texture::playAnimation()
    {
        if(!_animated)
            return;

        if(_index < _frames)
            _index+=_animationSpeed;
        else
            _index = 0;
    }

    uint32_t Texture::getWidth()
    {
        return _width;
    }

    char* Texture::getData()
    {
        return _data;
    }
}
