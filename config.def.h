/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>
/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Hack-Regular:size=10" };
static const char dmenufont[]       = "Hack-Regular:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_purple[]	    = "#4c2172";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_purple,  col_purple  },
};

static const char *const autostart[] = {
	"nitrogen", "--restore", NULL,
	"aslstatus", NULL,
	"xset", "r", "rate", "300", "70", NULL,
	"setxkbmap", "-option", "caps:swapescape", NULL,
        "xinput", "set-prop", "15", "321", "0", NULL,
	"xinput", "set-prop", "15", "313", "1", NULL,
        "numlockx", "on", NULL,
	"xset", "b", "off", NULL,
	"xsetroot", "-cursor_name", "left_ptr", NULL,
        "/usr/lib/polkit-gnome/polkit-gnome-authentication-agent-1", NULL,
	"picom", NULL,
	"dunst", NULL,
	"mpv", "--no-video", "/home/kellyr/.config/bspwm/startup.mp3", NULL,
        "emacs", "--daemon", NULL,
	"xfce4-power-manager", NULL,
	/* "xmodmap", "-e", "'keycode 135 = Multi_key'", NULL, */
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):''
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1,        0  },
	{ "firefox",  NULL,       NULL,       1 << 1,       0,           -1,        0  },
	{ "mpv",      NULL,       NULL,       1 << 3,       0,           -1,        0  },
	{ "vlc",      NULL,       NULL,       1 << 3,       0,           -1,        0  },
	{ NULL,       NULL,   "scratchpad",   0,            1,           -1,       's' },
	{ NULL,       NULL,   "fmscratch",    0,            1,           -1,       'f' },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int attachdirection = 2;    /* 0 default, 1 above, 2 aside, 3 below, 4 bottom, 5 top */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "DD",       doubledeck },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(CHAIN,KEY,TAG) \
	{ MODKEY,                       CHAIN,    KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           CHAIN,    KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             CHAIN,    KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, CHAIN,    KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre miniwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "alacritty", NULL };

/*First arg only serves to match against key in rules*/
static const char *scratchpadcmd[] = {"s", "alacritty", "-t", "scratchpad", NULL};
static const char *fmpadcmd[] = {"f", "alacritty", "-t", "fmscratch", "-e", "lfub", NULL};

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY|ShiftMask,             -1,	XK_Return, spawn,          SHCMD("dmenu_run-better.sh") },
	{ MODKEY,	                -1,	XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,		        -1,	XK_o,      spawn,          SHCMD("dmenufm") },
	{ MODKEY,		        -1,	XK_F2,     spawn,          SHCMD("xrandr --output HDMI-0 --auto --left-of LVDS-1-1 && nitrogen --head=0 --random --set-scaled && nitrogen --head=1 --random --set-scaled") },
	{ 0,		                -1,	XF86XK_AudioLowerVolume,      spawn,          SHCMD("amixer set Master 5%- unmute") },
	{ 0,		                -1,	XF86XK_AudioRaiseVolume,      spawn,          SHCMD("amixer set Master 5%+ unmute") },
	{ 0,		                -1,	XF86XK_AudioMute,             spawn,          SHCMD("amixer set Master toggle") },
/*	{ MODKEY|ShiftMask,	        -1,	XK_f,      spawn,          SHCMD("pcmanfm") },*/
	{ MODKEY|ShiftMask,	        -1,	XK_d,      spawn,          SHCMD("rofi -show drun -show-icons") },
	{ MODKEY,	                -1,	XK_w, 	   spawn,          SHCMD("firefox") },
	{ MODKEY,	                -1,	XK_e, 	   spawn,          SHCMD("emacsclient -c -a 'alacritty -e nvim'") },
	{ MODKEY,                       -1,	XK_grave,  togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY|ShiftMask,             -1,	XK_grave,  togglescratch,  {.v = fmpadcmd } },
	{ MODKEY,                       -1,	XK_b,      togglebar,      {0} },
	{ MODKEY|ShiftMask,             -1,	XK_j,      rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,             -1,	XK_k,      rotatestack,    {.i = -1 } },
	{ MODKEY,                       -1,	XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       -1,	XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ControlMask,           -1,	XK_j,      pushdown,     {.i = +1 } },
	{ MODKEY|ControlMask,           -1,	XK_k,      pushup,     {.i = -1 } },
	{ MODKEY,                       -1,	XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       -1,	XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       -1,	XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       -1,	XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       -1,	XK_z,      zoom,           {0} },
	{ MODKEY,                       -1,	XK_Tab,    view,           {0} },
	{ MODKEY,                       -1,	XK_q,      killclient,     {0} },
	{ MODKEY,                       -1,	XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       -1,	XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       -1,	XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       -1,	XK_r,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       -1,	XK_space,  setlayout,      {0} },
	{ MODKEY,                       -1,	XK_Delete, togglefloating, {0} },
	{ MODKEY,                       -1,	XK_s,      togglesticky,   {0} },
	{ MODKEY|ShiftMask,             -1,	XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       -1,	XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             -1,	XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       -1,	XK_bracketleft,  focusmon,       {.i = -1 } },
	{ MODKEY,                       -1,	XK_bracketright, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             -1,	XK_bracketleft,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             -1,	XK_bracketright, tagmon,         {.i = +1 } },
	TAGKEYS(                        -1,	XK_1,                      0)
	TAGKEYS(                        -1,	XK_2,                      1)
	TAGKEYS(                        -1,	XK_3,                      2)
	TAGKEYS(                        -1,	XK_4,                      3)
	TAGKEYS(                        -1,	XK_5,                      4)
	TAGKEYS(                        -1,	XK_6,                      5)
	TAGKEYS(                        -1,	XK_7,                      6)
	TAGKEYS(                        -1,	XK_8,                      7)
	TAGKEYS(                        -1,	XK_9,                      8)
	{ MODKEY|ShiftMask,             -1,	XK_x,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

