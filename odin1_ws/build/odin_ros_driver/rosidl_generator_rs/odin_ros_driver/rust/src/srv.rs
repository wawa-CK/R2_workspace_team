#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};




// Corresponds to odin_ros_driver__srv__GetAe_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GetAe_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub structure_needs_at_least_one_member: u8,

}



impl Default for GetAe_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::GetAe_Request::default())
  }
}

impl rosidl_runtime_rs::Message for GetAe_Request {
  type RmwMsg = super::srv::rmw::GetAe_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        structure_needs_at_least_one_member: msg.structure_needs_at_least_one_member,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      structure_needs_at_least_one_member: msg.structure_needs_at_least_one_member,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      structure_needs_at_least_one_member: msg.structure_needs_at_least_one_member,
    }
  }
}


// Corresponds to odin_ros_driver__srv__GetAe_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::GetAe_Response::default())
  }
}

impl rosidl_runtime_rs::Message for GetAe_Response {
  type RmwMsg = super::srv::rmw::GetAe_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        success: msg.success,
        rc: msg.rc,
        exposure_time: msg.exposure_time,
        gain: msg.gain,
        iso: msg.iso,
        brightness: msg.brightness,
        is_converged: msg.is_converged,
        env_lv: msg.env_lv,
        fps: msg.fps,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      success: msg.success,
      rc: msg.rc,
      exposure_time: msg.exposure_time,
      gain: msg.gain,
      iso: msg.iso,
      brightness: msg.brightness,
      is_converged: msg.is_converged,
      env_lv: msg.env_lv,
      fps: msg.fps,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      success: msg.success,
      rc: msg.rc,
      exposure_time: msg.exposure_time,
      gain: msg.gain,
      iso: msg.iso,
      brightness: msg.brightness,
      is_converged: msg.is_converged,
      env_lv: msg.env_lv,
      fps: msg.fps,
    }
  }
}


// Corresponds to odin_ros_driver__srv__GetAwb_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GetAwb_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub structure_needs_at_least_one_member: u8,

}



impl Default for GetAwb_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::GetAwb_Request::default())
  }
}

impl rosidl_runtime_rs::Message for GetAwb_Request {
  type RmwMsg = super::srv::rmw::GetAwb_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        structure_needs_at_least_one_member: msg.structure_needs_at_least_one_member,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      structure_needs_at_least_one_member: msg.structure_needs_at_least_one_member,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      structure_needs_at_least_one_member: msg.structure_needs_at_least_one_member,
    }
  }
}


// Corresponds to odin_ros_driver__srv__GetAwb_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::GetAwb_Response::default())
  }
}

impl rosidl_runtime_rs::Message for GetAwb_Response {
  type RmwMsg = super::srv::rmw::GetAwb_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        success: msg.success,
        rc: msg.rc,
        rgain: msg.rgain,
        grgain: msg.grgain,
        gbgain: msg.gbgain,
        bgain: msg.bgain,
        cct: msg.cct,
        ccri: msg.ccri,
        is_converged: msg.is_converged,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      success: msg.success,
      rc: msg.rc,
      rgain: msg.rgain,
      grgain: msg.grgain,
      gbgain: msg.gbgain,
      bgain: msg.bgain,
      cct: msg.cct,
      ccri: msg.ccri,
      is_converged: msg.is_converged,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      success: msg.success,
      rc: msg.rc,
      rgain: msg.rgain,
      grgain: msg.grgain,
      gbgain: msg.gbgain,
      bgain: msg.bgain,
      cct: msg.cct,
      ccri: msg.ccri,
      is_converged: msg.is_converged,
    }
  }
}


// Corresponds to odin_ros_driver__srv__SetAe_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::SetAe_Request::default())
  }
}

impl rosidl_runtime_rs::Message for SetAe_Request {
  type RmwMsg = super::srv::rmw::SetAe_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        mode: msg.mode,
        exposure_time: msg.exposure_time,
        gain: msg.gain,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      mode: msg.mode,
      exposure_time: msg.exposure_time,
      gain: msg.gain,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      mode: msg.mode,
      exposure_time: msg.exposure_time,
      gain: msg.gain,
    }
  }
}


// Corresponds to odin_ros_driver__srv__SetAe_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::SetAe_Response::default())
  }
}

impl rosidl_runtime_rs::Message for SetAe_Response {
  type RmwMsg = super::srv::rmw::SetAe_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        success: msg.success,
        rc: msg.rc,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      success: msg.success,
      rc: msg.rc,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      success: msg.success,
      rc: msg.rc,
    }
  }
}


