This is the project of home service robot. It can pickup package and deliver it to drop off zone.

1. pick_objects will send pickup zone and drop off zone as a goal to the robot.
   It will also publish message with topic "reach_pickup_zone" when robot reach the pickup zone;
   and publish message with topic "reach_dropoff_zone" when robot reach drop off zone.
   
   simple_pick_objects will send pickup zone and drop off zone as a goal to the robot. But it dos not publich message.
   It is used for the pick_object.sh only.
   
2. add_markers will draw a cube in the pickup zone first.
   It has callback function "reachPickupZoneCallback" associate with "reach_pickup_zone" message;
          callback function "reachDropOffZoneCallback" associate with "reach_dropoff_zone" message.
   
   simple_marker will initially publish cube at the pickup zone. After 5 seconds the cube should be hidden.
   Then after another 5 seconds it should appear at the drop off zone.
   This node will not subscribe any message.
   It is used for test add_marker.sh only.
   
Scripts added:
1. test_slam.sh: manually test SLAM.
2. test_navigation.sh: manual test navigation.
3. pick_objects.sh: The robot travels to the desired pickup zone,
                    displays a message that it reached its destination,
                    waits 5 seconds, travels to the desired drop off zone,
                    and displays a message that it reached the drop off zone.
4. add_marker.sh: The marker should initially be published at the pickup zone.
                  After 5 seconds it should be hidden.
                  Then after another 5 seconds it should appear at the drop off zone.
5. home_service.sh: Initially show the marker at the pickup zone.
                    Hide the marker once your robot reach the pickup zone.
                    Wait 5 seconds to simulate a pickup.
                    Show the marker at the drop off zone once your robot reaches it.
                  
