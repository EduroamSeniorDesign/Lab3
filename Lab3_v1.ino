#include <Adafruit_GFX.h>    // Core graphics library
#include <Fonts/FreeSans9pt7b.h> // 

#include <Adafruit_GFX.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_ILI9341.h>
#include <Adafruit_FT6206.h>

Adafruit_FT6206 ts = Adafruit_FT6206();

#define TFT_CS 10
#define TFT_DC 9
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

// Screen size in pixels
#define FULL_SCREEN_WIDTH 320
#define FULL_SCREEN_HEIGHT 240

// This area contains the current temp, temp adjustment, and 'Hold Temp' button
#define TEMP_FRAME_X 0
#define TEMP_FRAME_Y 40
#define TEMP_FRAME_W 260
#define TEMP_FRAME_H 150

#define TEMP_TEXT_X TEMP_FRAME_X + 6
#define TEMP_TEXT_Y TEMP_FRAME_Y  + TEMP_FRAME_H * 0.4

#define HOLD_STATUS_X HOLD_TEMP_X + 12
#define HOLD_STATUS_Y HOLD_TEMP_Y + 20
#define HOLD_STATUS_W MAIN_UP_ARROW_W
#define HOLD_STATUS_H 20

// Displays current function
#define CURRENT_FUNCTION_X 0
#define CURRENT_FUNCTION_Y 0
#define CURRENT_FUNCTION_W FULL_SCREEN_WIDTH*4/15 + 3
#define CURRENT_FUNCTION_H TEMP_FRAME_Y - COMPONENT_BORDER

#define CURRENT_FUNC_TEXT_X CURRENT_FUNCTION_X + 10
#define CURRENT_FUNC_TEXT_Y CURRENT_FUNCTION_Y + TOP_MARGIN + 18

#define FUNC_DATE_TIME_SIZE 1
#define FUNC_DATE_TIME_Y

#define TIME_TEXT_X TIME_X + 6
#define TIME_TEXT_Y TIME_Y + TOP_MARGIN + 18

// Date area
#define DATE_X CURRENT_FUNCTION_W + 2
#define DATE_Y 0
#define DATE_W FULL_SCREEN_WIDTH*2/5
#define DATE_H TEMP_FRAME_Y - COMPONENT_BORDER
// Date Text
#define DATE_TEXT_X DATE_X + 8
#define DATE_TEXT_Y DATE_Y + TOP_MARGIN + 18 
#define DATE_TEXT_SIZE 1

// Time area
#define TIME_X DATE_X + DATE_W + 2
#define TIME_Y 0
#define TIME_W FULL_SCREEN_WIDTH/3 - 6
#define TIME_H TEMP_FRAME_Y - COMPONENT_BORDER

#define TOP_NAV_H TEMP_FRAME_Y - COMPONENT_BORDER
#define BOTTOM_MARGIN 5

/********************* Bottom Nav constants ************************/
// Dimensions for bottom navigation bar
#define BOTTOM_NAV_X 0
#define BOTTOM_NAV_Y TEMP_FRAME_Y + TEMP_FRAME_H + COMPONENT_BORDER
#define BOTTOM_NAV_W TEMP_FRAME_W
#define BOTTOM_NAV_H 50 - BOTTOM_MARGIN
//240 - BOTTOM_NAV_Y - BOTTOM_MARGIN

#define DEFAULT_TXT_SIZE 1
#define BOTTOM_NAV_TXT_Y BOTTOM_NAV_Y + 28

#define HEAT_BTN_X BOTTOM_NAV_X
#define HEAT_BTN_Y BOTTOM_NAV_Y
#define HEAT_TXT_X 10
#define HEAT_BTN_W TEMP_FRAME_W/4

#define AC_TXT_X AC_BTN_X + 22
#define AC_BTN_X HEAT_BTN_W + COMPONENT_BORDER
#define AC_BTN_W TEMP_FRAME_W/4

#define AUTO_TXT_X AUTO_BTN_X + 10
#define AUTO_BTN_X AC_BTN_X + AC_BTN_W + COMPONENT_BORDER
#define AUTO_BTN_W TEMP_FRAME_W/4

#define OFF_TXT_X OFF_BTN_X + 10
#define OFF_BTN_X AUTO_BTN_X + AUTO_BTN_W + COMPONENT_BORDER
#define OFF_BTN_W TEMP_FRAME_W - (AUTO_BTN_X + AUTO_BTN_W) - 2


// Set Points area
#define SET_POINT_X TEMP_FRAME_W + COMPONENT_BORDER
#define SET_POINT_Y TEMP_FRAME_Y
#define SET_POINT_W FULL_SCREEN_WIDTH - SET_POINT_X -5
#define SET_POINT_H 80

#define SET_POINT_TEXT_X SET_POINT_X + 3
#define SET_POINT_TEXT_Y SET_POINT_Y + 15
#define VERTICAL_TEXT_OFFSET 15

// Hold button location and dimensions
#define HOLD_TEMP_X TEMP_FRAME_W * 0.70
#define HOLD_TEMP_Y TEMP_FRAME_H * 0.66
#define HOLD_TEMP_W TEMP_FRAME_W * 0.25
#define HOLD_TEMP_H TEMP_FRAME_H * 0.30
#define HOLD_BTN_COLOR ILI9341_BLUE