// Corresponds to odin_ros_driver__srv__SetAwb_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::SetAwb_Request::default())
  }
}

impl rosidl_runtime_rs::Message for SetAwb_Request {
  type RmwMsg = super::srv::rmw::SetAwb_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        mode: msg.mode,
        rgain: msg.rgain,
        bgain: msg.bgain,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      mode: msg.mode,
      rgain: msg.rgain,
      bgain: msg.bgain,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      mode: msg.mode,
      rgain: msg.rgain,
      bgain: msg.bgain,
    }
  }
}


// Corresponds to odin_ros_driver__srv__SetAwb_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::SetAwb_Response::default())
  }
}

impl rosidl_runtime_rs::Message for SetAwb_Response {
  type RmwMsg = super::srv::rmw::SetAwb_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        success: msg.success,
        rc: msg.rc,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      success: msg.success,
      rc: msg.rc,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      success: msg.success,
      rc: msg.rc,
    }
  }
}


// Corresponds to odin_ros_driver__srv__GetDeviceLogs_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GetDeviceLogs_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub dest_dir: std::string::String,

}



impl Default for GetDeviceLogs_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::GetDeviceLogs_Request::default())
  }
}

impl rosidl_runtime_rs::Message for GetDeviceLogs_Request {
  type RmwMsg = super::srv::rmw::GetDeviceLogs_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        dest_dir: msg.dest_dir.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        dest_dir: msg.dest_dir.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      dest_dir: msg.dest_dir.to_string(),
    }
  }
}


// Corresponds to odin_ros_driver__srv__GetDeviceLogs_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GetDeviceLogs_Response {
    /// true if rc == 0
    pub success: bool,

    /// 0=ok, -1=invalid args, -2=transfer in progress, -3=timeout/stall
    pub rc: i32,

}



impl Default for GetDeviceLogs_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::GetDeviceLogs_Response::default())
  }
}

impl rosidl_runtime_rs::Message for GetDeviceLogs_Response {
  type RmwMsg = super::srv::rmw::GetDeviceLogs_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        success: msg.success,
        rc: msg.rc,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      success: msg.success,
      rc: msg.rc,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      success: msg.success,
      rc: msg.rc,
    }
  }
}


// Corresponds to odin_ros_driver__srv__SaveMap_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SaveMap_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub value: i32,

}



impl Default for SaveMap_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::SaveMap_Request::default())
  }
}

impl rosidl_runtime_rs::Message for SaveMap_Request {
  type RmwMsg = super::srv::rmw::SaveMap_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        value: msg.value,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      value: msg.value,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      value: msg.value,
    }
  }
}


// Corresponds to odin_ros_driver__srv__SaveMap_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SaveMap_Response {
    /// true if the request was accepted (or rc == 0)
    pub success: bool,

    /// 0=ok, -2=another map transfer already in progress
    pub rc: i32,

}



impl Default for SaveMap_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::SaveMap_Response::default())
  }
}

impl rosidl_runtime_rs::Message for SaveMap_Response {
  type RmwMsg = super::srv::rmw::SaveMap_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        success: msg.success,
        rc: msg.rc,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      success: msg.success,
      rc: msg.rc,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      success: msg.success,
      rc: msg.rc,
    }
  }
}


// Corresponds to odin_ros_driver__srv__ResetAlgo_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ResetAlgo_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub value: i32,

}



impl Default for ResetAlgo_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::ResetAlgo_Request::default())
  }
}

impl rosidl_runtime_rs::Message for ResetAlgo_Request {
  type RmwMsg = super::srv::rmw::ResetAlgo_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        value: msg.value,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      value: msg.value,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      value: msg.value,
    }
  }
}


// Corresponds to odin_ros_driver__srv__ResetAlgo_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ResetAlgo_Response {
    /// true if rc == 0
    pub success: bool,

    /// 0=ok, see lidar_set_custom_parameter error codes
    pub rc: i32,

}



impl Default for ResetAlgo_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::ResetAlgo_Response::default())
  }
}

impl rosidl_runtime_rs::Message for ResetAlgo_Response {
  type RmwMsg = super::srv::rmw::ResetAlgo_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        success: msg.success,
        rc: msg.rc,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      success: msg.success,
      rc: msg.rc,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      success: msg.success,
      rc: msg.rc,
    }
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


