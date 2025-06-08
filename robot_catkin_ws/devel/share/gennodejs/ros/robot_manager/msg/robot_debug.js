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

class robot_debug {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.servo_run_power = null;
      this.robot_landF = null;
      this.robot_landB = null;
      this.robot_fhMax = null;
      this.robot_swMax = null;
      this.robot_sport_state = null;
      this.robot_fwctUp = null;
      this.robot_control = null;
      this.robot_fwctEnd = null;
    }
    else {
      if (initObj.hasOwnProperty('servo_run_power')) {
        this.servo_run_power = initObj.servo_run_power
      }
      else {
        this.servo_run_power = 0;
      }
      if (initObj.hasOwnProperty('robot_landF')) {
        this.robot_landF = initObj.robot_landF
      }
      else {
        this.robot_landF = 0;
      }
      if (initObj.hasOwnProperty('robot_landB')) {
        this.robot_landB = initObj.robot_landB
      }
      else {
        this.robot_landB = 0;
      }
      if (initObj.hasOwnProperty('robot_fhMax')) {
        this.robot_fhMax = initObj.robot_fhMax
      }
      else {
        this.robot_fhMax = 0;
      }
      if (initObj.hasOwnProperty('robot_swMax')) {
        this.robot_swMax = initObj.robot_swMax
      }
      else {
        this.robot_swMax = 0;
      }
      if (initObj.hasOwnProperty('robot_sport_state')) {
        this.robot_sport_state = initObj.robot_sport_state
      }
      else {
        this.robot_sport_state = 0;
      }
      if (initObj.hasOwnProperty('robot_fwctUp')) {
        this.robot_fwctUp = initObj.robot_fwctUp
      }
      else {
        this.robot_fwctUp = 0;
      }
      if (initObj.hasOwnProperty('robot_control')) {
        this.robot_control = initObj.robot_control
      }
      else {
        this.robot_control = 0;
      }
      if (initObj.hasOwnProperty('robot_fwctEnd')) {
        this.robot_fwctEnd = initObj.robot_fwctEnd
      }
      else {
        this.robot_fwctEnd = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type robot_debug
    // Serialize message field [servo_run_power]
    bufferOffset = _serializer.int32(obj.servo_run_power, buffer, bufferOffset);
    // Serialize message field [robot_landF]
    bufferOffset = _serializer.int32(obj.robot_landF, buffer, bufferOffset);
    // Serialize message field [robot_landB]
    bufferOffset = _serializer.int32(obj.robot_landB, buffer, bufferOffset);
    // Serialize message field [robot_fhMax]
    bufferOffset = _serializer.int32(obj.robot_fhMax, buffer, bufferOffset);
    // Serialize message field [robot_swMax]
    bufferOffset = _serializer.int32(obj.robot_swMax, buffer, bufferOffset);
    // Serialize message field [robot_sport_state]
    bufferOffset = _serializer.int32(obj.robot_sport_state, buffer, bufferOffset);
    // Serialize message field [robot_fwctUp]
    bufferOffset = _serializer.int32(obj.robot_fwctUp, buffer, bufferOffset);
    // Serialize message field [robot_control]
    bufferOffset = _serializer.int32(obj.robot_control, buffer, bufferOffset);
    // Serialize message field [robot_fwctEnd]
    bufferOffset = _serializer.int32(obj.robot_fwctEnd, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type robot_debug
    let len;
    let data = new robot_debug(null);
    // Deserialize message field [servo_run_power]
    data.servo_run_power = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [robot_landF]
    data.robot_landF = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [robot_landB]
    data.robot_landB = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [robot_fhMax]
    data.robot_fhMax = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [robot_swMax]
    data.robot_swMax = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [robot_sport_state]
    data.robot_sport_state = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [robot_fwctUp]
    data.robot_fwctUp = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [robot_control]
    data.robot_control = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [robot_fwctEnd]
    data.robot_fwctEnd = _deserializer.int32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 36;
  }

  static datatype() {
    // Returns string type for a message object
    return 'robot_manager/robot_debug';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '2f2e39311972ce7b431a280d95b132fa';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int32 servo_run_power
    int32 robot_landF
    int32 robot_landB
    int32 robot_fhMax
    int32 robot_swMax
    int32 robot_sport_state
    int32 robot_fwctUp
    int32 robot_control
    int32 robot_fwctEnd
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new robot_debug(null);
    if (msg.servo_run_power !== undefined) {
      resolved.servo_run_power = msg.servo_run_power;
    }
    else {
      resolved.servo_run_power = 0
    }

    if (msg.robot_landF !== undefined) {
      resolved.robot_landF = msg.robot_landF;
    }
    else {
      resolved.robot_landF = 0
    }

    if (msg.robot_landB !== undefined) {
      resolved.robot_landB = msg.robot_landB;
    }
    else {
      resolved.robot_landB = 0
    }

    if (msg.robot_fhMax !== undefined) {
      resolved.robot_fhMax = msg.robot_fhMax;
    }
    else {
      resolved.robot_fhMax = 0
    }

    if (msg.robot_swMax !== undefined) {
      resolved.robot_swMax = msg.robot_swMax;
    }
    else {
      resolved.robot_swMax = 0
    }

    if (msg.robot_sport_state !== undefined) {
      resolved.robot_sport_state = msg.robot_sport_state;
    }
    else {
      resolved.robot_sport_state = 0
    }

    if (msg.robot_fwctUp !== undefined) {
      resolved.robot_fwctUp = msg.robot_fwctUp;
    }
    else {
      resolved.robot_fwctUp = 0
    }

    if (msg.robot_control !== undefined) {
      resolved.robot_control = msg.robot_control;
    }
    else {
      resolved.robot_control = 0
    }

    if (msg.robot_fwctEnd !== undefined) {
      resolved.robot_fwctEnd = msg.robot_fwctEnd;
    }
    else {
      resolved.robot_fwctEnd = 0
    }

    return resolved;
    }
};

module.exports = robot_debug;
