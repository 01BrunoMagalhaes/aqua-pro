void initializeThreads() {
  displayThread.onRun(displayDataThread); //Atribui função a thread.
  displayThread.setInterval(2000); //Atribui tempo para execução para a Thread.

  waterLevelThread.onRun(verifyWaterLevel);
  waterLevelThread.setInterval(1000);

  tempControlThread.onRun(temperatureControl);
  tempControlThread.setInterval(1000);
}

void threadsControl() {
  if (displayThread.shouldRun()) {
    displayThread.run();  
  }
  
  if (waterLevelThread.shouldRun()) {
    waterLevelThread.run();  
  }

  if (tempControlThread.shouldRun()) {
    tempControlThread.run();  
  }

}
