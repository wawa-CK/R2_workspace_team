#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



#[link(name = "odin_ros_driver__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__odin_ros_driver__srv__GetAe_Request() -> *const std::ffi::c_void;
}

#[link(name = "odin_ros_driver__rosidl_generator_c")]
extern "C" {
    fn odin_ros_driver__srv__GetAe_Request__init(msg: *mut GetAe_Request) -> bool;
    fn odin_ros_driver__srv__GetAe_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<GetAe_Request>, size: usize) -> bool;
    fn odin_ros_driver__srv__GetAe_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<GetAe_Request>);
    fn odin_ros_driver__srv__GetAe_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<GetAe_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<GetAe_Request>) -> bool;
}

// Corresponds to odin_ros_driver__srv__GetAe_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GetAe_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub structure_needs_at_least_one_member: u8,

}



impl Default for GetAe_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !odin_ros_driver__srv__GetAe_Request__init(&mut msg as *mut _) {
        panic!("Call to odin_ros_driver__srv__GetAe_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for GetAe_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { odin_ros_driver__srv__GetAe_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { odin_ros_driver__srv__GetAe_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { odin_ros_driver__srv__GetAe_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for GetAe_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for GetAe_Request where Self: Sized {
  const TYPE_NAME: &'static str = "odin_ros_driver/srv/GetAe_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__odin_ros_driver__srv__GetAe_Request() }
  }
}


#[link(name = "odin_ros_driver__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__odin_ros_driver__srv__GetAe_Response() -> *const std::ffi::c_void;
}

#[link(name = "odin_ros_driver__rosidl_generator_c")]
extern "C" {
    fn odin_ros_driver__srv__GetAe_Response__init(msg: *mut GetAe_Response) -> bool;
    fn odin_ros_driver__srv__GetAe_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<GetAe_Response>, size: usize) -> bool;
    fn odin_ros_driver__srv__GetAe_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<GetAe_Response>);
    fn odin_ros_driver__srv__GetAe_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<GetAe_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<GetAe_Response>) -> bool;
}

// Corresponds to odin_ros_driver__srv__GetAe_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GetAe_Response {
    /// true if rc == 0
    pub success: bool,

    /// 0=ok, >0=device error (400..405 or 0xFF), <0=SDK error
    pub rc: i32,

    /// seconds (manual range 0.0001 .. 0.033)
    pub exposure_time: f32,

    /// analog gain
    pub gain: f32,

    /// equivalent ISO
    pub iso: i32,

    /// average frame brightness
    pub brightness: f32,

    /// 1=converged, 0=not converged
    pub is_converged: u8,

    /// ambient luminance level
    pub env_lv: f32,

    /// current frame rate
    pub fps: f32,

}



impl Default for GetAe_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !odin_ros_driver__srv__GetAe_Response__init(&mut msg as *mut _) {
        panic!("Call to odin_ros_driver__srv__GetAe_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for GetAe_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { odin_ros_driver__srv__GetAe_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { odin_ros_driver__srv__GetAe_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { odin_ros_driver__srv__GetAe_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for GetAe_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for GetAe_Response where Self: Sized {
  const TYPE_NAME: &'static str = "odin_ros_driver/srv/GetAe_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__odin_ros_driver__srv__GetAe_Response() }
  }
}


#[link(name = "odin_ros_driver__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__odin_ros_driver__srv__GetAwb_Request() -> *const std::ffi::c_void;
}

#[link(name = "odin_ros_driver__rosidl_generator_c")]
extern "C" {
    fn odin_ros_driver__srv__GetAwb_Request__init(msg: *mut GetAwb_Request) -> bool;
    fn odin_ros_driver__srv__GetAwb_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<GetAwb_Request>, size: usize) -> bool;
    fn odin_ros_driver__srv__GetAwb_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<GetAwb_Request>);
    fn odin_ros_driver__srv__GetAwb_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<GetAwb_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<GetAwb_Request>) -> bool;
}

// Corresponds to odin_ros_driver__srv__GetAwb_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GetAwb_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub structure_needs_at_least_one_member: u8,

}



