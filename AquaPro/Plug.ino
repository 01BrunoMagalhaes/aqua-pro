void initializePlugs() {
  pinMode(relay1, OUTPUT); 
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT); 

  turnRelayOff(relay1);
  turnRelayOff(relay2);
  turnRelayOff(relay3);
}

String getRelayStatus(int relayPosition) {
  int s = digitalRead(relayPosition);
  
  return s == 1 ? "OFF" : "ON";
}

void setRelayStatus(int relayPosition) {
  if (getRelayStatus(relayPosition).equals("OFF")) {
    digitalWrite(relayPosition, LOW);  //Liga rele
  } else {
    digitalWrite(relayPosition, HIGH);  //Liga rele
  }
}

void turnRelayOn(int relayPosition) {
  digitalWrite(relayPosition, LOW);
}

void turnRelayOff(int relayPosition) {
  digitalWrite(relayPosition, HIGH);
}
