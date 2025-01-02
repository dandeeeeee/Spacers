#include "raylib.h"
#include "raymath.h"

#define MIN(a,b) (((a)<(b))?(a):(b))

enum WindowState
{
    HOME,
    GAME,
    SETTINGS
};

class Window
{
private:
    Camera2D camera;
    RenderTexture2D target;
    Shader shader;
    int gameScreenWidth, gameScreenHeight;
    WindowState windowState;


private:
    void home();
    void game();
    void settings();


public:
    Window(int width, int height, const char* title)
        : gameScreenWidth(640), gameScreenHeight(480), windowState(HOME)
    {
        SetConfigFlags(FLAG_WINDOW_RESIZABLE);
        InitWindow(width, height, title);
        SetTargetFPS(60);

        camera = { 0 };
        camera.target = Vector2{ 0, 0 };
        camera.offset = Vector2{ (float)GetScreenWidth()/2, (float)GetScreenHeight()/2 };
        camera.rotation = 0.0f;
        camera.zoom = 1.0f;

        target = LoadRenderTexture(gameScreenWidth, gameScreenHeight);
        SetTextureFilter(target.texture, TEXTURE_FILTER_BILINEAR);
        // shader = LoadShader(0, TextFormat("resources/shaders/glsl%i/base.fs", 330));
    }


    void run()
    {
        while (!WindowShouldClose())
        {
            // Adjusts mouse input to match the game screen
            float scale = MIN((float)GetScreenWidth()/gameScreenWidth, (float)GetScreenHeight()/gameScreenHeight);
            Vector2 mouse = GetMousePosition();
            Vector2 virtualMouse = { 0 };
            virtualMouse.x = (mouse.x - (GetScreenWidth() - (gameScreenWidth*scale))*0.5f)/scale;
            virtualMouse.y = (mouse.y - (GetScreenHeight() - (gameScreenHeight*scale))*0.5f)/scale;
            virtualMouse = Vector2Clamp(virtualMouse, { 0, 0 }, { (float)gameScreenWidth, (float)gameScreenHeight });
            SetMouseOffset(-(GetScreenWidth() - (gameScreenWidth*scale))*0.5f, -(GetScreenHeight() - (gameScreenHeight*scale))*0.5f);
            SetMouseScale(1/scale, 1/scale);

            BeginTextureMode(target);
                ClearBackground(RAYWHITE);
                switch(windowState)
                {
                    case HOME:
                        home();
                        break;
                    case GAME:
                        game();
                        break;
                    case SETTINGS:
                        settings();
                        break;
                }
            EndTextureMode();

            BeginDrawing();
                ClearBackground(BLACK);
                DrawTexturePro(target.texture, Rectangle{ 0.0f, 0.0f, (float)target.texture.width, (float)-target.texture.height },
                            Rectangle{ (GetScreenWidth() - ((float)gameScreenWidth*scale))*0.5f, (GetScreenHeight() - ((float)gameScreenHeight*scale))*0.5f,
                            (float)gameScreenWidth*scale, (float)gameScreenHeight*scale }, Vector2{ 0, 0 }, 0.0f, WHITE);
            EndDrawing();
        }
    }

    ~Window()
    {
        // UnloadShader(shader);
        UnloadRenderTexture(target);
        CloseWindow();
    }
};