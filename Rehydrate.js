import React, { Component } from "react";
import { connect } from "react-redux";
import { View, Text } from "react-native";

class Rehydrate extends Component {
  render() {
    return this.props.rehydrated
      ? <View style={{ flex: 1 }}>
          {this.props.children}
        </View>
      : null;
  }
}

export default connect(state => {
  return {
    rehydrated: state.rehydrate
  };
})(Rehydrate);
