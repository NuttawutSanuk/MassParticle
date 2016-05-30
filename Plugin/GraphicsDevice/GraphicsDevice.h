﻿#pragma once

class GraphicsDevice
{
public:
    enum class DeviceType
    {
        Unknown,
        D3D9,
        D3D11,
        D3D12,
        OpenGL,
        Vulkan,
        PS4,
    };

    enum class Error
    {
        OK,
        Unknown,
        NotAvailable,
        InvalidParameter,
        OutOfMemory,
        InaccesibleFromCPU,
    };

    enum class TextureFormat
    {
        Unknown = 0,

        ElementsMask  = 0x0F,
        Elements_R    = 0x01,
        Elements_RG   = 0x02,
        Elements_RGBA = 0x04,

        LayoutMask  = 0x0F << 4,
        Layout_RGBA = 0x00 << 4,
        Layout_ARGB = 0x01 << 4,
        Layout_BGRA = 0x02 << 4,

        TypeMask = 0x0F << 8,
        Type_f16 = 0x01 << 8,
        Type_f32 = 0x02 << 8,
        Type_u8  = 0x03 << 8,
        Type_i16 = 0x04 << 8,
        Type_i32 = 0x05 << 8,

        Rf16    = Type_f16 | Layout_RGBA | Elements_R,
        RGf16   = Type_f16 | Layout_RGBA | Elements_RG,
        RGBAf16 = Type_f16 | Layout_RGBA | Elements_RGBA,
        Rf32    = Type_f32 | Layout_RGBA | Elements_R,
        RGf32   = Type_f32 | Layout_RGBA | Elements_RG,
        RGBAf32 = Type_f32 | Layout_RGBA | Elements_RGBA,
        Ru8     = Type_u8  | Layout_RGBA | Elements_R,
        RGu8    = Type_u8  | Layout_RGBA | Elements_RG,
        RGBAu8  = Type_u8  | Layout_RGBA | Elements_RGBA,
        Ri16    = Type_i16 | Layout_RGBA | Elements_R,
        RGi16   = Type_i16 | Layout_RGBA | Elements_RG,
        RGBAi16 = Type_i16 | Layout_RGBA | Elements_RGBA,
        Ri32    = Type_i32 | Layout_RGBA | Elements_R,
        RGi32   = Type_i32 | Layout_RGBA | Elements_RG,
        RGBAi32 = Type_i32 | Layout_RGBA | Elements_RGBA,

        I420    = 0x10 << 8,
    };

    enum class BufferType
    {
        Index,
        Vertex,
        Constant,
        Compute,
        End,
    };


public:
    virtual ~GraphicsDevice() {}
    virtual void* getDevicePtr() = 0;
    virtual DeviceType getDeviceType() = 0;

    virtual void sync() = 0;

    virtual Error readTexture(void *dst, size_t dstsize, void *src_tex, int width, int height, TextureFormat format) = 0;
    virtual Error writeTexture(void *dst_tex, int width, int height, TextureFormat format, const void *src, size_t write_size) = 0;

    virtual Error readBuffer(void *dst, const void *src_buf, size_t read_size, BufferType type) = 0;
    virtual Error writeBuffer(void *dst_buf, const void *src, size_t write_size, BufferType type) = 0;
};


int             GetTexelSize(GraphicsDevice::TextureFormat format);

GraphicsDevice* CreateGraphicsDevice(GraphicsDevice::DeviceType type, void *device_ptr);
void            ReleaseGraphicsDevice();
GraphicsDevice* GetGraphicsDevice();