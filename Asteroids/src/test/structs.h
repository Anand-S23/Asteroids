typedef struct {
    SDL_Renderer *renderer;
    SDL_Window *window;

	int up;
	int down; 
	int right; 
	int left; 
	int fire;
} App;


typedef struct {
	int x;
	int y;
	SDL_Texture* texture;
} Entity;