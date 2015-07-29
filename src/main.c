#include <pebble.h>

#define COUNT_PKEY 1
#define COUNT_DEFAULT 0
#define HP_NUM 01
#define ATK_NUM 02
#define DEF_NUM 03
#define SPATK_NUM 04
#define SPDEF_NUM 05
#define SPD_NUM 06
#define POOL_NUM 07
#define POOL_DEFAULT 510
  
#define REPEAT_INTERVAL 50
	
Window *window;
TextLayer *text_layer;
TextLayer *hp_num_layer;
TextLayer *atk_num_layer;
TextLayer *def_num_layer;
TextLayer *spatk_num_layer;
TextLayer *spdef_num_layer;
TextLayer *spd_num_layer;
TextLayer *total_num_layer;
InverterLayer *inv_layer;

static GBitmap *s_bg_bitmap;
static BitmapLayer *s_bitmap_layer;

int selection = 0;

GBitmap *action_icon_plus;
GBitmap *action_icon_minus;
GBitmap *action_icon_next;

ActionBarLayer *action_bar;

static int count = COUNT_DEFAULT;

struct Pokemon{
  char *name;
  int hp;
  int atk;
  int def;
  int spatk;
  int spdef;
  int spd;
  int total;
  int pool;
};

struct Pokemon p1;

void update() {
  //For testing layout only, comment out before release
  /*
  p1.hp=255;
  p1.atk=255;
  p1.def=255;
  p1.spatk=255;
  p1.spdef=255;
  p1.spd=255;
  */
  //i don't know how computer
  //please to help
  
  p1.total= (p1.hp+p1.atk+p1.def+p1.spatk+p1.spdef+p1.spd);
  
  static char hpbuff[10];
	snprintf(hpbuff, sizeof(hpbuff), "%i", p1.hp);
	text_layer_set_text(hp_num_layer, hpbuff);
  
	static char atkbuff[10];
	snprintf(atkbuff, sizeof(atkbuff), "%i", p1.atk);
	text_layer_set_text(atk_num_layer, atkbuff);
  
  static char defbuff[10];
	snprintf(defbuff, sizeof(defbuff), "%i", p1.def);
	text_layer_set_text(def_num_layer, defbuff);
  
  static char spatkbuff[10];
	snprintf(spatkbuff, sizeof(spatkbuff), "%i", p1.spatk);
	text_layer_set_text(spatk_num_layer, spatkbuff);

  static char spdefbuff[10];
	snprintf(spdefbuff, sizeof(spdefbuff), "%i", p1.spdef);
	text_layer_set_text(spdef_num_layer, spdefbuff);

  static char spdbuff[10];
	snprintf(spdbuff, sizeof(spdbuff), "%i", p1.spd);
	text_layer_set_text(spd_num_layer, spdbuff);
  
  static char totalbuff[10];
	snprintf(totalbuff, sizeof(totalbuff), "%i", p1.total);
	text_layer_set_text(total_num_layer, totalbuff);
  
  switch(selection){
      case 0:
      inverter_layer_destroy(inv_layer);
      inv_layer = inverter_layer_create(GRect(0, 60, 32, 15));
      layer_add_child(window_get_root_layer(window), (Layer*) inv_layer);
      break;
      case 1:
      inverter_layer_destroy(inv_layer);
      inv_layer = inverter_layer_create(GRect(35, 60, 32, 15));
      layer_add_child(window_get_root_layer(window), (Layer*) inv_layer);
      break;
      case 2:
      inverter_layer_destroy(inv_layer);
      inv_layer = inverter_layer_create(GRect(70, 60, 32, 15));
      layer_add_child(window_get_root_layer(window), (Layer*) inv_layer);
      break;
      case 3:
      inverter_layer_destroy(inv_layer);
      inv_layer = inverter_layer_create(GRect(0, 93, 32, 14));
      layer_add_child(window_get_root_layer(window), (Layer*) inv_layer);
      break;
      case 4:
      inverter_layer_destroy(inv_layer);
      inv_layer = inverter_layer_create(GRect(35, 93, 32, 14));
      layer_add_child(window_get_root_layer(window), (Layer*) inv_layer);
      break;
      case 5:
      inverter_layer_destroy(inv_layer);
      inv_layer = inverter_layer_create(GRect(70, 93, 32, 14));
      layer_add_child(window_get_root_layer(window), (Layer*) inv_layer);
      break;
    }
}

