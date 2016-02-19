// -*- c++-mode -*-
#ifndef POSE_WITH_COVARIANCE_DISPLAY_H
#define POSE_WITH_COVARIANCE_DISPLAY_H

#include <boost/shared_ptr.hpp>

#include <geometry_msgs/PoseWithCovarianceStamped.h>

#include <rviz/message_filter_display.h>
#include <rviz/selection/forwards.h>

namespace rviz
{
class Arrow;
class Axes;
class ColorProperty;
class EnumProperty;
class FloatProperty;
class BoolProperty;
class Shape;
}

namespace rviz_plugin_covariance
{

class CovarianceVisual;

class PoseWithCovarianceDisplaySelectionHandler;
typedef boost::shared_ptr<PoseWithCovarianceDisplaySelectionHandler> PoseWithCovarianceDisplaySelectionHandlerPtr;

/** @brief Accumulates and displays the pose from a geometry_msgs::PoseWithCovarianceStamped message. */
class PoseWithCovarianceDisplay: public rviz::MessageFilterDisplay<geometry_msgs::PoseWithCovarianceStamped>
{
Q_OBJECT
public:
  enum Shape
  {
    Arrow,
    Axes,
  };

  PoseWithCovarianceDisplay();
  virtual ~PoseWithCovarianceDisplay();

  virtual void onInitialize();
  virtual void reset();

protected:
  /** @brief Overridden from MessageFilterDisplay to get Arrow/Axes visibility correct. */
  virtual void onEnable();

private Q_SLOTS:
  void updateShapeVisibility();
  void updateColorAndAlpha();
  void updateShapeChoice();
  void updateAxisGeometry();
  void updateArrowGeometry();
  void updateCovarianceChoice();
  void updateCovarianceColorAndAlphaAndScale();

private:
  void clear();

  virtual void processMessage( const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& message );
  void setCovarianceNodes(const geometry_msgs::PoseWithCovariance& msg);

  rviz::Arrow* arrow_;
  rviz::Axes* axes_;
  rviz::Shape* covariance_position_shape_;
  rviz::Shape* covariance_orientation_shape_;
  bool pose_valid_;
  bool covariance_valid_;
  PoseWithCovarianceDisplaySelectionHandlerPtr coll_handler_;

  rviz::EnumProperty* shape_property_;

  rviz::ColorProperty* color_property_;
  rviz::FloatProperty* alpha_property_;

  rviz::FloatProperty* head_radius_property_;
  rviz::FloatProperty* head_length_property_;
  rviz::FloatProperty* shaft_radius_property_;
  rviz::FloatProperty* shaft_length_property_;

  rviz::FloatProperty* axes_length_property_;
  rviz::FloatProperty* axes_radius_property_;

  rviz::BoolProperty* covariance_property_;
  rviz::ColorProperty* covariance_position_color_property_;
  rviz::FloatProperty* covariance_position_alpha_property_;
  rviz::FloatProperty* covariance_position_scale_property_;
  rviz::ColorProperty* covariance_orientation_color_property_;
  rviz::FloatProperty* covariance_orientation_alpha_property_;
  rviz::FloatProperty* covariance_orientation_scale_property_;

  float covariance_position_scale_;
  float covariance_orientation_scale_;

  Ogre::SceneNode* covariance_position_node_;
  Ogre::SceneNode* covariance_orientation_node_;

  friend class PoseWithCovarianceDisplaySelectionHandler;
};

} // namespace rviz_plugin_covariance

#endif // POSE_WITH_COVARIANCE_DISPLAY_H
