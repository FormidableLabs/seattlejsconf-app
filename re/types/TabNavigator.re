type config = Js.t {. tintColor : string};

type routeConfig =
  Js.t {
    .
    screen : ReasonReact.reactClass,
    navigationOptions :
      Js.t {. tabBarLabel : string, tabBarIcon : config => ReasonReact.reactElement}
  };

type routesConfig = Js.t {. schedule : routeConfig, location : routeConfig, info : routeConfig};

type tabBarOptions =
  Js.t {
    .
    activeTintColor : string,
    inactiveTintColor : string,
    activeBackgroundColor : string,
    inactiveBackgroundColor : string
  };

type navConfig =
  Js.t {
    .
    animationEnabled : Js.boolean,
    tabBarOptions : tabBarOptions,
    tabBarPosition : string,
    tabBarComponent : ReasonReact.reactClass
  };

external _tabNavigator : routesConfig => navConfig => ReasonReact.reactClass =
  "TabNavigator" [@@bs.module "react-navigation"];

external tabBarBottom : ReasonReact.reactClass = "TabBarBottom" [@@bs.module "react-navigation"];

let create ::routeConfig ::navConfig => _tabNavigator routeConfig navConfig;
