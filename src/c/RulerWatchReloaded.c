#include <pebble.h>

#if defined(PBL_ROUND)
#define IS_ROUND true
#define RULER_XOFFSET 50
#define TEXT_HOUR_OFFSET 83
#define WIDTH 180
#define HEIGHT 180
#else
#define IS_ROUND false
#define RULER_XOFFSET 34
#define TEXT_HOUR_OFFSET 56
#define WIDTH 144
#define HEIGHT 168
#endif

#define RULER_SIZE -2
#define MAXRAIN 40;

#define LINE_THICK 3  

// For the gradiant effect, 1/2 pixels, 1/3 and 1/4
#define GRADIANT 4
#define GRADIANT_X_OFFSET -1
#define GRADIANT_Y_OFFSET -10

#ifdef PBL_COLOR 

#define BLUE_LINE GColorElectricBlue
#define RED_LINE GColorRed 
#define RAIN_COLOR GColorCobaltBlue
#define IS_COLOR true

#else

#define BLUE_LINE GColorWhite  
#define RAIN_COLOR GColorWhite
#define RED_LINE GColorWhite 
#define IS_COLOR false


#endif


#define STATUS_FONT FONT_KEY_GOTHIC_14


#define KEY_TEMPERATURE 0
#define KEY_CONDITIONS 1
#define KEY_DESCRIPTION 2
#define KEY_WIND_SPEED 3 
#define KEY_CLOUDS 4
#define KEY_HUMIDITY 5
#define KEY_SUNRISE 6
#define KEY_SUNSET 7  
#define KEY_TMIN 8 
#define KEY_TMAX 9  
#define KEY_ICON 10

#define KEY_FORECAST_TEMP1 11 
#define KEY_FORECAST_TEMP2 12
#define KEY_FORECAST_TEMP3 13
#define KEY_FORECAST_TEMP4 14
#define KEY_FORECAST_TEMP5 15
#define KEY_FORECAST_H1 16
#define KEY_FORECAST_H2 17
#define KEY_FORECAST_H3 18
#define KEY_FORECAST_RAIN1 21
#define KEY_FORECAST_RAIN2 22
#define KEY_FORECAST_RAIN3 23
#define KEY_FORECAST_RAIN4 24
#define KEY_FORECAST_RAIN5 25
#define KEY_FORECAST_ICON1 26
#define KEY_FORECAST_ICON2 27
#define KEY_FORECAST_ICON3 28
#define KEY_FORECAST_WIND1 29
#define KEY_FORECAST_WIND2 30
#define KEY_FORECAST_WIND3 31
#define KEY_LOCATION 32

#define KEY_GPS 33
#define KEY_INPUT_CITY 34
#define KEY_SELECT_UTC 35
#define KEY_RADIO_UNITS 36
#define KEY_RADIO_REFRESH 54
#define KEY_TOGGLE_VIBRATION 37
#define KEY_TOGGLE_BW_ICONS 38
#define KEY_COLOR_RIGHT_R 39
#define KEY_COLOR_RIGHT_G 40
#define KEY_COLOR_RIGHT_B 41
#define KEY_COLOR_LEFT_R 42
#define KEY_COLOR_LEFT_G 43
#define KEY_COLOR_LEFT_B 44
#define KEY_COLOR_HOURS_R 45
#define KEY_COLOR_HOURS_G 46
#define KEY_COLOR_HOURS_B 47

#define KEY_COLOR_RULER_R 48
#define KEY_COLOR_RULER_G 49
#define KEY_COLOR_RULER_B 50
#define KEY_COLOR_TEMPERATURES_R 51
#define KEY_COLOR_TEMPERATURES_G 52
#define KEY_COLOR_TEMPERATURES_B 53
#define KEY_RADIO_REFRESH 54
#define KEY_LAST_REFRESH 55

#define XOFFSET 18
#define YOFFSET 6

#if defined(PBL_ROUND)
#define TEXT_DAYW_STATUS_OFFSET_X 8 
#define TEXT_DAYW_STATUS_OFFSET_Y 34 
#define TEXT_DAY_STATUS_OFFSET_X 8 
#define TEXT_DAY_STATUS_OFFSET_Y 40 
#define TEXT_TEMP_OFFSET_X -6
#define TEXT_TEMP_OFFSET_Y 103 
#define TEXT_TMIN_OFFSET_X -3
#define TEXT_TMIN_OFFSET_Y 70 
#define TEXT_TMAX_OFFSET_X -3
#define TEXT_TMAX_OFFSET_Y 92 
#define ICON_X 15
#define ICON_Y 73
#define TEXT_MONTH_STATUS_OFFSET_X 6
#define TEXT_MONTH_STATUS_OFFSET_Y 129

#define BAT_STATUS_OFFSET_X 46
#define BAT_STATUS_OFFSET_Y 80

// For bluetooth lost notification
#define BT_STATUS_OFFSET_Y 7

#define WEATHER_OFFSET_X 0
#define WEATHER_OFFSET_Y 10

#else

#define TEXT_DAYW_STATUS_OFFSET_X 0 
#define TEXT_DAYW_STATUS_OFFSET_Y 1 
#define TEXT_DAY_STATUS_OFFSET_X 0
#define TEXT_DAY_STATUS_OFFSET_Y 7 
#define TEXT_TEMP_OFFSET_X 1
#define TEXT_TEMP_OFFSET_Y 123 
#define TEXT_TMIN_OFFSET_X 7
#define TEXT_TMIN_OFFSET_Y 58 
#define TEXT_TMAX_OFFSET_X 7
#define TEXT_TMAX_OFFSET_Y 100 
#define ICON_X -1
#define ICON_Y 70 
// For bluetooth lost notification
#define BT_STATUS_OFFSET_Y -60
#define TEXT_MONTH_STATUS_OFFSET_X -14
#define TEXT_MONTH_STATUS_OFFSET_Y 5

#define BAT_STATUS_OFFSET_X 27
#define BAT_STATUS_OFFSET_Y 90

#define WEATHER_OFFSET_X -14
#define WEATHER_OFFSET_Y 5
#endif 

#define ANIM_DELAY 1000     
#define ANIM_DURATION 2000
#define LINE_INTERVAL 5
#define MARK_0  42
#define MARK_5  12
#define MARK_15 22 
#define MARK_30 32


#define QUIET_TIME_START 22
#define QUIET_TIME_END 10



#define TAP_DURATION 2000

static bool is_hour_fictive =false; 
static bool is_vibration =false;

static Window *window;
static Layer *rootLayer;
static Layer *layer;

static int hour_size = 12 * LINE_INTERVAL; // 12 marks, one every 5 minutes
static int hour_part_size=0;
static GRect rect_text = { { RULER_XOFFSET + XOFFSET, 0 }, { 100, 100 } };

// WEATHER  

static char weather_temp[10]=" ";
static char conditions[100]=" ";
static char icon[20]=" ";
static char icon1[20]=" ";
static char icon2[20]=" ";
static char icon3[20]=" ";
static char h1[20]=" ";
static char h2[20]=" ";
static char h3[20]=" ";
static char location[100]=" ";  
static int tmin_val=0;
static int tmax_val=0;
static int wind_speed_val=0;
static int wind1_val=0;
static int wind2_val=0;
static int wind3_val=0;
static int temp1_val=0;
static int temp2_val=0;
static int temp3_val=0;
static int temp4_val=0;
static int temp5_val=0;
static int rain1_val=0;
static int rain2_val=0;
static int rain3_val=0;
static int rain4_val=0;
time_t last_refresh=0;
int duration=3600;
static char wind1[10]=" ";
static char wind2[10]=" ";
static char wind3[10]=" ";
static char temp1[10]=" ";
static char temp2[10]=" ";
static char temp3[10]=" ";
static char temp4[10]=" ";
static char temp5[10]=" ";
static char rain1[10]=" ";
static char rain2[10]=" ";
static char rain3[10]=" ";
static char rain4[10]=" ";
static char heure[8]=" ";

