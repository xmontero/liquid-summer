#include "LiquidSummer.h"
#include "Math.h"
#include "StarField.h"

#include <iostream>
#include <string>
#include <chrono>
#include <cmath>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

using namespace std;

//-------------------------------------------------------------------------//
// Constructors                                                            //
//-------------------------------------------------------------------------//

// throw system_error( ENOSYS, system_category() );

#define CLASS "LiquidSummer"
#define VENTEREXIT(x) cout << x << " " << CLASS << "::" << __func__ /* << " (" << __FILE__ << ":" << __LINE__ << ")" */ << endl
#define VENTER VENTEREXIT( "Entering" )
#define VEXIT VENTEREXIT( "Exitting" )

LiquidSummer::LiquidSummer()
{
	VENTER;
	
	openSdl();
	initResourcePaths();
	createWindow();
	createRenderer();
	//createTexture();
	openFont();
	
	VEXIT;
}

LiquidSummer::~LiquidSummer( void )
{
	VENTER;
	
	closeFont();
	//destroyTexture();
	destroyRenderer();
	destroyWindow();
	closeSdl();
	
	VEXIT;
}

//-------------------------------------------------------------------------//
// Opening and closing SDL                                                 //
//-------------------------------------------------------------------------//

void LiquidSummer::openSdl( void )
{
	openSdlBase();
	openSdlImage();
	openSdlTtf();
}
	
void LiquidSummer::openSdlBase( void )
{
	if( SDL_Init( SDL_INIT_EVERYTHING ) != 0 )
	{
		throw "SDL_Init returned a non zero value.";
	}
	
	sdlLibraryInitialized = true;
}

void LiquidSummer::openSdlImage( void )
{
	int desiredMask = IMG_INIT_JPG | IMG_INIT_PNG;
	int enabledMask = 0;
	
	if( ( ( enabledMask = IMG_Init( desiredMask ) ) & desiredMask ) != desiredMask )
	{
		//throw "IMG_Init returned enabledMask:" << enabledMask << " with desiredMask:" << desiredMask;
		throw "IMG_Init returned enabledMask different from desiredMask.";
	}
	
	sdlImageLibraryInitialized = true;
}

void LiquidSummer::openSdlTtf( void )
{
	if( TTF_Init() != 0 )
	{
		throw "TTF_Init returned a non zero value.";
	}
	
	sdlTtfLibraryInitialized = true;
}

void LiquidSummer::closeSdl( void )
{
	closeSdlTtf();
	closeSdlImage();
	closeSdlBase();
}

void LiquidSummer::closeSdlBase( void )
{
	if( sdlLibraryInitialized )
	{
		SDL_Quit();
	}
}

void LiquidSummer::closeSdlImage( void )
{
	if( sdlImageLibraryInitialized )
	{
		IMG_Quit();
	}
}

void LiquidSummer::closeSdlTtf( void )
{
	if( sdlTtfLibraryInitialized )
	{
		TTF_Quit();
	}
}

//-------------------------------------------------------------------------//
// Resource location initializations                                       //
//-------------------------------------------------------------------------//

void LiquidSummer::initResourcePaths( void )
{
	resourcePath = getResourcePath( projectName );
}

//-------------------------------------------------------------------------//
// Windows, Renderer and Texture handling                                  //
//-------------------------------------------------------------------------//

