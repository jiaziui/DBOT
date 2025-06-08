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

class robot_control {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.robot_control_date = null;
      this.robot_speed = null;
    }
    else {
      if (initObj.hasOwnProperty('robot_control_date')) {
        this.robot_control_date = initObj.robot_control_date
      }
      else {
        this.robot_control_date = 0;
      }
      if (initObj.hasOwnProperty('robot_speed')) {
        this.robot_speed = initObj.robot_speed
      }
      else {
        this.robot_speed = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type robot_control
    // Serialize message field [robot_control_date]
    bufferOffset = _serializer.int32(obj.robot_control_date, buffer, bufferOffset);
    // Serialize message field [robot_speed]
    bufferOffset = _serializer.int32(obj.robot_speed, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type robot_control
    let len;
    let data = new robot_control(null);
    // Deserialize message field [robot_control_date]
    data.robot_control_date = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [robot_speed]
    data.robot_speed = _deserializer.int32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 8;
  }

  static datatype() {
    // Returns string type for a message object
    return 'robot_manager/robot_control';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'dfb01f34da152f6ce58d56cb22596b17';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int32 robot_control_date
    int32 robot_speed
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new robot_control(null);
    if (msg.robot_control_date !== undefined) {
      resolved.robot_control_date = msg.robot_control_date;
    }
    else {
      resolved.robot_control_date = 0
    }

    if (msg.robot_speed !== undefined) {
      resolved.robot_speed = msg.robot_speed;
    }
    else {
      resolved.robot_speed = 0
    }

    return resolved;
    }
};

module.exports = robot_control;