// Config data
static bool is_gps;
static char city[50]=" ";
static int utc=1;
static bool is_metric=1;
static bool is_30mn=1;

static bool is_bw_icon=0;
static GColor color_right;
static GColor color_left;
static GColor color_hours;
static GColor color_ruler;
static GColor color_temp;


static GPoint line1_p1 = { 0, 84 };
static GPoint line1_p2 = { 143, 84 };

static GPoint line2_p1 = { 0, 0 };
static GPoint line2_p2 = { 0, 0 };
static int hour_line_ypos = 84+YOFFSET;
static char pebble_Lang[20]=" ";


bool is_charging=false;
bool is_tapped=false;
bool is_connected=true;;
static GFont statusfontsmall;
static GFont statusfontsmallbold;
static GFont statusfontdate;

static GFont hours60;


static int markWidth[12] = { MARK_0, MARK_5, MARK_5, MARK_15, MARK_5, MARK_5, MARK_30, MARK_5, MARK_5, MARK_15, MARK_5, MARK_5 };
static int labels_12h[28] = { 10, 11, 12, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 , 1};
static int labels[28] = { 22, 23, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 0, 1};
static uint8_t battery_level=0;

static char text[10] = "  ";

static char *weekdayLangFr[7]={"Dim","Lun","Mar","Mer","Jeu","Ven","Sam"};
static char *weekdayLangEn[7]={"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
static char *weekdayLangGe[7]={"Son","Mon","Die","Mit","Don","Fre","Sam"};
static char *weekdayLangSp[7]={"Dom","Lun","Mar","Mie","Jue","Vie","Sab"};



static int build_icon (char *text_icon){
  if (strcmp (text_icon,"01d")==0){
    if((is_bw_icon)||(!IS_COLOR))
      return RESOURCE_ID_ENSOLEILLE_W;
    else    
      return RESOURCE_ID_ENSOLEILLE;

  }  
  if (strcmp (text_icon,"01n")==0){

    if((is_bw_icon)||(!IS_COLOR))
      return RESOURCE_ID_NUIT_CLAIRE_W;
    else   
      return RESOURCE_ID_NUIT_CLAIRE;

  }    
  if (strcmp (text_icon,"02d")==0){
    if((is_bw_icon)||(!IS_COLOR))
      return RESOURCE_ID_FAIBLES_PASSAGES_NUAGEUX_W;
    else  
      return RESOURCE_ID_FAIBLES_PASSAGES_NUAGEUX;
  }    
  if (strcmp (text_icon,"02n")==0){
    if((is_bw_icon)||(!IS_COLOR))
      return RESOURCE_ID_NUIT_BIEN_DEGAGEE_W;
    else  
      return RESOURCE_ID_NUIT_BIEN_DEGAGEE;
  }  
  if (strcmp (text_icon,"03d")==0){
    if((is_bw_icon)||(!IS_COLOR))
      return RESOURCE_ID_DEVELOPPEMENT_NUAGEUX_W;
    else  
      return RESOURCE_ID_DEVELOPPEMENT_NUAGEUX;
  }   
  if (strcmp (text_icon,"03n")==0){
    if((is_bw_icon)||(!IS_COLOR))
      return RESOURCE_ID_NUIT_AVEC_DEVELOPPEMENT_NUAGEUX_W;
    else  
      return RESOURCE_ID_NUIT_AVEC_DEVELOPPEMENT_NUAGEUX;
  }    
  if (strcmp (text_icon,"04d")==0){
    if((is_bw_icon)||(!IS_COLOR))
      return RESOURCE_ID_FORTEMENT_NUAGEUX_W;
    else 
      return RESOURCE_ID_FORTEMENT_NUAGEUX;
  }    
  if (strcmp (text_icon,"04n")==0){
    if((is_bw_icon)||(!IS_COLOR))
      return RESOURCE_ID_NUIT_NUAGEUSE_W;
    else  
      return RESOURCE_ID_NUIT_NUAGEUSE;
  } 
  if (strcmp (text_icon,"09d")==0||strcmp (text_icon,"09n")==0){
    if((is_bw_icon)||(!IS_COLOR))
      return RESOURCE_ID_COUVERT_AVEC_AVERSES_W;
    else  
      return RESOURCE_ID_COUVERT_AVEC_AVERSES;
  }  

  if (strcmp (text_icon,"10d")==0){
    if((is_bw_icon)||(!IS_COLOR))
      return RESOURCE_ID_AVERSES_DE_PLUIE_FORTE_W;
    else  
      return RESOURCE_ID_AVERSES_DE_PLUIE_FORTE;
  }   
  if (strcmp (text_icon,"10n")==0){
    if((is_bw_icon)||(!IS_COLOR))
      return RESOURCE_ID_NUIT_AVEC_AVERSES_W;
    else  
      return RESOURCE_ID_NUIT_AVEC_AVERSES;
  }    

  if (strcmp (text_icon,"11d")==0||strcmp (text_icon,"11n")==0){
    if((is_bw_icon)||(!IS_COLOR))
      return RESOURCE_ID_FORTEMENT_ORAGEUX_W;
    else  
      return RESOURCE_ID_FORTEMENT_ORAGEUX;
  }    

  if (strcmp (text_icon,"13d")==0||strcmp (text_icon,"13n")==0){
    if((is_bw_icon)||(!IS_COLOR))
      return RESOURCE_ID_NEIGE_FORTE_W;
    else  
      return RESOURCE_ID_NEIGE_FORTE;
  }     

  if (strcmp (text_icon,"50d")==0||strcmp (text_icon,"50n")==0){
    if((is_bw_icon)||(!IS_COLOR))
      return RESOURCE_ID_BROUILLARD_W;
    else  
      return RESOURCE_ID_BROUILLARD;
  }   

  return RESOURCE_ID_BT;

}     


int abs(int x){
  if (x>=0)
    return x;
  else 
    return-x;
}

static void layer_update(Layer *me, GContext* ctx) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "is tapped ? %d", is_tapped);

  GBitmap *s_icon;
  if(is_tapped){
    // background
    graphics_context_set_fill_color(ctx, color_left);
    graphics_fill_rect(ctx, GRect(0,0, 180, 180), 0, GCornerNone);

    GRect rect_date = { { 0, 25 }, {WIDTH, 50} };


    char status_text[100];
    time_t t = time(NULL);
    struct tm now = *(localtime(&t)); 

    graphics_context_set_text_color(ctx, color_temp);
    snprintf(status_text, sizeof(status_text), "%s %i", weekdayLangEn[now.tm_wday], now.tm_mday);
    if (strcmp(pebble_Lang, "fr_FR") == 0)
      snprintf(status_text, sizeof(status_text), "%s %i", weekdayLangFr[now.tm_wday], now.tm_mday);

    if (strcmp(pebble_Lang, "de_DE") == 0)
      snprintf(status_text, sizeof(status_text), "%s %i", weekdayLangGe[now.tm_wday], now.tm_mday);

    if (strcmp(pebble_Lang, "es_ES") == 0)
      snprintf(status_text, sizeof(status_text), "%s %i", weekdayLangSp[now.tm_wday], now.tm_mday);


    graphics_draw_text(ctx, status_text, fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK), rect_date, GTextOverflowModeWordWrap,
                       GTextAlignmentCenter, NULL);


    // Batterie
    graphics_context_set_fill_color(ctx, color_temp);
    graphics_fill_rect(ctx, GRect(BAT_STATUS_OFFSET_X, BAT_STATUS_OFFSET_Y, 88, 30), 0, GCornerNone);

    graphics_fill_rect(ctx, GRect(BAT_STATUS_OFFSET_X+88, BAT_STATUS_OFFSET_Y+5, 7, 20), 0, GCornerNone);

    graphics_context_set_fill_color(ctx, color_left);


    int bat = battery_level*8/10;
    int invbat = 80-bat;
    if(!is_charging){
      graphics_fill_rect(ctx, GRect(BAT_STATUS_OFFSET_X+4+bat, BAT_STATUS_OFFSET_Y+4, invbat, 22), 0, GCornerNone);
    }
    graphics_context_set_fill_color(ctx, color_temp);



  }

  else{

    GRect rect_screen = { { 0+WEATHER_OFFSET_X, 0+WEATHER_OFFSET_Y }, {180 , 180 } };

    GRect rect_h1 = { { 37+WEATHER_OFFSET_X,118+WEATHER_OFFSET_Y }, {60, 20} };
    GRect rect_h2 = { { 67+WEATHER_OFFSET_X, 118+WEATHER_OFFSET_Y }, {60 , 20 } };
    GRect rect_h3 = { { 97+WEATHER_OFFSET_X, 118+WEATHER_OFFSET_Y }, {60 , 20 } };
    GRect rect_wind1 = { { 38+WEATHER_OFFSET_X, 145+WEATHER_OFFSET_Y }, {60 , 20 } };
    GRect rect_wind2 = { { 66+WEATHER_OFFSET_X, 145+WEATHER_OFFSET_Y}, {60 , 20 } };  
    GRect rect_wind3 = { { 97+WEATHER_OFFSET_X, 145+WEATHER_OFFSET_Y }, {60 , 20 } };


    #if defined(PBL_ROUND)
    GRect rect_time = { { 0, 15}, {180 , 180 } };
    GRect rect_t1 = { { -28+WEATHER_OFFSET_X, 57+WEATHER_OFFSET_Y},{60 , 20 } };
    GRect rect_t2= { { -28+WEATHER_OFFSET_X, 86+WEATHER_OFFSET_Y}, {60 , 20 } };
    #else
    GRect rect_time = { { 0, 0}, {144 , 180 } };
    GRect rect_t1 = { { -24+WEATHER_OFFSET_X, 57+WEATHER_OFFSET_Y},{60 , 20 } };
    GRect rect_t2= { { -24+WEATHER_OFFSET_X, 86+WEATHER_OFFSET_Y}, {60 , 20 } };
    #endif



    char h1_buffer[20]=" ";
    char h2_buffer[20]=" ";
    char h3_buffer[20]=" ";

    int hour_style;

    int i_h1 = atoi(h1);
    int i_h2 = atoi(h2);
    int i_h3 = atoi(h3);

    // Bluetooth



    // background
    graphics_context_set_fill_color(ctx, color_left);
    graphics_fill_rect(ctx, GRect(0,0, 180, 180), 0, GCornerNone);


    if(!is_connected){
      graphics_context_set_text_color(ctx, color_temp);
      if(IS_ROUND){
        graphics_draw_text(ctx, "X", statusfontdate, GRect(0,-2,WIDTH,30), GTextOverflowModeWordWrap,
                           GTextAlignmentCenter, NULL); 
      }
      else{
        graphics_draw_text(ctx, "X", statusfontdate, GRect(1,123,30,30), GTextOverflowModeWordWrap,
                           GTextAlignmentCenter, NULL); 

      }


    }



    snprintf(wind1, sizeof(wind1), "%i", wind1_val);
    snprintf(wind2, sizeof(wind2), "%i", wind2_val);
    snprintf(wind3, sizeof(wind3), "%i", wind3_val);

    snprintf(temp1, sizeof(temp1), "%i", temp1_val);
    snprintf(temp2, sizeof(temp2), "%i", temp2_val);
    snprintf(temp3, sizeof(temp3), "%i", temp3_val);
    snprintf(temp4, sizeof(temp4), "%i", temp4_val);
    snprintf(temp5, sizeof(temp5), "%i", temp5_val);

    snprintf(rain1, sizeof(rain1), "%i", rain1_val); 
    snprintf(rain2, sizeof(rain2), "%i", rain2_val); 
    snprintf(rain3, sizeof(rain3), "%i", rain3_val); 
    snprintf(rain4, sizeof(rain4), "%i", rain4_val); 


    // openweather diplay in 24 hours mode
    if(clock_is_24h_style())
      hour_style=24;
    else
      hour_style=12;

    i_h1=i_h1%hour_style;
    i_h2=i_h2%hour_style;
    i_h3=i_h3%hour_style;



    snprintf(h1_buffer, sizeof(h1_buffer), "%i", i_h1); 
    snprintf(h2_buffer, sizeof(h2_buffer), "%i", i_h2); 
    snprintf(h3_buffer, sizeof(h3_buffer), "%i", i_h3);   


    graphics_context_set_text_color(ctx, color_temp);

    graphics_draw_text(ctx, h1_buffer, statusfontdate, rect_h1, GTextOverflowModeWordWrap,
                       GTextAlignmentCenter, NULL); 
    graphics_draw_text(ctx, h2_buffer, statusfontdate, rect_h2, GTextOverflowModeWordWrap,
                       GTextAlignmentCenter, NULL); 
    graphics_draw_text(ctx, h3_buffer, statusfontdate, rect_h3, GTextOverflowModeWordWrap,
                       GTextAlignmentCenter, NULL); 
    graphics_draw_text(ctx, wind1, statusfontsmallbold, rect_wind1, GTextOverflowModeWordWrap,
                       GTextAlignmentCenter, NULL); 
    graphics_draw_text(ctx, wind2, statusfontsmallbold, rect_wind2, GTextOverflowModeWordWrap,
                       GTextAlignmentCenter, NULL); 
    graphics_draw_text(ctx, wind3, statusfontsmallbold, rect_wind3, GTextOverflowModeWordWrap,
                       GTextAlignmentCenter, NULL); 




    // recherche de tmin tmax sur l'échantillon

    int temps[5]={atoi(temp1),atoi(temp2),atoi(temp3),atoi(temp4),atoi(temp5)};


    // pluie
    int max_rain = MAXRAIN; 
    int rain_pixel=  45*rain1_val/max_rain;

    graphics_context_set_fill_color(ctx, RAIN_COLOR);

    if (rain_pixel > 45)
    {
      if(IS_COLOR){
        graphics_fill_rect(ctx, GRect(37+WEATHER_OFFSET_X, 76+WEATHER_OFFSET_Y, 30, 45), 0, GCornerNone);   
      }

      else {
        for (int i = 0; i<30;i=i+2){
          graphics_fill_rect(ctx, GRect(37+WEATHER_OFFSET_X+i, 76+WEATHER_OFFSET_Y, 1, 45), 0, GCornerNone);   
        }
      }


    }
    else
    {
      if(IS_COLOR){
        graphics_fill_rect(ctx, GRect(37+WEATHER_OFFSET_X,76+45-rain_pixel+WEATHER_OFFSET_Y , 30, rain_pixel), 0, GCornerNone); 
      }

      else {
        for (int i = 0; i<30;i=i+2){
          graphics_fill_rect(ctx, GRect(37+WEATHER_OFFSET_X+i,76+45-rain_pixel+WEATHER_OFFSET_Y , 1, rain_pixel), 0, GCornerNone); 
        }
      }

    }

    rain_pixel = 45*rain2_val/max_rain;
    if (rain_pixel > 45)
    {
      if(IS_COLOR){
        graphics_fill_rect(ctx, GRect(67+WEATHER_OFFSET_X, 76+WEATHER_OFFSET_Y, 30, 45), 0, GCornerNone);    
      }

      else {
        for (int i = 0; i<30;i=i+2){
          graphics_fill_rect(ctx, GRect(67+WEATHER_OFFSET_X+i, 76+WEATHER_OFFSET_Y, 1, 45), 0, GCornerNone);  
        }
      }    


    }
    else
    {

      if(IS_COLOR){
        graphics_fill_rect(ctx, GRect(67+WEATHER_OFFSET_X,76+45-rain_pixel+WEATHER_OFFSET_Y , 30, rain_pixel), 0, GCornerNone); 
      }

      else {
        for (int i = 0; i<30;i=i+2){
          graphics_fill_rect(ctx, GRect(67+WEATHER_OFFSET_X+i,76+45-rain_pixel+WEATHER_OFFSET_Y , 1, rain_pixel), 0, GCornerNone); 
        }
      }

    }

    rain_pixel = 45*rain3_val/max_rain;
    if (rain_pixel > 45)
    {

      if(IS_COLOR){
        graphics_fill_rect(ctx, GRect(97+WEATHER_OFFSET_X, 76+WEATHER_OFFSET_Y, 30, 45), 0, GCornerNone);   
      }

      else {
        for (int i = 0; i<30;i=i+2){
          graphics_fill_rect(ctx, GRect(97+WEATHER_OFFSET_X+i, 76+WEATHER_OFFSET_Y, 1, 45), 0, GCornerNone);   
        }
      }
    }
    else
    {

      if(IS_COLOR){
        graphics_fill_rect(ctx, GRect(97+WEATHER_OFFSET_X,76+45-rain_pixel+WEATHER_OFFSET_Y , 30, rain_pixel), 0, GCornerNone); 
      }

      else {
        for (int i = 0; i<30;i=i+2){
          graphics_fill_rect(ctx, GRect(97+WEATHER_OFFSET_X+i,76+45-rain_pixel+WEATHER_OFFSET_Y , 1, rain_pixel), 0, GCornerNone); 
        }
      }
    }
    rain_pixel = 45*rain4_val/max_rain;
    if (rain_pixel > 45)
    {
      if(IS_COLOR){
        graphics_fill_rect(ctx, GRect(127+WEATHER_OFFSET_X, 76+WEATHER_OFFSET_Y, 30, 45), 0, GCornerNone);   
      }

      else {
        for (int i = 0; i<30;i=i+2){
          graphics_fill_rect(ctx, GRect(127+WEATHER_OFFSET_X+i, 76+WEATHER_OFFSET_Y, 1, 45), 0, GCornerNone);   
        }
      }

    }
    else
    {
      if(IS_COLOR){
        graphics_fill_rect(ctx, GRect(127+WEATHER_OFFSET_X,76+45-rain_pixel +WEATHER_OFFSET_Y, 30, rain_pixel), 0, GCornerNone); 
      }

      else {
        for (int i = 0; i<30;i=i+2){
          graphics_fill_rect(ctx, GRect(127+WEATHER_OFFSET_X+i,76+45-rain_pixel +WEATHER_OFFSET_Y, 1, rain_pixel), 0, GCornerNone); 
        }
      }

    }




    APP_LOG(APP_LOG_LEVEL_INFO, "RAINS %i %i %i %i", rain1_val, rain2_val, rain3_val, rain4_val);



    int ttmin = temps[0];
    int ttmax = temps[0];

    for (int k=0; k<5;k++){
      if (ttmin>=temps[k]){
        ttmin=temps[k];
      }

      if (ttmax<temps[k]){
        ttmax=temps[k];
      } 
    }


    int echelle =1;
    while (ttmin<ttmax-echelle*3){
      echelle++;
    }

    static char t1[20];
    static char t2[20];


    snprintf(t1, sizeof(t1), "%i", ttmax);   
    snprintf(t2, sizeof(t2), "%i", ttmax-echelle*2); 

    graphics_context_set_text_color(ctx, color_temp);
    graphics_draw_text(ctx, t1, statusfontdate, rect_t1, GTextOverflowModeWordWrap,
                       GTextAlignmentRight, NULL); 
    graphics_draw_text(ctx, t2, statusfontdate, rect_t2, GTextOverflowModeWordWrap,
                       GTextAlignmentRight, NULL); 

    float f;
    f= 76 + (ttmax-temps[0])*15/echelle;
    int y1=(int)f;
    f= 76 + (ttmax-temps[1])*15/echelle;
    int y2=(int)f;
    f= 76 + (ttmax-temps[2])*15/echelle;
    int y3=(int)f; 
    f= 76 + (ttmax-temps[3])*15/echelle;   
    int y4=(int)f;
    f= 76 + (ttmax-temps[4])*15/echelle;
    int y5=(int)f;

    graphics_context_set_stroke_width(ctx, LINE_THICK);
    int freezing_temp;
    if(is_metric)
      freezing_temp=0;
    else
      freezing_temp=32;


    //Temperature
    if ((temps[0]<freezing_temp)&&(temps[1]<freezing_temp))
      graphics_context_set_stroke_color(ctx, BLUE_LINE);
    else
      graphics_context_set_stroke_color(ctx, RED_LINE);

    graphics_draw_line(ctx, GPoint(37+WEATHER_OFFSET_X,y1+WEATHER_OFFSET_Y),GPoint(67+WEATHER_OFFSET_X,y2+WEATHER_OFFSET_Y));

    if ((temps[1]<freezing_temp)&&(temps[2]<freezing_temp))
      graphics_context_set_stroke_color(ctx, BLUE_LINE);
    else
      graphics_context_set_stroke_color(ctx, RED_LINE);

    graphics_draw_line(ctx, GPoint(67+WEATHER_OFFSET_X,y2+WEATHER_OFFSET_Y),GPoint(97+WEATHER_OFFSET_X,y3+WEATHER_OFFSET_Y));

    if ((temps[2]<freezing_temp)&&(temps[3]<freezing_temp))
      graphics_context_set_stroke_color(ctx, BLUE_LINE);
    else
      graphics_context_set_stroke_color(ctx, RED_LINE);

    graphics_draw_line(ctx, GPoint(97+WEATHER_OFFSET_X,y3+WEATHER_OFFSET_Y),GPoint(127+WEATHER_OFFSET_X,y4+WEATHER_OFFSET_Y));

    if ((temps[3]<freezing_temp)&&(temps[4]<freezing_temp))  
      graphics_context_set_stroke_color(ctx, BLUE_LINE);
    else
      graphics_context_set_stroke_color(ctx, RED_LINE);

    graphics_draw_line(ctx, GPoint(127+WEATHER_OFFSET_X,y4+WEATHER_OFFSET_Y),GPoint(157+WEATHER_OFFSET_X,y5+WEATHER_OFFSET_Y));


    GRect rect_icon1= {{ 67-18+WEATHER_OFFSET_X, y2-40+WEATHER_OFFSET_Y }, {36 , 36 } };
    GRect rect_icon2= {{ 97-18+WEATHER_OFFSET_X, y3-40+WEATHER_OFFSET_Y }, {36 , 36 } };
    GRect rect_icon3= {{ 127-18+WEATHER_OFFSET_X, y4-40+WEATHER_OFFSET_Y }, {36 , 36 } };

    graphics_context_set_compositing_mode(ctx, GCompOpSet);

    if(!IS_COLOR){
      s_icon = gbitmap_create_with_resource(RESOURCE_ID_TABLE_OG);
      graphics_draw_bitmap_in_rect(ctx, s_icon, rect_screen);   
      gbitmap_destroy(s_icon);
    }
    else{
      s_icon = gbitmap_create_with_resource(RESOURCE_ID_TABLE);
      graphics_draw_bitmap_in_rect(ctx, s_icon, rect_screen);   
      gbitmap_destroy(s_icon);


    }


    int ic1 = build_icon(icon1);
    int ic2 = build_icon(icon2);
    int ic3 = build_icon(icon3);

    s_icon = gbitmap_create_with_resource(ic1);
    graphics_draw_bitmap_in_rect(ctx, s_icon, rect_icon1);
    gbitmap_destroy(s_icon);

    s_icon = gbitmap_create_with_resource(ic2);
    graphics_draw_bitmap_in_rect(ctx, s_icon, rect_icon2);
    gbitmap_destroy(s_icon);

    s_icon = gbitmap_create_with_resource(ic3);
    graphics_draw_bitmap_in_rect(ctx, s_icon, rect_icon3);
    gbitmap_destroy(s_icon);


    // heure
    time_t t = time(NULL);
    struct tm now = *(localtime(&t)); 
    char time_buffer[10];

    // Write the current hours and minutes into the buffer
    if(clock_is_24h_style() == true) {
      // Use 24 hour format
      strftime(heure, sizeof(heure), "%H:%M", &now);


    } else {
      // Use 12 hour format
      strftime(time_buffer, sizeof(time_buffer), "%I:%M", &now);
      snprintf(heure, sizeof(heure), "%s",time_buffer+(('0' == time_buffer[0])?1:0));

    }

    graphics_context_set_text_color(ctx, color_hours);
    graphics_draw_text(ctx, heure, fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK), rect_time, GTextOverflowModeWordWrap,
                       GTextAlignmentCenter, NULL);



  } 



}

