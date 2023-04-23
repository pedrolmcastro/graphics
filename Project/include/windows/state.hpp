/*
    Álvaro José Lopes                  - 10873365
    Natan Henrique Sanches             - 11795680
    Gabriel da Cunha Dertoni           - 11795717
    Pedro Lucas de Moliner de Castro   - 11795784
    João Guilherme Jarochinski Marinho - 10698193
*/


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
