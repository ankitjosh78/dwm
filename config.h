/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx = 1; /* border pixel of windows */
static const unsigned int gappx = 6;   /* gaps between windows */
static const unsigned int snap = 32;    /* snap pixel */
static const unsigned int systraypinning =
    0; /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor
          X */
static const unsigned int systrayspacing = 2; /* systray spacing */
static const int systraypinningfailfirst =
    1; /* 1: if pinning fails, display systray on the first monitor, False:
          display systray on the last monitor*/
static const int showsystray = 1; /* 0 means no systray */
static const int showbar = 1;     /* 0 means no bar */
static const int topbar = 1;      /* 0 means bottom bar */
static const char *fonts[] = {
    "JetBrains Mono Nerd Font:size=11:antialias=true:autohint=true",
    "Dejavu Sans Mono for Powerline:size=10",
    "JoyPixels:size=11:antialias=true:autohint=true",
    "FontAwesome:size=10:antialias=true:autohint=true",
};
static const char dmenufont[] = "JetBrains Mono Nerd Font:size=12";
#include "/home/ankit/.cache/wal/colors-wal-dwm.h"

/* tagging */
static const char *tagsalt[] = {"1", "2", "3", "4",
                            "5", "6","7","8","9"};

static const char *tags[] = { "🐧", "🔎", "⌨️", "💬", "👾", "🧲", "🖌️", "📺", "📸"};
//static const char *tags[] = {"🇦", "🌐", "👨‍💻", "💬",
//                             "🎮", "🎵", "🧲", "🎥","💰"};


static const Rule rules[] =
    {
        /* xprop(1):
         *	WM_CLASS(STRING) = instance, class
         *	WM_NAME(STRING) = title
         */
        /* class      instance   	title    	tags mask     isfloating
           monitor */
        {"Gimp", NULL, NULL, 1 << 6, 0, -1},
        {"kdenlive", NULL, NULL, 1 << 6, 0, -1},
        {"Microsoft-edge-beta", NULL, NULL, 1 << 1, 0, -1},
        {"Brave-browser", NULL, NULL, 1 << 1, 0, -1},
        //{ "st-256color",  NULL,     NULL,		1 << 0,       0, -1 },
        //{ "Pcmanfm",  NULL, 		NULL,		1 << 2,       0, -1 },
        {"discord", NULL, NULL, 1 << 4, 0, -1},
        {"mpv", NULL, NULL, 1 << 7, 0, -1},
        {"TelegramDesktop", NULL, NULL, 1 << 3, 0, -1},
        {"Signal", NULL, NULL, 1 << 3, 0, -1},
        {"code-oss", NULL, NULL, 1 << 2, 0, -1},
        {"TeamViewer", NULL, NULL, 1 << 3, 0, -1},
        {"AnyDesk", NULL, NULL, 1 << 3, 0, -1},
        {"Spotify", NULL, NULL, 1 << 7, 0, -1},
        {"qBittorrent", NULL, NULL, 1 << 5, 0, -1},
        {"obs", NULL, NULL, 1 << 8, 0, -1},
        {"SimpleScreenRecorder", NULL, NULL, 1 << 8, 0, -1},
        {"Rofi", NULL, NULL, 1 << 8, 1, -1},
};

/* layout(s) */
static const float mfact = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */
static const int resizehints =
    0; /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
    /* symbol     arrange function */
    {"[]=", tile}, /* first entry is default */
    {"[M]", monocle},
    {"><>", NULL}, /* no layout function means floating behavior */
     {"|M|", centeredmaster}, {">M>", centeredfloatingmaster},
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG)                                                      \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
      {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},               \
      {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                        \
      {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }

/* commands */
static char dmenumon[2] =
    "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run"};
static const char *term2cmd[] = {"alacritty", NULL};
static const char *term1cmd[] = {"st", NULL};
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "100x30", NULL };
static const char *filecmd[] = {"pcmanfm", NULL};
static const char *roficmd[] = {"rofi", "-show", "run", NULL};
static const char *bravecmd[] = {"brave", NULL};
static const char *nitrogencmd[] = {"nitrogen", NULL};
static const char *obs[] = {"obs", NULL};
static const char *discord[] = {"discord", NULL};
static const char *ytfzf[] = {"ytfzf","-DN", NULL};
static const char *scrotcmd[] = {"scrot", "-e", "mv $f ~/Pictures/ss/",
                                 NULL};
