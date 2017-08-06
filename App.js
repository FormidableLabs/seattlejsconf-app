import React from "react";
import { View, Text } from "react-native";
import ApolloClient, { createNetworkInterface } from "apollo-client";
import { ApolloProvider } from "react-apollo";
import { Font } from "expo";
import { compose, createStore, combineReducers, applyMiddleware } from "redux";
import { offline } from "redux-offline";
import config from "redux-offline/lib/defaults";

import Rehydrate from "./Rehydrate";
import { component as Root } from "./lib/js/re/root";

console.ignoredYellowBox = [
  "Warning: View.propTypes has been deprecated and will be removed in a future version of ReactNative. Use ViewPropTypes instead."
];

const networkInterface = createNetworkInterface({
  uri: `https://api.graph.cool/simple/v1/cj5cm0t4pnljk01087tv4g61a`
});

const client = new ApolloClient({
  networkInterface
});

const store = createStore(
  combineReducers({
    apollo: client.reducer(),
    rehydrate: (state = false, action) => {
      switch (action.type) {
        case "REHYDRATE_STORE":
          return true;
        default:
          return state;
      }
    }
  }),
  undefined,
  compose(
    applyMiddleware(client.middleware()),
    offline({
      ...config,
      persistCallback: () => {
        store.dispatch({ type: "REHYDRATE_STORE" });
      },
      persistOptions: {
        blacklist: ["rehydrate"]
      }
    })
  )
);

export default class App extends React.Component {
  state = {
    fontLoaded: false
  };

  async componentDidMount() {
    await Font.loadAsync({
      "open-sans": require("./static/OpenSans-Regular.ttf"),
      "open-sans-bold": require("./static/OpenSans-Bold.ttf"),
      montserrat: require("./static/Montserrat-Regular.ttf"),
      "montserrat-bold": require("./static/Montserrat-Bold.ttf")
    });

    this.setState({
      fontLoaded: true
    });
  }

  render() {
    return (
      <View style={{ flex: 1, backgroundColor: "rgb(54, 97, 115)" }}>
        <ApolloProvider client={client} store={store}>
          <Rehydrate>
            {this.state.fontLoaded ? <Root /> : null}
          </Rehydrate>
        </ApolloProvider>
      </View>
    );
    return;
  }
}