// Arrow button dimensions
#define ARROW_BUTTON_W_H 40
// Main page up arrow
#define MAIN_UP_ARROW_X TEMP_FRAME_X + 125
#define MAIN_UP_ARROW_Y TEMP_FRAME_Y + 10
#define MAIN_UP_ARROW_W ARROW_BUTTON_W_H
#define MAIN_UP_ARROW_H ARROW_BUTTON_W_H
#define MAIN_UP_ARROW_COLOR ILI9341_BLUE

// Main page down arrow
#define MAIN_DOWN_ARROW_X MAIN_UP_ARROW_X
#define MAIN_DOWN_ARROW_Y TEMP_FRAME_Y + TEMP_FRAME_H - MAIN_UP_ARROW_H - 10
#define MAIN_DOWN_ARROW_W ARROW_BUTTON_W_H
#define MAIN_DOWN_ARROW_H ARROW_BUTTON_W_H

// Tempurature Adjustment components
#define SET_TEMP_AREA_X MAIN_UP_ARROW_X
#define SET_TEMP_AREA_Y MAIN_UP_ARROW_Y + MAIN_UP_ARROW_H + 10
#define SET_TEMP_AREA_W MAIN_UP_ARROW_W + 5
#define SET_TEMP_AREA_H 40
#define SET_TEMP_SIZE 2
// Text between up and down arrow
#define SET_TEMP_TEXT_X MAIN_UP_ARROW_X
#define SET_TEMP_TEXT_Y MAIN_UP_ARROW_Y + MAIN_UP_ARROW_H + 35

/************************* Date and Time form constants *************************/
#define DOWN_BTN_OFFSET ARROW_H + 50
#define ARROW_H 25
#define ARROW_W 65
#define ARROW_COLOR ILI9341_BLUE
#define HORIZONTAL_OFFSET 30

#define DATE_TIME_UP_ARROWS_Y 80
#define DATE_TIME_DOWN_ARROWS_Y DATE_TIME_UP_ARROWS_Y + DOWN_BTN_OFFSET

#define DATE_TIME_TXT_Y DATE_TIME_UP_ARROWS_Y + ARROW_H + 35

#define HOUR_DOW_ADJUSTMENT_X 35

#define MINUTE_MONTH_ADJUSTMENT_X HOUR_DOW_ADJUSTMENT_X + ARROW_W + HORIZONTAL_OFFSET

#define DAY_ADJUSTMENT_X MINUTE_MONTH_ADJUSTMENT_X + ARROW_W + HORIZONTAL_OFFSET

#define ENTER_DATE_X 45
#define ENTER_DATE_Y TOP_NAV_H + 30

#define BACK_BTN_X 20
#define BACK_BTN_Y 190
#define BACK_BTN_W 60
#define BACK_BTN_H 40
#define BACK_BTN_TXT_X BACK_BTN_X + 7
#define BACK_BTN_TXT_Y BACK_BTN_Y + 23

#define CONFIRM_BTN_X 110
#define CONFIRM_BTN_Y 190
#define CONFIRM_BTN_W 180
#define CONFIRM_BTN_H 40
#define CONFIRM_BTN_TXT_X CONFIRM_BTN_X + 10
#define CONFIRM_BTN_TXT_Y CONFIRM_BTN_Y + 28
#define CONFIRM_TXT_SIZE 2

/*********************** Set Points Page constants **********************/
#define SET_PT_ADJUSTMENT_AREA_X TEMP_FRAME_X
#define SET_PT_ADJUSTMENT_AREA_Y TEMP_FRAME_Y
#define SET_PT_ADJUSTMENT_AREA_W 250
#define SET_PT_ADJUSTMENT_AREA_H 140

#define ACTION_NAV_X SET_PT_ADJUSTMENT_AREA_W + COMPONENT_BORDER
#define ACTION_NAV_Y TOP_NAV_H + COMPONENT_BORDER
#define ACTION_NAV_W FULL_SCREEN_WIDTH - SET_PT_ADJUSTMENT_AREA_W + COMPONENT_BORDER
#define ACTION_NAV_H SET_PT_ADJUSTMENT_AREA_H

#define POINT_SELECTION_LABEL_X 0
#define POINT_SELECTION_LABEL_Y SET_PT_ADJUSTMENT_AREA_Y + SET_PT_ADJUSTMENT_AREA_H + COMPONENT_BORDER
#define POINT_SELECTION_LABEL_H 20
#define POINT_SELECTION_Y POINT_SELECTION_LABEL_Y + POINT_SELECTION_LABEL_H + COMPONENT_BORDER
#define POINT_SELECTION_H FULL_SCREEN_HEIGHT - POINT_SELECTION_LABEL_Y + POINT_SELECTION_LABEL_H

#define SAVE_Y ACTION_NAV_Y
#define REMOVE_Y SAVE_Y + ACTION_BTN_H + COMPONENT_BORDER
#define HOME_Y REMOVE_Y + ACTION_BTN_H + COMPONENT_BORDER
#define SAVE_H ACTION_NAV_Y/3
#define ACTION_TEXT_Y_OFFSET 28
#define ACTION_BTN_H (ACTION_NAV_H/3) - 1 