void timer_callback(void *data){
  is_tapped=false;
  APP_LOG(APP_LOG_LEVEL_DEBUG,"dirty timer callback");
  layer_mark_dirty(layer);
}


static void handle_tap(AccelAxisType axis, int32_t direction) {
  if(!is_tapped){
    app_timer_register(TAP_DURATION, timer_callback, NULL);
    is_tapped = true;
    APP_LOG(APP_LOG_LEVEL_DEBUG,"dirty handle_tap");
    layer_mark_dirty(layer);

  }
}

static void handle_tick(struct tm *cur, TimeUnits units_changed) {
  time_t t = time(NULL);
  struct tm now = *(localtime(&t)); 


  if (is_vibration){
    if (now.tm_min == 0 && now.tm_hour >= QUIET_TIME_END && now.tm_hour <= QUIET_TIME_START) {
      vibes_double_pulse();
    }
  }


  // Get weather update every 30 minutes
  if(now.tm_min % 30 == 0) {
    if(((is_30mn)&&(now.tm_min % 30 == 0))||(now.tm_min % 60 == 0)){
      // Begin dictionary
      DictionaryIterator *iter;
      app_message_outbox_begin(&iter);

      // Add a key-value pair
      dict_write_uint8(iter, 0, 0);
      // Send the message!
      app_message_outbox_send();
    }
  }

  APP_LOG(APP_LOG_LEVEL_DEBUG, "Time now: %d", (int)mktime(&now));
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Last refresh: %d", (int)last_refresh);

  if((mktime(&now)-last_refresh)>duration){
    // Begin dictionary
    DictionaryIterator *iter;
    app_message_outbox_begin(&iter);

    // Add a key-value pair
    dict_write_uint8(iter, 0, 0);
    app_message_outbox_send();
  }

  APP_LOG(APP_LOG_LEVEL_DEBUG,"dirty tick");
  layer_mark_dirty(layer);
}

