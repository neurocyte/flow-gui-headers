/*
 * Minimal XInput2 shim for cross-compiling the Flow Control GUI renderer.
 *
 * sokol bundles every backend into a single static library (sokol_clib), so
 * sokol_app.c is always compiled even though flow does its own windowing via
 * wio and only links sokol_gfx. The vendored wio_unix_headers package ships
 * most of the X11/GL headers sokol needs but not <X11/extensions/XInput2.h>,
 * so this shim provides the few declarations sokol_app.c references. The
 * resulting sokol_app.o is never referenced and is dropped by the linker, so
 * none of these symbols ever have to resolve or behave correctly at run time.
 *
 * The XI_* event constants and the XIMaskLen/XISetMask/XIMaskIsSet macros come
 * from <X11/extensions/XI2.h> (provided by wio_unix_headers).
 */
#ifndef FLOW_SOKOL_SHIM_X11_XINPUT2_H
#define FLOW_SOKOL_SHIM_X11_XINPUT2_H

#include <X11/Xlib.h>
#include <X11/extensions/XI2.h>

typedef struct {
    int            mask_len;
    unsigned char *mask;
    double        *values;
} XIValuatorState;

typedef struct {
    int            deviceid;
    int            mask_len;
    unsigned char *mask;
} XIEventMask;

typedef struct {
    int             type;
    unsigned long   serial;
    Bool            send_event;
    Display        *display;
    int             extension;
    int             evtype;
    Time            time;
    int             deviceid;
    int             sourceid;
    int             detail;
    int             flags;
    XIValuatorState valuators;
    double         *raw_values;
} XIRawEvent;

extern Status XIQueryVersion(Display *display, int *major_version_inout, int *minor_version_inout);
extern int XISelectEvents(Display *display, Window win, XIEventMask *masks, int num_masks);

#endif /* FLOW_SOKOL_SHIM_X11_XINPUT2_H */
