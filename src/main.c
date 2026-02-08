#include "raylib.h"

#define WIDTH 2400
#define HEIGHT 1450
#define DEFAULT_BRUSH_SIZE 25
#define COLOR_PALETTE_POS 50
#define FONT_SIZE 40
#define NUMBERS_X_Y_POS 10

Color palette[] = {WHITE, RED, BLUE, GREEN, YELLOW, PINK, PURPLE};
const int number_colors = sizeof(palette) / sizeof(Color);

void draw_to_screen(const Color c, const int bs) {
    Vector2 mouse_pos = GetMousePosition();
    if (mouse_pos.x < (COLOR_PALETTE_POS * number_colors) && mouse_pos.y < COLOR_PALETTE_POS) {
        return;
    }
    DrawCircleV(mouse_pos, bs, c);
}

void erase_from_screen(const int bs) {
    Vector2 mouse_pos = GetMousePosition();
    if (mouse_pos.x < (COLOR_PALETTE_POS * number_colors) && mouse_pos.y < COLOR_PALETTE_POS) {
        return;
    }
    DrawCircleV(mouse_pos, bs, BLACK);
}

void change_color_keyboard(Color* c, int* i) {
    if (IsKeyPressed(KEY_ZERO)) {
        *c = WHITE;
        *i = 0;
    } else if (IsKeyPressed(KEY_ONE)) {
        *c = RED;
        *i = 1;
    } else if (IsKeyPressed(KEY_TWO)) {
        *c = BLUE;
        *i = 2;
    } else if (IsKeyPressed(KEY_THREE)) {
        *c = GREEN;
        *i = 3;
    } else if (IsKeyPressed(KEY_FOUR)) {
        *c = YELLOW;
        *i = 4;
    } else if (IsKeyPressed(KEY_FIVE)) {
        *c = PINK;
        *i = 5;
    } else if (IsKeyPressed(KEY_SIX)) {
        *c = PURPLE;
        *i = 6;
    }
}

void change_color_button(const Rectangle* buttons, Color* c, int* ci) {
    Vector2 mouse_pos = GetMousePosition();
    for (int i = 0; i < number_colors; i++) {
        if ((mouse_pos.x >= buttons[i].x && mouse_pos.x <= buttons[i].x + buttons[i].width) &&
            (mouse_pos.y >= buttons[i].y && mouse_pos.y <= buttons[i].y + buttons[i].height)) {
            *ci = i;
            switch (i) {
            case 0:
                *c = WHITE;
                break;
            case 1:
                *c = RED;
                break;
            case 2:
                *c = BLUE;
                break;
            case 3:
                *c = GREEN;
                break;
            case 4:
                *c = YELLOW;
                break;
            case 5:
                *c = PINK;
                break;
            case 6:
                *c = PURPLE;
                break;
            default:
                break;
            }
        }
    }
}

void change_brush_size(int* bs) {
    float mouse_wheel = GetMouseWheelMove();
    if (IsKeyDown(KEY_LEFT_CONTROL) && mouse_wheel != 0) {
        if (mouse_wheel > 0) {
            if (*bs < 50) {
                *bs += 1;
            }
        } else {
            if (*bs > 5) {
                *bs -= 1;
            }
        }
    }
}

void create_color_buttons(Rectangle* p) {
    for (int i = 0; i < number_colors; i++) {
        p[i].width = COLOR_PALETTE_POS;
        p[i].height = COLOR_PALETTE_POS;
        p[i].x = COLOR_PALETTE_POS * i;
        p[i].y = 0;
    }
}

void draw_colors(const int c, const Rectangle* p) {
    for (int i = 0; i < number_colors; i++) {
        DrawRectangleRec(p[i], palette[i]);
        if (c == i) {
            DrawText(TextFormat("%d", i), NUMBERS_X_Y_POS + (COLOR_PALETTE_POS * i),
                     NUMBERS_X_Y_POS, FONT_SIZE, GOLD);
        } else {
            DrawText(TextFormat("%d", i), NUMBERS_X_Y_POS + (COLOR_PALETTE_POS * i),
                     NUMBERS_X_Y_POS, FONT_SIZE, BLACK);
        }
    }
}

int main() {
    InitWindow(WIDTH, HEIGHT, "Paint");
    SetTargetFPS(60);

    Rectangle palette_buttons[number_colors];
    Color current_color = WHITE;
    int current_color_int = 0;
    int brush_size = DEFAULT_BRUSH_SIZE;

    create_color_buttons(palette_buttons);

    while (!WindowShouldClose()) {
        change_color_keyboard(&current_color, &current_color_int);
        change_brush_size(&brush_size);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            change_color_button(palette_buttons, &current_color, &current_color_int);
        }

        BeginDrawing();

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            draw_to_screen(current_color, brush_size);
        }

        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
            erase_from_screen(brush_size);
        }

        if (IsKeyDown(KEY_R)) {
            ClearBackground(BLACK);
        }

        draw_colors(current_color_int, palette_buttons);

        EndDrawing();
    }
    CloseWindow();
}