#define TEMP_ADJ_X SET_PT_ADJUSTMENT_AREA_X + 5
#define ARROWS_SM_W ARROW_W - 20

#define UP_ARROWS_Y SET_PT_ADJUSTMENT_AREA_Y + 30
#define DOWN_ARROWS_Y UP_ARROWS_Y + 60

#define H_OFFSET 20 // Offset between each set of up and down arrows

#define HOUR_X TEMP_ADJ_X + ARROWS_SM_W + H_OFFSET
#define MINUTE_X HOUR_X + ARROWS_SM_W + H_OFFSET
#define TIME_OF_DAY_X MINUTE_X + ARROWS_SM_W + H_OFFSET

#define SA_SUN_POINTS_X FULL_SCREEN_WIDTH/2 + COMPONENT_BORDER/2
#define SA_SUN_POINTS_W FULL_SCREEN_WIDTH/2 - COMPONENT_BORDER/2



#define SIZE_2_LETTER_H 30
#define TOP_MARGIN 5
#define DATE_TIME_RIGHT_BORDER 
#define COMPONENT_BORDER 2
#define RECTANGLE_RADIUS 5

#include <Fonts/FreeMonoBold9pt7b.h>
#define TEXT_FONT FreeMonoBold9pt7b

int temp = 100;
int setTemp = 72; // Default set tempurature
String currentFunction = "AC";
String currentFuncStatus = "Off";

int hour = 12;
int minute = 0;
String timeOfDay = "PM";

int dayOfWeek = 0;
int month = 0;
int day = 1;

String holdStatus = "Off";
boolean onMainPage = true;
boolean onSetDatePage = false;
boolean onSetTimePage = false;
boolean onSetPointsPage = false;

