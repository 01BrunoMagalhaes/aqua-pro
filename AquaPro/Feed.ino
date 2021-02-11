void initializeFeed() {
  servoFeed.attach(SERVO_FEED_PORT);
  servoFeed.write(0);
}

void feed(int times_to_feed) {
  int times_feeded = 0;

  Serial.println("Starting feeding for " + String(times_to_feed) + " times");
  
  while (times_feeded < times_to_feed) {
    servoFeed.write(0);
    servoFeed.write(80);
    Serial.println("Feed number " + String(times_feeded + 1));
    for (int i = 90; i <= 170; i+=5) {
      // Serial.println(i);
      servoFeed.write(i);
      delay(70);
    }
    
    servoFeed.write(0);
    times_feeded++;
    if (times_feeded != times_to_feed) {
      delay(8000);  
    }    
  }
  Serial.println("Finished feed time");
}
