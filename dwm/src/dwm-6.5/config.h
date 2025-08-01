/* See LICENSE file for copyright and license details. */

/*Systray (системный трей)*/
static const int showsystray = 1;         // Включить системный трей (1 — включён, 0 — выключен)
static const unsigned int systraypinning = 0;    // Закрепление трея за монитором (0 — текущий монитор)
static const unsigned int systrayonleft = 3;     // Положение трея (0 — справа от статуса)
static const unsigned int systrayspacing = 8;    // Отступы между иконками
static const int systraypinningfailfirst = 1;    // Если закрепление не удалось — на первый монитор
static const int systrayiconsize = 0;            // Размер иконок (0 — авто)

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Nord Font:size=10" };
static const char dmenufont[]       = "Nord Font:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#000000";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = {
    "1: Search",
    "2: Work",
    "3: Pling",
    "4: Notes",
    "5: AI",
    "6: Study",
    "7: Training",
    "8: Chats",
    "9: Music"
};

static const Rule rules[] = {
    /* class            instance    title       tags mask     isfloating   monitor */
    { "google-chrome",  NULL,       NULL,       1 << 0,       0,           -1 },
	//  { "Rofi",           NULL,       NULL,       1 << 0,       1,           -1 },
   // { "Alacritty",      NULL,       NULL,       1 << 0,       0,           -1 },
   // { "telegram-desktop", NULL,     NULL,       1 << 7,       0,           -1 },
    { "yandex-music",   NULL,       NULL,       1 << 8,       0,           -1 },
    // ... другие правила ...
};


/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
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
static const char *termcmd[]  = { "alacritty", NULL };
static const char *roficmd[]   = { "rofi", "-show", "drun", "-show-icons", NULL };
static const char *nvimcmd[]   = { "alacritty", "-e", "nvim", NULL };
static const char *vscodecmd[] = { "code", NULL };
static const char *chromecmd[]    = { "google-chrome", NULL };
static const char *obsidiancmd[]  = { "obsidian", NULL };
static const char *yandexcmd[]    = { "yandex-music", NULL };
static const char *screenshotcmd[] = { "scrot", "-s", "-e", "xclip -selection clipboard -t image/png -i $f", "/tmp/screenshot_%Y%m%d_%H%M%S.png", NULL };
static const char *fullscreenshotcmd[] = { "scrot", "-e", "xclip -selection clipboard -t image/png -i $f", "/tmp/screenshot_%Y%m%d_%H%M%S.png", NULL };

void
shiftview(const Arg *arg) {
    Arg shifted;
    if(arg->i > 0) // right shift
        shifted.ui = (selmon->tagset[selmon->seltags] << arg->i)
           | (selmon->tagset[selmon->seltags] >> (LENGTH(tags) - arg->i));
    else // left shift  
        shifted.ui = selmon->tagset[selmon->seltags] >> (- arg->i)
           | selmon->tagset[selmon->seltags] << (LENGTH(tags) + arg->i);
    view(&shifted);
}

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,            					  XK_r,      spawn, 				 {.v = roficmd } },
  { MODKEY,             				  XK_n,      spawn, 				 {.v = nvimcmd } },
  { MODKEY,            					  XK_v,      spawn,          {.v = vscodecmd } },
  { MODKEY|ShiftMask,     				XK_s,      spawn,          {.v = screenshotcmd } },        /* Выделенная область */
	{ MODKEY|ShiftMask,     				XK_Print,  spawn,          {.v = fullscreenshotcmd } },    /* Весь экран */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } }, 
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,              					XK_g,      spawn,          {.v = chromecmd } },   // Win+g — Google Chrome
	{ MODKEY,              					XK_o,      spawn,          {.v = obsidiancmd } }, // Win+o — Obsidian
	{ MODKEY,              					XK_y,      spawn,          {.v = yandexcmd } },   // Win+y — Яндекс Музыка
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
	{ 0,                    				XK_Print,  spawn,          {.v = fullscreenshotcmd } },
	// Циклическое переключение между тегами стрелками
{ MODKEY,                       XK_Left,   shiftview,      {.i = -1 } },
{ MODKEY,                       XK_Right,  shiftview,      {.i = +1 } },

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
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