static const char *upvol[] = {"/usr/bin/pactl", "set-sink-volume", "0", "+5%",
                              NULL};
static const char *downvol[] = {"/usr/bin/pactl", "set-sink-volume", "0", "-5%",
                                NULL};
static const char *mutevol[] = {"/usr/bin/pactl", "set-sink-mute", "0",
                                "toggle", NULL};

static Key keys[] = {
    /* modifier                     key        function        argument */
    {MODKEY, XK_p, spawn, {.v = dmenucmd}},
    {MODKEY, XK_period, spawn, SHCMD("dmenuunicode")},
    {MODKEY, XK_r, spawn, SHCMD("dmenurecord")},
    {MODKEY, XK_Print, spawn, {.v = scrotcmd}},
    {MODKEY | ShiftMask, XK_Return, spawn, {.v = filecmd}},
    {MODKEY | ShiftMask, XK_n, spawn, {.v = nitrogencmd}},
    {MODKEY | ShiftMask, XK_x, spawn, SHCMD("shut")},
    {MODKEY | ShiftMask, XK_y, spawn, {.v = ytfzf}},
    {MODKEY | ShiftMask, XK_d, spawn, {.v = discord}},
    {MODKEY | ShiftMask, XK_o, spawn, {.v = obs}},
    {MODKEY | ShiftMask, XK_b, spawn, {.v = bravecmd}},
    {MODKEY, XK_Return, spawn, {.v = term1cmd}},
	{ MODKEY,                       XK_o,  togglescratch,  {.v = scratchpadcmd } },
    {ControlMask | Mod1Mask, XK_t, spawn, {.v = term2cmd}},
    {MODKEY, XK_F12, spawn, {.v = roficmd}},
    {MODKEY, XK_b, togglebar, {0}},
    {MODKEY | ShiftMask, XK_j, rotatestack, {.i = +1}},
    {MODKEY | ShiftMask, XK_k, rotatestack, {.i = -1}},
    {MODKEY, XK_j, focusstack, {.i = +1}},
    {MODKEY, XK_k, focusstack, {.i = -1}},
    {MODKEY, XK_i, incnmaster, {.i = +1}},
    {MODKEY, XK_d, incnmaster, {.i = -1}},
    {MODKEY, XK_h, setmfact, {.f = -0.05}},
    {MODKEY, XK_l, setmfact, {.f = +0.05}},
    {MODKEY, XK_Return, zoom, {0}},
    {MODKEY, XK_Tab, view, {0}},
    {MODKEY, XK_q, killclient, {0}},
    {MODKEY, XK_t, setlayout, {.v = &layouts[0]}},
    {MODKEY, XK_m, setlayout, {.v = &layouts[1]}},
    {MODKEY, XK_f, setlayout, {.v = &layouts[2]}},
    {MODKEY, XK_u, setlayout, {.v = &layouts[3]}},
    {MODKEY, XK_space, setlayout, {0}},
    {MODKEY | ShiftMask, XK_space, togglefloating, {0}},
    {MODKEY, XK_0, view, {.ui = ~0}},
    {MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},
    {0, XF86XK_AudioLowerVolume, spawn, {.v = downvol}},
    {0, XF86XK_AudioMute, spawn, {.v = mutevol}},
    {0, XF86XK_AudioRaiseVolume, spawn, {.v = upvol}},
    {MODKEY, XK_comma, focusmon, {.i = -1}},
    {MODKEY, XK_period, focusmon, {.i = +1}},
    {MODKEY | ShiftMask, XK_comma, tagmon, {.i = -1}},
    {MODKEY | ShiftMask, XK_period, tagmon, {.i = +1}},
	{ MODKEY,                       XK_n,      togglealttag,   {0} },
    {MODKEY, XK_minus, setgaps, {.i = -1}},
    {MODKEY, XK_equal, setgaps, {.i = +1}},
    {MODKEY | ShiftMask, XK_equal, setgaps, {.i = 0}},
    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7) TAGKEYS(XK_9, 8) { MODKEY | ShiftMask, XK_r, quit, {0}},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function argument
     */
    {ClkLtSymbol, 0, Button1, setlayout, {0}},
    {ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]}},
    {ClkWinTitle, 0, Button2, zoom, {0}},
    {ClkStatusText, 0, Button2, spawn, {.v = term1cmd}},
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
};
