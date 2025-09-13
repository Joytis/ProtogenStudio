
template <typename T>
T Minimum(const T a, const T b) { return a < b ? a : b; }

template <typename T>
T Maximum(const T a, const T b) { return a > b ? a : b; }

template <typename T>
T Clamp(const T val, const T mi, const T ma) { return Minimum(Maximum(val, ma), mi); }

u32 Float4ToRGBAU32(float4 value)
{
    u32 returnColor = 0;
    returnColor |= static_cast<u8>(value.x() * 255.0f) << 24;
    returnColor |= static_cast<u8>(value.y() * 255.0f) << 16;
    returnColor |= static_cast<u8>(value.z() * 255.0f) << 8;
    returnColor |= static_cast<u8>(value.w() * 255.0f) << 0;
    return returnColor;
}