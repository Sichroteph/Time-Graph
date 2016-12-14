var myAPIKey = 'ae461f943802d620eafda5d9d3c98f91';

var xhrRequest = function (url, type, callback) {
  var xhr = new XMLHttpRequest();
  xhr.onload = function () {
    callback(this.responseText);
  };
  xhr.open(type, url);
  xhr.send();
};

function getForecast(url, url2) {
  var tmax;
  var tmin;
  var temp1;
  var temp2;
  var temp3;
  var temp4;
  var temp5;
  var h1;
  var h2;
  var h3;
  var hour1;
  var hour2;
  var hour3; 
  var rain1;
  var rain2;
  var rain3;
  var rain4;
  var rain5;
  var icon1;
  var icon2;
  var icon3;
  var wind1;
  var wind2;
  var wind3;

  // Forecasting data


  console.log("url2 is " + url2);  


  // Send request to OpenWeatherMap

  xhrRequest(url2, 'GET', 
             function(responseText) {

               // responseText contains a JSON object with weather info

               var responseFixed = responseText.replace(/3h/g,"hh");
               var json2 = JSON.parse(responseFixed);


               var t = json2.list[0].main.temp;
               tmax = t;
               tmin = t;

               for(var i=1;i<8;i++){
                 if (json2.list[i].main.temp>tmax)
                   tmax = json2.list[i].main.temp;
                 if (json2.list[i].main.temp<tmin)
                   tmin = json2.list[i].main.temp;
               }

               temp1=Math.round(json2.list[0].main.temp);
               console.log("temp1 " + temp1);
               temp2=Math.round(json2.list[1].main.temp);
               temp3=Math.round(json2.list[2].main.temp);
               temp4=Math.round(json2.list[3].main.temp);
               temp5=Math.round(json2.list[4].main.temp);

               h1=json2.list[1].dt;
               console.log("h1 " + h1);
               h2=json2.list[2].dt;
               h3=json2.list[3].dt;
                
               var date1=new Date(h1*1000);
               var date2=new Date(h2*1000);
               var date3=new Date(h3*1000);
                                  
               
               hour1=date1.getHours()+"";
               hour2=date2.getHours()+"";
               hour3=date3.getHours()+"";



               icon1 = json2.list[1].weather[0].icon;
               icon2 = json2.list[2].weather[0].icon;
               icon3 = json2.list[3].weather[0].icon;

               if (json2.list[0].rain===undefined){
                 rain1=0;
               }
               else{
                 rain1=json2.list[0].rain.hh;
                 if (rain1>-666)
                   rain1=Math.round(rain1*10);
                 else{
                   rain1=0;
                 }
               }

               if (json2.list[1].rain===undefined){
                 rain2=0;
               }
               else{
                 rain2=json2.list[1].rain.hh;
                 if (rain2>-666)
                   rain2=Math.round(rain2*10);
                 else{

                   rain2=0;
                 }
               }
               if (json2.list[2].rain===undefined){
                 rain3=0;
               }
               else{
                 rain3=json2.list[2].rain.hh;
                 if (rain3>-666)
                   rain3=Math.round(rain3*10);
                 else{

                   rain3=0;
                 }
               }
               if (json2.list[3].rain===undefined){
                 rain4=0;
               }
               else{
                 rain4=json2.list[3].rain.hh;
                 if (rain4>-666)
                   rain4=Math.round(rain4*10);
                 else{

                   rain4=0;
                 }
               }
               if (json2.list[4].rain===undefined){
                 rain5=0;
               }
               else{
                 rain5=json2.list[4].rain.hh;
                 if (rain5>-666)
                   rain5=Math.round(rain5*10);
                 else{

                   rain5=0;
                 }
               }

  
               var units = localStorage.getItem(152);
               
               if(units==1){
                 wind1=Math.round((json2.list[1].wind.speed)*3.6);
                 wind2=Math.round((json2.list[2].wind.speed)*3.6);
                 wind3=Math.round((json2.list[3].wind.speed)*3.6);
                 
               }
               else{
                 wind1=Math.round(json2.list[1].wind.speed);
                 wind2=Math.round(json2.list[2].wind.speed);
                 wind3=Math.round(json2.list[3].wind.speed);
                 
               }
                 
               
               
               tmax=Math.round(tmax);
               tmin=Math.round(tmin);
               //console.log("tmax est " + tmax);



               console.log("url is " + url);
               // Send request to OpenWeatherMap
               xhrRequest(url, 'GET', 
                          function(responseText) {
                            // responseText contains a JSON object with weather info
                            var json = JSON.parse(responseText);

                            var location = json.name;

                            var temperature;

                         
                            var units_s;

                            if(units==1){
                              units_s="F";
                            }
                            else{
                              units_s="C";
                            }

                             temperature = Math.round(json.main.temp)+units_s;

                            // Conditions
                            var conditions = json.weather[0].main; 

                            var description = json.weather[0].description;

                            var wind = Math.round(json.wind.speed);

                            var clouds = json.clouds.all;

                            var humidity = json.main.humidity;

                            var sunrise = json.sys.sunrise;

                            var sunset = json.sys.sunset;


                            var dsunrise=new Date(sunrise*1000);
                            var dsunset=new Date(sunset*1000);
                            var sunrise_hours = dsunrise.getHours();
                            var sunrise_minutes = "0"+ dsunrise.getMinutes();
                            var sunset_hours = dsunset.getHours();
                            var sunset_minutes = "0"+ dsunset.getMinutes();

                            var sunrise_string = sunrise_hours+":"+sunrise_minutes.substr(-2);
                            var sunset_string = sunset_hours+":"+sunset_minutes.substr(-2);
                            var icon = json.weather[0].icon;

                            // testenvoi layer
                            // Assemble dictionary using our keys
                            var dictionary = {
                              "KEY_TEMPERATURE": temperature,
                              "KEY_CONDITIONS": conditions,
                              "KEY_DESCRIPTION": description,
                              "KEY_WIND_SPEED" : wind,
                              "KEY_CLOUDS" : clouds,
                              "KEY_HUMIDITY" : humidity,
                              "KEY_SUNRISE" : sunrise_string,
                              "KEY_SUNSET" : sunset_string,
                              "KEY_TMIN" : tmin, 
                              "KEY_TMAX" : tmax,
                              "KEY_ICON" : icon,

                              "KEY_FORECAST_TEMP1" : temp1,
                              "KEY_FORECAST_TEMP2" : temp2,
                              "KEY_FORECAST_TEMP3" : temp3,
                              "KEY_FORECAST_TEMP4" : temp4,
                              "KEY_FORECAST_TEMP5" : temp5,
                              "KEY_FORECAST_H1" : hour1,
                              "KEY_FORECAST_H2" : hour2,
                              "KEY_FORECAST_H3" : hour3,
                              "KEY_FORECAST_RAIN1" : rain1,
                              "KEY_FORECAST_RAIN2" : rain2,
                              "KEY_FORECAST_RAIN3" : rain3,
                              "KEY_FORECAST_RAIN4" : rain4,
                              "KEY_FORECAST_RAIN5" : rain5,
                              "KEY_FORECAST_ICON1" : icon1,
                              "KEY_FORECAST_ICON2" : icon2,
                              "KEY_FORECAST_ICON3" : icon3,
                              "KEY_FORECAST_WIND1" : wind1,
                              "KEY_FORECAST_WIND2" : wind2,
                              "KEY_FORECAST_WIND3" : wind3,
                              "KEY_LOCATION" : location,

                            }; 

                            // Send to Pebble
                            Pebble.sendAppMessage(dictionary,
                                                  function(e) {
                                                    console.log("Weather info sent to Pebble successfully!");
                                                  },
                                                  function(e) {
                                                    console.log("Error sending weather info to Pebble!");
                                                  }
                                                 );
                          }      
                         );
             }
            );

}




