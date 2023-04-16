#pragma once


namespace windows {
    // Singleton RAII to manage GLFW init and terminate
    class State final {
    public:
        static auto get() -> State&;
        ~State() noexcept;

    private:
        State();
    };
}
