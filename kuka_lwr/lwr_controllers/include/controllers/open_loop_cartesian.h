#ifndef OPEN_LOOP_CARTESIAN_H_
#define OPEN_LOOP_CARTESIAN_H_

#include <ros/ros.h>
#include <kdl/jntarray.hpp>
#include <kdl/chainiksolvervel_pinv.hpp>

#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose.h>

#include <tf/LinearMath/Matrix3x3.h>
#include <tf/LinearMath/Vector3.h>

#include "utils/definitions.h"
#include "controllers/change_ctrl_mode.h"
#include "base_controllers.h"


namespace controllers
{

class Cartesian_velocity : public Base_controllers {

public:

    enum class CART_TYPE
    {
        VELOCITY_OPEN_LOOP=0,
        VELOCITY_PASSIVE_DS=1
    };

public:

    Cartesian_velocity(ros::NodeHandle &nh,
                        controllers::Change_ctrl_mode& change_ctrl_mode,
                        boost::shared_ptr<KDL::ChainIkSolverVel_pinv>& ik_vel_solver);

    void cart_vel_update(KDL::JntArray& tau_cmd,
                KDL::JntArrayAcc& joint_des,
                const KDL::JntArrayAcc& q_msr,
                const KDL::JntArray& K,
                const KDL::JntArray& D,
                const ros::Duration& period);

    void stop();

private:

    void command_cart_vel(const geometry_msgs::TwistConstPtr& msg);

    void command_orient(const geometry_msgs::Quaternion &msg);

private:

    Change_ctrl_mode &change_ctrl_mode;

    ros::Subscriber     sub_command_vel_;
    ros::Subscriber     sub_command_orient_;

    tf::Quaternion      x_des_orient_;
    tf::Matrix3x3       x_des_orient_rot_;
    tf::Matrix3x3       x_orient_;
    double              rot_stiffness;
    bool                bFirst;

    boost::shared_ptr<KDL::ChainIkSolverVel_pinv>       ik_vel_solver_;
    KDL::Twist                                          x_des_vel_;

};

}


#endif
