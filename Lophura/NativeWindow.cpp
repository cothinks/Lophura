#include "NativeWindow.h"
#include "Window.h"
#include "sdl.h"

LOPHURA_BEGIN

SDL_Surface* g_sdl_surface = NULL;

NativeWindow::NativeWindow(IWindowDelegate* delegate)
{
	window_delegate_ = delegate;
}

NativeWindow::~NativeWindow()
{
}

class MSWindow :public NativeWindow
{
public:
	MSWindow(IWindowDelegate* delegate) : NativeWindow(delegate)
	{}
	~MSWindow()
	{}
};


class SDLWindow : public NativeWindow
{
public:
	SDLWindow(IWindowDelegate* delegate) : NativeWindow(delegate),surface_(nullptr)
	{
		//remove these code
		if (CreateWindow()){
			RunWindow();
		}

	}
	~SDLWindow()
	{}
public:
	bool CreateWindow();
	void RunWindow();
private:
	SDL_Surface*	surface_;
};

bool SDLWindow::CreateWindow()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0){
		return false;
	}

	surface_ = SDL_SetVideoMode( 800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF );
	g_sdl_surface = surface_;

	if (surface_){
		SDL_WM_SetCaption( "Lophura", NULL );
		window_delegate_->OnCreate();
	}

	return true;
}

void SDLWindow::RunWindow()
{
	bool running = true;

	while ( running ){
		SDL_Event sdlEvt;

		if( SDL_PollEvent( &sdlEvt ) ){
			switch( sdlEvt.type ){
			case SDL_QUIT:					
					running = false;
				break;
			default:
				break;
			}
		}else{
			if (window_delegate_){
				window_delegate_->OnIdle();
			}
		}
	}

	if( surface_ ){
		SDL_FreeSurface( surface_ );
	}
}

NativeWindow* CreateNativeWindow(IWindowDelegate* delegate)
{
	return new SDLWindow(delegate);
}

LOPHURA_END