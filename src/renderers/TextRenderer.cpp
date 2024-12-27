#include "TextRenderer.h"

TextRenderer::TextRenderer() {
    textFont = LoadFontEx(FONT_FILE_NAME, 16, 0, 250);
}

TextRenderer::~TextRenderer() {
    UnloadFont(textFont);
}

void TextRenderer::render(ECS::World *world) {
    for (auto ent : world->each<TextComponent>()) {
        auto textComponent = ent->get<TextComponent>();

        std::string s = std::to_string(textComponent->getValue());
        std::string additionalString = "";

        switch (textComponent->type) {
            case Text::Type::SCORE_COUNTER:
                for (int i = 0; i < 10 - s.length(); i++)
                    additionalString += "0";
                s = additionalString + s;
                break;
            case Text::Type::COIN_COUNTER:
                s = "x " + s;
                break;
            case Text::Type::TIMER:
                renderTimerTextComponents(world);
                break;
            default:
                break;
        }

        const char *pchar = s.c_str();

        DrawTextEx(textFont, pchar, textComponent->position, textFont.baseSize, 1, RED);
    }
}

void TextRenderer::renderScoreTextComponents(ECS::World *world) {
    world->each<GameTextComponent>([&](
            ECS::Entity* entity,
            ECS::ComponentHandle<GameTextComponent> gameTextComponent) {
        if (!gameTextComponent->destroy()) {;
            const char* pchar = gameTextComponent->text.c_str();

            DrawTextEx(textFont, pchar, gameTextComponent->position, 12, 1, WHITE);
        }
    });
}

void TextRenderer::renderTimerTextComponents(ECS::World *world) {
    static auto lastUpdateTime = std::chrono::steady_clock::now();
    //std:: cout << "Last update time: " << std::chrono::duration_cast<std::chrono::seconds>(lastUpdateTime.time_since_epoch()).count() << std::endl;
    world->each<TimerComponent, TextComponent>([&](
            ECS::Entity* entity,
            ECS::ComponentHandle<TimerComponent> timerComponent,
            ECS::ComponentHandle<TextComponent> textComponent) {
                std::cout << "Timer component: " << timerComponent->time << std::endl;
        if (timerComponent->active) {
            // Calculate the elapsed time
            auto currentTime = std::chrono::steady_clock::now();
            auto elapsedSeconds = std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastUpdateTime).count();

            std:: cout << "Elapsed seconds: " << elapsedSeconds << std::endl;

            // Update the timer
            if (elapsedSeconds > 0) {
                timerComponent->time -= elapsedSeconds;
                lastUpdateTime = currentTime; // Reset the last update time

                // Ensure timer doesn't go below zero
                if (timerComponent->time < 0) {
                    timerComponent->time = 0;
                    timerComponent->active = false; // Deactivate the timer if it reaches zero
                }
            }

            // Convert the timer value to string and render it
            std::string s = std::to_string(timerComponent->time);
            const char *pchar = s.c_str();

            DrawTextEx(textFont, pchar, textComponent->position, textFont.baseSize, 1, RED);
        }
    });
}
