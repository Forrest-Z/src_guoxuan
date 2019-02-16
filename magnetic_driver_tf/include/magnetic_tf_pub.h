#ifndef MAGNETIC_TF_PUB
#define MAGNETIC_TF_PUB

#include <ros/ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int32MultiArray.h>
#include <geometry_msgs/Pose2D.h>
#include <nav_msgs/Odometry.h>

class MagneticTfPub
{
  private:
    ros::NodeHandle nh_;
    ros::Subscriber task_switch_sub_;
    ros::Subscriber magnetic_head_sub_;
    ros::Subscriber magnetic_tail_sub_;
    ros::Subscriber odom_sub_;

    ros::Publisher task_finished_pub_;

    double fake_pose_y_out_track_cm_;
    double param_test_;

    bool magnetic_head_is_forward_;
    bool magnetic_tail_is_forward_;

    bool run_task_;
    bool head_detected_magnetic_;
    bool tail_detected_magnetic_;
    bool need_recod_marker_pose_in_odom_;
    bool count_detected_tail_marker_;
    bool count_detected_head_marker_;
    bool can_detected_tail_marker_;
    bool can_detected_head_marker_;

    bool need_set_bzp_max_vel_x_;

    int signal_for_head_out_track_;
    int signal_for_tail_out_track_;
    int detected_tail_marker_times_;
    int detected_head_marker_times_;

    int points_num_consider_detected_magnetic_marker_;

    enum head_or_tail
    {
        NON,
        HEAD,
        TAIL
    };

    head_or_tail head_or_tail_;

    geometry_msgs::Pose2D magnetic_head_pose2d_;
    geometry_msgs::Pose2D magnetic_tail_pose2d_;
    geometry_msgs::Pose2D magnetic_marker_pose2d_;

    geometry_msgs::Pose2D odometry_marker_start_;
    geometry_msgs::Pose2D odometry_marker_end_;
    bool get_marker_middle_pose_;

    nav_msgs::Odometry odometry_recoder_;
    bool output_odometry_from_marker_;

    void TaskSwitchCallback(const std_msgs::HeaderPtr &task_switch_msg);
    void MagneticHeadCallback(const std_msgs::Int32MultiArrayPtr magnetic_head_msg);
    void MagneticTailCallback(const std_msgs::Int32MultiArrayPtr magnetic_tail_msg);
    void OdomCallback(const nav_msgs::OdometryConstPtr odometry_msg);

    void CmdVelPub( double linear, double angular );
    void SendTransform( double x, double y, double theta );
    void GetMagneticPoseInRobot(double& magnetic_tf_x, double& magnetic_tf_y, double& magnetic_tf_theta);
    double GetMarkerInOdometryDiff();

    double GetPoseYInRobotBase(bool magnetic_is_forward, const std_msgs::Int32MultiArrayPtr magnetic_tail_msg, int get_signal, int& num_detected_magnetic);
    double FakeYForControl(double magnetic_y_cm);
    void ResetParam();
    void StopRun();

  public:
    MagneticTfPub();
    ~MagneticTfPub();

    void Run();
};

#endif