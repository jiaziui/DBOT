// Auto-generated. Do not edit!

// (in-package robot_manager.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class robot_state {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.robot_electricity = null;
      this.robot_state = null;
      this.robot_driver_state = null;
      this.robot_camera_state = null;
    }
    else {
      if (initObj.hasOwnProperty('robot_electricity')) {
        this.robot_electricity = initObj.robot_electricity
      }
      else {
        this.robot_electricity = 0.0;
      }
      if (initObj.hasOwnProperty('robot_state')) {
        this.robot_state = initObj.robot_state
      }
      else {
        this.robot_state = 0;
      }
      if (initObj.hasOwnProperty('robot_driver_state')) {
        this.robot_driver_state = initObj.robot_driver_state
      }
      else {
        this.robot_driver_state = 0;
      }
      if (initObj.hasOwnProperty('robot_camera_state')) {
        this.robot_camera_state = initObj.robot_camera_state
      }
      else {
        this.robot_camera_state = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type robot_state
    // Serialize message field [robot_electricity]
    bufferOffset = _serializer.float32(obj.robot_electricity, buffer, bufferOffset);
    // Serialize message field [robot_state]
    bufferOffset = _serializer.int32(obj.robot_state, buffer, bufferOffset);
    // Serialize message field [robot_driver_state]
    bufferOffset = _serializer.int32(obj.robot_driver_state, buffer, bufferOffset);
    // Serialize message field [robot_camera_state]
    bufferOffset = _serializer.int32(obj.robot_camera_state, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type robot_state
    let len;
    let data = new robot_state(null);
    // Deserialize message field [robot_electricity]
    data.robot_electricity = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [robot_state]
    data.robot_state = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [robot_driver_state]
    data.robot_driver_state = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [robot_camera_state]
    data.robot_camera_state = _deserializer.int32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 16;
  }

  static datatype() {
    // Returns string type for a message object
    return 'robot_manager/robot_state';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '5bad53ba22220257c1d7f0639451f8f3';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32 robot_electricity
    int32 robot_state
    int32 robot_driver_state
    int32 robot_camera_state
    
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new robot_state(null);
    if (msg.robot_electricity !== undefined) {
      resolved.robot_electricity = msg.robot_electricity;
    }
    else {
      resolved.robot_electricity = 0.0
    }

    if (msg.robot_state !== undefined) {
      resolved.robot_state = msg.robot_state;
    }
    else {
      resolved.robot_state = 0
    }

    if (msg.robot_driver_state !== undefined) {
      resolved.robot_driver_state = msg.robot_driver_state;
    }
    else {
      resolved.robot_driver_state = 0
    }

    if (msg.robot_camera_state !== undefined) {
      resolved.robot_camera_state = msg.robot_camera_state;
    }
    else {
      resolved.robot_camera_state = 0
    }

    return resolved;
    }
};

module.exports = robot_state;
