void initializeTemp() {
  sensors.begin();

  if (DEBUG) {
    Serial.println(F("Searching for sensor DS18B20..."));
    Serial.print(F("Found "));
    Serial.print(sensors.getDeviceCount(), DEC);
    Serial.println(" sensor");
  }
  
  if (!sensors.getAddress(sensor1, 0)) 
     Serial.println(F("Sensor not found"));

  if (DEBUG)
    sensorAddress(sensor1);
}

void sensorAddress(DeviceAddress deviceAddress) {
  Serial.print(F("Sensor address: "));
  for (uint8_t i = 0; i < 8; i++) {
    // Adiciona zeros se necessário
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
  Serial.println();
}

float temp() {
  sensors.requestTemperatures();
  return sensors.getTempC(sensor1);  
}

void temperatureControl() {
  float temperature = temp();
  if(temperature > 5 && temperature < 50) {
    if (temperature >= tMax && temperature > tIdeal) {
      if(DEBUG) Serial.println(F("Turning coolet on")); 
      turnRelayOff(relayHeater);
      turnRelayOn(relayCooler);
    } else if (temperature <= tMin && temperature < tIdeal) {
      if(DEBUG) Serial.println(F("Turning heater on"));
      turnRelayOn(relayHeater);
      turnRelayOff(relayCooler);
    } else {
      if(DEBUG) Serial.println(F("Ideal temp"));
      turnRelayOff(relayHeater);
      turnRelayOff(relayCooler);
    } 
  } else {
    turnRelayOff(relayHeater);
    turnRelayOff(relayCooler);
  }
}
