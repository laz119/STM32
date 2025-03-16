
#include "MyProject.h"


/******************************************************************************/
float shaft_angle;//!< current motor angle
float electrical_angle;
float shaft_velocity;
float current_sp;
float shaft_velocity_sp;
float shaft_angle_sp;
DQVoltage_s voltage;
DQCurrent_s current;

TorqueControlType torque_controller;
MotionControlType controller;

float sensor_offset=0;
float zero_electric_angle;
/******************************************************************************/
// shaft angle calculation 转子角度计算
float shaftAngle(void)
{
  // if no sensor linked return previous value ( for open loop )
  //if(!sensor) return shaft_angle;
  return sensor_direction*getAngle() - sensor_offset;
}
// shaft velocity calculation 转子速度计算
float shaftVelocity(void)
{
  // if no sensor linked return previous value ( for open loop ) 如果没有传感器链接返回前一个值(对于开环)
  //if(!sensor) return shaft_velocity;
  return sensor_direction*LPF_velocity(getVelocity());
}
/******************************************************************************/
float electricalAngle(void)//电角度计算
{
  return _normalizeAngle((shaft_angle + sensor_offset) * pole_pairs - zero_electric_angle);
}
/******************************************************************************/


