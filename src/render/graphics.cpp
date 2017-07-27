#include "graphics.h" 
#include "utils/math.h"
#include <string>
namespace jin
{
namespace render
{

    void point(int x, int y)
    {
        float vers[] = { x + 0.5f , y + 0.5f };
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(2, GL_FLOAT, 0, (GLvoid*)vers);
        glDrawArrays(GL_POINTS, 0, 1);
        glDisableClientState(GL_VERTEX_ARRAY);
    }

    void points(int n, GLshort* p)
    {
        glEnableClientState(GL_VERTEX_ARRAY);

        glVertexPointer(2, GL_SHORT, 0, (GLvoid*)p);
        glDrawArrays(GL_POINTS, 0, n);

        glDisableClientState(GL_VERTEX_ARRAY);
    }

    void line(int x1, int y1, int x2, int y2)
    {
        glDisable(GL_TEXTURE_2D);
        float verts[] = {
            x1, y1,
            x2, y2
        };

        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(2, GL_FLOAT, 0, (GLvoid*)verts);
        glDrawArrays(GL_LINES, 0, 2);
        glDisableClientState(GL_VERTEX_ARRAY);
    }

    void circle(RENDER_MODE mode, int x, int y, int r)
    {
        r = r < 0 ? 0 : r;

        int points = 40;
        float two_pi = static_cast<float>(PI * 2);
        if (points <= 0) points = 1;
        float angle_shift = (two_pi / points);
        float phi = .0f;

        float *coords = new float[2 * (points + 1)];
        for (int i = 0; i < points; ++i, phi += angle_shift)
        {
            coords[2 * i] = x + r * cos(phi);
            coords[2 * i + 1] = y + r * sin(phi);
        }

        coords[2 * points] = coords[0];
        coords[2 * points + 1] = coords[1];

        polygon(mode, coords, points);

        delete[] coords;
    }

    void rect(RENDER_MODE mode, int x, int y, int w, int h)
    {
        float coords[] = { x, y, x + w, y, x + w, y + h, x, y + h };
        polygon(mode, coords, 4);
    }

    void triangle(RENDER_MODE mode, int x1, int y1, int x2, int y2, int x3, int y3)
    {
        float coords[] = { x1, y1, x2, y2, x3, y3 };
        polygon(mode, coords, 3);
    }

    void polygon_line(float* p, int count)
    {
        float* verts = new float[count * 4];
        for (int i = 0; i < count; i++)
        {
            // each line has two point n,n+1
            verts[i * 4] = p[i * 2];
            verts[i * 4 + 1] = p[i * 2 + 1];
            verts[i * 4 + 2] = p[(i + 1) % count * 2];
            verts[i * 4 + 3] = p[(i + 1) % count * 2 + 1];
        }

        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(2, GL_FLOAT, 0, (GLvoid*)verts);
        glDrawArrays(GL_LINES, 0, count * 2);
        glDisableClientState(GL_VERTEX_ARRAY);

        delete[] verts;
    }

    void polygon(RENDER_MODE mode, float* p, int count)
    {
        if (mode == LINE)
        {
            polygon_line(p, count);
        }
        else if (mode == FILL)
        {
            glEnableClientState(GL_VERTEX_ARRAY);
            glVertexPointer(2, GL_FLOAT, 0, (const GLvoid*)p);
            glDrawArrays(GL_POLYGON, 0, count);
            glDisableClientState(GL_VERTEX_ARRAY);
        }
    }

}
}
