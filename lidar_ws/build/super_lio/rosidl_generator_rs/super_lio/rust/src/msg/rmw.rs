#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};


#[link(name = "super_lio__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__super_lio__msg__CloudPose() -> *const std::ffi::c_void;
}

#[link(name = "super_lio__rosidl_generator_c")]
extern "C" {
    fn super_lio__msg__CloudPose__init(msg: *mut CloudPose) -> bool;
    fn super_lio__msg__CloudPose__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<CloudPose>, size: usize) -> bool;
    fn super_lio__msg__CloudPose__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<CloudPose>);
    fn super_lio__msg__CloudPose__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<CloudPose>, out_seq: *mut rosidl_runtime_rs::Sequence<CloudPose>) -> bool;
}

// Corresponds to super_lio__msg__CloudPose
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// CloudPose.msg

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct CloudPose {

    // This member is not documented.
    #[allow(missing_docs)]
    pub pose: geometry_msgs::msg::rmw::Pose,


    // This member is not documented.
    #[allow(missing_docs)]
    pub cloud: sensor_msgs::msg::rmw::PointCloud2,

}



impl Default for CloudPose {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !super_lio__msg__CloudPose__init(&mut msg as *mut _) {
        panic!("Call to super_lio__msg__CloudPose__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for CloudPose {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { super_lio__msg__CloudPose__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { super_lio__msg__CloudPose__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { super_lio__msg__CloudPose__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for CloudPose {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for CloudPose where Self: Sized {
  const TYPE_NAME: &'static str = "super_lio/msg/CloudPose";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__super_lio__msg__CloudPose() }
  }
}


#[link(name = "super_lio__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__super_lio__msg__CloudPose2() -> *const std::ffi::c_void;
}

#[link(name = "super_lio__rosidl_generator_c")]
extern "C" {
    fn super_lio__msg__CloudPose2__init(msg: *mut CloudPose2) -> bool;
    fn super_lio__msg__CloudPose2__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<CloudPose2>, size: usize) -> bool;
    fn super_lio__msg__CloudPose2__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<CloudPose2>);
    fn super_lio__msg__CloudPose2__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<CloudPose2>, out_seq: *mut rosidl_runtime_rs::Sequence<CloudPose2>) -> bool;
}

// Corresponds to super_lio__msg__CloudPose2
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// CloudPose2.msg

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct CloudPose2 {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub pose: rosidl_runtime_rs::Sequence<f32>,

    /// dense point cloud
    pub cloud_lidar: rosidl_runtime_rs::Sequence<f32>,

}



impl Default for CloudPose2 {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !super_lio__msg__CloudPose2__init(&mut msg as *mut _) {
        panic!("Call to super_lio__msg__CloudPose2__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for CloudPose2 {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { super_lio__msg__CloudPose2__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { super_lio__msg__CloudPose2__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { super_lio__msg__CloudPose2__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for CloudPose2 {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for CloudPose2 where Self: Sized {
  const TYPE_NAME: &'static str = "super_lio/msg/CloudPose2";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__super_lio__msg__CloudPose2() }
  }
}


