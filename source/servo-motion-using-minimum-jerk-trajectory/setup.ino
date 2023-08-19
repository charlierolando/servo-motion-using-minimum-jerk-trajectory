void ping_servo(String DXL_MODEL, uint8_t DXL_ID)
{
  const char *log;

  uint16_t model_number = 0;
  bool result = false;

#if USING_PROTOCOL_1
  if (DXL_MODEL == "p_1")
  {
    result = p_1.ping(DXL_ID, &model_number, &log);
    if (result == false)
    {
      CMD_PORT.println(log);
      CMD_PORT.println("Failed to ping, id: ");
      CMD_PORT.print(DXL_ID);
      CMD_PORT.println("\n");
    }
    else
    {
      CMD_PORT.println("Succeeded to ping");
      CMD_PORT.print("\nid : ");
      CMD_PORT.print(DXL_ID);
      CMD_PORT.print(" model_number : ");
      CMD_PORT.println(model_number);

      p_1.itemWrite(DXL_ID, "LED", 1, &log);
      CMD_PORT.println("Dynamixel Protocol 1 has been successfully connected \n");
    }
    
    result = p_1.jointMode(DXL_ID, 0, 0, &log);
    if (result == false)
    {
      Serial.println(log);
      Serial.println("Failed to change joint mode");
    }
    else
    {
      Serial.println("Succeed to change joint mode");
    }
  }

#endif

#if USING_PROTOCOL_2
#if USING_PROTOCOL_1 && USING_PROTOCOL_2
  else if (DXL_MODEL == "p_2")

#else
  if (DXL_MODEL == "p_2")

#endif

  {
    result = p_2.ping(DXL_ID, &model_number, &log);
    if (result == false)
    {
      CMD_PORT.println(log);
      CMD_PORT.println("Failed to ping, id: ");
      CMD_PORT.print(DXL_ID);
      CMD_PORT.println("\n");
    }
    else
    {
      CMD_PORT.println("Succeeded to ping");
      CMD_PORT.print("\nid : ");
      CMD_PORT.print(DXL_ID);
      CMD_PORT.print(" model_number : ");
      CMD_PORT.println(model_number);

      p_2.itemWrite(DXL_ID, "LED", 1, &log);
      CMD_PORT.println("Dynamixel Protocol 2 has been successfully connected \n");
    }
    
    result = p_2.jointMode(DXL_ID, 0, 0, &log);
    if (result == false)
    {
      Serial.println(log);
      Serial.println("Failed to change joint mode");
    }
    else
    {
      Serial.println("Succeed to change joint mode");
    }
  }

#endif

}

void setup_dxl_wb()
{
  const char *log;

#if USING_PROTOCOL_1
  p_1.init(DEVICE_NAME, BAUDRATE, &log);

#endif

#if USING_PROTOCOL_2
  p_2.init(DEVICE_NAME, BAUDRATE, &log);

#endif

  // ping servos
#if USING_PROTOCOL_1
  for (int i = 0; i < (sizeof(p_1_id) / sizeof(p_1_id[0])); i++)
    ping_servo("p_1", p_1_id[i]);

#endif

  // ping servos
#if USING_PROTOCOL_2
  for (int i = 0; i < (sizeof(p_2_id) / sizeof(p_2_id[0])); i++)
    ping_servo("p_2", p_2_id[i]);

#endif

}

void add_goalpos_syncWrite()
{
  const char *log;
  bool result = false;

#if USING_PROTOCOL_1
  result = p_1.addSyncWriteHandler(p_1_id[0], "Goal_Position", &log);
  if (result == false)
  {
    CMD_PORT.println(log);
    CMD_PORT.println("Failed to add sync write handler - P1");
  }
  else
  {
    CMD_PORT.println("Succeed to add sync write handler - P1");
  }

#endif

#if USING_PROTOCOL_2
  result = p_2.addSyncWriteHandler(p_2_id[0], "Goal_Position", &log);
  if (result == false)
  {
    CMD_PORT.println(log);
    CMD_PORT.println("Failed to add sync write handler - P2");
  }
  else
  {
    CMD_PORT.println("Succeed to add sync write handler - P2");
  }

#endif

}

void do_syncWrite()
{
  const char *log;

#if USING_PROTOCOL_1
  p_1.syncWrite(handler_index, &p_1_syncwrite_variable[0], &log);

#endif

#if USING_PROTOCOL_2
  p_2.syncWrite(handler_index, &p_2_syncwrite_variable[0], &log);

#endif

}

