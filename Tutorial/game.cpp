#include "game.h"
#include "surface.h"
#include "template.h"
#include "windows.h"

namespace Tmpl8
{
    void Game::Init() {}

    void Game::Shutdown() {}


    float x[2] = { 335, 320 }, y[2] = { 0, ScreenHeight - 50 }; //current coord
    float px[2] = { 335, 320 }, py[2] = { 0, ScreenHeight - 50 }; //old coords

    void Game::Tick(float deltaTime)
    {
        screen->Clear(0);
        Circle(screen, x[0], y[0], 16);
        Circle(screen, x[1], y[1], 49);
        // compute deltas.
        float dx = x[0] - px[0], dy = y[0] - py[0]; //calculates difference in coords, this is velocity
        float dx2 = x[1] - px[1], dy2 = y[1] - py[1];
        // store previous position.
        px[0] = x[0], py[0] = y[0];
        px[1] = x[1], py[1] = y[1];
        // Verlet integration
        x[0] += dx;
        y[0] += dy;
        x[1] += dx2;
        y[1] += dy2;
        // add force due to gravity.
        y[0] += 0.5f;
        y[1] += 0.5f;
        //constraints
        if (y[0] > (ScreenHeight - 17))
            py[0] = y[0], y[0] = ScreenHeight - 17;
        if (y[1] > (ScreenHeight - 50))
            py[1] = y[1], y[1] = ScreenHeight - 50;
        float xdist = x[1] - x[0];
        float ydist = y[1] - y[0];
        float distance = sqrtf(xdist * xdist + ydist * ydist);
        if (distance < (16 + 49))
        {
            float fix = (16 + 49) - distance;
            float fraction = fix / distance;
            x[0] -= (0.9 * (fraction * xdist));
            y[0] -= 0.9 * (fraction * ydist);
            x[1] += 0.1 * (fraction * xdist);
            y[1] += 0.1 * (fraction * ydist);
        }
        // delay
        Sleep(50);
    }

    void Game::Circle(Surface* s, float x, float y, float r)
    {
        for (int i = 0; i < 64; i++)
        {
            float r1 = (float)i * PI / 32, r2 = (float)(i + 1) * PI / 32;
            s->Line(x - r * sinf(r1), y - r * cosf(r1),
                x - r * sinf(r2), y - r * cosf(r2), 0xff0000);
        }
    }

};