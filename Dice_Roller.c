// WHAT: Roll D6/D8/D20 with Up/Down to choose die, OK to roll.
// SAFE: No RF, no storage writes.
// INSTALL (rookie-friendly):
// 1) Clone official firmware and install uFBT (Micro Flipper Build Tool).
// 2) Create folder: firmware/applications_user/dice_roller/
// 3) Put THIS file as: firmware/applications_user/dice_roller/dice_roller.c
// 4) Create application.fam (copy below between ===) in the same folder.
// 5) Build & run only this app:
//    ufbt launch dice_roller
// application.fam (paste this):
// ===
// App(
//   appid="dice_roller",
//   name="Dice Roller",
//   apptype=FlipperAppType.GUI,
//   entry_point="dice_roller_app",
//   requires=["gui"],
//   stack_size=1024,
// )
// ===
// COMMENTING: Use // for one line, or /* ... */ for blocks. None of this runs.
// ================================================================
#include <furi.h>
#include <gui/gui.h>
#include <gui/view_dispatcher.h>
#include <gui/modules/widget.h>
#include <input/input.h>

typedef struct { ViewDispatcher* vd; Widget* w; uint16_t faces; uint16_t last; } App1;

static void dr_draw(App1* a){
    widget_reset(a->w);
    widget_add_string_element(a->w,64,8,AlignCenter,AlignTop,FontPrimary,"Dice Roller");
    char buf[64];
    snprintf(buf,sizeof(buf),"Die: D%u\nLast: %u",a->faces,a->last);
    widget_add_string_multiline_element(a->w,64,28,AlignCenter,AlignTop,FontSecondary,buf);
    widget_add_string_element(a->w,64,58,AlignCenter,AlignBottom,FontSecondary,"Up/Down = die, OK = roll");
}

static bool dr_input(InputEvent* e, void* ctx){
    App1* a=ctx; if(e->type!=InputTypeShort) return false;
    if(e->key==InputKeyUp){ if(a->faces==6) a->faces=8; else if(a->faces==8) a->faces=20; else a->faces=6; }
    else if(e->key==InputKeyDown){ if(a->faces==6) a->faces=20; else if(a->faces==8) a->faces=6; else a->faces=8; }
    else if(e->key==InputKeyOk){ srand(furi_get_tick()); a->last=(rand()%a->faces)+1; }
    else if(e->key==InputKeyBack){ view_dispatcher_stop(a->vd); }
    dr_draw(a); return true;
}

int32_t dice_roller_app(void* p){ UNUSED(p); App1 a={0};
    a.vd=view_dispatcher_alloc(); a.w=widget_alloc(); a.faces=6; a.last=0;
    View* v=widget_get_view(a.w); view_set_input_callback(v,dr_input,&a);
    dr_draw(&a);
    Gui* gui=furi_record_open(RECORD_GUI);
    view_dispatcher_attach_to_gui(a.vd,gui,ViewDispatcherTypeFullscreen);
    view_dispatcher_add_view(a.vd,0,widget_get_view(a.w));
    view_dispatcher_switch_to_view(a.vd,0);
    view_dispatcher_run(a.vd);
    widget_free(a.w); view_dispatcher_free(a.vd); furi_record_close(RECORD_GUI); return 0; }