String months[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
String weekDays[] = { "Mon", "Tue", "Wed", "Th", "Fri", "Sat", "Sun" };

void setup(void)
{
  Serial.begin(9600);
  tft.begin();
  if (!ts.begin(40)) { 
    Serial.println("Unable to start touchscreen.");
  } 
  else { 
    Serial.println("Touchscreen started."); 
  }

  tft.fillScreen(ILI9341_BLACK);
  tft.setRotation(1); 
  tft.setFont(&TEXT_FONT); // Set text
  loadMainPage();
  //loadDatePage();
}

void loop(){
  
  // See if there's any  touch data for us
  if (ts.touched()) {   
    
    // Retrieve a point  
    TS_Point p = ts.getPoint(); 
    
    // rotate coordinate system
    // flip it around to match the screen.
    p.x = map(p.x, 0, 240, 240, 0);
    p.y = map(p.y, 0, 320, 320, 0);
    int y = tft.height() - p.x;
    int x = p.y;

    // Determine action and execute
    if(onMainPage) {
      mainPageAction(x, y);     
    } else if(onSetDatePage) {
      datePageAction(x, y);
    } else if(onSetTimePage) {
      timePageAction(x, y); 
    } else if(onSetPointsPage) {
      setPointPageAction(x, y);
    }
  }  
}

#define PTS_W SA_SUN_POINTS_W - 120
// TODO: Finish set points functionality
void setPointPageAction(int x, int y) {
  // Home btn clicked
  if(clickedComponent(x, y, ACTION_NAV_X, HOME_Y, ACTION_NAV_W, ACTION_BTN_H)) {
      onMainPage = true;
      onSetPointsPage = false;
      loadMainPage();
  } else if(clickedComponent(x, y, ACTION_NAV_X, SAVE_Y, ACTION_NAV_W, ACTION_BTN_H)) {
      Serial.println("Save btn clicked.");
  } else if(clickedComponent(x, y, ACTION_NAV_X, REMOVE_Y, ACTION_NAV_W, ACTION_BTN_H)) {
      Serial.println("Remove btn clicked.");
  } else if(clickedComponent(x, y, 0, POINT_SELECTION_Y, PTS_W, POINT_SELECTION_H)) {
      Serial.println(" Mon-Fri 1 btn clicked.");
  } else if(clickedComponent(x, y, PTS_W, POINT_SELECTION_Y, PTS_W, POINT_SELECTION_H)) {
      Serial.println(" Mon-Fri 2 btn clicked.");
  } else if(clickedComponent(x, y, PTS_W + PTS_W, POINT_SELECTION_Y, PTS_W, POINT_SELECTION_H)) {
      Serial.println(" Mon-Fri 3 btn clicked.");
  } else if(clickedComponent(x, y, PTS_W + PTS_W + PTS_W, POINT_SELECTION_Y, PTS_W, POINT_SELECTION_H)) {
      Serial.println(" Mon-Fri 4 btn clicked.");
  } else if(clickedComponent(x, y, SA_SUN_POINTS_X, POINT_SELECTION_Y, PTS_W, POINT_SELECTION_H)) {
      Serial.println(" Sa_Sun 1 btn clicked.");
  } else if(clickedComponent(x, y, SA_SUN_POINTS_X + PTS_W, POINT_SELECTION_Y, PTS_W, POINT_SELECTION_H)) {
      Serial.println(" Sa_Sun 2 btn clicked.");
  } else if(clickedComponent(x, y, SA_SUN_POINTS_X + PTS_W + PTS_W, POINT_SELECTION_Y, PTS_W, POINT_SELECTION_H)) {
      Serial.println(" Sa_Sun 3 btn clicked.");
  } else if(clickedComponent(x, y, SA_SUN_POINTS_X + PTS_W + PTS_W + PTS_W, POINT_SELECTION_Y, PTS_W, POINT_SELECTION_H)) {
      Serial.println(" Sa_Sun 4 btn clicked.");
  }
}

boolean clickedComponent(int px, int py, int x, int y, int w, int h) {
  if((px > x) && (px < (x + w))) {
    if ((py > y) && (py <= (y + h)))
      return true;
  } 
  return false; 
}

void mainPageAction(int x, int y) {
  // Up arrow is clicked
  if(clickedComponent(x, y, MAIN_UP_ARROW_X, MAIN_UP_ARROW_Y, MAIN_UP_ARROW_W, MAIN_UP_ARROW_H)) {
    incrementSetTemp(); 
    
  // Down arrow is clicked   
  } else if (clickedComponent(x, y, MAIN_DOWN_ARROW_X, MAIN_DOWN_ARROW_Y, MAIN_DOWN_ARROW_W, MAIN_DOWN_ARROW_H)) {
    decrementSetTemp();
      
  // Date is clicked  
  } else if (clickedComponent(x, y, DATE_X, DATE_Y, DATE_W, DATE_H)) {
    onMainPage = false;
    onSetDatePage = true;
    loadDatePage(); 
    
  // Time is clicked     
  } else if (clickedComponent(x, y, TIME_X, TIME_Y, TIME_W, TIME_H)) {
    onMainPage = false;
    onSetTimePage = true;
    loadTimePage();
       
  // Set Points is clicked   
  } else if (clickedComponent(x, y, SET_POINT_X, SET_POINT_Y, SET_POINT_W, SET_POINT_H)) {
    onMainPage = false;
    onSetPointsPage = true;
    loadSetPointPage(); 
      
  // Heat btn clicked   
  } else if (clickedComponent(x, y, HEAT_BTN_X, BOTTOM_NAV_Y, HEAT_BTN_W, BOTTOM_NAV_H)) {
    currentFunction = "HEAT";
    updateCurrentFunction(); 

  // AC btn clicked  
  } else if (clickedComponent(x, y, AC_BTN_X, BOTTOM_NAV_Y, AC_BTN_W, BOTTOM_NAV_H)) {
    currentFunction = "AC";
    updateCurrentFunction(); 

  // Auto btn clicked  
  } else if (clickedComponent(x, y, AUTO_BTN_X, BOTTOM_NAV_Y, AUTO_BTN_W, BOTTOM_NAV_H)) {
    currentFunction = "AUTO";
    updateCurrentFunction(); 

  // Off btn clicked  
  } else if (clickedComponent(x, y, OFF_BTN_X, BOTTOM_NAV_Y, OFF_BTN_W, BOTTOM_NAV_H)) {
    currentFunction = "OFF";
    updateCurrentFunction(); 

  // Hold btn clicked 
  } else if (clickedComponent(x, y, HOLD_TEMP_X, HOLD_TEMP_Y, HOLD_TEMP_W, HOLD_TEMP_H)) {
    toggleHold(); 
  } 
}

int setDayOfWeek;
int setMonth;
int setDay = 1;

#define FORM_TXT_SIZE 2
//// Should probably pass text size and text color  and cursor x/y as params
// Draws rectangle over text and replace with txt
// Used for updating text between up and down arrows in set date and set time form
void updateArea(int x, int y, int w, int h, String txt) {
  drawRectWithText(x, y, w, h, x, DATE_TIME_TXT_Y, txt, FORM_TXT_SIZE, ILI9341_WHITE);
  delay(20);  
}

void datePageAction(int x, int y) {
  // Day of week up arrow clicked
  if(clickedComponent(x, y, HOUR_DOW_ADJUSTMENT_X, DATE_TIME_UP_ARROWS_Y, ARROW_W, ARROW_H)) {
    setDayOfWeek = (setDayOfWeek + 1) % 7;  
    
  // Month up arrow clicked  
  } else if(clickedComponent(x, y, MINUTE_MONTH_ADJUSTMENT_X, DATE_TIME_UP_ARROWS_Y, ARROW_W, ARROW_H)) {
    setMonth = setMonth - 1;
    if(setMonth < 0)
      setMonth = 11;
     
  // Day up arrow clicked  
  } else if(clickedComponent(x, y, DAY_ADJUSTMENT_X, DATE_TIME_UP_ARROWS_Y, ARROW_W, ARROW_H)) {
    setDay = (setDay + 1) % 31; 

  // Day of week down arrow clicked   
  } else if(clickedComponent(x, y, HOUR_DOW_ADJUSTMENT_X, DATE_TIME_DOWN_ARROWS_Y, ARROW_W, ARROW_H)) {
    setDayOfWeek = setDayOfWeek - 1; 
    if(setDayOfWeek < 0) 
      setDayOfWeek = 6; 
    
  // Month down arrow clicked  
  } else if(clickedComponent(x, y, MINUTE_MONTH_ADJUSTMENT_X, DATE_TIME_DOWN_ARROWS_Y, ARROW_W, ARROW_H)) {
    setMonth = (setMonth + 1) % 12; 
     
  // Day down arrow clicked  
  } else if(clickedComponent(x, y, DAY_ADJUSTMENT_X, DATE_TIME_DOWN_ARROWS_Y, ARROW_W, ARROW_H)) {
    setDay = (setDay - 1);
    if(setDay < 1)
      setDay = 31; 
  }

  updateArea(HOUR_DOW_ADJUSTMENT_X, DATE_TIME_UP_ARROWS_Y + ARROW_H, ARROW_W, 45, weekDays[setDayOfWeek]);  
  updateArea(MINUTE_MONTH_ADJUSTMENT_X, DATE_TIME_UP_ARROWS_Y + ARROW_H, ARROW_W, 45, months[setMonth]); 
  updateArea(DAY_ADJUSTMENT_X, DATE_TIME_UP_ARROWS_Y + ARROW_H, ARROW_W, 40, formatNum(setDay));  

  // Back btn clicked
  if (clickedComponent(x, y, BACK_BTN_X, BACK_BTN_Y, BACK_BTN_W, BACK_BTN_H)) {
    onMainPage = true;
    onSetDatePage = false;
    loadMainPage();
  
  // Confirm btn clicked
  }else if (clickedComponent(x, y, CONFIRM_BTN_X, CONFIRM_BTN_Y, CONFIRM_BTN_W, CONFIRM_BTN_H)) {
    onMainPage = true;
    onSetDatePage = false;
    dayOfWeek = setDayOfWeek;
    month = setMonth;
    day = setDay;
    loadMainPage();
  }  
}

// Formats integer to two byte string
String formatNum(int num) {
  if(num < 10)
    return "0" + String(num);  
  else
    return String(num);  
}

int setHour = hour;
int setMinute = minute;
String setTimeOfDay = "PM";

void timePageAction(int x, int y) {
  // Hour up arrow clicked
  if(clickedComponent(x, y, HOUR_DOW_ADJUSTMENT_X, DATE_TIME_UP_ARROWS_Y, ARROW_W, ARROW_H)) {
    setHour = (setHour + 1) % 12;  
    
  // Minute up arrow clicked  
  } else if(clickedComponent(x, y, MINUTE_MONTH_ADJUSTMENT_X, DATE_TIME_UP_ARROWS_Y, ARROW_W, ARROW_H)) {
    setMinute = (setMinute + 1) % 59; 
     
  // Time of day up arrow clicked  
  } else if(clickedComponent(x, y, DAY_ADJUSTMENT_X, DATE_TIME_UP_ARROWS_Y, ARROW_W, ARROW_H)) {
    toggleTimeOfDay(); 

  // Hour down arrow clicked   
  } else if(clickedComponent(x, y, HOUR_DOW_ADJUSTMENT_X, DATE_TIME_DOWN_ARROWS_Y, ARROW_W, ARROW_H)) {
    setHour = (setHour - 1);
    if(setHour < 1)
      setHour = 12;
    
  // Minute down arrow clicked  
  } else if(clickedComponent(x, y, MINUTE_MONTH_ADJUSTMENT_X, DATE_TIME_DOWN_ARROWS_Y, ARROW_W, ARROW_H)) {
    setMinute = (setMinute - 1);
      if(setMinute < 1)
        setMinute = 59;
     
  // Time of day down arrow clicked  
  } else if(clickedComponent(x, y, DAY_ADJUSTMENT_X, DATE_TIME_DOWN_ARROWS_Y, ARROW_W, ARROW_H)) {
    toggleTimeOfDay(); 
  }

  updateArea(HOUR_DOW_ADJUSTMENT_X, DATE_TIME_UP_ARROWS_Y + ARROW_H, ARROW_W, 45, formatNum(setHour));  
  updateArea(MINUTE_MONTH_ADJUSTMENT_X, DATE_TIME_UP_ARROWS_Y + ARROW_H, ARROW_W, 45, formatNum(setMinute)); 
  updateArea(DAY_ADJUSTMENT_X, DATE_TIME_UP_ARROWS_Y + ARROW_H, ARROW_W, 40, setTimeOfDay); 

  // Back btn clicked
  if (clickedComponent(x, y, BACK_BTN_X, BACK_BTN_Y, BACK_BTN_W, BACK_BTN_H)) {
    onMainPage = true;
    onSetTimePage = false;
    loadMainPage();
    
  // Confirm btn clicked  
  }else if (clickedComponent(x, y, CONFIRM_BTN_X, CONFIRM_BTN_Y, CONFIRM_BTN_W, CONFIRM_BTN_H)) {
    onMainPage = true;
    onSetTimePage = false;
    hour = setHour;
    minute = setMinute;
    timeOfDay = setTimeOfDay;
    loadMainPage();
  }
}

void toggleTimeOfDay() {
  if(setTimeOfDay.equals("PM")) {
    setTimeOfDay = "AM";
  } else {
    setTimeOfDay = "PM";
  }
}

void loadSetPointPage() {
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_BLACK);
  drawTopNav();
  
  /**************** Adjustment area ***********************/
  // Tempurature buttons
  tft.fillRect(SET_PT_ADJUSTMENT_AREA_X, SET_PT_ADJUSTMENT_AREA_Y, SET_PT_ADJUSTMENT_AREA_W, SET_PT_ADJUSTMENT_AREA_H, ILI9341_WHITE);
  drawUpArrow(TEMP_ADJ_X, UP_ARROWS_Y, ARROWS_SM_W, ARROW_H);
  drawDownArrow(TEMP_ADJ_X, DOWN_ARROWS_Y, ARROWS_SM_W, ARROW_H); 
  // TODO: add text for temp
  
  // Hour buttons
  drawUpArrow(HOUR_X, UP_ARROWS_Y, ARROWS_SM_W, ARROW_H);
  drawDownArrow(HOUR_X, DOWN_ARROWS_Y, ARROWS_SM_W, ARROW_H);
  // TODO: add text for hours
  
  // Minute buttons
  drawUpArrow(MINUTE_X, UP_ARROWS_Y, ARROWS_SM_W, ARROW_H);
  drawDownArrow(MINUTE_X, DOWN_ARROWS_Y, ARROWS_SM_W, ARROW_H);
  // TODO: add text for minutes
  
  // Time of day buttons
  drawUpArrow(TIME_OF_DAY_X, UP_ARROWS_Y, ARROWS_SM_W, ARROW_H);
  drawDownArrow(TIME_OF_DAY_X, DOWN_ARROWS_Y, ARROWS_SM_W, ARROW_H);
  // TODO: add text for PM or AM

  
  /**************** Action nav *********************/
  tft.fillRect(ACTION_NAV_X, ACTION_NAV_Y, ACTION_NAV_W, ACTION_NAV_H, ILI9341_BLACK);
  // Draw save button
  drawRoundRectWithText(ACTION_NAV_X, SAVE_Y, ACTION_NAV_W, ACTION_BTN_H, RECTANGLE_RADIUS, ACTION_NAV_X, SAVE_Y + ACTION_TEXT_Y_OFFSET, "SAVE", DEFAULT_TXT_SIZE, ILI9341_WHITE);
  // Draw remove button
  drawRoundRectWithText(ACTION_NAV_X, REMOVE_Y, ACTION_NAV_W, ACTION_BTN_H, RECTANGLE_RADIUS, ACTION_NAV_X, REMOVE_Y + ACTION_TEXT_Y_OFFSET, "REMOVE", DEFAULT_TXT_SIZE, ILI9341_WHITE);
  // draw home button
  drawRoundRectWithText(ACTION_NAV_X, HOME_Y, ACTION_NAV_W, ACTION_BTN_H, RECTANGLE_RADIUS, ACTION_NAV_X, HOME_Y + ACTION_TEXT_Y_OFFSET, "HOME", DEFAULT_TXT_SIZE, ILI9341_WHITE);
  
  /******************* Point selection for Monday-Friday and Saturday - Sunday *************************/
  
  drawRectWithText(0, POINT_SELECTION_LABEL_Y, FULL_SCREEN_WIDTH, POINT_SELECTION_LABEL_H, 50, POINT_SELECTION_LABEL_Y + 14, " M-F            Sa-Sun", DEFAULT_TXT_SIZE, ILI9341_PINK);

  // Monday - Friday points
  drawRectWithText(0, POINT_SELECTION_Y, SA_SUN_POINTS_W, POINT_SELECTION_H, 3, POINT_SELECTION_Y + SIZE_2_LETTER_H, "1 2 3 4", 2, ILI9341_RED);

  // Saturday - Sunday points
  drawRectWithText(SA_SUN_POINTS_X, POINT_SELECTION_Y, SA_SUN_POINTS_W, POINT_SELECTION_H, SA_SUN_POINTS_X + 3, POINT_SELECTION_Y + SIZE_2_LETTER_H, "1 2 3 4", 2, ILI9341_BLUE);
}

