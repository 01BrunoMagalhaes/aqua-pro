void verifyWaterLevel() {
  if (digitalRead(waterSensor) == HIGH) {
    turnRelayOn(relayBoia);
    if(DEBUG) Serial.println(F("Water sensor level on"));
  } else {
    turnRelayOff(relayBoia);
    if(DEBUG) Serial.println(F("Water sensor level off"));
  }
}
