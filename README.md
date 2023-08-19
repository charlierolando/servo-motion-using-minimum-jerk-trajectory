# servo-motion-using-minimum-jerk-trajectory

>See [multi-protocol-dynamixel-servos](https://github.com/charlierolando/multi-protocol-dynamixel-servos/tree/main/)

![Result](https://github.com/charlierolando/servo-motion-using-minimum-jerk-trajectory/blob/main/images/images1.gif)

>klik [this](https://github.com/charlierolando/servo-motion-using-minimum-jerk-trajectory/blob/main/images/images1.gif) when the image doesn't appear

## [Code:](#code)

>klik [this](https://github.com/charlierolando/servo-motion-using-minimum-jerk-trajectory/blob/master/source/servo-motion-using-minimum-jerk-trajectory/servo-motion-using-minimum-jerk-trajectory.ino) to see the full code

```cpp title="editt.cpp"
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
```

## [References:](#references)

[ekorudiawan/Minimum-Jerk-Trajectory](https://github.com/ekorudiawan/Minimum-Jerk-Trajectory/tree/master)
