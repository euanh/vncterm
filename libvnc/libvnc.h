/*
 * QEMU VNC display driver
 * 
 * Copyright (C) 2006 Fabrice Bellard
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef _LIBVNC_LIBVNC_H
#define _LIBVNC_LIBVNC_H

/* VNC Authentication */
#define AUTHCHALLENGESIZE 16

struct DisplayState {
    uint8_t *data;
    int linesize;
    int depth;
    int bgr; /* BGR color order instead of RGB. Only valid for depth == 32 */
    int width;
    int height;
    int graphic_mode;
    void *opaque;

    void (*dpy_update)(struct DisplayState *s, int x, int y, int w, int h);
    void (*dpy_resize)(struct DisplayState *s, int w, int h);
    void (*dpy_refresh)(struct DisplayState *s);
    void (*dpy_copy)(struct DisplayState *s, int src_x, int src_y, int dst_x, int dst_y, int w, int h);
    void (*dpy_set_server_text)(struct DisplayState *s, char *text);
    void (*dpy_bell)(struct DisplayState *s);
    void (*dpy_copy_rect)(struct DisplayState *ds, int xf, int yf, int xt, int yt, int w, int h);
    
    void (*dpy_close_vncviewer_connections)(struct DisplayState *ds);
    unsigned char (*dpy_clients_connected)(struct DisplayState *ds);

    void *hw_opaque;
    void (*hw_update)(void *);
    void (*hw_invalidate)(void *);
    int (*hw_refresh)(struct DisplayState *);

    void *mouse_opaque;
    int (*mouse_is_absolute)(void *);
    void (*mouse_event)(int, int, int, int, void *);

    void (*kbd_put_keycode)(int);
    void (*kbd_put_keysym)(int);

    void *(*init_timer)(void (*)(void *), void *);
    uint64_t (*get_clock)(void);
    int (*set_timer)(void *, uint64_t);

    int (*set_fd_handler)(int, int (*)(void *), void (*)(void *),
			  void (*)(void *), void *);
    int (*set_fd_error_handler)(int, void (*)(void *));
};
typedef struct DisplayState DisplayState;

struct sockaddr;
int vnc_display_init(DisplayState *ds, struct sockaddr *sa,
		     int find_unused, char *title, char *keyboard_layout, 
		     unsigned int width, unsigned int height);


/* keyboard/mouse support */
#define MOUSE_EVENT_LBUTTON 0x01
#define MOUSE_EVENT_RBUTTON 0x02
#define MOUSE_EVENT_MBUTTON 0x04

/* keysym is a unicode code except for special keys (see QEMU_KEY_xxx
   constants) */
#define QEMU_KEY_ESC1(c) ((c) | 0xe100)
#define QEMU_KEY_BACKSPACE  0xff08
#define QEMU_KEY_UP         QEMU_KEY_ESC1('A')
#define QEMU_KEY_DOWN       QEMU_KEY_ESC1('B')
#define QEMU_KEY_RIGHT      QEMU_KEY_ESC1('C')
#define QEMU_KEY_LEFT       QEMU_KEY_ESC1('D')
#define QEMU_KEY_HOME       QEMU_KEY_ESC1(1)
#define QEMU_KEY_END        QEMU_KEY_ESC1(4)
#define QEMU_KEY_PAGEUP     QEMU_KEY_ESC1(5)
#define QEMU_KEY_PAGEDOWN   QEMU_KEY_ESC1(6)
#define QEMU_KEY_DELETE     QEMU_KEY_ESC1(3)

#define QEMU_KEY_MOD_CTRL  0x300
#define QEMU_KEY_MOD_SHIFT 0x400

#define QEMU_KEY_CTRL_UP         (QEMU_KEY_UP + QEMU_KEY_MOD_CTRL)
#define QEMU_KEY_CTRL_DOWN       (QEMU_KEY_DOWN + QEMU_KEY_MOD_CTRL)
#define QEMU_KEY_CTRL_LEFT       (QEMU_KEY_LEFT + QEMU_KEY_MOD_CTRL)
#define QEMU_KEY_CTRL_RIGHT      (QEMU_KEY_RIGHT + QEMU_KEY_MOD_CTRL)
#define QEMU_KEY_CTRL_HOME       (QEMU_KEY_HOME + QEMU_KEY_MOD_CTRL)
#define QEMU_KEY_CTRL_END        (QEMU_KEY_END + QEMU_KEY_MOD_CTRL)
#define QEMU_KEY_CTRL_PAGEUP     (QEMU_KEY_PAGEUP + QEMU_KEY_MOD_CTRL)
#define QEMU_KEY_CTRL_PAGEDOWN   (QEMU_KEY_PAGEDOWN + QEMU_KEY_MOD_CTRL)
#define QEMU_KEY_SHIFT_PAGEUP     (QEMU_KEY_PAGEUP + QEMU_KEY_MOD_SHIFT)
#define QEMU_KEY_SHIFT_PAGEDOWN   (QEMU_KEY_PAGEDOWN + QEMU_KEY_MOD_SHIFT)



#endif /* _LIBVNC_LIBVNC_H */
