
namespace Proto::Math
{
    template <typename T>
    T Minimum(const T a, const T b) { return a < b ? a : b; }
    
    template <typename T>
    T Maximum(const T a, const T b) { return a > b ? a : b; }
    
    template <typename T>
    T Clamp(const T val, const T mi, const T ma) { return Minimum(Maximum(val, ma), mi); }
}