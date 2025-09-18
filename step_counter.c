// ================================================================
// WHAT: Press OK to count a "step". Back exits. Up/Down adjust.
// SAVE: On exit, writes count to /ext/apps_data/step_counter/count.txt
// INSTALL (rookie-friendly):
// 1) Clone official firmware and install uFBT (Micro Flipper Build Tool).
// 2) Create folder: firmware/applications_user/step_counter/
// 3) Put THIS file as: firmware/applications_user/step_counter/step_counter.c
// 4) Create application.fam (copy below between ===) in the same folder.
// 5) Build & run only this app:
//    ufbt launch step_counter
// application.fam:
// ===
// App(
//   appid="step_counter",
//   name="Step Counter",
//   apptype=FlipperAppType.GUI,
//   entry_point="step_counter_app",
//   requires=["gui","storage"],
//   stack_size=1024,
// )
// ===
// ================================================================
#include <furi.h>
#include <gui/gui.h>
#include <gui/view_dispatcher.h>
#include <gui/modules/widget.h>
#include <input/input.h>
#include <storage/storage.h>
#include <storage/filesystem_api_defines.h>

typedef struct { ViewDispatcher* vd; Widget* w; uint32_t steps; } App2;
#define SC_DIR  "/ext/apps_data/step_counter"
#define SC_FILE SC_DIR "/count.txt"

static void sc_draw(App2* a){
    widget_reset(a->w);
    widget_add_string_element(a->w,64,8,AlignCenter,AlignTop,FontPrimary,"Step Counter");
    char b[64]; snprintf(b,sizeof(b),"Steps: %lu",(unsigned long)a->steps);
    widget_add_string_element(a->w,64,32,AlignCenter,AlignTop,FontSecondary,b);
    widget_add_string_element(a->w,64,58,AlignCenter,AlignBottom,FontSecondary,"OK +1  Up/Down +/-10");
}

static void sc_load(App2* a){ Storage* s=furi_record_open(RECORD_STORAGE); File* f=storage_file_alloc(s);
    if(!storage_common_stat(s,SC_DIR,NULL)) storage_common_mkdir(s,SC_DIR);
    if(storage_file_open(f,SC_FILE,FSAM_READ,FSOM_OPEN_EXISTING)){
        char buf[32]={0}; storage_file_read(f,buf,sizeof(buf)-1); a->steps=strtoul(buf,NULL,10); storage_file_close(f);
    } storage_file_free(f); furi_record_close(RECORD_STORAGE);
}

static void sc_save(App2* a){ Storage* s=furi_record_open(RECORD_STORAGE); File* f=storage_file_alloc(s);
    if(!storage_common_stat(s,SC_DIR,NULL)) storage_common_mkdir(s,SC_DIR);
    if(storage_file_open(f,SC_FILE,FSAM_WRITE,FSOM_CREATE_ALWAYS)){
        char buf[32]; snprintf(buf,sizeof(buf),"%lu\n",(unsigned long)a->steps);
        storage_file_write(f,buf,strlen(buf)); storage_file_close(f);
    } storage_file_free(f); furi_record_close(RECORD_STORAGE);
}

static bool sc_input(InputEvent* e, void* ctx){ App2* a=ctx; if(e->type!=InputTypeShort) return false;
    if(e->key==InputKeyOk) a->steps++;
    else if(e->key==InputKeyUp) a->steps+=10;
    else if(e->key==InputKeyDown) a->steps=(a->steps>=10)?a->steps-10:0;
    else if(e->key==InputKeyBack){ sc_save(a); view_dispatcher_stop(a->vd);} sc_draw(a); return true; }

int32_t step_counter_app(void* p){ UNUSED(p); App2 a={0}; a.vd=view_dispatcher_alloc(); a.w=widget_alloc(); sc_load(&a); sc_draw(&a);
    View* v=widget_get_view(a.w); view_set_input_callback(v,sc_input,&a);
    Gui* gui=furi_record_open(RECORD_GUI); view_dispatcher_attach_to_gui(a.vd,gui,ViewDispatcherTypeFullscreen);
    view_dispatcher_add_view(a.vd,0,widget_get_view(a.w)); view_dispatcher_switch_to_view(a.vd,0); view_dispatcher_run(a.vd);
    widget_free(a.w); view_dispatcher_free(a.vd); furi_record_close(RECORD_GUI); return 0; }
