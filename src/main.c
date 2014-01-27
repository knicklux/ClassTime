/*

   "Classic" Digital Watch Pebble App

 */

// Standard includes
#include "pebble.h"

#define lessonNum 16

//Define Debug true or false
#define DEBUG 1

// App-specific data
Window *window; // All apps must have at least one window
TextLayer *time_layer; // The clock
struct tm* lessonArray[lessonNum];


// Called once per second
static void handle_second_tick(struct tm* tick_time, TimeUnits units_changed) {

  static char time_text[] = "123456789"; // Needs to be static because it's used by the system later.
	int index = 0;
	int timeint = -1;
		
#if DEBUG
	//If DEBUG, test handle_second displaying a random number
	timeint = rand();
#else
	while (timeint < 0 && index < lessonNum){
	timeint = (int)difftime(tick_time, mktime(lessonArray[index]));
	++index;
	}
#endif
	
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
  text_layer_set_font(time_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
  
  // INIT the lessonArray
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
	int sec_delay = 49;
        
	static struct tm lesson_onetwo_b;
	lesson_onetwo_b.tm_sec = sec_delay;
	lesson_onetwo_b.tm_min = 54;        
	lesson_onetwo_b.tm_hour = 7;

	static struct tm lesson_onetwo_e;
	lesson_onetwo_e.tm_sec = sec_delay;
	lesson_onetwo_e.tm_min = 24;
	lesson_onetwo_e.tm_hour = 9;
        
	static struct tm lesson_three_b;
	lesson_three_b.tm_sec = sec_delay;
	lesson_three_b.tm_min = 44;
	lesson_three_b.tm_hour = 9;
        
	static struct tm lesson_three_e;
	lesson_three_e.tm_sec = sec_delay;
	lesson_three_e.tm_min = 29;
	lesson_three_e.tm_hour = 10;
        
	static struct tm lesson_four_b;
	lesson_four_b.tm_sec = sec_delay;
	lesson_four_b.tm_min = 34;
	lesson_four_b.tm_hour = 10;
        
	static struct tm lesson_four_e;
	lesson_four_e.tm_sec = sec_delay;
	lesson_four_e.tm_min = 19;
	lesson_four_e.tm_hour = 11;
        
	static struct tm lesson_five_b;
	lesson_five_b.tm_sec = sec_delay;
	lesson_five_b.tm_min = 34;
	lesson_five_b.tm_hour = 11;
        
	static struct tm lesson_five_e;
	lesson_five_e.tm_sec = sec_delay;
	lesson_five_e.tm_min = 19;
	lesson_five_e.tm_hour = 12;
        
	static struct tm lesson_six_b;
	lesson_six_b.tm_sec = sec_delay;
	lesson_six_b.tm_min = 24;
	lesson_six_b.tm_hour = 12;
        
	static struct tm lesson_six_e;
	lesson_six_e.tm_sec = sec_delay;
	lesson_six_e.tm_min = 9;
	lesson_six_e.tm_hour = 13;

	static struct tm lesson_seven_b;
	lesson_seven_b.tm_sec = sec_delay;
	lesson_seven_b.tm_min = 59;
	lesson_seven_b.tm_hour = 13;

	static struct tm lesson_seven_e;
	lesson_seven_e.tm_sec = sec_delay;
	lesson_seven_e.tm_min = 44;
	lesson_seven_e.tm_hour = 14;
        
	static struct tm lesson_eight_b;
	lesson_eight_b.tm_sec = sec_delay;
	lesson_eight_b.tm_min = 49;
	lesson_eight_b.tm_hour = 14;
        
	static struct tm lesson_eight_e;
	lesson_eight_e.tm_sec = sec_delay;
	lesson_eight_e.tm_min = 34;
	lesson_eight_e.tm_hour = 15;

	static struct tm lesson_nineten_b;
	lesson_nineten_b.tm_sec = sec_delay;
	lesson_nineten_b.tm_min = 44;
	lesson_nineten_b.tm_hour = 15;
        
	static struct tm lesson_nineten_e;
	lesson_nineten_e.tm_sec = sec_delay;
	lesson_nineten_e.tm_min = 14;
	lesson_nineten_e.tm_hour = 17;
        
	lessonArray[0] = &lesson_onetwo_b;
	lessonArray[1] = &lesson_onetwo_e;
	lessonArray[2] = &lesson_three_b;
	lessonArray[3] = &lesson_three_e;
	lessonArray[4] = &lesson_four_b;
	lessonArray[5] = &lesson_four_e;
	lessonArray[6] = &lesson_five_b;
	lessonArray[7] = &lesson_five_e;
	lessonArray[8] = &lesson_six_b;
	lessonArray[9] = &lesson_six_e;
	lessonArray[10] = &lesson_seven_b;
	lessonArray[11] = &lesson_seven_e;
	lessonArray[12] = &lesson_eight_b;
	lessonArray[13] = &lesson_eight_e;
	lessonArray[14] = &lesson_nineten_b;
	lessonArray[15] = &lesson_nineten_e;
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
