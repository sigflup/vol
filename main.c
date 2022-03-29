#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "./gui/libgui.h"

#include "back.xpm"
 
FILE *level;

group_t *main_grp;
struct object_t *knob_object;

int get_level(void) {
 int lev;
 level = popen("mixerctl outputs.master", "r");
 fscanf(level, "outputs.master=%d", &lev);
 pclose(level);
 return lev;
}

void set_level(int a) {
 char buf[1000];
 snprintf(buf, 1000, "mixerctl outputs.master=%d,%d",a,a);
 system(buf);
}

int knob_tick(struct object_t *obj, int data) {
 set_level(knob_object->param.d1);
 return RET_OK;
}

int main(void) {
 obj_param_t tmp_parm;
 globl_flags=0;

 printf("%d\n", getuid());

 init_gui(200,51, 0);

 SET_COLOR(globl_fg, 		200  ,200   ,200);
 SET_COLOR(globl_bg, 		33 ,33 ,33);
 main_grp = new_group(0,0, 200,51, 0,0);
 
 PARM(0,0,200,51,&globl_fg, &globl_bg, LOAD_XPM_FROM_ARRAY, proc_bitmap);
 tmp_parm.dp1 = back_xpm;
 new_obj(main_grp, &tmp_parm);

 PARM(100-21,0,41,51, &globl_fg, &globl_bg, CALL_BUTTON,proc_knob);
 tmp_parm.d1 = get_level();
 tmp_parm.d2 = 255;
 tmp_parm.callback = knob_tick;
 knob_object = new_obj(main_grp, &tmp_parm);

 group_loop(main_grp);

 return 0;
}
