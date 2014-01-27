/*

   "Classic" Digital Watch Pebble App

 */

// Standard includes
#include "pebble.h"

// Currently set to two
#define lessonNum 2

// App-specific data
Window *window; // All apps must have at least one window
TextLayer *time_layer; // The clock
struct tm* lessonArray[lessonNum];


// Called once per second
static void handle_second_tick(struct tm* tick_time, TimeUnits units_changed) {

  static char time_text[] = "123456789"; // Needs to be static because it's used by the system later.
	int index = 0;
	int timeint = -1;
	while (timeint < 0 && index < lessonNum){
	timeint = (int)difftime(tick_time, mktime(lessonArray[index]));
	++index;
	}	
	
	
  //strftime(time_text, sizeof(time_text), "%T", tick_time);
  snprintf(time_text, sizeof(time_text), "%T", timeint); 
  text_layer_set_text(time_layer, time_text);
}


// Handle the start-up of the app
static void do_init(void) {

  // Create our app's base window
  window = window_create();
  window_stack_push(window, true);
  window_set_background_color(window, GColorBlack);
  initLessons();

  // Init the text layer used to show the time
  time_layer = text_layer_create(GRect(29, 54, 144-40 /* width */, 168-54 /* height */));
  text_layer_set_text_color(time_layer, GColorWhite);
  text_layer_set_background_color(time_layer, GColorClear);
  text_layer_set_font(time_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));]
  
  // INit the lessonArray
  initLessonArray();

  // Ensures time is displayed immediately (will break if NULL tick event accessed).
  // (This is why it's a good idea to have a separate routine to do the update itself.)
  time_t now = time(NULL);
  struct tm *current_time = localtime(&now);
  handle_second_tick(current_time, SECOND_UNIT);
  tick_timer_service_subscribe(SECOND_UNIT, &handle_second_tick);

  layer_add_child(window_get_root_layer(window), text_layer_get_layer(time_layer));
}

void initLessonArray(void){
	//IMPLEMENT
}

static void do_deinit(void) {
  text_layer_destroy(time_layer);
  window_destroy(window);
}

// The main event/run loop for our app
int main(void) {
  do_init();
  app_event_loop();
  do_deinit();
}
