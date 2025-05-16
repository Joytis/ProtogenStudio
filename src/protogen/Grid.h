#pragma once

#include "Vector4.h"

namespace Proto
{
    static constexpr int MAX_GRID_WIDTH = 128;
    static constexpr int MAX_GRID_HEIGHT = 128;

    template<typename T>
    class Grid
    {
    public: 

        Grid(int width, int height, bool inverted) :
            _width(width),
            _height(height),
            _invert(inverted)
        {
            assert(width <= MAX_GRID_WIDTH);
            assert(height <= MAX_GRID_HEIGHT);
        }

        int Width() { return _width; }
        int Height() { return _height; }

        int GetIndex(int x, int y)
        {
            assert(x < _width);
            assert(y < _height);
            x = _invert ? (_width - 1 - x) : x;
            return x + (y * _width);
        }
        

        void Resize(int width, int height)
        {
            assert(width <= MAX_GRID_WIDTH);
            assert(height <= MAX_GRID_HEIGHT);
            _width = width;
            _height = height;
        }

        void Fill(T color)
        {
            for(auto& item : _buffer)
            {
                item = color;
            }
        }

        T& Get(int x, int y)
        {
            return _buffer[GetIndex(x, y)];
        }

        void Set(int x, int y, T& value)
        {
            _buffer[GetIndex(x, y)] = value;
        }

    private:
        int _width;
        int _height;
        bool _invert;
        T _buffer[MAX_GRID_WIDTH * MAX_GRID_HEIGHT];
    };

    using Vector4Grid = Grid<Vector4>;
}