static void handle_battery(BatteryChargeState charge) {
  battery_level = charge.charge_percent;
  APP_LOG(APP_LOG_LEVEL_DEBUG, "handle_battery -> %d", (int)battery_level);
  is_charging=charge.is_charging;
  APP_LOG(APP_LOG_LEVEL_DEBUG,"dirty handle battery");
  layer_mark_dirty(layer);
}



static void setHourLinePoints() {
  hour_line_ypos = HEIGHT / 2;


  line1_p1.y = line1_p2.y = hour_line_ypos;
  line2_p1 = line1_p1;
  line2_p2 = line1_p2;
  line2_p1.y++;
  line2_p2.y++;
}


/*
static void reset_weather(){
  snprintf(h1, sizeof(h1), "%s", " ");
  snprintf(h2, sizeof(h2), "%s", " ");
  snprintf(h3, sizeof(h3), "%s", " ");
  wind1_val=0;
  wind2_val=0;
  wind3_val=0;
  snprintf(location, sizeof(location), "%s", " ");

  temp1_val=0;
  temp2_val=0;
  temp3_val=0;
  temp4_val=0;
  temp5_val=0;
  rain1_val=0;
  rain2_val=0;
  rain3_val=0;
  rain4_val=0;

  tmin_val=0;
  tmax_val=0;


  snprintf(icon1, sizeof(icon1), "%s", " ");
  snprintf(icon2, sizeof(icon2), "%s", " ");
  snprintf(icon3, sizeof(icon3), "%s", " ");

  snprintf(weather_temp, sizeof(weather_temp), "%s", " ");


}

*/
void bt_handler(bool connected) {
  if(connected){
    is_connected=true;
  }
  else
  {
    is_connected=false;
  }
  APP_LOG(APP_LOG_LEVEL_DEBUG,"dirty handler bt");
  layer_mark_dirty(layer);
}


