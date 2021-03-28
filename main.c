#include <SFML/Graphics.h> // Graphics stuff
#include <stdbool.h> // boolean values
#include <stdio.h> // printf

#define KEYSIZE 75

typedef struct {
    const char* str;
    bool pressed;
    sfVector2f pos;
    sfKeyCode keyCode;
} key;
 
int main() {
    sfVideoMode mode = {600, 400, 32};
    sfRenderWindow* window;
    sfRectangleShape* rect;
    sfEvent event;
    
    key keys[6];
    
    // Initializing every key to being not pressed
    for(int i = 0; i < sizeof(keys)/sizeof(keys[0]); i++) { keys[i].pressed = false; }
    // Hard coded values lmao
    // Size will probably also be hard coded to 50 as long as everything else it set to hard coded values
    keys[0].keyCode = sfKeyNumpad8; // Up
    keys[0].pos.x = KEYSIZE*4;
    keys[0].pos.y = 0;
    keys[1].keyCode = sfKeyNumpad4; // Left
    keys[1].pos.x = KEYSIZE*3;
    keys[1].pos.y = KEYSIZE;
    keys[2].keyCode = sfKeyNumpad5; // Down
    keys[2].pos.x = KEYSIZE*4;
    keys[2].pos.y = KEYSIZE;
    keys[3].keyCode = sfKeyNumpad6; // Right
    keys[3].pos.x = KEYSIZE*5;
    keys[3].pos.y = KEYSIZE;
    keys[4].keyCode = sfKeyX;
    keys[4].pos.x = 0;
    keys[4].pos.y = KEYSIZE;
    keys[5].keyCode = sfKeyC;
    keys[5].pos.x = KEYSIZE;
    keys[5].pos.y = KEYSIZE;

    /* Create the main window */
    window = sfRenderWindow_create(mode, "SFML window", sfResize | sfClose, NULL);
    if (!window)
        return 1;
    
    // Framerate cap so that it doesnt use up all of a single thread on my garbage i3-3240 lmao
    // This is still over my monitor's refresh rate so it doesnt really matter besides just not going at 2 billion fps
    sfRenderWindow_setFramerateLimit(window, 200);
    
    rect = sfRectangleShape_create();
    sfVector2f size = {KEYSIZE, KEYSIZE};
    sfRectangleShape_setSize(rect, size);
 
    /* Start the game loop */
    while (sfRenderWindow_isOpen(window))
    {
        /* Process events */
        while (sfRenderWindow_pollEvent(window, &event))
        {
            /* Close window : exit */
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
            
            switch(event.type){
                case sfEvtKeyPressed:
                    switch(event.key.code){
                        case sfKeyQ:
                        case sfKeyEscape:
                            sfRenderWindow_close(window);
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
        }

        /* Clear the screen */
        sfRenderWindow_clear(window, sfColor_fromRGB(32,32,32));
 
        //sfRenderWindow_drawRectangleShape(window, rect, NULL);
        for(int i = 0; i < sizeof(keys)/sizeof(key); i++){
            sfRectangleShape_setPosition(rect, keys[i].pos);
            
            if(sfKeyboard_isKeyPressed(keys[i].keyCode)){
                sfRectangleShape_setFillColor(rect, sfColor_fromInteger(0x00659FFF));
            } else {
                sfRectangleShape_setFillColor(rect, sfColor_fromInteger(0x00A2FFFF));
            }
            
            sfRenderWindow_drawRectangleShape(window, rect, NULL);
        }
        
 
        /* Update the window */
        sfRenderWindow_display(window);
    }

    /* Cleanup resources */
    sfRectangleShape_destroy(rect);
    sfRenderWindow_destroy(window);

    return 0;
}
