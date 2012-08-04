/*********************************************************************
* Software License Agreement (BSD License)
*
*  Copyright (c) 2012, Willow Garage, Inc.
*  All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*   * Neither the name of Willow Garage, Inc. nor the names of its
*     contributors may be used to endorse or promote products derived
*     from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
*  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
*  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
*  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
*  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
*  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
*********************************************************************/

/*------------------------------------------------------*/
/*   DO NOT INCLUDE THIS FILE DIRECTLY                  */
/*------------------------------------------------------*/

/** @brief The state corresponding to a link */
class LinkState
{
  friend class KinematicState;
public:
  
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW
  
  /** @brief Constructor */
  LinkState(KinematicState *state, const KinematicModel::LinkModel* lm);
  ~LinkState(void);
  
  /** @brief Get the name of link corresponding to this state */
  const std::string& getName(void) const
  {
    return link_model_->getName();
  }
  
  /** @brief Get the kinematic state that this link state is part of*/
  const KinematicState* getKinematicState(void) const
  {
    return kinematic_state_;
  }
  
  /** @brief Get the kinematic state that this link state is part of*/
  KinematicState* getKinematicState(void)
  {
    return kinematic_state_;
  }
  
  /** @brief Set the link state to the input transform */
  void updateGivenGlobalLinkTransform(const Eigen::Affine3d& transform);
  
  /** \brief Recompute global_collision_body_transform and global_link_transform */
  void computeTransform(void);
  
  /** \brief Update all attached bodies given set link transforms */
  void updateAttachedBodies(void);
  
  /** @brief Get the link model corresponding to this state */
  const KinematicModel::LinkModel* getLinkModel(void) const
  {
    return link_model_;
  }
  
  /** @brief Get the joint state corresponding to the parent joint of this link */
  const JointState* getParentJointState(void) const
  {
    return parent_joint_state_;
  }
  
  /** @brief Get the link state corresponding to the parent link of this link */
  const LinkState* getParentLinkState(void) const
  {
    return parent_link_state_;
  }
  
  /** @brief Get all the bodies attached to this link */
  void getAttachedBodies(std::vector<const AttachedBody*> &attached_bodies) const;
  
  /** @brief Get the attached body with name \e id */
  const AttachedBody* getAttachedBody(const std::string &id) const;
  
  /** \brief Check if an attached body named \e id exists in this group */
  bool hasAttachedBody(const std::string &id) const;
  
  /** @brief Get the global transform for this link */
  const Eigen::Affine3d& getGlobalLinkTransform(void) const
  {
    return global_link_transform_;
  }
  
  /** @brief Get the global transform for the collision body associated with this link */
  const Eigen::Affine3d& getGlobalCollisionBodyTransform(void) const
  {
    return global_collision_body_transform_;
  }
  
  /**
     @brief Attach a body to this link
     @param id The string id associated with the attached body
     @param shapes The shapes that make up the attached body
     @param attach_trans The desired transform between this link and the attached body
     @param touch_links The set of links that the attached body is allowed to touch
  */
  void attachBody(const std::string &id,
                  const std::vector<shapes::ShapeConstPtr> &shapes,
                  const std::vector<Eigen::Affine3d> &attach_trans,
                  const std::vector<std::string> &touch_links);
  
  /**
     @brief Clear the attached body
     @param id The name of the attached body to clear
  */
  bool clearAttachedBody(const std::string &id);
  
  /** @brief Clear all attached bodies */
  void clearAttachedBodies(void);
  
private:
  
  /** \brief The kinematic state this link is part of */
  KinematicState                      *kinematic_state_;
  
  const KinematicModel::LinkModel     *link_model_;
  
  const JointState                    *parent_joint_state_;
  
  const LinkState                     *parent_link_state_;
  
  std::map<std::string, AttachedBody*> attached_body_map_;
  
  /** \brief The global transform this link forwards (computed by forward kinematics) */
  Eigen::Affine3d                      global_link_transform_;
  
  /** \brief The global transform for this link (computed by forward kinematics) */
  Eigen::Affine3d                      global_collision_body_transform_;
};
