
PROTO_NAMESPACE

#define ENUM_NAME_FUNCTION(enumName) \
    const char* enumName##_Name(enumName e) { \
        int index = Clamp((int)e, 0, ((int)enumName::MAX) - 1); \
        return enumName##_Names[index];  \
    } \

// Blend Mode Functions ========
enum class BlendMode
{
    BestFit,
    FullBlend,
    MAX,
};
static const char* BlendMode_Names[] {
    "Best Fit",
    "Full Blend",
};
ENUM_NAME_FUNCTION(BlendMode)

// Panel Hardware Functions ========
enum class PanelHardware
{
    AdaFruitLED64x32,
    MAX
};
static const char* PanelHardware_Names[] {
    "Adafruit LED 64 x 32 Display",
};
ENUM_NAME_FUNCTION(PanelHardware)

// Expressions Enums ========
enum class ExpressionType
{
    Happy,
    Sadge,
    Pensive,
    Shocked,
    MAX
};
static const char* ExpressionType_Names[] {
    "Happy",
    "Sadge",
    "Pensive",
    "Shocked"
};
ENUM_NAME_FUNCTION(ExpressionType)

// Expressions Groups ========
enum class FacialRegionType
{
    Eyes,
    Mouth,
    MAX
};
static const char* FacialRegionType_Names[] {
    "Eyes",
    "Mouth",
};
ENUM_NAME_FUNCTION(FacialRegionType)

struct PanelTableRow { int width; int height; };
static const PanelTableRow PanelHardware_Dimensions[] {
    { 64, 32 }
};

int PanelHardware_Width(PanelHardware e) 
{ 
    int index = Clamp((int)e, 0, ((int)PanelHardware::MAX) - 1);
    return PanelHardware_Dimensions[index].width; 
}
int PanelHardware_Height(PanelHardware e) 
{ 
    int index = Clamp((int)e, 0, ((int)PanelHardware::MAX) - 1);
    return PanelHardware_Dimensions[index].height; 
}

PROTO_NAMESPACE_END