impl Default for GetAwb_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !odin_ros_driver__srv__GetAwb_Request__init(&mut msg as *mut _) {
        panic!("Call to odin_ros_driver__srv__GetAwb_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for GetAwb_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { odin_ros_driver__srv__GetAwb_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { odin_ros_driver__srv__GetAwb_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { odin_ros_driver__srv__GetAwb_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for GetAwb_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for GetAwb_Request where Self: Sized {
  const TYPE_NAME: &'static str = "odin_ros_driver/srv/GetAwb_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__odin_ros_driver__srv__GetAwb_Request() }
  }
}


#[link(name = "odin_ros_driver__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__odin_ros_driver__srv__GetAwb_Response() -> *const std::ffi::c_void;
}

#[link(name = "odin_ros_driver__rosidl_generator_c")]
extern "C" {
    fn odin_ros_driver__srv__GetAwb_Response__init(msg: *mut GetAwb_Response) -> bool;
    fn odin_ros_driver__srv__GetAwb_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<GetAwb_Response>, size: usize) -> bool;
    fn odin_ros_driver__srv__GetAwb_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<GetAwb_Response>);
    fn odin_ros_driver__srv__GetAwb_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<GetAwb_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<GetAwb_Response>) -> bool;
}

// Corresponds to odin_ros_driver__srv__GetAwb_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GetAwb_Response {
    /// true if rc == 0
    pub success: bool,

    /// 0=ok, >0=device error (400..405 or 0xFF), <0=SDK error
    pub rc: i32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub rgain: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub grgain: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub gbgain: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub bgain: f32,

    /// color temperature in Kelvin
    pub cct: f32,

    /// color temperature deviation
    pub ccri: f32,

    /// 1=converged, 0=not converged
    pub is_converged: u8,

}



impl Default for GetAwb_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !odin_ros_driver__srv__GetAwb_Response__init(&mut msg as *mut _) {
        panic!("Call to odin_ros_driver__srv__GetAwb_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for GetAwb_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { odin_ros_driver__srv__GetAwb_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { odin_ros_driver__srv__GetAwb_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { odin_ros_driver__srv__GetAwb_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for GetAwb_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for GetAwb_Response where Self: Sized {
  const TYPE_NAME: &'static str = "odin_ros_driver/srv/GetAwb_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__odin_ros_driver__srv__GetAwb_Response() }
  }
}


#[link(name = "odin_ros_driver__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__odin_ros_driver__srv__SetAe_Request() -> *const std::ffi::c_void;
}

#[link(name = "odin_ros_driver__rosidl_generator_c")]
extern "C" {
    fn odin_ros_driver__srv__SetAe_Request__init(msg: *mut SetAe_Request) -> bool;
    fn odin_ros_driver__srv__SetAe_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<SetAe_Request>, size: usize) -> bool;
    fn odin_ros_driver__srv__SetAe_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<SetAe_Request>);
    fn odin_ros_driver__srv__SetAe_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<SetAe_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<SetAe_Request>) -> bool;
}

// Corresponds to odin_ros_driver__srv__SetAe_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SetAe_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub mode: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub exposure_time: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub gain: f32,

}



impl Default for SetAe_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !odin_ros_driver__srv__SetAe_Request__init(&mut msg as *mut _) {
        panic!("Call to odin_ros_driver__srv__SetAe_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for SetAe_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { odin_ros_driver__srv__SetAe_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { odin_ros_driver__srv__SetAe_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { odin_ros_driver__srv__SetAe_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for SetAe_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for SetAe_Request where Self: Sized {
  const TYPE_NAME: &'static str = "odin_ros_driver/srv/SetAe_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__odin_ros_driver__srv__SetAe_Request() }
  }
}


#[link(name = "odin_ros_driver__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__odin_ros_driver__srv__SetAe_Response() -> *const std::ffi::c_void;
}

#[link(name = "odin_ros_driver__rosidl_generator_c")]
extern "C" {
    fn odin_ros_driver__srv__SetAe_Response__init(msg: *mut SetAe_Response) -> bool;
    fn odin_ros_driver__srv__SetAe_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<SetAe_Response>, size: usize) -> bool;
    fn odin_ros_driver__srv__SetAe_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<SetAe_Response>);
    fn odin_ros_driver__srv__SetAe_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<SetAe_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<SetAe_Response>) -> bool;
}

