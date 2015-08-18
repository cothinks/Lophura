#include "samples/sample_app/include/window.h"
#include "samples/sample_app/include/native_window.h"

#include "3rd/SDL/include/SDL.h"

SDL_Surface* g_sdl_surface = NULL;

namespace sample_app{



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

	void get_surface(SDL_Surface*& surface)
	{
		surface = surface_;
	}
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
		window_delegate_->OnCreate(surface_);
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

};