function locationSuccess(pos) {
  var units = localStorage.getItem(152);
  var units_s;

  if(units==1){
    units_s="imperial";
  }
  else{
    units_s="metric";
  }

  var url1 = 'http://api.openweathermap.org/data/2.5/weather?lat=' +
      pos.coords.latitude + '&lon=' + pos.coords.longitude + '&appid=' + myAPIKey + '&units='+units_s;

  var url2 = 'http://api.openweathermap.org/data/2.5/forecast?lat=' +
      pos.coords.latitude + '&lon=' + pos.coords.longitude + '&appid=' + myAPIKey + '&units='+units_s;

  //pluie
  //var url = "http://api.openweathermap.org/data/2.5/weather?lat=-6.21&lon=106.85&appid=ae461f943802d620eafda5d9d3c98f91&units=metric"               
  //soleil
  //var url = "http://api.openweathermap.org/data/2.5/weather?&lat=43.700111&lon=-79.416298" + '&appid=' + myAPIKey + '&units=metric';

  //pour pluie
  //var url2 = "http://api.openweathermap.org/data/2.5/forecast?lat=-6.21&lon=106.85&appid=ae461f943802d620eafda5d9d3c98f91&units=metric"
  //pour soleil
  //var url2 = "http://api.openweathermap.org/data/2.5/forecast?&lat=43.700111&lon=-79.416298&appid=ae461f943802d620eafda5d9d3c98f91&units=metric"
  getForecast(url1,url2);
}

function locationError(err) {
  console.log("Error requesting location!");
}



function send_url_position() {
  navigator.geolocation.getCurrentPosition(
    locationSuccess,
    locationError,
    {timeout: 15000, maximumAge: 60000}
  );


}

function send_url_city() {
  var city = localStorage.getItem(151);
  var units = localStorage.getItem(152);
  var units_s;
  if(units==1){
    units_s="imperial";
  }
  else{
    units_s="metric";
  }
  var url1 = 'http://api.openweathermap.org/data/2.5/weather?q='+city+ '&appid=' + myAPIKey + '&units='+units_s;
  var url2 = 'http://api.openweathermap.org/data/2.5/forecast?q='+city+ '&appid=' + myAPIKey + '&units='+units_s;  
  getForecast(url1,url2);
}

