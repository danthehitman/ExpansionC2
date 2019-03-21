#include "src\graphics\window.h"
#include "src\math\maths.h"
#include "src\graphics\shader.h"

#include "src/graphics/buffers/buffer.h"
#include "src/graphics/buffers/indexbuffer.h"
#include "src/graphics/buffers/vertexarray.h"

#include "src\graphics\renderer2d.h"
#include "src\graphics\simple2drenderer.h"
#include "src\graphics\batchrenderer2d.h"

#include "src\graphics\staticsprite.h"
#include "src\graphics\sprite.h"
#include "src/utils/timer.h"

#include "src\graphics\layers\tilelayer.h"

#include <time.h>

#define BATCH_RENDERER 1
#define TEST_50K_SPRITES 0


//int main()
//{
//    using namespace ec2;
//    using namespace graphics;
//    using namespace maths;
//
//    Window window("EC2", 960, 540);
//    //glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//
//    mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
//
//    Shader* s = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
//    Shader shader = *s;
//    shader.enable();
//    shader.setUniform2f("light_pos", vec2(4.0f, 1.5f));
//
//    TileLayer layer(s);
//
//    for (float y = -9.0f; y < 9.0f; y+= 0.1)
//    {
//        for (float x = -16.0f; x < 16.0f; x += 0.1)
//        {
//            layer.add(new Sprite(x, y, 0.09f, 0.09f, maths::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
//        }
//    }
//
//    Timer time;
//    float t = 0;
//    unsigned int frames = 0;
//
//    while (!window.closed())
//    {
//        window.clear();
//        double x, y;
//        window.getMousePosition(x, y);
//        shader.enable();
//        shader.setUniform2f("light_pos", vec2((float)(x * 32.0f / 960.0f - 16.0f), (float)(9.0f - y * 18.0f / 540.0f)));
//
//        layer.render();
//
//        window.update();
//        frames++;
//        if (time.elapsed() - t > 1.0f)
//        {
//            t += 1.0f;
//            printf("%d fps\n", frames);
//            frames = 0;
//        }
//    }
//
//    return 0;
//}

int main()
{
    using namespace ec2;
    using namespace graphics;
    using namespace maths;

    Window window("Sparky!", 960, 540);
    // glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

    Shader* s = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
    Shader* s2 = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
    Shader& shader = *s;
    Shader& shader2 = *s2;
    shader.enable();
    shader2.enable();
    shader.setUniform2f("light_pos", vec2(4.0f, 1.5f));
    shader2.setUniform2f("light_pos", vec2(4.0f, 1.5f));

    TileLayer layer(&shader);

#if TEST_50K_SPRITES
    for (float y = -9.0f; y < 9.0f; y += 0.1)
    {
        for (float x = -16.0f; x < 16.0f; x += 0.1)
        {
            layer.add(new Sprite(x, y, 0.09f, 0.09f, maths::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
        }
    }

#else
    Sprite* button = new Sprite(-15.0f, 5.0f, 6, 3, maths::vec4(1, 1, 1, 1));
    layer.add(button);
    //layer.push(maths::mat4(button->getPosition()));
    layer.add(new Sprite(0.5f, 0.5f, 5.0f, 2.0f, maths::vec4(1, 0, 1, 1)));
    //layer.pop();

#endif

    TileLayer layer2(&shader2);
    layer2.add(new Sprite(-2, -2, 4, 4, maths::vec4(1, 0, 1, 1)));

    Timer time;
    float timer = 0;
    unsigned int frames = 0;

    while (!window.closed())
    {
        window.clear();
        double x, y;
        window.getMousePosition(x, y);
        shader.enable();
        shader.setUniform2f("light_pos", vec2((float)(x * 32.0f / 960.0f - 16.0f), (float)(9.0f - y * 18.0f / 540.0f)));
        //shader.setUniform2f("light_pos", vec2((float)(x * 32.0f / 960.0f - 16.0f), (float)(9.0f - y * 18.0f / 540.0f)));
        //shader.setUniform2f("light_pos", vec2(-8, -3));
        shader2.enable();

        layer.render();
        //layer2.render();

        window.update();
        frames++;
        if (time.elapsed() - timer > 1.0f)
        {
            timer += 1.0f;
            printf("%d fps\n", frames);
            frames = 0;
        }
    }

    return 0;
}


//int main()
//{    
//    using namespace ec2;
//    using namespace graphics;
//    using namespace maths;
//
//    Window window("EC2", 960, 540);
//    //glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//
//    mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
//
//    Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
//    shader.enable();
//    shader.setUniformMat4("pr_matrix", ortho);
//
//    std::vector<Renderable2D*> sprites;
//    srand(time(NULL));
//
//    for (float y = 0; y < 9.0f; y+= 0.05)
//    {
//        for (float x = 0; x < 16.0f; x += 0.05)
//        {
//            sprites.push_back(new 
//#if BATCH_RENDERER
//                Sprite
//#else
//                StaticSprite
//#endif
//                (x, y, 0.04f, 0.04f, maths::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)
//#if !BATCH_RENDERER
//                    , shader
//#endif                    
//                    ));
//        }
//    }
//
//
//#if BATCH_RENDERER
//    Sprite sprite1(5, 5, 4, 4, maths::vec4(1, 0, 1, 1));
//    Sprite sprite2(7, 1, 2, 3, maths::vec4(0.2f, 0, 1, 1));
//    BatchRenderer2D renderer;
//
//#else
//    StaticSprite sprite1(5, 5, 4, 4, maths::vec4(1, 0, 1, 1), shader);
//    StaticSprite sprite2(7, 1, 2, 3, maths::vec4(0.2f, 0, 1, 1), shader);
//    Simple2DRenderer renderer;
//#endif
//
//    shader.setUniform2f("light_pos", vec2(4.0f, 1.5f));
//    shader.setUniform4f("customColor", vec4(0.2f, 0.3f, 0.8f, 1.0f));
//
//    Timer time;
//    float t = 0;
//    unsigned int frames = 0;
//
//    while (!window.closed())
//    {
//        window.clear(); 
//
//        mat4 mat = mat4::translation(vec3(5, 5, 5));
//        mat = mat * mat4::rotation(time.elapsed() * 100, vec3(0, 0, 1));
//        mat = mat * mat4::translation(vec3(-5, -5, -5));
//        shader.setUniformMat4("ml_matrix", mat);
//        
//        double x, y;
//        window.getMousePosition(x, y);
//        shader.setUniform2f("light_pos", vec2((float)(x * 16.0f / 960.0f), (float)(9.0f - y * 9.0f / 540.0f)));
//#if BATCH_RENDERER
//        renderer.begin();
//#endif
//        for (int i = 0; i < sprites.size(); i++)
//        {
//            renderer.submit(sprites[i]);
//        }
//        /*renderer.submit(&sprite1);
//        renderer.submit(&sprite2);*/
//#if BATCH_RENDERER
//        renderer.end();
//#endif
//        renderer.flush();
//
//        window.update();
//        frames++;
//        if (time.elapsed() - t > 1.0f)
//        {
//            t += 1.0f;
//            printf("%d fps\n", frames);
//            frames = 0;
//        }
//    }
//
//    return 0;
//}