static void initBatteryLevel() {
  BatteryChargeState battery_state = battery_state_service_peek();
  battery_level = battery_state.charge_percent;
}



static void inbox_received_callback(DictionaryIterator *iterator, void *context) {

  // Read tuples for data
  Tuple *temp_tuple = dict_find(iterator, KEY_TEMPERATURE);
  Tuple *conditions_tuple = dict_find(iterator, KEY_CONDITIONS);
  Tuple *wind_speed_tuple = dict_find(iterator, KEY_WIND_SPEED);
  Tuple *tmin_tuple = dict_find(iterator, KEY_TMIN);
  Tuple *tmax_tuple = dict_find(iterator, KEY_TMAX); 
  Tuple *icon_tuple = dict_find(iterator, KEY_ICON);
  Tuple *h1_tuple = dict_find(iterator, KEY_FORECAST_H1);
  Tuple *h2_tuple = dict_find(iterator, KEY_FORECAST_H2);
  Tuple *h3_tuple = dict_find(iterator, KEY_FORECAST_H3);
  Tuple *wind1_tuple = dict_find(iterator, KEY_FORECAST_WIND1);
  Tuple *wind2_tuple = dict_find(iterator, KEY_FORECAST_WIND2);
  Tuple *wind3_tuple = dict_find(iterator, KEY_FORECAST_WIND3);
  Tuple *location_tuple = dict_find(iterator, KEY_LOCATION);
  Tuple *temp1_tuple = dict_find(iterator, KEY_FORECAST_TEMP1);
  Tuple *temp2_tuple = dict_find(iterator, KEY_FORECAST_TEMP2);
  Tuple *temp3_tuple = dict_find(iterator, KEY_FORECAST_TEMP3);
  Tuple *temp4_tuple = dict_find(iterator, KEY_FORECAST_TEMP4);
  Tuple *temp5_tuple = dict_find(iterator, KEY_FORECAST_TEMP5);
  Tuple *icon1_tuple = dict_find(iterator, KEY_FORECAST_ICON1);
  Tuple *icon2_tuple = dict_find(iterator, KEY_FORECAST_ICON2);
  Tuple *icon3_tuple = dict_find(iterator, KEY_FORECAST_ICON3);
  Tuple *rain1_tuple = dict_find(iterator, KEY_FORECAST_RAIN1);
  Tuple *rain2_tuple = dict_find(iterator, KEY_FORECAST_RAIN2);
  Tuple *rain3_tuple = dict_find(iterator, KEY_FORECAST_RAIN3);
  Tuple *rain4_tuple = dict_find(iterator, KEY_FORECAST_RAIN4);

  Tuple *gps_tuple = dict_find(iterator, KEY_GPS);
  Tuple *city_tuple = dict_find(iterator, KEY_INPUT_CITY);
  Tuple *utc_tuple = dict_find(iterator, KEY_SELECT_UTC);
  Tuple *radio_tuple = dict_find(iterator, KEY_RADIO_UNITS);
  Tuple *refresh_tuple = dict_find(iterator, KEY_RADIO_REFRESH);
  Tuple *vibration_tuple = dict_find(iterator, KEY_TOGGLE_VIBRATION);
  Tuple *bw_icon_tuple = dict_find(iterator, KEY_TOGGLE_BW_ICONS);

  Tuple *color_right_r_tuple = dict_find(iterator, KEY_COLOR_RIGHT_R);
  Tuple *color_right_g_tuple = dict_find(iterator, KEY_COLOR_RIGHT_G);
  Tuple *color_right_b_tuple = dict_find(iterator, KEY_COLOR_RIGHT_B);

  Tuple *color_left_r_tuple = dict_find(iterator, KEY_COLOR_LEFT_R);
  Tuple *color_left_g_tuple = dict_find(iterator, KEY_COLOR_LEFT_G);
  Tuple *color_left_b_tuple = dict_find(iterator, KEY_COLOR_LEFT_B); 

  Tuple *color_hours_r_tuple = dict_find(iterator, KEY_COLOR_HOURS_R);
  Tuple *color_hours_g_tuple = dict_find(iterator, KEY_COLOR_HOURS_G);
  Tuple *color_hours_b_tuple = dict_find(iterator, KEY_COLOR_HOURS_B);

  Tuple *color_ruler_r_tuple = dict_find(iterator, KEY_COLOR_RULER_R);
  Tuple *color_ruler_g_tuple = dict_find(iterator, KEY_COLOR_RULER_G);
  Tuple *color_ruler_b_tuple = dict_find(iterator, KEY_COLOR_RULER_B);

  Tuple *color_temp_r_tuple = dict_find(iterator, KEY_COLOR_TEMPERATURES_R);
  Tuple *color_temp_g_tuple = dict_find(iterator, KEY_COLOR_TEMPERATURES_G);
  Tuple *color_temp_b_tuple = dict_find(iterator, KEY_COLOR_TEMPERATURES_B);

  int red;
  int green;
  int blue;

  if(gps_tuple&&city_tuple&&utc_tuple&&radio_tuple&&vibration_tuple&&bw_icon_tuple&&color_right_r_tuple&&color_right_g_tuple
     &&color_right_b_tuple&&color_left_r_tuple&&color_left_g_tuple&&color_left_b_tuple&&color_hours_r_tuple
     &&color_hours_g_tuple&&color_hours_b_tuple&&color_ruler_r_tuple&&color_ruler_g_tuple&&color_ruler_b_tuple
     &&color_temp_r_tuple&&color_temp_g_tuple&&color_temp_b_tuple&&refresh_tuple){

    is_gps=gps_tuple->value->int32;

    snprintf(city, sizeof(city), "%s", city_tuple->value->cstring);  


    char utc_char[10];
    snprintf(utc_char, sizeof(utc_char), "%s", utc_tuple->value->cstring);  

    utc=atoi(utc_char);

    is_metric=!(radio_tuple->value->int32);
    is_30mn=(refresh_tuple->value->int32);
    APP_LOG(APP_LOG_LEVEL_DEBUG, "is_30mn %i", (int)is_30mn);


    is_vibration=vibration_tuple->value->int32;
    is_bw_icon=bw_icon_tuple->value->int32;

    red = color_right_r_tuple->value->int32;
    green = color_right_g_tuple->value->int32;
    blue = color_right_b_tuple->value->int32;
    // Persist values
    persist_write_int(KEY_COLOR_RIGHT_R, red);
    persist_write_int(KEY_COLOR_RIGHT_G, green);
    persist_write_int(KEY_COLOR_RIGHT_B, blue);
    color_right = GColorFromRGB(red, green, blue);

    red = color_left_r_tuple->value->int32;
    green = color_left_g_tuple->value->int32;
    blue = color_left_b_tuple->value->int32;
    // Persist values
    persist_write_int(KEY_COLOR_LEFT_R, red);
    persist_write_int(KEY_COLOR_LEFT_G, green);
    persist_write_int(KEY_COLOR_LEFT_B, blue);
    color_left = GColorFromRGB(red, green, blue);

    red = color_hours_r_tuple->value->int32;
    green = color_hours_g_tuple->value->int32;
    blue = color_hours_b_tuple->value->int32;
    APP_LOG(APP_LOG_LEVEL_DEBUG, "RGB color temp %i %i %i", red, green, blue);
    // Persist values
    persist_write_int(KEY_COLOR_HOURS_R, red);
    persist_write_int(KEY_COLOR_HOURS_G, green);
    persist_write_int(KEY_COLOR_HOURS_B, blue);
    color_hours=GColorFromRGB(red, green, blue);

    red = color_ruler_r_tuple->value->int32;
    green = color_ruler_g_tuple->value->int32;
    blue = color_ruler_b_tuple->value->int32;
    // Persist values
    persist_write_int(KEY_COLOR_RULER_R, red);
    persist_write_int(KEY_COLOR_RULER_G, green);
    persist_write_int(KEY_COLOR_RULER_B, blue);
    color_ruler=GColorFromRGB(red, green, blue);

    red = color_temp_r_tuple->value->int32;
    green = color_temp_g_tuple->value->int32;
    blue = color_temp_b_tuple->value->int32;
    color_temp=GColorFromRGB(red, green, blue);  

    // Colors for OG pebbles
    if(!IS_COLOR){
      color_temp=GColorWhite;
      color_ruler=GColorWhite;
      color_hours=GColorWhite;
      color_left=GColorBlack;
      color_right=GColorBlack;
    }

    // Persist values
    persist_write_int(KEY_COLOR_TEMPERATURES_R, red);
    persist_write_int(KEY_COLOR_TEMPERATURES_G, green);
    persist_write_int(KEY_COLOR_TEMPERATURES_B, blue);


    persist_write_bool(KEY_GPS, is_gps);
    persist_write_string(KEY_INPUT_CITY, city);
    persist_write_int(KEY_SELECT_UTC, utc);
    persist_write_bool( KEY_RADIO_UNITS, is_metric);
    persist_write_bool( KEY_RADIO_REFRESH, is_30mn);
    persist_write_bool( KEY_TOGGLE_VIBRATION, is_vibration);
    persist_write_bool( KEY_TOGGLE_BW_ICONS, is_bw_icon);
    APP_LOG(APP_LOG_LEVEL_DEBUG,"dirty inbox_received_callback+ settings");

    // We refresh the weather


    layer_mark_dirty(layer);  



  }
  // If all data is available, use it
  if(temp_tuple && conditions_tuple && wind_speed_tuple && icon_tuple && wind_speed_tuple && tmin_tuple &&tmax_tuple&&h1_tuple&&h2_tuple&&h3_tuple&&wind1_tuple&&wind2_tuple
     &&wind3_tuple&&location_tuple&&temp1_tuple&&temp1_tuple&&temp2_tuple&&temp3_tuple&&temp4_tuple&&temp5_tuple&&icon1_tuple&&icon2_tuple&&icon3_tuple&&rain1_tuple&&rain2_tuple
     &&rain3_tuple&&rain4_tuple) {

    snprintf(weather_temp, sizeof(weather_temp), "%s", temp_tuple->value->cstring);
    snprintf(conditions, sizeof(conditions), "%s", conditions_tuple->value->cstring);
    snprintf(h1, sizeof(h1), "%s", h1_tuple->value->cstring);
    snprintf(h2, sizeof(h2), "%s", h2_tuple->value->cstring);
    snprintf(h3, sizeof(h3), "%s", h3_tuple->value->cstring);
    snprintf(icon, sizeof(icon), "%s", icon_tuple->value->cstring);
    snprintf(location, sizeof(location), "%s", location_tuple->value->cstring);
    snprintf(icon1, sizeof(icon1), "%s", icon1_tuple->value->cstring);
    snprintf(icon2, sizeof(icon2), "%s", icon2_tuple->value->cstring);
    snprintf(icon3, sizeof(icon3), "%s", icon3_tuple->value->cstring);

    rain1_val=(int)rain1_tuple->value->int32;
    rain2_val=(int)rain2_tuple->value->int32;
    rain3_val=(int)rain3_tuple->value->int32;
    rain4_val=(int)rain4_tuple->value->int32;
    tmin_val=(int)tmin_tuple->value->int32;
    tmax_val=(int)tmax_tuple->value->int32;
    wind1_val=(int)wind1_tuple->value->int32;
    wind2_val=(int)wind2_tuple->value->int32;
    wind3_val=(int)wind3_tuple->value->int32;
    temp1_val=(int)temp1_tuple->value->int32;
    temp2_val=(int)temp2_tuple->value->int32;
    temp3_val=(int)temp3_tuple->value->int32;
    temp4_val=(int)temp4_tuple->value->int32;
    temp5_val=(int)temp5_tuple->value->int32;
    wind_speed_val=(int)wind_speed_tuple->value->int32;

    time_t t = time(NULL);
    struct tm now = *(localtime(&t)); 

    last_refresh = mktime(&now);

    persist_write_string(KEY_TEMPERATURE, weather_temp);
    persist_write_string(KEY_CONDITIONS, conditions);
    persist_write_string(KEY_FORECAST_H1, h1);
    persist_write_string(KEY_FORECAST_H2, h2);
    persist_write_string(KEY_FORECAST_H3, h3);
    persist_write_string(KEY_ICON, icon);
    persist_write_string(KEY_LOCATION, location);

    persist_write_string(KEY_FORECAST_ICON1, icon1);
    persist_write_string(KEY_FORECAST_ICON2, icon2);
    persist_write_string(KEY_FORECAST_ICON3, icon3);

    persist_write_int(KEY_LAST_REFRESH, last_refresh);

    persist_write_int(KEY_WIND_SPEED, wind_speed_val);
    persist_write_int(KEY_TMIN, tmin_val);
    persist_write_int(KEY_TMAX, tmax_val);

    persist_write_int(KEY_FORECAST_WIND1, wind1_val);
    persist_write_int(KEY_FORECAST_WIND2, wind2_val);
    persist_write_int(KEY_FORECAST_WIND3, wind3_val);

    persist_write_int(KEY_FORECAST_TEMP1, temp1_val);
    persist_write_int(KEY_FORECAST_TEMP2, temp2_val);
    persist_write_int(KEY_FORECAST_TEMP3, temp3_val);
    persist_write_int(KEY_FORECAST_TEMP4, temp4_val);
    persist_write_int(KEY_FORECAST_TEMP5, temp5_val);

    persist_write_int(KEY_FORECAST_RAIN1, rain1_val);
    persist_write_int(KEY_FORECAST_RAIN2, rain2_val);
    persist_write_int(KEY_FORECAST_RAIN3, rain3_val);
    persist_write_int(KEY_FORECAST_RAIN4, rain4_val);

    APP_LOG(APP_LOG_LEVEL_DEBUG,"dirty inbox_received_callback + weather");
    layer_mark_dirty(layer);  

  }
}