// Corresponds to odin_ros_driver__srv__SetAe_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SetAe_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,

    /// 0=ok, >0=device error (400..405 or 0xFF), <0=SDK error
    pub rc: i32,

}



impl Default for SetAe_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !odin_ros_driver__srv__SetAe_Response__init(&mut msg as *mut _) {
        panic!("Call to odin_ros_driver__srv__SetAe_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for SetAe_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { odin_ros_driver__srv__SetAe_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { odin_ros_driver__srv__SetAe_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { odin_ros_driver__srv__SetAe_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for SetAe_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for SetAe_Response where Self: Sized {
  const TYPE_NAME: &'static str = "odin_ros_driver/srv/SetAe_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__odin_ros_driver__srv__SetAe_Response() }
  }
}


#[link(name = "odin_ros_driver__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__odin_ros_driver__srv__SetAwb_Request() -> *const std::ffi::c_void;
}

#[link(name = "odin_ros_driver__rosidl_generator_c")]
extern "C" {
    fn odin_ros_driver__srv__SetAwb_Request__init(msg: *mut SetAwb_Request) -> bool;
    fn odin_ros_driver__srv__SetAwb_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<SetAwb_Request>, size: usize) -> bool;
    fn odin_ros_driver__srv__SetAwb_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<SetAwb_Request>);
    fn odin_ros_driver__srv__SetAwb_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<SetAwb_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<SetAwb_Request>) -> bool;
}

// Corresponds to odin_ros_driver__srv__SetAwb_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SetAwb_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub mode: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub rgain: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub bgain: f32,

}



impl Default for SetAwb_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !odin_ros_driver__srv__SetAwb_Request__init(&mut msg as *mut _) {
        panic!("Call to odin_ros_driver__srv__SetAwb_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for SetAwb_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { odin_ros_driver__srv__SetAwb_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { odin_ros_driver__srv__SetAwb_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { odin_ros_driver__srv__SetAwb_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for SetAwb_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for SetAwb_Request where Self: Sized {
  const TYPE_NAME: &'static str = "odin_ros_driver/srv/SetAwb_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__odin_ros_driver__srv__SetAwb_Request() }
  }
}


#[link(name = "odin_ros_driver__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__odin_ros_driver__srv__SetAwb_Response() -> *const std::ffi::c_void;
}

#[link(name = "odin_ros_driver__rosidl_generator_c")]
extern "C" {
    fn odin_ros_driver__srv__SetAwb_Response__init(msg: *mut SetAwb_Response) -> bool;
    fn odin_ros_driver__srv__SetAwb_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<SetAwb_Response>, size: usize) -> bool;
    fn odin_ros_driver__srv__SetAwb_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<SetAwb_Response>);
    fn odin_ros_driver__srv__SetAwb_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<SetAwb_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<SetAwb_Response>) -> bool;
}

// Corresponds to odin_ros_driver__srv__SetAwb_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SetAwb_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,

    /// 0=ok, >0=device error (400..405 or 0xFF), <0=SDK error
    pub rc: i32,

}



impl Default for SetAwb_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !odin_ros_driver__srv__SetAwb_Response__init(&mut msg as *mut _) {
        panic!("Call to odin_ros_driver__srv__SetAwb_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for SetAwb_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { odin_ros_driver__srv__SetAwb_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { odin_ros_driver__srv__SetAwb_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { odin_ros_driver__srv__SetAwb_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for SetAwb_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for SetAwb_Response where Self: Sized {
  const TYPE_NAME: &'static str = "odin_ros_driver/srv/SetAwb_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__odin_ros_driver__srv__SetAwb_Response() }
  }
}


#[link(name = "odin_ros_driver__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__odin_ros_driver__srv__GetDeviceLogs_Request() -> *const std::ffi::c_void;
}

