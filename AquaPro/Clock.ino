void  initializeClock(){
  Rtc.Begin();
//  RtcDateTime data_compilacao = RtcDateTime(__DATE__, __TIME__);
//   Rtc.SetDateTime(data_compilacao);  

//RtcDateTime data = RtcDateTime(2017,12,1,5,0,0);
//Rtc.SetDateTime(data);
  if (!Rtc.IsDateTimeValid()){
    Serial.println(F("Relógio desatualizado."));
    Rtc.SetDateTime(RtcDateTime(__DATE__, __TIME__));
  }
  if(!Rtc.GetIsRunning()){
    Rtc.SetIsRunning(true);
  }
  Rtc.Enable32kHzPin(false);
  Rtc.SetSquareWavePin(DS3231SquareWavePin_ModeNone);
  if(DEBUG) Serial.println("Configurado");
}

String clockDateTime() {
  return clockDate() + " " + clockTime();
}

String clockTime() {
  RtcDateTime now = Rtc.GetDateTime();
  return String(formatTime(now, "h:m"));
}

String clockDate() {
  RtcDateTime now = Rtc.GetDateTime();
  return String(formatDate(now, "d/m/y"));
}

String formatTime(const RtcDateTime& dt, String format) {
  String h = dt.Hour() < 10 ? "0" + String(dt.Hour()) : String(dt.Hour()) ;
  String m = dt.Minute() < 10 ? "0" + String(dt.Minute()) : String(dt.Minute()) ;
  String s = dt.Second() < 10 ? "0" + String(dt.Second()) : String(dt.Second()) ;
  format.replace("h",h);
  format.replace("m",m);
  format.replace("s",s);
  return format;
}

String formatDate(const RtcDateTime& dt, String format){
  String d = dt.Day() < 10 ? "0" + String(dt.Day()) : String(dt.Day()) ;
  String m = dt.Month() < 10 ? "0" + String(dt.Month()) : String(dt.Month()) ;
  String y = String(dt.Year()) ;
  format.replace("d",d);
  format.replace("m",m);
  format.replace("y",y);
  return format;
}
