type config = {. "tintColor": string};

type routeConfig = {
  .
  "screen": ReasonReact.reactClass,
  "navigationOptions": {
    .
    "tabBarLabel": string,
    "tabBarIcon": config => ReasonReact.reactElement
  }
};

type routesConfig = {
  .
  "schedule": routeConfig,
  "location": routeConfig,
  "info": routeConfig
};

type tabBarOptions = {
  .
  "activeTintColor": string,
  "inactiveTintColor": string,
  "activeBackgroundColor": string,
  "inactiveBackgroundColor": string
};

type navConfig = {
  .
  "animationEnabled": Js.boolean,
  "tabBarOptions": tabBarOptions,
  "tabBarPosition": string,
  "tabBarComponent": ReasonReact.reactClass
};

[@bs.module "react-navigation"]
external _tabNavigator : (routesConfig, navConfig) => ReasonReact.reactClass = "TabNavigator";

[@bs.module "react-navigation"] external tabBarBottom : ReasonReact.reactClass = "TabBarBottom";

let create = (~routeConfig, ~navConfig) => _tabNavigator(routeConfig, navConfig);
