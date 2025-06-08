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

class robot_speaker {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.chinese_text = null;
      this.msg_buffer_flag = null;
      this.msg_clear_buffer_flag = null;
    }
    else {
      if (initObj.hasOwnProperty('chinese_text')) {
        this.chinese_text = initObj.chinese_text
      }
      else {
        this.chinese_text = '';
      }
      if (initObj.hasOwnProperty('msg_buffer_flag')) {
        this.msg_buffer_flag = initObj.msg_buffer_flag
      }
      else {
        this.msg_buffer_flag = 0;
      }
      if (initObj.hasOwnProperty('msg_clear_buffer_flag')) {
        this.msg_clear_buffer_flag = initObj.msg_clear_buffer_flag
      }
      else {
        this.msg_clear_buffer_flag = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type robot_speaker
    // Serialize message field [chinese_text]
    bufferOffset = _serializer.string(obj.chinese_text, buffer, bufferOffset);
    // Serialize message field [msg_buffer_flag]
    bufferOffset = _serializer.int32(obj.msg_buffer_flag, buffer, bufferOffset);
    // Serialize message field [msg_clear_buffer_flag]
    bufferOffset = _serializer.int32(obj.msg_clear_buffer_flag, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type robot_speaker
    let len;
    let data = new robot_speaker(null);
    // Deserialize message field [chinese_text]
    data.chinese_text = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [msg_buffer_flag]
    data.msg_buffer_flag = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [msg_clear_buffer_flag]
    data.msg_clear_buffer_flag = _deserializer.int32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += _getByteLength(object.chinese_text);
    return length + 12;
  }

  static datatype() {
    // Returns string type for a message object
    return 'robot_manager/robot_speaker';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '40c45f84b5c08c0a75df65acb133f8c5';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string chinese_text
    int32 msg_buffer_flag
    int32 msg_clear_buffer_flag
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new robot_speaker(null);
    if (msg.chinese_text !== undefined) {
      resolved.chinese_text = msg.chinese_text;
    }
    else {
      resolved.chinese_text = ''
    }

    if (msg.msg_buffer_flag !== undefined) {
      resolved.msg_buffer_flag = msg.msg_buffer_flag;
    }
    else {
      resolved.msg_buffer_flag = 0
    }

    if (msg.msg_clear_buffer_flag !== undefined) {
      resolved.msg_clear_buffer_flag = msg.msg_clear_buffer_flag;
    }
    else {
      resolved.msg_clear_buffer_flag = 0
    }

    return resolved;
    }
};

module.exports = robot_speaker;