static void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Outbox send failed!");
}

static void outbox_sent_callback(DictionaryIterator *iterator, void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Outbox send success!");
}



static void init() {
  time_t t;
  int i;

  statusfontsmall = fonts_get_system_font(FONT_KEY_GOTHIC_14);
  statusfontsmallbold = fonts_get_system_font(FONT_KEY_GOTHIC_14_BOLD);
  statusfontdate = fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD);


  if(persist_exists(KEY_GPS)&&persist_exists(KEY_SELECT_UTC)&&persist_exists(KEY_RADIO_UNITS)
     &&persist_exists(KEY_RADIO_REFRESH)&&persist_exists(KEY_TOGGLE_VIBRATION)&&persist_exists(KEY_TOGGLE_BW_ICONS)){

    is_gps=persist_read_bool(KEY_GPS); 
    utc=persist_read_int(KEY_SELECT_UTC);

    is_metric=persist_read_bool(KEY_RADIO_UNITS);
    is_30mn=persist_read_bool(KEY_RADIO_REFRESH);

    is_vibration=persist_read_bool(KEY_TOGGLE_VIBRATION);
    is_bw_icon=persist_read_bool(KEY_TOGGLE_BW_ICONS);

    int red;
    int green;
    int blue;
    red = persist_read_int(KEY_COLOR_RIGHT_R);
    green = persist_read_int(KEY_COLOR_RIGHT_G);
    blue = persist_read_int(KEY_COLOR_RIGHT_B);
    color_right=GColorFromRGB(red, green, blue);

    red = persist_read_int(KEY_COLOR_LEFT_R);
    green = persist_read_int(KEY_COLOR_LEFT_G);
    blue = persist_read_int(KEY_COLOR_LEFT_B);
    color_left=GColorFromRGB(red, green, blue);

    red = persist_read_int(KEY_COLOR_HOURS_R);
    green = persist_read_int(KEY_COLOR_HOURS_G);
    blue = persist_read_int(KEY_COLOR_HOURS_B);
    color_hours=GColorFromRGB(red, green, blue);

    red = persist_read_int(KEY_COLOR_RULER_R);
    green = persist_read_int(KEY_COLOR_RULER_G);
    blue = persist_read_int(KEY_COLOR_RULER_B);
    color_ruler=GColorFromRGB(red, green, blue);

    red = persist_read_int(KEY_COLOR_TEMPERATURES_R);
    green = persist_read_int(KEY_COLOR_TEMPERATURES_G);
    blue = persist_read_int(KEY_COLOR_TEMPERATURES_B);
    color_temp=GColorFromRGB(red, green, blue);

  }
  else{
    is_gps=true; 
    utc=0;

    is_metric=true;
    is_vibration=false;
    is_bw_icon=false; 
    color_right=GColorCadetBlue;
    color_left=GColorWhite;
    color_hours=GColorWhite;
    color_ruler=GColorBlack;
    color_temp=GColorCadetBlue;
  }
  if(persist_exists(KEY_LAST_REFRESH)&&persist_exists(KEY_WIND_SPEED)&&persist_exists(KEY_TMIN)
     &&persist_exists(KEY_TMAX)&&persist_exists(KEY_FORECAST_WIND1)&&persist_exists(KEY_FORECAST_WIND2)
     &&persist_exists(KEY_FORECAST_WIND3)&&persist_exists(KEY_FORECAST_TEMP1)&&persist_exists(KEY_FORECAST_TEMP2)
     &&persist_exists(KEY_FORECAST_TEMP3)&&persist_exists(KEY_FORECAST_TEMP4)&&persist_exists(KEY_FORECAST_TEMP5)
     &&persist_exists(KEY_FORECAST_RAIN1)&&persist_exists(KEY_FORECAST_RAIN2)&&persist_exists(KEY_FORECAST_RAIN3)
     &&persist_exists(KEY_FORECAST_RAIN4)&&persist_exists(KEY_TEMPERATURE)&&persist_exists(KEY_CONDITIONS)
     &&persist_exists(KEY_FORECAST_H1)&&persist_exists(KEY_FORECAST_H2)&&persist_exists(KEY_FORECAST_H3)
     &&persist_exists(KEY_ICON)&&persist_exists(KEY_LOCATION)&&persist_exists(KEY_FORECAST_ICON1)
     &&persist_exists(KEY_FORECAST_ICON2)&&persist_exists(KEY_FORECAST_ICON3)){

    last_refresh = persist_read_int(KEY_LAST_REFRESH);
    wind_speed_val = persist_read_int(KEY_WIND_SPEED);
    tmin_val = persist_read_int(KEY_TMIN);
    tmax_val = persist_read_int(KEY_TMAX);
    wind1_val = persist_read_int(KEY_FORECAST_WIND1);
    wind2_val = persist_read_int(KEY_FORECAST_WIND2);
    wind3_val = persist_read_int(KEY_FORECAST_WIND3);
    temp1_val = persist_read_int(KEY_FORECAST_TEMP1);
    temp2_val = persist_read_int(KEY_FORECAST_TEMP2);
    temp3_val = persist_read_int(KEY_FORECAST_TEMP3);
    temp4_val = persist_read_int(KEY_FORECAST_TEMP4);
    temp5_val = persist_read_int(KEY_FORECAST_TEMP5);
    rain1_val = persist_read_int(KEY_FORECAST_RAIN1);
    rain2_val = persist_read_int(KEY_FORECAST_RAIN2);
    rain3_val = persist_read_int(KEY_FORECAST_RAIN3);
    rain4_val = persist_read_int(KEY_FORECAST_RAIN4);

    persist_read_string(KEY_TEMPERATURE, weather_temp, sizeof(weather_temp));
    persist_read_string(KEY_CONDITIONS, conditions, sizeof(conditions));
    persist_read_string(KEY_FORECAST_H1, h1, sizeof(h1));
    persist_read_string(KEY_FORECAST_H2, h2, sizeof(h2));
    persist_read_string(KEY_FORECAST_H3, h3, sizeof(h3));
    persist_read_string(KEY_ICON, icon, sizeof(icon));
    persist_read_string(KEY_LOCATION, location, sizeof(location));
    persist_read_string(KEY_FORECAST_ICON1, icon1, sizeof(icon1));
    persist_read_string(KEY_FORECAST_ICON2, icon2, sizeof(icon2));
    persist_read_string(KEY_FORECAST_ICON3, icon3, sizeof(icon3));
  }
  else{
    last_refresh = 0;
    wind_speed_val = 0;
    tmin_val = 0;
    tmax_val = 0;
    wind1_val = 0;
    wind2_val = 0;
    wind3_val = 0;
    temp1_val = 0;
    temp2_val = 0;
    temp3_val = 0;
    temp4_val = 0;
    temp5_val = 0;
    rain1_val = 0;
    rain2_val = 0;
    rain3_val = 0;
    rain4_val = 0;
    snprintf(weather_temp, sizeof(weather_temp), " ");
    snprintf(conditions, sizeof(conditions), " ");
    snprintf(h1, sizeof(h1), " ");
    snprintf(h2, sizeof(h2), " ");
    snprintf(h3, sizeof(h3), " ");
    snprintf(icon, sizeof(icon), " ");
    snprintf(icon1, sizeof(icon1), " ");
    snprintf(icon2, sizeof(icon2), " ");
    snprintf(icon3, sizeof(icon3), " ");
    snprintf(location, sizeof(location), " ");
  }

  if(!IS_COLOR){
    color_temp=GColorWhite;
    color_ruler=GColorWhite;
    color_hours=GColorWhite;
    color_left=GColorBlack;
    color_right=GColorBlack;
  }

  APP_LOG(APP_LOG_LEVEL_DEBUG, "\n\nis_30mn %d \n is_gps %d\n utc %d\nis_metric %d\nis_vibration %d\nis_bw_icon %d\n", is_30mn, is_gps, utc, is_metric, is_vibration, is_bw_icon);

  snprintf(pebble_Lang, sizeof(pebble_Lang), "%s", i18n_get_system_locale());

  hours60 = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_CLEARVIEW_60));

  BatteryChargeState charge_state = battery_state_service_peek();
  is_charging = charge_state.is_charging;
  is_connected = connection_service_peek_pebble_app_connection();

  if (!clock_is_24h_style()) {
    for (i=0; i<28; i++) {
      labels[i] = labels_12h[i];
    }
  }

  setHourLinePoints();
  initBatteryLevel();

  window = window_create();
  window_set_background_color(window, color_left);
  window_stack_push(window, true);

  rootLayer = window_get_root_layer(window);

  layer = layer_create(layer_get_bounds(rootLayer));
  layer_set_update_proc(layer, layer_update);
  layer_add_child(rootLayer, layer);

  hour_part_size = 26 * hour_size;

  if(is_30mn)
    duration=1800;
  else
    duration=3600;



  accel_tap_service_subscribe(handle_tap);
  tick_timer_service_subscribe(MINUTE_UNIT, handle_tick);
  battery_state_service_subscribe(handle_battery);
  bluetooth_connection_service_subscribe(bt_handler); 

  //JS Messages

  app_message_register_inbox_received(inbox_received_callback);
  app_message_register_outbox_failed(outbox_failed_callback);
  app_message_register_outbox_sent(outbox_sent_callback);

  // Open AppMessage
  //
  app_message_open(700, 700);
  /*
 1 + (n * 7) + D1 + ... + Dn
 Where n is the number of Tuples in the Dictionary and Dx are the sizes of the values in the Tuples. 
 The size of the Dictionary header is 1 byte. The size of the header for each Tuple is 7 bytes.
 */

}


static void deinit() {

  accel_tap_service_unsubscribe();
  tick_timer_service_unsubscribe();
  battery_state_service_unsubscribe();
  bluetooth_connection_service_unsubscribe();  
  app_message_deregister_callbacks();

  layer_destroy(layer);
  window_destroy(window);

}

int main(void) {
  init();
  app_event_loop();
  deinit();
}