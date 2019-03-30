//ros libraries
#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "nav_msgs/OccupancyGrid.h"
#include "std_msgs/Int8MultiArray.h"
//c++ libraries
#include <iostream>
#include <vector>
#include <utility>
#include <math.h>

using namespace std;

float map_res = 0.05;//map resolution(m/cell)
const float res = 0.25;          //angular resolution of lidar in degrees
const int num_values = 1080;     //no. of rays emitted by the lidar
const int begin = 180;
const int radius_in_cm = 60;     //radius around on object to be in safe limit for path-planning
const int lane_in_cm = 30;       //radius around lane for path planning
const int side_in_cm = 30;
const int base_lidar_dist = 0;   //distance from vehicle centre to lidar in cm(only in y-direction)

const int cam_lidar_dist = 0;    //distance from camera to lidar in cm
const int width = 28/map_res;//map size
const int height = 16/map_res;
const int range = 16/map_res;//2m in cells
int l_width,l_height;//lane map size          

ros::Publisher map_pub; //blown_map_pub;
std_msgs::Int8MultiArray lane_map;

pair<float,float> convToCart(int i,float r) //convert from polar to cartesian co-ordinates
{  
  
   float ang = i*0.25*(3.14/180);
   float x = r*cos(ang);
   float y = r*sin(ang);
   return make_pair(x,y);
   cout<<"range"<<endl;
}

void laneCallback(nav_msgs::OccupancyGrid msg)
{
   int i,j;
   l_width = msg.info.width;
   l_height = msg.info.height;
   for(i=0;i<l_height;i++)//initialising map
   {
      for(j=0;j<l_width;j++)
      {
         lane_map.data.push_back(0);
      }
   }
   
   for(i=l_height-1;i>=0;i--)//initialising map
   {
      for(j=0;j<l_width;j++)
      {
         int i1;
         i1=l_height-1-i;

         lane_map.data[i1*l_width+j] = msg.data[i*l_width+j];
      }
   }    
}

void lidarCallback(const sensor_msgs::LaserScan::ConstPtr& msg)
{
   
   float radius_in_cells;
   float minor_axis_in_cells = (lane_in_cm*0.01)/map_res;//elliptically blowing lanes
   float major_axis_in_cells = minor_axis_in_cells + 3;
   float base_lidar_dist_in_cells = (base_lidar_dist*0.01)/map_res;
   float base_cam_dist_in_cells = ((cam_lidar_dist - base_lidar_dist)*0.01)/map_res;
   int i,j,k,l;

   nav_msgs::OccupancyGrid grid_map;
   grid_map.header.stamp = ros::Time::now();
   grid_map.header.frame_id = "/base_link";
   grid_map.info.resolution = map_res;
   grid_map.info.origin.position.x = 0.0;
   grid_map.info.origin.position.y = 0.0;
   grid_map.info.origin.position.z = 0.0;
   grid_map.info.origin.orientation.x = 0.0;
   grid_map.info.origin.orientation.y = 0.0;
   grid_map.info.origin.orientation.z = 0.0;
   grid_map.info.origin.orientation.w = 1.0;
   grid_map.info.width = width;
   grid_map.info.height = height;
   grid_map.info.map_load_time = ros::Time::now();

   vector< pair<float,float> > cartesian(num_values,make_pair(0,0));
   for(i= 0;i<(num_values);i++)
   { 
     
      cartesian[i] = convToCart((i-num_values/2),msg->ranges[i]);

   }

  
   for(i=0;i<height;i++)//initialising map
   {
      for(j=0;j<width;j++)
      {
         grid_map.data.push_back(0);
      }
   }
   int counter = 0;
   for(int i = begin;i < (num_values - begin); i++) 
   {
      int x_coord = round(cartesian[i].first/map_res);
      int y_coord = round(cartesian[i].second/map_res);
      

      if(y_coord > -range && y_coord <= range)//limiting obstacle detection to only 20m
      {
         if(x_coord <= range && x_coord >= 0)
         {
            cout<<((i-num_values/2)*0.25)<<"  "<<x_coord<<" "<<y_coord<<endl;
	     	counter++;
                grid_map.data[x_coord*width+y_coord+width/2] = 1;
         }
      } 
    
   }
   cout<<"counter"<<counter<<endl;
   int size = sizeof(grid_map.data);
   
   map_pub.publish(grid_map);
   grid_map.data.clear();
}

int main(int argc,char** argv)
{
   ros::init(argc,argv,"local_map2");
   ros::NodeHandle n,n1,n2,n3;
   ros::Subscriber lane_sub=n.subscribe<nav_msgs::OccupancyGrid>("/Lane_Occupancy_Grid",1,laneCallback);
   ros::Subscriber lidar_sub=n1.subscribe<sensor_msgs::LaserScan>("/scan",1,lidarCallback);
   map_pub=n2.advertise<nav_msgs::OccupancyGrid>("scan/local_map_2",1);

   ros::Rate loop_rate(15.0);

   while(ros::ok())
   {
     ros::spinOnce();//check for incoming messages
     loop_rate.sleep(); 
   }
   return 0; 
}
