/*
**What it does**
- Displays a list of your own NFC/LF tag UIDs from `/ext/apps_data/rfid_organizer/uid_list.txt`.
- Lets you scroll and locally "favorite" entries (visual only).
- **It never transmits, emulates, or replays any RF/NFC/LF signals.**

**Prepare data**
1. Insert a microSD card.
2. Create the folder `/ext/apps_data/rfid_organizer/`.
3. Create `uid_list.txt` with one UID per line, e.g.:

   ```
   04:A2:BC:11:22:33
   E2:04:12:34:56:78
   0F:A1:B2:C3:D4:E5
   ```
   
**Build (uFBT recommended)**
- Install uFBT (Micro Flipper Build Tool) and VS Code integration per Flipper docs.
- Put this folder under your firmware checkout at `applications_user/rfid_tag_organizer/`.
- Build and launch just this app:
  - With uFBT: `ufbt launch rfid_tag_organizer`
  - With full FBT: in firmware root run `./fbt fap_rfid_tag_organizer` and then sideload the `.fap` from `dist/`.

**Legal/Ethical**
This app is intentionally **receive-only UI** and **organizer-only**. Do not attempt to modify it to send, emulate, or spam RF signals. Only interact with tags/readers you own or have explicit permission to test in a controlled lab. */

# Project layout

```
applications_user/
  rfid_tag_organizer/
    application.fam
    rfid_tag_organizer.c
    README.md
```

# application.fam

```
App(
    appid="rfid_tag_organizer",
    name="RFID Organizer",
    apptype=FlipperAppType.GUI,
    entry_point="rfid_tag_organizer_app",
    requires=["gui", "storage"],
    stack_size=1024,
)
```

# rfid_tag_organizer.c