void loadMainPage() {
  tft.fillScreen(ILI9341_BLACK);
  drawTopNav();
  drawTempFrame();
  
  // Draw set point btn
  drawRoundRectWithText(SET_POINT_X, SET_POINT_Y, SET_POINT_W, SET_POINT_H, RECTANGLE_RADIUS, SET_POINT_TEXT_X, SET_POINT_TEXT_Y, "Set", DEFAULT_TXT_SIZE, ILI9341_WHITE);
  tft.setCursor(SET_POINT_TEXT_X , SET_POINT_TEXT_Y + VERTICAL_TEXT_OFFSET);
  tft.println("Point"); 
  
  drawBottomNav();   
}

void loadDatePage() {
  tft.fillScreen(ILI9341_BLACK);
  drawDateTimeForm();

  tft.setCursor(ENTER_DATE_X, ENTER_DATE_Y);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(2);
  tft.println("ENTER DATE"); 
}

void loadTimePage() {
  tft.fillScreen(ILI9341_BLACK);
  drawDateTimeForm();
  tft.setCursor(ENTER_DATE_X, ENTER_DATE_Y);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(2);
  tft.println("ENTER TIME");   
}

void drawDateTimeForm() {
  tft.fillRect(0, TOP_NAV_H + COMPONENT_BORDER, FULL_SCREEN_WIDTH, 240 - TOP_NAV_H, ILI9341_WHITE);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(DEFAULT_TXT_SIZE+1);
  drawTopNav();

  // Draw back button
  drawRoundRectWithText(BACK_BTN_X, BACK_BTN_Y, BACK_BTN_W, BACK_BTN_H, RECTANGLE_RADIUS, BACK_BTN_TXT_X, BACK_BTN_TXT_Y, "Back", DEFAULT_TXT_SIZE, ILI9341_RED);
  // Draw confirm button
  drawRoundRectWithText(CONFIRM_BTN_X, CONFIRM_BTN_Y, CONFIRM_BTN_W, CONFIRM_BTN_H, RECTANGLE_RADIUS, CONFIRM_BTN_TXT_X, CONFIRM_BTN_TXT_Y, "Confirm", CONFIRM_TXT_SIZE, ILI9341_GREEN);
  
  // Hour or day of week adjustment
  drawUpArrow(HOUR_DOW_ADJUSTMENT_X, DATE_TIME_UP_ARROWS_Y, ARROW_W, ARROW_H);
  drawDownArrow(HOUR_DOW_ADJUSTMENT_X, DATE_TIME_DOWN_ARROWS_Y, ARROW_W, ARROW_H);  

  // Text between arrows
  if(onSetDatePage) {
    tft.setCursor(HOUR_DOW_ADJUSTMENT_X, DATE_TIME_TXT_Y);  
    tft.println(weekDays[dayOfWeek]);
  } else {
    tft.setCursor(HOUR_DOW_ADJUSTMENT_X + 10, DATE_TIME_TXT_Y); 
    tft.println(formatNum(hour));  
  }

  // Minute or month adjustment arrows
  drawUpArrow(MINUTE_MONTH_ADJUSTMENT_X, DATE_TIME_UP_ARROWS_Y, ARROW_W, ARROW_H);
  drawDownArrow(MINUTE_MONTH_ADJUSTMENT_X, DATE_TIME_DOWN_ARROWS_Y, ARROW_W, ARROW_H);

  if(onSetDatePage) {
    tft.setCursor(MINUTE_MONTH_ADJUSTMENT_X, DATE_TIME_TXT_Y); 
    tft.println(months[month]);
  } else {  
    tft.setCursor(MINUTE_MONTH_ADJUSTMENT_X + 10, DATE_TIME_TXT_Y); 
    tft.println(formatNum(minute));  
  }

  // Day of week or day adjustment arrows
  drawUpArrow(DAY_ADJUSTMENT_X, DATE_TIME_UP_ARROWS_Y, ARROW_W, ARROW_H);
  drawDownArrow(DAY_ADJUSTMENT_X, DATE_TIME_DOWN_ARROWS_Y, ARROW_W, ARROW_H);  

  if(onSetDatePage) {
    tft.setCursor(DAY_ADJUSTMENT_X + 10, DATE_TIME_TXT_Y); 
    tft.println(formatNum(day));
  } else {
    tft.setCursor(DAY_ADJUSTMENT_X + 10, DATE_TIME_TXT_Y);  
    tft.println(timeOfDay);  
  } 
}

