

// ARbitrarily 64 kilobytes. 
constexpr u32 SAVE_BUFFER_SIZE = KBs(64);
constexpr u32 MAX_UNDO = 64;

constexpr u32 UNDO_BUFFER_SIZE = SAVE_BUFFER_SIZE * MAX_UNDO;

namespace Undo
{
    void* gs_undoBuffer = nullptr;
    int gs_currentIndex = 0;
    int gs_size = 0;
    
    void Initialize()
    {
        assert(gs_undoBuffer == nullptr);
        gs_undoBuffer = malloc(UNDO_BUFFER_SIZE);
    }

}