#[link(name = "odin_ros_driver__rosidl_generator_c")]
extern "C" {
    fn odin_ros_driver__srv__GetDeviceLogs_Request__init(msg: *mut GetDeviceLogs_Request) -> bool;
    fn odin_ros_driver__srv__GetDeviceLogs_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<GetDeviceLogs_Request>, size: usize) -> bool;
    fn odin_ros_driver__srv__GetDeviceLogs_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<GetDeviceLogs_Request>);
    fn odin_ros_driver__srv__GetDeviceLogs_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<GetDeviceLogs_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<GetDeviceLogs_Request>) -> bool;
}

// Corresponds to odin_ros_driver__srv__GetDeviceLogs_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GetDeviceLogs_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub dest_dir: rosidl_runtime_rs::String,

}



impl Default for GetDeviceLogs_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !odin_ros_driver__srv__GetDeviceLogs_Request__init(&mut msg as *mut _) {
        panic!("Call to odin_ros_driver__srv__GetDeviceLogs_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for GetDeviceLogs_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { odin_ros_driver__srv__GetDeviceLogs_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { odin_ros_driver__srv__GetDeviceLogs_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { odin_ros_driver__srv__GetDeviceLogs_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for GetDeviceLogs_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for GetDeviceLogs_Request where Self: Sized {
  const TYPE_NAME: &'static str = "odin_ros_driver/srv/GetDeviceLogs_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__odin_ros_driver__srv__GetDeviceLogs_Request() }
  }
}


#[link(name = "odin_ros_driver__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__odin_ros_driver__srv__GetDeviceLogs_Response() -> *const std::ffi::c_void;
}

#[link(name = "odin_ros_driver__rosidl_generator_c")]
extern "C" {
    fn odin_ros_driver__srv__GetDeviceLogs_Response__init(msg: *mut GetDeviceLogs_Response) -> bool;
    fn odin_ros_driver__srv__GetDeviceLogs_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<GetDeviceLogs_Response>, size: usize) -> bool;
    fn odin_ros_driver__srv__GetDeviceLogs_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<GetDeviceLogs_Response>);
    fn odin_ros_driver__srv__GetDeviceLogs_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<GetDeviceLogs_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<GetDeviceLogs_Response>) -> bool;
}

// Corresponds to odin_ros_driver__srv__GetDeviceLogs_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GetDeviceLogs_Response {
    /// true if rc == 0
    pub success: bool,

    /// 0=ok, -1=invalid args, -2=transfer in progress, -3=timeout/stall
    pub rc: i32,

}



impl Default for GetDeviceLogs_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !odin_ros_driver__srv__GetDeviceLogs_Response__init(&mut msg as *mut _) {
        panic!("Call to odin_ros_driver__srv__GetDeviceLogs_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for GetDeviceLogs_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { odin_ros_driver__srv__GetDeviceLogs_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { odin_ros_driver__srv__GetDeviceLogs_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { odin_ros_driver__srv__GetDeviceLogs_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for GetDeviceLogs_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for GetDeviceLogs_Response where Self: Sized {
  const TYPE_NAME: &'static str = "odin_ros_driver/srv/GetDeviceLogs_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__odin_ros_driver__srv__GetDeviceLogs_Response() }
  }
}


#[link(name = "odin_ros_driver__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__odin_ros_driver__srv__SaveMap_Request() -> *const std::ffi::c_void;
}

#[link(name = "odin_ros_driver__rosidl_generator_c")]
extern "C" {
    fn odin_ros_driver__srv__SaveMap_Request__init(msg: *mut SaveMap_Request) -> bool;
    fn odin_ros_driver__srv__SaveMap_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<SaveMap_Request>, size: usize) -> bool;
    fn odin_ros_driver__srv__SaveMap_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<SaveMap_Request>);
    fn odin_ros_driver__srv__SaveMap_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<SaveMap_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<SaveMap_Request>) -> bool;
}

// Corresponds to odin_ros_driver__srv__SaveMap_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SaveMap_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub value: i32,

}



