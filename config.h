/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 0;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=14" };
static const char dmenufont[]       = "monospace:size=14";
static const char col_gray1[]       = "#111111";
static const char col_gray2[]       = "#222222";
static const char col_gray3[]       = "#444444";
static const char col_gray4[]       = "#999999";
static const char col_cyan[]        = "#AAAACC";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_gray2, col_gray3 },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "brd" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
	{ "Sublime",  NULL,       NULL,       2,            0,           -1 },
	{ "eagle",    NULL,       NULL,       4,            0,           -1 },
	{ "thunderbird", NULL,    NULL,       7,            0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.58; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask // Left Win key. Mod1Mask is left alt key
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };


// custom commands for function keys
// note these don't use MODKEY and are just mapped directly to the function keys
static const char *newmonitor[] = { "xrandr", "--output", "HDMI2", "--auto", "--above", "eDP1", NULL };
static const char *volup[] = { "amixer", "set", "Master", "5%+", "-q", NULL };
static const char *volmute[] = { "amixer", "-D", "pulse", "set", "Master", "1+", "toggle", "-q", NULL };
static const char *voldn[] = { "amixer", "set", "Master", "5%-", "-q", NULL };
static const char *network[] = { "st", "nmtui", NULL };

static const char *notouch[] = { "xinput", "disable", "\"SynPS/2 Synaptics Touchpad\"", NULL };
static const char *touchon[] = { "xinput", "enable", "\"SynPS/2 Synaptics Touchpad\"", NULL };

static const char *lowbright[] = { "xrandr", "--output", "eDP1", "--brightness", "0.45", NULL };
static const char *midlowbright[] = { "xrandr", "--output", "eDP1", "--brightness", "0.6", NULL };
static const char *normalbright[] = { "xrandr", "--output", "eDP1", "--brightness", "0.75", NULL };
static const char *bright[] = { "xrandr", "--output", "eDP1", "--brightness", "1.0", NULL };

// MOD+F7 = run xrandr --auto (to detect new monitor)

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
        { 0,                            XK_F7,     spawn,          {.v = newmonitor } },
        { 0,                            XK_F1,     spawn,          {.v = volmute } },
        { 0,                            XK_F2,     spawn,          {.v = voldn } },
        { 0,                            XK_F3,     spawn,          {.v = volup } },
        { 0,                            XK_F8,     spawn,          {.v = network } },
        { 0,                            XK_F12,    spawn,          {.v = notouch } },
        { MODKEY,                       XK_F12,    spawn,          {.v = touchon } },
        { MODKEY,                       XK_F5,     spawn,          {.v = lowbright } },
        { 0,                            XK_F5,     spawn,          {.v = midlowbright } },
        { 0,                            XK_F6,     spawn,          {.v = normalbright } },
        { MODKEY,                       XK_F6,     spawn,          {.v = bright } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
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

