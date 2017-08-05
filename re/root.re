open ReactNative;

let scheduleIcon config =>
  <Icon name="calendar" size=36 color=config##tintColor style=Style.(style [marginTop 5.]) />;

let locationIcon config =>
  <Icon name="location" size=36 color=config##tintColor style=Style.(style [marginTop 5.]) />;

let infoIcon config =>
  <Icon name="question" size=36 color=config##tintColor style=Style.(style [marginTop 5.]) />;

let routeConfig: TabNavigator.routesConfig = {
  "schedule": {
    "screen": Schedule.wrappedComponent,
    "navigationOptions": {"tabBarLabel": "Schedule", "tabBarIcon": scheduleIcon}
  },
  "location": {
    "screen": Location.jsComponent,
    "navigationOptions": {"tabBarLabel": "Location", "tabBarIcon": locationIcon}
  },
  "info": {
    "screen": Info.jsComponent,
    "navigationOptions": {"tabBarLabel": "Info", "tabBarIcon": infoIcon}
  }
};

let navConfig: TabNavigator.navConfig = {
  "animationEnabled": Js.true_,
  "tabBarOptions": {
    "activeTintColor": "rgb(185,219,111)",
    "inactiveTintColor": "rgba(255,255,255, .5)",
    "activeBackgroundColor": "rgb(54, 97, 115)",
    "inactiveBackgroundColor": "rgb(75, 118, 134)"
  },
  "tabBarPosition": "bottom",
  "tabBarComponent": TabNavigator.tabBarBottom
};

let component = TabNavigator.create ::routeConfig ::navConfig;