void drawTempFrame() {
  // Draw temp area
  drawRectWithText(TEMP_FRAME_X, TEMP_FRAME_Y, TEMP_FRAME_W, TEMP_FRAME_H, TEMP_TEXT_X, TEMP_TEXT_Y, String(temp), 3, ILI9341_WHITE);

  // Draw hold btn
  drawRoundRectWithText(HOLD_TEMP_X, HOLD_TEMP_Y, HOLD_TEMP_W, HOLD_TEMP_H, RECTANGLE_RADIUS, HOLD_TEMP_X + 12, HOLD_TEMP_Y + 18, "Hold", DEFAULT_TXT_SIZE, HOLD_BTN_COLOR);
  tft.setCursor(HOLD_TEMP_X + 12 , HOLD_TEMP_Y + 18*2);
  tft.println(holdStatus); 
  
  // Temp adjustment area
  drawUpArrow(MAIN_UP_ARROW_X, MAIN_UP_ARROW_Y, MAIN_UP_ARROW_W, MAIN_UP_ARROW_H);
  drawDownArrow(MAIN_DOWN_ARROW_X, MAIN_DOWN_ARROW_Y, MAIN_DOWN_ARROW_W, MAIN_DOWN_ARROW_H);
  updateSetTemp();  
}

void drawBottomNav() {
  // Heat button 
  drawRoundRectWithText(BOTTOM_NAV_X, BOTTOM_NAV_Y, HEAT_BTN_W, BOTTOM_NAV_H, RECTANGLE_RADIUS, HEAT_TXT_X, BOTTOM_NAV_TXT_Y, "HEAT", DEFAULT_TXT_SIZE, ILI9341_WHITE);
  // AC button
  drawRoundRectWithText(AC_BTN_X, BOTTOM_NAV_Y, AC_BTN_W, BOTTOM_NAV_H, RECTANGLE_RADIUS, AC_TXT_X, BOTTOM_NAV_TXT_Y, "AC", DEFAULT_TXT_SIZE, ILI9341_WHITE);
  // Auto button
  drawRoundRectWithText(AUTO_BTN_X, BOTTOM_NAV_Y, AUTO_BTN_W, BOTTOM_NAV_H, RECTANGLE_RADIUS, AUTO_TXT_X, BOTTOM_NAV_TXT_Y, "AUTO", DEFAULT_TXT_SIZE, ILI9341_WHITE);
  // Off button -- Note width is hardcoded with -5 to align with the frame displaying the temp... should not hardcode
  drawRoundRectWithText(OFF_BTN_X, BOTTOM_NAV_Y, AUTO_BTN_W-5, BOTTOM_NAV_H, RECTANGLE_RADIUS, OFF_TXT_X, BOTTOM_NAV_TXT_Y, "OFF", DEFAULT_TXT_SIZE, ILI9341_WHITE);
}

