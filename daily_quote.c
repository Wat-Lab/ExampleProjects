// ================================================================
// Mini-App #4: Daily Quote Viewer (Single file, ~<200 LoC)
// File: daily_quote.c
// ------------------------------------------------
// WHAT: Loads quotes from /ext/apps_data/daily_quote/quotes.txt (one per line)
// USE: Up/Down change; OK random; Back exit.
// INSTALL: folder daily_quote; create quotes.txt on SD.
// 1) Clone official firmware and install uFBT (Micro Flipper Build Tool).
// 2) Create folder: firmware/applications_user/daily_quote/
// 3) Put THIS file as: firmware/applications_user/daily_quote/daily_quote.c
// 4) Create application.fam (copy below between ===) in the same folder.
// 5) Build & run only this app:
//    ufbt launch daily_quote
// application.fam:
// ===
// App(
//   appid="daily_quote",
//   name="Daily Quote",
//   apptype=FlipperAppType.GUI,
//   entry_point="daily_quote_app",
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

typedef struct { ViewDispatcher* vd; Widget* w; FuriString** items; size_t count; size_t idx; } App4;
#define DQ_DIR  "/ext/apps_data/daily_quote"
#define DQ_FILE DQ_DIR "/quotes.txt"

static void dq_free(App4* a){ if(!a||!a->items) return; for(size_t i=0;i<a->count;i++) if(a->items[i]) furi_string_free(a->items[i]); free(a->items); a->items=NULL; a->count=0; }

static void dq_load(App4* a){ Storage* s=furi_record_open(RECORD_STORAGE); File* f=storage_file_alloc(s);
    if(!storage_common_stat(s,DQ_DIR,NULL)) storage_common_mkdir(s,DQ_DIR);
    if(storage_file_open(f,DQ_FILE,FSAM_READ,FSOM_OPEN_EXISTING)){
        size_t cnt=0; char tmp[128]; while(storage_file_read(f,tmp,sizeof(tmp))>0){ for(size_t i=0;i<sizeof(tmp)&&tmp[i];i++) if(tmp[i]=='\n') cnt++; }
        storage_file_seek(f,0,true);
        a->items=calloc((cnt?cnt:1),sizeof(FuriString*)); a->count=0;
        FuriString* line=furi_string_alloc();
        while(storage_file_read_line(f,line)){ furi_string_trim(line); if(furi_string_size(line)==0) continue; a->items[a->count++]=furi_string_alloc_set(line);} furi_string_free(line); storage_file_close(f);
    }
    storage_file_free(f); furi_record_close(RECORD_STORAGE);
    a->idx= (a->count? 0:0);
}

static void dq_draw(App4* a){ widget_reset(a->w);
    widget_add_string_element(a->w,64,8,AlignCenter,AlignTop,FontPrimary,"Daily Quote");
    if(!a->count){ widget_add_string_multiline_element(a->w,4,24,AlignLeft,AlignTop,FontSecondary,"No quotes found.\nCreate /ext/apps_data/daily_quote/quotes.txt\n(one per line). "); }
    else { widget_add_string_multiline_element(a->w,4,24,AlignLeft,AlignTop,FontSecondary,furi_string_get_cstr(a->items[a->idx])); }
    widget_add_string_element(a->w,64,58,AlignCenter,AlignBottom,FontSecondary,"Up/Down scroll • OK random"); }

static bool dq_input(InputEvent* e, void* ctx){ App4* a=ctx; if(e->type!=InputTypeShort) return false;
    if(e->key==InputKeyUp && a->count) a->idx=(a->idx+a->count-1)%a->count;
    else if(e->key==InputKeyDown && a->count) a->idx=(a->idx+1)%a->count;
    else if(e->key==InputKeyOk && a->count){ srand(furi_get_tick()); a->idx=rand()%a->count; }
    else if(e->key==InputKeyBack){ view_dispatcher_stop(a->vd);} dq_draw(a); return true; }

int32_t daily_quote_app(void* p){ UNUSED(p); App4 a={0}; a.vd=view_dispatcher_alloc(); a.w=widget_alloc(); dq_load(&a); dq_draw(&a);
    View* v=widget_get_view(a.w); view_set_input_callback(v,dq_input,&a);
    Gui* gui=furi_record_open(RECORD_GUI); view_dispatcher_attach_to_gui(a.vd,gui,ViewDispatcherTypeFullscreen);
    view_dispatcher_add_view(a.vd,0,widget_get_view(a.w)); view_dispatcher_switch_to_view(a.vd,0); view_dispatcher_run(a.vd);
    dq_free(&a); widget_free(a.w); view_dispatcher_free(a.vd); furi_record_close(RECORD_GUI); return 0; }