impl Default for SaveMap_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !odin_ros_driver__srv__SaveMap_Request__init(&mut msg as *mut _) {
        panic!("Call to odin_ros_driver__srv__SaveMap_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for SaveMap_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { odin_ros_driver__srv__SaveMap_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { odin_ros_driver__srv__SaveMap_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { odin_ros_driver__srv__SaveMap_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for SaveMap_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for SaveMap_Request where Self: Sized {
  const TYPE_NAME: &'static str = "odin_ros_driver/srv/SaveMap_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__odin_ros_driver__srv__SaveMap_Request() }
  }
}


#[link(name = "odin_ros_driver__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__odin_ros_driver__srv__SaveMap_Response() -> *const std::ffi::c_void;
}

#[link(name = "odin_ros_driver__rosidl_generator_c")]
extern "C" {
    fn odin_ros_driver__srv__SaveMap_Response__init(msg: *mut SaveMap_Response) -> bool;
    fn odin_ros_driver__srv__SaveMap_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<SaveMap_Response>, size: usize) -> bool;
    fn odin_ros_driver__srv__SaveMap_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<SaveMap_Response>);
    fn odin_ros_driver__srv__SaveMap_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<SaveMap_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<SaveMap_Response>) -> bool;
}

// Corresponds to odin_ros_driver__srv__SaveMap_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SaveMap_Response {
    /// true if the request was accepted (or rc == 0)
    pub success: bool,

    /// 0=ok, -2=another map transfer already in progress
    pub rc: i32,

}



impl Default for SaveMap_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !odin_ros_driver__srv__SaveMap_Response__init(&mut msg as *mut _) {
        panic!("Call to odin_ros_driver__srv__SaveMap_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for SaveMap_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { odin_ros_driver__srv__SaveMap_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { odin_ros_driver__srv__SaveMap_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { odin_ros_driver__srv__SaveMap_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for SaveMap_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for SaveMap_Response where Self: Sized {
  const TYPE_NAME: &'static str = "odin_ros_driver/srv/SaveMap_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__odin_ros_driver__srv__SaveMap_Response() }
  }
}


#[link(name = "odin_ros_driver__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__odin_ros_driver__srv__ResetAlgo_Request() -> *const std::ffi::c_void;
}

#[link(name = "odin_ros_driver__rosidl_generator_c")]
extern "C" {
    fn odin_ros_driver__srv__ResetAlgo_Request__init(msg: *mut ResetAlgo_Request) -> bool;
    fn odin_ros_driver__srv__ResetAlgo_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ResetAlgo_Request>, size: usize) -> bool;
    fn odin_ros_driver__srv__ResetAlgo_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ResetAlgo_Request>);
    fn odin_ros_driver__srv__ResetAlgo_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ResetAlgo_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<ResetAlgo_Request>) -> bool;
}

// Corresponds to odin_ros_driver__srv__ResetAlgo_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ResetAlgo_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub value: i32,

}



impl Default for ResetAlgo_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !odin_ros_driver__srv__ResetAlgo_Request__init(&mut msg as *mut _) {
        panic!("Call to odin_ros_driver__srv__ResetAlgo_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ResetAlgo_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { odin_ros_driver__srv__ResetAlgo_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { odin_ros_driver__srv__ResetAlgo_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { odin_ros_driver__srv__ResetAlgo_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ResetAlgo_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ResetAlgo_Request where Self: Sized {
  const TYPE_NAME: &'static str = "odin_ros_driver/srv/ResetAlgo_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__odin_ros_driver__srv__ResetAlgo_Request() }
  }
}


#[link(name = "odin_ros_driver__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__odin_ros_driver__srv__ResetAlgo_Response() -> *const std::ffi::c_void;
}

#[link(name = "odin_ros_driver__rosidl_generator_c")]
extern "C" {
    fn odin_ros_driver__srv__ResetAlgo_Response__init(msg: *mut ResetAlgo_Response) -> bool;
    fn odin_ros_driver__srv__ResetAlgo_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ResetAlgo_Response>, size: usize) -> bool;
    fn odin_ros_driver__srv__ResetAlgo_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ResetAlgo_Response>);
    fn odin_ros_driver__srv__ResetAlgo_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ResetAlgo_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<ResetAlgo_Response>) -> bool;
}

// Corresponds to odin_ros_driver__srv__ResetAlgo_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ResetAlgo_Response {
    /// true if rc == 0
    pub success: bool,

    /// 0=ok, see lidar_set_custom_parameter error codes
    pub rc: i32,

}