// purdy useful for drawing round buttons with text
void drawRoundRectWithText(int x, int y, int w, int h, int r, int cursor_x, int cursor_y, String txt, int txt_size, uint16_t color) {
  tft.fillRoundRect(x, y, w, h, r, color);
  tft.setCursor(cursor_x, cursor_y);
  tft.setTextSize(txt_size);
  tft.println(txt);  
}

// purdy useful for drawing buttons with text
void drawRectWithText(int x, int y, int w, int h, int cursor_x, int cursor_y, String txt, int txt_size, uint16_t color) {
  tft.fillRect(x, y, w, h, color);
  tft.setCursor(cursor_x, cursor_y);
  tft.setTextSize(txt_size);
  tft.println(txt);  
}

void updateCurrentFunction() {
  tft.fillRoundRect(CURRENT_FUNCTION_X, CURRENT_FUNCTION_Y, CURRENT_FUNCTION_W, CURRENT_FUNCTION_H, RECTANGLE_RADIUS, ILI9341_WHITE);

  // Function status probs not necessar...
  if(currentFunction.equals("AC")) {
    tft.setCursor(CURRENT_FUNC_TEXT_X , CURRENT_FUNC_TEXT_Y);    
  } else if (currentFunction.equals("HEAT") || currentFunction.equals("AUTO") ) {
    tft.setCursor(CURRENT_FUNC_TEXT_X - 10 , CURRENT_FUNC_TEXT_Y);   
  } else if(currentFunction.equals("OFF")) {
    tft.setCursor(CURRENT_FUNC_TEXT_X + 15 , CURRENT_FUNC_TEXT_Y);
  }
  String currStat = currentFuncStatus;
  if(currentFunction.equals("OFF")) {
    currStat = "";
  }
  
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(FUNC_DATE_TIME_SIZE);
  tft.println(String(currentFunction + " " + currStat));
}

