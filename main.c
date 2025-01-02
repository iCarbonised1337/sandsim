#include <raylib.h>
#include <stdio.h>
#include <raymath.h>

// Defining functions
int signf(float x) {
    return (x > 0.0f) - (x < 0.0f);
}
//------------------------------------------------------------------------------------
typedef struct particle {
    float mass; // particle mass
    float drag; // drag coeffiecent experienced
    Vector2 pos;
    Vector2 vel; // initialising the velocity vector
    Vector2 accel; // current acceleration of the particle
    Vector2 friction; // acceleration due to friction, NOT the frictional force itself
    Vector2 forceDirn; /*The direction the ball will accelerate in*/
} particle;
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    float radius = 10; // radius of the balls
    float push = 1000; // px per frametime
    float coeff_restitution = 0.5;
    float speed = 0; // current speed of the particle
    float DelT; // frametime of current frame
    Color Teal = {0, 128, 128, 255}; // The color teal

    particle ball; // creating a ball
    ball.mass = 1;
    ball.drag = 0.5;

    ball.pos.x = 100;
    ball.pos.y = 100;
    char string_speed[5]= ""; //string to store the speed as a string
    
    //float max_speed = 1000;
    InitWindow(screenWidth, screenHeight, "SandSim");
    // InitAudioDevice();
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    //--------------------------------------------------------------------------------------
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
    // Event Handling
        //----------------------------------------------------------------------------------
    
    DelT = GetFrameTime();
    
    ball.forceDirn = Vector2Zero(); // reset the force direction vector for this frame

    if (IsKeyDown(KEY_W))
    {
        ball.forceDirn.y -= 1;
    }
    if (IsKeyDown(KEY_A))
    {
        ball.forceDirn.x -= 1;
    }
    if (IsKeyDown(KEY_S))
    {
        ball.forceDirn.y += 1;
    }
    if (IsKeyDown(KEY_D))
    {
        ball.forceDirn.x += 1;
    }
    if (IsKeyDown(KEY_SPACE))
    {
        ball.vel = Vector2Zero();
    }

    // Normalise the forceDirn vector
    ball.forceDirn = Vector2Normalize(ball.forceDirn);

    // now the acceleration will be the same in all directions, i.e moving diagonally wont give you 1.41 times the max force
    ball.accel = Vector2Scale(ball.forceDirn, push/ball.mass);

    //Check if ball is inside the frame in X and Y seperately
    if ( (ball.pos.x+(radius)>screenWidth))
    {
        ball.pos.x = screenWidth-radius;
        ball.vel.x-=(1+coeff_restitution)*ball.vel.x;
    }
    if ((ball.pos.x < radius))
    {
        ball.pos.x = radius;
        ball.vel.x-=(1+coeff_restitution)*ball.vel.x;
    }
    
    if ((ball.pos.y+(radius)>screenHeight))
    {
        ball.pos.y = screenHeight-radius;
        ball.vel.y-=(1+coeff_restitution)*ball.vel.y;
    }
    if ((ball.pos.y < radius))
    {
        ball.pos.y = radius;
        ball.vel.y-=(1+coeff_restitution)*ball.vel.y;
    }


    // make friction work
        ball.friction.x = -ball.drag*ball.vel.x;
        ball.friction.y = -ball.drag*ball.vel.y;
        //----------------------------------------------------------------------------------
    // Update
        //----------------------------------------------------------------------------------
    ball.vel = Vector2Add(Vector2Scale(Vector2Add(ball.accel,ball.friction),DelT),ball.vel);
    ball.pos.x += ball.vel.x*DelT;
    ball.pos.y += ball.vel.y*DelT;
    ball.accel = Vector2Zero();
    // speed calculation for displaying
    speed = Vector2Length(ball.vel);

        //----------------------------------------------------------------------------------
    // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(BLACK);
            sprintf(string_speed,"%0.0f", speed);
            DrawText(string_speed,0,0,20,WHITE);
            DrawCircle(ball.pos.x,ball.pos.y,radius,Teal);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    // CloseAudioDevice();
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}