void add_pos_syncRead()
{
  const char *log;
  bool result = false;

#if USING_PROTOCOL_1
  result = p_1.addSyncReadHandler(p_1_id[0], "Present_Position", &log);
  if (result == false)
  {
    CMD_PORT.println(log);
    CMD_PORT.println("Failed to add sync read handler - P1");
  }
  else
  {
    CMD_PORT.println("Succeed to add sync read handler - P1");
  }

#endif

#if USING_PROTOCOL_2
  result = p_2.addSyncReadHandler(p_2_id[0], "Present_Position", &log);
  if (result == false)
  {
    CMD_PORT.println(log);
    CMD_PORT.println("Failed to add sync read handler - P2");
  }
  else
  {
    CMD_PORT.println("Succeed to add sync read handler - P2");
  }

#endif

}

void enable_torque(String DXL_MODEL, bool TORQUE)
{
  const char *log;

  if (DXL_MODEL == "p_1")
  {
#if USING_PROTOCOL_1
    CMD_PORT.println("Enable-Disable Dynamixel P1 torque");

    if (TORQUE == 1)
    {
      // Enable Dynamixel P1 torque
      for (int i = 0; i < (sizeof(p_1_id) / sizeof(p_1_id[0])); i++)
        p_1.torqueOn(p_1_id[i], &log);
    }
    else if (TORQUE == 0)
    {
      // Disable Dynamixel P1 torque
      for (int i = 0; i < (sizeof(p_1_id) / sizeof(p_1_id[0])); i++)
        p_1.torqueOff(p_1_id[i], &log);
    }

    CMD_PORT.println("Enable-Disable Dynamixel P1 torque done");

#endif
  }

  else if (DXL_MODEL == "p_2")
  {
#if USING_PROTOCOL_2
    CMD_PORT.println("Enable-Disable Dynamixel P2 torque");

    if (TORQUE == 1)
    {
      // Enable Dynamixel P2 torque
      for (int i = 0; i < (sizeof(p_2_id) / sizeof(p_2_id[0])); i++)
        p_2.torqueOn(p_2_id[i], &log);
    }
    else if (TORQUE == 0)
    {
      // Disable Dynamixel P2 torque
      for (int i = 0; i < (sizeof(p_2_id) / sizeof(p_2_id[0])); i++)
        p_2.torqueOff(p_2_id[i], &log);
    }

    CMD_PORT.println("Enable-Disable Dynamixel P2 torque done");

#endif
  }
}

void enable_led(String DXL_MODEL, uint8_t myLED)
{
  const char *log;

  if (DXL_MODEL == "p_1")
  {
#if USING_PROTOCOL_1
    CMD_PORT.println("Enable-Disable Dynamixel P1 LED");

    for (int i = 0; i < (sizeof(p_1_id) / sizeof(p_1_id[0])); i++)
      p_1.itemWrite(p_1_id[i], "LED", myLED, &log);

    CMD_PORT.println("Enable-Disable Dynamixel P1 LED done");

#endif
  }

  else if (DXL_MODEL == "p_2")
  {
#if USING_PROTOCOL_2
    CMD_PORT.println("Enable-Disable Dynamixel P2 LED");

    for (int i = 0; i < (sizeof(p_2_id) / sizeof(p_2_id[0])); i++)
      p_2.itemWrite(p_2_id[i], "LED", myLED, &log);

    CMD_PORT.println("Enable-Disable Dynamixel P2 LED done");

#endif
  }
}

void turn_off_led_all_servo()
{
  enable_led("p_1", false);
  enable_led("p_2", false);
}

void p_1_velocity(int32_t velocity)
{
#if USING_PROTOCOL_1
  CMD_PORT.println("Set Dynamixel P1 Velocity");

  for (int i = 0; i < (sizeof(p_1_id) / sizeof(p_1_id[0])); i++)
    p_1.goalVelocity(p_1_id[i], (int32_t) velocity);

  CMD_PORT.println("Set Dynamixel P1 Velocity done");

#endif

}

void p_2_velocity(int32_t velocity)
{
#if USING_PROTOCOL_2
  CMD_PORT.println("Set Dynamixel P2 Velocity");

  for (int i = 0; i < (sizeof(p_2_id) / sizeof(p_2_id[0])); i++)
    p_2.goalVelocity(p_2_id[i], (int32_t) velocity);

  CMD_PORT.println("Set Dynamixel P2 Velocity done");

#endif

}

////////***************************// BEEP ////////***************************/////

void beep()
{
#if defined(__OPENCM904__)

#else
  tone(BDPIN_BUZZER, 500); // Send 0.5KHz sound signal...
  delay(125);        // ...for 0.125 sec
  tone(BDPIN_BUZZER, 1000); // Send 1KHz sound signal...
  delay(125);        // ...for 0.125 sec
  tone(BDPIN_BUZZER, 1500); // Send 1.5KHz sound signal...
  delay(125);        // ...for 0.125 sec
  tone(BDPIN_BUZZER, 500); // Send 0.5KHz sound signal...
  delay(125);        // ...for 0.125 sec
  noTone(BDPIN_BUZZER);     // Stop sound...

#endif
}

////////***************************// BEEP ////////***************************/////