impl Default for ResetAlgo_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !odin_ros_driver__srv__ResetAlgo_Response__init(&mut msg as *mut _) {
        panic!("Call to odin_ros_driver__srv__ResetAlgo_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ResetAlgo_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { odin_ros_driver__srv__ResetAlgo_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { odin_ros_driver__srv__ResetAlgo_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { odin_ros_driver__srv__ResetAlgo_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ResetAlgo_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ResetAlgo_Response where Self: Sized {
  const TYPE_NAME: &'static str = "odin_ros_driver/srv/ResetAlgo_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__odin_ros_driver__srv__ResetAlgo_Response() }
  }
}






#[link(name = "odin_ros_driver__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__odin_ros_driver__srv__GetAe() -> *const std::ffi::c_void;
}

// Corresponds to odin_ros_driver__srv__GetAe
#[allow(missing_docs, non_camel_case_types)]
pub struct GetAe;

impl rosidl_runtime_rs::Service for GetAe {
    type Request = GetAe_Request;
    type Response = GetAe_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__odin_ros_driver__srv__GetAe() }
    }
}




#[link(name = "odin_ros_driver__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__odin_ros_driver__srv__GetAwb() -> *const std::ffi::c_void;
}

// Corresponds to odin_ros_driver__srv__GetAwb
#[allow(missing_docs, non_camel_case_types)]
pub struct GetAwb;

impl rosidl_runtime_rs::Service for GetAwb {
    type Request = GetAwb_Request;
    type Response = GetAwb_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__odin_ros_driver__srv__GetAwb() }
    }
}




#[link(name = "odin_ros_driver__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__odin_ros_driver__srv__SetAe() -> *const std::ffi::c_void;
}

// Corresponds to odin_ros_driver__srv__SetAe
#[allow(missing_docs, non_camel_case_types)]
pub struct SetAe;

impl rosidl_runtime_rs::Service for SetAe {
    type Request = SetAe_Request;
    type Response = SetAe_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__odin_ros_driver__srv__SetAe() }
    }
}




#[link(name = "odin_ros_driver__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__odin_ros_driver__srv__SetAwb() -> *const std::ffi::c_void;
}

// Corresponds to odin_ros_driver__srv__SetAwb
#[allow(missing_docs, non_camel_case_types)]
pub struct SetAwb;

impl rosidl_runtime_rs::Service for SetAwb {
    type Request = SetAwb_Request;
    type Response = SetAwb_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__odin_ros_driver__srv__SetAwb() }
    }
}




#[link(name = "odin_ros_driver__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__odin_ros_driver__srv__GetDeviceLogs() -> *const std::ffi::c_void;
}

// Corresponds to odin_ros_driver__srv__GetDeviceLogs
#[allow(missing_docs, non_camel_case_types)]
pub struct GetDeviceLogs;

impl rosidl_runtime_rs::Service for GetDeviceLogs {
    type Request = GetDeviceLogs_Request;
    type Response = GetDeviceLogs_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__odin_ros_driver__srv__GetDeviceLogs() }
    }
}




#[link(name = "odin_ros_driver__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__odin_ros_driver__srv__SaveMap() -> *const std::ffi::c_void;
}

// Corresponds to odin_ros_driver__srv__SaveMap
#[allow(missing_docs, non_camel_case_types)]
pub struct SaveMap;

impl rosidl_runtime_rs::Service for SaveMap {
    type Request = SaveMap_Request;
    type Response = SaveMap_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__odin_ros_driver__srv__SaveMap() }
    }
}




#[link(name = "odin_ros_driver__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__odin_ros_driver__srv__ResetAlgo() -> *const std::ffi::c_void;
}

// Corresponds to odin_ros_driver__srv__ResetAlgo
#[allow(missing_docs, non_camel_case_types)]
pub struct ResetAlgo;

impl rosidl_runtime_rs::Service for ResetAlgo {
    type Request = ResetAlgo_Request;
    type Response = ResetAlgo_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__odin_ros_driver__srv__ResetAlgo() }
    }
}


