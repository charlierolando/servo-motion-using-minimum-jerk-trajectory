#include <DynamixelWorkbench.h>
// p1 or P1 -> Protocol 1.0
// p2 or P2 -> Protocol 2.0

#define CMD_PORT     Serial // Set CMD Port
#define BAUDRATE     1000000  // Set 1Mbps baudrate

#if defined(__OPENCM904__)
#define DEVICE_NAME "1" //Dynamixel on Serial1 <-OpenCM 9.04
#elif defined(__OPENCR__)
#define DEVICE_NAME ""
#endif

#define USING_PROTOCOL_1 false // set off
#define NUMBER_OF_PROTOCOL_1_SERVO 2
const uint8_t p_1_id[NUMBER_OF_PROTOCOL_1_SERVO] = {1, 2}; // {servo_ID_1, servo_ID_2, ...};

#define USING_PROTOCOL_2 true // set on
#define NUMBER_OF_PROTOCOL_2_SERVO 1 // set only 1 servo
const uint8_t p_2_id[NUMBER_OF_PROTOCOL_2_SERVO] = {3}; // set id servo -> 3

#if USING_PROTOCOL_1
DynamixelWorkbench p_1;
int32_t p_1_syncwrite_variable[NUMBER_OF_PROTOCOL_1_SERVO];

#endif

#if USING_PROTOCOL_2
DynamixelWorkbench p_2;
int32_t p_2_syncwrite_variable[NUMBER_OF_PROTOCOL_2_SERVO];

#endif

const uint8_t handler_index = 0;

void setup()
{
  CMD_PORT.begin(BAUDRATE);

  CMD_PORT.println("setup");

#if defined(__OPENCM904__)

#else
  pinMode(BDPIN_BUZZER, OUTPUT); // Set BDPIN_BUZZER - pin 31 as an output
  // beep sound
  tone(BDPIN_BUZZER, 1500); // Send 1.5KHz sound signal...

  digitalWrite(BDPIN_DXL_PWR_EN, HIGH); // set Dxl Power Pin to High // TTL power is on

#endif

  // setup device and baudrate
  setup_dxl_wb();
  // setup syncwrite
  add_goalpos_syncWrite();

  // enable torque all p1 servos
  enable_torque("p_1", true);
  // enable torque all p2 servos
  enable_torque("p_2", true);

  // turn on all p1 led servos
  enable_led("p_1", true);
  // turn on all p2 led servos
  enable_led("p_2", true);

  delay(1000);
  // turn off all p1 and/or p2 led servos
  turn_off_led_all_servo();

  // init pos servo
  p_1_syncwrite_variable[0] = 0; // set the goal position to p_1_id[0]
  do_syncWrite(); // write the goal position for p1 and p2

  // beep sound
  beep();

  CMD_PORT.println("setup done");

}

void loop()
{
  /****************************************************************************/
  // Trajectory for one servo
  // total_time = 2 seconds, dt = 0.01 ms, init_pos = 0, and target_pos = 4095
  /****************************************************************************/
  float total_time = 2; // set total time motion (s)
  float dt = 0.01; // set dt value (ms)

  int init_pos = 0; // init pos value
  int target_pos = 4095; // target pos value

  float t = 0;
  while (t <= total_time)
  {
    p_2_syncwrite_variable[0] = init_pos + (target_pos - init_pos) * (10 * pow((t / total_time), 3) - 15 *  pow((t / total_time), 4) + 6 *  pow((t / total_time), 5));
    do_syncWrite(); // write the goal position for p1 and p2

    delay(int(dt * 1000));

    t = t + dt;
  }


  /****************************************************************************/
  // Trajectory for one servo
  // total_time = 2 seconds, dt = 0.01 ms, init_pos = 4095, and target_pos = 0
  /****************************************************************************/
  total_time = 2; // set total time motion (s)
  dt = 0.01; // set dt value (ms)

  init_pos = 4095; // init pos value
  target_pos = 0; // target pos value

  t = 0;
  while (t <= total_time)
  {
    p_2_syncwrite_variable[0] = init_pos + (target_pos - init_pos) * (10 * pow((t / total_time), 3) - 15 *  pow((t / total_time), 4) + 6 *  pow((t / total_time), 5));
    do_syncWrite(); // write the goal position for p1 and p2

    delay(int(dt * 1000));

    t = t + dt;
  }
}
