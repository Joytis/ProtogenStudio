#pragma once

PROTO_NAMESPACE

static constexpr int MAX_GRID_WIDTH = 128;
static constexpr int MAX_GRID_HEIGHT = 128;

class Grid
{
public: 
    
    Grid() : Grid(0, 0, false) {} 

    Grid(int width, int height, bool inverted) :
        _width(width),
        _height(height),
        _invert(inverted)
    {
        Resize(width, height);
    }
    
    void SetInverted(bool flipped)
    {
        _invert = flipped;
    }

    void Resize(int width, int height)
    {
        assert(width <= MAX_GRID_WIDTH);
        assert(height <= MAX_GRID_HEIGHT);
        _width = width;
        _height = height;
        memset(_buffer, sizeof(_buffer), 0);
    }

    int Width() const { return _width; }
    int Height() const { return _height; }

    int GetIndex(int x, int y) const
    {
        assert(x < _width);
        assert(y < _height);
        x = _invert ? (_width - 1 - x) : x;
        return x + (y * _width);
    }
    
    void Fill(float4 color)
    {
        for(auto& item : _buffer)
        {
            item = color;
        }
    }

    const float4& Get(int x, int y) const
    {
        int index = GetIndex(x, y);
        return _buffer[index];
    }

    float4& GetMutable(int x, int y)
    {
        int index = GetIndex(x, y);
        return _buffer[index];
    }

    void Set(int x, int y, const float4& value)
    {
        int index = GetIndex(x, y);
        _buffer[index] = value;
    }

private:
    int _width;
    int _height;
    bool _invert;
    float4 _buffer[MAX_GRID_WIDTH * MAX_GRID_HEIGHT];
};

PROTO_NAMESPACE_END