// This nav is at the top of all pages
void drawTopNav() {
  updateCurrentFunction(); // Draw current function box & text
  // Draw date area
  String date = weekDays[dayOfWeek] + " " + months[month] + " " + String(day);
  drawRoundRectWithText(DATE_X, DATE_Y, DATE_W, DATE_H, RECTANGLE_RADIUS, DATE_TEXT_X, DATE_TEXT_Y, date, DEFAULT_TXT_SIZE, ILI9341_WHITE);
  // Draw time area 
  drawRoundRectWithText(TIME_X, TIME_Y, TIME_W, TIME_H, RECTANGLE_RADIUS, TIME_TEXT_X, TIME_TEXT_Y, formatTime(), DEFAULT_TXT_SIZE, ILI9341_WHITE); 
}

String formatTime() {
  String m = String(minute);
  if(minute < 10)
    m = "0" + m;
  return String(hour) + ":" + m + " " + timeOfDay;
}

void toggleHold() {
  if(holdStatus.equals("Off")) {
    holdStatus = "On";
  } else {
    holdStatus = "Off";
  }
  // Clear current text and update 
  drawRectWithText(HOLD_STATUS_X, HOLD_STATUS_Y, HOLD_STATUS_W, HOLD_STATUS_H, HOLD_STATUS_X, HOLD_STATUS_Y + 18, holdStatus, DEFAULT_TXT_SIZE, HOLD_BTN_COLOR);
  delay(100);
}

void drawSetTemp() {
  tft.setCursor(MAIN_UP_ARROW_X, MAIN_UP_ARROW_Y + MAIN_UP_ARROW_H + 12);
  tft.setTextSize(4);
  tft.println(setTemp); 
}

// should be using update area instead...
void updateSetTemp() {
  drawRectWithText(SET_TEMP_AREA_X, SET_TEMP_AREA_Y, SET_TEMP_AREA_W, SET_TEMP_AREA_H, SET_TEMP_TEXT_X, SET_TEMP_TEXT_Y, String(setTemp), DEFAULT_TXT_SIZE  + 1, ILI9341_WHITE);
  delay(100);  
}

void incrementSetTemp() {
  if(setTemp < 90) {
    setTemp++;
    updateSetTemp();
  }
}

void decrementSetTemp() {
   if(setTemp > 60) {
    setTemp--;
    updateSetTemp(); 
  }
}

void drawUpArrow(int x, int y, int w, int h) {
  tft.fillRoundRect(x, y, w, h, RECTANGLE_RADIUS, MAIN_UP_ARROW_COLOR);
  tft.fillTriangle(x + 0.2*w , y + 0.8*h , x + .5*w , y + 0.2*h ,x + 0.8*w , y + .8*h , ILI9341_WHITE);
}

void drawDownArrow(int x, int y, int w, int h) {
  tft.fillRoundRect(x, y, w, h,RECTANGLE_RADIUS, MAIN_UP_ARROW_COLOR);
  tft.fillTriangle(x + 0.2*w , y + 0.2*h , x + .5*w , y + 0.8*h, x + 0.8*w , y + .2*h , ILI9341_WHITE);
}
