void initializePlugs() {
  pinMode(relay1, OUTPUT); 
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relayBoia, OUTPUT);

  pinMode(relayHeater, OUTPUT); 
  pinMode(relayCooler, OUTPUT);

  turnRelayOff(relay1);
  turnRelayOff(relay2);
  turnRelayOff(relay3);
  turnRelayOff(relayHeater);
  turnRelayOff(relayCooler);
  turnRelayOff(relayBoia);
}

String getRelayStatus(int relayPosition) {
  int s = digitalRead(relayPosition);
  
  return s == 1 ? "OFF" : "ON";
}

void toggleRelay(int relayPosition) {
  digitalWrite(relayPosition, !digitalRead(relayPosition));
}

void turnRelayOn(int relayPosition) {
  digitalWrite(relayPosition, LOW);
}

void turnRelayOff(int relayPosition) {
  digitalWrite(relayPosition, HIGH);
}
