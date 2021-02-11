void initializeThreads() {  
  displayThread.onRun(displayDataThread); //Atribui função a thread.
  displayThread.setInterval(1000); //Atribui tempo para execução para a Thread.

  waterLevelThread.onRun(verifyWaterLevel);
  waterLevelThread.setInterval(10);

  tempControlThread.onRun(temperatureControl);
  tempControlThread.setInterval(1000);

  resetProgramThread.onRun(resetProgram);
  resetProgramThread.setInterval(21600000); //6 hours

  threadCtr.add(&displayThread);
  threadCtr.add(&waterLevelThread);
  threadCtr.add(&tempControlThread);
  threadCtr.add(&resetProgramThread);
}

void threadsControl() {
  threadCtr.run();
}
