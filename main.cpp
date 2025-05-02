#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <algorithm>
#include <array>
#include <chrono>
#include <iostream>
#include <ratio>
#include <stdexcept>

void sdlCheck(bool success)
{
    if (!success) {
        throw std::runtime_error{SDL_GetError()};
    }
}

template <class T>
T* sdlCheck(T* ptr)
{
    if (!ptr) {
        throw std::runtime_error{SDL_GetError()};
    }
    return ptr;
}

int main(int argc, char* argv[])
{
    sdlCheck(SDL_Init(SDL_INIT_VIDEO));
    auto window = sdlCheck(SDL_CreateWindow("Stick Finger", 800, 600, 0));
    auto renderer = sdlCheck(SDL_CreateRenderer(window, nullptr));

    sdlCheck(SDL_RenderClear(renderer));
    sdlCheck(SDL_RenderPresent(renderer));

    using Clock = std::chrono::high_resolution_clock;
    auto times = std::array<Clock::time_point, 2>{};
    size_t timeIndex = 0;

    for (auto event = SDL_Event{}; SDL_WaitEvent(&event); ) {
        if (event.type != SDL_EVENT_KEY_DOWN) {
            continue;
        }

        times.at(timeIndex) = Clock::now();
        timeIndex = (timeIndex + 1) % times.size();

        if (event.key.key == SDLK_ESCAPE) {
            break;
        }

        if (timeIndex == 0) {
            auto [minTime, maxTime] = std::ranges::minmax(times);
            auto gapSeconds = std::chrono::duration_cast<
                std::chrono::duration<double, std::milli>>(
                    maxTime - minTime).count();
            std::cout << "gap: " << gapSeconds << " ms" << std::endl;
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
}