void LiquidSummer::createWindow( void )
{
	sdlWindow = SDL_CreateWindow( projectName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	
	if( sdlWindow == nullptr )
	{
		throw "SDL_CreateWindow returned a nullptr.";
	}
}

void LiquidSummer::destroyWindow( void )
{
	if( sdlWindow )
	{
		SDL_DestroyWindow( sdlWindow );
	}
}

void LiquidSummer::createRenderer( void )
{
	sdlRenderer = SDL_CreateRenderer( sdlWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
	
	if( sdlRenderer == nullptr )
	{
		throw "SDL_CreateRenderer returned a nullptr.";
	}
}

void LiquidSummer::destroyRenderer( void )
{
	if( sdlRenderer )
	{
		SDL_DestroyRenderer( sdlRenderer );
	}
}

/*
void LiquidSummer::createTexture( void )
{
	const string filename = resourcePath + imageName;
	
	sdlTexture = IMG_LoadTexture( sdlRenderer, filename.c_str() );
	
	if( sdlTexture == nullptr )
	{
		throw "IMG_LoadTexture returned a nullptr.";
	}
}
*/

void LiquidSummer::destroyTexture( void )
{
	if( sdlTexture )
	{
		SDL_DestroyTexture( sdlTexture );
	}
}

void LiquidSummer::openFont( void )
{
	const string fontFile = resourcePath + fontName;
	const int fontSize = 9;
	
	sdlFont = TTF_OpenFont( fontFile.c_str(), fontSize );
	if( sdlFont == nullptr )
	{
		throw "TTF_OpenFont returned a nullptr.";
	}
}

void LiquidSummer::closeFont( void )
{
	if( sdlFont )
	{
		TTF_CloseFont( sdlFont );
	}
}

//-------------------------------------------------------------------------//
// Public                                                                  //
//-------------------------------------------------------------------------//

void LiquidSummer::run( void )
{
	VENTER;
	
	startChrono();
	
	while( ! quit )
	{
		updateChrono();
		processEvents();
		renderFrame();
	}
	
	VEXIT;
}

//-------------------------------------------------------------------------//
// Private                                                                 //
//-------------------------------------------------------------------------//

/*
 * Draw an SDL_Texture to an SDL_Renderer at some destination rect
 * taking a clip of the texture if desired
 * @param texture The source texture we want to draw
 * @param renderer The renderer we want to draw too
 * @param dst The destination rectangle to render the texture too
 * @param clip The sub-section of the texture to draw (clipping rect)
 *		default of nullptr draws the entire texture
 */
void LiquidSummer::renderTexture( SDL_Texture * sdlTexture, SDL_Renderer * sdlRenderer, SDL_Rect destinationRectangle, SDL_Rect * sourceRectangle )
{
	SDL_RenderCopy( sdlRenderer, sdlTexture, sourceRectangle, & destinationRectangle );
}

/*
 * Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving
 * the texture's width and height and taking a clip of the texture if desired
 * If a clip is passed, the clip's width and height will be used instead of the texture's
 * @param texture The source texture we want to draw
 * @param renderer The renderer we want to draw too
 * @param x The x coordinate to draw too
 * @param y The y coordinate to draw too
 * @param clip The sub-section of the texture to draw (clipping rect)
 *		default of nullptr draws the entire texture
 */
void LiquidSummer::renderTexture( SDL_Texture * sdlTexture, SDL_Renderer * sdlRenderer, int x, int y, SDL_Rect * sourceRectangle )
{
	SDL_Rect destinationRectangle;
	destinationRectangle.x = x;
	destinationRectangle.y = y;
	
	if( sourceRectangle != nullptr )
	{
		destinationRectangle.w = sourceRectangle->w;
		destinationRectangle.h = sourceRectangle->h;
	}
	else
	{
		SDL_QueryTexture( sdlTexture, NULL, NULL, & destinationRectangle.w, & destinationRectangle.h );
	}
	
	renderTexture( sdlTexture, sdlRenderer, destinationRectangle, sourceRectangle );
}

void LiquidSummer::startChrono( void )
{
	chronoStart = chrono::high_resolution_clock::now();
}

void LiquidSummer::updateChrono( void )
{
	elapsedFrames++;
	chronoLastStartOfFrameLoop = chrono::high_resolution_clock::now();
	chronoElapsed = chronoLastStartOfFrameLoop - chronoStart;
	chronoElapsedInMicroseconds = chrono::duration_cast< chrono::microseconds >( chronoElapsed ).count();
	
	if( chronoElapsedInMicroseconds > 0 )
	{
		framesPerSecond = ( double )( elapsedFrames - 1 ) * 1000000 / chronoElapsedInMicroseconds;
	}
}

void LiquidSummer::processEvents( void )
{
	static SDL_Event sdlEvent;
	
	while( SDL_PollEvent( & sdlEvent ) )
	{
		switch( sdlEvent.type )
		{
			case SDL_QUIT:
				
				quit = true;
				break;
				
			case SDL_KEYDOWN:
				
				switch( sdlEvent.key.keysym.sym )
				{
					case SDLK_1:
						
						spriteId = 0;
						break;
						
					case SDLK_2:
						
						spriteId = 1;
						break;
						
					case SDLK_3:
						
						spriteId = 2;
						break;
						
					case SDLK_4:
						
						spriteId = 3;
						break;
						
					case SDLK_ESCAPE:
						
						quit = true;
						break;
						
					case SDLK_LEFT:
						
						x = x - 10;
						break;
						
					case SDLK_RIGHT:
						
						x = x + 10;
						break;
						
					case SDLK_UP:
						
						y = y - 10;
						break;
						
					case SDLK_DOWN:
						
						y = y + 10;
						break;
						
					default:
						
						break;
				}
				break;
				
			case SDL_MOUSEMOTION:
				
				mousePressed = bool( sdlEvent.motion.state & SDL_BUTTON_LMASK );
				if( mousePressed )
				{
					mouseX = sdlEvent.motion.x;
					mouseY = sdlEvent.motion.y;
					mouseValid = true;
				}
				
			default:
				
				break;
		}
	}
}

void LiquidSummer::renderFrame( void )
{
	//Setup the clips for our image
	//static SDL_Rect spriteRectangles[ 4 ];
	static bool done = false;
	
	if( ! done )
	{
		//Since our clips our uniform in size we can generate a list of their
		//positions using some math (the specifics of this are covered in the lesson)
		for( int i = 0; i < 4; ++i )
		{
			//spriteRectangles[ i ].x = i / 2 * spriteWidth;
			//spriteRectangles[ i ].y = i % 2 * spriteHeight;
			//spriteRectangles[ i ].w = spriteWidth;
			//spriteRectangles[ i ].h = spriteHeight;
		}
		
		done = true;
	}
	
	SDL_SetRenderDrawColor( sdlRenderer, 0, 0, 0, 0 );
	SDL_RenderClear( sdlRenderer );
	
	//renderTexture( sdlTexture, sdlRenderer, x, y, & spriteRectangles[ spriteId ] );
	
	// if( mousePressed )
	// {
	// 	SDL_SetRenderDrawColor( sdlRenderer, 128, 255, 192, 64 );
	// 	SDL_SetRenderDrawBlendMode( sdlRenderer, SDL_BLENDMODE_ADD );
	// 	SDL_RenderDrawLine( sdlRenderer, 0, 0, mouseX, mouseY );
	// }
	
	drawStarField();
	
	drawDebug();
	SDL_RenderPresent( sdlRenderer );
}

string LiquidSummer::getResourcePath( const string & subDir )
{
	
#ifdef _WIN32
	const char PATH_SEP = '\\';
#else
	const char PATH_SEP = '/';
#endif
	
	static string baseRes;
	
	if( baseRes.empty() )
	{
		char * basePath = SDL_GetBasePath();
		
		if( basePath )
		{
			baseRes = basePath;
			SDL_free( basePath );
		}
		else
		{
			throw "Error getting resource path.";
		}
		
		//We replace the last bin/ with res/ to get the the resource path
		size_t pos = baseRes.rfind( "build" );
		baseRes = baseRes.substr( 0, pos ) + "resources" + PATH_SEP;
	}
	
	return subDir.empty() ? baseRes : baseRes + subDir + PATH_SEP;
}

SDL_Texture * LiquidSummer::renderText( const string & message, SDL_Color color )
{
	SDL_Surface * sdlSurface = TTF_RenderText_Blended( sdlFont, message.c_str(), color );
	if( sdlSurface == nullptr )
	{
		throw "TTF_RenderText_Blended returned a nullptr.";
	}
	
	SDL_SetRenderDrawBlendMode( sdlRenderer, SDL_BLENDMODE_BLEND );
	SDL_Texture * texture = SDL_CreateTextureFromSurface( sdlRenderer, sdlSurface );
	if( texture == nullptr )
	{
		throw "SDL_CreateTextureFromSurface returned a nullptr.";
	}
	
	SDL_FreeSurface( sdlSurface );
	
	return texture;
}

void LiquidSummer::drawDebug( void )
{
	string debugMessage;
	
	int debugWidth;
	int debugHeight;
	int debugX;
	int debugY;
	
	debugMessage = "elapsed: " + to_string( chronoElapsedInMicroseconds / 1000000.0 ) + " FPS: " + to_string( framesPerSecond );
	
	SDL_Color color = { 255, 255, 255, 20 };
	SDL_Texture * debugTexture = renderText( debugMessage.c_str(), color );
	
	SDL_QueryTexture( debugTexture, NULL, NULL, & debugWidth, & debugHeight );
	
	debugX = SCREEN_WIDTH - debugWidth;
	debugY = 0 /*SCREEN_HEIGHT*/;
	
	SDL_SetRenderDrawBlendMode( sdlRenderer, SDL_BLENDMODE_BLEND );
	renderTexture( debugTexture, sdlRenderer, debugX, debugY );
}

void LiquidSummer::drawStarField( void )
{
	static const int n = 30000;
	static const double CameraZ = 2000;
	static StarField starField( n );
	double currentZ;
	double maxZ = 0;
	double minZ = 0;
	double zRange;
	double projectionFactor;
	
	static SDL_Point sdlPoints[ n ];
	
	if( mouseValid )
	{
		starField.rotationYAngularSpeed = 0.04 * ( mouseX - SCREEN_WIDTH / 2 ) / SCREEN_WIDTH;
		starField.rotationXAngularSpeed = -0.04 * ( mouseY - SCREEN_HEIGHT / 2 ) / SCREEN_HEIGHT;
	}
	
	starField.step();
	
	//---------------------------------------------------------------------//
	//                                                                     //
	//    |<----------------------------->|                                //
	//               Cz          |<--Rz-->|                                //
	//                                    |                                //
	//                                    |                                //
	//    o ---------------------+--------O---------                       //
	//          ------         Rx|        |                                //
	//                ------     v        | Sx                             //
	//                      -----*-       v                                //
	//                           | -------*                                //
	//                                                                     //
	// Point is at { Rx, Rz } (R stands for "real")                        //
	// Projection is at Sx (S stands for "screen")                         //
	// Camera is at Cz (C stands for "camera").                            //
	//                                                                     //
	//    Sx           Rx          //              Cz                      //
	// ------- = -------------    //     Sx = ------------- * Rx           //
	//    Cz      ( Cz - Rz )    //            ( Cz - Rz )                 //
	//                                                                     //
	// Compute the factor and reuse it for X and Y.                        //
	//                                                                     //
	//                                                                     //
	//---------------------------------------------------------------------//
	
	for( int i = 0; i < n; i++ )
	{
		projectionFactor = CameraZ / ( CameraZ - starField.starField[ i ].z );
		
		sdlPoints[ i ].x = ( projectionFactor * starField.starField[ i ].x ) + SCREEN_WIDTH / 2;
		sdlPoints[ i ].y = ( projectionFactor * starField.starField[ i ].y ) + SCREEN_HEIGHT / 2;
		
		currentZ = starField.starField[ i ].z;
		
		if( maxZ < currentZ )
		{
			maxZ = currentZ;
		}
		
		if( minZ > currentZ )
		{
			minZ = currentZ;
		}
	}
	
	zRange = maxZ - minZ;
	
	SDL_SetRenderDrawBlendMode( sdlRenderer, SDL_BLENDMODE_ADD );
	
	for( int i = 0; i < n; i++ )
	{
		double zIndex1 = ( starField.starField[ i ].z - minZ ) / zRange;
		double zIndex2 = zIndex1 * zIndex1;
		double zIndex3 = zIndex2 * zIndex1;
		
		SDL_SetRenderDrawColor( sdlRenderer, 192 * zIndex1, 255 * zIndex3, 128 * zIndex3 , 128 * zIndex2 );
		SDL_RenderDrawPoint( sdlRenderer, sdlPoints[ i ].x, sdlPoints[ i ].y );
	}
}
