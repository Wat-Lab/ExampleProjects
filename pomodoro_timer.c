// ================================================================
// Mini-App #3: Pomodoro Timer (25/5) (Single file, ~<200 LoC)
// File: pomodoro_timer.c
// ------------------------------------------------
// WHAT: 25 min Work, 5 min Break. OK start/stop, Up reset, Down toggle mode.
// // INSTALL (rookie-friendly):
// 1) Clone official firmware and install uFBT (Micro Flipper Build Tool).
// 2) Create folder: firmware/applications_user/pomodoro_timer/
// 3) Put THIS file as: firmware/applications_user/pomodoro_timer/pomodoro_timer.c
// 4) Create application.fam (copy below between ===) in the same folder.
// 5) Build & run only this app:
//    ufbt launch pomodoro_timer
// application.fam:
// ===
// App(
//   appid="pomodoro_timer",
//   name="Pomodoro",
//   apptype=FlipperAppType.GUI,
//   entry_point="pomodoro_timer_app",
//   requires=["gui"],
//   stack_size=1024,
// )
// ===
// ================================================================
#include <furi.h>
#include <gui/gui.h>
#include <gui/view_dispatcher.h>
#include <gui/modules/widget.h>
#include <input/input.h>

typedef struct { ViewDispatcher* vd; Widget* w; bool running; bool work; uint32_t start; uint32_t dur_ms; } App3;
#define MIN(x,y) ((x)<(y)?(x):(y))

static void p_draw(App3* a){
    widget_reset(a->w);
    widget_add_string_element(a->w,64,8,AlignCenter,AlignTop,FontPrimary,"Pomodoro");
    uint32_t left=a->running? ( (a->start + a->dur_ms) > furi_get_tick() ? (a->start+a->dur_ms - furi_get_tick()) : 0 ) : a->dur_ms;
    uint32_t sec=left/1000; uint32_t m=sec/60; uint32_t s=sec%60;
    char buf[64]; snprintf(buf,sizeof(buf),"%s %02lu:%02lu", a->work?"Work":"Break", (unsigned long)m,(unsigned long)s);
    widget_add_string_element(a->w,64,34,AlignCenter,AlignTop,FontSecondary,buf);
    widget_add_string_element(a->w,64,58,AlignCenter,AlignBottom,FontSecondary,"OK start/stop • Up reset • Down mode");
}

static void p_reset(App3* a){ a->running=false; a->dur_ms=(a->work?25:5)*60*1000; }

static bool p_input(InputEvent* e, void* ctx){ App3* a=ctx; if(e->type!=InputTypeShort) return false;
    if(e->key==InputKeyOk){ if(a->running){ a->dur_ms=( (a->start+a->dur_ms)>furi_get_tick()? (a->start+a->dur_ms - furi_get_tick()) : 0 ); a->running=false; }
        else { a->start=furi_get_tick(); a->running=true; } }
    else if(e->key==InputKeyUp){ p_reset(a);} 
    else if(e->key==InputKeyDown){ a->work=!a->work; p_reset(a);} 
    else if(e->key==InputKeyBack){ view_dispatcher_stop(a->vd);} p_draw(a); return true; }

int32_t pomodoro_timer_app(void* p){ UNUSED(p); App3 a={0}; a.vd=view_dispatcher_alloc(); a.w=widget_alloc(); a.work=true; p_reset(&a); p_draw(&a);
    View* v=widget_get_view(a.w); view_set_input_callback(v,p_input,&a);
    Gui* gui=furi_record_open(RECORD_GUI); view_dispatcher_attach_to_gui(a.vd,gui,ViewDispatcherTypeFullscreen);
    view_dispatcher_add_view(a.vd,0,widget_get_view(a.w)); view_dispatcher_switch_to_view(a.vd,0); view_dispatcher_run(a.vd);
    widget_free(a.w); view_dispatcher_free(a.vd); furi_record_close(RECORD_GUI); return 0; }