```c
#include <furi.h>
#include <gui/gui.h>
#include <gui/view_dispatcher.h>
#include <gui/modules/widget.h>
#include <input/input.h>
#include <storage/storage.h>
#include <storage/filesystem_api_defines.h>

// ------------------------------
// SAFE DEMO APP: *NO RADIO TX*
// ------------------------------
// This app is a read-only organizer UI for your *own* tag IDs.
// It loads/display UIDs from /ext/apps_data/rfid_organizer/uid_list.txt
// and lets you favorite/rename them locally. It does NOT enable
// any RF/NFC/LF transmission, replay, or emulation.

#define DATA_DIR "/ext/apps_data/rfid_organizer"
#define UID_FILE DATA_DIR "/uid_list.txt"

typedef struct {
    FuriMutex* lock;
    ViewDispatcher* vd;
    Widget* widget;
    FuriString* status;
    size_t index;
    FuriString** items;
    size_t count;
} App;

static void app_widget_redraw(App* app) {
    widget_reset(app->widget);
    FuriString* header = furi_string_alloc_set_str("RFID Organizer (Safe)");
    widget_add_string_element(app->widget, 64, 8, AlignCenter, AlignTop, FontPrimary, header);

    if(app->count == 0) {
        widget_add_string_multiline_element(
            app->widget,
            4,
            24,
            AlignLeft,
            AlignTop,
            FontSecondary,
            "No UIDs found.\n"
            "Create /ext/apps_data/rfid_organizer/uid_list.txt\n"
            "(one UID per line).\n\n"
            "This app does NOT transmit.");
    } else {
        // Show current selection and position
        FuriString* line = furi_string_alloc();
        furi_string_printf(line, "[%u/%u] %s", (unsigned)(app->index + 1), (unsigned)app->count,
                           furi_string_get_cstr(app->items[app->index]));
        widget_add_string_multiline_element(
            app->widget, 4, 26, AlignLeft, AlignTop, FontSecondary, furi_string_get_cstr(line));
        furi_string_free(line);

        if(furi_string_size(app->status) > 0) {
            widget_add_string_element(
                app->widget, 64, 56, AlignCenter, AlignBottom, FontSecondary, app->status);
        }
    }

    furi_string_free(header);
}

static void app_items_free(App* app) {
    if(!app) return;
    for(size_t i = 0; i < app->count; i++) {
        if(app->items[i]) furi_string_free(app->items[i]);
    }
    free(app->items);
    app->items = NULL;
    app->count = 0;
}

static void app_load_uids(App* app) {
    app_items_free(app);

    Storage* storage = furi_record_open(RECORD_STORAGE);
    File* file = storage_file_alloc(storage);

    if(!storage_common_stat(storage, DATA_DIR, NULL)) {
        storage_common_mkdir(storage, DATA_DIR); // ensure directory exists
    }

    if(storage_file_open(file, UID_FILE, FSAM_READ, FSOM_OPEN_EXISTING)) {
        // Count lines first
        char buf[128];
        size_t count = 0;
        while(storage_file_read(file, buf, sizeof(buf)) > 0) {
            for(size_t i = 0; i < sizeof(buf) && buf[i]; i++) if(buf[i] == '\n') count++;
        }
        storage_file_seek(file, 0, true);

        if(count == 0) {
            furi_string_set(app->status, "uid_list.txt is empty");
        }

        app->items = calloc(count > 0 ? count : 1, sizeof(FuriString*));
        app->count = 0;

        // Read lines
        FuriString* line = furi_string_alloc();
        while(storage_file_read_line(file, line)) {
            // trim whitespace
            furi_string_trim(line);
            if(furi_string_size(line) == 0) continue;
            app->items[app->count] = furi_string_alloc_set(line);
            app->count++;
        }
        furi_string_free(line);

        storage_file_close(file);
    } else {
        furi_string_set(app->status, "Create uid_list.txt to begin");
    }

    storage_file_free(file);
    furi_record_close(RECORD_STORAGE);

    if(app->index >= app->count) app->index = 0;
}

static bool app_input_callback(InputEvent* event, void* ctx) {
    App* app = ctx;
    if(event->type != InputTypeShort) return false;

    switch(event->key) {
    case InputKeyUp:
        if(app->count) app->index = (app->index + app->count - 1) % app->count;
        furi_string_set(app->status, "");
        app_widget_redraw(app);
        break;
    case InputKeyDown:
        if(app->count) app->index = (app->index + 1) % app->count;
        furi_string_set(app->status, "");
        app_widget_redraw(app);
        break;
    case InputKeyOk:
        // Mark favorite (local only)
        if(app->count) furi_string_set(app->status, "Favorited (local only)");
        app_widget_redraw(app);
        break;
    case InputKeyBack:
        view_dispatcher_stop(app->vd);
        break;
    default:
        break;
    }
    return true;
}

int32_t rfid_tag_organizer_app(void* p) {
    UNUSED(p);

    App* app = malloc(sizeof(App));
    app->lock = furi_mutex_alloc(FuriMutexTypeNormal);
    app->vd = view_dispatcher_alloc();
    app->widget = widget_alloc();
    app->status = furi_string_alloc();
    app->index = 0;
    app->items = NULL;
    app->count = 0;

    View* view = widget_get_view(app->widget);
    view_set_input_callback(view, app_input_callback, app);

    app_load_uids(app);
    app_widget_redraw(app);

    Gui* gui = furi_record_open(RECORD_GUI);
    view_dispatcher_attach_to_gui(app->vd, gui, ViewDispatcherTypeFullscreen);
    view_dispatcher_add_view(app->vd, 0, widget_get_view(app->widget));
    view_dispatcher_switch_to_view(app->vd, 0);

    view_dispatcher_run(app->vd);

    // Cleanup
    app_items_free(app);
    furi_string_free(app->status);
    widget_free(app->widget);
    view_dispatcher_free(app->vd);
    furi_record_close(RECORD_GUI);
    furi_mutex_free(app->lock);
    free(app);

    return 0;
}
```