void increment() {
  if(p1.pool>0){
    switch(selection){
      case 0:
      if(p1.hp<255){p1.hp++;p1.pool--;}
      break;
      case 1:
      if(p1.atk<255){p1.atk++;p1.pool--;}
      break;
      case 2:
      if(p1.def<255){p1.def++;p1.pool--;}
      break;
      case 3:
      if(p1.spatk<255){p1.spatk++;p1.pool--;}
      break;
      case 4:
      if(p1.spdef<255){p1.spdef++;p1.pool--;}
      break;
      case 5:
      if(p1.spd<255){p1.spd++;p1.pool--;}
      break;
    }
  }
}

void decrement() {
  if(p1.pool<510){
    switch(selection){
      case 0:
      if(p1.hp!=0){p1.hp--;p1.pool++;}
      break;
      case 1:
      if(p1.atk!=0){p1.atk--;p1.pool++;}
      break;
      case 2:
      if(p1.def!=0){p1.def--;p1.pool++;}
      break;
      case 3:
      if(p1.spatk!=0){p1.spatk--;p1.pool++;}
      break;
      case 4:
      if(p1.spdef!=0){p1.spdef--;p1.pool++;}
      break;
      case 5:
      if(p1.spd!=0){p1.spd--;p1.pool++;}
      break;
    } 
  }
}

void next(){
  if(selection!=5){
    selection++;
  }
  else{
    selection=0;
  }
}

void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  next();
	update();
}

void down_click_handler(ClickRecognizerRef recognizer, void *context) {
	decrement();
	update();
}

void up_click_handler(ClickRecognizerRef recognizer, void *context) {
	increment();
	update();
}

void click_config_provider(void *context) {
	window_single_repeating_click_subscribe(BUTTON_ID_SELECT, REPEAT_INTERVAL, (ClickHandler) select_click_handler);
	window_single_repeating_click_subscribe(BUTTON_ID_UP, REPEAT_INTERVAL, (ClickHandler) up_click_handler);
	window_single_repeating_click_subscribe(BUTTON_ID_DOWN, REPEAT_INTERVAL, (ClickHandler) down_click_handler);
}

