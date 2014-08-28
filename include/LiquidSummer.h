#ifndef LIQUID_SUMMER_LIQUID_SUMMER_H
#define LIQUID_SUMMER_LIQUID_SUMMER_H

#include <string>
#include <chrono>

#include <SDL.h>
#include <SDL_ttf.h>

class LiquidSummer
{
	private:
		
		static const int SCREEN_WIDTH  = 640;
		static const int SCREEN_HEIGHT = 480;
		
		const std::string projectName = "liquid-summer";
		//const std::string imageName = "image.png";
		const std::string fontName = "Cousine-Regular.ttf";
		
		bool sdlLibraryInitialized = false;
		bool sdlImageLibraryInitialized = false;
		bool sdlTtfLibraryInitialized = false;
		bool sdlWindowCreated = false;
		bool sdlRendererCreated = false;
		bool sdlTextureCreated = false;
		bool sdlFontOpen = false;
		
		SDL_Window * sdlWindow = nullptr;
		SDL_Renderer * sdlRenderer = nullptr;
		SDL_Texture * sdlTexture = nullptr;
		TTF_Font * sdlFont = nullptr;
		
		std::string resourcePath = "";
		
		bool quit = false;
		int spriteId = 0;
		
		int spriteWidth = 100;
		int spriteHeight = 100;
		int x = SCREEN_WIDTH / 2;
		int y = SCREEN_HEIGHT / 2;
		int mouseXLeft = x;
		int mouseYLeft = y;
		int mouseXRight = x;
		int mouseYRight = y;
		bool mousePressed = false;
		bool mouseValidLeft = false;
		bool mouseValidRight = false;
		int displayedStarField = 2;
		
		int elapsedFrames = 0;
		std::chrono::high_resolution_clock::time_point chronoStart;
		std::chrono::high_resolution_clock::time_point chronoLastStartOfFrameLoop;
		std::chrono::high_resolution_clock::duration chronoElapsed;
		long long chronoElapsedInMicroseconds = 0;
		float framesPerSecond = 0;
		
	public:
		
		LiquidSummer();
		~LiquidSummer();
		void run( void );
		
	private:
		
		void openSdl( void );
		void openSdlBase( void );
		void openSdlImage( void );
		void openSdlTtf( void );
		void closeSdl( void );
		void closeSdlBase( void );
		void closeSdlImage( void );
		void closeSdlTtf( void );
		
		void initResourcePaths( void );

		void createWindow( void );
		void createRenderer( void );
		void createTexture( void );
		void destroyWindow( void );
		void destroyRenderer( void );
		void destroyTexture( void );
		void openFont( void );
		void closeFont( void );
		
		void renderTexture( SDL_Texture *, SDL_Renderer *, SDL_Rect destinationRectangle, SDL_Rect * sourceRectangle = nullptr );
		void renderTexture( SDL_Texture *, SDL_Renderer *, int x, int y, SDL_Rect * sourceRectangle = nullptr );
		
		void startChrono( void );
		void updateChrono( void );
		void processEvents( void );
		void renderFrame( void );
		
		std::string getResourcePath( const std::string & subDir = "" );
		SDL_Texture * renderText( const std::string & message, SDL_Color color );
		
		void drawStarField( void );
		void drawDebug( void );
};

#endif
