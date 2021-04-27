#include <SFML/Graphics.h> // Graphics stuff
#include <stdbool.h> // boolean values
#include <stdio.h> // printf

typedef struct {
	// Drawn size
	sfVector2f size;
	// Texture coordinates
	sfIntRect unpressedRect, pressedRect;
	// Drawn position
	sfVector2f pos;
	// SFML key for when it's checked if it's pressed
	sfKeyCode keyCode;
} key;

// Really bad hard coded values lmao
key keys[] = {
	{ // W
		.size = {.x=128,.y=128},
		.unpressedRect={.left=0,.top=0,.width=128,.height=128},
		.pressedRect={.left=0,.top=128,.width=128,.height=128},
		.pos={.x=128,.y=0},
		.keyCode=sfKeyW,
	},
	{ // A
		.size = {.x=128,.y=128},
		.unpressedRect={.left=128,.top=0,.width=128,.height=128},
		.pressedRect={.left=128,.top=128,.width=128,.height=128},
		.pos={.x=0,.y=128},
		.keyCode=sfKeyA,
	},
	{ // S
		.size = {.x=128,.y=128},
		.unpressedRect={.left=256,.top=0,.width=128,.height=128},
		.pressedRect={.left=256,.top=128,.width=128,.height=128},
		.pos={.x=128,.y=128},
		.keyCode=sfKeyS,
	},
	{ // D
		.size = {.x=128,.y=128},
		.unpressedRect={.left=384,.top=0,.width=128,.height=128},
		.pressedRect={.left=384,.top=128,.width=128,.height=128},
		.pos={.x=256,.y=128},
		.keyCode=sfKeyD,
	},
	{ // V
		.size = {.x=128,.y=128},
		.unpressedRect={.left=512,.top=0,.width=128,.height=128},
		.pressedRect={.left=512,.top=128,.width=128,.height=128},
		.pos={.x=0,.y=256},
		.keyCode=sfKeyV,
	},
	{ // R
		.size = {.x=128,.y=128},
		.unpressedRect={.left=640,.top=0,.width=128,.height=128},
		.pressedRect={.left=640,.top=128,.width=128,.height=128},
		.pos={.x=128,.y=256},
		.keyCode=sfKeyR,
	},
	{ // Enter
		.size = {.x=128,.y=128},
		.unpressedRect={.left=768,.top=0,.width=128,.height=128},
		.pressedRect={.left=768,.top=128,.width=128,.height=128},
		.pos={.x=256,.y=256},
		.keyCode=sfKeyEnter
	},
};
 
int main() {
	sfVideoMode mode = {600, 400, 32};
	sfRenderWindow* window;
	sfRectangleShape* rect;
	sfEvent event;
	
	sfTexture* keysTexture;
	keysTexture = sfTexture_createFromFile("res/keys.png", NULL);
	
	/* Create the main window */
	window = sfRenderWindow_create(mode, "SFML window", sfResize | sfClose, NULL);
	if (!window)
		return 1;
	
	// Framerate cap so that it doesnt use up all of a single thread on my garbage i3-3240 lmao
	// This is still over my monitor's refresh rate so it doesnt really matter besides just not going at 2 billion fps
	sfRenderWindow_setFramerateLimit(window, 200);
	
	rect = sfRectangleShape_create();
	sfRectangleShape_setTexture(rect, keysTexture, 0);
	
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
		
		for(int i = 0; i < sizeof(keys)/sizeof(key); i++){
			sfRectangleShape_setPosition(rect, keys[i].pos);
			sfRectangleShape_setSize(rect, keys[i].size);
			
			sfIntRect textureRect;
			
			// checking if the key is pressed
			if(sfKeyboard_isKeyPressed(keys[i].keyCode)){
				textureRect = keys[i].pressedRect;
			} else {
				textureRect = keys[i].unpressedRect;
			}
			
			sfRectangleShape_setTextureRect(rect, textureRect);
			
			sfRenderWindow_drawRectangleShape(window, rect, NULL);
		}
		
		
		/* Update the window */
		sfRenderWindow_display(window);
	}
	
	/* Cleanup resources */
	sfRectangleShape_destroy(rect);
	sfTexture_destroy(keysTexture);
	sfRenderWindow_destroy(window);
	
	return 0;
}
