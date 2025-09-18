// ================================================================
// WHAT: Displays current battery voltage (read-only). OK refresh.
// INSTALL: folder battery_viewer.
// INSTALL (rookie‑friendly):
// 1) Clone official firmware and install uFBT (Micro Flipper Build Tool).
// 2) Create folder: firmware/applications_user/battery_viewer/
// 3) Put THIS file as: firmware/applications_user/battery_viewer/battery_viewer.c
// 4) Create application.fam (copy below between ===) in the same folder.
// 5) Build & run only this app:
// ufbt launch battery_viewer
// application.fam:
// ===
// App(
//   appid="battery_viewer",
//   name="Battery Volt",
//   apptype=FlipperAppType.GUI",
//   entry_point="battery_viewer_app",
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
#include <furi_hal_power.h>

typedef struct { ViewDispatcher* vd; Widget* w; float v; } App5;

static float bv_read(){ return furi_hal_power_get_battery_voltage(); }

static void bv_draw(App5* a){
    widget_reset(a->w);
    widget_add_string_element(a->w,64,8,AlignCenter,AlignTop,FontPrimary,"Battery Voltage");
    char b[64]; snprintf(b,sizeof(b),"%.2f V",a->v);
    widget_add_string_element(a->w,64,34,AlignCenter,AlignTop,FontSecondary,b);
    widget_add_string_element(a->w,64,58,AlignCenter,AlignBottom,FontSecondary,"OK refresh • Back exit");
}

static bool bv_input(InputEvent* e, void* ctx){ App5* a=ctx; if(e->type!=InputTypeShort) return false;
    if(e->key==InputKeyOk){ a->v=bv_read(); }
    else if(e->key==InputKeyBack){ view_dispatcher_stop(a->vd);} bv_draw(a); return true; }

int32_t battery_viewer_app(void* p){ UNUSED(p); App5 a={0}; a.vd=view_dispatcher_alloc(); a.w=widget_alloc(); a.v=bv_read(); bv_draw(&a);
    View* v=widget_get_view(a.w); view_set_input_callback(v,bv_input,&a);
    Gui* gui=furi_record_open(RECORD_GUI); view_dispatcher_attach_to_gui(a.vd,gui,ViewDispatcherTypeFullscreen);
    view_dispatcher_add_view(a.vd,0,widget_get_view(a.w)); view_dispatcher_switch_to_view(a.vd,0); view_dispatcher_run(a.vd);
    widget_free(a.w); view_dispatcher_free(a.vd); furi_record_close(RECORD_GUI); return 0; }