function getWeather(){

  var gps = localStorage.getItem(150);
  if((gps===null||gps==1)) {
    send_url_position() ;           
  }
  //city string
  else if(localStorage.getItem(150)!==null)
  {
    send_url_city() ;      
  }

}

// Listen for when the watchface is opened
Pebble.addEventListener('ready', 
                        function(e) {
                          console.log("PebbleKit JS ready!");
                          getWeather();
                        }
                       );

// Listen for when an AppMessage is received
Pebble.addEventListener('appmessage',
                        function(e) {
                          console.log("AppMessage received!");
                          getWeather();  
                        }                     
                       );



Pebble.addEventListener('showConfiguration', function() {
  var url = 'http://sichroteph.github.io/Time-Graph/';
  console.log('Showing configuration page: ' + url);
  Pebble.openURL(url);
});





Pebble.addEventListener('webviewclosed', function(e) {
  var configData = JSON.parse(decodeURIComponent(e.response));
  console.log('Configuration page returned: ' + JSON.stringify(configData));

  var gps = configData['gps'];
  var input_city = configData['input_city'];
  var select_utc = configData['select_utc'];
  var radio_units = configData['radio_units'];
  var radio_refresh = configData['radio_refresh'];
  var toggle_vibration = configData['toggle_vibration'];
  var toggle_bw_icons = configData['toggle_bw_icons'];
  var color_right_back = configData['color_right_back'];
  var color_left_back = configData['color_left_back'];
  var color_hours = configData['color_hours'];
  var color_ruler = configData['color_ruler'];
  var color_temperatures = configData['color_temperatures'];

 
  var dict = {};

  dict['KEY_GPS'] = configData['gps'] ? 1 : 0;  // Send a boolean as an integer
  dict['KEY_INPUT_CITY'] = configData['input_city'];
  dict['KEY_SELECT_UTC'] = configData['select_utc'];
  dict['KEY_RADIO_UNITS'] = configData['radio_units'] ? 1 : 0;
  dict['KEY_RADIO_REFRESH'] = configData['radio_refresh'] ? 1 : 0;
  dict['KEY_TOGGLE_VIBRATION'] = configData['toggle_vibration'] ? 1 : 0;
  dict['KEY_TOGGLE_BW_ICONS'] = configData['toggle_bw_icons'] ? 1 : 0;

  dict['KEY_COLOR_RIGHT_R'] = parseInt(color_right_back.substring(2, 4), 16);
  dict['KEY_COLOR_RIGHT_G'] = parseInt(color_right_back.substring(4, 6), 16);
  dict['KEY_COLOR_RIGHT_B'] = parseInt(color_right_back.substring(6, 8), 16);
  dict['KEY_COLOR_LEFT_R'] = parseInt(color_left_back.substring(2, 4), 16);
  dict['KEY_COLOR_LEFT_G'] = parseInt(color_left_back.substring(4, 6), 16);
  dict['KEY_COLOR_LEFT_B'] = parseInt(color_left_back.substring(6, 8), 16);


  dict['KEY_COLOR_HOURS_R'] = parseInt(color_hours.substring(2, 4), 16);
  dict['KEY_COLOR_HOURS_G'] = parseInt(color_hours.substring(4, 6), 16);
  dict['KEY_COLOR_HOURS_B'] = parseInt(color_hours.substring(6, 8), 16);
  console.log("colour_hours " + color_hours);
  console.log('parse int value', parseInt(color_hours.substring(1, 3), 16), parseInt(color_hours.substring(3, 5), 16),  parseInt(color_hours.substring(5, 7), 16));
  console.log('R G B ' + color_hours.substring(1, 3) + " "+ color_hours.substring(3, 5)+" "+color_hours.substring(5, 7));


  dict['KEY_COLOR_RULER_R'] = parseInt(color_ruler.substring(2, 4), 16);
  dict['KEY_COLOR_RULER_G'] = parseInt(color_ruler.substring(4, 6), 16);
  dict['KEY_COLOR_RULER_B'] = parseInt(color_ruler.substring(6, 8), 16);

  dict['KEY_COLOR_TEMPERATURES_R'] = parseInt(color_temperatures.substring(2, 4), 16);
  dict['KEY_COLOR_TEMPERATURES_G'] = parseInt(color_temperatures.substring(4, 6), 16);
  dict['KEY_COLOR_TEMPERATURES_B'] = parseInt(color_temperatures.substring(6, 8), 16);


  // Send to watchapp
  Pebble.sendAppMessage(dict, function() {
    console.log('Send successful: ' + JSON.stringify(dict));
  }, function() {
    console.log('Send failed!');
  }
                       );

  // Persist write a key with associated value

  localStorage.setItem(150, configData['gps'] ? 1 : 0);
  localStorage.setItem(151, configData['input_city']);
  localStorage.setItem(152, configData['radio_units'] ? 1 : 0);

  // refresh weather
  getWeather();


});