void window_load(Window *window) {//------------------------------------------------------------------------------------------------ window_load

  Layer *layer = window_get_root_layer(window);
  
  s_bg_bitmap = gbitmap_create_with_resource(RESOURCE_ID_EVBG_APLITE);
  s_bitmap_layer = bitmap_layer_create(GRect(0,0,144,168));
  bitmap_layer_set_bitmap(s_bitmap_layer,s_bg_bitmap);
  
	hp_num_layer = text_layer_create(GRect(0,66,32,32));
  atk_num_layer = text_layer_create(GRect(32+3, 66, 32, 32));
  def_num_layer = text_layer_create(GRect(64+6, 66, 32, 32));
  spatk_num_layer = text_layer_create(GRect(0, 98, 32, 32));
  spdef_num_layer = text_layer_create(GRect(32+3, 98, 32, 32));
  spd_num_layer = text_layer_create(GRect(64+6, 98, 32, 32));
  total_num_layer = text_layer_create(GRect(64+6, 123, 32, 32));
  
  text_layer_set_font(hp_num_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
	text_layer_set_background_color(hp_num_layer, GColorClear);
	text_layer_set_text_alignment(hp_num_layer, GTextAlignmentCenter);
	
  text_layer_set_font(atk_num_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
	text_layer_set_background_color(atk_num_layer, GColorClear);
	text_layer_set_text_alignment(atk_num_layer, GTextAlignmentCenter);
  
  text_layer_set_font(def_num_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
	text_layer_set_background_color(def_num_layer, GColorClear);
	text_layer_set_text_alignment(def_num_layer, GTextAlignmentCenter);
  
  text_layer_set_font(spatk_num_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
	text_layer_set_background_color(spatk_num_layer, GColorClear);
	text_layer_set_text_alignment(spatk_num_layer, GTextAlignmentCenter);
  
  text_layer_set_font(spdef_num_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
	text_layer_set_background_color(spdef_num_layer, GColorClear);
	text_layer_set_text_alignment(spdef_num_layer, GTextAlignmentCenter);
  
  text_layer_set_font(spd_num_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
	text_layer_set_background_color(spd_num_layer, GColorClear);
	text_layer_set_text_alignment(spd_num_layer, GTextAlignmentCenter);
  
  text_layer_set_font(total_num_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  text_layer_set_text_color(total_num_layer, GColorWhite);
	text_layer_set_background_color(total_num_layer, GColorClear);
	text_layer_set_text_alignment(total_num_layer, GTextAlignmentCenter);
  
  inv_layer = inverter_layer_create(GRect(0, 60, 32, 15));
  
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_bitmap_layer));
  layer_add_child(layer, text_layer_get_layer(hp_num_layer));
  layer_add_child(layer, text_layer_get_layer(atk_num_layer));
  layer_add_child(layer, text_layer_get_layer(def_num_layer));
  layer_add_child(layer, text_layer_get_layer(spatk_num_layer));
  layer_add_child(layer, text_layer_get_layer(spdef_num_layer));
  layer_add_child(layer, text_layer_get_layer(spd_num_layer));
  layer_add_child(layer, text_layer_get_layer(total_num_layer));
  
  layer_add_child(window_get_root_layer(window), (Layer*) inv_layer);
  
  action_bar = action_bar_layer_create();
	action_bar_layer_add_to_window(action_bar, window);
	action_bar_layer_set_click_config_provider(action_bar, click_config_provider);

	action_bar_layer_set_icon(action_bar, BUTTON_ID_UP, action_icon_plus);
	action_bar_layer_set_icon(action_bar, BUTTON_ID_SELECT, action_icon_next);
	action_bar_layer_set_icon(action_bar, BUTTON_ID_DOWN, action_icon_minus);
  
  update();
}

void window_unload(Window *window) {
	text_layer_destroy(text_layer);
	action_bar_layer_destroy(action_bar);
}

void init() { //------------------------------------------------------------------------------------------------ Init
  
	action_icon_plus = gbitmap_create_with_resource(RESOURCE_ID_PLUS_WHITE);
  action_icon_next = gbitmap_create_with_resource(RESOURCE_ID_NEXT_WHITE);
	action_icon_minus = gbitmap_create_with_resource(RESOURCE_ID_MINUS_WHITE);

	window = window_create();

	window_set_window_handlers(window, (WindowHandlers) {
		.load = window_load,
		.unload = window_unload,
	});

	count = persist_exists(COUNT_PKEY) ? persist_read_int(COUNT_PKEY) : COUNT_DEFAULT;
  p1.hp = persist_exists(HP_NUM) ? persist_read_int(HP_NUM) : COUNT_DEFAULT;
  p1.atk = persist_exists(ATK_NUM) ? persist_read_int(ATK_NUM) : COUNT_DEFAULT;
  p1.def = persist_exists(DEF_NUM) ? persist_read_int(DEF_NUM) : COUNT_DEFAULT;
  p1.spatk = persist_exists(SPATK_NUM) ? persist_read_int(SPATK_NUM) : COUNT_DEFAULT;
  p1.spdef = persist_exists(SPDEF_NUM) ? persist_read_int(SPDEF_NUM) : COUNT_DEFAULT;
  p1.spd = persist_exists(SPD_NUM) ? persist_read_int(SPD_NUM) : COUNT_DEFAULT;
  
  p1.pool= persist_exists(POOL_NUM) ? persist_read_int(POOL_NUM) : POOL_DEFAULT;
  
  window_stack_push(window, true);
}

void deinit() {//------------------------------------------------------------------------------------------------ deinit
	//persist_write_int(COUNT_PKEY, count);
  persist_write_int(HP_NUM, p1.hp);
  persist_write_int(ATK_NUM, p1.atk);
  persist_write_int(DEF_NUM, p1.def);
  persist_write_int(SPATK_NUM, p1.spatk);
  persist_write_int(SPDEF_NUM, p1.spdef);
  persist_write_int(SPD_NUM, p1.spd);
  persist_write_int(POOL_NUM, p1.pool);
  
	window_destroy(window);
	gbitmap_destroy(action_icon_plus);
	gbitmap_destroy(action_icon_minus);
	gbitmap_destroy(action_icon_next);
}

int main() {//------------------------------------------------------------------------------------------------ main
	init();
	app_event_loop();
	deinit();
}